/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bl_context.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Bootloader global context data.
//!
//! @ingroup context
bootloader_context_t g_bootloaderContext = {.memoryInterface = &g_memoryInterface,
                                            .memoryMap = g_memoryMap,
#if BL_FEATURE_EXPAND_MEMORY
                                            .externalMemoryMap = g_externalMemoryMap,
#endif // BL_FEATURE_EXPAND_MEMORY
                                            .propertyInterface = &g_propertyInterface,
};
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
