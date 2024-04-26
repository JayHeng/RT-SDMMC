/*
 * Copyright 2017-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if !defined(__SDMMC_INIT_H__)
#define __SDMMC_INIT_H__

#include "fsl_gpio.h"
#include "fsl_iomuxc.h"
#if FSL_FEATURE_SOC_PORT_COUNT
#include "fsl_port.h"
#endif
#include "bootloader_common.h"
#include "fsl_sdmmc_common.h"
#include "fsl_sdmmc_host.h"
#include "fsl_sdmmc_spec.h"

/******************************************************************************
 * Definitions.
 *****************************************************************************/
enum
{
    kSDMMC_PWR_DOWN_20MS = 0,
    kSDMMC_PWR_DOWN_10MS = 1,
    kSDMMC_PWR_DOWN_5MS = 2,
    kSDMMC_PWR_DOWN_2D5MS = 3,

    kSDMMC_PWR_UP_5MS = 0,
    kSDMMC_PWR_UP_2D5MS = 1,
};

////////////////////////////////////////////////////////////////////////////////
// Basic Definitions
////////////////////////////////////////////////////////////////////////////////
/*! @brief USDHC base address. */
#define BOARD_USDHC1_BASEADDR USDHC1
#define BOARD_USDHC2_BASEADDR USDHC2
/*! @brief USDHC frequency. */
#define BOARD_USDHC1_CLK_FREQ (CLOCK_GetFreq(kCLOCK_SysPllPfd0Clk) / (CLOCK_GetDiv(kCLOCK_Usdhc1Div) + 1U))
#define BOARD_USDHC2_CLK_FREQ (CLOCK_GetFreq(kCLOCK_SysPllPfd0Clk) / (CLOCK_GetDiv(kCLOCK_Usdhc2Div) + 1U))
/*! @brief USDHC pin port. */
#define BOARD_USDHC1_CD_GPIO_BASE (GPIO2)
#define BOARD_USDHC1_CD_GPIO_PIN (28)
#define BOARD_USDHC1_CD_GPIO_IOMUXC IOMUXC_GPIO_B1_12_GPIO2_IO28
#define BOARD_USDHC1_CMD_IOMUXC IOMUXC_GPIO_SD_B0_00_USDHC1_CMD
#define BOARD_USDHC1_CLK_IOMUXC IOMUXC_GPIO_SD_B0_01_USDHC1_CLK
#define BOARD_USDHC1_DATA0_IOMUXC IOMUXC_GPIO_SD_B0_02_USDHC1_DATA0
#define BOARD_USDHC1_DATA1_IOMUXC IOMUXC_GPIO_SD_B0_03_USDHC1_DATA1
#define BOARD_USDHC1_DATA2_IOMUXC IOMUXC_GPIO_SD_B0_04_USDHC1_DATA2
#define BOARD_USDHC1_DATA3_IOMUXC IOMUXC_GPIO_SD_B0_05_USDHC1_DATA3
#define BOARD_USDHC1_VSELECT_IOMUXC IOMUXC_GPIO_B1_14_USDHC1_VSELECT
#define BOARD_USDHC1_RESET_B_GPIO_BASE (GPIO2)
#define BOARD_USDHC1_RESET_B_GPIO_PIN (31)
#define BOARD_USDHC1_RESET_B_GPIO_IOMUXC IOMUXC_GPIO_B1_15_GPIO2_IO31

#define BOARD_USDHC2_CD_GPIO_BASE (GPIO3)
#define BOARD_USDHC2_CD_GPIO_PIN (25)
#define BOARD_USDHC2_CD_GPIO_IOMUXC IOMUXC_GPIO_EMC_39_GPIO3_IO25
#define BOARD_USDHC2_CMD_IOMUXC IOMUXC_GPIO_SD_B1_05_USDHC2_CMD
#define BOARD_USDHC2_CLK_IOMUXC IOMUXC_GPIO_SD_B1_04_USDHC2_CLK
#define BOARD_USDHC2_DATA0_IOMUXC IOMUXC_GPIO_SD_B1_03_USDHC2_DATA0
#define BOARD_USDHC2_DATA1_IOMUXC IOMUXC_GPIO_SD_B1_02_USDHC2_DATA1
#define BOARD_USDHC2_DATA2_IOMUXC IOMUXC_GPIO_SD_B1_01_USDHC2_DATA2
#define BOARD_USDHC2_DATA3_IOMUXC IOMUXC_GPIO_SD_B1_00_USDHC2_DATA3
#define BOARD_USDHC2_DATA4_IOMUXC IOMUXC_GPIO_SD_B1_08_USDHC2_DATA4
#define BOARD_USDHC2_DATA5_IOMUXC IOMUXC_GPIO_SD_B1_09_USDHC2_DATA5
#define BOARD_USDHC2_DATA6_IOMUXC IOMUXC_GPIO_SD_B1_10_USDHC2_DATA6
#define BOARD_USDHC2_DATA7_IOMUXC IOMUXC_GPIO_SD_B1_11_USDHC2_DATA7
#define BOARD_USDHC2_VSELECT_IOMUXC IOMUXC_GPIO_EMC_38_USDHC2_VSELECT
#define BOARD_USDHC2_RESET_B_GPIO_BASE (GPIO3)
#define BOARD_USDHC2_RESET_B_GPIO_PIN (6)
#define BOARD_USDHC2_RESET_B_GPIO_IOMUXC IOMUXC_GPIO_SD_B1_06_GPIO3_IO06

#if BL_FEATURE_SD_MODULE && BL_FEATURE_SD_MODULE_HAS_CARD_DETECT
#if defined(BL_FEATURE_SD_MODULE_CARD_DETECT_LEVEL)
#define BOARD_USDHC_CARD_INSERT_CD_LEVEL (BL_FEATURE_SD_MODULE_CARD_DETECT_LEVEL)
#endif
#if defined(BL_FEATURE_SD_MODULE_CARD_DETECT_TIMEOUT)
#define BOARD_TIMEOUT_CARD_DETECT (BL_FEATURE_SD_MODULE_CARD_DETECT_TIMEOUT)
#else
#define BOARD_TIMEOUT_CARD_DETECT 0
#endif
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void usdhc_power_control_init(USDHC_Type *base);
void usdhc_power_control(USDHC_Type *base, bool state);
void usdhc_vselect_init(USDHC_Type *base);

/*! @brief Power control init function. */
#define BOARD_USDHC_POWER_CONTROL_INIT(base) usdhc_power_control_init(base)
/*! @brief Power control enable/disable function. */
#define BOARD_USDHC_POWER_CONTROL(base, state) usdhc_power_control(base, state)
/*! @brief vselect function. */
#define BOARD_USDHC_VSELECT_INIT(base) usdhc_vselect_init(base)
/*! @brief CD pin init function. */
#define BOARD_USDHC_CD_INIT(base, cdType)
/*! @brief Get CD GPIO levle. */
#define BOARD_USDHC_CD_GPIO_STATUS(base) (0)
/*! @brief SD card detection pin config fucntion for KSDK, not really used */
#define BOARD_USDHC_CD_GPIO_INIT()
/*! @brief SD card detection status fucntion for KSDK, not really used */
#define BOARD_USDHC_CD_STATUS() (0)

////////////////////////////////////////////////////////////////////////////////
// Board Definitions
////////////////////////////////////////////////////////////////////////////////

#define BOARD_SD_SUPPORT_180V (BL_FEATURE_SD_MODULE_SUPPORT_1V8)
////////////////////////////////////////////////////////////////////////////////
// Board FUNC Definitions
////////////////////////////////////////////////////////////////////////////////

extern void mmc_pinmux_config(USDHC_Type *base, mmc_data_bus_width_t busWidth);
extern void mmc_io_update(USDHC_Type *base, mmc_data_bus_width_t busWidth, uint32_t speed, uint32_t strength);
extern void sd_pinmux_config(USDHC_Type *base, sd_data_bus_width_t busWidth);
extern void sd_io_update(USDHC_Type *base, sd_data_bus_width_t busWidth, uint32_t speed, uint32_t strength);

#if BL_FEATURE_SD_MODULE

/*! @brief SD power control init function. */
#define BOARD_USDHC_SDCARD_RESET_CONTROL_INIT(base) BOARD_USDHC_POWER_CONTROL_INIT(base)
/*! @brief SD power enable/disable function. */
#define BOARD_USDHC_SDCARD_RESET_CONTROL(base, state) BOARD_USDHC_POWER_CONTROL(base, state)
/*! @brief SD vselect init function. */
#define BOARD_USDHC_SDCARD_VSELECT_INIT(base) BOARD_USDHC_VSELECT_INIT(base)
/*! @brief SD power control init function. */
#define BOARD_USDHC_SDCARD_POWER_CONTROL_INIT()
/*! @brief SD power enable/disable function. */
#define BOARD_USDHC_SDCARD_POWER_CONTROL(state)

#define BOARD_SD_MUX_CONFIG(base, busWidth)  sd_pinmux_config(base, busWidth)

#define BOARD_SD_PIN_CONFIG(speed, strength)

/* define for SD config IO driver strength dynamic */
#define BOARD_SD_IO_UPDATE(base, busWidth, speed, strength) 
#endif

#if BL_FEATURE_MMC_MODULE

/*! @brief MMC power control init function. */
#define BOARD_USDHC_MMCCARD_RESET_CONTROL_INIT(base) BOARD_USDHC_POWER_CONTROL_INIT(base)
/*! @brief MMC power enable/disable function. */
#define BOARD_USDHC_MMCCARD_RESET_CONTROL(base, state) BOARD_USDHC_POWER_CONTROL(base, state)
/*! @brief MMC vselect init function. */
#define BOARD_USDHC_MMCCARD_VSELECT_INIT(base) BOARD_USDHC_VSELECT_INIT(base)
/*! @brief MMC power control init function. */
#define BOARD_USDHC_MMCCARD_POWER_CONTROL_INIT()
/*! @brief MMC power enable/disable function. */
#define BOARD_USDHC_MMCCARD_POWER_CONTROL(state)

#define BOARD_MMC_MUX_CONFIG(base, busWidth) mmc_pinmux_config(base, busWidth)

#define BOARD_MMC_PIN_CONFIG(speed, strength)
/* define for MMC config IO driver strength dynamic */
#define BOARD_MMC_IO_UPDATE(base, busWidth, speed, strength) 
#endif

#endif // __SDMMC_INIT_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
