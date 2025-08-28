/*
 * Copyright 2017-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#if !defined(__TARGET_CONFIG_H__)
#define __TARGET_CONFIG_H__

#include "fusemap.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
// Workaround to make the __USED work fine with IAR toolchain
#if defined(__ICCARM__)
#undef __USED
#define __USED __root
#endif

//!@brief Reserved RAM size during Bootloader execution
enum
{
    kBootloader_ReservedRAM_Size = 0x1c000
};

//!@brief Unique ID constants
enum _uid_constrants
{
    kUniqueId_SizeInBytes = 16,
};

//!@brief uSDHC boot device type definitions
enum
{
    kBootFuseDeviceType_MMC = 0,
    kBootFuseDeviceType_SD = 1,
};

//! @brief Version constants for the target.
enum _target_version_constants
{
    kTarget_Version_Name = 'T',
    kTarget_Version_Major = 2,
    kTarget_Version_Minor = 0,
    kTarget_Version_Bugfix = 0
};

enum _sdmmc_constants
{
    kSdmmcMem_ImageStartOffset = 0x1000, // Must be aligned to FSL_SDMMC_DEFAULT_BLOCK_SIZE(512);
    kSdmmcMem_InitialImageSize = 0x200,  // Must be aligned to FSL_SDMMC_DEFAULT_BLOCK_SIZE(512);
};

//! @brief Memory Map index constants
enum _special_memorymap_constants
{
    // kIndexFlashArray = 0,
    // kIndexSRAM = 1,
    kIndexSRAMX = 2,
    kIndexSRAM1 = 3,
    kIndexSRAM2 = 4,
    kIndexSRAM3 = 5,

    kRAMSections = 5,

    // kSRAMSeparatrix = (uint32_t)0x20000000 //!< This value is the start address of SRAM_U
};

#endif // __TARGET_CONFIG_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
