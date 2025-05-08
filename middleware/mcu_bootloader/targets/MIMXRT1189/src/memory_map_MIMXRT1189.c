/*
 * Copyright 2018 NXP
 *
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bootloader.h"
#include "memory.h"
#include "memory_config.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////
//! @brief Memory map
//!
//! This map is not const because it is updated at runtime with the actual sizes of
//! flash and RAM for the chip we're running on.
//! @note Do not change the index of Flash, SRAM, or QSPI (see memory.h).
memory_map_entry_t g_memoryMap[] = {
    // M33 CODE TCM SRAM(256KB)
    { .startAddress = M33_CODE_TCM_START_ADDRESS_IN_M33,
      .endAddress = M33_CODE_TCM_END_ADDRESS_IN_M33,
      .memoryProperty = kMemoryIsExecutable | kMemoryType_RAM,
      .memoryId = kMemoryInternal,
      .memoryInterface = &g_normalMemoryInterface },

    // M33 CODE TCM NS SRAM(256KB)
    { .startAddress = M33_CODE_TCM_NS_START_ADDRESS_IN_M33,
      .endAddress = M33_CODE_TCM_NS_END_ADDRESS_IN_M33,
      .memoryProperty = kMemoryIsExecutable | kMemoryType_RAM,
      .memoryId = kMemoryInternal,
      .memoryInterface = &g_normalMemoryInterface },

    // M33 SYS TCM SRAM(256KB)
    { .startAddress = M33_SYS_TCM_START_ADDRESS_IN_M33,
      .endAddress = M33_SYS_TCM_END_ADDRESS_IN_M33,
      .memoryProperty = kMemoryIsExecutable | kMemoryType_RAM,
      .memoryId = kMemoryInternal,
      .memoryInterface = &g_normalMemoryInterface },

    // M33 SYS TCM NS SRAM(256KB)
    { .startAddress = M33_SYS_TCM_NS_START_ADDRESS_IN_M33,
      .endAddress = M33_SYS_TCM_NS_END_ADDRESS_IN_M33,
      .memoryProperty = kMemoryIsExecutable | kMemoryType_RAM,
      .memoryId = kMemoryInternal,
      .memoryInterface = &g_normalMemoryInterface },

    // M7 TCM SRAM
    { .startAddress = M7_TCM_START_ADDRESS_IN_M33,
      .endAddress = M7_TCM_END_ADDRESS_IN_M33, /* Flexible size which will be filled during ROM initialization. */
      .memoryProperty = kMemoryIsExecutable | kMemoryType_RAM,
      .memoryId = kMemoryInternal,
      .memoryInterface = &g_normalMemoryInterface },

    // M7 TCM NS SRAM
    { .startAddress = M7_TCM_NS_START_ADDRESS_IN_M33,
      .endAddress = M7_TCM_NS_END_ADDRESS_IN_M33, /* Flexible size which will be filled during ROM initialization. */
      .memoryProperty = kMemoryIsExecutable | kMemoryType_RAM,
      .memoryId = kMemoryInternal,
      .memoryInterface = &g_normalMemoryInterface },

    // OCRAM SRAM
    { .startAddress = OCRAM_START_ADDRESS,
      .endAddress = OCRAM_END_ADDRESS, /* Flexible size which will be filled during ROM initialization. */
      .memoryProperty = kMemoryIsExecutable | kMemoryType_RAM,
      .memoryId = kMemoryInternal,
      .memoryInterface = &g_normalMemoryInterface },

    // OCRAM NS SRAM
    { .startAddress = OCRAM_NS_START_ADDRESS,
      .endAddress = OCRAM_NS_END_ADDRESS, /* Flexible size which will be filled during ROM initialization. */
      .memoryProperty = kMemoryIsExecutable | kMemoryType_RAM,
      .memoryId = kMemoryInternal,
      .memoryInterface = &g_normalMemoryInterface },

    // Terminator
    { 0 }
};

#if BL_FEATURE_EXPAND_MEMORY
external_memory_map_entry_t g_externalMemoryMap[] = {
#if BL_FEATURE_SD_MODULE
    // SD card memory
    { .memoryId = kMemorySDCard,
      .status = kStatus_Success,
      .basicUnitCount = 0,
      .basicUnitSize = 512,
      .memoryInterface = &g_sdMemoryInterface },
#endif // BL_FEATURE_SD_MODULE
#if BL_FEATURE_MMC_MODULE
    // MMC card memory
    { .memoryId = kMemoryMMCCard,
      .status = kStatus_Success,
      .basicUnitCount = 0,
      .basicUnitSize = 512,
      .memoryInterface = &g_mmcMemoryInterface },
#endif // BL_FEATURE_MMC_MODULE
    { 0 } // Terminator
};
#endif // #if BL_FEATURE_EXPAND_MEMORY

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
