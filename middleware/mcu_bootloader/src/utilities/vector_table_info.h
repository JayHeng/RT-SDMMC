/*
 * Copyright (c) 2013 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#if !defined(__VECTOR_TABLE_INFO_H__)
#define __VECTOR_TABLE_INFO_H__

#include "bootloader_config.h"

//! @addtogroup vector_table_info
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Defines a constant for the default vector table.
enum _vector_table_address
{
    //! @brief Address of the default vector table, which is always 0.
    kDefaultVectorTableAddress = 0
};

//! @brief Constants for the entries of the vector table.
enum _vector_table_entries
{
    kInitialSP = 0, //!< Initial stack pointer.
    kInitialPC = 1, //!< Reset vector.
};

//! @}

#endif // __VECTOR_TABLE_INFO_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
