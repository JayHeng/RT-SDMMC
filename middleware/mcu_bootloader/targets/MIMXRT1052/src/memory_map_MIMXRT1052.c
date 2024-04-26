/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bl_context.h"
#include "memory.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Memory map for RT105x.
//!
//! This map is not const because it is updated at runtime with the actual sizes of
//! flash and RAM for the chip we're running on.
//! @note Do not change the index of Flash, SRAM, or QSPI (see memory.h).
memory_map_entry_t g_memoryMap[] = {
    // ITCM SRAM(128KB)
    { 0x00000000, 0x0001ffff, kMemoryIsExecutable | kMemoryType_RAM, kMemoryInternal, &g_normalMemoryInterface },
    // DTCM SRAM(128KB)
    { 0x20000000, 0x2001ffff, kMemoryIsExecutable | kMemoryType_RAM, kMemoryInternal, &g_normalMemoryInterface },
    // OCRAM (256KB)
    { 0x20200000, 0x2023ffff, kMemoryIsExecutable | kMemoryType_RAM, kMemoryInternal, &g_normalMemoryInterface },
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
