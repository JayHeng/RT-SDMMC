/*
* Copyright 2014-2016 Freescale Semiconductor, Inc.
* Copyright 2016-2019 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*
*/

#ifndef __BOOTLOADER_CONFIG_H__
#define __BOOTLOADER_CONFIG_H__

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//
// Bootloader configuration options
//

//==============================================================================
//! @name Device type configuration macros
//@{
#if !defined(BL_DEVICE_IS_LPC_SERIES)
#define BL_DEVICE_IS_LPC_SERIES (1)
#endif
//@}

//==============================================================================
//! @name Target-resident configuration macros
//@{
#if !defined(BL_TARGET_FLASH)
#define BL_TARGET_FLASH (0)
#endif
//@}

//==============================================================================
//! @name Commmand configuration macros
//@{
// Determines the supported command set (normal/minimal)
#if !defined(BL_FEATURE_MIN_PROFILE)
#define BL_FEATURE_MIN_PROFILE (1)
#endif

//@}
// Memory expansion features
#define BL_FEATURE_EXPAND_MEMORY (1)

// Determine whether to support MMC/eMMC
#define BL_FEATURE_MMC_MODULE (1)
#if BL_FEATURE_ENABLE_MKBOOT_DEVICE_MMC && !BL_FEATURE_MMC_MODULE
#error "'BL_FEATURE_ENABLE_MKBOOT_DEVICE_MMC' requires 'BL_FEATURE_MMC_MODULE'"
#endif
#if BL_FEATURE_MMC_MODULE
#define BL_FEATURE_MMC_MODULE_ERASE_VERIFY (1)
#define BL_FEATURE_MMC_MODULE_ENABLE_PERMANENT_CONFIG (0)
#endif // BL_FEATURE_MMC_MODULE

// Determine whether to support eSD/SD/SDHC/SDXC
#define BL_FEATURE_SD_MODULE (1)
#if BL_FEATURE_ENABLE_MKBOOT_DEVICE_SD && !BL_FEATURE_SD_MODULE
#error "'BL_FEATURE_ENABLE_MKBOOT_DEVICE_SD' requires 'BL_FEATURE_SD_MODULE'"
#endif
#if BL_FEATURE_SD_MODULE
#define BL_FEATURE_SD_MODULE_ERASE_VERIFY (1)
#endif // BL_FEATURE_SD_MODULE

// Determines whether to store external memory info in property
#define BL_FEATURE_EXTERNAL_MEMORY_PROPERTY (1)

// Determines whether to use OTFAD module for image decryption on qspi flash
#define BL_HAS_OTFAD_MODULE (1)
//@}

//==============================================================================
//! @name Misc configuration macros
//@{

#define BL_FEATURE_PROPERTY_RAM_REGION_COUNT (4)
#define BL_FEATURE_PROPERTY_RESERVED_REGION_COUNT (4)


//@}

#endif // __BOOTLOADER_CONFIG_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
