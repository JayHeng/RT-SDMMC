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

#endif // __BOOTLOADER_CONFIG_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
