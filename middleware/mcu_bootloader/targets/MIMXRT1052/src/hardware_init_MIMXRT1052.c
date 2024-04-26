/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bl_context.h"
#include "bootloader_common.h"
#include "fsl_assert.h"
#include "fsl_device_registers.h"
#include "fsl_lpuart.h"
#include "fusemap.h"
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define FREQ_396MHz (396000000U)
#define FREQ_480MHz (480000000U)
#define FREQ_528MHz (528000000U)
#define FREQ_24MHz (24000000U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Codes
 ******************************************************************************/

void dummy_byte_callback(uint8_t byte)
{
    (void)byte;
}

void debug_init(void) {}

#if __ICCARM__

size_t __write(int handle, const unsigned char *buf, size_t size)
{
    return size;
}

#endif // __ICCARM__

void update_available_peripherals() {}

void init_hardware(void)
{

}

void deinit_hardware(void)
{

}

//!@brief Get the hab status.
habstatus_option_t get_hab_status()
{
    if (ROM_OCOTP_SEC_CONFIG_VALUE() & 0x2)
    {
        return kHabStatus_Close;
    }
    else
    {
        return kHabStatus_Open;
    }
}



////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
