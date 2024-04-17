/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_rtos_abstraction.h"
#include "vector_table_info.h"
#include "microseconds.h"
#include "bootloader_common.h"
#include "bl_shutdown_cleanup.h"
#include "bl_context.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
extern void init_interrupts(void);

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

// See bl_shutdown_cleanup.h for documentation of this function.
void shutdown_cleanup(shutdown_type_t shutdown)
{
    if (shutdown != kShutdownType_Reset)
    {
    }

    if (shutdown != kShutdownType_Cleanup)
    {
    }

    // If we are permanently exiting the bootloader, there are a few extra things to do.
    if (shutdown == kShutdownType_Shutdown)
    {
        // Turn off global interrupt
        lock_acquire();

        // Shutdown microseconds driver.
        microseconds_shutdown();

        init_interrupts();

        // Set the VTOR to default.
        SCB->VTOR = kDefaultVectorTableAddress;

        // Restore clock to default before leaving bootloader.
        configure_clocks(kClockOption_ExitBootloader);

        // De-initialize hardware such as disabling port clock gate
        deinit_hardware();

        // Restore global interrupt.
        __enable_irq();

#if BL_FEATURE_BYPASS_WATCHDOG
        // De-initialize watchdog
        bootloader_watchdog_deinit();
#endif // BL_FEATURE_BYPASS_WATCHDOG
    }

    // Memory barriers for good measure.
    __ISB();
    __DSB();
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
