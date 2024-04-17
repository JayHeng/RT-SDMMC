/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _property_h
#define _property_h

#include <stdint.h>

#include "bootloader_common.h"
#include "fsl_device_registers.h"
#include "vector_table_info.h"

//! @addtogroup property
//! @{

////////////////////////////////////////////////////////////////////////////////
// Declarations
////////////////////////////////////////////////////////////////////////////////

//@}

//! @brief Property store status codes.
enum _property_errors
{
    kStatus_UnknownProperty = MAKE_STATUS(kStatusGroup_PropertyStore, 0),
    kStatus_ReadOnlyProperty = MAKE_STATUS(kStatusGroup_PropertyStore, 1),    //!< Property is read-only.
    kStatus_InvalidPropertyValue = MAKE_STATUS(kStatusGroup_PropertyStore, 2) //!< Property value is out of range.
};

//! @brief Property tags.
//! @note Do not change any tag values. Add tags at the end.
enum _property_tag
{
    kPropertyTag_ListProperties = 0x00,
    kPropertyTag_BootloaderVersion = 0x01,
    kPropertyTag_AvailablePeripherals = 0x02,
    kPropertyTag_FlashStartAddress = 0x03,
    kPropertyTag_FlashSizeInBytes = 0x04,
    kPropertyTag_FlashSectorSize = 0x05,
    kPropertyTag_FlashBlockCount = 0x06,
    kPropertyTag_AvailableCommands = 0x07,
    kPropertyTag_CrcCheckStatus = 0x08,
    kPropertyTag_Reserved9 = 0x09,
    kPropertyTag_VerifyWrites = 0x0a,
    kPropertyTag_MaxPacketSize = 0x0b,
    kPropertyTag_ReservedRegions = 0x0c,
    kPropertyTag_Reserved13 = 0x0d,
    kPropertyTag_RAMStartAddress = 0x0e,
    kPropertyTag_RAMSizeInBytes = 0x0f,
    kPropertyTag_SystemDeviceId = 0x10,
    kPropertyTag_FlashSecurityState = 0x11,
    kPropertyTag_UniqueDeviceId = 0x12,
    kPropertyTag_FacSupport = 0x13,
    kPropertyTag_FlashAccessSegmentSize = 0x14,
    kPropertyTag_FlashAccessSegmentCount = 0x15,
    kPropertyTag_FlashReadMargin = 0x16,
    kPropertyTag_QspiInitStatus = 0x17,
    kPropertyTag_TargetVersion = 0x18,
    kPropertyTag_ExternalMemoryAttributes = 0x19,
    kPropertyTag_ReliableUpdateStatus = 0x1a,
    kPropertyTag_FlashPageSize = 0x1b,
    kPropertyTag_FuseLockedStatus = 0x1f,
    kPropertyTag_InvalidProperty = 0xFF,
};

//! @brief Property constants.
enum _property_constants
{
    kProperty_ReservedRegionsCount = 2,
    kProperty_FlashReservedRegionIndex = 0,
    kProperty_RamReservedRegionIndex = 1,

    kProperty_FlashVersionIdSizeInBytes = 8,
};

//! @brief Bit positions for clock flags in configuration data.
enum _clock_flags
{
    kClockFlag_HighSpeed = (1 << 0)
};

//! @brief Bit positions for boot flags in configuration data
enum _boot_flags
{
    kBootFlag_DirectBoot = (1 << 0)
};

//! @brief Flash constants.
enum _flash_constants
{
    //! @brief The bootloader configuration data location .
    //!
    //! A User Application should populate a BootloaderConfigurationData
    //! struct at 0x3c0 from the beginning of the application image which must
    //! be the User Application vector table for the flash-resident bootloader
    //! collaboration.
    kBootloaderConfigAreaAddress = (uint32_t)(APP_VECTOR_TABLE) + 0x3c0,
#if defined(FSL_FEATURE_FLASH_HAS_MULTIPLE_FLASH) || defined(FSL_FEATURE_FLASH_PFLASH_1_START_ADDRESS)
#if BL_FEATURE_SUPPORT_DFLASH
    kFLASHCount = 3,
#else
    kFLASHCount = 2,
#endif // BL_FEATURE_SUPPORT_DFLASH
#else
#if BL_FEATURE_SUPPORT_DFLASH
    kFLASHCount = 2,
#else
    kFLASHCount = 1,
#endif // BL_FEATURE_SUPPORT_DFLASH
#endif
};

//! @brief Structure of a reserved regions entry.
typedef struct ReservedRegion
{
    uint32_t startAddress;
    uint32_t endAddress;
} reserved_region_t;

//! @brief Structure of a unique device id.
typedef struct UniqueDeviceId
{
    uint32_t uid[kUniqueId_SizeInBytes / sizeof(uint32_t)];
} unique_device_id_t;

//! @brief External Memory Properties tag
enum _external_memory_property_tags
{
    kExternalMemoryPropertyTag_InitStatus = 0,         //!< Init status tag
    kExternalMemoryPropertyTag_StartAddress = 1,       //!< Start address tag
    kExternalMemoryPropertyTag_MemorySizeInKbytes = 2, //!< Memory size tag
    kExternalMemoryPropertyTag_PageSize = 3,           //!< Pag size tag
    kExternalMemoryPropertyTag_SectorSize = 4,         //!< Sector size tag
    kExternalMemoryPropertyTag_BlockSize = 5,          //!< Block size tag

    kExternalMemoryPropertyTag_Start = kExternalMemoryPropertyTag_StartAddress,
    kExternalMemoryPropertyTag_End = kExternalMemoryPropertyTag_BlockSize,
};

//! @brief Exernal Memory attribute store
typedef struct
{
    uint32_t availableAttributesFlag; //!< Available Atrributes, bit map
    uint32_t startAddress;            //!< start Address of external memory
    uint32_t flashSizeInKB;           //!< flash size of external memory
    uint32_t pageSize;                //!< page size of external memory
    uint32_t sectorSize;              //!< sector size of external memory
    uint32_t blockSize;               //!< block size of external memory
} external_memory_property_store_t;

enum _ram_constants
{
#if CPU_IS_ARM_CORTEX_M7 || CPU_IS_ARM_CORTEX_M33
    kRAMCount = 3,
#endif

    kPropertyIndex_SRAM = 0,
#if CPU_IS_ARM_CORTEX_M7 || CPU_IS_ARM_CORTEX_M33

    kPropertyIndex_DTCM = 1,
    kPropertyIndex_OCRAM = 2,
#endif
};

//! @brief Structure of property store.
typedef struct PropertyStore
{
    standard_version_t bootloaderVersion;     //!< Current bootloader version.
    standard_version_t targetVersion;         //!< Target version number.
    uint32_t ramStartAddress[kRAMCount];   //!< Start address of RAM
    uint32_t ramSizeInBytes[kRAMCount];    //!< Size in bytes of RAM
    unique_device_id_t UniqueDeviceId;             //!< Unique identification for the device.
    reserved_region_t reservedRegions[kProperty_ReservedRegionsCount]; //!< Flash and Ram reserved regions.
    external_memory_property_store_t externalMemoryPropertyStore; //!< Property store for external memory

} property_store_t;

enum _property_store_tags
{
    //! @brief Tag value used to validate the bootloader configuration data.
    kPropertyStoreTag = FOUR_CHAR_CODE('k', 'c', 'f', 'g')
};

//! @brief External Memory properties interface
typedef struct ExternalMemoryPropertyInterface
{
    uint32_t memoryId;
    status_t (*get)(uint32_t tag, uint32_t *value);
} external_memory_property_interface_t;

//! @brief Interface to property operations.
typedef struct PropertyInterface
{
    status_t (*load_user_config)(void); //!< Load the user configuration data
    status_t (*init)(void);             //!< Initialize
    status_t (*get)(uint8_t tag, uint32_t id, const void **value, uint32_t *valueSize); //!< Get property
    status_t (*set_uint32)(uint8_t tag, uint32_t value);                                //!< Set uint32_t property
    property_store_t *store;                                                            //!< The property store
} property_interface_t;

////////////////////////////////////////////////////////////////////////////////
// Externs
////////////////////////////////////////////////////////////////////////////////

//! @brief Property interface.
extern const property_interface_t g_propertyInterface;

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if __cplusplus
extern "C"
{
#endif

    //! @name Property Store
    //@{

    //! @brief Early initialization function to get user configuration data
    status_t bootloader_property_load_user_config(void);

    //! @brief Initialize the property store.
    status_t bootloader_property_init(void);

    //! @brief Get a property.
    //!
    //! Example calling sequence for uint32_t property:
    //! @code
    //! void * value;
    //! uint32_t valueSize;
    //! status_t status = bootloader_property_get(sometag, &value, &valueSize);
    //! uint32_t result = *(uint32_t *)value;
    //! @endcode
    //!
    //! @param tag Tag of the requested property
    //! @param memoryId Id for specified external memory, for example: 1 represent QuadSPI 0
    //! @param value Pointer to where to write a pointer to the result, may be NULL
    //! @param valueSize Size in bytes of the property value, may be NULL
    //!
    //! @retval kStatus_Success
    //! @retval kStatus_UnknownProperty
    status_t bootloader_property_get(uint8_t tag, uint32_t memoryId, const void **value, uint32_t *valueSize);

    //! @brief Set a property.
    //!
    //! Only uint32_t properties can be set with this function.
    //!
    //! @param tag Tag of the property to set
    //! @param value New property value
    //!
    //! @retval kStatus_Success
    //! @retval kStatus_UnknownProperty
    //! @retval kStatus_ReadOnlyProperty
    status_t bootloader_property_set_uint32(uint8_t tag, uint32_t value);

    //@}

#if __cplusplus
}
#endif

//! @}

#endif // _property_h
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
