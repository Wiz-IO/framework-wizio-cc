#include "AES_ECB_128.h"

static uint8_t sUsedKeys = 0;

#define CRYPTO_DMA_IN_DONE 0x00000002    // DMA done interrupt mask
#define CRYPTO_RESULT_RDY 0x00000001     // Result ready interrupt mask
#define CRYPTO_DMA_BUS_ERR 0x80000000    // DMA Bus error
#define CRYPTO_KEY_ST_WR_ERR 0x40000000  // Key Store Write failed
#define CRYPTO_KEY_ST_RD_ERR 0x20000000  // Key Store Read failed
#define CRYPTO_IRQTYPE_LEVEL 0x00000001  // Crypto Level interrupt enabled
#define CRYPTO_IRQTYPE_PULSE 0x00000000  // Crypto pulse interrupt enabled
#define CRYPTO_DMA_CHAN0 0x00000001      // Crypto DMA Channel 0
#define CRYPTO_DMA_CHAN1 0x00000002      // Crypto DMA Channel 1
#define CRYPTO_AES128_ENCRYPT 0x0000000C //
#define CRYPTO_AES128_DECRYPT 0x00000008 //
#define CRYPTO_DMA_READY 0x00000000      // DMA ready
#define CRYPTO_DMA_BSY 0x00000003        // DMA busy
#define CRYPTO_DMA_BUS_ERROR 0x00020000  // DMA encountered bus error

// AES module return codes
#define AES_SUCCESS 0
#define AES_KEYSTORE_READ_ERROR 1
#define AES_KEYSTORE_WRITE_ERROR 2
#define AES_DMA_BUS_ERROR 3
#define CCM_AUTHENTICATION_FAILED 4
#define AES_ECB_TEST_ERROR 8
#define AES_NULL_ERROR 9
#define AES_CCM_TEST_ERROR 10
#define AES_DMA_BSY 11

static uint32_t AesEcbStatus(void)
{
    uint32_t ui32Status;
    // Get the current DMA status.
    ui32Status = HWREG(CRYPTO_BASE + CRYPTO_O_DMASTAT);
    // Check if DMA is still busy.
    if (ui32Status & CRYPTO_DMA_BSY)
    {
        return (AES_DMA_BSY);
    }
    // Check the status of the DMA operation - return error if not success.
    if (ui32Status & CRYPTO_DMA_BUS_ERROR)
    {
        return (AES_DMA_BUS_ERROR);
    }
    // Operation successful - disable interrupt and return success.
    IntDisable(INT_CRYPTO_RESULT_AVAIL_IRQ);
    return (AES_SUCCESS);
}

__STATIC_INLINE void AesEcbFinish(void)
{
    // Result has already been copied to the output buffer by DMA.
    // Disable master control/DMA clock and clear the operating mode.
    HWREG(CRYPTO_BASE + CRYPTO_O_ALGSEL) = 0x00000000;
    HWREG(CRYPTO_BASE + CRYPTO_O_AESCTL) = 0x00000000;
}

static uint32_t AesEcb(uint32_t *input,
                       uint32_t *output,
                       uint32_t ui32KeyLocation,
                       bool bEncrypt)
{
    IntDisable(INT_CRYPTO_RESULT_AVAIL_IRQ); // here not have isr_handle()
    IntPendClear(INT_CRYPTO_RESULT_AVAIL_IRQ);
    AESIntClear(AES_RESULT_RDY | AES_DMA_IN_DONE | AES_DMA_BUS_ERR);
    AESSelectAlgorithm(AES_ALGSEL_AES);
    if (AESReadFromKeyStore(ui32KeyLocation) != AES_SUCCESS)
    {
        //printf("[ERROR] %s()\n", __func__);
        return AES_KEYSTORE_READ_ERROR;
    }
    AESSetCtrl(bEncrypt ? CRYPTO_AESCTL_DIR : 0); // If set to 1 an encrypt operation is performed.
    AESSetDataLength(AES_ECB_LENGTH);
    AESStartDMAOperation((uint8_t *)input, AES_ECB_LENGTH, (uint8_t *)output, AES_ECB_LENGTH);
    return AES_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int aes_setkey_enc(aes_context *ctx, const unsigned char *key, unsigned int keybits)
{
    unsigned char key_idx;
    if (ctx->magic != CC2652_AES_CTX_MAGIC)
        return -1;
    if (ctx->key_idx != CC2652_AES_KEY_UNUSED)
        sUsedKeys &= ~(1 << ctx->key_idx);
    if (keybits != 128u) /* our hardware only supports 128 bit keys */
        return -1;
    for (key_idx = 0; ((sUsedKeys >> key_idx) & 0x01) != 0 && key_idx < 8; key_idx++)
        ;
    if (key_idx >= 8) /* we have no more room for this key */
        return -2;
    if (AESWriteToKeyStore((uint8_t *)key, AES_128_KEY_LENGTH_BYTES, key_idx) != AES_SUCCESS)
        return -3;
    sUsedKeys |= (1 << key_idx);
    ctx->key_idx = key_idx;
    return 0;
}

int aes_setkey_dec(aes_context *ctx, const unsigned char *key, unsigned int keybits)
{
    unsigned char key_idx;
    if (ctx->magic != CC2652_AES_CTX_MAGIC)
        return -1;
    if (ctx->key_idx != CC2652_AES_KEY_UNUSED)
        sUsedKeys &= ~(1 << ctx->key_idx);
    if (keybits != 128u) /* our hardware only supports 128 bit keys */
        return -2;
    for (key_idx = 0; ((sUsedKeys >> key_idx) & 0x01) != 0 && key_idx < 8; key_idx++)
        ;
    if (key_idx >= 8) /* we have no more room for this key */
        return -3;
    if (AESWriteToKeyStore((uint8_t *)key, AES_128_KEY_LENGTH_BYTES, key_idx) != AES_SUCCESS)
        return -4;
    sUsedKeys |= (1 << key_idx);
    ctx->key_idx = key_idx;
    return 0;
}

int aes_crypt_ecb(aes_context *ctx, int mode, const unsigned char input[16], unsigned char output[16])
{
    int retval = -1;
    retval = AesEcb((uint32_t *)input, (uint32_t *)output, ctx->key_idx, mode == AES_ENCRYPT);
    if (retval == AES_SUCCESS)
    {
        while ((retval = AesEcbStatus()) == AES_DMA_BSY)
            ;
        AesEcbFinish();
        retval = AES_SUCCESS;
    }
    return retval;
}

void aes_init(aes_context *ctx)
{
    ctx->magic = CC2652_AES_CTX_MAGIC;
    ctx->key_idx = CC2652_AES_KEY_UNUSED;
    soc_power_on_periphery(PRCM_PERIPH_CRYPTO, 1, 0, 0);
}

void aes_free(aes_context *ctx)
{
    if (ctx->magic == CC2652_AES_CTX_MAGIC)
    {
        soc_power_off_periphery(PRCM_PERIPH_CRYPTO, 1, 0, 0);
        if (ctx->key_idx != CC2652_AES_KEY_UNUSED)
            sUsedKeys &= ~(1 << ctx->key_idx);
        memset((void *)ctx, 0x00, sizeof(ctx));
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//__attribute__((aligned(4)))
static const unsigned char aes_test_ecb_dec[3][16] = {
    {0x44, 0x41, 0x6A, 0xC2, 0xD1, 0xF5, 0x3C, 0x58,
     0x33, 0x03, 0x91, 0x7E, 0x6B, 0xE9, 0xEB, 0xE0},
    {0x48, 0xE3, 0x1E, 0x9E, 0x25, 0x67, 0x18, 0xF2,
     0x92, 0x29, 0x31, 0x9C, 0x19, 0xF1, 0x5B, 0xA4},
    {0x05, 0x8C, 0xCF, 0xFD, 0xBB, 0xCB, 0x38, 0x2D,
     0x1F, 0x6F, 0x56, 0x58, 0x5D, 0x8A, 0x4A, 0xDE}};

//__attribute__((aligned(4)))
static const unsigned char aes_test_ecb_enc[3][16] = {
    {0xC3, 0x4C, 0x05, 0x2C, 0xC0, 0xDA, 0x8D, 0x73,
     0x45, 0x1A, 0xFE, 0x5F, 0x03, 0xBE, 0x29, 0x7F},
    {0xF3, 0xF6, 0x75, 0x2A, 0xE8, 0xD7, 0x83, 0x11,
     0x38, 0xF0, 0x41, 0x56, 0x06, 0x31, 0xB1, 0x14},
    {0x8B, 0x79, 0xEE, 0xCC, 0x93, 0xA0, 0xEE, 0x5D,
     0xFF, 0x30, 0xB4, 0xEA, 0x21, 0x63, 0x6D, 0xA4}};

int aes_ecb_128_self_test(int verbose)
{
    printf("[AES] %s()\n", __func__);

    aes_context ctx;
    int ret = 0, i, j, u, v, res;
    unsigned char buf[64];
    unsigned char key[32];
    memset(key, 0, 32);

    aes_init(&ctx);

    for (i = 0; i < 6; i++)
    {
        u = i >> 1;
        v = i & 1;

        if (verbose != 0)
            printf("  AES-ECB-%3d ( %s ): ", 128 + u * 64, (v == AES_DECRYPT) ? "decrypt" : "encrypt");

        memset(buf, 0, 16);

        if (v == AES_DECRYPT)
        {
            res = aes_setkey_dec(&ctx, key, 128 + u * 64);
            for (j = 0; j < 10000; j++)
            {
                res = aes_crypt_ecb(&ctx, v, buf, buf);
            }
            if (memcmp(buf, aes_test_ecb_dec[u], 16) != 0)
            {
                if (verbose != 0)
                    printf("FAILED\n");
                ret = 1;
                goto exit;
            }
        }
        else
        {
            res = aes_setkey_enc(&ctx, key, 128 + u * 64);
            for (j = 0; j < 10000; j++)
            {
                res = aes_crypt_ecb(&ctx, v, buf, buf);
            }
            if (memcmp(buf, aes_test_ecb_enc[u], 16) != 0)
            {
                if (verbose != 0)
                    printf("FAILED\n");
                ret = 1;
                goto exit;
            }
        }
        if (verbose != 0)
            printf("passed\n");
    }
    if (verbose != 0)
        printf("\n");

exit:
    aes_free(&ctx);
    return (ret);
}
