/*
 * Copyright 2018 - 2019 NXP
 *
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_clock.h"
#include "fusemap.h"
#include "microseconds.h"
#include "property.h"
////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
#define FREQ_1MHz (1000000UL)
#define FREQ_24MHz (24UL * FREQ_1MHz)
#define FREQ_400MHz (400UL * FREQ_1MHz)
#define FREQ_480MHz (480UL * FREQ_1MHz)
#define FREQ_594MHz (594UL * FREQ_1MHz)
#define FREQ_696MHz (696UL * FREQ_1MHz)

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
// See bootloader_common for documentation on this function.
void configure_clocks(bootloader_clock_option_t option)
{
    if (option == kClockOption_EnterBootloader)
    {
        SystemCoreClock = CLOCK_GetRootClockFreq(kCLOCK_Root_M33);
    }
}

//! @brief Gets the clock value used for microseconds driver
uint32_t microseconds_get_clock(void)
{
#ifndef BL_TARGET_FPGA
    return CLOCK_GetRootClockFreq(kCLOCK_Root_Bus_Aon);
#else
    return FPGA_FREQ_BUS;
#endif
}

//! @brief Return uart clock frequency according to instance
uint32_t get_uart_clock(uint32_t instance)
{
#ifndef BL_TARGET_FPGA
    switch (instance)
    {
        case 1:
        case 2:
            return CLOCK_GetRootClockFreq(kCLOCK_Root_Lpuart0102);
        case 3:
        case 4:
            return CLOCK_GetRootClockFreq(kCLOCK_Root_Lpuart0304);
        case 5:
        case 6:
            return CLOCK_GetRootClockFreq(kCLOCK_Root_Lpuart0506);
        case 7:
        case 8:
            return CLOCK_GetRootClockFreq(kCLOCK_Root_Lpuart0708);
        case 9:
        case 10:
            return CLOCK_GetRootClockFreq(kCLOCK_Root_Lpuart0910);
        case 11:
        case 12:
            return CLOCK_GetRootClockFreq(kCLOCK_Root_Lpuart1112);
        default:
            return 0;
    }
#else
    return FPGA_FREQ_UART;
#endif
}

void spi_clock_gate_enable(uint32_t instance)
{
    // Note: This function is no longer needed, empty function is created to satisfy the memory interface
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
