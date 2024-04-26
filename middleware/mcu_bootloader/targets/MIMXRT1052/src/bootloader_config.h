/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __BOOTLOADER_CONFIG_H__
#define __BOOTLOADER_CONFIG_H__

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//
// Bootloader configuration options
//

//! @name Peripheral configuration macros
//@{

#if !defined(BL_TARGET_FLASH) && !defined(BL_TARGET_RAM)
#define BL_TARGET_FLASH (0)
#endif

#define BL_FEATURE_MIN_PROFILE (0)

////////////////////////////////////////////////////////////////////////////////
// Non-XIP External Memory Module Configurations
////////////////////////////////////////////////////////////////////////////////
#define BL_FEATURE_EXPAND_MEMORY (1)

#define BL_FEATURE_MMC_MODULE (1)
#if BL_FEATURE_MMC_MODULE
#define BL_FEATURE_MMC_MODULE_ERASE_VERIFY (1)
#define BL_FEATURE_MMC_MODULE_PERIPHERAL_INSTANCE (2)
#define BL_FEATURE_MMC_MODULE_ENABLE_PERMANENT_CONFIG (0)
#endif // BL_FEATURE_MMC_MODULE

#define BL_FEATURE_SD_MODULE (1)
#if BL_FEATURE_SD_MODULE
#define BL_FEATURE_SD_MODULE_ERASE_VERIFY (1)
#define BL_FEATURE_SD_MODULE_PERIPHERAL_INSTANCE (1)
#endif // BL_FEATURE_SD_MODULE

#if BL_FEATURE_EXPAND_MEMORY
#define BL_FEATURE_EXTERNAL_MEMORY_PROPERTY (1)
#endif

#define BL_FEATURE_OCOTP_MODULE (FSL_FEATURE_SOC_OCOTP_COUNT)


#endif // __BOOTLOADER_CONFIG_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
