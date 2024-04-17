/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define exit exit_default
#include <stdbool.h>
#include "bl_context.h"
#include "bl_peripheral.h"
#include "bl_shutdown_cleanup.h"
#include "bootloader.h"
#include "bootloader_common.h"
#include "fsl_assert.h"
#include "fsl_rtos_abstraction.h"
#include "microseconds.h"
#include "property.h"
#include "vector_table_info.h"
#include "mmc_memory.h"

//! @addtogroup bl_core
//! @{

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

static void get_user_application_entry(uint32_t *appEntry, uint32_t *appStack);
static void jump_to_application(uint32_t applicationAddress, uint32_t stackPointer);

static void bootloader_init(void);
static void bootloader_run(void);

int main(void);

// Not used, but needed to resolve reference in startup.s.
// uint32_t g_bootloaderTree;

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

//! @brief Returns the user application address and stack pointer.
//!
//! For flash-resident and rom-resident target, gets the user application address
//! and stack pointer from the APP_VECTOR_TABLE.
//! Ram-resident version does not support jumping to application address.
static void get_user_application_entry(uint32_t *appEntry, uint32_t *appStack)
{
    assert(appEntry);
    assert(appStack);

    *appEntry = APP_VECTOR_TABLE[kInitialPC];
    *appStack = APP_VECTOR_TABLE[kInitialSP];
}


//! @brief Exits bootloader and jumps to the user application.
static void jump_to_application(uint32_t applicationAddress, uint32_t stackPointer)
{
    shutdown_cleanup(kShutdownType_Shutdown);

    // Create the function call to the user application.
    // Static variables are needed since changed the stack pointer out from under the compiler
    // we need to ensure the values we are using are not stored on the previous stack
    static uint32_t s_stackPointer = 0;
    s_stackPointer = stackPointer;
    static void (*farewellBootloader)(void) = 0;
    farewellBootloader = (void (*)(void))applicationAddress;

    // Set the VTOR to the application vector table address.
    SCB->VTOR = (uint32_t)APP_VECTOR_TABLE;

    // Set stack pointers to the application stack pointer.
    __set_MSP(s_stackPointer);
    __set_PSP(s_stackPointer);

    // Jump to the application.
    farewellBootloader();
    // Dummy fcuntion call, should never go to this fcuntion call
    shutdown_cleanup(kShutdownType_Shutdown);
}

//! A given jump address is considered valid if:
//! - Not 0x00000000
//! - Not 0xffffffff
//! - Not the reset handler entry point for the bootloader
//! - Is in flash or is in RAM or QuadSPI (if available)
//! @note this interface is also used by the configure_quadspi command
bool is_valid_application_location(uint32_t applicationAddress)
{
    const memory_map_entry_t *map;
    // Verify that the jumpLocation is non zero and then either within flash or RAM, both calculations are:
    // (jumpLocation >= startAddress) && (jumpLocation < (startAddress + size))
    if ((!applicationAddress) ||              // address is not null AND
        (applicationAddress == 0xffffffff) || // address is not blank Flash (0xff) AND
        (applicationAddress == (uint32_t)&Reset_Handler))
    {
        return false;
    }

    bool isValid = false;
    const uint32_t minThumb2InstructionSize = 2; // smallest thumb2 instruction size is 16-bit.
    // Check if the application address is in valid executable memory range
    status_t status = find_map_entry(applicationAddress, minThumb2InstructionSize, &map);
    if ((status == kStatus_Success) && (map->memoryProperty & kMemoryIsExecutable))
    {
        isValid = true;
    }

    return isValid;
}

bool is_valid_stackpointer_location(uint32_t stackpointerAddress)
{
    const memory_map_entry_t *map;
    bool isValid = false;

    map = &g_bootloaderContext.memoryMap[0];

    while (map->memoryInterface != NULL)
    {
        if ((map->memoryProperty & kMemoryIsExecutable) && (map->memoryProperty & kMemoryType_RAM))
        {
            if ((stackpointerAddress > map->startAddress) && (stackpointerAddress <= (map->endAddress + 1)))
            {
                isValid = true;
                break;
            }
        }

        ++map;
    }

    return isValid;
}

//! @brief Initialize the bootloader and peripherals.
//!
//! This function initializes hardware and clocks, loads user configuration data, and initialzes
//! a number of drivers. It then enters the active peripheral detection phase by calling
//! get_active_peripheral(). Once the peripheral is detected, the packet and comand interfaces
//! are initialized.
//!
//! Note that this routine may not return if peripheral detection times out and the bootloader
//! jumps directly to the user application in flash.
static void bootloader_init(void)
{
    // Init the global irq lock
    lock_init();

    // Init pinmux and other hardware setup.
    init_hardware();

    // Configure clocks.
    configure_clocks(kClockOption_EnterBootloader);

    // Start the lifetime counter
    microseconds_init();

    // Init address range of flash array, SRAM_L and SRAM U.
    g_bootloaderContext.memoryInterface->init();
    
    // Fully init the property store.
    g_bootloaderContext.propertyInterface->init();
}

uint8_t s_testBuf[0x400];

static void bootloader_run(void)
{
    status_t status = kStatus_InvalidArgument;
    
    mmc_config_t mmcConfig = 
    {
       .word0.U = 0xc0001200,
       .word1.U = 0x00040002,
    };

    status = mem_config(kMemoryMMCCard, (uint32_t *)&mmcConfig);
    if (status == kStatus_Success)
    {
        memset(s_testBuf, 0x0, sizeof(s_testBuf));
        
        status = mem_read(0x8000, sizeof(s_testBuf), s_testBuf, kMemoryMMCCard);
        if (status == kStatus_Success)
        {
            debug_printf("Info: emmc read test pass\r\n");
        }
    }

  
    while (1)
    {

    }
}

//! @brief Entry point for the bootloader.
int main(void)
{
    bootloader_init();
    bootloader_run();

    // Should never end up here.
    debug_printf("Warning: reached end of main()\r\n");
    return 0;
}

//! Since we never exit this gets rid of the C standard functions that cause
//! extra ROM size usage.
#undef exit
void exit(int arg) {}

#if defined(__CC_ARM) || (__ARMCC_VERSION)
#define ITM_Port8(n) (*((volatile unsigned char *)(0xE0000000 + 4 * n)))
#define ITM_Port16(n) (*((volatile unsigned short *)(0xE0000000 + 4 * n)))
#define ITM_Port32(n) (*((volatile unsigned long *)(0xE0000000 + 4 * n)))

#define DEMCR (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA 0x01000000

FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f)
{
    if (DEMCR & TRCENA)
    {
        while (ITM_Port32(0) == 0)
            ;
        ITM_Port8(0) = ch;
    }
    return (ch);
}
#endif

//! @}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
