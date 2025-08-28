/*
* Copyright 2014-2016 Freescale Semiconductor, Inc.
* Copyright 2016-2019 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*
*/

#include "bl_context.h"
#include "bootloader_common.h"
#include "fsl_assert.h"
#include "fsl_device_registers.h"
#include "memory.h"
#include "property.h"
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
// Declarations
////////////////////////////////////////////////////////////////////////////////

#ifndef BL_FEATURE_RESERVED_REGION_AUTO_PROBE
#define BL_FEATURE_RESERVED_REGION_AUTO_PROBE 1
#endif

#if BL_FEATURE_RESERVED_REGION_AUTO_PROBE
#if (defined(__ICCARM__)) // IAR
#pragma section = ".intvec"
#pragma section = "ApplicationFlash"
#pragma section = "ApplicationRam"
#if defined(BL_TARGET_RAM) && (BL_TARGET_RAM == 1)
#define __RAM_START ((uint32_t)__section_begin(".intvec"))
#else
#define __RAM_START ((uint32_t)__section_begin("ApplicationRam"))
#endif // #if defined(BL_TARGET_RAM)
#if BL_FEATURE_ARENA
extern uint8_t __ARENA_MEM_END[];
#define __RAM_END ((uint32_t)__ARENA_MEM_END - 1)
#else
#define __RAM_END ((uint32_t)__section_end("ApplicationRam") - 1)
#endif // #if BL_FEATURE_ARENA
#define __ROM_START ((uint32_t)__section_begin(".intvec"))
#define __ROM_END ((uint32_t)__section_end("ApplicationFlash"))
#elif(defined(__CC_ARM)) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) // MDK
extern uint32_t Image$$VECTOR_ROM$$Base[];
extern uint32_t Image$$ER_m_text$$Limit[];
extern char Image$$VECTOR_RAM$$Base[];
#define __RAM_START ((uint32_t)Image$$VECTOR_RAM$$Base)
#if BL_FEATURE_ARENA
extern uint32_t Image$$__ARENA_MEM$$Limit[];
#define __RAM_END ((uint32_t)Image$$__ARENA_MEM$$Limit - 1)
#else
extern uint32_t Image$$ARM_LIB_STACK$$ZI$$Limit[];
#define __RAM_END ((uint32_t)Image$$ARM_LIB_STACK$$ZI$$Limit - 1)
#endif // #if BL_FEATURE_ARENA
#define __ROM_START ((uint32_t)Image$$VECTOR_ROM$$Base)
#define __ROM_END ((uint32_t)Image$$ER_m_text$$Limit)
#elif(defined(__GNUC__)) // GCC
extern uint32_t __VECTOR_RAM[];
extern uint32_t __VECTOR_TABLE[];
extern char __DATA_END[];
#define __RAM_START ((uint32_t)__VECTOR_RAM)
#if BL_FEATURE_ARENA
extern uint32_t __ARENA_MEM_END[];
#define __RAM_END ((uint32_t)__ARENA_MEM_END - 1)
#else
extern uint32_t __STACK_TOP[];
#define __RAM_END ((uint32_t)__STACK_TOP - 1)
#endif // #if BL_FEATURE_ARENA
#define __ROM_START ((uint32_t)__VECTOR_TABLE)
#define __ROM_END ((uint32_t)__DATA_END)
#else
#error Unknown toolchain!
#endif // __ICCARM__
#endif // BL_FEATURE_RESERVED_REGION_AUTO_PROBE

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
enum
{
    kUid_SizeInBytes = 16,
};

enum
{
    kSysDeviceID_SizeInBytes = 4,
};

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Storage for property values.
property_store_t g_propertyStore;
//! @brief Map for external memory property interface.
extern const external_memory_property_interface_t g_externalMemPropertyInterfaceMap[];

// See property.h for documentation on this data structure.
const property_interface_t g_propertyInterface = { bootloader_property_init,
                                                   bootloader_property_get, bootloader_property_set_uint32,
                                                   &g_propertyStore };

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////
// !@brief Get external memory properties
status_t bootloader_get_external_memory_properties(uint32_t memoryId, external_memory_property_store_t *store);

void bootloader_property_soc_update(void);

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

// See property.h for documentation on this function.
status_t bootloader_property_init(void)
{
    uint32_t rompatchVersion = 0;
    uint32_t productIdFuseIdx = 24; //  fuse bit 23:16 are the rom patch version, 00010000b means rom patch version 1.0
    status_t status = otp_fuse_read(productIdFuseIdx, &rompatchVersion);
    rompatchVersion = (rompatchVersion & 0xFF0000) >> 16u;

    if (status != kStatus_Success)
    {
        return status;
    }

    property_store_t *propertyStore = g_bootloaderContext.propertyInterface->store;

// Fill in reserved regions.
//! @todo Support other tool chain

#if BL_FEATURE_RESERVED_REGION_AUTO_PROBE
    uint32_t flashStart = 0;
    uint32_t flashEnd = 0;
    uint32_t ramStart = 0;
    uint32_t ramEnd = 0;

    ramStart = __RAM_START;
    ramEnd = __RAM_END;
    assert(ramEnd);

    propertyStore->reservedRegions[kProperty_FlashReservedRegionIndex].startAddress = flashStart;
    propertyStore->reservedRegions[kProperty_FlashReservedRegionIndex].endAddress = flashEnd;
    propertyStore->reservedRegions[kProperty_RamReservedRegionIndex].startAddress = ramStart;
    propertyStore->reservedRegions[kProperty_RamReservedRegionIndex].endAddress = ramEnd;
#endif // BL_FEATURE_RESERVED_REGION_AUTO_PROBE

// Fill in unique device id value.
#if defined(SYSCON)
#if defined(SYSCON_DEVICE_ID0_PARTID_MASK)
    propertyStore->UniqueDeviceId.uid[0] = SYSCON->DEVICE_ID0;
#endif
#if defined(SYSCON_DEVICE_ID1_REVID_MASK)
    propertyStore->UniqueDeviceId.uid[1] = SYSCON->DEVICE_ID1;
#elif defined(SYSCON_DIEID_REV_ID_MASK)
    propertyStore->UniqueDeviceId.uid[1] = SYSCON->DIEID;
#endif
#elif defined(SYSCTL0)
    propertyStore->UniqueDeviceId.uid[0] = SYSCTL0->UUID[0];
    propertyStore->UniqueDeviceId.uid[1] = SYSCTL0->UUID[1];
    propertyStore->UniqueDeviceId.uid[2] = SYSCTL0->UUID[2];
    propertyStore->UniqueDeviceId.uid[3] = SYSCTL0->UUID[3];
#else
#error Unsupport LPC devices.
#endif

    // Set address range of RAM in property interface
    uint32_t ramIndex = 0;
    const memory_map_entry_t *map = (memory_map_entry_t *)&g_bootloaderContext.memoryMap[0];
    while (map->memoryInterface != NULL)
    {
        if ((map->memoryProperty & kMemoryType_RAM) && (map->memoryProperty & kMemoryIsExecutable))
        {
            assert(ramIndex < kRAMCount);

            propertyStore->ramStartAddress[ramIndex] = map->startAddress;
            propertyStore->ramSizeInBytes[ramIndex] = map->endAddress - map->startAddress + 1;
            ramIndex++;
        }
        ++map;
    }

    bootloader_property_soc_update();

    return kStatus_Success;
}

// See property.h for documentation on this function.
status_t bootloader_property_get(uint8_t tag, uint32_t id, const void **value, uint32_t *valueSize)
{
    property_store_t *propertyStore = g_bootloaderContext.propertyInterface->store;
    // Set default value size, may be modified below.
    uint32_t returnSize = sizeof(uint32_t);
    const void *returnValue;
    switch (tag)
    {
        case kPropertyTag_RAMStartAddress:
            if (id >= kRAMCount)
            {
                returnValue = &propertyStore->ramStartAddress[0];
            }
            else
            {
                returnValue = &propertyStore->ramStartAddress[id];
            }
            break;

        case kPropertyTag_RAMSizeInBytes:
            if (id >= kRAMCount)
            {
                returnValue = &propertyStore->ramSizeInBytes[0];
            }
            else
            {
                returnValue = &propertyStore->ramSizeInBytes[id];
            }
            break;

        case kPropertyTag_ReservedRegions:
            returnSize = sizeof(propertyStore->reservedRegions);
            returnValue = propertyStore->reservedRegions;
            break;

        case kPropertyTag_UniqueDeviceId:
            returnSize = kUid_SizeInBytes;
            returnValue = &propertyStore->UniqueDeviceId;
            break;
#if BL_FEATURE_EXTERNAL_MEMORY_PROPERTY
        case kPropertyTag_ExternalMemoryAttributes:
        {
            status_t status =
                bootloader_get_external_memory_properties(id, &propertyStore->externalMemoryPropertyStore);
            if (status != kStatus_Success)
            {
                return status;
            }
        }
            returnSize = sizeof(propertyStore->externalMemoryPropertyStore);
            returnValue = &propertyStore->externalMemoryPropertyStore;
            break;
#endif // BL_FEATURE_EXTERNAL_MEMORY_PROPERTY

        default:
            return kStatus_UnknownProperty;
    }

    // Set the return size.
    if (valueSize)
    {
        *valueSize = returnSize;
    }

    // Set the return value
    if (value)
    {
        *value = returnValue;
    }

    return kStatus_Success;
}

// See property.h for documentation on this function.
status_t bootloader_property_set_uint32(uint8_t tag, uint32_t value)
{
    switch (tag)
    {
        case kPropertyTag_BootloaderVersion:
        case kPropertyTag_AvailablePeripherals:
        case kPropertyTag_RAMStartAddress:
        case kPropertyTag_RAMSizeInBytes:
        case kPropertyTag_AvailableCommands:
#if BL_FEATURE_EXTERNAL_MEMORY_PROPERTY
        case kPropertyTag_ExternalMemoryAttributes:
#endif // BL_FEATURE_EXTERNAL_MEMORY_PROPERTY
        case kPropertyTag_MaxPacketSize:
        case kPropertyTag_ReservedRegions:
        case kPropertyTag_SystemDeviceId:
        case kPropertyTag_UniqueDeviceId:
        case kPropertyTag_TargetVersion:
            return kStatus_ReadOnlyProperty;
        default:
            return kStatus_UnknownProperty;
    }
}

#if BL_FEATURE_EXTERNAL_MEMORY_PROPERTY
status_t bootloader_get_external_memory_properties(uint32_t memoryId, external_memory_property_store_t *store)
{
    extern const external_memory_property_interface_t g_externalMemPropertyInterfaceMap[];

    // Find external memory property interface map.
    const external_memory_property_interface_t *map = &g_externalMemPropertyInterfaceMap[0];
    while (map && map->get)
    {
        if (map->memoryId == memoryId)
        {
            break;
        }
        map++;
    }

    if (map->get == NULL)
    {
        return kStatus_InvalidArgument;
    }

    external_memory_property_store_t propertyStore = { 0 };
    uint32_t memoryInitStatus = kStatus_Fail;
    status_t status = map->get(kExternalMemoryPropertyTag_InitStatus, &memoryInitStatus);
    if (status != kStatus_Success)
    {
        return status;
    }

    if (memoryInitStatus != kStatus_Success)
    {
        return memoryInitStatus;
    }

    uint32_t *property = (uint32_t *)&propertyStore.startAddress;
    propertyStore.availableAttributesFlag = 0;
    for (uint32_t tag = kExternalMemoryPropertyTag_Start; tag <= kExternalMemoryPropertyTag_End; tag++)
    {
        uint32_t tmp = 0;
        status_t status = map->get(tag, &tmp);
        if (status == kStatus_Success)
        {
            *property = tmp;
            propertyStore.availableAttributesFlag |= 1 << (tag - 1);
        }
        else
        {
            *property = 0;
        }

        property++;
    }

    memcpy(store, &propertyStore, sizeof(propertyStore));

    return kStatus_Success;
}
#endif // BL_FEATURE_EXTERNAL_MEMORY_PROPERTY


////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
