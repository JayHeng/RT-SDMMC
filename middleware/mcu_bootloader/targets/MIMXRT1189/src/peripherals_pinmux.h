/*
 * Copyright 2018 NXP
 *
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_iomuxc.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

/*====================== SOC Definitions ===========================*/
#if FSL_FEATURE_SOC_RGPIO_COUNT
//! Convert RGPIO to common GPIO code.
#define GPIO_Type RGPIO_Type
#define GPIO_PinInit RGPIO_PinInit
#define GPIO_WritePinOutput RGPIO_WritePinOutput
#define GPIO_GetPinsInterruptFlags(base) RGPIO_GetPinsInterruptFlags(base, UART1_RX_GPIO_IRQOutput)
#define GPIO_ClearPinsInterruptFlags(base, mask) RGPIO_ClearPinsInterruptFlags(base, UART1_RX_GPIO_IRQOutput, mask)
#define GPIO_SetPinInterruptConfig(base, pin, mode) \
    RGPIO_SetPinInterruptConfig(base, pin, UART1_RX_GPIO_IRQOutput, mode)
#define gpio_pin_config_t rgpio_pin_config_t
#define kGPIO_DigitalInput kRGPIO_DigitalInput
#define kGPIO_DigitalOutput kRGPIO_DigitalOutput
#define kGPIO_IntFallingEdge kRGPIO_InterruptFallingEdge
#define kGPIO_NoIntmode kRGPIO_InterruptOrDMADisabled
#endif

static inline void IOMUXC_RestoreDefault(uint32_t muxRegister,
                                         uint32_t muxMode,
                                         uint32_t inputRegister,
                                         uint32_t inputDaisy,
                                         uint32_t configRegister,
                                         uint32_t muxDefaultMode,
                                         uint32_t configDefaultValue)
{
    *((volatile uint32_t *)muxRegister) = muxDefaultMode;
    if (inputRegister)
    {
        *((volatile uint32_t *)inputRegister) = 0 /*Daisy defualt value*/;
    }
    if (configRegister)
    {
        *((volatile uint32_t *)configRegister) = configDefaultValue;
    }
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
