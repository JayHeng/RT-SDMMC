/*
 * Copyright 2017-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bootloader_common.h"
#include "fsl_assert.h"
#include "fsl_device_registers.h"
#include "fsl_sdmmc_common.h"
#include "fusemap.h"
#include "sdmmc_init.h"
#if BL_FEATURE_MMC_MODULE
#include "mmc_memory.h"
#endif
#if BL_FEATURE_SD_MODULE
#include "sd_memory.h"
#endif
/*******************************************************************************
 * Definitons
 ******************************************************************************/


/*******************************************************************************
 * Variable
 ******************************************************************************/

const uint32_t usdhc_vselect_pin_settings = IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1);

/*
 * Config DATA3 pin as the CD pin. DATA3 pin must be pulled down to act as a card detection pin.
 */
const uint32_t usdhc_cmd_pin_settings = IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                        IOMUXC_SW_PAD_CTL_PAD_DSE(1); 
const uint32_t usdhc_clk_pin_settings = IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |     \
                                        IOMUXC_SW_PAD_CTL_PAD_SPEED(1) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                        IOMUXC_SW_PAD_CTL_PAD_DSE(4);
const uint32_t usdhc_data_pin_settings = IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                         IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                         IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                         IOMUXC_SW_PAD_CTL_PAD_DSE(1);
const uint32_t usdhc_data_pin_nopull = IOMUXC_SW_PAD_CTL_PAD_PKE(0) | IOMUXC_SW_PAD_CTL_PAD_ODE(0);

/*******************************************************************************
 * Code
 ******************************************************************************/
void usdhc_power_control_init(USDHC_Type *base)
{
    if (base == BOARD_USDHC1_BASEADDR)
    {
        IOMUXC_SetPinMux(BOARD_USDHC1_RESET_B_GPIO_IOMUXC, false);
        gpio_pin_config_t sw_config = {
            kGPIO_DigitalOutput,
            0,
            kGPIO_NoIntmode,
        };
        GPIO_PinInit(BOARD_USDHC1_RESET_B_GPIO_BASE, BOARD_USDHC1_RESET_B_GPIO_PIN, &sw_config);
    }
    else if (base == BOARD_USDHC2_BASEADDR)
    {
        IOMUXC_SetPinMux(BOARD_USDHC2_RESET_B_GPIO_IOMUXC, false);
        gpio_pin_config_t sw_config = {
            kGPIO_DigitalOutput,
            0,
            kGPIO_NoIntmode,
        };
        GPIO_PinInit(BOARD_USDHC2_RESET_B_GPIO_BASE, BOARD_USDHC2_RESET_B_GPIO_PIN, &sw_config);
    }
}

void usdhc_power_control(USDHC_Type *base, bool state)
{
    if (base == BOARD_USDHC1_BASEADDR)
    {
        GPIO_WritePinOutput(BOARD_USDHC1_RESET_B_GPIO_BASE, BOARD_USDHC1_RESET_B_GPIO_PIN, state);
    }
    else if (base == BOARD_USDHC2_BASEADDR)
    {
        GPIO_WritePinOutput(BOARD_USDHC2_RESET_B_GPIO_BASE, BOARD_USDHC2_RESET_B_GPIO_PIN, state);
    }
}

void usdhc_vselect_init(USDHC_Type *base)
{
    if (base == BOARD_USDHC1_BASEADDR)
    {
        IOMUXC_SetPinMux(BOARD_USDHC1_VSELECT_IOMUXC, false);
        IOMUXC_SetPinConfig(BOARD_USDHC1_VSELECT_IOMUXC, usdhc_vselect_pin_settings);
    }
    else if (base == BOARD_USDHC2_BASEADDR)
    {
        IOMUXC_SetPinMux(BOARD_USDHC2_VSELECT_IOMUXC, false);
        IOMUXC_SetPinConfig(BOARD_USDHC2_VSELECT_IOMUXC, usdhc_vselect_pin_settings);
    }
}

#if BL_FEATURE_MMC_MODULE
void mmc_pinmux_config(USDHC_Type *base, mmc_data_bus_width_t busWidth)
{
    if (base == BOARD_USDHC1_BASEADDR)
    {
        switch (busWidth)
        {
            case kMMC_DataBusWidth8bitDDR:
            case kMMC_DataBusWidth8bit:
            case kMMC_DataBusWidth4bitDDR:
            case kMMC_DataBusWidth4bit:
                IOMUXC_SetPinMux(BOARD_USDHC1_DATA1_IOMUXC, false);
                IOMUXC_SetPinMux(BOARD_USDHC1_DATA2_IOMUXC, false);
                IOMUXC_SetPinMux(BOARD_USDHC1_DATA3_IOMUXC, false);
                IOMUXC_SetPinConfig(BOARD_USDHC1_DATA1_IOMUXC, usdhc_data_pin_settings);
                IOMUXC_SetPinConfig(BOARD_USDHC1_DATA2_IOMUXC, usdhc_data_pin_settings);
                IOMUXC_SetPinConfig(BOARD_USDHC1_DATA3_IOMUXC, usdhc_data_pin_settings);
            case kMMC_DataBusWidth1bit:
            default:
                IOMUXC_SetPinMux(BOARD_USDHC1_CMD_IOMUXC, true);
                IOMUXC_SetPinMux(BOARD_USDHC1_CLK_IOMUXC, false);
                IOMUXC_SetPinMux(BOARD_USDHC1_DATA0_IOMUXC, false);
                IOMUXC_SetPinConfig(BOARD_USDHC1_CMD_IOMUXC, usdhc_cmd_pin_settings);
                IOMUXC_SetPinConfig(BOARD_USDHC1_CLK_IOMUXC, usdhc_clk_pin_settings);
                IOMUXC_SetPinConfig(BOARD_USDHC1_DATA0_IOMUXC, usdhc_data_pin_settings);
        }
    }
    else if (base == BOARD_USDHC2_BASEADDR)
    {
        switch (busWidth)
        {
            case kMMC_DataBusWidth8bitDDR:
            case kMMC_DataBusWidth8bit:
                IOMUXC_SetPinMux(BOARD_USDHC2_DATA4_IOMUXC, false);
                IOMUXC_SetPinMux(BOARD_USDHC2_DATA5_IOMUXC, false);
                IOMUXC_SetPinMux(BOARD_USDHC2_DATA6_IOMUXC, false);
                IOMUXC_SetPinMux(BOARD_USDHC2_DATA7_IOMUXC, false);
                IOMUXC_SetPinConfig(BOARD_USDHC2_DATA4_IOMUXC, usdhc_data_pin_settings);
                IOMUXC_SetPinConfig(BOARD_USDHC2_DATA5_IOMUXC, usdhc_data_pin_settings);
                IOMUXC_SetPinConfig(BOARD_USDHC2_DATA6_IOMUXC, usdhc_data_pin_settings);
                IOMUXC_SetPinConfig(BOARD_USDHC2_DATA7_IOMUXC, usdhc_data_pin_settings);
            case kMMC_DataBusWidth4bitDDR:
            case kMMC_DataBusWidth4bit:
                IOMUXC_SetPinMux(BOARD_USDHC2_DATA1_IOMUXC, false);
                IOMUXC_SetPinMux(BOARD_USDHC2_DATA2_IOMUXC, false);
                IOMUXC_SetPinMux(BOARD_USDHC2_DATA3_IOMUXC, false);
                IOMUXC_SetPinConfig(BOARD_USDHC2_DATA1_IOMUXC, usdhc_data_pin_settings);
                IOMUXC_SetPinConfig(BOARD_USDHC2_DATA2_IOMUXC, usdhc_data_pin_settings);
                IOMUXC_SetPinConfig(BOARD_USDHC2_DATA3_IOMUXC, usdhc_data_pin_settings);
            case kMMC_DataBusWidth1bit:
            default:
                IOMUXC_SetPinMux(BOARD_USDHC2_CMD_IOMUXC, true);
                IOMUXC_SetPinMux(BOARD_USDHC2_CLK_IOMUXC, false);
                IOMUXC_SetPinMux(BOARD_USDHC2_DATA0_IOMUXC, false);
                IOMUXC_SetPinConfig(BOARD_USDHC2_CMD_IOMUXC, usdhc_cmd_pin_settings);
                IOMUXC_SetPinConfig(BOARD_USDHC2_CLK_IOMUXC, usdhc_clk_pin_settings);
                IOMUXC_SetPinConfig(BOARD_USDHC2_DATA0_IOMUXC, usdhc_data_pin_settings);
        }
    }
}

status_t get_mmc_default_configuration(mmc_card_t *card)
{
    status_t status = kStatus_Fail;
    return status;
}
#endif // #if BL_FEATURE_MMC_MODULE

#if BL_FEATURE_SD_MODULE
void sd_pinmux_config(USDHC_Type *base, sd_data_bus_width_t busWidth)
{
    if (base == BOARD_USDHC1_BASEADDR)
    {
        switch (busWidth)
        {
            case kUSDHC_DataBusWidth4Bit:
                IOMUXC_SetPinMux(BOARD_USDHC1_DATA1_IOMUXC, false);
                IOMUXC_SetPinMux(BOARD_USDHC1_DATA2_IOMUXC, false);
                IOMUXC_SetPinMux(BOARD_USDHC1_DATA3_IOMUXC, false);
                IOMUXC_SetPinConfig(BOARD_USDHC1_DATA1_IOMUXC, usdhc_data_pin_settings);
                IOMUXC_SetPinConfig(BOARD_USDHC1_DATA2_IOMUXC, usdhc_data_pin_settings);
                IOMUXC_SetPinConfig(BOARD_USDHC1_DATA3_IOMUXC, usdhc_data_pin_settings);
            case kUSDHC_DataBusWidth1Bit:
                IOMUXC_SetPinMux(BOARD_USDHC1_CMD_IOMUXC, true);
                IOMUXC_SetPinMux(BOARD_USDHC1_CLK_IOMUXC, false);
                IOMUXC_SetPinMux(BOARD_USDHC1_DATA0_IOMUXC, false);
                IOMUXC_SetPinConfig(BOARD_USDHC1_CMD_IOMUXC, usdhc_cmd_pin_settings);
                IOMUXC_SetPinConfig(BOARD_USDHC1_CLK_IOMUXC, usdhc_clk_pin_settings);
                IOMUXC_SetPinConfig(BOARD_USDHC1_DATA0_IOMUXC, usdhc_data_pin_settings);
        }
        if (busWidth == kSD_DataBusWidth1Bit)
        {
            /*
             * Note: Pull-down on DATA3 pin is enabled by default. Disable it to let SD Card enter the SD mode.
             */
            IOMUXC_SetPinConfig(BOARD_USDHC1_DATA3_IOMUXC, usdhc_data_pin_nopull);
        }
    }
    else if (base == BOARD_USDHC2_BASEADDR)
    {
        switch (busWidth)
        {
            case kUSDHC_DataBusWidth4Bit:
                IOMUXC_SetPinMux(BOARD_USDHC2_DATA1_IOMUXC, false);
                IOMUXC_SetPinMux(BOARD_USDHC2_DATA2_IOMUXC, false);
                IOMUXC_SetPinMux(BOARD_USDHC2_DATA3_IOMUXC, false);
                IOMUXC_SetPinConfig(BOARD_USDHC2_DATA1_IOMUXC, usdhc_data_pin_settings);
                IOMUXC_SetPinConfig(BOARD_USDHC2_DATA2_IOMUXC, usdhc_data_pin_settings);
                IOMUXC_SetPinConfig(BOARD_USDHC2_DATA3_IOMUXC, usdhc_data_pin_settings);
            case kUSDHC_DataBusWidth1Bit:
                IOMUXC_SetPinMux(BOARD_USDHC2_CMD_IOMUXC, true);
                IOMUXC_SetPinMux(BOARD_USDHC2_CLK_IOMUXC, false);
                IOMUXC_SetPinMux(BOARD_USDHC2_DATA0_IOMUXC, false);
                IOMUXC_SetPinConfig(BOARD_USDHC2_CMD_IOMUXC, usdhc_cmd_pin_settings);
                IOMUXC_SetPinConfig(BOARD_USDHC2_CLK_IOMUXC, usdhc_clk_pin_settings);
                IOMUXC_SetPinConfig(BOARD_USDHC2_DATA0_IOMUXC, usdhc_data_pin_settings);
        }
        if (busWidth == kSD_DataBusWidth1Bit)
        {
            /*
             * Note: Pull-down on DATA3 pin is enabled by default. Disable it to let SD Card enter the SD mode.
             */
            IOMUXC_SetPinConfig(BOARD_USDHC2_DATA3_IOMUXC, usdhc_data_pin_nopull);
        }
    }
}

status_t get_sd_default_configuration(sd_card_t *card)
{
    status_t status = kStatus_Fail;
    return status;
}
#endif // #if BL_FEATURE_SD_MODULE
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
