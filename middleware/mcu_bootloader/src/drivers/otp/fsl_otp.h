/*
 * Copyright 2017-2018 NXP
 *
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FSL_OTP_H__
#define __FSL_OTP_H__

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_common.h"

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief OTP driver version. Version 1.0.0.
 *
 * Current version: 1.0.0
 *
 * Change log:
 * - Version 1.0.0
 *   - initial version
 */
#define FSL_OTP_DRIVER_VERSION (MAKE_VERSION(1, 0, 0))
/*@}*/

/* @brief OTP Status Group */
enum
{
    kStatusGroup_OtpGroup = 0x210,
};

/* @brief OTP Error Status definitions */
enum
{
    kStatus_OTP_InvalidAddress = MAKE_STATUS(kStatusGroup_OtpGroup, 1), /*!< Invalid OTP address */
    kStatus_OTP_ProgramFail = MAKE_STATUS(kStatusGroup_OtpGroup, 2),    /*!< Program Fail */
    kStatus_OTP_CrcFail = MAKE_STATUS(kStatusGroup_OtpGroup, 3),        /*!< CrcCheck Fail */
    kStatus_OTP_Error = MAKE_STATUS(kStatusGroup_OtpGroup, 4),          /*!< Errors happened during OTP operation */
    kStatus_OTP_EccCheckFail = MAKE_STATUS(kStatusGroup_OtpGroup, 5),   /*!< Ecc Check failed during OTP operation */
    kStatus_OTP_Locked = MAKE_STATUS(kStatusGroup_OtpGroup, 6),         /*!< OTP Fuse field has been locked */
    kStatus_OTP_Timeout = MAKE_STATUS(kStatusGroup_OtpGroup, 7),        /*!< OTP operation time out */
    kStatus_OTP_CrcCheckPass = MAKE_STATUS(kStatusGroup_OtpGroup, 8),   /*!< OTP CRC Check Pass */
};

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*
 * @brief Initialize OTP controller
 *
 * This function enables OTP Controller clock.
 *
 * @param src_clk_freq The Frequency of the source clock of OTP controller
 *
 * @return
 *      kStatus_Success
 */
status_t otp_init(uint32_t src_clk_freq);

/*
 * @brief De-Initialize OTP controller
 *
 * This functin disables OTP Controller Clock.
 *
 * @return
 *      kStatus_Success
 */
status_t otp_deinit(void);

/*
 * @brief Read Fuse value from OTP Fuse Block
 *
 * This function read fuse data from OTP Fuse block to specified data buffer.
 *
 * @param addr Fuse address
 * @param data Buffer to hold the data read from OTP Fuse block
 *
 * @return kStatus_Success - Data read from OTP Fuse block successfully
 *         kStatus_InvalidArgument - data pointer is invalid
 *         kStatus_OTP_EccCheckFail - Ecc Check Failed
 *         kStatus_OTP_Error - Other Errors
 */
status_t otp_fuse_read(uint32_t addr, uint32_t *data);

/*
 * @brief Program value to OTP Fuse block
 *
 * This function program data to specified OTP Fuse address.
 *
 * @param addr Fuse address
 * @param data data to be programmed into OTP Fuse block
 * @param lock lock the fuse field or not
 * @return kStatus_Success - Data has been programmed into OTP Fuse block successfully
 *         kStatus_OTP_ProgramFail - Fuse programming failed
 *         kStatus_OTP_Locked - The address to be programmed into is locked
 *         kStatus_OTP_Error - Other Errors
 */
status_t otp_fuse_program(uint32_t addr, uint32_t data, bool lock);

/*
 * @brief Reload all shadow registers from OTP fuse block
 *
 * This function reloads all the shadow registers from OTP Fuse block
 *
 * @return kStatus_Success - Shadow registers' reloadding succeeded.
 *         kStatus_OTP_EccCheckFail - Ecc Check Failed
 *         kStatus_OTP_Error - Other Errors
 */
status_t otp_shadow_register_reload(void);

/*
 * @brief Do CRC Check via OTP controller
 *
 * This function checks whether data in specified fuse address ranges match the crc value in the specified CRC address
 *  and return the actual crc value as needed.
 *
 * @param start_addr Start address of selected Fuse address range
 * @param end_addr   End address of selected Fuse address range
 * @param crc_addr   Address that hold CRC data
 *
 * @return kStatus_Success CRC check succeeded, CRC value matched.
 *         kStatus_InvalidArgument - Invalid Argument
 *         kStatus_OTP_EccCheckFail Ecc Check Failed
 *         kStatus_OTP_CrcFail CRC Check Failed
 */
status_t otp_crc_check(uint32_t start_addr, uint32_t end_addr, uint32_t crc_addr);

/*
 * @brief Calculate the CRC checksum for specified data for OTP
 *
 * This function calculates the CRC checksum for specified data for OTP
 *
 * @param src the source address of data
 * @param numberOfWords number of Fuse words
 * @param crcChecksum   Buffer to store the CRC checksum
 *
 * @return kStatus_Success CRC checksum is computed successfully.
 *         kStatus_InvalidArgument - Invalid Argument
 */
status_t otp_crc_calc(uint32_t *src, uint32_t numberOfWords, uint32_t *crcChecksum);

#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */

#endif // __FSL_OTP_H__
