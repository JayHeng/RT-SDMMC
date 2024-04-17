/*
 * Copyright 2018 - 2019 NXP
 *
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bl_semc.h"
#include "fusemap.h"
#include "memory_config.h"
#include "peripherals_pinmux.h"
#include "spi_nor_eeprom_memory.h"

////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define FREQ_396MHz (396000000U)
#define FREQ_480MHz (480000000U)
#define FREQ_528MHz (528000000U)
#define FREQ_24MHz (24000000U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void update_memory_map(void);

/*******************************************************************************
 * Codes
 ******************************************************************************/

#if __ICCARM__

size_t __write(int handle, const unsigned char *buf, size_t size)
{
    return size;
}

#endif // __ICCARM__

void update_available_peripherals()
{
    // Flashloader always uses NXP Kboot PID and VID.
}

void init_hardware(void)
{
    // Configure Clocks
    configure_clocks(kClockOption_EnterBootloader);

    // Update memory map according to actual Fuse definitions
    update_memory_map();
}

void deinit_hardware(void)
{

}

//!@brief Get the hab status.
habstatus_option_t get_hab_status(void)
{
    habstatus_option_t habStatus = kHabStatus_Close;

    if (FUSE_FIELD_RETURN_VALUE)
    {
        habStatus = kHabStatus_Open;
    }
    else
    {
        if (FUSE_SEC_CONFIG_VALUE == 1)
        {
            habStatus = kHabStatus_Open;
        }
        else if (FUSE_SEC_CONFIG_VALUE < 1)
        {
            habStatus = kHabStatus_Open;
        }
        else
        {
            habStatus = kHabStatus_Close;
        }
    }

    return habStatus;
}

void update_memory_map(void)
{
    typedef struct
    {
        uint16_t dtcmSize;
        uint16_t itcmSize;
        uint16_t ocramSize;
    } flexram_cfg_t;

    const flexram_cfg_t k_flexramCfgList[] = {
        { 256, 256, 0 },   { 320, 192, 0 },  { 384, 128, 0 },  { 448, 64, 0 },    { 512, 0, 0 },    { 192, 320, 0 },
        { 128, 384, 0 },   { 64, 448, 0 },   { 0, 512, 0 },    { 256, 192, 64 },  { 320, 128, 64 }, { 384, 64, 64 },
        { 448, 0, 64 },    { 192, 256, 64 }, { 128, 320, 64 }, { 64, 384, 64 },   { 0, 448, 64 },   { 192, 192, 128 },
        { 256, 128, 128 }, { 328, 64, 128 }, { 384, 0, 128 },  { 128, 256, 128 }, { 64, 320, 128 }, { 0, 384, 128 },
        { 192, 128, 192 }, { 256, 64, 192 }, { 320, 0, 192 },  { 128, 192, 192 }, { 64, 256, 192 }, { 0, 320, 192 },
        { 128, 128, 256 }, { 192, 64, 256 }, { 256, 0, 256 },  { 64, 192, 256 },  { 0, 256, 256 },  { 128, 64, 320 },
        { 192, 0, 320 },   { 64, 128, 320 }, { 0, 192, 320 },  { 64, 64, 384 },   { 128, 0, 384 },  { 0, 128, 384 },
        { 64, 0, 448 },    { 0, 64, 448 },   { 0, 0, 512 },
    };

    uint32_t flexramCfgIndex = FUSE_FLEXRAM_CFG_VALUE;
    if (flexramCfgIndex >= ARRAY_SIZE(k_flexramCfgList))
    {
        // Reset the device and try to reboot again in case this issue is caused by abnormals
        NVIC_SystemReset();
    }
    debug_printf("FLEXRAM config, index = %x, dtcmSize = %x, itcmSize = %x, ocramSize = %x\n", flexramCfgIndex,
                 k_flexramCfgList[flexramCfgIndex].dtcmSize, k_flexramCfgList[flexramCfgIndex].itcmSize,
                 k_flexramCfgList[flexramCfgIndex].ocramSize);

    {
        uint32_t itcmSize = 1024u * k_flexramCfgList[flexramCfgIndex].itcmSize;
        uint32_t dtcmSize = 1024u * k_flexramCfgList[flexramCfgIndex].dtcmSize;
        uint32_t flexramOcramSize = 1024u * k_flexramCfgList[flexramCfgIndex].ocramSize;

        // ITCM
        g_memoryMap[kIndexITCM].startAddress = M7_ITCM_SRAM_START_ADDRESS;
        g_memoryMap[kIndexITCM].endAddress = g_memoryMap[kIndexITCM].startAddress + itcmSize - 1;

        // DTCM
        g_memoryMap[kIndexDTCM].startAddress = M7_DTCM_SRAM_START_ADDRESS;
        g_memoryMap[kIndexDTCM].endAddress = g_memoryMap[kIndexDTCM].startAddress + dtcmSize - 1;

        // OCRAM
        uint32_t fixedOcramSize = M4_OCRAM_SIZE + OCRAM1_SIZE + OCRAM2_SIZE + OCRAM_ECC_SIZE + FLEXRAM_ECC_SIZE;
        g_memoryMap[kIndexOCRAM].startAddress = OCRAM_START_ADDRESS;
        g_memoryMap[kIndexOCRAM].endAddress =
            g_memoryMap[kIndexOCRAM].startAddress + fixedOcramSize + flexramOcramSize - 1;
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
