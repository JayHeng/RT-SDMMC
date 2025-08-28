/*
 * Copyright 2017-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef __FUSEMAP_H__
#define __FUSEMAP_H__

#include "fsl_device_registers.h"
#include "otp/fsl_otp.h"

#define OTP_PTE_VALID_CONFIG_FUSE_IDX (39)


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                    //
//                                                                                                                    //
//                                  Common boot cfg fuse definitions                                                  //
//                                                                                                                    //
//                                                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// BOOT SPEED
#define OTP_BOOTSPEED_FUSE_IDX (0x60)
#define OTP_BOOTSPEED_SHIFT (7u)
#define OTP_BOOTSPEED_MASK (1u << OTP_BOOTSPEED_SHIFT)
#define OTP_BOOTSPEED_VALUE() ((OCOTP->OTP_SHADOW[OTP_BOOTSPEED_FUSE_IDX] & OTP_BOOTSPEED_MASK) >> OTP_BOOTSPEED_SHIFT)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                    //
//                                                                                                                    //
//                                  eMMC/SD related fuse definitions                                                  //
//                                                                                                                    //
//                                                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SDHC_DEVICE_TYPE
#define OTP_SDHC_DEVICE_TYPE_FUSE_IDX (0x62)
#define OTP_SDHC_DEVICE_TYPE_SHIFT (0u)
#define OTP_SDHC_DEVICE_TYPE_MASK (0x1u << OTP_SDHC_DEVICE_TYPE_SHIFT)
#define OTP_SDHC_DEVICE_TYPE_VALUE() \
    ((OCOTP->OTP_SHADOW[OTP_SDHC_DEVICE_TYPE_FUSE_IDX] & OTP_SDHC_DEVICE_TYPE_MASK) >> OTP_SDHC_DEVICE_TYPE_SHIFT)

// SDHC_BUS_WIDTH
#define OTP_SDHC_BUS_WIDTH_FUSE_IDX (0x62)
#define OTP_SDHC_BUS_WIDTH_SHIFT (1u)
#define OTP_SDHC_BUS_WIDTH_MASK (0x3u << OTP_SDHC_BUS_WIDTH_SHIFT)
#define OTP_SDHC_BUS_WIDTH_VALUE() \
    ((OCOTP->OTP_SHADOW[OTP_SDHC_BUS_WIDTH_FUSE_IDX] & OTP_SDHC_BUS_WIDTH_MASK) >> OTP_SDHC_BUS_WIDTH_SHIFT)

// SDHC_SPEED
#define OTP_SDHC_SPEED_FUSE_IDX (0x62)
#define OTP_SDHC_SPEED_SHIFT (3u)
#define OTP_SDHC_SPEED_MASK (0x3u << OTP_SDHC_SPEED_SHIFT)
#define OTP_SDHC_SPEED_VALUE() \
    ((OCOTP->OTP_SHADOW[OTP_SDHC_SPEED_FUSE_IDX] & OTP_SDHC_SPEED_MASK) >> OTP_SDHC_SPEED_SHIFT)

// SDHC_PWR_CYCLE_EN
#define OTP_SDHC_PWR_CYCLE_EN_FUSE_IDX (0x62)
#define OTP_SDHC_PWR_CYCLE_EN_SHIFT (5u)
#define OTP_SDHC_PWR_CYCLE_EN_MASK (0x1u << OTP_SDHC_PWR_CYCLE_EN_SHIFT)
#define OTP_SDHC_PWR_CYCLE_EN_VALUE() \
    ((OCOTP->OTP_SHADOW[OTP_SDHC_PWR_CYCLE_EN_FUSE_IDX] & OTP_SDHC_PWR_CYCLE_EN_MASK) >> OTP_SDHC_PWR_CYCLE_EN_SHIFT)

// SDHC0_PWR_POL
#define OTP_SDHC0_PWR_POL_FUSE_IDX (0x62)
#define OTP_SDHC0_PWR_POL_SHIFT (6u)
#define OTP_SDHC0_PWR_POL_MASK (0x1u << OTP_SDHC0_PWR_POL_SHIFT)
#define OTP_SDHC0_PWR_POL_VALUE() \
    ((OCOTP->OTP_SHADOW[OTP_SDHC0_PWR_POL_FUSE_IDX] & OTP_SDHC0_PWR_POL_MASK) >> OTP_SDHC0_PWR_POL_SHIFT)

// SDHC1_PWR_POL
#define OTP_SDHC1_PWR_POL_FUSE_IDX (0x62)
#define OTP_SDHC1_PWR_POL_SHIFT (7u)
#define OTP_SDHC1_PWR_POL_MASK (0x1u << OTP_SDHC1_PWR_POL_SHIFT)
#define OTP_SDHC1_PWR_POL_VALUE() \
    ((OCOTP->OTP_SHADOW[OTP_SDHC1_PWR_POL_FUSE_IDX] & OTP_SDHC1_PWR_POL_MASK) >> OTP_SDHC1_PWR_POL_SHIFT)

// SDHC_PWR_CYCLE_WAIT
#define OTP_SDHC_PWR_CYCLE_WAIT_FUSE_IDX (0x62)
#define OTP_SDHC_PWR_CYCLE_WAIT_SHIFT (8u)
#define OTP_SDHC_PWR_CYCLE_WAIT_MASK (0x3u << OTP_SDHC_PWR_CYCLE_WAIT_SHIFT)
#define OTP_SDHC_PWR_CYCLE_WAIT_VALUE()                                                      \
    ((OCOTP->OTP_SHADOW[OTP_SDHC_PWR_CYCLE_WAIT_FUSE_IDX] & OTP_SDHC_PWR_CYCLE_WAIT_MASK) >> \
     OTP_SDHC_PWR_CYCLE_WAIT_SHIFT)

// SDHC_PWR_STABLE_WAIT
#define OTP_SDHC_PWR_STABLE_WAIT_FUSE_IDX (0x62)
#define OTP_SDHC_PWR_STABLE_WAIT_SHIFT (10u)
#define OTP_SDHC_PWR_STABLE_WAIT_MASK (0x1u << OTP_SDHC_PWR_STABLE_WAIT_SHIFT)
#define OTP_SDHC_PWR_STABLE_WAIT_VALUE()                                                       \
    ((OCOTP->OTP_SHADOW[OTP_SDHC_PWR_STABLE_WAIT_FUSE_IDX] & OTP_SDHC_PWR_STABLE_WAIT_MASK) >> \
     OTP_SDHC_PWR_STABLE_WAIT_SHIFT)

// SDHC0_CARD_VOLTAGE
#define OTP_SDHC0_CARD_VOLTAGE_FUSE_IDX (0x62)
#define OTP_SDHC0_CARD_VOLTAGE_SHIFT (11u)
#define OTP_SDHC0_CARD_VOLTAGE_MASK (1u << OTP_SDHC0_CARD_VOLTAGE_SHIFT)
#define OTP_SDHC0_CARD_VOLTAGE_VALUE() \
    ((OCOTP->OTP_SHADOW[OTP_SDHC0_CARD_VOLTAGE_FUSE_IDX] & OTP_SDHC0_CARD_VOLTAGE_MASK) >> OTP_SDHC0_CARD_VOLTAGE_SHIFT)

// SDHC1_CARD_VOLTAGE
#define OTP_SDHC1_CARD_VOLTAGE_FUSE_IDX (0x62)
#define OTP_SDHC1_CARD_VOLTAGE_SHIFT (12u)
#define OTP_SDHC1_CARD_VOLTAGE_MASK (1u << OTP_SDHC1_CARD_VOLTAGE_SHIFT)
#define OTP_SDHC1_CARD_VOLTAGE_VALUE() \
    ((OCOTP->OTP_SHADOW[OTP_SDHC1_CARD_VOLTAGE_FUSE_IDX] & OTP_SDHC1_CARD_VOLTAGE_MASK) >> OTP_SDHC1_CARD_VOLTAGE_SHIFT)

// SDHC_CARD_RESET_PRE_IDLE
#define OTP_SDHC_RESET_PRE_IDLE_FUSE_IDX (0x62)
#define OTP_SDHC_RESET_PRE_IDLE_SHIFT (13u)
#define OTP_SDHC_RESET_PRE_IDLE_MASK (1u << OTP_SDHC_RESET_PRE_IDLE_SHIFT)
#define OTP_SDHC_RESET_PRE_IDLE_VALUE()                                                      \
    ((OCOTP->OTP_SHADOW[OTP_SDHC_RESET_PRE_IDLE_FUSE_IDX] & OTP_SDHC_RESET_PRE_IDLE_MASK) >> \
     OTP_SDHC_RESET_PRE_IDLE_SHIFT)

// SDHC_FAST_MODE_EN
#define OTP_SDHC_FAST_MODE_EN_FUSE_IDX (0x62)
#define OTP_SDHC_FAST_MODE_EN_SHIFT (14u)
#define OTP_SDHC_FAST_MODE_EN_MASK (1u << OTP_SDHC_FAST_MODE_EN_SHIFT)
#define OTP_SDHC_FAST_MODE_EN_VALUE() \
    ((OCOTP->OTP_SHADOW[OTP_SDHC_FAST_MODE_EN_FUSE_IDX] & OTP_SDHC_FAST_MODE_EN_MASK) >> OTP_SDHC_FAST_MODE_EN_SHIFT)

// SDHC_FASTBOOT_ACK_EN
#define OTP_SDHC_FASTBOOT_ACK_EN_FUSE_IDX (0x62)
#define OTP_SDHC_FASTBOOT_ACK_EN_SHIFT (15u)
#define OTP_SDHC_FASTBOOT_ACK_EN_MASK (1u << OTP_SDHC_FASTBOOT_ACK_EN_SHIFT)
#define OTP_SDHC_FASTBOOT_ACK_EN_VALUE()                                                       \
    ((OCOTP->OTP_SHADOW[OTP_SDHC_FASTBOOT_ACK_EN_FUSE_IDX] & OTP_SDHC_FASTBOOT_ACK_EN_MASK) >> \
     OTP_SDHC_FASTBOOT_ACK_EN_SHIFT)

// SDHC_PAD_CTL_FREEZE
#define OTP_SDHC_PAD_CTL_FREEZE_FUSE_IDX (0x62)
#define OTP_SDHC_PAD_CTL_FREEZE_SHIFT (16u)
#define OTP_SDHC_PAD_CTL_FREEZE_MASK (0x1u << OTP_SDHC_PAD_CTL_FREEZE_SHIFT)
#define OTP_SDHC_PAD_CTL_FREEZE_VALUE()                                                      \
    ((OCOTP->OTP_SHADOW[OTP_SDHC_PAD_CTL_FREEZE_FUSE_IDX] & OTP_SDHC_PAD_CTL_FREEZE_MASK) >> \
     OTP_SDHC_PAD_CTL_FREEZE_SHIFT)

// SDHC_PAD_CTL_FAST_FREEZE
#define OTP_SDHC_PAD_CTL_FAST_FREEZE_FUSE_IDX (0x62)
#define OTP_SDHC_PAD_CTL_FAST_FREEZE_SHIFT (17u)
#define OTP_SDHC_PAD_CTL_FAST_FREEZE_MASK (0x1u << OTP_SDHC_PAD_CTL_FAST_FREEZE_SHIFT)
#define OTP_SDHC_PAD_CTL_FAST_FREEZE_VALUE()                                                           \
    ((OCOTP->OTP_SHADOW[OTP_SDHC_PAD_CTL_FAST_FREEZE_FUSE_IDX] & OTP_SDHC_PAD_CTL_FAST_FREEZE_MASK) >> \
     OTP_SDHC_PAD_CTL_FAST_FREEZE_SHIFT)

#define OTP_SDHC_PAD_CONTROL_OVERRIDE_VALUE() \
    ((OTP_SDHC_PAD_CTL_FREEZE_VALUE()) | (OTP_SDHC_PAD_CTL_FAST_FREEZE_VALUE() << 1u))

// SDHC_PAD_SETTING_OVERRIDE
#define OTP_SDHC_PAD_SETTING_OVERRIDE_FUSE_IDX (0x62)
#define OTP_SDHC_PAD_SETTING_OVERRIDE_SHIFT (28u)
#define OTP_SDHC_PAD_SETTING_OVERRIDE_MASK (0xfu << OTP_SDHC_PAD_SETTING_OVERRIDE_SHIFT)
#define OTP_SDHC_PAD_SETTING_OVERRIDE_VALUE()                                                            \
    ((OCOTP->OTP_SHADOW[OTP_SDHC_PAD_SETTING_OVERRIDE_FUSE_IDX] & OTP_SDHC_PAD_SETTING_OVERRIDE_MASK) >> \
     OTP_SDHC_PAD_SETTING_OVERRIDE_SHIFT)

// SDHC_DLL_SETTING_TUNING_OVERRIDE_ENABLE
#define OTP_SDHC_DLL_SETTING_TUNING_OVERRIDE_ENABLE_FUSE_IDX (0x63)
#define OTP_SDHC_DLL_SETTING_TUNING_OVERRIDE_ENABLE_SHIFT (7u)
#define OTP_SDHC_DLL_SETTING_TUNING_OVERRIDE_ENABLE_MASK (0x1u << OTP_SDHC_DLL_SETTING_TUNING_OVERRIDE_ENABLE_SHIFT)
#define OTP_SDHC_DLL_SETTING_TUNING_OVERRIDE_ENABLE_VALUE()                     \
    ((OCOTP->OTP_SHADOW[OTP_SDHC_DLL_SETTING_TUNING_OVERRIDE_ENABLE_FUSE_IDX] & \
      OTP_SDHC_DLL_SETTING_TUNING_OVERRIDE_ENABLE_MASK) >>                      \
     OTP_SDHC_DLL_SETTING_TUNING_OVERRIDE_ENABLE_SHIFT)

// SDHC_DLL_SETTING_TUNING_START
#define OTP_SDHC_DLL_SETTING_TUNING_START_FUSE_IDX (0x63)
#define OTP_SDHC_DLL_SETTING_TUNING_START_SHIFT (8u)
#define OTP_SDHC_DLL_SETTING_TUNING_START_MASK (0xffu << OTP_SDHC_DLL_SETTING_TUNING_START_SHIFT)
#define OTP_SDHC_DLL_SETTING_TUNING_START_VALUE()                                                                \
    ((OCOTP->OTP_SHADOW[OTP_SDHC_DLL_SETTING_TUNING_START_FUSE_IDX] & OTP_SDHC_DLL_SETTING_TUNING_START_MASK) >> \
     OTP_SDHC_DLL_SETTING_TUNING_START_SHIFT)

// SDHC_DLL_SETTING_TUNING_STEP
#define OTP_SDHC_DLL_SETTING_TUNING_STEP_FUSE_IDX (0x63)
#define OTP_SDHC_DLL_SETTING_TUNING_STEP_SHIFT (16u)
#define OTP_SDHC_DLL_SETTING_TUNING_STEP_MASK (0x7u << OTP_SDHC_DLL_SETTING_TUNING_STEP_SHIFT)
#define OTP_SDHC_DLL_SETTING_TUNING_STEP_VALUE()                                                               \
    ((OCOTP->OTP_SHADOW[OTP_SDHC_DLL_SETTING_TUNING_STEP_FUSE_IDX] & OTP_SDHC_DLL_SETTING_TUNING_STEP_MASK) >> \
     OTP_SDHC_DLL_SETTING_TUNING_STEP_SHIFT)

#endif // __FUSEMAP_H__
