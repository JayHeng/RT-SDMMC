/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bl_context.h"
#include "memory.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Memory map for LPC6824.
//!
//! This map is not const because it is updated at runtime with the actual sizes of
//! flash and RAM for the chip we're running on.
//! @note See memory.h for index requirements.
memory_map_entry_t g_memoryMap[] = {
    // SRAM0 Secure Alias address (size: 4.5MB)
    { 0x10000000u, 0x10477fffu, kMemoryIsExecutable | kMemoryType_RAM | kMemoryAliasAddr, kMemoryInternal,
      &g_normalMemoryInterface },

    // SRAM0 (size: 4.5MB)
    { 0x00000000u, 0x00477fffu, kMemoryIsExecutable | kMemoryType_RAM, kMemoryInternal, &g_normalMemoryInterface },

    // System RAM (size: 4.5MB)
    { 0x20000000u, 0x20477fffu, kMemoryIsExecutable | kMemoryType_RAM, kMemoryInternal, &g_normalMemoryInterface },

    // System RAM Secure Alias address (size: 4.5MB)
    { 0x30000000u, 0x30477fffu, kMemoryIsExecutable | kMemoryType_RAM | kMemoryAliasAddr, kMemoryInternal,
      &g_normalMemoryInterface },

    // Terminator
    { 0 }
};


external_memory_map_entry_t g_externalMemoryMap[] = {
#if BL_FEATURE_SD_MODULE
    { kMemorySDCard, 0, 0, 512, &g_sdMemoryInterface }, // SD card memory
#endif
#if BL_FEATURE_MMC_MODULE
    { kMemoryMMCCard, 0, 0, 512, &g_mmcMemoryInterface }, // MMC card memory
#endif
    { 0 } // Terminator
};

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
