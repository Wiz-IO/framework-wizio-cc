#include "interface.h"

#define PWR_PRINTF printf

typedef struct
{
    const uint32_t domain;
    uint8_t cnt;
} domain_t;
static domain_t ctx_domain[9] = {
    {PRCM_DOMAIN_RFCORE, 0},
    {PRCM_DOMAIN_SERIAL, 0},
    {PRCM_DOMAIN_PERIPH, 0},
    {PRCM_DOMAIN_SYSBUS, 0},
    {PRCM_DOMAIN_VIMS, 0},
    {PRCM_DOMAIN_CPU, 0},
    {PRCM_DOMAIN_TIMER, 0},
    {PRCM_DOMAIN_CLKCTRL, 0},
    {PRCM_DOMAIN_MCU, 0},
};

bool soc_power_on_domain(uint32_t domain)
{
    for (int i = 0; i < 9; i++)
    {
        if (domain == ctx_domain[i].domain)
        {
            if (0 == ctx_domain[i].cnt++)
            {
                PRCMPowerDomainOn(domain);
                while (PRCMPowerDomainsAllOn(domain) != PRCM_DOMAIN_POWER_ON)
                    ;
                PRCMDomainEnable(domain);
                PRCMLoadSet();
                while (!PRCMLoadGet())
                    ;
                //PWR_PRINTF("[PWR] %s( %04X ) ON\n", __func__, (int)domain);
            }
            //PWR_PRINTF("[PWR] %s( %04X ) ON ( %d )\n", __func__, (int)domain, (int)ctx_domain[i].cnt);
            return true;
        }
    }
    //PWR_PRINTF("[ERROR] %s( %04X )\n", __func__, (int)domain);
    return false;
}

bool soc_power_off_domain(uint32_t domain)
{
    for (int i = 0; i < 9; i++)
    {
        if (domain == ctx_domain[i].domain)
        {
            switch (ctx_domain[i].cnt)
            {
            case 0:
                //PWR_PRINTF("[PWR] %s( %X ) IS OFF\n", __func__, (int)domain);
                break;
            case 1:
                PRCMDomainDisable(domain);
                PRCMLoadSet();
                while (!PRCMLoadGet())
                    ;
                PRCMPowerDomainOff(domain);
                while (PRCMPowerDomainsAllOn(domain) != PRCM_DOMAIN_POWER_OFF)
                    ;
                //PWR_PRINTF("[PWR] %s( %04X ) OFF\n", __func__, (int)domain);
            default:
                ctx_domain[i].cnt -= 1;
                //PWR_PRINTF("[PWR] %s( %04X ) OFF ( %d )\n", __func__, (int)domain, (int)ctx_domain[i].cnt);
                break;
            }
            return true;
        }
    }
    //PWR_PRINTF("[ERROR] %s( %04X )\n", __func__, (int)domain);
    return false;
}

///////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    const uint32_t periphery;
    const uint32_t domain;
    uint8_t normal, sleep, deep;
} periphery_t;

static periphery_t ctx_periphery[15] = {
    {PRCM_PERIPH_TIMER0, -1, 0, 0, 0},                 // TODO
    {PRCM_PERIPH_TIMER1, -1, 0, 0, 0},                 // TODO
    {PRCM_PERIPH_TIMER2, -1, 0, 0, 0},                 // TODO
    {PRCM_PERIPH_TIMER3, -1, 0, 0, 0},                 // TODO
    {PRCM_PERIPH_SSI0, PRCM_DOMAIN_SERIAL, 0, 0, 0},   //
    {PRCM_PERIPH_SSI1, PRCM_DOMAIN_PERIPH, 0, 0, 0},   //
    {PRCM_PERIPH_UART0, PRCM_DOMAIN_SERIAL, 0, 0, 0},  //
    {PRCM_PERIPH_UART1, PRCM_DOMAIN_PERIPH, 0, 0, 0},  //
    {PRCM_PERIPH_I2C0, PRCM_DOMAIN_SERIAL, 0, 0, 0},   // TODO
    {PRCM_PERIPH_CRYPTO, PRCM_DOMAIN_PERIPH, 0, 0, 0}, //
    {PRCM_PERIPH_TRNG, PRCM_DOMAIN_PERIPH, 0, 0, 0},   //
    {PRCM_PERIPH_PKA, -1, 0, 0, 0},                    // TODO
    {PRCM_PERIPH_UDMA, -1, 0, 0, 0},                   // TODO
    {PRCM_PERIPH_GPIO, PRCM_DOMAIN_PERIPH, 0, 0, 0},   //
    {PRCM_PERIPH_I2S, -1, 0, 0, 0},                    // TODO
};

bool soc_power_on_periphery(uint32_t periphery, bool normal, bool sleep, bool deep)
{
    for (int i = 0; i < 15; i++)
    {
        bool load_set = false;
        if (periphery == ctx_periphery[i].periphery)
        {
            if (normal)
            {
                if (soc_power_on_domain(ctx_periphery[i].domain))
                {
                    if (0 == ctx_periphery[i].normal++)
                    {
                        PRCMPeripheralRunEnable(periphery);
                        load_set = true;
                        //PWR_PRINTF("[PWR] %s( %04X ) NORMAL ON\n", __func__, (int)periphery);
                    }
                    //PWR_PRINTF("[PWR] %s( %04X ) NORMAL ( %d )\n", __func__, (int)periphery, (int)ctx_periphery[i].normal);
                }
            }

            if (sleep)
            {
                if (soc_power_on_domain(ctx_periphery[i].domain))
                {
                    if (0 == ctx_periphery[i].sleep++)
                    {
                        PRCMPeripheralSleepEnable(periphery);
                        load_set = true;
                    }
                }
            }

            if (deep)
            {
                if (soc_power_on_domain(ctx_periphery[i].domain))
                {
                    if (0 == ctx_periphery[i].deep++)
                    {
                        PRCMPeripheralDeepSleepEnable(periphery);
                        load_set = true;
                    }
                }
            }

            if (load_set)
            {
                PRCMLoadSet();
                while (!PRCMLoadGet())
                    ;
            }
            return true;
        }
    }
    //PWR_PRINTF("[ERROR] %s( %04X )\n", __func__, (int)periphery);
    return false;
}

bool soc_power_off_periphery(uint32_t periphery, bool normal, bool sleep, bool deep)
{
    for (int i = 0; i < 15; i++)
    {
        int load_set = 0;
        if (normal)
        {
            switch (ctx_periphery[i].normal)
            {
            case 0:
                //PWR_PRINTF("[PWR] %s( %X ) IS OFF\n", __func__, (int)periphery);
                break;
            case 1:
                PRCMPeripheralRunDisable(periphery);
                load_set++;
            default:
                ctx_periphery[i].normal -= 1;
                //PWR_PRINTF("[PWR] %s( %04X ) NORMAL ( %d )\n", __func__, (int)periphery, (int)ctx_periphery[i].normal);
                break;
            }
        }

        if (sleep)
        {
            switch (ctx_periphery[i].sleep)
            {
            case 0:
                //PWR_PRINTF("[PWR] %s( %X ) IS OFF\n", __func__, (int)periphery);
                break;
            case 1:
                PRCMPeripheralSleepDisable(periphery);
                load_set++;
            default:
                ctx_periphery[i].sleep -= 1;
                //PWR_PRINTF("[PWR] %s( %04X ) SLEEP ( %d )\n", __func__, (int)periphery, (int)ctx_periphery[i].sleep);
                break;
            }
        }

        if (deep)
        {
            switch (ctx_periphery[i].deep)
            {
            case 0:
                //PWR_PRINTF("[PWR] %s( %X ) IS OFF\n", __func__, (int)periphery);
                break;
            case 1:
                PRCMPeripheralDeepSleepDisable(periphery);
                load_set++;
            default:
                ctx_periphery[i].deep -= 1;
                //PWR_PRINTF("[PWR] %s( %04X ) SLEEP ( %d )\n", __func__, (int)periphery, (int)ctx_periphery[i].deep);
                break;
            }
        }

        if (load_set)
        {
            PRCMLoadSet();
            while (!PRCMLoadGet())
                ;
            while (load_set--)
                soc_power_off_domain(ctx_periphery[i].domain);
        }
        return true;
    }
    //PWR_PRINTF("[ERROR] %s( %04X )\n", __func__, (int)periphery);
    return false;
}

#if 0
void powerOn(uint32_t domain, uint32_t periph, bool sleep, bool deep_sleep)
{
    if (domain)
    {
        PRCMPowerDomainOn(domain);
        while (PRCMPowerDomainsAllOn(domain) != PRCM_DOMAIN_POWER_ON)
            ;
    }
    if (periph)
    {
        PRCMPeripheralRunEnable(periph);
        if (sleep)
            PRCMPeripheralSleepEnable(periph);
        if (deep_sleep)
            PRCMPeripheralDeepSleepEnable(periph);
        PRCMLoadSet();
        while (!PRCMLoadGet())
            ;
    }
}

void powerOff(uint32_t domain, uint32_t periph)
{
    if (periph)
    {
        PRCMPeripheralRunDisable(periph);
        PRCMPeripheralSleepDisable(periph);
        PRCMPeripheralDeepSleepDisable(periph);
        PRCMLoadSet();
        while (!PRCMLoadGet())
            ;
    }

    if (domain)
    {
        PRCMPowerDomainOff(domain);
        while (PRCMPowerDomainsAllOff(domain) != PRCM_DOMAIN_POWER_ON)
            ;
    }
}

#endif