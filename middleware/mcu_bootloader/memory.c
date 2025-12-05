/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bootloader_common.h"
#include "memory.h"

//! @addtogroup memif
//! @{

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief This variable is used to do flush operation, it is bind to write operation.


////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

// See memory.h for documentation on this function.
#if BL_FEATURE_EXPAND_MEMORY
status_t find_external_map_entry(uint32_t address,
                                 uint32_t length,
                                 uint32_t memory_id,
                                 const external_memory_map_entry_t **map)
{
    status_t status = kStatusMemoryRangeInvalid;

    // Set starting entry.
    assert(map);
    if (map)
    {
        *map = &g_externalMemoryMap[0];
    }

    // Scan memory map array looking for a match.
    while ((length > 0) && map && *map)
    {
        if (((*map)->memoryId == 0) && ((*map)->status == 0) && ((*map)->basicUnitCount == 0) &&
            ((*map)->basicUnitSize == 0) && ((*map)->memoryInterface == NULL))
        {
            break;
        }

        // Check if the memory id is matched.
        if (memory_id == (*map)->memoryId)
        {
            // Check that the length fits in this entry's address range.
            if (((uint64_t)address + length) <= ((uint64_t)(*map)->basicUnitCount * (*map)->basicUnitSize))
            {
                status = kStatus_Success;
            }
            break;
        }
        ++(*map);
    }

    return status;
}

status_t find_external_map_index(uint32_t memoryId, uint32_t *index)
{
    status_t status = kStatus_InvalidArgument;

    const external_memory_map_entry_t *map;
    uint32_t searchingIndex = 0;

    if (index == NULL)
    {
        return status;
    }

    map = &g_externalMemoryMap[0];
    // Scan memory map array looking for a match.
    while(map && (map->memoryId != 0) && (map->memoryInterface != NULL))
    {
        if (memoryId == map->memoryId)
        {
            *index = searchingIndex;
            // Find the correct index.
            status = kStatus_Success;
            break;
        }
        searchingIndex++;
        map++;
    };

    return status;
}
#endif // BL_FEATURE_EXPAND_MEMORY


//! @}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
