/*
 * Copyright 2018 - 2019 NXP
 *
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_clock.h"
#include "microseconds.h"
#include "property.h"
#include "bl_semc.h"
#include "fusemap.h"
////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
#define FREQ_1MHz (1000000UL)
#define FREQ_528MHz (528UL * FREQ_1MHz)
#define FREQ_24MHz (24UL * FREQ_1MHz)
#define FREQ_480MHz (480UL * FREQ_1MHz)
#define FREQ_400MHz (400UL * FREQ_1MHz)
#define FREQ_500MHz (500UL * FREQ_1MHz)
#define FREQ_696MHz (696UL * FREQ_1MHz)
#define FREQ_19P2MHz (19200000u) // 19.2MHz
#define FREQ_594MHz (594UL * FREQ_1MHz)
#define FREQ_664MHz (664UL * FREQ_1MHz)

enum
{
    kCm7ClockSrc_RC400M = 0xaa,
    kCm7ClockSrc_PLL_ARM = 0x3c,
};

enum
{
    kCm4ClockSrc_RC400M = 0xaa,
    kCm4ClockSrc_PLL_480 = 0x3c,
};

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////
uint32_t get_cm7_core_src(void);

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
static inline uint32_t get_clock_div(uint32_t root, uint32_t maxFreq)
{
    return ((root + maxFreq - 1) / maxFreq);
}


uint32_t get_cm7_core_src(void)
{
    if (FUSE_BOOT_FREQ_VALUE)
    {
        return kCm7ClockSrc_PLL_ARM;
    }
    else
    {
        return kCm7ClockSrc_RC400M;
    }
}

// See bootloader_common for documentation on this function.
void configure_clocks(bootloader_clock_option_t option)
{
    enum
    {
        kMaxFreq_M7 = 700 * FREQ_1MHz,
        kMaxFreq_M4 = 240 * FREQ_1MHz,
    };

    if (option == kClockOption_EnterBootloader)
    {
        SystemCoreClock = FREQ_24MHz; // Default core clock before initializing the boot clock
        // assert(CCM->CLOCK_ROOT[kCLOCK_Root_M7].CONTROL && CCM->CLOCK_ROOT[kCLOCK_Root_M7].CONTROL);

        uint32_t postDivider = 1 << (FUSE_LPB_BOOT_VALUE);
        if (postDivider > 8)
        {
            postDivider = 1;
        }

        {
            if (get_cm7_core_src() == kCm7ClockSrc_RC400M)
            {
                uint32_t clockToSwitch = FREQ_400MHz;
                uint32_t cm7ClockDiv = get_clock_div(clockToSwitch, kMaxFreq_M7) * postDivider;
                CCM->CLOCK_ROOT[kCLOCK_Root_Lpuart1].CONTROL = CCM_CLOCK_ROOT_CONTROL_DIV(4) | CCM_CLOCK_ROOT_CONTROL_MUX(2);
                SystemCoreClock = clockToSwitch / cm7ClockDiv;
            }
            else /* get_cm7_core_src() == kCm7ClockSrc_PLL_ARM */
            {
                CCM->CLOCK_ROOT[kCLOCK_Root_Lpuart1].CONTROL = CCM_CLOCK_ROOT_CONTROL_DIV(2) | CCM_CLOCK_ROOT_CONTROL_MUX(4);
                if (FUSE_SPEED_LIMIT_VALUE == 1)
                {
                    SystemCoreClock = FREQ_500MHz / postDivider;
                }
                else
                {
                    SystemCoreClock = FREQ_696MHz / postDivider;
                }
            }
        }
    }
}

// Get OCOTP clock
uint32_t get_ocotp_clock(void)
{
    return get_bus_clock();
}

uint32_t get_bus_clock(void)
{
    // PIT is from BUS clock, the maximum bus clock is 200MHz
    uint32_t clkRoot = CCM->CLOCK_ROOT[kCLOCK_Root_Bus].CONTROL;
    uint32_t div = (clkRoot & CCM_CLOCK_ROOT_CONTROL_DIV_MASK) >> CCM_CLOCK_ROOT_CONTROL_DIV_SHIFT;
    uint32_t mux = (clkRoot & CCM_CLOCK_ROOT_CONTROL_MUX_MASK) >> CCM_CLOCK_ROOT_CONTROL_MUX_SHIFT;
    uint32_t busFreq = 0;

    switch (mux)
    {
        default:
        case 0:
            busFreq = FREQ_1MHz * 24u;
            break;
        case 1:
            busFreq = FREQ_1MHz * 24u;
            break;
        case 2:
            busFreq = FREQ_1MHz * 400u;
            break;
        case 3:
            busFreq = FREQ_1MHz * 16u;
            break;
        case 4:
            busFreq = FREQ_1MHz * 480u;
            break;
        case 5:
            busFreq = FREQ_1MHz * 200u;
            break;
        case 6:
            busFreq = FREQ_1MHz * 528u;
            break;
        case 7:
            busFreq = FREQ_1MHz * 297u;
            break;
    }
    return busFreq / (div + 1);
}

//! @brief Gets the clock value used for microseconds driver
uint32_t microseconds_get_clock(void)
{
    return get_bus_clock();
}

//! @brief Return uart clock frequency according to instance
uint32_t get_uart_clock(uint32_t instance)
{
    // LPUART1 clock has been configured to 80MHz in clock_configure
    uint32_t lpuart_clock = 0;
    lpuart_clock = 80 * FREQ_1MHz; // 80MHz;
    return lpuart_clock;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
