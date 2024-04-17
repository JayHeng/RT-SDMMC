/*
 * Copyright 2018 NXP
 *
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FUSEMAP_H__
#define __FUSEMAP_H__

#include "fsl_device_registers.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

#define FUSE_BANK0_OFFSET 0x800
#define HW_FUSE_REG_ADDR(n) (OCOTP_BASE + FUSE_BANK0_OFFSET + ((n)*0x10))
#define HW_OCOTP_REG_RD(n) (*(volatile uint32_t *)HW_FUSE_REG_ADDR(n))

/* ======================== Boot Configuration ================================= */
/* SPEED_LIMIT */
#define FUSE_SPEED_LIMIT_SHIFT (2)
#define FUSE_SPEED_LIMIT_MASK (1u << FUSE_SPEED_LIMIT_SHIFT)
#define FUSE_SPEED_LIMIT_VALUE ((HW_OCOTP_REG_RD(0x07) & FUSE_SPEED_LIMIT_MASK) >> FUSE_SPEED_LIMIT_SHIFT)

/* ========================== LP boot ======================================= */
#define FUSE_LPB_BOOT_SHIFT 4
#define FUSE_LPB_BOOT_MASK (0x03 << FUSE_LPB_BOOT_SHIFT)
#define FUSE_LPB_BOOT_VALUE ((HW_OCOTP_REG_RD(0x1a) & FUSE_LPB_BOOT_MASK) >> FUSE_LPB_BOOT_SHIFT)

#define FUSE_BOOT_FREQ_SHIFT 0x03
#define FUSE_BOOT_FREQ_MASK (1u << FUSE_BOOT_FREQ_SHIFT)
#define FUSE_BOOT_FREQ_VALUE ((HW_OCOTP_REG_RD(0x1a) & FUSE_BOOT_FREQ_MASK) >> FUSE_BOOT_FREQ_SHIFT)

/* ========================== Secure/Encrypt boot ======================================= */
/* FIELD_RETURN */
#define FUSE_FIELD_RETURN_SHIFT ((uint8_t)4)
#define FUSE_FIELD_RETURN_MASK (0xFu << FUSE_FIELD_RETURN_SHIFT)
#define FUSE_FIELD_RETURN_VALUE ((HW_OCOTP_REG_RD(0x0D) & FUSE_FIELD_RETURN_MASK) >> FUSE_FIELD_RETURN_SHIFT)

/* SEC Config[0] */
#define FUSE_SEC_CONFIG0_SHIFT ((uint8_t)1)
#define FUSE_SEC_CONFIG0_MASK (1u << FUSE_SEC_CONFIG0_SHIFT)
#define FUSE_SEC_CONFIG0_VALUE ((HW_OCOTP_REG_RD(0x0E) & FUSE_SEC_CONFIG0_MASK) >> FUSE_SEC_CONFIG0_SHIFT)
/* SEC_Config[1] */
#define FUSE_SEC_CONFIG1_SHIFT ((uint8_t)1)
#define FUSE_SEC_CONFIG1_MASK (1u << FUSE_SEC_CONFIG1_SHIFT)
#define FUSE_SEC_CONFIG1_VALUE ((HW_OCOTP_REG_RD(0x16) & FUSE_SEC_CONFIG1_MASK) >> FUSE_SEC_CONFIG1_SHIFT)
#define FUSE_SEC_CONFIG_VALUE (FUSE_SEC_CONFIG0_VALUE | (FUSE_SEC_CONFIG1_VALUE << 1))

/* ========================== MMC/SD boot(Common Part)======================================= */
/* SD/MMC instance 1 reset polarity */
#define FUSE_SD1_RST_ACTIVE_POLARITY_SHIFT ((uint8_t)2)
#define FUSE_SD1_RST_ACTIVE_POLARITY_MASK ((uint32_t)(0x1 << FUSE_SD1_RST_ACTIVE_POLARITY_SHIFT))
#define FUSE_SD1_RST_ACTIVE_POLARITY_VALUE \
    ((HW_OCOTP_REG_RD(0x17) & FUSE_SD1_RST_ACTIVE_POLARITY_MASK) >> FUSE_SD1_RST_ACTIVE_POLARITY_SHIFT)

/* SD/MMC instance 2 reset polarity */
#define FUSE_SD2_RST_ACTIVE_POLARITY_SHIFT ((uint8_t)1)
#define FUSE_SD2_RST_ACTIVE_POLARITY_MASK ((uint32_t)(0x1 << FUSE_SD2_RST_ACTIVE_POLARITY_SHIFT))
#define FUSE_SD2_RST_ACTIVE_POLARITY_VALUE \
    ((HW_OCOTP_REG_RD(0x17) & FUSE_SD2_RST_ACTIVE_POLARITY_MASK) >> FUSE_SD2_RST_ACTIVE_POLARITY_SHIFT)

/* ========================== Misc. Configuration ======================================= */
/* FLEXRAM PART */
#define FUSE_FLEXRAM_CFG_SHIFT ((uint8_t)16)
#define FUSE_FLEXRAM_CFG_MASK (0x3fu << FUSE_FLEXRAM_CFG_SHIFT)
#define FUSE_FLEXRAM_CFG_VALUE ((HW_OCOTP_REG_RD(0x47) & FUSE_FLEXRAM_CFG_MASK) >> FUSE_FLEXRAM_CFG_SHIFT)

#endif /* __FUSEMAP_H__*/
