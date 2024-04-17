/*
 * Copyright (c) 2014-2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "bootloader_common.h"
#include "bootloader.h"
#include "memory.h"
#include "property.h"
#include "fsl_assert.h"
#include <string.h>
#include <stdint.h>
#include "fsl_device_registers.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Local function prototypes
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////



bool is_in_execute_only_region(uint32_t start, uint32_t lengthInBytes)
{
#if FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL
    flash_xacc_state_t state = kFLASH_AccessStateUnLimited;
    g_bootloaderContext.flashDriverInterface->flash_is_execute_only(&g_bootloaderContext.allFlashState[kFlashIndex_Main], start,
                                                                    lengthInBytes, &state);
    if (state == kFLASH_AccessStateUnLimited)
    {
#if BL_HAS_SECONDARY_INTERNAL_FLASH
        g_bootloaderContext.flashDriverInterface->flash_is_execute_only(&g_bootloaderContext.allFlashState[kFlashIndex_Secondary], start,
                                                                        lengthInBytes, &state);
        if (state != kFLASH_AccessStateUnLimited)
        {
            return true;
        }
        else
#endif // BL_HAS_SECONDARY_INTERNAL_FLASH
        {
            return false;
        }
    }
    else
    {
        return true;
    }
#else
    return false;
#endif // FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL
}

//To solve the compilation problem of MCUX newlib.nano
#if defined(__GNUC__)
void _close(void)
{
}
void _lseek(void)
{
}
void _read(void)
{
}
void _write(void)
{
}
void _fstat(void)
{
}
void _getpid(void)
{
}
void _isatty(void)
{
}
void _kill(void)
{
}
#endif
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
