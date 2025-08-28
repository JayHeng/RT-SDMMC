/*
 * Copyright 2017-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "bl_context.h"
#include "bootloader_common.h"
#include "fsl_assert.h"
#include "fsl_device_registers.h"
#include "fsl_reset.h"
#include "fsl_clock.h"
#include "fusemap.h"
#include "target_config.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
enum
{
    kSize_32KB = 32u * 1024u,
    kSize_64KB = 64u * 1024u,
    kSize_128KB = 128u * 1024u,
    kSize_256KB = 256u * 1024u
};

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

void pmc_apply_cfg(void);

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void update_memory_map_lpc_sram(void)
{
    const uint32_t kSramPartitionSize[32] = {
        kSize_32KB,  kSize_32KB,  kSize_32KB,  kSize_32KB,  // 0 - 3
        kSize_32KB,  kSize_32KB,  kSize_32KB,  kSize_32KB,  // 4 - 7
        kSize_64KB,  kSize_64KB,  kSize_64KB,  kSize_64KB,  // 8 - 11
        kSize_128KB, kSize_128KB, kSize_128KB, kSize_128KB, // 12 - 15
        kSize_256KB, kSize_256KB, kSize_256KB, kSize_256KB, // 16 - 19
        kSize_256KB, kSize_256KB, kSize_256KB, kSize_256KB, // 20 - 23
        kSize_256KB, kSize_256KB, kSize_256KB, kSize_256KB, // 24 - 27
        kSize_256KB, kSize_256KB, 0,           0,           // 28 - 31
    };
    static uint32_t s_sramIndex = 0;

    // Detect the maximum RAM size
    uint32_t ramPartionSizeIndex = 31;
    while ((SYSCTL0->SRAMCFGENABLE0 & (1u << ramPartionSizeIndex)) == 0)
    {
        ramPartionSizeIndex--;
    }

    // Update the RAM size after all required SRAM partitions are powered up.
    uint32_t actualRamSize = 0;
    for (uint32_t i = 0; i <= ramPartionSizeIndex; i++)
    {
        actualRamSize += kSramPartitionSize[i];
    }

    // Update the memory map to match the actual SoC configuration.
    memory_map_entry_t *mapEntry = (memory_map_entry_t *)g_bootloaderContext.memoryMap;
    uint32_t index = 0;
    while ((mapEntry != NULL) && mapEntry->memoryInterface != NULL)
    {
        if (mapEntry->memoryProperty & kMemoryType_RAM)
        {
            if (s_sramIndex == index)
            {
                mapEntry->endAddress = mapEntry->startAddress + actualRamSize - 1;
                ++s_sramIndex;
                debug_printf("memory_map_entry: start=%x, end=%x\n", mapEntry->startAddress, mapEntry->endAddress);
            }
        }
        ++index;
        ++mapEntry;
    }
}

void init_hardware_api(void)
{
}

void pmc_apply_cfg(void)
{
    // Apply PMC change and while until the FSM is idle
    PMC->CTRL |= PMC_CTRL_APPLYCFG_MASK;            // Apply updated PMC PDRUNCFGbits (RAM power gates).
    while (PMC->STATUS & PMC_STATUS_ACTIVEFSM_MASK) // Wait until all the PMC finite state machines are idle
    {
    }
}

#define SYSCTL0_PERICFGENABLE1_SDIO0_EN_MASK     (0x4U)
#define SYSCTL0_PERICFGENABLE1_SDIO1_EN_MASK     (0x8U)

void init_hardware(void)
{
    // Power on eMMC RAM as needed
    if (SYSCTL0->PERICFGENABLE1 & SYSCTL0_PERICFGENABLE1_SDIO0_EN_MASK)
    {
        SYSCTL0->PDRUNCFG1_CLR = (SYSCTL0_PDRUNCFG1_USDHC0_SRAM_APD_MASK | SYSCTL0_PDRUNCFG1_USDHC0_SRAM_PPD_MASK);
    }

    if (SYSCTL0->PERICFGENABLE1 & SYSCTL0_PERICFGENABLE1_SDIO1_EN_MASK)
    {
        SYSCTL0->PDRUNCFG1_CLR = (SYSCTL0_PDRUNCFG1_USDHC1_SRAM_APD_MASK | SYSCTL0_PDRUNCFG1_USDHC1_SRAM_PPD_MASK);
    }

    // Apply PMC change
    pmc_apply_cfg();

    // Configure clock here because the configure_clocks has been removed from bl_main.c
    configure_clocks(kClockOption_EnterBootloader);
}

void deinit_hardware(void)
{

}


void debug_init(void)
{
}

#if __ICCARM__

size_t __write(int handle, const unsigned char *buf, size_t size)
{
    return size;
}

#endif // __ICCARM__

// Update Reserved RAM regions
void bootloader_property_soc_update(void)
{
    property_store_t *propertyStore = g_bootloaderContext.propertyInterface->store;

    uint32_t reservedSize = kBootloader_ReservedRAM_Size;

    // Set address range of RAM in property interface
    uint32_t ramIndex = 0;
    const memory_map_entry_t *map = (memory_map_entry_t *)&g_bootloaderContext.memoryMap[0];
    while (map->memoryInterface != NULL)
    {
        if ((map->memoryProperty & kMemoryType_RAM) && (map->memoryProperty & kMemoryIsExecutable))
        {
            assert(ramIndex < kRAMCount);
            propertyStore->reservedRegions[ramIndex].startAddress = map->startAddress;
            propertyStore->reservedRegions[ramIndex].endAddress = map->startAddress + reservedSize - 1;
            ramIndex++;
        }
        ++map;
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
