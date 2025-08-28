/*
 * Copyright 2017-2018 NXP
 *
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_otp.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
enum
{
    kOtpMaxSupportedFreq = 120000000u, // Max supported Freq is 120MHz
};

/*******************************************************************************
* Prototypes
************ ******************************************************************/
/* @brief Wait until OTP controller is idle */
static status_t otp_wait_busy(void);

/* @brief Clear all error status */
static void otp_clear_status(void);

/*******************************************************************************
 * Code
 ******************************************************************************/
static status_t otp_wait_busy(void)
{
    /*
     * Assume core clock is 300MHz, the general fuse operation should not exceed 100ms
     * Maximum allowed ticks is 300MHz / 10
     * The below loop needs at least 4 CPU cycles, so the timeout rounds for below loop is 300MHz / 10 / 4
     *
     */
    uint32_t timeout = 300u * 1000u * 1000u / 10u / 4u;
    while ((OCOTP->OTP_STATUS & OCOTP_OTP_STATUS_BUSY_MASK) && timeout)
    {
        timeout--;
    }

    status_t status;
    if (timeout < 1u)
    {
        status = kStatus_OTP_Timeout;
    }
    else
    {
        status = kStatus_Success;
    }

    return status;
}

static void otp_clear_status(void)
{
    // Write 1s to clear all error status
    OCOTP->OTP_STATUS = (OCOTP_OTP_STATUS_PROGFAIL_MASK | OCOTP_OTP_STATUS_ERROR_MASK | OCOTP_OTP_STATUS_CRC_FAIL_MASK |
                         OCOTP_OTP_STATUS_SEC_RELOAD_MASK | OCOTP_OTP_STATUS_DED_RELOAD_MASK |
                         OCOTP_OTP_STATUS_LOCKED_MASK | OCOTP_OTP_STATUS_SEC_MASK | OCOTP_OTP_STATUS_DED_MASK);
}

/* See fsl_otp.h for more details */
status_t otp_init(uint32_t src_clk_freq)
{
    // Enable Clock
    CLKCTL0->PSCCTL0_SET = CLKCTL0_PSCCTL0_OTP_CLK_MASK;
    // Clear Powerdown bit
    OCOTP->OTP_PDN &= (uint32_t)~OCOTP_OTP_PDN_PDN_MASK;

    // Check and set the OTP clock divider as needed.
    uint32_t otp_clk_divider = 1 + (src_clk_freq / kOtpMaxSupportedFreq);
    if (otp_clk_divider > 1)
    {
        OCOTP->OTP_CLK_DIV =
            OCOTP_OTP_CLK_DIV_DIV(otp_clk_divider - 1) | OCOTP_OTP_CLK_DIV_HALT(1) | OCOTP_OTP_CLK_DIV_REQFLAG(1);
        while (OCOTP->OTP_CLK_DIV & OCOTP_OTP_CLK_DIV_REQFLAG_MASK)
        {
        }
        OCOTP->OTP_CLK_DIV &= (uint32_t)~OCOTP_OTP_CLK_DIV_HALT_MASK;
    }

    return kStatus_Success;
}

/* See fsl_otp.h for more details */
status_t otp_deinit(void)
{
    // Enable Powerdown bit
    OCOTP->OTP_PDN = OCOTP_OTP_PDN_PDN_MASK;

    /* Note: Keep OTP clock in case the access to shadow registers is still needed. */

    return kStatus_Success;
}

/* See fsl_otp.h for more details */
status_t otp_fuse_read(uint32_t addr, uint32_t *data)
{
    status_t status = kStatus_InvalidArgument;

    do
    {
        if (data == NULL)
        {
            break;
        }

        status = otp_wait_busy();
        if (status != kStatus_Success)
        {
            break;
        }

        otp_clear_status();

        // Start reading
        OCOTP->OTP_CTRL = OCOTP_OTP_CTRL_ADDR(addr);
        OCOTP->OTP_READ_CTRL = OCOTP_OTP_READ_CTRL_READ(1);

        // Wait until read completes
        status = otp_wait_busy();
        if (status != kStatus_Success)
        {
            break;
        }

        // Check whether errors happened or not.
        uint32_t otp_status = OCOTP->OTP_STATUS;
        if (otp_status & (OCOTP_OTP_STATUS_ERROR_MASK | OCOTP_OTP_STATUS_DED_MASK))
        {
            if (otp_status & OCOTP_OTP_STATUS_DED_MASK)
            {
                status = kStatus_OTP_EccCheckFail;
            }
            else
            {
                status = kStatus_OTP_Error;
            }
            break;
        }

        status = kStatus_Success;
        *data = OCOTP->OTP_READ_DATA;

    } while (0);

    return status;
}

/* See fsl_otp.h for more details */
status_t otp_shadow_register_reload(void)
{
    status_t status;

    do
    {
        status = otp_wait_busy();
        if (status != kStatus_Success)
        {
            break;
        }

        otp_clear_status();

        // Start reloading all shadow registers
        OCOTP->OTP_CTRL = OCOTP_OTP_CTRL_RELOAD_SHADOWS_MASK;

        // Wait until reloading operation completes
        status = otp_wait_busy();
        if (status != kStatus_Success)
        {
            break;
        }

        // Check whether errors happened or not.
        uint32_t otp_status = OCOTP->OTP_STATUS;
        if (otp_status & (OCOTP_OTP_STATUS_ERROR_MASK | OCOTP_OTP_STATUS_DED_MASK))
        {
            if (otp_status & OCOTP_OTP_STATUS_DED_MASK)
            {
                status = kStatus_OTP_EccCheckFail;
            }
            else
            {
                status = kStatus_OTP_Error;
            }
        }
        else
        {
            status = kStatus_Success;
        }

    } while (0);

    return status;
}

/* See fsl_otp.h for more details */
status_t otp_crc_check(uint32_t start_addr, uint32_t end_addr, uint32_t crc_addr)
{
    status_t status = kStatus_InvalidArgument;

    do
    {
        if ((start_addr > end_addr) || (start_addr == crc_addr) || (end_addr == crc_addr))
        {
            break;
        }

        status = otp_wait_busy();
        if (status != kStatus_Success)
        {
            break;
        }

        otp_clear_status();

        // Start CRC checking
        OCOTP->OTP_CRC_ADDR = OCOTP_OTP_CRC_ADDR_CRC_START_ADDR(start_addr) |
                              OCOTP_OTP_CRC_ADDR_CRC_END_ADDR(end_addr) | OCOTP_OTP_CRC_ADDR_CRC_REF_ADDR(crc_addr);
        OCOTP->OTP_CTRL = OCOTP_OTP_CTRL_CRC_TEST_MASK;

        // Wait until CRC Check completes
        status = otp_wait_busy();
        if (status != kStatus_Success)
        {
            break;
        }

        // Check whether errors happened or not.
        uint32_t otp_status = OCOTP->OTP_STATUS;
        if (otp_status & (OCOTP_OTP_STATUS_ERROR_MASK | OCOTP_OTP_STATUS_DED_MASK | OCOTP_OTP_STATUS_CRC_FAIL_MASK))
        {
            if (otp_status & OCOTP_OTP_STATUS_DED_MASK)
            {
                status = kStatus_OTP_EccCheckFail;
            }
            else if (otp_status & OCOTP_OTP_STATUS_CRC_FAIL_MASK)
            {
                status = kStatus_OTP_CrcFail;
            }
            else
            {
                status = kStatus_OTP_Error;
            }
        }
        else
        {
            status = kStatus_OTP_CrcCheckPass;
        }

    } while (0);

    return status;
}

