/*
 @file      cc26x2r1f.lds
 @brief     CC26x2R1F rev2 linker configuration file for GNU compiler.

 Revised    $Date$
 Revision   $Revision$

 This file is auto-generated.

  Copyright (C) 2017 Texas Instruments Incorporated - http:www.ti.com/


  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

    Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

    Neither the name of Texas Instruments Incorporated nor the names of
    its contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


  * -Xlinker --defsym=STACKSIZE=1024
*/

/* Entry Point */
ENTRY( resetISR )

/* System memory map */
MEMORY
{
    /* Application is stored in and executes from internal flash */
    FLASH (RX) : ORIGIN = 0x0, LENGTH = 0x57FA8

    /* Customer Configuration Area (CCFG) */
    FLASH_CCFG (RX) : ORIGIN = 0x57FA8, LENGTH = 88

    /* Application uses internal RAM for data */
    SRAM (RWX) : ORIGIN = 0x20000000, LENGTH = 0x14000

    /* Application can use GPRAM region as RAM if cache is disabled in the CCFG
    (DEFAULT_CCFG_SIZE_AND_DIS_FLAGS.SET_CCFG_SIZE_AND_DIS_FLAGS_DIS_GPRAM = 0) */
    GPRAM (RWX) : ORIGIN = 0x11000000, LENGTH = 0x2000
}

/*. Highest address of the stack. Used in startup file .*/
_estack = ORIGIN(SRAM) + LENGTH(SRAM); /*end of SRAM .*/
STACKSIZE = DEFINED(STACKSIZE) ? STACKSIZE : 1024; 

/* Section allocation in memory */
SECTIONS
{
    .resetVecs (0) : AT (0) {
        KEEP (*(.resetVecs))
    } > FLASH


    /*
     * UDMACC26XX_CONFIG_BASE below must match UDMACC26XX_CONFIG_BASE defined
     * by ti/drivers/dma/UDMACC26XX.h
     * The user is allowed to change UDMACC26XX_CONFIG_BASE to move it away from
     * the default address 0x2000_1800, but remember it must be 1024 bytes aligned.
     */
    UDMACC26XX_CONFIG_BASE = 0x20001800;

    /*
     * Define absolute addresses for the DMA channels.
     * DMA channels must always be allocated at a fixed offset from the DMA base address.
     * --------- DO NOT MODIFY -----------
     */
    DMA_UART0_RX_CONTROL_TABLE_ENTRY_ADDRESS  = (UDMACC26XX_CONFIG_BASE + 0x10);
    DMA_UART0_TX_CONTROL_TABLE_ENTRY_ADDRESS  = (UDMACC26XX_CONFIG_BASE + 0x20);
    DMA_SPI0_RX_CONTROL_TABLE_ENTRY_ADDRESS   = (UDMACC26XX_CONFIG_BASE + 0x30);
    DMA_SPI0_TX_CONTROL_TABLE_ENTRY_ADDRESS   = (UDMACC26XX_CONFIG_BASE + 0x40);
    DMA_UART1_RX_CONTROL_TABLE_ENTRY_ADDRESS  = (UDMACC26XX_CONFIG_BASE + 0x50);
    DMA_UART1_TX_CONTROL_TABLE_ENTRY_ADDRESS  = (UDMACC26XX_CONFIG_BASE + 0x60);
    DMA_ADC_PRI_CONTROL_TABLE_ENTRY_ADDRESS   = (UDMACC26XX_CONFIG_BASE + 0x70);
    DMA_GPT0A_PRI_CONTROL_TABLE_ENTRY_ADDRESS = (UDMACC26XX_CONFIG_BASE + 0x90);
    DMA_SPI1_RX_CONTROL_TABLE_ENTRY_ADDRESS   = (UDMACC26XX_CONFIG_BASE + 0x100);
    DMA_SPI1_TX_CONTROL_TABLE_ENTRY_ADDRESS   = (UDMACC26XX_CONFIG_BASE + 0x110);

    DMA_UART0_RX_ALT_CONTROL_TABLE_ENTRY_ADDRESS = (UDMACC26XX_CONFIG_BASE + 0x210);
    DMA_UART0_TX_ALT_CONTROL_TABLE_ENTRY_ADDRESS = (UDMACC26XX_CONFIG_BASE + 0x220);
    DMA_SPI0_RX_ALT_CONTROL_TABLE_ENTRY_ADDRESS  = (UDMACC26XX_CONFIG_BASE + 0x230);
    DMA_SPI0_TX_ALT_CONTROL_TABLE_ENTRY_ADDRESS  = (UDMACC26XX_CONFIG_BASE + 0x240);
    DMA_UART1_RX_ALT_CONTROL_TABLE_ENTRY_ADDRESS = (UDMACC26XX_CONFIG_BASE + 0x250);
    DMA_UART1_TX_ALT_CONTROL_TABLE_ENTRY_ADDRESS = (UDMACC26XX_CONFIG_BASE + 0x260);
    DMA_ADC_ALT_CONTROL_TABLE_ENTRY_ADDRESS      = (UDMACC26XX_CONFIG_BASE + 0x270);
    DMA_GPT0A_ALT_CONTROL_TABLE_ENTRY_ADDRESS    = (UDMACC26XX_CONFIG_BASE + 0x290);
    DMA_SPI1_RX_ALT_CONTROL_TABLE_ENTRY_ADDRESS  = (UDMACC26XX_CONFIG_BASE + 0x300);
    DMA_SPI1_TX_ALT_CONTROL_TABLE_ENTRY_ADDRESS  = (UDMACC26XX_CONFIG_BASE + 0x310);

    /*
     * Allocate UART0, UART1, SPI0, SPI1, ADC, and GPTimer0 DMA descriptors at absolute addresses.
     * --------- DO NOT MODIFY -----------
     */
    UDMACC26XX_uart0RxControlTableEntry_is_placed = 0;
    .dmaUart0RxControlTableEntry DMA_UART0_RX_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_UART0_RX_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaUart0RxControlTableEntry)} > SRAM

    UDMACC26XX_uart0TxControlTableEntry_is_placed = 0;
    .dmaUart0TxControlTableEntry DMA_UART0_TX_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_UART0_TX_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaUart0TxControlTableEntry)} > SRAM

    UDMACC26XX_dmaSpi0RxControlTableEntry_is_placed = 0;
    .dmaSpi0RxControlTableEntry DMA_SPI0_RX_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_SPI0_RX_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaSpi0RxControlTableEntry)} > SRAM

    UDMACC26XX_dmaSpi0TxControlTableEntry_is_placed = 0;
    .dmaSpi0TxControlTableEntry DMA_SPI0_TX_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_SPI0_TX_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaSpi0TxControlTableEntry)} > SRAM

    UDMACC26XX_uart1RxControlTableEntry_is_placed = 0;
    .dmaUart1RxControlTableEntry DMA_UART1_RX_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_UART1_RX_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaUart1RxControlTableEntry)} > SRAM

    UDMACC26XX_uart1TxControlTableEntry_is_placed = 0;
    .dmaUart1TxControlTableEntry DMA_UART1_TX_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_UART1_TX_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaUart1TxControlTableEntry)} > SRAM

    UDMACC26XX_dmaADCPriControlTableEntry_is_placed = 0;
    .dmaADCPriControlTableEntry DMA_ADC_PRI_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_ADC_PRI_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaADCPriControlTableEntry)} > SRAM

    UDMACC26XX_dmaGPT0APriControlTableEntry_is_placed = 0;
    .dmaGPT0APriControlTableEntry DMA_GPT0A_PRI_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_GPT0A_PRI_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaGPT0APriControlTableEntry)} > SRAM

    UDMACC26XX_dmaSpi1RxControlTableEntry_is_placed = 0;
    .dmaSpi1RxControlTableEntry DMA_SPI1_RX_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_SPI1_RX_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaSpi1RxControlTableEntry)} > SRAM

    UDMACC26XX_dmaSpi1TxControlTableEntry_is_placed = 0;
    .dmaSpi1TxControlTableEntry DMA_SPI1_TX_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_SPI1_TX_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaSpi1TxControlTableEntry)} > SRAM

    UDMACC26XX_uart0RxAltControlTableEntry_is_placed = 0;
    .dmaUart0RxAltControlTableEntry DMA_UART0_RX_ALT_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_UART0_RX_ALT_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaUart0RxAltControlTableEntry)} > SRAM

    UDMACC26XX_uart0TxAltControlTableEntry_is_placed = 0;
    .dmaUart0TxAltControlTableEntry DMA_UART0_TX_ALT_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_UART0_TX_ALT_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaUart0TxAltControlTableEntry)} > SRAM

    UDMACC26XX_dmaSpi0RxAltControlTableEntry_is_placed = 0;
    .dmaSpi0RxAltControlTableEntry DMA_SPI0_RX_ALT_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_SPI0_RX_ALT_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaSpi0RxAltControlTableEntry)} > SRAM

    UDMACC26XX_dmaSpi0TxAltControlTableEntry_is_placed = 0;
    .dmaSpi0TxAltControlTableEntry DMA_SPI0_TX_ALT_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_SPI0_TX_ALT_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaSpi0TxAltControlTableEntry)} > SRAM

    UDMACC26XX_uart1RxAltControlTableEntry_is_placed = 0;
    .dmaUart1RxAltControlTableEntry DMA_UART1_RX_ALT_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_UART1_RX_ALT_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaUart1RxAltControlTableEntry)} > SRAM

    UDMACC26XX_uart1TxAltControlTableEntry_is_placed = 0;
    .dmaUart1TxAltControlTableEntry DMA_UART1_TX_ALT_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_UART1_TX_ALT_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaUart1TxAltControlTableEntry)} > SRAM

    UDMACC26XX_dmaADCAltControlTableEntry_is_placed = 0;
    .dmaADCAltControlTableEntry DMA_ADC_ALT_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_ADC_ALT_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaADCAltControlTableEntry)} > SRAM

    UDMACC26XX_dmaGPT0AAltControlTableEntry_is_placed = 0;
    .dmaGPT0AAltControlTableEntry DMA_GPT0A_ALT_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_GPT0A_ALT_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaGPT0AAltControlTableEntry)} > SRAM

    UDMACC26XX_dmaSpi1RxAltControlTableEntry_is_placed = 0;
    .dmaSpi1RxAltControlTableEntry DMA_SPI1_RX_ALT_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_SPI1_RX_ALT_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaSpi1RxAltControlTableEntry)} > SRAM

    UDMACC26XX_dmaSpi1TxAltControlTableEntry_is_placed = 0;
    .dmaSpi1TxAltControlTableEntry DMA_SPI1_TX_ALT_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_SPI1_TX_ALT_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaSpi1TxAltControlTableEntry)} > SRAM

    .text :
    {
        _text = .;
        /* KEEP(*(.resetVecs)) */
        *(.text*)
        *(.rodata*)
        *(.init)
        *(.fini*)
        *(.eh_frame*)
        _etext = .;
    } > FLASH = 0

   .ARM.exidx :
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > FLASH

    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > FLASH

    .init_array :
    {
        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(SORT(.preinit_array.*)))
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);

        . = ALIGN(4);        
        _init_array = .;
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
        _einit_array = .;

        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        *(SORT(.fini_array.*))
        *(.fini_array)
        PROVIDE_HIDDEN (__fini_array_end = .);        
    } > FLASH
        
    .data :
    {
        __data_load__ = LOADADDR (.data);
        __data_start__ = .;
        _data = .;
        *(vtable)
        *(.data*)
        _edata = .;
        __data_end__ = .;
    } > SRAM AT > FLASH
    _ldata = LOADADDR(.data);

    .bss :
    {
        __bss_start__ = .;
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
        __bss_end__ = .;

        . = ALIGN(4);
        __HeapStart = .;           
    } > SRAM

    .heap (NOLOAD) : { KEEP(*(.heap)) } > SRAM

    .stack (NOLOAD) : ALIGN(0x8) {
        _stack = .;
        __stack = .;
        KEEP(*(.stack))
        . += STACKSIZE;
        _stack_end = .;
        __stack_end = .;
    } > SRAM

    .ccfg :
    {
        KEEP(*(.ccfg));
    } > FLASH_CCFG

    .gpram :
    {
    } > GPRAM

}

