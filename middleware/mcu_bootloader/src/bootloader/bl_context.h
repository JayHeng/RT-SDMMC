/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if !defined(__CONTEXT_H__)
#define __CONTEXT_H__

#include "bootloader_common.h"
#include "memory.h"
#include "property.h"

//! @addtogroup context
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Structure of bootloader global context.
typedef struct _bootloaderContext
{
    //! @name API tree
    //@{
    const memory_interface_t *memoryInterface; //!< Abstract interface to memory operations.
    const memory_map_entry_t *memoryMap;       //!< Memory map used by abstract memory interface.
    const external_memory_map_entry_t *externalMemoryMap; //!< Memory map used by external memory devices.
    const property_interface_t *propertyInterface;        //!< Interface to property store.
} bootloader_context_t;

////////////////////////////////////////////////////////////////////////////////
// Externs
////////////////////////////////////////////////////////////////////////////////

extern bootloader_context_t g_bootloaderContext;

//! @}

#endif // __CONTEXT_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
