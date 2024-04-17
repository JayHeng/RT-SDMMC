/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if !defined(__BOOTLOADER_H__)
#define __BOOTLOADER_H__

#include "bootloader_common.h"
#include "bl_context.h"
#include "bl_version.h"
#include "bl_shutdown_cleanup.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Verify that a given address is ok to jump to.
 *
 * @param applicationAddress The entry point address to validate.
 * @return Boolean indicating whether the address is valid.
 *
 * @ingroup bl_core
 */
bool is_valid_application_location(uint32_t applicationAddress);

/*!
 * @brief Verify that a given address is ok to set as stack pointer base address.
 *
 * @param stackpointerAddress The stack pointer address to validate.
 * @return Boolean indicating whether the address is valid.
 *
 * @ingroup bl_core
 */
bool is_valid_stackpointer_location(uint32_t stackpointerAddress);

#if defined(__cplusplus)
}
#endif

#endif // __BOOTLOADER_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
