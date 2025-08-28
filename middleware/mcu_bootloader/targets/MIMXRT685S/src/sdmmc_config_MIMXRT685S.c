/*
* Copyright 2014-2016 Freescale Semiconductor, Inc.
* Copyright 2016-2018 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*
*/

#include "bootloader_common.h"
#include "fsl_device_registers.h"
#include "bootloader.h"
#include "fusemap.h"
#include "sdmmc_init.h"
#include "fsl_assert.h"
#include "fsl_mmc.h"
#include "fsl_sd.h"
#include "lpc_gpio/fsl_gpio.h"
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
 * Variables
 ******************************************************************************/
const uint32_t usdhc_reset_pin_settings = IOPCTL_PIO_IBENA(1) | IOPCTL_PIO_SLEWRATE(0) | IOPCTL_PIO_FULLDRIVE(1);
const uint32_t usdhc_vselect_pin_settings = IOPCTL_PIO_PUPDENA(1) | IOPCTL_PIO_PUPDSEL(1) | IOPCTL_PIO_IBENA(1) |
                                            IOPCTL_PIO_SLEWRATE(0) | IOPCTL_PIO_FULLDRIVE(1);
const uint32_t usdhc_cmd_pin_settings = IOPCTL_PIO_PUPDENA(1) | IOPCTL_PIO_PUPDSEL(1) | IOPCTL_PIO_IBENA(1) |
                                        IOPCTL_PIO_SLEWRATE(0) | IOPCTL_PIO_FULLDRIVE(1);
const uint32_t usdhc_clk_pin_settings = IOPCTL_PIO_PUPDENA(1) | IOPCTL_PIO_PUPDSEL(1) | IOPCTL_PIO_IBENA(1) |
                                        IOPCTL_PIO_SLEWRATE(0) | IOPCTL_PIO_FULLDRIVE(1);
const uint32_t usdhc_data_pin_settings = IOPCTL_PIO_PUPDENA(1) | IOPCTL_PIO_PUPDSEL(1) | IOPCTL_PIO_IBENA(1) |
                                         IOPCTL_PIO_SLEWRATE(0) | IOPCTL_PIO_FULLDRIVE(1);
/*******************************************************************************
 * Code
 ******************************************************************************/
#if BL_FEATURE_MMC_MODULE || BL_FEATURE_SD_MODULE
static inline void IOPAD_Set(IOPCTL_Type *base, uint8_t port, uint8_t pin, uint32_t fsel, uint32_t setting)
{
    base->PIO[port][pin] = IOPCTL_PIO_FSEL(fsel) | ((setting) & (~IOPCTL_PIO_FSEL_MASK));
}

void usdhc_power_control_init(USDHC_Type *base)
{
    if (base == BOARD_USDHC0_BASEADDR)
    {
        IOPAD_Set(BOARD_USDHC0_RESET_B_IOPAD, usdhc_reset_pin_settings);
        gpio_pin_config_t sw_config = { kGPIO_DigitalOutput, !OTP_SDHC0_PWR_POL_VALUE() };
        GPIO_PortInit(BOARD_USDHC0_RESET_B_PORT);
        GPIO_PinInit(BOARD_USDHC0_RESET_B_GPIO, &sw_config);
    }
    else if (base == BOARD_USDHC1_BASEADDR)
    {
        IOPAD_Set(BOARD_USDHC1_RESET_B_IOPAD, usdhc_reset_pin_settings);
        gpio_pin_config_t sw_config = { kGPIO_DigitalOutput, !OTP_SDHC1_PWR_POL_VALUE() };
        GPIO_PortInit(BOARD_USDHC1_RESET_B_PORT);
        GPIO_PinInit(BOARD_USDHC1_RESET_B_GPIO, &sw_config);
    }
}

void usdhc_power_control(USDHC_Type *base, bool state)
{
    if (base == BOARD_USDHC0_BASEADDR)
    {
        GPIO_PinWrite(BOARD_USDHC0_RESET_B_GPIO, state);
    }
    else if (base == BOARD_USDHC1_BASEADDR)
    {
        GPIO_PinWrite(BOARD_USDHC1_RESET_B_GPIO, state);
    }
}

void usdhc_vselect_init(USDHC_Type *base)
{
    if (base == BOARD_USDHC0_BASEADDR)
    {
        IOPAD_Set(BOARD_USDHC0_VSELECT_IOPAD, usdhc_vselect_pin_settings);
    }
    else if (base == BOARD_USDHC1_BASEADDR)
    {
        IOPAD_Set(BOARD_USDHC1_VSELECT_IOPAD, usdhc_vselect_pin_settings);
    }
}
#endif // #if BL_FEATURE_MMC_MODULE || BL_FEATURE_SD_MODULE

#if BL_FEATURE_MMC_MODULE
void mmc_pinmux_config(USDHC_Type *base, mmc_data_bus_width_t busWidth)
{
    if (base == BOARD_USDHC0_BASEADDR)
    {
        switch (busWidth)
        {
            case kMMC_DataBusWidth8bitDDR:
            case kMMC_DataBusWidth8bit:
                IOPAD_Set(BOARD_USDHC0_DATA4_IOPAD, usdhc_data_pin_settings);
                IOPAD_Set(BOARD_USDHC0_DATA5_IOPAD, usdhc_data_pin_settings);
                IOPAD_Set(BOARD_USDHC0_DATA6_IOPAD, usdhc_data_pin_settings);
                IOPAD_Set(BOARD_USDHC0_DATA7_IOPAD, usdhc_data_pin_settings);
            case kMMC_DataBusWidth4bitDDR:
            case kMMC_DataBusWidth4bit:
                IOPAD_Set(BOARD_USDHC0_DATA1_IOPAD, usdhc_data_pin_settings);
                IOPAD_Set(BOARD_USDHC0_DATA2_IOPAD, usdhc_data_pin_settings);
                IOPAD_Set(BOARD_USDHC0_DATA3_IOPAD, usdhc_data_pin_settings);
            case kMMC_DataBusWidth1bit:
            default:
                IOPAD_Set(BOARD_USDHC0_CMD_IOPAD, usdhc_cmd_pin_settings);
                IOPAD_Set(BOARD_USDHC0_CLK_IOPAD, usdhc_clk_pin_settings);
                IOPAD_Set(BOARD_USDHC0_DATA0_IOPAD, usdhc_data_pin_settings);
        }
    }
    else if (base == BOARD_USDHC1_BASEADDR)
    {
        switch (busWidth)
        {
            case kMMC_DataBusWidth8bitDDR:
            case kMMC_DataBusWidth8bit:
                IOPAD_Set(BOARD_USDHC1_DATA4_IOPAD, usdhc_data_pin_settings);
                IOPAD_Set(BOARD_USDHC1_DATA5_IOPAD, usdhc_data_pin_settings);
                IOPAD_Set(BOARD_USDHC1_DATA6_IOPAD, usdhc_data_pin_settings);
                IOPAD_Set(BOARD_USDHC1_DATA7_IOPAD, usdhc_data_pin_settings);
            case kMMC_DataBusWidth4bitDDR:
            case kMMC_DataBusWidth4bit:
                IOPAD_Set(BOARD_USDHC1_DATA1_IOPAD, usdhc_data_pin_settings);
                IOPAD_Set(BOARD_USDHC1_DATA2_IOPAD, usdhc_data_pin_settings);
                IOPAD_Set(BOARD_USDHC1_DATA3_IOPAD, usdhc_data_pin_settings);
            case kMMC_DataBusWidth1bit:
            default:
                IOPAD_Set(BOARD_USDHC1_CMD_IOPAD, usdhc_cmd_pin_settings);
                IOPAD_Set(BOARD_USDHC1_CLK_IOPAD, usdhc_clk_pin_settings);
                IOPAD_Set(BOARD_USDHC1_DATA0_IOPAD, usdhc_data_pin_settings);
        }
    }
}

#if BL_FEATURE_MASTER_BOOT
bool is_mmc_fast_boot_enabled(void)
{
    return OTP_SDHC_FAST_MODE_EN_VALUE();
}

status_t get_mmc_configuration(mmc_card_t *card)
{
    status_t status = kStatus_Fail;

    boot_device_info_t boot_device_info = get_boot_device();
    // Must be master boot mode. And MMC must be the primary boot device or recovery boot device.
    if ((boot_device_info.periphMask & kPeripheralType_MMC) ||
        (boot_device_info.recoveryPeriphMask & kPeripheralType_MMC))
    {
        uint32_t instance;
        if (boot_device_info.periphMask == kPeripheralType_MMC) // mmc is primary boot device.
        {
            instance = boot_device_info.instance;
        }
        else // mmc is recovery boot device.
        {
            instance = boot_device_info.recoveryBootDeviceInstance;
        }

        debug_printf("Bootloader: %s, instance %x is selected.", __func__, instance);
        if (!instance) // Only two instances
        {
            card->host.base = BOARD_USDHC0_BASEADDR;
            card->host.sourceClock_Hz = BOARD_USDHC0_CLK_FREQ;
            card->userConfig.powerPolarity = OTP_SDHC0_PWR_POL_VALUE();
            card->userConfig.switch1V8 = OTP_SDHC0_CARD_VOLTAGE_VALUE();
        }
        else
        {
            card->host.base = BOARD_USDHC1_BASEADDR;
            card->host.sourceClock_Hz = BOARD_USDHC1_CLK_FREQ;
            card->userConfig.powerPolarity = OTP_SDHC1_PWR_POL_VALUE();
            card->userConfig.switch1V8 = OTP_SDHC1_CARD_VOLTAGE_VALUE();
        }

        debug_printf("Bootloader: %s, power cycle is %s", __func__,
                     OTP_SDHC_PWR_CYCLE_EN_VALUE() ? "enabled" : "disabled");
        card->userConfig.enablePowerCycle = OTP_SDHC_PWR_CYCLE_EN_VALUE();

        debug_printf("Bootloader: %s, ack is %s", __func__, OTP_SDHC_FASTBOOT_ACK_EN_VALUE() ? "enabled" : "disabled");
        card->userConfig.enableAck = OTP_SDHC_FASTBOOT_ACK_EN_VALUE();

        debug_printf("Bootloader: %s, Reset Pre-Idle is %s", __func__,
                     OTP_SDHC_RESET_PRE_IDLE_VALUE() ? "disabled" : "enabled");
        card->userConfig.noPreIdle = OTP_SDHC_RESET_PRE_IDLE_VALUE();

        debug_printf("Bootloader: %s, speed %x is selected.", __func__, OTP_SDHC_SPEED_VALUE());
        switch (OTP_SDHC_SPEED_VALUE())
        {
            case 0:
                card->userConfig.timing = kMMC_HighSpeedTimingNone;
                break;
            default: /* For fuse value 2, 3, select high speed timing. */
            case 1:
                card->userConfig.timing = kMMC_HighSpeedTiming;
                break;
        }

        debug_printf("Bootloader: %s, bus width %x is selected.", __func__, OTP_SDHC_BUS_WIDTH_VALUE());
        switch (OTP_SDHC_BUS_WIDTH_VALUE())
        {
            default:
            case 0:
                card->userConfig.busWidth = kMMC_DataBusWidth4bit;
                break;
            case 1:
                card->userConfig.busWidth = kMMC_DataBusWidth8bit;
                break;
            case 2:
                card->userConfig.busWidth = kMMC_DataBusWidth4bitDDR;
                break;
            case 3:
                card->userConfig.busWidth = kMMC_DataBusWidth8bitDDR;
                break;
        }

        switch (OTP_SDHC_PWR_CYCLE_WAIT_VALUE())
        {
            default:
            case kSDMMC_PWR_DOWN_20MS:
#if defined(BL_TARGET_RTL)
                card->userConfig.powerDownDelay_US = 20; // To speed up the RTL simulation.
#else
                card->userConfig.powerDownDelay_US = 20 * 1000;
#endif
                break;
            case kSDMMC_PWR_DOWN_10MS:
                card->userConfig.powerDownDelay_US = 10 * 1000;
                break;
            case kSDMMC_PWR_DOWN_5MS:
                card->userConfig.powerDownDelay_US = 5 * 1000;
                break;
            case kSDMMC_PWR_DOWN_2D5MS:
                card->userConfig.powerDownDelay_US = 25 * 100;
                break;
        }

        switch (OTP_SDHC_PWR_STABLE_WAIT_VALUE())
        {
            default:
            case kSDMMC_PWR_UP_5MS:
#if defined(BL_TARGET_RTL)
                card->userConfig.powerUpDelay_US = 5; // To speed up the RTL simulation.
#else
                card->userConfig.powerUpDelay_US = 5 * 1000;
#endif
                break;
            case kSDMMC_PWR_UP_2D5MS:
                card->userConfig.powerUpDelay_US = 25 * 100;
                break;
        }

        if (OTP_SDHC_PAD_CONTROL_OVERRIDE_VALUE() != 0)
        {
            // set this highspeed pad comp timeout to 100
            int32_t timeout = HS_PAD_COMP_TMO;
            while (((SYSCTL0->SDIOPADCTL & SYSCTL0_SDIOPADCTL_COMPOK_MASK) == 0) || (timeout-- > 0))
            {
            }

            if (OTP_SDHC_PAD_CTL_FREEZE_VALUE() != 0)
            {
                SYSCTL0->SDIOPADCTL |= (1 << 9);
            }
            else if (OTP_SDHC_PAD_CTL_FAST_FREEZE_VALUE() != 0)
            {
                SYSCTL0->SDIOPADCTL |= (1 << 8);
            }
        }

        status = kStatus_Success;
    }
    // else
    // return kStatus_Fail;

    return status;
}
#endif // #if BL_FEATURE_MASTER_BOOT

status_t get_mmc_default_configuration(mmc_card_t *card)
{
    // Used by memory interface. For LPCNext0, always failed.
    status_t status = kStatus_Fail;
    return status;
}
#endif // #if BL_FEATURE_MMC_MODULE

#if BL_FEATURE_SD_MODULE
void sd_pinmux_config(USDHC_Type *base, sd_data_bus_width_t busWidth)
{
    if (base == BOARD_USDHC0_BASEADDR)
    {
        switch (busWidth)
        {
            case kSD_DataBusWidth4Bit:
                IOPAD_Set(BOARD_USDHC0_DATA1_IOPAD, usdhc_data_pin_settings);
                IOPAD_Set(BOARD_USDHC0_DATA2_IOPAD, usdhc_data_pin_settings);
                IOPAD_Set(BOARD_USDHC0_DATA3_IOPAD, usdhc_data_pin_settings);
            case kSD_DataBusWidth1Bit:
            default:
                IOPAD_Set(BOARD_USDHC0_CMD_IOPAD, usdhc_cmd_pin_settings);
                IOPAD_Set(BOARD_USDHC0_CLK_IOPAD, usdhc_clk_pin_settings);
                IOPAD_Set(BOARD_USDHC0_DATA0_IOPAD, usdhc_data_pin_settings);
        }
    }
    else if (base == BOARD_USDHC1_BASEADDR)
    {
        switch (busWidth)
        {
            case kSD_DataBusWidth4Bit:
                IOPAD_Set(BOARD_USDHC1_DATA1_IOPAD, usdhc_data_pin_settings);
                IOPAD_Set(BOARD_USDHC1_DATA2_IOPAD, usdhc_data_pin_settings);
                IOPAD_Set(BOARD_USDHC1_DATA3_IOPAD, usdhc_data_pin_settings);
            case kSD_DataBusWidth1Bit:
            default:
                IOPAD_Set(BOARD_USDHC1_CMD_IOPAD, usdhc_cmd_pin_settings);
                IOPAD_Set(BOARD_USDHC1_CLK_IOPAD, usdhc_clk_pin_settings);
                IOPAD_Set(BOARD_USDHC1_DATA0_IOPAD, usdhc_data_pin_settings);
        }
    }
}

#if BL_FEATURE_MASTER_BOOT
status_t get_sd_configuration(sd_card_t *card)
{
    status_t status = kStatus_Fail;

    boot_device_info_t boot_device_info = get_boot_device();
    // SD must be the primary boot device or recovery boot device.
    if ((boot_device_info.periphMask == kPeripheralType_SD) ||
        (boot_device_info.recoveryPeriphMask == kPeripheralType_SD))
    {
        uint32_t instance;
        if (boot_device_info.periphMask == kPeripheralType_SD) // sd is primary boot device.
        {
            instance = boot_device_info.instance;
        }
        else // sd is recovery boot device.
        {
            instance = boot_device_info.recoveryBootDeviceInstance;
        }

        debug_printf("Bootloader: %s, instance %x is selected.", __func__, instance);
        if (!instance) // Only two instances
        {
            card->host.base = BOARD_USDHC0_BASEADDR;
            card->host.sourceClock_Hz = BOARD_USDHC0_CLK_FREQ;
            card->userConfig.powerPolarity = OTP_SDHC0_PWR_POL_VALUE();
        }
        else
        {
            card->host.base = BOARD_USDHC1_BASEADDR;
            card->host.sourceClock_Hz = BOARD_USDHC1_CLK_FREQ;
            card->userConfig.powerPolarity = OTP_SDHC1_PWR_POL_VALUE();
        }

        card->userConfig.enablePowerCycle = OTP_SDHC_PWR_CYCLE_EN_VALUE();

        debug_printf("Bootloader: %s, speed %x is selected.", __func__, OTP_SDHC_SPEED_VALUE());
        card->userConfig.timing = (sd_timing_mode_t)OTP_SDHC_SPEED_VALUE();

        debug_printf("Bootloader: %s, bus width %x is selected.", __func__, OTP_SDHC_BUS_WIDTH_VALUE());
        switch (OTP_SDHC_BUS_WIDTH_VALUE())
        {
            case 0:
                card->userConfig.busWidth = kSD_DataBusWidth1Bit;
                break;
            default: /* For fuse value 2, 3, select the max width(4 bit)*/
            case 1:
                card->userConfig.busWidth = kSD_DataBusWidth4Bit;
                break;
        }

        switch (OTP_SDHC_PWR_CYCLE_WAIT_VALUE())
        {
            default:
            case kSDMMC_PWR_DOWN_20MS:
#if defined(BL_TARGET_RTL)
                card->userConfig.powerDownDelay_US = 20; // To speed up the RTL simulation.
#else
                card->userConfig.powerDownDelay_US = 20 * 1000;
#endif
                break;
            case kSDMMC_PWR_DOWN_10MS:
                card->userConfig.powerDownDelay_US = 10 * 1000;
                break;
            case kSDMMC_PWR_DOWN_5MS:
                card->userConfig.powerDownDelay_US = 5 * 1000;
                break;
            case kSDMMC_PWR_DOWN_2D5MS:
                card->userConfig.powerDownDelay_US = 25 * 100;
                break;
        }

        switch (OTP_SDHC_PWR_STABLE_WAIT_VALUE())
        {
            default:
            case kSDMMC_PWR_UP_5MS:
#if defined(BL_TARGET_RTL)
                card->userConfig.powerUpDelay_US = 5; // To speed up the RTL simulation.
#else
                card->userConfig.powerUpDelay_US = 5 * 1000;
#endif
                break;
            case kSDMMC_PWR_UP_2D5MS:
                card->userConfig.powerUpDelay_US = 25 * 100;
                break;
        }

        if (OTP_SDHC_DLL_SETTING_TUNING_OVERRIDE_ENABLE_VALUE())
        {
            card->userConfig.tuningStart = OTP_SDHC_DLL_SETTING_TUNING_START_VALUE();
            card->userConfig.tuningStep = OTP_SDHC_DLL_SETTING_TUNING_STEP_VALUE();
            if (card->userConfig.tuningStep == 0)
            {
                card->userConfig.tuningStep = 1;
            }
        }
        else
        {
            card->userConfig.tuningStart = SDMMCHOST_STANDARD_TUNING_START;
            card->userConfig.tuningStep = SDMMCHOST_TUINIG_STEP;
        }
        debug_printf("Bootloader: %s, tuning start = %x, step = %x.", __func__, card->userConfig.tuningStart,
                     card->userConfig.tuningStep);

        if (OTP_SDHC_PAD_CONTROL_OVERRIDE_VALUE() != 0)
        {
            SYSCTL0->SDIOPADCTL = OTP_SDHC_PAD_CONTROL_OVERRIDE_VALUE();
            debug_printf("Bootloader: %s, SDIOPADCTL = %x.", __func__, SYSCTL0->SDIOPADCTL);
        }

        status = kStatus_Success;
    }
    // else
    // return kStatus_Fail;
    debug_printf("Bootloader: %s, return status = %x.", __func__, status);

    return status;
}
#endif // #if BL_FEATURE_MASTER_BOOT

status_t get_sd_default_configuration(sd_card_t *card)
{
    status_t status = kStatus_Fail;
    return status;
}
#endif // #if BL_FEATURE_SD_MODULE
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
