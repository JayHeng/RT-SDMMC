;/*****************************************************************************
; * @file:    startup_LPC6824.s
; * @purpose: CMSIS Cortex-M33 Core Device Startup File
; *           LPC6824
; * @version: 1.0
; * @date:    2017-7-14
; *----------------------------------------------------------------------------
; *
; Copyright 1997-2016 Freescale Semiconductor, Inc.
; Copyright 2016-2017 NXP
; All rights reserved.
;
; SPDX-License-Identifier: BSD-3-Clause
;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        EXTERN  __stack_chk_guard
        EXTERN  romcp_handler
        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA

__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler

        DCD     DefaultISR
        DCD     HardFault_Handler
        DCD     DefaultISR
        DCD     DefaultISR
        DCD     UsageFault_Handler
__vector_table_0x1c
        DCD     SecureFault_Handler
        DCD     0
        DCD     0
        DCD     0
        DCD     SVC_Handler
        DCD     DefaultISR
        DCD     0
        DCD     DefaultISR
        DCD     SysTick_Handler

        ; External Interrupts
        DCD     DefaultISR  ; Windowed watchdog timer 0, Brownout detect
        DCD     DMA0_IRQHandler  ; DMA controller
        DCD     DefaultISR  ; Non-Secure HSGPIO_INT0
        DCD     DefaultISR  ; Non-Secure HSGPIO_INT1
        DCD     PIN_INT0_IRQHandler  ; Pin interrupt 0 or pattern match engine slice 0
        DCD     DefaultISR  ; Pin interrupt 1 or pattern match engine slice 1
        DCD     DefaultISR  ; Pin interrupt 2 or pattern match engine slice 2
        DCD     DefaultISR  ; Pin interrupt 3 or pattern match engine slice 3
        DCD     DefaultISR  ; Micro-tick Timer
        DCD     MRT0_IRQHandler  ; Multi-rate timer
        DCD     DefaultISR  ; Standard counter/timer CTIMER0
        DCD     DefaultISR  ; Standard counter/timer CTIMER1
        DCD     DefaultISR  ; SCTimer/PWM
        DCD     DefaultISR  ; Standard counter/timer CTIMER3
        DCD     FLEXCOMM0_IRQHandler  ; Flexcomm Interface 0 (USART, SPI, I2C , I2S)
        DCD     DefaultISR  ; Flexcomm Interface 1 (USART, SPI, I2C , I2S)
        DCD     FLEXCOMM2_IRQHandler  ; Flexcomm Interface 2 (USART, SPI, I2C , I2S)
        DCD     DefaultISR  ; Flexcomm Interface 3 (USART, SPI, I2C , I2S)
        DCD     DefaultISR  ; Flexcomm Interface 4 (USART, SPI, I2C , I2S)
        DCD     DefaultISR  ; Flexcomm Interface 5 (USART, SPI, I2C , I2S)
        DCD     FLEXCOMM14_IRQHandler  ; Flexcomm Interface 14 (SPI)
        DCD     DefaultISR  ; Flexcomm Interface 15 (I2C)
        DCD     DefaultISR  ; Analog to Digital Convertor.
        DCD     DefaultISR  ; Reserved interrupt.
        DCD     DefaultISR  ; ACMP and CAPT interrupt.
        DCD     DefaultISR  ; Digital microphone and DMIC subsystem
        DCD     DefaultISR  ; Hardware wake-up interrupt
        DCD     DefaultISR  ; Hypervisor interrupt
        DCD     DefaultISR  ; Secure Violation interrupt
        DCD     DefaultISR  ; Hardware Voice Activity Detector
        DCD     DefaultISR  ; Reserved interrupt
        DCD     DefaultISR  ; Random Number Generator interrupt
        DCD     DefaultISR  ; RTC alarm and wake-up interrupts
        DCD     DefaultISR  ; Reserved interrupt
        DCD     DefaultISR  ; Messaging Unit - Side A
        DCD     DefaultISR  ; Pin interrupt 4 or pattern match engine slice 4
        DCD     DefaultISR  ; Pin interrupt 5or pattern match engine slice 5
        DCD     DefaultISR  ; Pin interrupt 6 or pattern match engine slice 6
        DCD     DefaultISR  ; Pin interrupt 7 or pattern match engine slice 7
        DCD     DefaultISR  ; Standard counter/timer CTIMER2
        DCD     DefaultISR  ; Standard counter/timer CTIMER4
        DCD     DefaultISR  ; OS_EVENT Timer interrupt
        DCD     DefaultISR  ; QuadSPI interrupts
        DCD     DefaultISR  ; Flexcomm Interface 6 (USART, SPI, I2C , I2S)
        DCD     DefaultISR  ; Flexcomm Interface 7 (USART, SPI, I2C , I2S)
        DCD     SDIO0_IRQHandler  ; SD/MMC
        DCD     SDIO1_IRQHandler  ; SD/MMC
        DCD     DefaultISR  ; Secure HSGPIO_INT0 interrupt
        DCD     DefaultISR  ; Secure HSGPIO_INT1 interrupt
        DCD     DefaultISR  ; I3C interrupt
        DCD     USB0_IRQHandler  ; USB device
        DCD     USB0_NEEDCLK_IRQHandler  ; USB Activity Wake-up Interrupt
        DCD     DefaultISR  ; Windowed watchdog timer 1, Brownout detect
        DCD     USBPHY_DCD_IRQHandler  ; USB PHY interrupt
        DCD     DefaultISR  ; DMA controller
        DCD     DefaultISR  ; QDDKEY interrupt
        DCD     DefaultISR  ; POWERQUAD interrupt
        DCD     DefaultISR  ; CASPER interrupt
        DCD     DefaultISR  ; PMIC interrupt
        DCD     HASH_IRQHandler  ; HASH interrupt
        DCD     DefaultISR  ; Dynamic Process Monitor interrupt
        DCD     DefaultISR  ; PVTVF0_RED interrupt
        DCD     DefaultISR  ; PVTVF1_AMBER interrupt
        DCD     DefaultISR  ; PVTVF1_RED interrupt
__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size  EQU   __Vectors_End - __Vectors


clkctl0pscclkctrlset2	EQU	  0x40001048
pdruncfg0               EQU     0x40002610
pdruncfg1               EQU     0x40002614
pdruncfg2               EQU     0x40002618
pdruncfg3               EQU     0x4000261c
pdruncfgclr0            EQU     0x40002630
pdruncfgclr1            EQU     0x40002634
pdruncfgclr2            EQU     0x40002638
pdruncfgclr3            EQU     0x4000263c
pwrstatus               EQU	  0x40135004
pwrctrl	EQU	  0x4013500C

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;

        THUMB


        SECTION .text:CODE(4)
power_on_rom_mem
        ; enable the clock to PMC first
         LDR    r0, =clkctl0pscclkctrlset2
         LDR    r1, =0x20000000
         STR    r1, [r0]
         ;  Turn on partition 1 SRAMs before using stack push/pops
         LDR     r0, =pdruncfgclr2
         LDR    r1, =0x0e
         STR    r1, [r0]
         STR    r1, [r0, #4]
         LDR    r0, =pwrctrl
         LDR    r1, [r0]
         ORR    r1, r1, #1
         STR    r1, [r0]
         LDR    r0, =pwrstatus
wait_until_activefsm_0
         LDR    r1, [r0]
         ANDS   r1, r1, #1
         BNE    wait_until_activefsm_0
         BX     LR

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        IMPORT  go_fatal_mode
        IMPORT  init_data_bss_common
        IMPORT  main
        IMPORT  secure_counter_init

        CPSID   I               ; Mask interrupts
        LDR     R0, =0xE000ED08
        LDR     R1, =__vector_table
        STR     R1, [R0]
        LDR     R2, [R1]
        MSR     MSP, R2
        LDR     R0, =sfb(CSTACK)
        MSR     MSPLIM, R0
        LDR     R0, =power_on_rom_mem
        BLX     R0
        LDR     R0, =__stack_chk_guard
        LDR     R1, =0x5ac33ca5
        STR     R1, [R0]
        LDR     R0, =secure_counter_init
        BLX     R0
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =init_data_bss_common
        BLX     R0
        CPSIE   I               ; Unmask interrupts
        LDR     R0, =main
        BX      R0
        B       go_fatal_mode   ; mine field
        B       go_fatal_mode   ; mine filed
        B       go_fatal_mode


        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B .

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B .

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
        B .

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B .

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B .

        PUBWEAK SecureFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SecureFault_Handler
        B .

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B .

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
        B .

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B .

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B .

        PUBWEAK WDT0_BOD_IRQHandler
        PUBWEAK WDT0_BOD_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
WDT0_BOD_IRQHandler
        LDR     R0, =WDT0_BOD_DriverIRQHandler
        BX      R0
        PUBWEAK DMA0_IRQHandler
        PUBWEAK DMA0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA0_IRQHandler
        LDR     R0, =DMA0_DriverIRQHandler
        BX      R0
        PUBWEAK NSHSGPIO_INT0_IRQHandler
        PUBWEAK NSHSGPIO_INT0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
NSHSGPIO_INT0_IRQHandler
        LDR     R0, =NSHSGPIO_INT0_DriverIRQHandler
        BX      R0
        PUBWEAK NSHSGPIO_INT1_IRQHandler
        PUBWEAK NSHSGPIO_INT1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
NSHSGPIO_INT1_IRQHandler
        LDR     R0, =NSHSGPIO_INT1_DriverIRQHandler
        BX      R0
        PUBWEAK PIN_INT0_IRQHandler
        PUBWEAK PIN_INT0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PIN_INT0_IRQHandler
        LDR     R0, =PIN_INT0_DriverIRQHandler
        BX      R0
        PUBWEAK PIN_INT1_IRQHandler
        PUBWEAK PIN_INT1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PIN_INT1_IRQHandler
        LDR     R0, =PIN_INT1_DriverIRQHandler
        BX      R0
        PUBWEAK PIN_INT2_IRQHandler
        PUBWEAK PIN_INT2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PIN_INT2_IRQHandler
        LDR     R0, =PIN_INT2_DriverIRQHandler
        BX      R0
        PUBWEAK PIN_INT3_IRQHandler
        PUBWEAK PIN_INT3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PIN_INT3_IRQHandler
        LDR     R0, =PIN_INT3_DriverIRQHandler
        BX      R0
        PUBWEAK UTICK0_IRQHandler
        PUBWEAK UTICK0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
UTICK0_IRQHandler
        LDR     R0, =UTICK0_DriverIRQHandler
        BX      R0
        PUBWEAK MRT0_IRQHandler
        PUBWEAK MRT0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
MRT0_IRQHandler
        LDR     R0, =MRT0_DriverIRQHandler
        BX      R0
        PUBWEAK CTIMER0_IRQHandler
        PUBWEAK CTIMER0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CTIMER0_IRQHandler
        LDR     R0, =CTIMER0_DriverIRQHandler
        BX      R0
        PUBWEAK CTIMER1_IRQHandler
        PUBWEAK CTIMER1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CTIMER1_IRQHandler
        LDR     R0, =CTIMER1_DriverIRQHandler
        BX      R0
        PUBWEAK SCT0_IRQHandler
        PUBWEAK SCT0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SCT0_IRQHandler
        LDR     R0, =SCT0_DriverIRQHandler
        BX      R0
        PUBWEAK CTIMER3_IRQHandler
        PUBWEAK CTIMER3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CTIMER3_IRQHandler
        LDR     R0, =CTIMER3_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM0_IRQHandler
        PUBWEAK FLEXCOMM0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM0_IRQHandler
        LDR     R0, =FLEXCOMM0_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM1_IRQHandler
        PUBWEAK FLEXCOMM1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM1_IRQHandler
        LDR     R0, =FLEXCOMM1_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM2_IRQHandler
        PUBWEAK FLEXCOMM2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM2_IRQHandler
        LDR     R0, =FLEXCOMM2_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM3_IRQHandler
        PUBWEAK FLEXCOMM3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM3_IRQHandler
        LDR     R0, =FLEXCOMM3_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM4_IRQHandler
        PUBWEAK FLEXCOMM4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM4_IRQHandler
        LDR     R0, =FLEXCOMM4_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM5_IRQHandler
        PUBWEAK FLEXCOMM5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM5_IRQHandler
        LDR     R0, =FLEXCOMM5_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM14_IRQHandler
        PUBWEAK FLEXCOMM14_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM14_IRQHandler
        LDR     R0, =FLEXCOMM14_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM15_IRQHandler
        PUBWEAK FLEXCOMM15_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM15_IRQHandler
        LDR     R0, =FLEXCOMM15_DriverIRQHandler
        BX      R0
        PUBWEAK ADC0_IRQHandler
        PUBWEAK ADC0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ADC0_IRQHandler
        LDR     R0, =ADC0_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved0_IRQHandler
        PUBWEAK Reserved0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved0_IRQHandler
        LDR     R0, =Reserved0_DriverIRQHandler
        BX      R0
        PUBWEAK ACMP_IRQHandler
        PUBWEAK ACMP_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ACMP_IRQHandler
        LDR     R0, =ACMP_DriverIRQHandler
        BX      R0
        PUBWEAK DMIC0_IRQHandler
        PUBWEAK DMIC0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMIC0_IRQHandler
        LDR     R0, =DMIC0_DriverIRQHandler
        BX      R0
        PUBWEAK HW_WAKE_IRQHandler
        PUBWEAK HW_WAKE_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
HW_WAKE_IRQHandler
        LDR     R0, =HW_WAKE_DriverIRQHandler
        BX      R0
        PUBWEAK HYPERVISOR_IRQHandler
        PUBWEAK HYPERVISOR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
HYPERVISOR_IRQHandler
        LDR     R0, =HYPERVISOR_DriverIRQHandler
        BX      R0
        PUBWEAK SECUREVIOLATION_IRQHandler
        PUBWEAK SECUREVIOLATION_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SECUREVIOLATION_IRQHandler
        LDR     R0, =SECUREVIOLATION_DriverIRQHandler
        BX      R0
        PUBWEAK HWVAD0_IRQHandler
        PUBWEAK HWVAD0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
HWVAD0_IRQHandler
        LDR     R0, =HWVAD0_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved30_IRQHandler
        PUBWEAK Reserved30_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved30_IRQHandler
        LDR     R0, =Reserved30_DriverIRQHandler
        BX      R0
        PUBWEAK TRNG_IRQHandler
        PUBWEAK TRNG_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TRNG_IRQHandler
        LDR     R0, =TRNG_DriverIRQHandler
        BX      R0
        PUBWEAK RTC_IRQHandler
        PUBWEAK RTC_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
RTC_IRQHandler
        LDR     R0, =RTC_DriverIRQHandler
        BX      R0
        PUBWEAK DSP_TIE_EXPSTATE1_IRQHandler
        PUBWEAK DSP_TIE_EXPSTATE1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DSP_TIE_EXPSTATE1_IRQHandler
        LDR     R0, =DSP_TIE_EXPSTATE1_DriverIRQHandler
        BX      R0
        PUBWEAK MU_A_IRQHandler
        PUBWEAK MU_A_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
MU_A_IRQHandler
        LDR     R0, =MU_A_DriverIRQHandler
        BX      R0
        PUBWEAK PIN_INT4_IRQHandler
        PUBWEAK PIN_INT4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PIN_INT4_IRQHandler
        LDR     R0, =PIN_INT4_DriverIRQHandler
        BX      R0
        PUBWEAK PIN_INT5_IRQHandler
        PUBWEAK PIN_INT5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PIN_INT5_IRQHandler
        LDR     R0, =PIN_INT5_DriverIRQHandler
        BX      R0
        PUBWEAK PIN_INT6_IRQHandler
        PUBWEAK PIN_INT6_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PIN_INT6_IRQHandler
        LDR     R0, =PIN_INT6_DriverIRQHandler
        BX      R0
        PUBWEAK PIN_INT7_IRQHandler
        PUBWEAK PIN_INT7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PIN_INT7_IRQHandler
        LDR     R0, =PIN_INT7_DriverIRQHandler
        BX      R0
        PUBWEAK CTIMER2_IRQHandler
        PUBWEAK CTIMER2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CTIMER2_IRQHandler
        LDR     R0, =CTIMER2_DriverIRQHandler
        BX      R0
        PUBWEAK CTIMER4_IRQHandler
        PUBWEAK CTIMER4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CTIMER4_IRQHandler
        LDR     R0, =CTIMER4_DriverIRQHandler
        BX      R0
        PUBWEAK OS_EVENT_TIMER_IRQHandler
        PUBWEAK OS_EVENT_TIMER_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
OS_EVENT_TIMER_IRQHandler
        LDR     R0, =OS_EVENT_TIMER_DriverIRQHandler
        BX      R0
        PUBWEAK QSPI_IRQHandler
        PUBWEAK QSPI_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
QSPI_IRQHandler
        LDR     R0, =QSPI_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM6_IRQHandler
        PUBWEAK FLEXCOMM6_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM6_IRQHandler
        LDR     R0, =FLEXCOMM6_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM7_IRQHandler
        PUBWEAK FLEXCOMM7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM7_IRQHandler
        LDR     R0, =FLEXCOMM7_DriverIRQHandler
        BX      R0
        PUBWEAK SDIO0_IRQHandler
        PUBWEAK SDIO0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SDIO0_IRQHandler
        LDR     R0, =SDIO0_DriverIRQHandler
        BX      R0
        PUBWEAK SDIO1_IRQHandler
        PUBWEAK SDIO1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SDIO1_IRQHandler
        LDR     R0, =SDIO1_DriverIRQHandler
        BX      R0
        PUBWEAK SHSGPIO_INT0_IRQHandler
        PUBWEAK SHSGPIO_INT0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SHSGPIO_INT0_IRQHandler
        LDR     R0, =SHSGPIO_INT0_DriverIRQHandler
        BX      R0
        PUBWEAK SHSGPIO_INT1_IRQHandler
        PUBWEAK SHSGPIO_INT1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SHSGPIO_INT1_IRQHandler
        LDR     R0, =SHSGPIO_INT1_DriverIRQHandler
        BX      R0
        PUBWEAK I3C_IRQHandler
        PUBWEAK I3C_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I3C_IRQHandler
        LDR     R0, =I3C_DriverIRQHandler
        BX      R0
        PUBWEAK USB0_IRQHandler
        PUBWEAK USB0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
USB0_IRQHandler
        LDR     R0, =USB0_DriverIRQHandler
        BX      R0
        PUBWEAK USB0_NEEDCLK_IRQHandler
        PUBWEAK USB0_NEEDCLK_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
USB0_NEEDCLK_IRQHandler
        LDR     R0, =USB0_NEEDCLK_DriverIRQHandler
        BX      R0
        PUBWEAK WDT1_BOD_IRQHandler
        PUBWEAK WDT1_BOD_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
WDT1_BOD_IRQHandler
        LDR     R0, =WDT1_BOD_DriverIRQHandler
        BX      R0
        PUBWEAK USBPHY_DCD_IRQHandler
        PUBWEAK USBPHY_DCD_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
USBPHY_DCD_IRQHandler
        LDR     R0, =USBPHY_DCD_DriverIRQHandler
        BX      R0
        PUBWEAK DMA1_IRQHandler
        PUBWEAK DMA1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA1_IRQHandler
        LDR     R0, =DMA1_DriverIRQHandler
        BX      R0
        PUBWEAK QDDKEY_IRQHandler
        PUBWEAK QDDKEY_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
QDDKEY_IRQHandler
        LDR     R0, =QDDKEY_DriverIRQHandler
        BX      R0
        PUBWEAK POWERQUAD_IRQHandler
        PUBWEAK POWERQUAD_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
POWERQUAD_IRQHandler
        LDR     R0, =POWERQUAD_DriverIRQHandler
        BX      R0
        PUBWEAK CASPER_IRQHandler
        PUBWEAK CASPER_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CASPER_IRQHandler
        LDR     R0, =CASPER_DriverIRQHandler
        BX      R0
        PUBWEAK PMIC_IRQHandler
        PUBWEAK PMIC_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PMIC_IRQHandler
        LDR     R0, =PMIC_DriverIRQHandler
        BX      R0
        PUBWEAK HASH_IRQHandler
        PUBWEAK HASH_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
HASH_IRQHandler
        LDR     R0, =HASH_DriverIRQHandler
        BX      R0
        PUBWEAK DPM_IRQHandler
        PUBWEAK DPM_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DPM_IRQHandler
        LDR     R0, =DPM_DriverIRQHandler
        BX      R0
        PUBWEAK PVTVF0_RED_IRQHandler
        PUBWEAK PVTVF0_RED_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PVTVF0_RED_IRQHandler
        LDR     R0, =PVTVF0_RED_DriverIRQHandler
        BX      R0
        PUBWEAK PVTVF1_AMBER_IRQHandler
        PUBWEAK PVTVF1_AMBER_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PVTVF1_AMBER_IRQHandler
        LDR     R0, =PVTVF1_AMBER_DriverIRQHandler
        BX      R0
        PUBWEAK PVTVF1_RED_IRQHandler
        PUBWEAK PVTVF1_RED_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PVTVF1_RED_IRQHandler
        LDR     R0, =PVTVF1_RED_DriverIRQHandler
        BX      R0
WDT0_BOD_DriverIRQHandler
DMA0_DriverIRQHandler
NSHSGPIO_INT0_DriverIRQHandler
NSHSGPIO_INT1_DriverIRQHandler
PIN_INT0_DriverIRQHandler
PIN_INT1_DriverIRQHandler
PIN_INT2_DriverIRQHandler
PIN_INT3_DriverIRQHandler
UTICK0_DriverIRQHandler
MRT0_DriverIRQHandler
CTIMER0_DriverIRQHandler
CTIMER1_DriverIRQHandler
SCT0_DriverIRQHandler
CTIMER3_DriverIRQHandler
FLEXCOMM0_DriverIRQHandler
FLEXCOMM1_DriverIRQHandler
FLEXCOMM2_DriverIRQHandler
FLEXCOMM3_DriverIRQHandler
FLEXCOMM4_DriverIRQHandler
FLEXCOMM5_DriverIRQHandler
FLEXCOMM14_DriverIRQHandler
FLEXCOMM15_DriverIRQHandler
ADC0_DriverIRQHandler
Reserved0_DriverIRQHandler
ACMP_DriverIRQHandler
DMIC0_DriverIRQHandler
HW_WAKE_DriverIRQHandler
HYPERVISOR_DriverIRQHandler
SECUREVIOLATION_DriverIRQHandler
HWVAD0_DriverIRQHandler
Reserved30_DriverIRQHandler
TRNG_DriverIRQHandler
RTC_DriverIRQHandler
DSP_TIE_EXPSTATE1_DriverIRQHandler
MU_A_DriverIRQHandler
PIN_INT4_DriverIRQHandler
PIN_INT5_DriverIRQHandler
PIN_INT6_DriverIRQHandler
PIN_INT7_DriverIRQHandler
CTIMER2_DriverIRQHandler
CTIMER4_DriverIRQHandler
OS_EVENT_TIMER_DriverIRQHandler
QSPI_DriverIRQHandler
FLEXCOMM6_DriverIRQHandler
FLEXCOMM7_DriverIRQHandler
SDIO0_DriverIRQHandler
SDIO1_DriverIRQHandler
SHSGPIO_INT0_DriverIRQHandler
SHSGPIO_INT1_DriverIRQHandler
I3C_DriverIRQHandler
USB0_DriverIRQHandler
USB0_NEEDCLK_DriverIRQHandler
WDT1_BOD_DriverIRQHandler
USBPHY_DCD_DriverIRQHandler
DMA1_DriverIRQHandler
QDDKEY_DriverIRQHandler
POWERQUAD_DriverIRQHandler
CASPER_DriverIRQHandler
PMIC_DriverIRQHandler
HASH_DriverIRQHandler
DPM_DriverIRQHandler
PVTVF0_RED_DriverIRQHandler
PVTVF1_AMBER_DriverIRQHandler
PVTVF1_RED_DriverIRQHandler
DefaultISR
        B go_fatal_mode
        B go_fatal_mode

        END
