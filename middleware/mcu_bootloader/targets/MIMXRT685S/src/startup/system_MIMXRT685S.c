/*
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*!
 * @file LPC6824
 * @version 1.0
 * @date 2017-07-14
 * @brief Device specific configuration file for LPC6824 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"
#include "otp/fsl_otp.h"
#include "fusemap.h"
#include "bootloader_config.h"
#include <stdbool.h>
#include "bootloader/bootloader.h"
#include "bootloader_common.h"
#include "utilities/debug_util.h"

/*******************************************************************************
* Definitions
*******************************************************************************/

enum
{
    kSram_EnableFirst32KB = 0x01u,
    kSram_EnableFirst64KB = 0x03u,
    kSram_EnableFirst96KB = 0x07u,
    kSram_EnableFirst128KB = 0x0fu,
};

#define DEFAULT_CLK (12000000u)

/*******************************************************************************
 * Extern Variables
 ******************************************************************************/

/*******************************************************************************
* Prototypes
*******************************************************************************/

/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */
uint32_t SystemCoreClock BL_SECTION(".noinit");
uint32_t __stack_chk_guard BL_SECTION(".noinit");

/*******************************************************************************
* Codes
*******************************************************************************/
void SystemInit(void)
{

    SystemCoreClock = DEFAULT_CLK;

    // Ensure first 128KB of RAM is enabled for ROM use.
    SYSCTL0->SRAMCFGENABLE0 |= kSram_EnableFirst128KB;

}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate(void)
{
    /* LPCnext0 systemCoreClockUpdate */
}
