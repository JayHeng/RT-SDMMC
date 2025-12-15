/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdbool.h>
#include "bootloader_common.h"
#include "property.h"
#include "sd_memory.h"

//! @addtogroup bl_core
//! @{

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#define SDCARD_RW_SELFTEST (1)

#define BOARD_RT600_EVK_USDHC_CARD    (1)

#if BOARD_RT600_EVK_USDHC_CARD
#define SD_CFG_OPTION0   (0xD0080100)
#define APP_EXEC_START   (0x80000)
#define APP_LENGTH       (0x6000)
#endif

#define APP_SDCARD_START  (0x80000)

static void bootloader_init(void);
static void bootloader_run(void);

int main(void);

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

static void bootloader_var_init(void)
{
    g_externalMemoryMap[0].memoryId = kMemorySDCard;
    g_externalMemoryMap[0].status = kStatus_Success;
    g_externalMemoryMap[0].basicUnitCount = 0;
    g_externalMemoryMap[0].basicUnitSize = 512;
    g_externalMemoryMap[0].memoryInterface = &g_sdMemoryInterface;
}


//! @brief Initialize the bootloader and peripherals.
//!
//! This function initializes hardware and clocks, loads user configuration data, and initialzes
//! a number of drivers. It then enters the active peripheral detection phase by calling
//! get_active_peripheral(). Once the peripheral is detected, the packet and comand interfaces
//! are initialized.
//!
//! Note that this routine may not return if peripheral detection times out and the bootloader
//! jumps directly to the user application in flash.
static void bootloader_init(void)
{
    bootloader_var_init();

    // Init pinmux and other hardware setup.
    init_hardware();

    // Configure clocks.
    configure_clocks(kClockOption_EnterBootloader);
    
    g_sdMemoryInterface.init();
}

#if SDCARD_RW_SELFTEST
uint8_t s_sdTestBuffer[512];
#endif

static void bootloader_run(void)
{
    status_t status = kStatus_InvalidArgument;
    
    sd_config_t sdConfig = 
    {
       .word0.U = SD_CFG_OPTION0,
    };

    status = g_sdMemoryInterface.config((uint32_t *)&sdConfig);
    if (status == kStatus_Success)
    {
#if SDCARD_RW_SELFTEST
        for (uint32_t i = 0; i < sizeof(s_sdTestBuffer); i++)
        {
            s_sdTestBuffer[i] = i & 0xFF;
        }
        status = g_sdMemoryInterface.write(APP_SDCARD_START, sizeof(s_sdTestBuffer), s_sdTestBuffer);
#endif
        status = g_sdMemoryInterface.read(APP_SDCARD_START, APP_LENGTH, (uint8_t *)APP_EXEC_START);
        if (status == kStatus_Success)
        {
            __NOP();
        }
    }

    while (1)
    {

    }
}

//! @brief Entry point for the bootloader.
int main(void)
{
    bootloader_init();
    bootloader_run();

    return 0;
}

//! @}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
