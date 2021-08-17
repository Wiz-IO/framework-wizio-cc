#include <interface.h>
#include <driverlib/aes.h>

typedef struct
{
    uint8_t magic;
    signed char key_idx;
} aes_context;

#define CC2652_AES_KEY_UNUSED (-1)
#define CC2652_AES_CTX_MAGIC (0x7E)

#define AES_ENCRYPT 1
#define AES_DECRYPT 0
#define AES_ECB_LENGTH 16

void aes_init(aes_context *ctx);
void aes_free(aes_context *ctx);
int aes_crypt_ecb(aes_context *ctx, int mode, const unsigned char input[16], unsigned char output[16]);
int aes_setkey_dec(aes_context *ctx, const unsigned char *key, unsigned int keybits);
int aes_setkey_enc(aes_context *ctx, const unsigned char *key, unsigned int keybits);

int aes_ecb_128_self_test(int verbose);

class AesEcb128
{
private:
    aes_context mContext;
    bool key_is_set;
    uint8_t Key[16];

public:
    AesEcb128(void)
    {
        key_is_set = false;
        aes_init(&mContext);
    }
    AesEcb128(const char aKey[16])
    {
        memcpy(Key, aKey, 16);
        key_is_set = true;
        aes_init(&mContext);
    }
    AesEcb128(const uint8_t aKey[16])
    {
        memcpy(Key, aKey, 16);
        key_is_set = true;
        aes_init(&mContext);
    }

    ~AesEcb128(void) { aes_free(&mContext); }

    ///////////////////////////////////////////////////////////////////////////////////////

    bool SetEncKey(const char aKey[16]) { return aes_setkey_enc(&mContext, (uint8_t *)aKey, 128) == 0; }
    bool SetEncKey(const uint8_t aKey[16]) { return aes_setkey_enc(&mContext, aKey, 128) == 0; }
    bool Encrypt(const uint8_t aInput[16], uint8_t aOutput[16])
    {
        if (key_is_set)
            if (aes_setkey_enc(&mContext, Key, 128) != 0)
                return false;
        return aes_crypt_ecb(&mContext, AES_ENCRYPT, aInput, aOutput) == 0;
    }

    ///////////////////////////////////////////////////////////////////////////////////////

    bool SetDecKey(const char aKey[16]) { return aes_setkey_dec(&mContext, (uint8_t *)aKey, 128) == 0; }
    bool SetDecKey(const uint8_t aKey[16]) { return aes_setkey_dec(&mContext, aKey, 128) == 0; }
    bool Decrypt(const uint8_t aInput[16], uint8_t aOutput[16])
    {
        if (key_is_set)
            if (aes_setkey_dec(&mContext, Key, 128) != 0)
                return false;
        return aes_crypt_ecb(&mContext, AES_DECRYPT, aInput, aOutput) == 0;
    }
};