/*
 * Copyright 2017 NXP
 *
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bootloader_common.h"
#include "memory.h"
#include "property.h"

const external_memory_property_interface_t g_externalMemPropertyInterfaceMap[] = {
#if BL_FEATURE_SD_MODULE
    { kMemorySDCard, sd_get_property }, // SD card memory
#endif
#if BL_FEATURE_MMC_MODULE
    { kMemoryMMCCard, mmc_get_property }, // MMC/eMMC card memory
#endif
    { 0 } // Terminator
};

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
