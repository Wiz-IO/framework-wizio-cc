/******************************************************************************
*  Filename:       rf_patch_mce_iqdump.h
*
*  Description: RF core patch for IQ-dump support in CC13x2 PG2.1 and CC26x2 PG2.1
*
*  Copyright (c) 2015-2020, Texas Instruments Incorporated
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*
*  1) Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*
*  2) Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer in the documentation
*     and/or other materials provided with the distribution.
*
*  3) Neither the name of the ORGANIZATION nor the names of its contributors may
*     be used to endorse or promote products derived from this software without
*     specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************/

#include <stdint.h>
#include "rf_patch_mce_iqdump.h"
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)

#ifndef MCE_PATCH_TYPE
#define MCE_PATCH_TYPE static const uint32_t
#endif

#ifndef PATCH_FUN_SPEC
#define PATCH_FUN_SPEC
#endif

#ifndef RFC_MCERAM_BASE
#define RFC_MCERAM_BASE 0x21008000
#endif

#ifndef MCE_PATCH_MODE
#define MCE_PATCH_MODE 0
#endif

MCE_PATCH_TYPE patchIqdumpMce[363] = { 
   0x2fcf6030,
   0x00013f9d,
   0xff00003f,
   0x07ff0fff,
   0x0300f800,
   0x00068080,
   0x00170003,
   0x00003d1f,
   0x08000000,
   0x0000000f,
   0x00000387,
   0x00434074,
   0x00828000,
   0x06f00080,
   0x091e0000,
   0x00540510,
   0x00000007,
   0x00505014,
   0xc02f0000,
   0x017f0c30,
   0x00000000,
   0x00000000,
   0x00000000,
   0x0000aa00,
   0x66ca7223,
   0xa4e5a35d,
   0x73057303,
   0x73047203,
   0x72047306,
   0x72917391,
   0xffc0b008,
   0xa0089010,
   0x720e720d,
   0x7210720f,
   0x7100b0d0,
   0xa0d0b110,
   0x8162721b,
   0x39521020,
   0x00200670,
   0x11011630,
   0x6c011401,
   0x60886087,
   0x613e6104,
   0x60876087,
   0x60876087,
   0x60886087,
   0x61e46104,
   0x60876087,
   0x60876087,
   0x60886087,
   0x614e6104,
   0x60876087,
   0x60876087,
   0x60886087,
   0x62006104,
   0x60876087,
   0x60876087,
   0x60886087,
   0x61866104,
   0x60876087,
   0x60876087,
   0x61126088,
   0x1210614e,
   0x73117223,
   0x73137312,
   0x001081b1,
   0xb07091b0,
   0x607d6044,
   0x66d0c030,
   0xc2b2c0c1,
   0x1820c4e0,
   0x6e236f13,
   0x16121611,
   0x7830688e,
   0x78a099c0,
   0x94909480,
   0xc750c4f2,
   0x40a01820,
   0x6e231203,
   0x689d1612,
   0x999078b0,
   0xb63c7263,
   0x8190607d,
   0x81709640,
   0x2a703980,
   0x16111001,
   0x84b484a2,
   0xc0f5c0f3,
   0x1c01c200,
   0xc10040c9,
   0x40bf1c10,
   0x10134cc1,
   0x18301803,
   0x1a101a13,
   0x68bc3912,
   0x13f360c9,
   0x13f360c9,
   0xc1001015,
   0x1a151850,
   0x39141a10,
   0xb0e868c7,
   0xb1287100,
   0xb230a0e8,
   0x8990b910,
   0xb1119930,
   0x7100b0d1,
   0xb012b002,
   0xa0d1b111,
   0xb6307291,
   0xb013b003,
   0xb0e0722c,
   0xb1207100,
   0x92c08170,
   0xb1207100,
   0x22f08170,
   0x13f044e2,
   0x40ee1c03,
   0x964292c3,
   0xb1207100,
   0x964492c5,
   0xb1207100,
   0xa630b0e0,
   0xa0e17000,
   0x9910c030,
   0x9930c040,
   0xb0d1b111,
   0xb1117100,
   0x7291a0d1,
   0xa002a003,
   0x7000a230,
   0x73127311,
   0x66d0c040,
   0x91f0c100,
   0xb63364a5,
   0xb0d3b113,
   0xa0d37100,
   0x607d64f5,
   0x73127311,
   0x66d0c050,
   0x91f0c030,
   0xb0e8b634,
   0xb1287100,
   0xb230a0e8,
   0xb012b002,
   0xb013b003,
   0x92f01200,
   0xb0e1b121,
   0xb1217100,
   0x06208210,
   0x45261e20,
   0x66d0c060,
   0xb1217100,
   0x92f181d1,
   0x00000000,
   0x82120000,
   0x1e220622,
   0xc070412e,
   0xa63466d0,
   0x607d64f5,
   0xa0f0a0d2,
   0x7311a0f3,
   0x66447312,
   0x66d0c080,
   0xc035b0d2,
   0x9b757100,
   0xb074ba38,
   0x6148b112,
   0xa0f0a0d2,
   0x7311a0f3,
   0x66447312,
   0xc000c18b,
   0x120c91e0,
   0x786a1218,
   0x788e787d,
   0xb07410a9,
   0xc050b0d2,
   0x7100b112,
   0xc0906960,
   0xc03566d0,
   0x7100b112,
   0x8bf09b75,
   0x8ca165d9,
   0x41732201,
   0x1ca81080,
   0x12084572,
   0x65d01618,
   0x65d98c00,
   0x22018ca1,
   0x1090417e,
   0x1e091a19,
   0x10a9457e,
   0x818465d0,
   0x41661e04,
   0x1c4c14bc,
   0x61664eb3,
   0xa0f0a0d2,
   0x7311a0f3,
   0x66447312,
   0x120c721e,
   0xb0741205,
   0xc050b0d2,
   0x7100b112,
   0xc0a06992,
   0x789d66d0,
   0xb11289ce,
   0x8c907100,
   0x41a42200,
   0x22108230,
   0xb23145a4,
   0x66d0c0b0,
   0x8ab29a3d,
   0x3d823182,
   0x31808af0,
   0x18023d80,
   0x1e0e063e,
   0x1e2e41c6,
   0x1e3e41b8,
   0x105641bf,
   0x3d161426,
   0x61c71065,
   0x31261056,
   0x14261856,
   0x10653d26,
   0x105661c7,
   0x18563136,
   0x3d361426,
   0x61c71065,
   0x39761026,
   0x818491c6,
   0x41991e04,
   0x1c4c161c,
   0x61994eb3,
   0xc0b01001,
   0x391191c1,
   0x10001000,
   0x69d21000,
   0x31307000,
   0x1cd03d30,
   0x1ce04de0,
   0x700049e2,
   0x700010d0,
   0x700010e0,
   0x66d0c0c0,
   0xa0f0a0d2,
   0x7311a0f3,
   0x66447312,
   0xb0f0b130,
   0x80b07100,
   0x45f32200,
   0xb23161ee,
   0x66d0c0d0,
   0xa0f0b130,
   0xc035b0d2,
   0x9b757100,
   0xb074ba38,
   0x61fab112,
   0x66d0c0e0,
   0xa0f0a0d2,
   0x7311a0f3,
   0x66447312,
   0xc000c18b,
   0x120c91e0,
   0x786a1218,
   0x788e787d,
   0xb13010a9,
   0x7100b0f0,
   0x220080b0,
   0x62134618,
   0xb231b074,
   0x66d0c0f0,
   0xa0f0b130,
   0xc020b0d2,
   0x7100b112,
   0xc0356a20,
   0x7100b112,
   0x8bf09b75,
   0x8ca165d9,
   0x42312201,
   0x1ca81080,
   0x12084630,
   0x65d01618,
   0x65d98c00,
   0x22018ca1,
   0x1090423c,
   0x1e091a19,
   0x10a9463c,
   0x818465d0,
   0x42241e04,
   0x1c4c14bc,
   0x62244eb3,
   0x22308240,
   0xb0d5464c,
   0xb1157100,
   0x6244a0d5,
   0x66d0c100,
   0xb006b118,
   0xb004b016,
   0xb002b014,
   0x8440b012,
   0x04207842,
   0x39838173,
   0x94e32a73,
   0x1832c1f2,
   0x10213162,
   0x00123151,
   0x94400020,
   0x16101030,
   0x22103930,
   0x1220426a,
   0x10033150,
   0x16303180,
   0x12029380,
   0x22731204,
   0x84a0427c,
   0x89829970,
   0x84c01a82,
   0x89849970,
   0x627e1a84,
   0x42892263,
   0x997084b0,
   0x1a808980,
   0x84d01402,
   0x89809970,
   0x14041a80,
   0x84b06295,
   0x04107851,
   0x89829970,
   0x84d01a42,
   0x04107851,
   0x89849970,
   0x31521a44,
   0x39633154,
   0x16130633,
   0x38343832,
   0x39823182,
   0x00423184,
   0x84a09722,
   0x84b09590,
   0x84c095a0,
   0x84d095b0,
   0x781095c0,
   0x90509030,
   0x90407820,
   0xb2359060,
   0x9170cd90,
   0xa2357000,
   0x7100b112,
   0xb112a0d2,
   0x81b0ba3c,
   0x39248b54,
   0x00043184,
   0xc11091b4,
   0x739166d0,
   0x66ca7291,
   0x72027206,
   0x73057204,
   0x607d7306,
   0xc8018630,
   0x04103151,
   0x70009630,
   0x89f09a00,
   0x46d12200,
   0x7000b9e0
};

PATCH_FUN_SPEC void rf_patch_mce_iqdump(void)
{
#ifdef __PATCH_NO_UNROLLING
   uint32_t i;
   for (i = 0; i < 363; i++) {
      HWREG(RFC_MCERAM_BASE + 4 * i) = patchIqdumpMce[i];
   }
#else
   const uint32_t *pS = patchIqdumpMce;
   volatile unsigned long *pD = &HWREG(RFC_MCERAM_BASE);
   uint32_t t1, t2, t3, t4, t5, t6, t7, t8;
   uint32_t nIterations = 45;

   do {
      t1 = *pS++;
      t2 = *pS++;
      t3 = *pS++;
      t4 = *pS++;
      t5 = *pS++;
      t6 = *pS++;
      t7 = *pS++;
      t8 = *pS++;
      *pD++ = t1;
      *pD++ = t2;
      *pD++ = t3;
      *pD++ = t4;
      *pD++ = t5;
      *pD++ = t6;
      *pD++ = t7;
      *pD++ = t8;
   } while (--nIterations);

   t1 = *pS++;
   t2 = *pS++;
   t3 = *pS++;
   *pD++ = t1;
   *pD++ = t2;
   *pD++ = t3;
#endif
}
/* -------- ASSEMBLY CODE ----------------------------------------------
;  mce_ram_bank.asm:      1 ;;; --------------------------------------------------------------------------------
;  mce_ram_bank.asm:      2 ;;; MCE patch
;  mce_ram_bank.asm:      3 ;;;
;  mce_ram_bank.asm:      4 ;;; IQdump patch has 4 modes (programmed by protocol ID)
;  mce_ram_bank.asm:      5 ;;;  Protocol ID 0 - Infinite Register update Blind mode (starting immediately)
;  mce_ram_bank.asm:      6 ;;;  Protocol ID 1 - Infinite Register update Sync mode (starting after SFD detection)
;  mce_ram_bank.asm:      7 ;;;  Protocol ID 2 - Packet Size RFC FIFO Blind mode (starting immediately)
;  mce_ram_bank.asm:      8 ;;;  Protocol ID 3 - Packet Size RFC FIFO Sync mode (starting after SFD detection)  
;  mce_ram_bank.asm:      9 ;;; IQDump is a programmable/flexible mode with the following parameters
;  mce_ram_bank.asm:     10 ;;; - DataRate
;  mce_ram_bank.asm:     11 ;;; - Deviation
;  mce_ram_bank.asm:     12 ;;; - Shape (Gaussian or FSK)
;  mce_ram_bank.asm:     13 ;;; - RX BW
;  mce_ram_bank.asm:     14 ;;;
;  mce_ram_bank.asm:     15 ;;; Possible memory reduction. Merge RFC FIFO Blind/Sync mode to one common mode and then 
;  mce_ram_bank.asm:     16 ;;; change behaviour later by CONFIGURATION register instead of Protocol ID / Mode. 
;  mce_ram_bank.asm:     17 ;;; --------------------------------------------------------------------------------
;  mce_ram_bank.asm:     18         
;  mce_ram_bank.asm:     19 __DBG__ .assign 1
;  mce_ram_bank.asm:     20 .include "dbg.asm"
;  dbg.asm:               1 ;;; Include file for handling debug print in TOPsm
;  dbg.asm:               2         
;  dbg.asm:               3 ;;; --------------------------------------------------------------------------------
;  dbg.asm:               4 ;;; Macro for handling code generated from DBG_PRINT0
;  dbg.asm:               5 .MACRO _DBG0   cmd
;  dbg.asm:               6 .ifdef __DBG__
;  dbg.asm:               7         lli     \cmd, r0
;  dbg.asm:               8         jsr     _DBG_PRINT
;  dbg.asm:               9 .endif __DBG__
;  dbg.asm:              10 .ENDM
;  dbg.asm:              11 
;  dbg.asm:              12 ;;; --------------------------------------------------------------------------------
;  dbg.asm:              13 ;;; Macro for handling code generated from DBG_PRINT1
;  dbg.asm:              14 .MACRO _DBG1   cmd, reg0
;  dbg.asm:              15 .ifdef __DBG__
;  dbg.asm:              16         lli     \cmd, r0
;  dbg.asm:              17         output  \reg0, MCETRCPAR0
;  dbg.asm:              18         jsr     _DBG_PRINT
;  dbg.asm:              19 .endif __DBG__
;  dbg.asm:              20 .ENDM
;  dbg.asm:              21 
;  dbg.asm:              22 ;;; --------------------------------------------------------------------------------
;  dbg.asm:              23 ;;; Macro for handling code generated from DBG_PRINT2
;  dbg.asm:              24 .MACRO _DBG2   cmd, reg0, reg1
;  dbg.asm:              25 .ifdef __DBG__
;  dbg.asm:              26         lli     \cmd, r0
;  dbg.asm:              27         output  \reg0, MCETRCPAR0
;  dbg.asm:              28         output  \reg1, MCETRCPAR1
;  dbg.asm:              29         jsr     _DBG_PRINT
;  dbg.asm:              30 .endif __DBG__
;  dbg.asm:              31 .ENDM
;  dbg.asm:              32 
;  dbg.asm:              33 ;;; --------------------------------------------------------------------------------
;  dbg.asm:              34 ;;; Macro for inserting handling code for debug printing - insert once in source file
;  dbg.asm:              35 
;  dbg.asm:              36 .MACRO DBG_FUNC
;  dbg.asm:              37 .ifdef __DBG__
;  dbg.asm:              38 ;;; DBG_PRINT
;  dbg.asm:              39 ;;; R0 = pkt hdr
;  dbg.asm:              40 _DBG_PRINT:
;  dbg.asm:              41         output  r0, MCETRCCMD    ; R0 = pkt hdr
;  dbg.asm:              42 _DBG_PRINT_WAIT:         
;  dbg.asm:              43         input   MCETRCBUSY, r0   ; Wait until BUSY is released
;  dbg.asm:              44         btst    0, r0            ; Test bit 0
;  dbg.asm:              45         bne     _DBG_PRINT_WAIT
;  dbg.asm:              46         outbset MCETRCSEND_SEND, MCETRCSEND
;  dbg.asm:              47         rts
;  dbg.asm:              48 .endif __DBG__
;  dbg.asm:              49 .ENDM
;  dbg.asm:              50                 
;  dbg.asm:              51         
;  mce_ram_bank.asm:     21 
;  mce_ram_bank.asm:     22 .DEFINE CMD_OK 1
;  mce_ram_bank.asm:     23 .DEFINE CMD_ERR 2
;  mce_ram_bank.asm:     24 
;  mce_ram_bank.asm:     25 ;;; --------------------------------------------------------------------------------
;  mce_ram_bank.asm:     26 ;;; Includes & Defines
;  mce_ram_bank.asm:     27 ;;; 
;  mce_ram_bank.asm:     28 .include "mce_commonlib.asm"
;  mce_commonlib.asm:     1 ;;;  Only define MCE events if they are not already defined
;  mce_commonlib.asm:     2 .ifndef MCEEVENT0_CL_RX_IRQ
;  mce_commonlib.asm:     3 	;;; --------------------------------------------------------------------------------
;  mce_commonlib.asm:     4 	;;; MCE EVENT IO MAP
;  mce_commonlib.asm:     5 	;;; --------------------------------------------------------------------------------
;  mce_commonlib.asm:     6 
;  mce_commonlib.asm:     7         ;; -------------------------------------------------------------
;  mce_commonlib.asm:     8         ;; This file is **manually** generated, and needs to
;  mce_commonlib.asm:     9         ;; replicate the event mapping found in cc26_rfcore/hdl/rtl/mdm_rtl.vhd
;  mce_commonlib.asm:    10         ;;
;  mce_commonlib.asm:    11         ;; The registers MCEEVENTn, MCEEVENTMSKn, MCEEVENTCLRn all
;  mce_commonlib.asm:    12         ;; have identical mapping
;  mce_commonlib.asm:    13         ;; -------------------------------------------------------------
;  mce_commonlib.asm:    14 
;  mce_commonlib.asm:    15 
;  mce_commonlib.asm:    16         ; --------------------------------------------------------------
;  mce_commonlib.asm:    17         ; MCEEVENT0 event register bit positions
;  mce_commonlib.asm:    18         ;        
;  mce_commonlib.asm:    19         .DEFINE MCEEVENT0_MDMAPI_WR              0 ; New command from CPE received in MDMAPI register
;  mce_commonlib.asm:    20         .DEFINE MCEEVENT0_TIMER_IRQ              1 ; Timer period expired in local timer
;  mce_commonlib.asm:    21         .DEFINE MCEEVENT0_CLKEN_4BAUD            2 ; Clock enable event at 4 times baud rate
;  mce_commonlib.asm:    22         .DEFINE MCEEVENT0_FIFO_ERR_UNDERFLOW     3 ; FIFO underflow error event
;  mce_commonlib.asm:    23         .DEFINE MCEEVENT0_FIFO_ERR_OVERFLOW      4 ; FIFO overflow error event
;  mce_commonlib.asm:    24         .DEFINE MCEEVENT0_RFECMD_IRQ             5 ; New command from RFE received in MCERCEV register
;  mce_commonlib.asm:    25         .DEFINE MCEEVENT0_COUNTER_IRQ            6 ; Counter value reached in local timer
;  mce_commonlib.asm:    26         .DEFINE MCEEVENT0_MDMFIFO_WR             7 ; A write to the MDMFIFO register from CPE
;  mce_commonlib.asm:    27         .DEFINE MCEEVENT0_CPEFWEVENT0            8 ; Firmware defined event from CPE
;  mce_commonlib.asm:    28         .DEFINE MCEEVENT0_CPEFWEVENT1            9 ; Firmware defined event from CPE
;  mce_commonlib.asm:    29         .DEFINE MCEEVENT0_BDEC_EN               10 ; BDEC output enable
;  mce_commonlib.asm:    30         .DEFINE MCEEVENT0_FRAC_EN               11 ; FRAC output enable
;  mce_commonlib.asm:    31         .DEFINE MCEEVENT0_DL_TX_DONE            12 ; SMI serdes data word transmit done
;  mce_commonlib.asm:    32         .DEFINE MCEEVENT0_CL_TX_DONE            13 ; SMI serdes command word transmit done
;  mce_commonlib.asm:    33         .DEFINE MCEEVENT0_DL_RX_IRQ             14 ; SMI serdes data word receive interrupt
;  mce_commonlib.asm:    34         .DEFINE MCEEVENT0_CL_RX_IRQ             15 ; SMI serdes command word receive interrupt
;  mce_commonlib.asm:    35 
;  mce_commonlib.asm:    36         ; --------------------------------------------------------------
;  mce_commonlib.asm:    37         ; MCEEVENT1 event register bit positions
;  mce_commonlib.asm:    38         ; 
;  mce_commonlib.asm:    39         .DEFINE MCEEVENT1_PREAMBLE_DONE          0 ; Preamble done interrupt from modulator
;  mce_commonlib.asm:    40         .DEFINE MCEEVENT1_CLKEN_BAUD             1 ; Baud indication 
;  mce_commonlib.asm:    41         .DEFINE MCEEVENT1_FIFOWR_READY           2 ; It is legal to write to MDMFIFOWR register
;  mce_commonlib.asm:    42         .DEFINE MCEEVENT1_FIFORD_VALID           3 ; It is leval to read from MDMFIFORD register
;  mce_commonlib.asm:    43         .DEFINE MCEEVENT1_VITACC                 4 ; Unused event
;  mce_commonlib.asm:    44         .DEFINE MCEEVENT1_MDMCMDPAR0_WR          5 ; A write to MDMCMDPAR0 register from CPE
;  mce_commonlib.asm:    45         .DEFINE MCEEVENT1_MDMCMDPAR1_WR          6 ; A write to MDMCMDPAR1 register from CPE
;  mce_commonlib.asm:    46         .DEFINE MCEEVENT1_CLKEN_BAUD_F           7 ; Flushed Baud Indication 
;  mce_commonlib.asm:    47         .DEFINE MCEEVENT1_RAT_EVENT0             8 ; Radio timer event 0
;  mce_commonlib.asm:    48         .DEFINE MCEEVENT1_RAT_EVENT1             9 ; Radio timer event 1
;  mce_commonlib.asm:    49         .DEFINE MCEEVENT1_RAT_EVENT2            10 ; Radio timer event 2
;  mce_commonlib.asm:    50         .DEFINE MCEEVENT1_RAT_EVENT3            11 ; Radio timer event 3
;  mce_commonlib.asm:    51         .DEFINE MCEEVENT1_RAT_EVENT4            12 ; Radio timer event 4
;  mce_commonlib.asm:    52         .DEFINE MCEEVENT1_RAT_EVENT5            13 ; Radio timer event 5
;  mce_commonlib.asm:    53         .DEFINE MCEEVENT1_RAT_EVENT6            14 ; Radio timer event 6
;  mce_commonlib.asm:    54         .DEFINE MCEEVENT1_RAT_EVENT7            15 ; Radio timer event 7
;  mce_commonlib.asm:    55 
;  mce_commonlib.asm:    56         ; --------------------------------------------------------------
;  mce_commonlib.asm:    57         ; MCEEVENT2 event register bit positions
;  mce_commonlib.asm:    58         ;
;  mce_commonlib.asm:    59         .DEFINE MCEEVENT2_C1BE_A_POS_PEAK       0 ; Correlator peak detect: corr A > thr A (occurs one sample after peak)
;  mce_commonlib.asm:    60         .DEFINE MCEEVENT2_C1BE_A_NEG_PEAK       1 ; Correlator peak detect: corr A < -thr A (occurs one sample after peak)
;  mce_commonlib.asm:    61         .DEFINE MCEEVENT2_C1BE_A_ANY_PEAK       2 ; Correlator peak detect: abs(corr A) > thr A (occurs one sample after peak)
;  mce_commonlib.asm:    62         .DEFINE MCEEVENT2_C1BE_B_POS_PEAK       3 ; Correlator peak detect: corr B > thr B (occurs one sample after peak)
;  mce_commonlib.asm:    63         .DEFINE MCEEVENT2_C1BE_B_NEG_PEAK       4 ; Correlator peak detect: corr B < -thr B (occurs one sample after peak)
;  mce_commonlib.asm:    64         .DEFINE MCEEVENT2_C1BE_B_ANY_PEAK       5 ; Correlator peak detect: abs(corr B) > thr B (occurs one sample after peak)
;  mce_commonlib.asm:    65         .DEFINE MCEEVENT2_C1BE_C_POS_PEAK       6 ; Correlator peak detect: corr C > thr C (occurs one sample after peak)
;  mce_commonlib.asm:    66         .DEFINE MCEEVENT2_C1BE_C_NEG_PEAK       7 ; Correlator peak detect: corr C < -thr C (occurs one sample after peak)
;  mce_commonlib.asm:    67         .DEFINE MCEEVENT2_C1BE_C_ANY_PEAK       8 ; Correlator peak detect: abs(corr C) > thr C (occurs one sample after peak)
;  mce_commonlib.asm:    68         .DEFINE MCEEVENT2_C1BE_CMB_POS_PEAK     9 ; Correlator peak detect: corr CMB > thr CMB (occurs one sample after peak)
;  mce_commonlib.asm:    69         .DEFINE MCEEVENT2_C1BE_CMB_NEG_PEAK    10 ; Correlator peak detect: corr CMB < -thr CMB (occurs one sample after peak)
;  mce_commonlib.asm:    70         .DEFINE MCEEVENT2_C1BE_CMB_ANY_PEAK    11 ; Correlator peak detect: abs(corr CMB) > thr CMB (occurs one sample after peak)        
;  mce_commonlib.asm:    71         .DEFINE MCEEVENT2_C1BE_B_LOADED        12 ; Correlator B loaded (by auto-copy function)
;  mce_commonlib.asm:    72         .DEFINE MCEEVENT2_SWQU_SYNCED_IRQ      13 ; Sync word qualifier detected sync word
;  mce_commonlib.asm:    73         .DEFINE MCEEVENT2_MDMGPI0              14 ; Event from RFCore GPI 0
;  mce_commonlib.asm:    74         .DEFINE MCEEVENT2_MDMGPI1              15 ; Event from RFCore GPI 1
;  mce_commonlib.asm:    75 
;  mce_commonlib.asm:    76         ; --------------------------------------------------------------
;  mce_commonlib.asm:    77         ; MCEEVENT3 event register bit positions
;  mce_commonlib.asm:    78         ;
;  mce_commonlib.asm:    79         .DEFINE MCEEVENT3_C1BE_D_POS_PEAK       0 ; Correlator peak detect: corr A > thr A (occurs one sample after peak)
;  mce_commonlib.asm:    80         .DEFINE MCEEVENT3_C1BE_D_NEG_PEAK       1 ; Correlator peak detect: corr A < -thr A (occurs one sample after peak)
;  mce_commonlib.asm:    81         .DEFINE MCEEVENT3_C1BE_D_ANY_PEAK       2 ; Correlator peak detect: abs(corr A) > thr A (occurs one sample after peak)
;  mce_commonlib.asm:    82         .DEFINE MCEEVENT3_C1BE_E_POS_PEAK       3 ; Correlator peak detect: corr B > thr B (occurs one sample after peak)
;  mce_commonlib.asm:    83         .DEFINE MCEEVENT3_C1BE_E_NEG_PEAK       4 ; Correlator peak detect: corr B < -thr B (occurs one sample after peak)
;  mce_commonlib.asm:    84         .DEFINE MCEEVENT3_C1BE_E_ANY_PEAK       5 ; Correlator peak detect: abs(corr B) > thr B (occurs one sample after peak)
;  mce_commonlib.asm:    85         .DEFINE MCEEVENT3_C1BE_F_POS_PEAK       6 ; Correlator peak detect: corr C > thr C (occurs one sample after peak)
;  mce_commonlib.asm:    86         .DEFINE MCEEVENT3_C1BE_F_NEG_PEAK       7 ; Correlator peak detect: corr C < -thr C (occurs one sample after peak)
;  mce_commonlib.asm:    87         .DEFINE MCEEVENT3_C1BE_F_ANY_PEAK       8 ; Correlator peak detect: abs(corr C) > thr C (occurs one sample after peak)
;  mce_commonlib.asm:    88         .DEFINE MCEEVENT3_C1BE_CMB_DE_POS_PEAK  9 ; Correlator peak detect: corr CMB > thr CMB (occurs one sample after peak)
;  mce_commonlib.asm:    89         .DEFINE MCEEVENT3_C1BE_CMB_DE_NEG_PEAK 10 ; Correlator peak detect: corr CMB < -thr CMB (occurs one sample after peak)
;  mce_commonlib.asm:    90         .DEFINE MCEEVENT3_C1BE_CMB_DE_ANY_PEAK 11 ; Correlator peak detect: abs(corr CMB) > thr CMB (occurs one sample after peak)        
;  mce_commonlib.asm:    91         .DEFINE MCEEVENT3_C1BE_G_POS_PEAK      12 ; Correlator peak detect: corr G > thr G 
;  mce_commonlib.asm:    92         .DEFINE MCEEVENT3_C1BE_G_NEG_PEAK      13 ; Correlator peak detect: corr G < -thr G 
;  mce_commonlib.asm:    93         .DEFINE MCEEVENT3_C1BE_G_ANY_PEAK      14 ; Correlator peak detect: abs(corr G) > thr G 
;  mce_commonlib.asm:    94         .DEFINE MCEEVENT3_SWQU_FALSE_SYNC_IRQ  15 ; Sync owrd qualifier false sync 
;  mce_commonlib.asm:    95 .endif
;  mce_commonlib.asm:    96 
;  mce_commonlib.asm:    97 
;  mce_commonlib.asm:    98 ;;; Note, Agama does not have the MROM dump macroes nor functions, as this is implemented in HW 
;  mce_ram_bank.asm:     29 .INCLUDE "../inc/mdm_regs.asm"
;  mdm_regs.asm:          1 ; -------------------------------------------------------------
;  mdm_regs.asm:          2 ; This file is automatically generated by topsmregs script:
;  mdm_regs.asm:          3 ;   /vobs/cc26xxAgamaFwDev/radio_domain/tools/topsm/topsmregs.pl -target asm -i /vobs/cc26xxIpDev/modules/cc26_rfcore_ig/doc/MCEregs.txt
;  mdm_regs.asm:          4 ; File generated at 09-Mar-2021 17:46
;  mdm_regs.asm:          5 ;
;  mdm_regs.asm:          6 
;  mdm_regs.asm:          7 .ifndef _MDM_REGS_ASM_
;  mdm_regs.asm:          8 _MDM_REGS_ASM_ .assign 1
;  mdm_regs.asm:          9 
;  mdm_regs.asm:         10 ; --------------------------------------------------------------
;  mdm_regs.asm:         11 ; MDMENABLE
;  mdm_regs.asm:         12 ; 
;  mdm_regs.asm:         13 MDMENABLE                                         .assign     0
;  mdm_regs.asm:         14 MDMENABLE_PDIF2                                   .assign    11 ;
;  mdm_regs.asm:         15 MDMENABLE_PHASECORR                               .assign    10 ;
;  mdm_regs.asm:         16 MDMENABLE_HILBDISC                                .assign     9 ;
;  mdm_regs.asm:         17 MDMENABLE_FB2PLL                                  .assign     8 ;
;  mdm_regs.asm:         18 MDMENABLE_VITACC                                  .assign     7 ;
;  mdm_regs.asm:         19 MDMENABLE_ADCDIG                                  .assign     6 ;
;  mdm_regs.asm:         20 MDMENABLE_SMI                                     .assign     5 ;
;  mdm_regs.asm:         21 MDMENABLE_DEMODULATOR                             .assign     4 ;
;  mdm_regs.asm:         22 MDMENABLE_MODULATOR                               .assign     3 ;
;  mdm_regs.asm:         23 MDMENABLE_TIMEBASE                                .assign     2 ;
;  mdm_regs.asm:         24 MDMENABLE_TXRXFIFO                                .assign     1 ;
;  mdm_regs.asm:         25 MDMENABLE_mce                                   .assign     0 ;
;  mdm_regs.asm:         26 ; --------------------------------------------------------------
;  mdm_regs.asm:         27 ; MDMINIT
;  mdm_regs.asm:         28 ; 
;  mdm_regs.asm:         29 MDMINIT                                           .assign     1
;  mdm_regs.asm:         30 MDMINIT_PDIF2                                     .assign    11 ;
;  mdm_regs.asm:         31 MDMINIT_PHASECORR                                 .assign    10 ;
;  mdm_regs.asm:         32 MDMINIT_HILBDISC                                  .assign     9 ;
;  mdm_regs.asm:         33 MDMINIT_FB2PLL                                    .assign     8 ;
;  mdm_regs.asm:         34 MDMINIT_VITACC                                    .assign     7 ;
;  mdm_regs.asm:         35 MDMINIT_ADCDIG                                    .assign     6 ;
;  mdm_regs.asm:         36 MDMINIT_SMI                                       .assign     5 ;
;  mdm_regs.asm:         37 MDMINIT_DEMODULATOR                               .assign     4 ;
;  mdm_regs.asm:         38 MDMINIT_MODULATOR                                 .assign     3 ;
;  mdm_regs.asm:         39 MDMINIT_TIMEBASE                                  .assign     2 ;
;  mdm_regs.asm:         40 MDMINIT_TXRXFIFO                                  .assign     1 ;
;  mdm_regs.asm:         41 MDMINIT_mce                                     .assign     0 ;
;  mdm_regs.asm:         42 ; --------------------------------------------------------------
;  mdm_regs.asm:         43 ; MDMPDREQ
;  mdm_regs.asm:         44 ; 
;  mdm_regs.asm:         45 MDMPDREQ                                          .assign     2
;  mdm_regs.asm:         46 MDMPDREQ_mcePDREQ                               .assign     0 ;
;  mdm_regs.asm:         47 ; --------------------------------------------------------------
;  mdm_regs.asm:         48 ; DEMENABLE0
;  mdm_regs.asm:         49 ; 
;  mdm_regs.asm:         50 DEMENABLE0                                        .assign     3
;  mdm_regs.asm:         51 DEMENABLE0_FE23                                   .assign    15 ;
;  mdm_regs.asm:         52 DEMENABLE0_FE13                                   .assign    14 ;
;  mdm_regs.asm:         53 DEMENABLE0_FELP                                   .assign    13 ;
;  mdm_regs.asm:         54 DEMENABLE0_THRD                                   .assign    12 ;
;  mdm_regs.asm:         55 DEMENABLE0_FRAC                                   .assign    11 ;
;  mdm_regs.asm:         56 DEMENABLE0_FIDC                                   .assign    10 ;
;  mdm_regs.asm:         57 DEMENABLE0_CHFI                                   .assign     9 ;
;  mdm_regs.asm:         58 DEMENABLE0_BDEC                                   .assign     8 ;
;  mdm_regs.asm:         59 DEMENABLE0_IQMC                                   .assign     7 ;
;  mdm_regs.asm:         60 DEMENABLE0_MGE2                                   .assign     6 ;
;  mdm_regs.asm:         61 DEMENABLE0_MGE1                                   .assign     5 ;
;  mdm_regs.asm:         62 DEMENABLE0_RSVD                                   .assign     4 ;
;  mdm_regs.asm:         63 DEMENABLE0_CODC                                   .assign     3 ;
;  mdm_regs.asm:         64 DEMENABLE0_CMI4                                   .assign     2 ;
;  mdm_regs.asm:         65 DEMENABLE0_CMIX                                   .assign     1 ;
;  mdm_regs.asm:         66 DEMENABLE0_HILB                                   .assign     0 ;
;  mdm_regs.asm:         67 ; --------------------------------------------------------------
;  mdm_regs.asm:         68 ; DEMENABLE1
;  mdm_regs.asm:         69 ; 
;  mdm_regs.asm:         70 DEMENABLE1                                        .assign     4
;  mdm_regs.asm:         71 DEMENABLE1_VITE                                   .assign    15 ;
;  mdm_regs.asm:         72 DEMENABLE1_MLSE                                   .assign    14 ;
;  mdm_regs.asm:         73 DEMENABLE1_SOFD                                   .assign    13 ;
;  mdm_regs.asm:         74 DEMENABLE1_SWQU                                   .assign    12 ;
;  mdm_regs.asm:         75 DEMENABLE1_MAFC                                   .assign    11 ;
;  mdm_regs.asm:         76 DEMENABLE1_MAFI                                   .assign    10 ;
;  mdm_regs.asm:         77 DEMENABLE1_FIFE                                   .assign     9 ;
;  mdm_regs.asm:         78 DEMENABLE1_PDIF                                   .assign     8 ;
;  mdm_regs.asm:         79 DEMENABLE1_CA2P                                   .assign     7 ;
;  mdm_regs.asm:         80 DEMENABLE1_FECP                                   .assign     6 ;
;  mdm_regs.asm:         81 DEMENABLE1_FEC5                                   .assign     5 ;
;  mdm_regs.asm:         82 DEMENABLE1_C1BE                                   .assign     4 ;
;  mdm_regs.asm:         83 DEMENABLE1_LQIE                                   .assign     3 ;
;  mdm_regs.asm:         84 DEMENABLE1_F4BA                                   .assign     2 ;
;  mdm_regs.asm:         85 DEMENABLE1_STIM                                   .assign     1 ;
;  mdm_regs.asm:         86 DEMENABLE1_DSBU                                   .assign     0 ;
;  mdm_regs.asm:         87 ; --------------------------------------------------------------
;  mdm_regs.asm:         88 ; DEMINIT0
;  mdm_regs.asm:         89 ; 
;  mdm_regs.asm:         90 DEMINIT0                                          .assign     5
;  mdm_regs.asm:         91 DEMINIT0_FE23                                     .assign    15 ;
;  mdm_regs.asm:         92 DEMINIT0_FE13                                     .assign    14 ;
;  mdm_regs.asm:         93 DEMINIT0_FELP                                     .assign    13 ;
;  mdm_regs.asm:         94 DEMINIT0_THRD                                     .assign    12 ;
;  mdm_regs.asm:         95 DEMINIT0_FRAC                                     .assign    11 ;
;  mdm_regs.asm:         96 DEMINIT0_FIDC                                     .assign    10 ;
;  mdm_regs.asm:         97 DEMINIT0_CHFI                                     .assign     9 ;
;  mdm_regs.asm:         98 DEMINIT0_BDEC                                     .assign     8 ;
;  mdm_regs.asm:         99 DEMINIT0_IQMC                                     .assign     7 ;
;  mdm_regs.asm:        100 DEMINIT0_MGE2                                     .assign     6 ;
;  mdm_regs.asm:        101 DEMINIT0_MGE1                                     .assign     5 ;
;  mdm_regs.asm:        102 DEMINIT0_RSVD                                     .assign     4 ;
;  mdm_regs.asm:        103 DEMINIT0_CODC                                     .assign     3 ;
;  mdm_regs.asm:        104 DEMINIT0_CMI4                                     .assign     2 ;
;  mdm_regs.asm:        105 DEMINIT0_CMIX                                     .assign     1 ;
;  mdm_regs.asm:        106 DEMINIT0_HILB                                     .assign     0 ;
;  mdm_regs.asm:        107 ; --------------------------------------------------------------
;  mdm_regs.asm:        108 ; DEMINIT1
;  mdm_regs.asm:        109 ; 
;  mdm_regs.asm:        110 DEMINIT1                                          .assign     6
;  mdm_regs.asm:        111 DEMINIT1_VITE                                     .assign    15 ;
;  mdm_regs.asm:        112 DEMINIT1_MLSE                                     .assign    14 ;
;  mdm_regs.asm:        113 DEMINIT1_SOFD                                     .assign    13 ;
;  mdm_regs.asm:        114 DEMINIT1_SWQU                                     .assign    12 ;
;  mdm_regs.asm:        115 DEMINIT1_MAFC                                     .assign    11 ;
;  mdm_regs.asm:        116 DEMINIT1_MAFI                                     .assign    10 ;
;  mdm_regs.asm:        117 DEMINIT1_FIFE                                     .assign     9 ;
;  mdm_regs.asm:        118 DEMINIT1_PDIF                                     .assign     8 ;
;  mdm_regs.asm:        119 DEMINIT1_CA2P                                     .assign     7 ;
;  mdm_regs.asm:        120 DEMINIT1_FECP                                     .assign     6 ;
;  mdm_regs.asm:        121 DEMINIT1_FEC5                                     .assign     5 ;
;  mdm_regs.asm:        122 DEMINIT1_C1BE                                     .assign     4 ;
;  mdm_regs.asm:        123 DEMINIT1_LQIE                                     .assign     3 ;
;  mdm_regs.asm:        124 DEMINIT1_F4BA                                     .assign     2 ;
;  mdm_regs.asm:        125 DEMINIT1_STIM                                     .assign     1 ;
;  mdm_regs.asm:        126 DEMINIT1_DSBU                                     .assign     0 ;
;  mdm_regs.asm:        127 ; --------------------------------------------------------------
;  mdm_regs.asm:        128 ; MCESTROBES0
;  mdm_regs.asm:        129 ; 
;  mdm_regs.asm:        130 MCESTROBES0                                       .assign     7
;  mdm_regs.asm:        131 MCESTROBES0_EVENT5                                .assign    12 ;
;  mdm_regs.asm:        132 MCESTROBES0_EVENT4                                .assign    11 ;
;  mdm_regs.asm:        133 MCESTROBES0_ROMDUMP                               .assign    10 ;
;  mdm_regs.asm:        134 MCESTROBES0_VITACCSTART                           .assign     9 ;
;  mdm_regs.asm:        135 MCESTROBES0_MLSETERM                              .assign     8 ;
;  mdm_regs.asm:        136 MCESTROBES0_EVENT3                                .assign     7 ;
;  mdm_regs.asm:        137 MCESTROBES0_EVENT2                                .assign     6 ;
;  mdm_regs.asm:        138 MCESTROBES0_EVENT1                                .assign     5 ;
;  mdm_regs.asm:        139 MCESTROBES0_EVENT0                                .assign     4 ;
;  mdm_regs.asm:        140 MCESTROBES0_MCETIMBALIGN                          .assign     3 ;
;  mdm_regs.asm:        141 MCESTROBES0_DSBURESTART                           .assign     2 ;
;  mdm_regs.asm:        142 MCESTROBES0_RSVD                                  .assign     1 ;
;  mdm_regs.asm:        143 MCESTROBES0_CMDDONE                               .assign     0 ;
;  mdm_regs.asm:        144 ; --------------------------------------------------------------
;  mdm_regs.asm:        145 ; MCESTROBES1
;  mdm_regs.asm:        146 ; 
;  mdm_regs.asm:        147 MCESTROBES1                                       .assign     8
;  mdm_regs.asm:        148 MCESTROBES1_C1BECOPYCMD2                          .assign    15 ;
;  mdm_regs.asm:        149 MCESTROBES1_C1BEPEAKGCMD                          .assign    14 ;
;  mdm_regs.asm:        150 MCESTROBES1_C1BEPEAKDECMD                         .assign    13 ;
;  mdm_regs.asm:        151 MCESTROBES1_C1BEPEAKFCMD                          .assign    12 ;
;  mdm_regs.asm:        152 MCESTROBES1_C1BEPEAKECMD                          .assign    11 ;
;  mdm_regs.asm:        153 MCESTROBES1_C1BEPEAKDCMD                          .assign    10 ;
;  mdm_regs.asm:        154 MCESTROBES1_C1BEPEAKABCMD                         .assign     9 ;
;  mdm_regs.asm:        155 MCESTROBES1_C1BEPEAKCCMD                          .assign     8 ;
;  mdm_regs.asm:        156 MCESTROBES1_C1BEPEAKBCMD                          .assign     7 ;
;  mdm_regs.asm:        157 MCESTROBES1_C1BEPEAKACMD                          .assign     6 ;
;  mdm_regs.asm:        158 MCESTROBES1_C1BEADVANCECMD                        .assign     5 ;
;  mdm_regs.asm:        159 MCESTROBES1_C1BESTALLCMD                          .assign     4 ;
;  mdm_regs.asm:        160 MCESTROBES1_C1BEROTCMD                            .assign     2 ;
;  mdm_regs.asm:        161 MCESTROBES1_C1BECOPYCMD                           .assign     1 ;
;  mdm_regs.asm:        162 MCESTROBES1_RESERVED                              .assign     0 ;
;  mdm_regs.asm:        163 ; --------------------------------------------------------------
;  mdm_regs.asm:        164 ; MCEEVENT0
;  mdm_regs.asm:        165 ; 
;  mdm_regs.asm:        166 MCEEVENT0                                         .assign     9
;  mdm_regs.asm:        167 MCEEVENT0_CL_RX_IRQ                               .assign    15 ;
;  mdm_regs.asm:        168 MCEEVENT0_DL_RX_IRQ                               .assign    14 ;
;  mdm_regs.asm:        169 MCEEVENT0_CL_TX_DONE                              .assign    13 ;
;  mdm_regs.asm:        170 MCEEVENT0_DL_TX_DONE                              .assign    12 ;
;  mdm_regs.asm:        171 MCEEVENT0_FRAC_EN                                 .assign    11 ;
;  mdm_regs.asm:        172 MCEEVENT0_BDEC_EN                                 .assign    10 ;
;  mdm_regs.asm:        173 MCEEVENT0_CPEFWEVENT1                             .assign     9 ;
;  mdm_regs.asm:        174 MCEEVENT0_CPEFWEVENT0                             .assign     8 ;
;  mdm_regs.asm:        175 MCEEVENT0_MDMFIFO_WR                              .assign     7 ;
;  mdm_regs.asm:        176 MCEEVENT0_COUNTER_IRQ                             .assign     6 ;
;  mdm_regs.asm:        177 MCEEVENT0_RFECMD_IRQ                              .assign     5 ;
;  mdm_regs.asm:        178 MCEEVENT0_FIFO_ERR_OVERFLOW                       .assign     4 ;
;  mdm_regs.asm:        179 MCEEVENT0_FIFO_ERR_UNDERFLOW                      .assign     3 ;
;  mdm_regs.asm:        180 MCEEVENT0_CLKEN_4BAUD                             .assign     2 ;
;  mdm_regs.asm:        181 MCEEVENT0_TIMER_IRQ                               .assign     1 ;
;  mdm_regs.asm:        182 MCEEVENT0_MDMAPI_WR                               .assign     0 ;
;  mdm_regs.asm:        183 ; --------------------------------------------------------------
;  mdm_regs.asm:        184 ; MCEEVENT1
;  mdm_regs.asm:        185 ; 
;  mdm_regs.asm:        186 MCEEVENT1                                         .assign    10
;  mdm_regs.asm:        187 MCEEVENT1_RAT_EVENT7                              .assign    15 ;
;  mdm_regs.asm:        188 MCEEVENT1_RAT_EVENT6                              .assign    14 ;
;  mdm_regs.asm:        189 MCEEVENT1_RAT_EVENT5                              .assign    13 ;
;  mdm_regs.asm:        190 MCEEVENT1_RAT_EVENT4                              .assign    12 ;
;  mdm_regs.asm:        191 MCEEVENT1_RAT_EVENT3                              .assign    11 ;
;  mdm_regs.asm:        192 MCEEVENT1_RAT_EVENT2                              .assign    10 ;
;  mdm_regs.asm:        193 MCEEVENT1_RAT_EVENT1                              .assign     9 ;
;  mdm_regs.asm:        194 MCEEVENT1_RAT_EVENT0                              .assign     8 ;
;  mdm_regs.asm:        195 MCEEVENT1_CLKEN_BAUD_F                            .assign     7 ;
;  mdm_regs.asm:        196 MCEEVENT1_MDMCMDPAR1_WR                           .assign     6 ;
;  mdm_regs.asm:        197 MCEEVENT1_MDMCMDPAR0_WR                           .assign     5 ;
;  mdm_regs.asm:        198 MCEEVENT1_VITACC                                  .assign     4 ;
;  mdm_regs.asm:        199 MCEEVENT1_FIFORD_VALID                            .assign     3 ;
;  mdm_regs.asm:        200 MCEEVENT1_FIFOWR_READY                            .assign     2 ;
;  mdm_regs.asm:        201 MCEEVENT1_CLKEN_BAUD                              .assign     1 ;
;  mdm_regs.asm:        202 MCEEVENT1_PREAMBLE_DONE                           .assign     0 ;
;  mdm_regs.asm:        203 ; --------------------------------------------------------------
;  mdm_regs.asm:        204 ; MCEEVENT2
;  mdm_regs.asm:        205 ; 
;  mdm_regs.asm:        206 MCEEVENT2                                         .assign    11
;  mdm_regs.asm:        207 MCEEVENT2_MDMGPI1                                 .assign    15 ;
;  mdm_regs.asm:        208 MCEEVENT2_MDMGPI0                                 .assign    14 ;
;  mdm_regs.asm:        209 MCEEVENT2_SWQU_SYNCED_IRQ                         .assign    13 ;
;  mdm_regs.asm:        210 MCEEVENT2_C1BE_B_LOADED                           .assign    12 ;
;  mdm_regs.asm:        211 MCEEVENT2_C1BE_CMB_ANY_PEAK                       .assign    11 ;
;  mdm_regs.asm:        212 MCEEVENT2_C1BE_CMB_NEG_PEAK                       .assign    10 ;
;  mdm_regs.asm:        213 MCEEVENT2_C1BE_CMB_POS_PEAK                       .assign     9 ;
;  mdm_regs.asm:        214 MCEEVENT2_C1BE_C_ANY_PEAK                         .assign     8 ;
;  mdm_regs.asm:        215 MCEEVENT2_C1BE_C_NEG_PEAK                         .assign     7 ;
;  mdm_regs.asm:        216 MCEEVENT2_C1BE_C_POS_PEAK                         .assign     6 ;
;  mdm_regs.asm:        217 MCEEVENT2_C1BE_B_ANY_PEAK                         .assign     5 ;
;  mdm_regs.asm:        218 MCEEVENT2_C1BE_B_NEG_PEAK                         .assign     4 ;
;  mdm_regs.asm:        219 MCEEVENT2_C1BE_B_POS_PEAK                         .assign     3 ;
;  mdm_regs.asm:        220 MCEEVENT2_C1BE_A_ANY_PEAK                         .assign     2 ;
;  mdm_regs.asm:        221 MCEEVENT2_C1BE_A_NEG_PEAK                         .assign     1 ;
;  mdm_regs.asm:        222 MCEEVENT2_C1BE_A_POS_PEAK                         .assign     0 ;
;  mdm_regs.asm:        223 ; --------------------------------------------------------------
;  mdm_regs.asm:        224 ; MCEEVENT3
;  mdm_regs.asm:        225 ; 
;  mdm_regs.asm:        226 MCEEVENT3                                         .assign    12
;  mdm_regs.asm:        227 MCEEVENT3_SWQU_FALSE_SYNC_IRQ                     .assign    15 ;
;  mdm_regs.asm:        228 MCEEVENT3_C1BE_G_ANY_PEAK                         .assign    14 ;
;  mdm_regs.asm:        229 MCEEVENT3_C1BE_G_NEG_PEAK                         .assign    13 ;
;  mdm_regs.asm:        230 MCEEVENT3_C1BE_G_POS_PEAK                         .assign    12 ;
;  mdm_regs.asm:        231 MCEEVENT3_C1BE_CMB_DE_ANY_PEAK                    .assign    11 ;
;  mdm_regs.asm:        232 MCEEVENT3_C1BE_CMB_DE_NEG_PEAK                    .assign    10 ;
;  mdm_regs.asm:        233 MCEEVENT3_C1BE_CMB_DE_POS_PEAK                    .assign     9 ;
;  mdm_regs.asm:        234 MCEEVENT3_C1BE_F_ANY_PEAK                         .assign     8 ;
;  mdm_regs.asm:        235 MCEEVENT3_C1BE_F_NEG_PEAK                         .assign     7 ;
;  mdm_regs.asm:        236 MCEEVENT3_C1BE_F_POS_PEAK                         .assign     6 ;
;  mdm_regs.asm:        237 MCEEVENT3_C1BE_E_ANY_PEAK                         .assign     5 ;
;  mdm_regs.asm:        238 MCEEVENT3_C1BE_E_NEG_PEAK                         .assign     4 ;
;  mdm_regs.asm:        239 MCEEVENT3_C1BE_E_POS_PEAK                         .assign     3 ;
;  mdm_regs.asm:        240 MCEEVENT3_C1BE_D_ANY_PEAK                         .assign     2 ;
;  mdm_regs.asm:        241 MCEEVENT3_C1BE_D_NEG_PEAK                         .assign     1 ;
;  mdm_regs.asm:        242 MCEEVENT3_C1BE_D_POS_PEAK                         .assign     0 ;
;  mdm_regs.asm:        243 ; --------------------------------------------------------------
;  mdm_regs.asm:        244 ; MCEEVENTMSK0
;  mdm_regs.asm:        245 ; 
;  mdm_regs.asm:        246 MCEEVENTMSK0                                      .assign    13
;  mdm_regs.asm:        247 MCEEVENTMSK0_CL_RX_IRQ                            .assign    15 ;
;  mdm_regs.asm:        248 MCEEVENTMSK0_DL_RX_IRQ                            .assign    14 ;
;  mdm_regs.asm:        249 MCEEVENTMSK0_CL_TX_DONE                           .assign    13 ;
;  mdm_regs.asm:        250 MCEEVENTMSK0_DL_TX_DONE                           .assign    12 ;
;  mdm_regs.asm:        251 MCEEVENTMSK0_FRAC_EN                              .assign    11 ;
;  mdm_regs.asm:        252 MCEEVENTMSK0_BDEC_EN                              .assign    10 ;
;  mdm_regs.asm:        253 MCEEVENTMSK0_CPEFWEVENT1                          .assign     9 ;
;  mdm_regs.asm:        254 MCEEVENTMSK0_CPEFWEVENT0                          .assign     8 ;
;  mdm_regs.asm:        255 MCEEVENTMSK0_MDMFIFO_WR                           .assign     7 ;
;  mdm_regs.asm:        256 MCEEVENTMSK0_COUNTER_IRQ                          .assign     6 ;
;  mdm_regs.asm:        257 MCEEVENTMSK0_RFECMD_IRQ                           .assign     5 ;
;  mdm_regs.asm:        258 MCEEVENTMSK0_FIFO_ERR_OVERFLOW                    .assign     4 ;
;  mdm_regs.asm:        259 MCEEVENTMSK0_FIFO_ERR_UNDERFLOW                   .assign     3 ;
;  mdm_regs.asm:        260 MCEEVENTMSK0_CLKEN_4BAUD                          .assign     2 ;
;  mdm_regs.asm:        261 MCEEVENTMSK0_TIMER_IRQ                            .assign     1 ;
;  mdm_regs.asm:        262 MCEEVENTMSK0_MDMAPI_WR                            .assign     0 ;
;  mdm_regs.asm:        263 ; --------------------------------------------------------------
;  mdm_regs.asm:        264 ; MCEEVENTMSK1
;  mdm_regs.asm:        265 ; 
;  mdm_regs.asm:        266 MCEEVENTMSK1                                      .assign    14
;  mdm_regs.asm:        267 MCEEVENTMSK1_RAT_EVENT7                           .assign    15 ;
;  mdm_regs.asm:        268 MCEEVENTMSK1_RAT_EVENT6                           .assign    14 ;
;  mdm_regs.asm:        269 MCEEVENTMSK1_RAT_EVENT5                           .assign    13 ;
;  mdm_regs.asm:        270 MCEEVENTMSK1_RAT_EVENT4                           .assign    12 ;
;  mdm_regs.asm:        271 MCEEVENTMSK1_RAT_EVENT3                           .assign    11 ;
;  mdm_regs.asm:        272 MCEEVENTMSK1_RAT_EVENT2                           .assign    10 ;
;  mdm_regs.asm:        273 MCEEVENTMSK1_RAT_EVENT1                           .assign     9 ;
;  mdm_regs.asm:        274 MCEEVENTMSK1_RAT_EVENT0                           .assign     8 ;
;  mdm_regs.asm:        275 MCEEVENTMSK1_CLKEN_BAUD_F                         .assign     7 ;
;  mdm_regs.asm:        276 MCEEVENTMSK1_MDMCMDPAR1_WR                        .assign     6 ;
;  mdm_regs.asm:        277 MCEEVENTMSK1_MDMCMDPAR0_WR                        .assign     5 ;
;  mdm_regs.asm:        278 MCEEVENTMSK1_VITACC                               .assign     4 ;
;  mdm_regs.asm:        279 MCEEVENTMSK1_FIFORD_VALID                         .assign     3 ;
;  mdm_regs.asm:        280 MCEEVENTMSK1_FIFOWR_READY                         .assign     2 ;
;  mdm_regs.asm:        281 MCEEVENTMSK1_CLKEN_BAUD                           .assign     1 ;
;  mdm_regs.asm:        282 MCEEVENTMSK1_PREAMBLE_DONE                        .assign     0 ;
;  mdm_regs.asm:        283 ; --------------------------------------------------------------
;  mdm_regs.asm:        284 ; MCEEVENTMSK2
;  mdm_regs.asm:        285 ; 
;  mdm_regs.asm:        286 MCEEVENTMSK2                                      .assign    15
;  mdm_regs.asm:        287 MCEEVENTMSK2_MDMGPI1                              .assign    15 ;
;  mdm_regs.asm:        288 MCEEVENTMSK2_MDMGPI0                              .assign    14 ;
;  mdm_regs.asm:        289 MCEEVENTMSK2_SWQU_SYNCED_IRQ                      .assign    13 ;
;  mdm_regs.asm:        290 MCEEVENTMSK2_C1BE_B_LOADED                        .assign    12 ;
;  mdm_regs.asm:        291 MCEEVENTMSK2_C1BE_CMB_ANY_PEAK                    .assign    11 ;
;  mdm_regs.asm:        292 MCEEVENTMSK2_C1BE_CMB_NEG_PEAK                    .assign    10 ;
;  mdm_regs.asm:        293 MCEEVENTMSK2_C1BE_CMB_POS_PEAK                    .assign     9 ;
;  mdm_regs.asm:        294 MCEEVENTMSK2_C1BE_C_ANY_PEAK                      .assign     8 ;
;  mdm_regs.asm:        295 MCEEVENTMSK2_C1BE_C_NEG_PEAK                      .assign     7 ;
;  mdm_regs.asm:        296 MCEEVENTMSK2_C1BE_C_POS_PEAK                      .assign     6 ;
;  mdm_regs.asm:        297 MCEEVENTMSK2_C1BE_B_ANY_PEAK                      .assign     5 ;
;  mdm_regs.asm:        298 MCEEVENTMSK2_C1BE_B_NEG_PEAK                      .assign     4 ;
;  mdm_regs.asm:        299 MCEEVENTMSK2_C1BE_B_POS_PEAK                      .assign     3 ;
;  mdm_regs.asm:        300 MCEEVENTMSK2_C1BE_A_ANY_PEAK                      .assign     2 ;
;  mdm_regs.asm:        301 MCEEVENTMSK2_C1BE_A_NEG_PEAK                      .assign     1 ;
;  mdm_regs.asm:        302 MCEEVENTMSK2_C1BE_A_POS_PEAK                      .assign     0 ;
;  mdm_regs.asm:        303 ; --------------------------------------------------------------
;  mdm_regs.asm:        304 ; MCEEVENTMSK3
;  mdm_regs.asm:        305 ; 
;  mdm_regs.asm:        306 MCEEVENTMSK3                                      .assign    16
;  mdm_regs.asm:        307 MCEEVENTMSK3_SWQU_FALSE_SYNC_IRQ                  .assign    15 ;
;  mdm_regs.asm:        308 MCEEVENTMSK3_C1BE_G_ANY_PEAK                      .assign    14 ;
;  mdm_regs.asm:        309 MCEEVENTMSK3_C1BE_G_NEG_PEAK                      .assign    13 ;
;  mdm_regs.asm:        310 MCEEVENTMSK3_C1BE_G_POS_PEAK                      .assign    12 ;
;  mdm_regs.asm:        311 MCEEVENTMSK3_C1BE_CMB_DE_ANY_PEAK                 .assign    11 ;
;  mdm_regs.asm:        312 MCEEVENTMSK3_C1BE_CMB_DE_NEG_PEAK                 .assign    10 ;
;  mdm_regs.asm:        313 MCEEVENTMSK3_C1BE_CMB_DE_POS_PEAK                 .assign     9 ;
;  mdm_regs.asm:        314 MCEEVENTMSK3_C1BE_F_ANY_PEAK                      .assign     8 ;
;  mdm_regs.asm:        315 MCEEVENTMSK3_C1BE_F_NEG_PEAK                      .assign     7 ;
;  mdm_regs.asm:        316 MCEEVENTMSK3_C1BE_F_POS_PEAK                      .assign     6 ;
;  mdm_regs.asm:        317 MCEEVENTMSK3_C1BE_E_ANY_PEAK                      .assign     5 ;
;  mdm_regs.asm:        318 MCEEVENTMSK3_C1BE_E_NEG_PEAK                      .assign     4 ;
;  mdm_regs.asm:        319 MCEEVENTMSK3_C1BE_E_POS_PEAK                      .assign     3 ;
;  mdm_regs.asm:        320 MCEEVENTMSK3_C1BE_D_ANY_PEAK                      .assign     2 ;
;  mdm_regs.asm:        321 MCEEVENTMSK3_C1BE_D_NEG_PEAK                      .assign     1 ;
;  mdm_regs.asm:        322 MCEEVENTMSK3_C1BE_D_POS_PEAK                      .assign     0 ;
;  mdm_regs.asm:        323 ; --------------------------------------------------------------
;  mdm_regs.asm:        324 ; MCEEVENTCLR0
;  mdm_regs.asm:        325 ; 
;  mdm_regs.asm:        326 MCEEVENTCLR0                                      .assign    17
;  mdm_regs.asm:        327 MCEEVENTCLR0_CL_RX_IRQ                            .assign    15 ;
;  mdm_regs.asm:        328 MCEEVENTCLR0_DL_RX_IRQ                            .assign    14 ;
;  mdm_regs.asm:        329 MCEEVENTCLR0_CL_TX_DONE                           .assign    13 ;
;  mdm_regs.asm:        330 MCEEVENTCLR0_DL_TX_DONE                           .assign    12 ;
;  mdm_regs.asm:        331 MCEEVENTCLR0_FRAC_EN                              .assign    11 ;
;  mdm_regs.asm:        332 MCEEVENTCLR0_BDEC_EN                              .assign    10 ;
;  mdm_regs.asm:        333 MCEEVENTCLR0_CPEFWEVENT1                          .assign     9 ;
;  mdm_regs.asm:        334 MCEEVENTCLR0_CPEFWEVENT0                          .assign     8 ;
;  mdm_regs.asm:        335 MCEEVENTCLR0_MDMFIFO_WR                           .assign     7 ;
;  mdm_regs.asm:        336 MCEEVENTCLR0_COUNTER_IRQ                          .assign     6 ;
;  mdm_regs.asm:        337 MCEEVENTCLR0_RFECMD_IRQ                           .assign     5 ;
;  mdm_regs.asm:        338 MCEEVENTCLR0_FIFO_ERR_OVERFLOW                    .assign     4 ;
;  mdm_regs.asm:        339 MCEEVENTCLR0_FIFO_ERR_UNDERFLOW                   .assign     3 ;
;  mdm_regs.asm:        340 MCEEVENTCLR0_CLKEN_4BAUD                          .assign     2 ;
;  mdm_regs.asm:        341 MCEEVENTCLR0_TIMER_IRQ                            .assign     1 ;
;  mdm_regs.asm:        342 MCEEVENTCLR0_MDMAPI_WR                            .assign     0 ;
;  mdm_regs.asm:        343 ; --------------------------------------------------------------
;  mdm_regs.asm:        344 ; MCEEVENTCLR1
;  mdm_regs.asm:        345 ; 
;  mdm_regs.asm:        346 MCEEVENTCLR1                                      .assign    18
;  mdm_regs.asm:        347 MCEEVENTCLR1_RAT_EVENT7                           .assign    15 ;
;  mdm_regs.asm:        348 MCEEVENTCLR1_RAT_EVENT6                           .assign    14 ;
;  mdm_regs.asm:        349 MCEEVENTCLR1_RAT_EVENT5                           .assign    13 ;
;  mdm_regs.asm:        350 MCEEVENTCLR1_RAT_EVENT4                           .assign    12 ;
;  mdm_regs.asm:        351 MCEEVENTCLR1_RAT_EVENT3                           .assign    11 ;
;  mdm_regs.asm:        352 MCEEVENTCLR1_RAT_EVENT2                           .assign    10 ;
;  mdm_regs.asm:        353 MCEEVENTCLR1_RAT_EVENT1                           .assign     9 ;
;  mdm_regs.asm:        354 MCEEVENTCLR1_RAT_EVENT0                           .assign     8 ;
;  mdm_regs.asm:        355 MCEEVENTCLR1_CLKEN_BAUD_F                         .assign     7 ;
;  mdm_regs.asm:        356 MCEEVENTCLR1_MDMCMDPAR1_WR                        .assign     6 ;
;  mdm_regs.asm:        357 MCEEVENTCLR1_MDMCMDPAR0_WR                        .assign     5 ;
;  mdm_regs.asm:        358 MCEEVENTCLR1_VITACC                               .assign     4 ;
;  mdm_regs.asm:        359 MCEEVENTCLR1_FIFORD_VALID                         .assign     3 ;
;  mdm_regs.asm:        360 MCEEVENTCLR1_FIFOWR_READY                         .assign     2 ;
;  mdm_regs.asm:        361 MCEEVENTCLR1_CLKEN_BAUD                           .assign     1 ;
;  mdm_regs.asm:        362 MCEEVENTCLR1_PREAMBLE_DONE                        .assign     0 ;
;  mdm_regs.asm:        363 ; --------------------------------------------------------------
;  mdm_regs.asm:        364 ; MCEEVENTCLR2
;  mdm_regs.asm:        365 ; 
;  mdm_regs.asm:        366 MCEEVENTCLR2                                      .assign    19
;  mdm_regs.asm:        367 MCEEVENTCLR2_MDMGPI1                              .assign    15 ;
;  mdm_regs.asm:        368 MCEEVENTCLR2_MDMGPI0                              .assign    14 ;
;  mdm_regs.asm:        369 MCEEVENTCLR2_SWQU_SYNCED_IRQ                      .assign    13 ;
;  mdm_regs.asm:        370 MCEEVENTCLR2_C1BE_B_LOADED                        .assign    12 ;
;  mdm_regs.asm:        371 MCEEVENTCLR2_C1BE_CMB_ANY_PEAK                    .assign    11 ;
;  mdm_regs.asm:        372 MCEEVENTCLR2_C1BE_CMB_NEG_PEAK                    .assign    10 ;
;  mdm_regs.asm:        373 MCEEVENTCLR2_C1BE_CMB_POS_PEAK                    .assign     9 ;
;  mdm_regs.asm:        374 MCEEVENTCLR2_C1BE_C_ANY_PEAK                      .assign     8 ;
;  mdm_regs.asm:        375 MCEEVENTCLR2_C1BE_C_NEG_PEAK                      .assign     7 ;
;  mdm_regs.asm:        376 MCEEVENTCLR2_C1BE_C_POS_PEAK                      .assign     6 ;
;  mdm_regs.asm:        377 MCEEVENTCLR2_C1BE_B_ANY_PEAK                      .assign     5 ;
;  mdm_regs.asm:        378 MCEEVENTCLR2_C1BE_B_NEG_PEAK                      .assign     4 ;
;  mdm_regs.asm:        379 MCEEVENTCLR2_C1BE_B_POS_PEAK                      .assign     3 ;
;  mdm_regs.asm:        380 MCEEVENTCLR2_C1BE_A_ANY_PEAK                      .assign     2 ;
;  mdm_regs.asm:        381 MCEEVENTCLR2_C1BE_A_NEG_PEAK                      .assign     1 ;
;  mdm_regs.asm:        382 MCEEVENTCLR2_C1BE_A_POS_PEAK                      .assign     0 ;
;  mdm_regs.asm:        383 ; --------------------------------------------------------------
;  mdm_regs.asm:        384 ; MCEEVENTCLR3
;  mdm_regs.asm:        385 ; 
;  mdm_regs.asm:        386 MCEEVENTCLR3                                      .assign    20
;  mdm_regs.asm:        387 MCEEVENTCLR3_SWQU_FALSE_SYNC_IRQ                  .assign    15 ;
;  mdm_regs.asm:        388 MCEEVENTCLR3_C1BE_G_ANY_PEAK                      .assign    14 ;
;  mdm_regs.asm:        389 MCEEVENTCLR3_C1BE_G_NEG_PEAK                      .assign    13 ;
;  mdm_regs.asm:        390 MCEEVENTCLR3_C1BE_G_POS_PEAK                      .assign    12 ;
;  mdm_regs.asm:        391 MCEEVENTCLR3_C1BE_CMB_DE_ANY_PEAK                 .assign    11 ;
;  mdm_regs.asm:        392 MCEEVENTCLR3_C1BE_CMB_DE_NEG_PEAK                 .assign    10 ;
;  mdm_regs.asm:        393 MCEEVENTCLR3_C1BE_CMB_DE_POS_PEAK                 .assign     9 ;
;  mdm_regs.asm:        394 MCEEVENTCLR3_C1BE_F_ANY_PEAK                      .assign     8 ;
;  mdm_regs.asm:        395 MCEEVENTCLR3_C1BE_F_NEG_PEAK                      .assign     7 ;
;  mdm_regs.asm:        396 MCEEVENTCLR3_C1BE_F_POS_PEAK                      .assign     6 ;
;  mdm_regs.asm:        397 MCEEVENTCLR3_C1BE_E_ANY_PEAK                      .assign     5 ;
;  mdm_regs.asm:        398 MCEEVENTCLR3_C1BE_E_NEG_PEAK                      .assign     4 ;
;  mdm_regs.asm:        399 MCEEVENTCLR3_C1BE_E_POS_PEAK                      .assign     3 ;
;  mdm_regs.asm:        400 MCEEVENTCLR3_C1BE_D_ANY_PEAK                      .assign     2 ;
;  mdm_regs.asm:        401 MCEEVENTCLR3_C1BE_D_NEG_PEAK                      .assign     1 ;
;  mdm_regs.asm:        402 MCEEVENTCLR3_C1BE_D_POS_PEAK                      .assign     0 ;
;  mdm_regs.asm:        403 ; --------------------------------------------------------------
;  mdm_regs.asm:        404 ; MCEPROGRAMSRC
;  mdm_regs.asm:        405 ; 
;  mdm_regs.asm:        406 MCEPROGRAMSRC                                     .assign    21
;  mdm_regs.asm:        407 MCEPROGRAMSRC_ROMBANK                             .assign     1 ;
;  mdm_regs.asm:        408 MCEPROGRAMSRC_RAMROM                              .assign     0 ;
;  mdm_regs.asm:        409 ; --------------------------------------------------------------
;  mdm_regs.asm:        410 ; MDMAPI
;  mdm_regs.asm:        411 ; 
;  mdm_regs.asm:        412 MDMAPI                                            .assign    22
;  mdm_regs.asm:        413 MDMAPI_PROTOCOLID                                 .assign     8 ;
;  mdm_regs.asm:        414 MDMAPI_MDMCMD                                     .assign     0 ;
;  mdm_regs.asm:        415 ; --------------------------------------------------------------
;  mdm_regs.asm:        416 ; MDMCMDPAR0
;  mdm_regs.asm:        417 ; 
;  mdm_regs.asm:        418 MDMCMDPAR0                                        .assign    23
;  mdm_regs.asm:        419 MDMCMDPAR0_PAR0                                   .assign     0 ;
;  mdm_regs.asm:        420 ; --------------------------------------------------------------
;  mdm_regs.asm:        421 ; MDMCMDPAR1
;  mdm_regs.asm:        422 ; 
;  mdm_regs.asm:        423 MDMCMDPAR1                                        .assign    24
;  mdm_regs.asm:        424 MDMCMDPAR1_PAR1                                   .assign     0 ;
;  mdm_regs.asm:        425 ; --------------------------------------------------------------
;  mdm_regs.asm:        426 ; MDMCMDPAR2
;  mdm_regs.asm:        427 ; 
;  mdm_regs.asm:        428 MDMCMDPAR2                                        .assign    25
;  mdm_regs.asm:        429 MDMCMDPAR2_PAR                                    .assign     0 ;
;  mdm_regs.asm:        430 ; --------------------------------------------------------------
;  mdm_regs.asm:        431 ; MDMRFCHANNEL
;  mdm_regs.asm:        432 ; 
;  mdm_regs.asm:        433 MDMRFCHANNEL                                      .assign    26
;  mdm_regs.asm:        434 MDMRFCHANNEL_VALUE                                .assign     0 ;
;  mdm_regs.asm:        435 ; --------------------------------------------------------------
;  mdm_regs.asm:        436 ; MDMSTATUS
;  mdm_regs.asm:        437 ; 
;  mdm_regs.asm:        438 MDMSTATUS                                         .assign    27
;  mdm_regs.asm:        439 MDMSTATUS_VALUE                                   .assign     0 ;
;  mdm_regs.asm:        440 ; --------------------------------------------------------------
;  mdm_regs.asm:        441 ; MDMFIFOWR
;  mdm_regs.asm:        442 ; 
;  mdm_regs.asm:        443 MDMFIFOWR                                         .assign    28
;  mdm_regs.asm:        444 MDMFIFOWR_PAYLOADIN                               .assign     0 ;
;  mdm_regs.asm:        445 ; --------------------------------------------------------------
;  mdm_regs.asm:        446 ; MDMFIFORD
;  mdm_regs.asm:        447 ; 
;  mdm_regs.asm:        448 MDMFIFORD                                         .assign    29
;  mdm_regs.asm:        449 MDMFIFORD_PAYLOADOUT                              .assign     0 ;
;  mdm_regs.asm:        450 ; --------------------------------------------------------------
;  mdm_regs.asm:        451 ; MDMFIFOWRCTRL
;  mdm_regs.asm:        452 ; 
;  mdm_regs.asm:        453 MDMFIFOWRCTRL                                     .assign    30
;  mdm_regs.asm:        454 MDMFIFOWRCTRL_FIFOWRPORT                          .assign     4 ;
;  mdm_regs.asm:        455 MDMFIFOWRCTRL_WORDSZWR                            .assign     0 ;
;  mdm_regs.asm:        456 ; --------------------------------------------------------------
;  mdm_regs.asm:        457 ; MDMFIFORDCTRL
;  mdm_regs.asm:        458 ; 
;  mdm_regs.asm:        459 MDMFIFORDCTRL                                     .assign    31
;  mdm_regs.asm:        460 MDMFIFORDCTRL_FIFORDPORT                          .assign     4 ;
;  mdm_regs.asm:        461 MDMFIFORDCTRL_WORDSZRD                            .assign     0 ;
;  mdm_regs.asm:        462 ; --------------------------------------------------------------
;  mdm_regs.asm:        463 ; MDMFIFOCFG
;  mdm_regs.asm:        464 ; 
;  mdm_regs.asm:        465 MDMFIFOCFG                                        .assign    32
;  mdm_regs.asm:        466 MDMFIFOCFG_AFULLTHR                               .assign     8 ;
;  mdm_regs.asm:        467 MDMFIFOCFG_AEMPTYTHR                              .assign     0 ;
;  mdm_regs.asm:        468 ; --------------------------------------------------------------
;  mdm_regs.asm:        469 ; MDMFIFOSTA
;  mdm_regs.asm:        470 ; 
;  mdm_regs.asm:        471 MDMFIFOSTA                                        .assign    33
;  mdm_regs.asm:        472 MDMFIFOSTA_OVERFLOW                               .assign     5 ;
;  mdm_regs.asm:        473 MDMFIFOSTA_ALMOSTFULL                             .assign     4 ;
;  mdm_regs.asm:        474 MDMFIFOSTA_ALMOSTEMPTY                            .assign     3 ;
;  mdm_regs.asm:        475 MDMFIFOSTA_UNDERFLOW                              .assign     2 ;
;  mdm_regs.asm:        476 MDMFIFOSTA_RXVALID                                .assign     1 ;
;  mdm_regs.asm:        477 MDMFIFOSTA_TXREADY                                .assign     0 ;
;  mdm_regs.asm:        478 ; --------------------------------------------------------------
;  mdm_regs.asm:        479 ; CPEFWEVENT
;  mdm_regs.asm:        480 ; 
;  mdm_regs.asm:        481 CPEFWEVENT                                        .assign    34
;  mdm_regs.asm:        482 CPEFWEVENT_EVENT3                                 .assign     3 ;
;  mdm_regs.asm:        483 CPEFWEVENT_EVENT2                                 .assign     2 ;
;  mdm_regs.asm:        484 CPEFWEVENT_EVENT1                                 .assign     1 ;
;  mdm_regs.asm:        485 CPEFWEVENT_EVENT0                                 .assign     0 ;
;  mdm_regs.asm:        486 ; --------------------------------------------------------------
;  mdm_regs.asm:        487 ; RFESEND
;  mdm_regs.asm:        488 ; 
;  mdm_regs.asm:        489 RFESEND                                           .assign    35
;  mdm_regs.asm:        490 RFESEND_MCECMD                                    .assign     0 ;
;  mdm_regs.asm:        491 ; --------------------------------------------------------------
;  mdm_regs.asm:        492 ; RFERCEV
;  mdm_regs.asm:        493 ; 
;  mdm_regs.asm:        494 RFERCEV                                           .assign    36
;  mdm_regs.asm:        495 RFERCEV_RFECMD                                    .assign     0 ;
;  mdm_regs.asm:        496 ; --------------------------------------------------------------
;  mdm_regs.asm:        497 ; SMICONF
;  mdm_regs.asm:        498 ; 
;  mdm_regs.asm:        499 SMICONF                                           .assign    37
;  mdm_regs.asm:        500 SMICONF_SMIENABLE                                 .assign     8 ;
;  mdm_regs.asm:        501 SMICONF_PRESCALER                                 .assign     4 ;
;  mdm_regs.asm:        502 SMICONF_MLENGTH                                   .assign     0 ;
;  mdm_regs.asm:        503 ; --------------------------------------------------------------
;  mdm_regs.asm:        504 ; SMIDLOUTG
;  mdm_regs.asm:        505 ; 
;  mdm_regs.asm:        506 SMIDLOUTG                                         .assign    38
;  mdm_regs.asm:        507 SMIDLOUTG_DL                                      .assign     0 ;
;  mdm_regs.asm:        508 ; --------------------------------------------------------------
;  mdm_regs.asm:        509 ; SMICLOUTG
;  mdm_regs.asm:        510 ; 
;  mdm_regs.asm:        511 SMICLOUTG                                         .assign    39
;  mdm_regs.asm:        512 SMICLOUTG_CL                                      .assign     0 ;
;  mdm_regs.asm:        513 ; --------------------------------------------------------------
;  mdm_regs.asm:        514 ; SMIDLINC
;  mdm_regs.asm:        515 ; 
;  mdm_regs.asm:        516 SMIDLINC                                          .assign    40
;  mdm_regs.asm:        517 SMIDLINC_DL                                       .assign     0 ;
;  mdm_regs.asm:        518 ; --------------------------------------------------------------
;  mdm_regs.asm:        519 ; SMICLINC
;  mdm_regs.asm:        520 ; 
;  mdm_regs.asm:        521 SMICLINC                                          .assign    41
;  mdm_regs.asm:        522 SMICLINC_CL                                       .assign     0 ;
;  mdm_regs.asm:        523 ; --------------------------------------------------------------
;  mdm_regs.asm:        524 ; SMISTA
;  mdm_regs.asm:        525 ; 
;  mdm_regs.asm:        526 SMISTA                                            .assign    42
;  mdm_regs.asm:        527 SMISTA_INCCLERROR                                 .assign     1 ;
;  mdm_regs.asm:        528 SMISTA_INCDLERROR                                 .assign     0 ;
;  mdm_regs.asm:        529 ; --------------------------------------------------------------
;  mdm_regs.asm:        530 ; ADCDIGCONF
;  mdm_regs.asm:        531 ; 
;  mdm_regs.asm:        532 ADCDIGCONF                                        .assign    43
;  mdm_regs.asm:        533 ADCDIGCONF_QBRANCHEN                              .assign     1 ;
;  mdm_regs.asm:        534 ADCDIGCONF_IBRANCHEN                              .assign     0 ;
;  mdm_regs.asm:        535 ; --------------------------------------------------------------
;  mdm_regs.asm:        536 ; MODPRECTRL
;  mdm_regs.asm:        537 ; 
;  mdm_regs.asm:        538 MODPRECTRL                                        .assign    44
;  mdm_regs.asm:        539 MODPRECTRL_REPS                                   .assign     4 ;
;  mdm_regs.asm:        540 MODPRECTRL_SIZE                                   .assign     0 ;
;  mdm_regs.asm:        541 ; --------------------------------------------------------------
;  mdm_regs.asm:        542 ; MODSYMMAP0
;  mdm_regs.asm:        543 ; 
;  mdm_regs.asm:        544 MODSYMMAP0                                        .assign    45
;  mdm_regs.asm:        545 MODSYMMAP0_SYM3                                   .assign    12 ;
;  mdm_regs.asm:        546 MODSYMMAP0_SYM2                                   .assign     8 ;
;  mdm_regs.asm:        547 MODSYMMAP0_SYM1                                   .assign     4 ;
;  mdm_regs.asm:        548 MODSYMMAP0_SYM0                                   .assign     0 ;
;  mdm_regs.asm:        549 ; --------------------------------------------------------------
;  mdm_regs.asm:        550 ; MODSYMMAP1
;  mdm_regs.asm:        551 ; 
;  mdm_regs.asm:        552 MODSYMMAP1                                        .assign    46
;  mdm_regs.asm:        553 MODSYMMAP1_SYM7                                   .assign    12 ;
;  mdm_regs.asm:        554 MODSYMMAP1_SYM6                                   .assign     8 ;
;  mdm_regs.asm:        555 MODSYMMAP1_SYM5                                   .assign     4 ;
;  mdm_regs.asm:        556 MODSYMMAP1_SYM4                                   .assign     0 ;
;  mdm_regs.asm:        557 ; --------------------------------------------------------------
;  mdm_regs.asm:        558 ; MODSOFTTX
;  mdm_regs.asm:        559 ; 
;  mdm_regs.asm:        560 MODSOFTTX                                         .assign    47
;  mdm_regs.asm:        561 MODSOFTTX_SOFTSYMBOL                              .assign     0 ;
;  mdm_regs.asm:        562 ; --------------------------------------------------------------
;  mdm_regs.asm:        563 ; MDMBAUD
;  mdm_regs.asm:        564 ; 
;  mdm_regs.asm:        565 MDMBAUD                                           .assign    48
;  mdm_regs.asm:        566 MDMBAUD_RATEWORD                                  .assign     0 ;
;  mdm_regs.asm:        567 ; --------------------------------------------------------------
;  mdm_regs.asm:        568 ; MDMBAUDPRE
;  mdm_regs.asm:        569 ; 
;  mdm_regs.asm:        570 MDMBAUDPRE                                        .assign    49
;  mdm_regs.asm:        571 MDMBAUDPRE_ALIGNVALUE                             .assign    13 ;
;  mdm_regs.asm:        572 MDMBAUDPRE_EXTRATEWORD                            .assign     8 ;
;  mdm_regs.asm:        573 MDMBAUDPRE_PRESCALER                              .assign     0 ;
;  mdm_regs.asm:        574 ; --------------------------------------------------------------
;  mdm_regs.asm:        575 ; MODMAIN
;  mdm_regs.asm:        576 ; 
;  mdm_regs.asm:        577 MODMAIN                                           .assign    50
;  mdm_regs.asm:        578 MODMAIN_SPREADFACTOR                              .assign     6 ;
;  mdm_regs.asm:        579 MODMAIN_FECSELECT                                 .assign     2 ;
;  mdm_regs.asm:        580 MODMAIN_MODLEVELS                                 .assign     0 ;
;  mdm_regs.asm:        581 ; --------------------------------------------------------------
;  mdm_regs.asm:        582 ; DEMMISC0
;  mdm_regs.asm:        583 ; 
;  mdm_regs.asm:        584 DEMMISC0                                          .assign    51
;  mdm_regs.asm:        585 DEMMISC0_CMI4FMIXSIGN                             .assign    12 ;
;  mdm_regs.asm:        586 DEMMISC0_HILBREMOVEREAL                           .assign    11 ;
;  mdm_regs.asm:        587 DEMMISC0_HILBEN                                   .assign    10 ;
;  mdm_regs.asm:        588 DEMMISC0_CMIXN                                    .assign     0 ;
;  mdm_regs.asm:        589 ; --------------------------------------------------------------
;  mdm_regs.asm:        590 ; DEMMISC1
;  mdm_regs.asm:        591 ; 
;  mdm_regs.asm:        592 DEMMISC1                                          .assign    52
;  mdm_regs.asm:        593 DEMMISC1_MGE2SRCSEL                               .assign     2 ;
;  mdm_regs.asm:        594 DEMMISC1_CHFIBW                                   .assign     0 ;
;  mdm_regs.asm:        595 ; --------------------------------------------------------------
;  mdm_regs.asm:        596 ; DEMMISC2
;  mdm_regs.asm:        597 ; 
;  mdm_regs.asm:        598 DEMMISC2                                          .assign    53
;  mdm_regs.asm:        599 DEMMISC2_LQIPERIOD                                .assign    14 ;
;  mdm_regs.asm:        600 DEMMISC2_MLSERUN                                  .assign    13 ;
;  mdm_regs.asm:        601 DEMMISC2_MAFCGAIN                                 .assign    11 ;
;  mdm_regs.asm:        602 DEMMISC2_STIMESTONLY                              .assign    10 ;
;  mdm_regs.asm:        603 DEMMISC2_STIMTEAPERIOD                            .assign     7 ;
;  mdm_regs.asm:        604 DEMMISC2_STIMTEAGAIN                              .assign     4 ;
;  mdm_regs.asm:        605 DEMMISC2_PDIFLINPREDEN                            .assign     3 ;
;  mdm_regs.asm:        606 DEMMISC2_PDIFDESPECKLEREN                         .assign     2 ;
;  mdm_regs.asm:        607 DEMMISC2_PDIFIQCONJEN                             .assign     1 ;
;  mdm_regs.asm:        608 DEMMISC2_PDIFLIMITRANGE                           .assign     0 ;
;  mdm_regs.asm:        609 ; --------------------------------------------------------------
;  mdm_regs.asm:        610 ; DEMMISC3
;  mdm_regs.asm:        611 ; 
;  mdm_regs.asm:        612 DEMMISC3                                          .assign    54
;  mdm_regs.asm:        613 DEMMISC3_BDE1DVGA                                 .assign    10 ;
;  mdm_regs.asm:        614 DEMMISC3_BDE2DVGA                                 .assign     8 ;
;  mdm_regs.asm:        615 DEMMISC3_BDE1NUMSTAGES                            .assign     5 ;
;  mdm_regs.asm:        616 DEMMISC3_PDIFDECIM                                .assign     3 ;
;  mdm_regs.asm:        617 DEMMISC3_BDECNUMSTAGES                            .assign     0 ;
;  mdm_regs.asm:        618 ; --------------------------------------------------------------
;  mdm_regs.asm:        619 ; DEMIQMC0
;  mdm_regs.asm:        620 ; 
;  mdm_regs.asm:        621 DEMIQMC0                                          .assign    55
;  mdm_regs.asm:        622 DEMIQMC0_GAINFACTOR                               .assign     8 ;
;  mdm_regs.asm:        623 DEMIQMC0_PHASEFACTOR                              .assign     0 ;
;  mdm_regs.asm:        624 ; --------------------------------------------------------------
;  mdm_regs.asm:        625 ; DEMDSBU
;  mdm_regs.asm:        626 ; 
;  mdm_regs.asm:        627 DEMDSBU                                           .assign    56
;  mdm_regs.asm:        628 DEMDSBU_DSBUDELAY                                 .assign     0 ;
;  mdm_regs.asm:        629 ; --------------------------------------------------------------
;  mdm_regs.asm:        630 ; DEMDSBU2
;  mdm_regs.asm:        631 ; 
;  mdm_regs.asm:        632 DEMDSBU2                                          .assign    57
;  mdm_regs.asm:        633 DEMDSBU2_DSBUAVGLENGTH                            .assign     0 ;
;  mdm_regs.asm:        634 ; --------------------------------------------------------------
;  mdm_regs.asm:        635 ; DEMCODC0
;  mdm_regs.asm:        636 ; 
;  mdm_regs.asm:        637 DEMCODC0                                          .assign    58
;  mdm_regs.asm:        638 DEMCODC0_ESTSEL                                   .assign    11 ;
;  mdm_regs.asm:        639 DEMCODC0_COMPSEL                                  .assign     9 ;
;  mdm_regs.asm:        640 DEMCODC0_IIRUSEINITIAL                            .assign     8 ;
;  mdm_regs.asm:        641 DEMCODC0_IIRGAIN                                  .assign     5 ;
;  mdm_regs.asm:        642 DEMCODC0_IIREN                                    .assign     4 ;
;  mdm_regs.asm:        643 DEMCODC0_ACCCONTMODE                              .assign     3 ;
;  mdm_regs.asm:        644 DEMCODC0_ACCPERIOD                                .assign     1 ;
;  mdm_regs.asm:        645 DEMCODC0_ACCEN                                    .assign     0 ;
;  mdm_regs.asm:        646 ; --------------------------------------------------------------
;  mdm_regs.asm:        647 ; DEMFIDC0
;  mdm_regs.asm:        648 ; 
;  mdm_regs.asm:        649 DEMFIDC0                                          .assign    59
;  mdm_regs.asm:        650 DEMFIDC0_COMPSEL                                  .assign     4 ;
;  mdm_regs.asm:        651 DEMFIDC0_ACCPERIOD                                .assign     2 ;
;  mdm_regs.asm:        652 DEMFIDC0_ACCCONTMODE                              .assign     1 ;
;  mdm_regs.asm:        653 DEMFIDC0_ACCEN                                    .assign     0 ;
;  mdm_regs.asm:        654 ; --------------------------------------------------------------
;  mdm_regs.asm:        655 ; DEMFEXB0
;  mdm_regs.asm:        656 ; 
;  mdm_regs.asm:        657 DEMFEXB0                                          .assign    60
;  mdm_regs.asm:        658 DEMFEXB0_OUT2PASSTHROUGH                          .assign    13 ;
;  mdm_regs.asm:        659 DEMFEXB0_OUT2SRCSEL                               .assign    11 ;
;  mdm_regs.asm:        660 DEMFEXB0_OUT1PASSTHROUGH                          .assign    10 ;
;  mdm_regs.asm:        661 DEMFEXB0_OUT1SRCSEL                               .assign     8 ;
;  mdm_regs.asm:        662 DEMFEXB0_B4SRCSEL                                 .assign     6 ;
;  mdm_regs.asm:        663 DEMFEXB0_B3SRCSEL                                 .assign     4 ;
;  mdm_regs.asm:        664 DEMFEXB0_B2SRCSEL                                 .assign     2 ;
;  mdm_regs.asm:        665 DEMFEXB0_B1SRCSEL                                 .assign     0 ;
;  mdm_regs.asm:        666 ; --------------------------------------------------------------
;  mdm_regs.asm:        667 ; DEMDSXB0
;  mdm_regs.asm:        668 ; 
;  mdm_regs.asm:        669 DEMDSXB0                                          .assign    61
;  mdm_regs.asm:        670 DEMDSXB0_OUT2PASSTHROUGH                          .assign    13 ;
;  mdm_regs.asm:        671 DEMDSXB0_OUT1PASSTHROUGH                          .assign    12 ;
;  mdm_regs.asm:        672 DEMDSXB0_OUTSRCSEL2                               .assign    10 ;
;  mdm_regs.asm:        673 DEMDSXB0_OUTSRCSEL1                               .assign     8 ;
;  mdm_regs.asm:        674 DEMDSXB0_B4SRCSEL                                 .assign     6 ;
;  mdm_regs.asm:        675 DEMDSXB0_B3SRCSEL                                 .assign     4 ;
;  mdm_regs.asm:        676 DEMDSXB0_B2SRCSEL                                 .assign     2 ;
;  mdm_regs.asm:        677 DEMDSXB0_B1SRCSEL                                 .assign     0 ;
;  mdm_regs.asm:        678 ; --------------------------------------------------------------
;  mdm_regs.asm:        679 ; DEMD2XB0
;  mdm_regs.asm:        680 ; 
;  mdm_regs.asm:        681 DEMD2XB0                                          .assign    62
;  mdm_regs.asm:        682 DEMD2XB0_B3SRCSEL                                 .assign    10 ;
;  mdm_regs.asm:        683 DEMD2XB0_OUT2PASSTHROUGH                          .assign     9 ;
;  mdm_regs.asm:        684 DEMD2XB0_OUT1PASSTHROUGH                          .assign     8 ;
;  mdm_regs.asm:        685 DEMD2XB0_OUTSRCSEL2                               .assign     6 ;
;  mdm_regs.asm:        686 DEMD2XB0_OUTSRCSEL1                               .assign     4 ;
;  mdm_regs.asm:        687 DEMD2XB0_B2SRCSEL                                 .assign     2 ;
;  mdm_regs.asm:        688 DEMD2XB0_B1SRCSEL                                 .assign     0 ;
;  mdm_regs.asm:        689 ; --------------------------------------------------------------
;  mdm_regs.asm:        690 ; DEMFIFE0
;  mdm_regs.asm:        691 ; 
;  mdm_regs.asm:        692 DEMFIFE0                                          .assign    63
;  mdm_regs.asm:        693 DEMFIFE0_FINEFOESEL                               .assign    11 ;
;  mdm_regs.asm:        694 DEMFIFE0_FOCFFSEL                                 .assign     9 ;
;  mdm_regs.asm:        695 DEMFIFE0_ACCCNTMODE                               .assign     8 ;
;  mdm_regs.asm:        696 DEMFIFE0_ACCPERIOD                                .assign     6 ;
;  mdm_regs.asm:        697 DEMFIFE0_ACCEN                                    .assign     5 ;
;  mdm_regs.asm:        698 DEMFIFE0_IIRUSEINITIAL                            .assign     4 ;
;  mdm_regs.asm:        699 DEMFIFE0_IIRGAIN                                  .assign     1 ;
;  mdm_regs.asm:        700 DEMFIFE0_IIREN                                    .assign     0 ;
;  mdm_regs.asm:        701 ; --------------------------------------------------------------
;  mdm_regs.asm:        702 ; DEMMAFI0
;  mdm_regs.asm:        703 ; 
;  mdm_regs.asm:        704 DEMMAFI0                                          .assign    64
;  mdm_regs.asm:        705 DEMMAFI0_C1C7                                     .assign     8 ;
;  mdm_regs.asm:        706 DEMMAFI0_C0C8                                     .assign     0 ;
;  mdm_regs.asm:        707 ; --------------------------------------------------------------
;  mdm_regs.asm:        708 ; DEMMAFI1
;  mdm_regs.asm:        709 ; 
;  mdm_regs.asm:        710 DEMMAFI1                                          .assign    65
;  mdm_regs.asm:        711 DEMMAFI1_C3C5                                     .assign     8 ;
;  mdm_regs.asm:        712 DEMMAFI1_C2C6                                     .assign     0 ;
;  mdm_regs.asm:        713 ; --------------------------------------------------------------
;  mdm_regs.asm:        714 ; DEMMAFI2
;  mdm_regs.asm:        715 ; 
;  mdm_regs.asm:        716 DEMMAFI2                                          .assign    66
;  mdm_regs.asm:        717 DEMMAFI2_C4                                       .assign     0 ;
;  mdm_regs.asm:        718 ; --------------------------------------------------------------
;  mdm_regs.asm:        719 ; DEMMAFI3
;  mdm_regs.asm:        720 ; 
;  mdm_regs.asm:        721 DEMMAFI3                                          .assign    67
;  mdm_regs.asm:        722 DEMMAFI3_K                                        .assign     0 ;
;  mdm_regs.asm:        723 ; --------------------------------------------------------------
;  mdm_regs.asm:        724 ; DEMC1BE0
;  mdm_regs.asm:        725 ; 
;  mdm_regs.asm:        726 DEMC1BE0                                          .assign    68
;  mdm_regs.asm:        727 DEMC1BE0_MASKB                                    .assign    11 ;
;  mdm_regs.asm:        728 DEMC1BE0_MASKA                                    .assign     6 ;
;  mdm_regs.asm:        729 DEMC1BE0_CASCCONF                                 .assign     4 ;
;  mdm_regs.asm:        730 DEMC1BE0_COPYCONF                                 .assign     0 ;
;  mdm_regs.asm:        731 ; --------------------------------------------------------------
;  mdm_regs.asm:        732 ; DEMC1BE1
;  mdm_regs.asm:        733 ; 
;  mdm_regs.asm:        734 DEMC1BE1                                          .assign    69
;  mdm_regs.asm:        735 DEMC1BE1_THRESHOLDB                               .assign     8 ;
;  mdm_regs.asm:        736 DEMC1BE1_THRESHOLDA                               .assign     0 ;
;  mdm_regs.asm:        737 ; --------------------------------------------------------------
;  mdm_regs.asm:        738 ; DEMC1BE2
;  mdm_regs.asm:        739 ; 
;  mdm_regs.asm:        740 DEMC1BE2                                          .assign    70
;  mdm_regs.asm:        741 DEMC1BE2_PEAKCONF                                 .assign     8 ;
;  mdm_regs.asm:        742 DEMC1BE2_THRESHOLDC                               .assign     0 ;
;  mdm_regs.asm:        743 ; --------------------------------------------------------------
;  mdm_regs.asm:        744 ; DEMC1BE10
;  mdm_regs.asm:        745 ; 
;  mdm_regs.asm:        746 DEMC1BE10                                         .assign    71
;  mdm_regs.asm:        747 DEMC1BE10_PEAKCONF_G                              .assign    15 ;
;  mdm_regs.asm:        748 DEMC1BE10_PEAKCONF_CF                             .assign    13 ;
;  mdm_regs.asm:        749 DEMC1BE10_MASKE                                   .assign     8 ;
;  mdm_regs.asm:        750 DEMC1BE10_MASKD                                   .assign     3 ;
;  mdm_regs.asm:        751 DEMC1BE10_CASCCONF                                .assign     0 ;
;  mdm_regs.asm:        752 ; --------------------------------------------------------------
;  mdm_regs.asm:        753 ; DEMC1BE11
;  mdm_regs.asm:        754 ; 
;  mdm_regs.asm:        755 DEMC1BE11                                         .assign    72
;  mdm_regs.asm:        756 DEMC1BE11_THRESHOLDE                              .assign     8 ;
;  mdm_regs.asm:        757 DEMC1BE11_THRESHOLDD                              .assign     0 ;
;  mdm_regs.asm:        758 ; --------------------------------------------------------------
;  mdm_regs.asm:        759 ; DEMC1BE12
;  mdm_regs.asm:        760 ; 
;  mdm_regs.asm:        761 DEMC1BE12                                         .assign    73
;  mdm_regs.asm:        762 DEMC1BE12_THRESHOLDG                              .assign     8 ;
;  mdm_regs.asm:        763 DEMC1BE12_THRESHOLDF                              .assign     0 ;
;  mdm_regs.asm:        764 ; --------------------------------------------------------------
;  mdm_regs.asm:        765 ; MDMSYNC0
;  mdm_regs.asm:        766 ; 
;  mdm_regs.asm:        767 MDMSYNC0                                          .assign    74
;  mdm_regs.asm:        768 MDMSYNC0_SWA15C0                                  .assign     0 ;
;  mdm_regs.asm:        769 ; --------------------------------------------------------------
;  mdm_regs.asm:        770 ; MDMSYNC1
;  mdm_regs.asm:        771 ; 
;  mdm_regs.asm:        772 MDMSYNC1                                          .assign    75
;  mdm_regs.asm:        773 MDMSYNC1_SWA31C16                                 .assign     0 ;
;  mdm_regs.asm:        774 ; --------------------------------------------------------------
;  mdm_regs.asm:        775 ; MDMSYNC2
;  mdm_regs.asm:        776 ; 
;  mdm_regs.asm:        777 MDMSYNC2                                          .assign    76
;  mdm_regs.asm:        778 MDMSYNC2_SWB15C0                                  .assign     0 ;
;  mdm_regs.asm:        779 ; --------------------------------------------------------------
;  mdm_regs.asm:        780 ; MDMSYNC3
;  mdm_regs.asm:        781 ; 
;  mdm_regs.asm:        782 MDMSYNC3                                          .assign    77
;  mdm_regs.asm:        783 MDMSYNC3_SWB31C16                                 .assign     0 ;
;  mdm_regs.asm:        784 ; --------------------------------------------------------------
;  mdm_regs.asm:        785 ; DEMSWQU0
;  mdm_regs.asm:        786 ; 
;  mdm_regs.asm:        787 DEMSWQU0                                          .assign    78
;  mdm_regs.asm:        788 DEMSWQU0_SYNC_MODE                                .assign     7 ;
;  mdm_regs.asm:        789 DEMSWQU0_AUTOMAFC                                 .assign     6 ;
;  mdm_regs.asm:        790 DEMSWQU0_RUN                                      .assign     5 ;
;  mdm_regs.asm:        791 DEMSWQU0_REFLEN                                   .assign     0 ;
;  mdm_regs.asm:        792 ; --------------------------------------------------------------
;  mdm_regs.asm:        793 ; DEMFB2P0
;  mdm_regs.asm:        794 ; 
;  mdm_regs.asm:        795 DEMFB2P0                                          .assign    79
;  mdm_regs.asm:        796 DEMFB2P0_BETA                                     .assign     8 ;
;  mdm_regs.asm:        797 DEMFB2P0_ALPHA                                    .assign     0 ;
;  mdm_regs.asm:        798 ; --------------------------------------------------------------
;  mdm_regs.asm:        799 ; DEMFB2P1
;  mdm_regs.asm:        800 ; 
;  mdm_regs.asm:        801 DEMFB2P1                                          .assign    80
;  mdm_regs.asm:        802 DEMFB2P1_FB2P_OPEN                                .assign    14 ;
;  mdm_regs.asm:        803 DEMFB2P1_HDIS_PRS                                 .assign    12 ;
;  mdm_regs.asm:        804 DEMFB2P1_IIR_GAIN                                 .assign    10 ;
;  mdm_regs.asm:        805 DEMFB2P1_IIR_BW                                   .assign     7 ;
;  mdm_regs.asm:        806 DEMFB2P1_FB2PLL_LIMIT                             .assign     0 ;
;  mdm_regs.asm:        807 ; --------------------------------------------------------------
;  mdm_regs.asm:        808 ; DEMPHAC0
;  mdm_regs.asm:        809 ; 
;  mdm_regs.asm:        810 DEMPHAC0                                          .assign    81
;  mdm_regs.asm:        811 DEMPHAC0_REF_B                                    .assign     8 ;
;  mdm_regs.asm:        812 DEMPHAC0_REF_A                                    .assign     0 ;
;  mdm_regs.asm:        813 ; --------------------------------------------------------------
;  mdm_regs.asm:        814 ; DEMPHAC1
;  mdm_regs.asm:        815 ; 
;  mdm_regs.asm:        816 DEMPHAC1                                          .assign    82
;  mdm_regs.asm:        817 DEMPHAC1_PHAC_TR_LEN                              .assign    10 ;
;  mdm_regs.asm:        818 DEMPHAC1_PHAC_SYM_LEN                             .assign     7 ;
;  mdm_regs.asm:        819 DEMPHAC1_PHASE_INCR                               .assign     0 ;
;  mdm_regs.asm:        820 ; --------------------------------------------------------------
;  mdm_regs.asm:        821 ; DEMPHAC2
;  mdm_regs.asm:        822 ; 
;  mdm_regs.asm:        823 DEMPHAC2                                          .assign    83
;  mdm_regs.asm:        824 DEMPHAC2_ALPHA                                    .assign     8 ;
;  mdm_regs.asm:        825 DEMPHAC2_BETA                                     .assign     0 ;
;  mdm_regs.asm:        826 ; --------------------------------------------------------------
;  mdm_regs.asm:        827 ; DEMPHAC3
;  mdm_regs.asm:        828 ; 
;  mdm_regs.asm:        829 DEMPHAC3                                          .assign    84
;  mdm_regs.asm:        830 DEMPHAC3_IIR_BW                                   .assign     0 ;
;  mdm_regs.asm:        831 ; --------------------------------------------------------------
;  mdm_regs.asm:        832 ; DEMPHAC4
;  mdm_regs.asm:        833 ; 
;  mdm_regs.asm:        834 DEMPHAC4                                          .assign    85
;  mdm_regs.asm:        835 DEMPHAC4_TR_15_0                                  .assign     0 ;
;  mdm_regs.asm:        836 ; --------------------------------------------------------------
;  mdm_regs.asm:        837 ; DEMPHAC5
;  mdm_regs.asm:        838 ; 
;  mdm_regs.asm:        839 DEMPHAC5                                          .assign    86
;  mdm_regs.asm:        840 DEMPHAC5_TR_31_16                                 .assign     0 ;
;  mdm_regs.asm:        841 ; --------------------------------------------------------------
;  mdm_regs.asm:        842 ; DEMPHAC6
;  mdm_regs.asm:        843 ; 
;  mdm_regs.asm:        844 DEMPHAC6                                          .assign    87
;  mdm_regs.asm:        845 DEMPHAC6_TR_47_32                                 .assign     0 ;
;  mdm_regs.asm:        846 ; --------------------------------------------------------------
;  mdm_regs.asm:        847 ; DEMPHAC7
;  mdm_regs.asm:        848 ; 
;  mdm_regs.asm:        849 DEMPHAC7                                          .assign    88
;  mdm_regs.asm:        850 DEMPHAC7_TR_63_48                                 .assign     0 ;
;  mdm_regs.asm:        851 ; --------------------------------------------------------------
;  mdm_regs.asm:        852 ; DEMC1BEREF0
;  mdm_regs.asm:        853 ; 
;  mdm_regs.asm:        854 DEMC1BEREF0                                       .assign    89
;  mdm_regs.asm:        855 DEMC1BEREF0_CAR15C0                               .assign     0 ;
;  mdm_regs.asm:        856 ; --------------------------------------------------------------
;  mdm_regs.asm:        857 ; DEMC1BEREF1
;  mdm_regs.asm:        858 ; 
;  mdm_regs.asm:        859 DEMC1BEREF1                                       .assign    90
;  mdm_regs.asm:        860 DEMC1BEREF1_CAR31C16                              .assign     0 ;
;  mdm_regs.asm:        861 ; --------------------------------------------------------------
;  mdm_regs.asm:        862 ; DEMC1BEREF2
;  mdm_regs.asm:        863 ; 
;  mdm_regs.asm:        864 DEMC1BEREF2                                       .assign    91
;  mdm_regs.asm:        865 DEMC1BEREF2_CBR15C0                               .assign     0 ;
;  mdm_regs.asm:        866 ; --------------------------------------------------------------
;  mdm_regs.asm:        867 ; DEMC1BEREF3
;  mdm_regs.asm:        868 ; 
;  mdm_regs.asm:        869 DEMC1BEREF3                                       .assign    92
;  mdm_regs.asm:        870 DEMC1BEREF3_CBR31C16                              .assign     0 ;
;  mdm_regs.asm:        871 ; --------------------------------------------------------------
;  mdm_regs.asm:        872 ; DEMC1BEREF4
;  mdm_regs.asm:        873 ; 
;  mdm_regs.asm:        874 DEMC1BEREF4                                       .assign    93
;  mdm_regs.asm:        875 DEMC1BEREF4_CDR15C0                               .assign     0 ;
;  mdm_regs.asm:        876 ; --------------------------------------------------------------
;  mdm_regs.asm:        877 ; DEMC1BEREF5
;  mdm_regs.asm:        878 ; 
;  mdm_regs.asm:        879 DEMC1BEREF5                                       .assign    94
;  mdm_regs.asm:        880 DEMC1BEREF5_CDR31C16                              .assign     0 ;
;  mdm_regs.asm:        881 ; --------------------------------------------------------------
;  mdm_regs.asm:        882 ; DEMC1BEREF6
;  mdm_regs.asm:        883 ; 
;  mdm_regs.asm:        884 DEMC1BEREF6                                       .assign    95
;  mdm_regs.asm:        885 DEMC1BEREF6_CER15C0                               .assign     0 ;
;  mdm_regs.asm:        886 ; --------------------------------------------------------------
;  mdm_regs.asm:        887 ; DEMC1BEREF7
;  mdm_regs.asm:        888 ; 
;  mdm_regs.asm:        889 DEMC1BEREF7                                       .assign    96
;  mdm_regs.asm:        890 DEMC1BEREF7_CER31C16                              .assign     0 ;
;  mdm_regs.asm:        891 ; --------------------------------------------------------------
;  mdm_regs.asm:        892 ; DEMMLSE4MAP
;  mdm_regs.asm:        893 ; 
;  mdm_regs.asm:        894 DEMMLSE4MAP                                       .assign    97
;  mdm_regs.asm:        895 DEMMLSE4MAP_MAP_P3                                .assign     6 ;
;  mdm_regs.asm:        896 DEMMLSE4MAP_MAP_P1                                .assign     4 ;
;  mdm_regs.asm:        897 DEMMLSE4MAP_MAP_M1                                .assign     2 ;
;  mdm_regs.asm:        898 DEMMLSE4MAP_MAP_M3                                .assign     0 ;
;  mdm_regs.asm:        899 ; --------------------------------------------------------------
;  mdm_regs.asm:        900 ; DEMC1BE13
;  mdm_regs.asm:        901 ; 
;  mdm_regs.asm:        902 DEMC1BE13                                         .assign    98
;  mdm_regs.asm:        903 DEMC1BE13_CORRVALUED                              .assign     0 ;
;  mdm_regs.asm:        904 ; --------------------------------------------------------------
;  mdm_regs.asm:        905 ; MODCTRL
;  mdm_regs.asm:        906 ; 
;  mdm_regs.asm:        907 MODCTRL                                           .assign    99
;  mdm_regs.asm:        908 MODCTRL_CDC_COL_RESTART                           .assign    12 ;
;  mdm_regs.asm:        909 MODCTRL_DSBUSEL                                   .assign    11 ;
;  mdm_regs.asm:        910 MODCTRL_HDISMODE                                  .assign    10 ;
;  mdm_regs.asm:        911 MODCTRL_PARBITQUALEN                              .assign     9 ;
;  mdm_regs.asm:        912 MODCTRL_STIMEARLYLATE                             .assign     7 ;
;  mdm_regs.asm:        913 MODCTRL_EARLYLATE                                 .assign     6 ;
;  mdm_regs.asm:        914 MODCTRL_SOFTPDIFFMODE                             .assign     5 ;
;  mdm_regs.asm:        915 MODCTRL_SOFTTXENABLE                              .assign     4 ;
;  mdm_regs.asm:        916 MODCTRL_FECENABLE                                 .assign     3 ;
;  mdm_regs.asm:        917 MODCTRL_FEC5TERMINATE                             .assign     2 ;
;  mdm_regs.asm:        918 MODCTRL_TONEINSERT                                .assign     1 ;
;  mdm_regs.asm:        919 MODCTRL_PREAMBLEINSERT                            .assign     0 ;
;  mdm_regs.asm:        920 ; --------------------------------------------------------------
;  mdm_regs.asm:        921 ; MODPREAMBLE
;  mdm_regs.asm:        922 ; 
;  mdm_regs.asm:        923 MODPREAMBLE                                       .assign   100
;  mdm_regs.asm:        924 MODPREAMBLE_WORD                                  .assign     0 ;
;  mdm_regs.asm:        925 ; --------------------------------------------------------------
;  mdm_regs.asm:        926 ; DEMFRAC0
;  mdm_regs.asm:        927 ; 
;  mdm_regs.asm:        928 DEMFRAC0                                          .assign   101
;  mdm_regs.asm:        929 DEMFRAC0_P15C0                                    .assign     0 ;
;  mdm_regs.asm:        930 ; --------------------------------------------------------------
;  mdm_regs.asm:        931 ; DEMFRAC1
;  mdm_regs.asm:        932 ; 
;  mdm_regs.asm:        933 DEMFRAC1                                          .assign   102
;  mdm_regs.asm:        934 DEMFRAC1_P27C16                                   .assign     0 ;
;  mdm_regs.asm:        935 ; --------------------------------------------------------------
;  mdm_regs.asm:        936 ; DEMFRAC2
;  mdm_regs.asm:        937 ; 
;  mdm_regs.asm:        938 DEMFRAC2                                          .assign   103
;  mdm_regs.asm:        939 DEMFRAC2_Q15C0                                    .assign     0 ;
;  mdm_regs.asm:        940 ; --------------------------------------------------------------
;  mdm_regs.asm:        941 ; DEMFRAC3
;  mdm_regs.asm:        942 ; 
;  mdm_regs.asm:        943 DEMFRAC3                                          .assign   104
;  mdm_regs.asm:        944 DEMFRAC3_Q27C16                                   .assign     0 ;
;  mdm_regs.asm:        945 ; --------------------------------------------------------------
;  mdm_regs.asm:        946 ; DEMCODC1
;  mdm_regs.asm:        947 ; 
;  mdm_regs.asm:        948 DEMCODC1                                          .assign   105
;  mdm_regs.asm:        949 DEMCODC1_COMPIVAL                                 .assign     0 ;
;  mdm_regs.asm:        950 ; --------------------------------------------------------------
;  mdm_regs.asm:        951 ; DEMCODC2
;  mdm_regs.asm:        952 ; 
;  mdm_regs.asm:        953 DEMCODC2                                          .assign   106
;  mdm_regs.asm:        954 DEMCODC2_COMPQVAL                                 .assign     0 ;
;  mdm_regs.asm:        955 ; --------------------------------------------------------------
;  mdm_regs.asm:        956 ; DEMFIDC1
;  mdm_regs.asm:        957 ; 
;  mdm_regs.asm:        958 DEMFIDC1                                          .assign   107
;  mdm_regs.asm:        959 DEMFIDC1_COMPIVAL                                 .assign     0 ;
;  mdm_regs.asm:        960 ; --------------------------------------------------------------
;  mdm_regs.asm:        961 ; DEMFIDC2
;  mdm_regs.asm:        962 ; 
;  mdm_regs.asm:        963 DEMFIDC2                                          .assign   108
;  mdm_regs.asm:        964 DEMFIDC2_COMPQVAL                                 .assign     0 ;
;  mdm_regs.asm:        965 ; --------------------------------------------------------------
;  mdm_regs.asm:        966 ; DEMFIFE1
;  mdm_regs.asm:        967 ; 
;  mdm_regs.asm:        968 DEMFIFE1                                          .assign   109
;  mdm_regs.asm:        969 DEMFIFE1_FOCFBREGVAL                              .assign     0 ;
;  mdm_regs.asm:        970 ; --------------------------------------------------------------
;  mdm_regs.asm:        971 ; DEMTHRD0
;  mdm_regs.asm:        972 ; 
;  mdm_regs.asm:        973 DEMTHRD0                                          .assign   110
;  mdm_regs.asm:        974 DEMTHRD0_THR2                                     .assign     8 ;
;  mdm_regs.asm:        975 DEMTHRD0_RESERVED                                 .assign     7 ;
;  mdm_regs.asm:        976 DEMTHRD0_THR1                                     .assign     0 ;
;  mdm_regs.asm:        977 ; --------------------------------------------------------------
;  mdm_regs.asm:        978 ; DEMTHRD1
;  mdm_regs.asm:        979 ; 
;  mdm_regs.asm:        980 DEMTHRD1                                          .assign   111
;  mdm_regs.asm:        981 DEMTHRD1_THR3                                     .assign     0 ;
;  mdm_regs.asm:        982 ; --------------------------------------------------------------
;  mdm_regs.asm:        983 ; DEMMAFC0
;  mdm_regs.asm:        984 ; 
;  mdm_regs.asm:        985 DEMMAFC0                                          .assign   112
;  mdm_regs.asm:        986 DEMMAFC0_COMPVAL                                  .assign     0 ;
;  mdm_regs.asm:        987 ; --------------------------------------------------------------
;  mdm_regs.asm:        988 ; DEMMAFI4
;  mdm_regs.asm:        989 ; 
;  mdm_regs.asm:        990 DEMMAFI4                                          .assign   113
;  mdm_regs.asm:        991 DEMMAFI4_TERM_VAL                                 .assign     0 ;
;  mdm_regs.asm:        992 ; --------------------------------------------------------------
;  mdm_regs.asm:        993 ; DEMSWIMBAL
;  mdm_regs.asm:        994 ; 
;  mdm_regs.asm:        995 DEMSWIMBAL                                        .assign   114
;  mdm_regs.asm:        996 DEMSWIMBAL_IMBALB                                 .assign     8 ;
;  mdm_regs.asm:        997 DEMSWIMBAL_IMBALA                                 .assign     0 ;
;  mdm_regs.asm:        998 ; --------------------------------------------------------------
;  mdm_regs.asm:        999 ; DEMSOFTPDIFF
;  mdm_regs.asm:       1000 ; 
;  mdm_regs.asm:       1001 DEMSOFTPDIFF                                      .assign   115
;  mdm_regs.asm:       1002 DEMSOFTPDIFF_SOFTPDIFF                            .assign     0 ;
;  mdm_regs.asm:       1003 ; --------------------------------------------------------------
;  mdm_regs.asm:       1004 ; DEMDEBUG
;  mdm_regs.asm:       1005 ; 
;  mdm_regs.asm:       1006 DEMDEBUG                                          .assign   116
;  mdm_regs.asm:       1007 DEMDEBUG_DECSTAGEDEBUG                            .assign     5 ;
;  mdm_regs.asm:       1008 DEMDEBUG_FRONTENDDEBUG                            .assign     1 ;
;  mdm_regs.asm:       1009 DEMDEBUG_LOOPBACKMODE                             .assign     0 ;
;  mdm_regs.asm:       1010 ; --------------------------------------------------------------
;  mdm_regs.asm:       1011 ; VITCTRL
;  mdm_regs.asm:       1012 ; 
;  mdm_regs.asm:       1013 VITCTRL                                           .assign   117
;  mdm_regs.asm:       1014 VITCTRL_METRSEL                                   .assign    10 ;
;  mdm_regs.asm:       1015 VITCTRL_READEPTH                                  .assign     6 ;
;  mdm_regs.asm:       1016 VITCTRL_APMRDBACKSEL                              .assign     2 ;
;  mdm_regs.asm:       1017 VITCTRL_ACSITERATIONS                             .assign     1 ;
;  mdm_regs.asm:       1018 VITCTRL_SOFTMETRICS                               .assign     0 ;
;  mdm_regs.asm:       1019 ; --------------------------------------------------------------
;  mdm_regs.asm:       1020 ; VITCOMPUTE
;  mdm_regs.asm:       1021 ; 
;  mdm_regs.asm:       1022 VITCOMPUTE                                        .assign   118
;  mdm_regs.asm:       1023 VITCOMPUTE_COMPUTE                                .assign     0 ;
;  mdm_regs.asm:       1024 ; --------------------------------------------------------------
;  mdm_regs.asm:       1025 ; VITAPMRDBACK
;  mdm_regs.asm:       1026 ; 
;  mdm_regs.asm:       1027 VITAPMRDBACK                                      .assign   119
;  mdm_regs.asm:       1028 VITAPMRDBACK_VALUE                                .assign     0 ;
;  mdm_regs.asm:       1029 ; --------------------------------------------------------------
;  mdm_regs.asm:       1030 ; VITSTATE
;  mdm_regs.asm:       1031 ; 
;  mdm_regs.asm:       1032 VITSTATE                                          .assign   120
;  mdm_regs.asm:       1033 VITSTATE_VALUE                                    .assign     0 ;
;  mdm_regs.asm:       1034 ; --------------------------------------------------------------
;  mdm_regs.asm:       1035 ; VITBRMETRIC10
;  mdm_regs.asm:       1036 ; 
;  mdm_regs.asm:       1037 VITBRMETRIC10                                     .assign   121
;  mdm_regs.asm:       1038 VITBRMETRIC10_MET1                                .assign     8 ;
;  mdm_regs.asm:       1039 VITBRMETRIC10_MET0                                .assign     0 ;
;  mdm_regs.asm:       1040 ; --------------------------------------------------------------
;  mdm_regs.asm:       1041 ; VITBRMETRIC32
;  mdm_regs.asm:       1042 ; 
;  mdm_regs.asm:       1043 VITBRMETRIC32                                     .assign   122
;  mdm_regs.asm:       1044 VITBRMETRIC32_MET3                                .assign     8 ;
;  mdm_regs.asm:       1045 VITBRMETRIC32_MET2                                .assign     0 ;
;  mdm_regs.asm:       1046 ; --------------------------------------------------------------
;  mdm_regs.asm:       1047 ; VITBRMETRIC54
;  mdm_regs.asm:       1048 ; 
;  mdm_regs.asm:       1049 VITBRMETRIC54                                     .assign   123
;  mdm_regs.asm:       1050 VITBRMETRIC54_MET5                                .assign     8 ;
;  mdm_regs.asm:       1051 VITBRMETRIC54_MET4                                .assign     0 ;
;  mdm_regs.asm:       1052 ; --------------------------------------------------------------
;  mdm_regs.asm:       1053 ; VITBRMETRIC76
;  mdm_regs.asm:       1054 ; 
;  mdm_regs.asm:       1055 VITBRMETRIC76                                     .assign   124
;  mdm_regs.asm:       1056 VITBRMETRIC76_MET7                                .assign     8 ;
;  mdm_regs.asm:       1057 VITBRMETRIC76_MET6                                .assign     0 ;
;  mdm_regs.asm:       1058 ; --------------------------------------------------------------
;  mdm_regs.asm:       1059 ; VITBRSEL0
;  mdm_regs.asm:       1060 ; 
;  mdm_regs.asm:       1061 VITBRSEL0                                         .assign   125
;  mdm_regs.asm:       1062 VITBRSEL0_BR3MUX                                  .assign     9 ;
;  mdm_regs.asm:       1063 VITBRSEL0_BR2MUX                                  .assign     6 ;
;  mdm_regs.asm:       1064 VITBRSEL0_BR1MUX                                  .assign     3 ;
;  mdm_regs.asm:       1065 VITBRSEL0_BR0MUX                                  .assign     0 ;
;  mdm_regs.asm:       1066 ; --------------------------------------------------------------
;  mdm_regs.asm:       1067 ; VITAPMSEL0
;  mdm_regs.asm:       1068 ; 
;  mdm_regs.asm:       1069 VITAPMSEL0                                        .assign   126
;  mdm_regs.asm:       1070 VITAPMSEL0_APM3MUX                                .assign     9 ;
;  mdm_regs.asm:       1071 VITAPMSEL0_APM2MUX                                .assign     6 ;
;  mdm_regs.asm:       1072 VITAPMSEL0_APM1MUX                                .assign     3 ;
;  mdm_regs.asm:       1073 VITAPMSEL0_APM0MUX                                .assign     0 ;
;  mdm_regs.asm:       1074 ; --------------------------------------------------------------
;  mdm_regs.asm:       1075 ; VITBRSEL1
;  mdm_regs.asm:       1076 ; 
;  mdm_regs.asm:       1077 VITBRSEL1                                         .assign   127
;  mdm_regs.asm:       1078 VITBRSEL1_BR3MUX                                  .assign     9 ;
;  mdm_regs.asm:       1079 VITBRSEL1_BR2MUX                                  .assign     6 ;
;  mdm_regs.asm:       1080 VITBRSEL1_BR1MUX                                  .assign     3 ;
;  mdm_regs.asm:       1081 VITBRSEL1_BR0MUX                                  .assign     0 ;
;  mdm_regs.asm:       1082 ; --------------------------------------------------------------
;  mdm_regs.asm:       1083 ; VITAPMSEL1
;  mdm_regs.asm:       1084 ; 
;  mdm_regs.asm:       1085 VITAPMSEL1                                        .assign   128
;  mdm_regs.asm:       1086 VITAPMSEL1_APM3MUX                                .assign     9 ;
;  mdm_regs.asm:       1087 VITAPMSEL1_APM2MUX                                .assign     6 ;
;  mdm_regs.asm:       1088 VITAPMSEL1_APM1MUX                                .assign     3 ;
;  mdm_regs.asm:       1089 VITAPMSEL1_APM0MUX                                .assign     0 ;
;  mdm_regs.asm:       1090 ; --------------------------------------------------------------
;  mdm_regs.asm:       1091 ; VITBRSEL2
;  mdm_regs.asm:       1092 ; 
;  mdm_regs.asm:       1093 VITBRSEL2                                         .assign   129
;  mdm_regs.asm:       1094 VITBRSEL2_BR3MUX                                  .assign     9 ;
;  mdm_regs.asm:       1095 VITBRSEL2_BR2MUX                                  .assign     6 ;
;  mdm_regs.asm:       1096 VITBRSEL2_BR1MUX                                  .assign     3 ;
;  mdm_regs.asm:       1097 VITBRSEL2_BR0MUX                                  .assign     0 ;
;  mdm_regs.asm:       1098 ; --------------------------------------------------------------
;  mdm_regs.asm:       1099 ; VITAPMSEL2
;  mdm_regs.asm:       1100 ; 
;  mdm_regs.asm:       1101 VITAPMSEL2                                        .assign   130
;  mdm_regs.asm:       1102 VITAPMSEL2_APM3MUX                                .assign     9 ;
;  mdm_regs.asm:       1103 VITAPMSEL2_APM2MUX                                .assign     6 ;
;  mdm_regs.asm:       1104 VITAPMSEL2_APM1MUX                                .assign     3 ;
;  mdm_regs.asm:       1105 VITAPMSEL2_APM0MUX                                .assign     0 ;
;  mdm_regs.asm:       1106 ; --------------------------------------------------------------
;  mdm_regs.asm:       1107 ; VITBRSEL3
;  mdm_regs.asm:       1108 ; 
;  mdm_regs.asm:       1109 VITBRSEL3                                         .assign   131
;  mdm_regs.asm:       1110 VITBRSEL3_BR3MUX                                  .assign     9 ;
;  mdm_regs.asm:       1111 VITBRSEL3_BR2MUX                                  .assign     6 ;
;  mdm_regs.asm:       1112 VITBRSEL3_BR1MUX                                  .assign     3 ;
;  mdm_regs.asm:       1113 VITBRSEL3_BR0MUX                                  .assign     0 ;
;  mdm_regs.asm:       1114 ; --------------------------------------------------------------
;  mdm_regs.asm:       1115 ; VITAPMSEL3
;  mdm_regs.asm:       1116 ; 
;  mdm_regs.asm:       1117 VITAPMSEL3                                        .assign   132
;  mdm_regs.asm:       1118 VITAPMSEL3_APM3MUX                                .assign     9 ;
;  mdm_regs.asm:       1119 VITAPMSEL3_APM2MUX                                .assign     6 ;
;  mdm_regs.asm:       1120 VITAPMSEL3_APM1MUX                                .assign     3 ;
;  mdm_regs.asm:       1121 VITAPMSEL3_APM0MUX                                .assign     0 ;
;  mdm_regs.asm:       1122 ; --------------------------------------------------------------
;  mdm_regs.asm:       1123 ; VITBRSEL4
;  mdm_regs.asm:       1124 ; 
;  mdm_regs.asm:       1125 VITBRSEL4                                         .assign   133
;  mdm_regs.asm:       1126 VITBRSEL4_BR3MUX                                  .assign     9 ;
;  mdm_regs.asm:       1127 VITBRSEL4_BR2MUX                                  .assign     6 ;
;  mdm_regs.asm:       1128 VITBRSEL4_BR1MUX                                  .assign     3 ;
;  mdm_regs.asm:       1129 VITBRSEL4_BR0MUX                                  .assign     0 ;
;  mdm_regs.asm:       1130 ; --------------------------------------------------------------
;  mdm_regs.asm:       1131 ; VITAPMSEL4
;  mdm_regs.asm:       1132 ; 
;  mdm_regs.asm:       1133 VITAPMSEL4                                        .assign   134
;  mdm_regs.asm:       1134 VITAPMSEL4_APM3MUX                                .assign     9 ;
;  mdm_regs.asm:       1135 VITAPMSEL4_APM2MUX                                .assign     6 ;
;  mdm_regs.asm:       1136 VITAPMSEL4_APM1MUX                                .assign     3 ;
;  mdm_regs.asm:       1137 VITAPMSEL4_APM0MUX                                .assign     0 ;
;  mdm_regs.asm:       1138 ; --------------------------------------------------------------
;  mdm_regs.asm:       1139 ; VITBRSEL5
;  mdm_regs.asm:       1140 ; 
;  mdm_regs.asm:       1141 VITBRSEL5                                         .assign   135
;  mdm_regs.asm:       1142 VITBRSEL5_BR3MUX                                  .assign     9 ;
;  mdm_regs.asm:       1143 VITBRSEL5_BR2MUX                                  .assign     6 ;
;  mdm_regs.asm:       1144 VITBRSEL5_BR1MUX                                  .assign     3 ;
;  mdm_regs.asm:       1145 VITBRSEL5_BR0MUX                                  .assign     0 ;
;  mdm_regs.asm:       1146 ; --------------------------------------------------------------
;  mdm_regs.asm:       1147 ; VITAPMSEL5
;  mdm_regs.asm:       1148 ; 
;  mdm_regs.asm:       1149 VITAPMSEL5                                        .assign   136
;  mdm_regs.asm:       1150 VITAPMSEL5_APM3MUX                                .assign     9 ;
;  mdm_regs.asm:       1151 VITAPMSEL5_APM2MUX                                .assign     6 ;
;  mdm_regs.asm:       1152 VITAPMSEL5_APM1MUX                                .assign     3 ;
;  mdm_regs.asm:       1153 VITAPMSEL5_APM0MUX                                .assign     0 ;
;  mdm_regs.asm:       1154 ; --------------------------------------------------------------
;  mdm_regs.asm:       1155 ; VITBRSEL6
;  mdm_regs.asm:       1156 ; 
;  mdm_regs.asm:       1157 VITBRSEL6                                         .assign   137
;  mdm_regs.asm:       1158 VITBRSEL6_BR3MUX                                  .assign     9 ;
;  mdm_regs.asm:       1159 VITBRSEL6_BR2MUX                                  .assign     6 ;
;  mdm_regs.asm:       1160 VITBRSEL6_BR1MUX                                  .assign     3 ;
;  mdm_regs.asm:       1161 VITBRSEL6_BR0MUX                                  .assign     0 ;
;  mdm_regs.asm:       1162 ; --------------------------------------------------------------
;  mdm_regs.asm:       1163 ; VITAPMSEL6
;  mdm_regs.asm:       1164 ; 
;  mdm_regs.asm:       1165 VITAPMSEL6                                        .assign   138
;  mdm_regs.asm:       1166 VITAPMSEL6_APM3MUX                                .assign     9 ;
;  mdm_regs.asm:       1167 VITAPMSEL6_APM2MUX                                .assign     6 ;
;  mdm_regs.asm:       1168 VITAPMSEL6_APM1MUX                                .assign     3 ;
;  mdm_regs.asm:       1169 VITAPMSEL6_APM0MUX                                .assign     0 ;
;  mdm_regs.asm:       1170 ; --------------------------------------------------------------
;  mdm_regs.asm:       1171 ; VITBRSEL7
;  mdm_regs.asm:       1172 ; 
;  mdm_regs.asm:       1173 VITBRSEL7                                         .assign   139
;  mdm_regs.asm:       1174 VITBRSEL7_BR3MUX                                  .assign     9 ;
;  mdm_regs.asm:       1175 VITBRSEL7_BR2MUX                                  .assign     6 ;
;  mdm_regs.asm:       1176 VITBRSEL7_BR1MUX                                  .assign     3 ;
;  mdm_regs.asm:       1177 VITBRSEL7_BR0MUX                                  .assign     0 ;
;  mdm_regs.asm:       1178 ; --------------------------------------------------------------
;  mdm_regs.asm:       1179 ; VITAPMSEL7
;  mdm_regs.asm:       1180 ; 
;  mdm_regs.asm:       1181 VITAPMSEL7                                        .assign   140
;  mdm_regs.asm:       1182 VITAPMSEL7_APM3MUX                                .assign     9 ;
;  mdm_regs.asm:       1183 VITAPMSEL7_APM2MUX                                .assign     6 ;
;  mdm_regs.asm:       1184 VITAPMSEL7_APM1MUX                                .assign     3 ;
;  mdm_regs.asm:       1185 VITAPMSEL7_APM0MUX                                .assign     0 ;
;  mdm_regs.asm:       1186 ; --------------------------------------------------------------
;  mdm_regs.asm:       1187 ; LOCMULTA
;  mdm_regs.asm:       1188 ; 
;  mdm_regs.asm:       1189 LOCMULTA                                          .assign   141
;  mdm_regs.asm:       1190 LOCMULTA_AVALUE                                   .assign     0 ;
;  mdm_regs.asm:       1191 ; --------------------------------------------------------------
;  mdm_regs.asm:       1192 ; LOCMULTB
;  mdm_regs.asm:       1193 ; 
;  mdm_regs.asm:       1194 LOCMULTB                                          .assign   142
;  mdm_regs.asm:       1195 LOCMULTB_BVALUE                                   .assign     0 ;
;  mdm_regs.asm:       1196 ; --------------------------------------------------------------
;  mdm_regs.asm:       1197 ; LOCMULTC0
;  mdm_regs.asm:       1198 ; 
;  mdm_regs.asm:       1199 LOCMULTC0                                         .assign   143
;  mdm_regs.asm:       1200 LOCMULTC0_C15C0                                   .assign     0 ;
;  mdm_regs.asm:       1201 ; --------------------------------------------------------------
;  mdm_regs.asm:       1202 ; LOCMULTC1
;  mdm_regs.asm:       1203 ; 
;  mdm_regs.asm:       1204 LOCMULTC1                                         .assign   144
;  mdm_regs.asm:       1205 LOCMULTC1_C31C16                                  .assign     0 ;
;  mdm_regs.asm:       1206 ; --------------------------------------------------------------
;  mdm_regs.asm:       1207 ; TIMCTRL
;  mdm_regs.asm:       1208 ; 
;  mdm_regs.asm:       1209 TIMCTRL                                           .assign   145
;  mdm_regs.asm:       1210 TIMCTRL_CAPTURESOURCE                             .assign     8 ;
;  mdm_regs.asm:       1211 TIMCTRL_ENABLECAPTURE                             .assign     7 ;
;  mdm_regs.asm:       1212 TIMCTRL_COUNTERSOURCE                             .assign     5 ;
;  mdm_regs.asm:       1213 TIMCTRL_CLEARCOUNTER                              .assign     4 ;
;  mdm_regs.asm:       1214 TIMCTRL_ENABLECOUNTER                             .assign     3 ;
;  mdm_regs.asm:       1215 TIMCTRL_TIMERSOURCE                               .assign     1 ;
;  mdm_regs.asm:       1216 TIMCTRL_ENABLETIMER                               .assign     0 ;
;  mdm_regs.asm:       1217 ; --------------------------------------------------------------
;  mdm_regs.asm:       1218 ; TIMINC
;  mdm_regs.asm:       1219 ; 
;  mdm_regs.asm:       1220 TIMINC                                            .assign   146
;  mdm_regs.asm:       1221 TIMINC_INCUNIT                                    .assign     0 ;
;  mdm_regs.asm:       1222 ; --------------------------------------------------------------
;  mdm_regs.asm:       1223 ; TIMPERIOD
;  mdm_regs.asm:       1224 ; 
;  mdm_regs.asm:       1225 TIMPERIOD                                         .assign   147
;  mdm_regs.asm:       1226 TIMPERIOD_PERIOD                                  .assign     0 ;
;  mdm_regs.asm:       1227 ; --------------------------------------------------------------
;  mdm_regs.asm:       1228 ; TIMCOUNTER
;  mdm_regs.asm:       1229 ; 
;  mdm_regs.asm:       1230 TIMCOUNTER                                        .assign   148
;  mdm_regs.asm:       1231 TIMCOUNTER_VALUE                                  .assign     0 ;
;  mdm_regs.asm:       1232 ; --------------------------------------------------------------
;  mdm_regs.asm:       1233 ; TIMCAPT
;  mdm_regs.asm:       1234 ; 
;  mdm_regs.asm:       1235 TIMCAPT                                           .assign   149
;  mdm_regs.asm:       1236 TIMCAPT_VALUE                                     .assign     0 ;
;  mdm_regs.asm:       1237 ; --------------------------------------------------------------
;  mdm_regs.asm:       1238 ; TIMEBASE
;  mdm_regs.asm:       1239 ; 
;  mdm_regs.asm:       1240 TIMEBASE                                          .assign   150
;  mdm_regs.asm:       1241 TIMEBASE_FLUSH                                    .assign     0 ;
;  mdm_regs.asm:       1242 ; --------------------------------------------------------------
;  mdm_regs.asm:       1243 ; COUNT1IN
;  mdm_regs.asm:       1244 ; 
;  mdm_regs.asm:       1245 COUNT1IN                                          .assign   151
;  mdm_regs.asm:       1246 COUNT1IN_VAL                                      .assign     0 ;
;  mdm_regs.asm:       1247 ; --------------------------------------------------------------
;  mdm_regs.asm:       1248 ; COUNT1RES
;  mdm_regs.asm:       1249 ; 
;  mdm_regs.asm:       1250 COUNT1RES                                         .assign   152
;  mdm_regs.asm:       1251 COUNT1RES_COUNT                                   .assign     0 ;
;  mdm_regs.asm:       1252 ; --------------------------------------------------------------
;  mdm_regs.asm:       1253 ; BRMACC0
;  mdm_regs.asm:       1254 ; 
;  mdm_regs.asm:       1255 BRMACC0                                           .assign   153
;  mdm_regs.asm:       1256 BRMACC0_SYM1ST                                    .assign     8 ;
;  mdm_regs.asm:       1257 BRMACC0_SYM2ND                                    .assign     0 ;
;  mdm_regs.asm:       1258 ; --------------------------------------------------------------
;  mdm_regs.asm:       1259 ; BRMACC1
;  mdm_regs.asm:       1260 ; 
;  mdm_regs.asm:       1261 BRMACC1                                           .assign   154
;  mdm_regs.asm:       1262 BRMACC1_METRIC01                                  .assign     8 ;
;  mdm_regs.asm:       1263 BRMACC1_METRIC00                                  .assign     0 ;
;  mdm_regs.asm:       1264 ; --------------------------------------------------------------
;  mdm_regs.asm:       1265 ; BRMACC2
;  mdm_regs.asm:       1266 ; 
;  mdm_regs.asm:       1267 BRMACC2                                           .assign   155
;  mdm_regs.asm:       1268 BRMACC2_METRIC11                                  .assign     8 ;
;  mdm_regs.asm:       1269 BRMACC2_METRIC10                                  .assign     0 ;
;  mdm_regs.asm:       1270 ; --------------------------------------------------------------
;  mdm_regs.asm:       1271 ; VITACCCTRL
;  mdm_regs.asm:       1272 ; 
;  mdm_regs.asm:       1273 VITACCCTRL                                        .assign   156
;  mdm_regs.asm:       1274 VITACCCTRL_POLYNOM1                               .assign     9 ;
;  mdm_regs.asm:       1275 VITACCCTRL_POLYNOM0                               .assign     2 ;
;  mdm_regs.asm:       1276 VITACCCTRL_CODELENGTH                             .assign     0 ;
;  mdm_regs.asm:       1277 ; --------------------------------------------------------------
;  mdm_regs.asm:       1278 ; VITACCRDBIT
;  mdm_regs.asm:       1279 ; 
;  mdm_regs.asm:       1280 VITACCRDBIT                                       .assign   157
;  mdm_regs.asm:       1281 VITACCRDBIT_RXBIT                                 .assign     0 ;
;  mdm_regs.asm:       1282 ; --------------------------------------------------------------
;  mdm_regs.asm:       1283 ; MCETRCSEND
;  mdm_regs.asm:       1284 ; 
;  mdm_regs.asm:       1285 MCETRCSEND                                        .assign   158
;  mdm_regs.asm:       1286 MCETRCSEND_SEND                                   .assign     0 ;
;  mdm_regs.asm:       1287 ; --------------------------------------------------------------
;  mdm_regs.asm:       1288 ; MCETRCBUSY
;  mdm_regs.asm:       1289 ; 
;  mdm_regs.asm:       1290 MCETRCBUSY                                        .assign   159
;  mdm_regs.asm:       1291 MCETRCBUSY_BUSY                                   .assign     0 ;
;  mdm_regs.asm:       1292 ; --------------------------------------------------------------
;  mdm_regs.asm:       1293 ; MCETRCCMD
;  mdm_regs.asm:       1294 ; 
;  mdm_regs.asm:       1295 MCETRCCMD                                         .assign   160
;  mdm_regs.asm:       1296 MCETRCCMD_PARCNT                                  .assign     8 ;
;  mdm_regs.asm:       1297 MCETRCCMD_PKTHDR                                  .assign     0 ;
;  mdm_regs.asm:       1298 ; --------------------------------------------------------------
;  mdm_regs.asm:       1299 ; MCETRCPAR0
;  mdm_regs.asm:       1300 ; 
;  mdm_regs.asm:       1301 MCETRCPAR0                                        .assign   161
;  mdm_regs.asm:       1302 MCETRCPAR0_PAR0                                   .assign     0 ;
;  mdm_regs.asm:       1303 ; --------------------------------------------------------------
;  mdm_regs.asm:       1304 ; MCETRCPAR1
;  mdm_regs.asm:       1305 ; 
;  mdm_regs.asm:       1306 MCETRCPAR1                                        .assign   162
;  mdm_regs.asm:       1307 MCETRCPAR1_PAR1                                   .assign     0 ;
;  mdm_regs.asm:       1308 ; --------------------------------------------------------------
;  mdm_regs.asm:       1309 ; RDCAPT0
;  mdm_regs.asm:       1310 ; 
;  mdm_regs.asm:       1311 RDCAPT0                                           .assign   163
;  mdm_regs.asm:       1312 RDCAPT0_DEMDSBU1                                  .assign    15 ;
;  mdm_regs.asm:       1313 RDCAPT0_DEMC1BEX                                  .assign    14 ;
;  mdm_regs.asm:       1314 RDCAPT0_DEMSOFD0                                  .assign    13 ;
;  mdm_regs.asm:       1315 RDCAPT0_DEMLQIE0                                  .assign    12 ;
;  mdm_regs.asm:       1316 RDCAPT0_DEMSTIM1                                  .assign    11 ;
;  mdm_regs.asm:       1317 RDCAPT0_DEMSTIM0                                  .assign    10 ;
;  mdm_regs.asm:       1318 RDCAPT0_DEMFIFE2                                  .assign     9 ;
;  mdm_regs.asm:       1319 RDCAPT0_DEMPDIF0                                  .assign     8 ;
;  mdm_regs.asm:       1320 RDCAPT0_DEMCA2P0                                  .assign     7 ;
;  mdm_regs.asm:       1321 RDCAPT0_DEMFIDC4                                  .assign     6 ;
;  mdm_regs.asm:       1322 RDCAPT0_DEMFIDC3                                  .assign     5 ;
;  mdm_regs.asm:       1323 RDCAPT0_DEMMGEX2                                  .assign     4 ;
;  mdm_regs.asm:       1324 RDCAPT0_DEMMGEX1                                  .assign     3 ;
;  mdm_regs.asm:       1325 RDCAPT0_DEMDSBU0                                  .assign     2 ;
;  mdm_regs.asm:       1326 RDCAPT0_DEMCODC4                                  .assign     1 ;
;  mdm_regs.asm:       1327 RDCAPT0_DEMCODC3                                  .assign     0 ;
;  mdm_regs.asm:       1328 ; --------------------------------------------------------------
;  mdm_regs.asm:       1329 ; DEMCODC3
;  mdm_regs.asm:       1330 ; 
;  mdm_regs.asm:       1331 DEMCODC3                                          .assign   164
;  mdm_regs.asm:       1332 DEMCODC3_ESTOUTI                                  .assign     0 ;
;  mdm_regs.asm:       1333 ; --------------------------------------------------------------
;  mdm_regs.asm:       1334 ; DEMCODC4
;  mdm_regs.asm:       1335 ; 
;  mdm_regs.asm:       1336 DEMCODC4                                          .assign   165
;  mdm_regs.asm:       1337 DEMCODC4_ESTOUTQ                                  .assign     0 ;
;  mdm_regs.asm:       1338 ; --------------------------------------------------------------
;  mdm_regs.asm:       1339 ; DEMMGEx1
;  mdm_regs.asm:       1340 ; 
;  mdm_regs.asm:       1341 DEMMGEX1                                          .assign   166
;  mdm_regs.asm:       1342 DEMMGEX1_MGE1ESTOUT                               .assign     0 ;
;  mdm_regs.asm:       1343 ; --------------------------------------------------------------
;  mdm_regs.asm:       1344 ; DEMMGEx2
;  mdm_regs.asm:       1345 ; 
;  mdm_regs.asm:       1346 DEMMGEX2                                          .assign   167
;  mdm_regs.asm:       1347 DEMMGEX2_MGE2ESTOUT                               .assign     0 ;
;  mdm_regs.asm:       1348 ; --------------------------------------------------------------
;  mdm_regs.asm:       1349 ; DEMFIDC3
;  mdm_regs.asm:       1350 ; 
;  mdm_regs.asm:       1351 DEMFIDC3                                          .assign   168
;  mdm_regs.asm:       1352 DEMFIDC3_ESTOUTI                                  .assign     0 ;
;  mdm_regs.asm:       1353 ; --------------------------------------------------------------
;  mdm_regs.asm:       1354 ; DEMFIDC4
;  mdm_regs.asm:       1355 ; 
;  mdm_regs.asm:       1356 DEMFIDC4                                          .assign   169
;  mdm_regs.asm:       1357 DEMFIDC4_ESTOUTQ                                  .assign     0 ;
;  mdm_regs.asm:       1358 ; --------------------------------------------------------------
;  mdm_regs.asm:       1359 ; DEMCA2P0
;  mdm_regs.asm:       1360 ; 
;  mdm_regs.asm:       1361 DEMCA2P0                                          .assign   170
;  mdm_regs.asm:       1362 DEMCA2P0_PHASE                                    .assign     0 ;
;  mdm_regs.asm:       1363 ; --------------------------------------------------------------
;  mdm_regs.asm:       1364 ; DEMPDIF0
;  mdm_regs.asm:       1365 ; 
;  mdm_regs.asm:       1366 DEMPDIF0                                          .assign   171
;  mdm_regs.asm:       1367 DEMPDIF0_PDIFF                                    .assign     0 ;
;  mdm_regs.asm:       1368 ; --------------------------------------------------------------
;  mdm_regs.asm:       1369 ; DEMC1BE3
;  mdm_regs.asm:       1370 ; 
;  mdm_regs.asm:       1371 DEMC1BE3                                          .assign   172
;  mdm_regs.asm:       1372 DEMC1BE3_CORRVALUEA                               .assign     0 ;
;  mdm_regs.asm:       1373 ; --------------------------------------------------------------
;  mdm_regs.asm:       1374 ; DEMC1BE4
;  mdm_regs.asm:       1375 ; 
;  mdm_regs.asm:       1376 DEMC1BE4                                          .assign   173
;  mdm_regs.asm:       1377 DEMC1BE4_CORRVALUEB                               .assign     0 ;
;  mdm_regs.asm:       1378 ; --------------------------------------------------------------
;  mdm_regs.asm:       1379 ; DEMC1BE5
;  mdm_regs.asm:       1380 ; 
;  mdm_regs.asm:       1381 DEMC1BE5                                          .assign   174
;  mdm_regs.asm:       1382 DEMC1BE5_CORRVALUEC                               .assign     0 ;
;  mdm_regs.asm:       1383 ; --------------------------------------------------------------
;  mdm_regs.asm:       1384 ; DEMFIFE2
;  mdm_regs.asm:       1385 ; 
;  mdm_regs.asm:       1386 DEMFIFE2                                          .assign   175
;  mdm_regs.asm:       1387 DEMFIFE2_FINEFOCEST                               .assign     0 ;
;  mdm_regs.asm:       1388 ; --------------------------------------------------------------
;  mdm_regs.asm:       1389 ; DEMDSBU0
;  mdm_regs.asm:       1390 ; 
;  mdm_regs.asm:       1391 DEMDSBU0                                          .assign   176
;  mdm_regs.asm:       1392 DEMDSBU0_RDPOUT                                   .assign     0 ;
;  mdm_regs.asm:       1393 ; --------------------------------------------------------------
;  mdm_regs.asm:       1394 ; DEMDSBU1
;  mdm_regs.asm:       1395 ; 
;  mdm_regs.asm:       1396 DEMDSBU1                                          .assign   177
;  mdm_regs.asm:       1397 DEMDSBU1_AVGVAL                                   .assign     0 ;
;  mdm_regs.asm:       1398 ; --------------------------------------------------------------
;  mdm_regs.asm:       1399 ; DEMSTIM0
;  mdm_regs.asm:       1400 ; 
;  mdm_regs.asm:       1401 DEMSTIM0                                          .assign   178
;  mdm_regs.asm:       1402 DEMSTIM0_EVENTS                                   .assign     0 ;
;  mdm_regs.asm:       1403 ; --------------------------------------------------------------
;  mdm_regs.asm:       1404 ; DEMSTIM1
;  mdm_regs.asm:       1405 ; 
;  mdm_regs.asm:       1406 DEMSTIM1                                          .assign   179
;  mdm_regs.asm:       1407 DEMSTIM1_GARDNERERROR                             .assign     4 ;
;  mdm_regs.asm:       1408 DEMSTIM1_DELTA                                    .assign     0 ;
;  mdm_regs.asm:       1409 ; --------------------------------------------------------------
;  mdm_regs.asm:       1410 ; DEMSWQU1
;  mdm_regs.asm:       1411 ; 
;  mdm_regs.asm:       1412 DEMSWQU1                                          .assign   180
;  mdm_regs.asm:       1413 DEMSWQU1_MAFCCOMPVAL                              .assign     2 ;
;  mdm_regs.asm:       1414 DEMSWQU1_SWSEL                                    .assign     1 ;
;  mdm_regs.asm:       1415 DEMSWQU1_SYNCED                                   .assign     0 ;
;  mdm_regs.asm:       1416 ; --------------------------------------------------------------
;  mdm_regs.asm:       1417 ; DEMLQIE0
;  mdm_regs.asm:       1418 ; 
;  mdm_regs.asm:       1419 DEMLQIE0                                          .assign   181
;  mdm_regs.asm:       1420 DEMLQIE0_LQI                                      .assign     0 ;
;  mdm_regs.asm:       1421 ; --------------------------------------------------------------
;  mdm_regs.asm:       1422 ; DEMSOFD0
;  mdm_regs.asm:       1423 ; 
;  mdm_regs.asm:       1424 DEMSOFD0                                          .assign   182
;  mdm_regs.asm:       1425 DEMSOFD0_SOFTSYMBOL                               .assign     0 ;
;  mdm_regs.asm:       1426 ; --------------------------------------------------------------
;  mdm_regs.asm:       1427 ; RDCAPT1
;  mdm_regs.asm:       1428 ; 
;  mdm_regs.asm:       1429 RDCAPT1                                           .assign   183
;  mdm_regs.asm:       1430 RDCAPT1_DEMHDIS0                                  .assign    13 ;
;  mdm_regs.asm:       1431 RDCAPT1_DEMFB2P2                                  .assign    12 ;
;  mdm_regs.asm:       1432 RDCAPT1_DEMPHAC                                   .assign    11 ;
;  mdm_regs.asm:       1433 RDCAPT1_DEMMAFI5                                  .assign    10 ;
;  mdm_regs.asm:       1434 RDCAPT1_DEMMLSE4BITS                              .assign     9 ;
;  mdm_regs.asm:       1435 RDCAPT1_DEMPNSOFT                                 .assign     8 ;
;  mdm_regs.asm:       1436 RDCAPT1_DEMMLSEBIT                                .assign     7 ;
;  mdm_regs.asm:       1437 RDCAPT1_DEMTHRD4                                  .assign     6 ;
;  mdm_regs.asm:       1438 RDCAPT1_DEMBDEC0                                  .assign     5 ;
;  mdm_regs.asm:       1439 RDCAPT1_DEMBDEC1                                  .assign     4 ;
;  mdm_regs.asm:       1440 RDCAPT1_DEMCHFI0                                  .assign     3 ;
;  mdm_regs.asm:       1441 RDCAPT1_DEMCHFI1                                  .assign     2 ;
;  mdm_regs.asm:       1442 RDCAPT1_DEMFRAC4                                  .assign     1 ;
;  mdm_regs.asm:       1443 RDCAPT1_DEMFRAC5                                  .assign     0 ;
;  mdm_regs.asm:       1444 ; --------------------------------------------------------------
;  mdm_regs.asm:       1445 ; DEMTHRD4
;  mdm_regs.asm:       1446 ; 
;  mdm_regs.asm:       1447 DEMTHRD4                                          .assign   184
;  mdm_regs.asm:       1448 DEMTHRD4_DECISION                                 .assign     0 ;
;  mdm_regs.asm:       1449 ; --------------------------------------------------------------
;  mdm_regs.asm:       1450 ; DEMMLSEBIT
;  mdm_regs.asm:       1451 ; 
;  mdm_regs.asm:       1452 DEMMLSEBIT                                        .assign   185
;  mdm_regs.asm:       1453 DEMMLSEBIT_MLSEBIT                                .assign     0 ;
;  mdm_regs.asm:       1454 ; --------------------------------------------------------------
;  mdm_regs.asm:       1455 ; DEMMLSE4BITS
;  mdm_regs.asm:       1456 ; 
;  mdm_regs.asm:       1457 DEMMLSE4BITS                                      .assign   186
;  mdm_regs.asm:       1458 DEMMLSE4BITS_MLSE4BITS                            .assign     0 ;
;  mdm_regs.asm:       1459 ; --------------------------------------------------------------
;  mdm_regs.asm:       1460 ; DEMBDEC0
;  mdm_regs.asm:       1461 ; 
;  mdm_regs.asm:       1462 DEMBDEC0                                          .assign   187
;  mdm_regs.asm:       1463 DEMBDEC0_IVAL                                     .assign     0 ;
;  mdm_regs.asm:       1464 ; --------------------------------------------------------------
;  mdm_regs.asm:       1465 ; DEMBDEC1
;  mdm_regs.asm:       1466 ; 
;  mdm_regs.asm:       1467 DEMBDEC1                                          .assign   188
;  mdm_regs.asm:       1468 DEMBDEC1_QVAL                                     .assign     0 ;
;  mdm_regs.asm:       1469 ; --------------------------------------------------------------
;  mdm_regs.asm:       1470 ; DEMCHFI0
;  mdm_regs.asm:       1471 ; 
;  mdm_regs.asm:       1472 DEMCHFI0                                          .assign   189
;  mdm_regs.asm:       1473 DEMCHFI0_IVAL                                     .assign     0 ;
;  mdm_regs.asm:       1474 ; --------------------------------------------------------------
;  mdm_regs.asm:       1475 ; DEMCHFI1
;  mdm_regs.asm:       1476 ; 
;  mdm_regs.asm:       1477 DEMCHFI1                                          .assign   190
;  mdm_regs.asm:       1478 DEMCHFI1_QVAL                                     .assign     0 ;
;  mdm_regs.asm:       1479 ; --------------------------------------------------------------
;  mdm_regs.asm:       1480 ; DEMFRAC4
;  mdm_regs.asm:       1481 ; 
;  mdm_regs.asm:       1482 DEMFRAC4                                          .assign   191
;  mdm_regs.asm:       1483 DEMFRAC4_IVAL                                     .assign     0 ;
;  mdm_regs.asm:       1484 ; --------------------------------------------------------------
;  mdm_regs.asm:       1485 ; DEMFRAC5
;  mdm_regs.asm:       1486 ; 
;  mdm_regs.asm:       1487 DEMFRAC5                                          .assign   192
;  mdm_regs.asm:       1488 DEMFRAC5_QVAL                                     .assign     0 ;
;  mdm_regs.asm:       1489 ; --------------------------------------------------------------
;  mdm_regs.asm:       1490 ; DEMPNSOFT
;  mdm_regs.asm:       1491 ; 
;  mdm_regs.asm:       1492 DEMPNSOFT                                         .assign   193
;  mdm_regs.asm:       1493 DEMPNSOFT_PNSOFT                                  .assign     0 ;
;  mdm_regs.asm:       1494 ; --------------------------------------------------------------
;  mdm_regs.asm:       1495 ; DEMMAFI5
;  mdm_regs.asm:       1496 ; 
;  mdm_regs.asm:       1497 DEMMAFI5                                          .assign   194
;  mdm_regs.asm:       1498 DEMMAFI5_MAFIOUT                                  .assign     0 ;
;  mdm_regs.asm:       1499 ; --------------------------------------------------------------
;  mdm_regs.asm:       1500 ; DEMC1BE6
;  mdm_regs.asm:       1501 ; 
;  mdm_regs.asm:       1502 DEMC1BE6                                          .assign   195
;  mdm_regs.asm:       1503 DEMC1BE6_VAL                                      .assign     0 ;
;  mdm_regs.asm:       1504 ; --------------------------------------------------------------
;  mdm_regs.asm:       1505 ; DEMC1BE7
;  mdm_regs.asm:       1506 ; 
;  mdm_regs.asm:       1507 DEMC1BE7                                          .assign   196
;  mdm_regs.asm:       1508 DEMC1BE7_VAL                                      .assign     0 ;
;  mdm_regs.asm:       1509 ; --------------------------------------------------------------
;  mdm_regs.asm:       1510 ; DEMC1BE8
;  mdm_regs.asm:       1511 ; 
;  mdm_regs.asm:       1512 DEMC1BE8                                          .assign   197
;  mdm_regs.asm:       1513 DEMC1BE8_VAL                                      .assign     0 ;
;  mdm_regs.asm:       1514 ; --------------------------------------------------------------
;  mdm_regs.asm:       1515 ; DEMC1BE9
;  mdm_regs.asm:       1516 ; 
;  mdm_regs.asm:       1517 DEMC1BE9                                          .assign   198
;  mdm_regs.asm:       1518 DEMC1BE9_VAL                                      .assign     0 ;
;  mdm_regs.asm:       1519 ; --------------------------------------------------------------
;  mdm_regs.asm:       1520 ; DEMC1BEA
;  mdm_regs.asm:       1521 ; 
;  mdm_regs.asm:       1522 DEMC1BEA                                          .assign   199
;  mdm_regs.asm:       1523 DEMC1BEA_QUALB                                    .assign     6 ;
;  mdm_regs.asm:       1524 DEMC1BEA_QUALA                                    .assign     0 ;
;  mdm_regs.asm:       1525 ; --------------------------------------------------------------
;  mdm_regs.asm:       1526 ; MDMSPAR0
;  mdm_regs.asm:       1527 ; 
;  mdm_regs.asm:       1528 MDMSPAR0                                          .assign   200
;  mdm_regs.asm:       1529 MDMSPAR0_VAL                                      .assign     0 ;
;  mdm_regs.asm:       1530 ; --------------------------------------------------------------
;  mdm_regs.asm:       1531 ; MDMSPAR1
;  mdm_regs.asm:       1532 ; 
;  mdm_regs.asm:       1533 MDMSPAR1                                          .assign   201
;  mdm_regs.asm:       1534 MDMSPAR1_VAL                                      .assign     0 ;
;  mdm_regs.asm:       1535 ; --------------------------------------------------------------
;  mdm_regs.asm:       1536 ; MDMSPAR2
;  mdm_regs.asm:       1537 ; 
;  mdm_regs.asm:       1538 MDMSPAR2                                          .assign   202
;  mdm_regs.asm:       1539 MDMSPAR2_VAL                                      .assign     0 ;
;  mdm_regs.asm:       1540 ; --------------------------------------------------------------
;  mdm_regs.asm:       1541 ; MDMSPAR3
;  mdm_regs.asm:       1542 ; 
;  mdm_regs.asm:       1543 MDMSPAR3                                          .assign   203
;  mdm_regs.asm:       1544 MDMSPAR3_VAL                                      .assign     0 ;
;  mdm_regs.asm:       1545 ; --------------------------------------------------------------
;  mdm_regs.asm:       1546 ; DEMSOFD1
;  mdm_regs.asm:       1547 ; 
;  mdm_regs.asm:       1548 DEMSOFD1                                          .assign   204
;  mdm_regs.asm:       1549 DEMSOFD1_SOFTX0                                   .assign     0 ;
;  mdm_regs.asm:       1550 ; --------------------------------------------------------------
;  mdm_regs.asm:       1551 ; DEMSOFD2
;  mdm_regs.asm:       1552 ; 
;  mdm_regs.asm:       1553 DEMSOFD2                                          .assign   205
;  mdm_regs.asm:       1554 DEMSOFD2_SOFTX1                                   .assign     0 ;
;  mdm_regs.asm:       1555 ; --------------------------------------------------------------
;  mdm_regs.asm:       1556 ; DEMSOFD3
;  mdm_regs.asm:       1557 ; 
;  mdm_regs.asm:       1558 DEMSOFD3                                          .assign   206
;  mdm_regs.asm:       1559 DEMSOFD3_SOFTX2                                   .assign     0 ;
;  mdm_regs.asm:       1560 ; --------------------------------------------------------------
;  mdm_regs.asm:       1561 ; DEMSOFD4
;  mdm_regs.asm:       1562 ; 
;  mdm_regs.asm:       1563 DEMSOFD4                                          .assign   207
;  mdm_regs.asm:       1564 DEMSOFD4_SOFTX3                                   .assign     0 ;
;  mdm_regs.asm:       1565 ; --------------------------------------------------------------
;  mdm_regs.asm:       1566 ; DEMC1BE14
;  mdm_regs.asm:       1567 ; 
;  mdm_regs.asm:       1568 DEMC1BE14                                         .assign   208
;  mdm_regs.asm:       1569 DEMC1BE14_CORRVALUEE                              .assign     0 ;
;  mdm_regs.asm:       1570 ; --------------------------------------------------------------
;  mdm_regs.asm:       1571 ; DEMC1BE15
;  mdm_regs.asm:       1572 ; 
;  mdm_regs.asm:       1573 DEMC1BE15                                         .assign   209
;  mdm_regs.asm:       1574 DEMC1BE15_CORRVALUEF                              .assign     0 ;
;  mdm_regs.asm:       1575 ; --------------------------------------------------------------
;  mdm_regs.asm:       1576 ; DEMC1BE16
;  mdm_regs.asm:       1577 ; 
;  mdm_regs.asm:       1578 DEMC1BE16                                         .assign   210
;  mdm_regs.asm:       1579 DEMC1BE16_VAL                                     .assign     0 ;
;  mdm_regs.asm:       1580 ; --------------------------------------------------------------
;  mdm_regs.asm:       1581 ; DEMC1BE17
;  mdm_regs.asm:       1582 ; 
;  mdm_regs.asm:       1583 DEMC1BE17                                         .assign   211
;  mdm_regs.asm:       1584 DEMC1BE17_VAL                                     .assign     0 ;
;  mdm_regs.asm:       1585 ; --------------------------------------------------------------
;  mdm_regs.asm:       1586 ; DEMC1BE18
;  mdm_regs.asm:       1587 ; 
;  mdm_regs.asm:       1588 DEMC1BE18                                         .assign   212
;  mdm_regs.asm:       1589 DEMC1BE18_VAL                                     .assign     0 ;
;  mdm_regs.asm:       1590 ; --------------------------------------------------------------
;  mdm_regs.asm:       1591 ; DEMC1BE19
;  mdm_regs.asm:       1592 ; 
;  mdm_regs.asm:       1593 DEMC1BE19                                         .assign   213
;  mdm_regs.asm:       1594 DEMC1BE19_VAL                                     .assign     0 ;
;  mdm_regs.asm:       1595 ; --------------------------------------------------------------
;  mdm_regs.asm:       1596 ; DEMC1BE20
;  mdm_regs.asm:       1597 ; 
;  mdm_regs.asm:       1598 DEMC1BE20                                         .assign   214
;  mdm_regs.asm:       1599 DEMC1BE20_CORRVALUEG                              .assign     0 ;
;  mdm_regs.asm:       1600 ; --------------------------------------------------------------
;  mdm_regs.asm:       1601 ; DEMDSBU3
;  mdm_regs.asm:       1602 ; 
;  mdm_regs.asm:       1603 DEMDSBU3                                          .assign   215
;  mdm_regs.asm:       1604 DEMDSBU3_WRPOUT                                   .assign     0 ;
;  mdm_regs.asm:       1605 ; --------------------------------------------------------------
;  mdm_regs.asm:       1606 ; MCEDUMP0
;  mdm_regs.asm:       1607 ; 
;  mdm_regs.asm:       1608 MCEDUMP0                                          .assign   216
;  mdm_regs.asm:       1609 MCEDUMP0_DONE                                     .assign     0 ;
;  mdm_regs.asm:       1610 ; --------------------------------------------------------------
;  mdm_regs.asm:       1611 ; MCEGPO0
;  mdm_regs.asm:       1612 ; 
;  mdm_regs.asm:       1613 MCEGPO0                                           .assign   217
;  mdm_regs.asm:       1614 MCEGPO0_HWDATAMUX                                 .assign    11 ;
;  mdm_regs.asm:       1615 MCEGPO0_HWCLKSTRETCH                              .assign     9 ;
;  mdm_regs.asm:       1616 MCEGPO0_HWCLKMUX                                  .assign     5 ;
;  mdm_regs.asm:       1617 MCEGPO0_FWCTRL                                    .assign     4 ;
;  mdm_regs.asm:       1618 MCEGPO0_GPO3                                      .assign     3 ;
;  mdm_regs.asm:       1619 MCEGPO0_GPO2                                      .assign     2 ;
;  mdm_regs.asm:       1620 MCEGPO0_GPO1                                      .assign     1 ;
;  mdm_regs.asm:       1621 MCEGPO0_GPO0                                      .assign     0 ;
;  mdm_regs.asm:       1622 ; --------------------------------------------------------------
;  mdm_regs.asm:       1623 ; DEMPHAC8
;  mdm_regs.asm:       1624 ; 
;  mdm_regs.asm:       1625 DEMPHAC8                                          .assign   218
;  mdm_regs.asm:       1626 DEMPHAC8_METRIC01                                 .assign     8 ;
;  mdm_regs.asm:       1627 DEMPHAC8_METRIC00                                 .assign     0 ;
;  mdm_regs.asm:       1628 ; --------------------------------------------------------------
;  mdm_regs.asm:       1629 ; DEMPHAC9
;  mdm_regs.asm:       1630 ; 
;  mdm_regs.asm:       1631 DEMPHAC9                                          .assign   219
;  mdm_regs.asm:       1632 DEMPHAC9_METRIC11                                 .assign     8 ;
;  mdm_regs.asm:       1633 DEMPHAC9_METRIC10                                 .assign     0 ;
;  mdm_regs.asm:       1634 ; --------------------------------------------------------------
;  mdm_regs.asm:       1635 ; DEMFB2P2
;  mdm_regs.asm:       1636 ; 
;  mdm_regs.asm:       1637 DEMFB2P2                                          .assign   220
;  mdm_regs.asm:       1638 DEMFB2P2_VAL                                      .assign     0 ;
;  mdm_regs.asm:       1639 ; --------------------------------------------------------------
;  mdm_regs.asm:       1640 ; DEMHDIS0
;  mdm_regs.asm:       1641 ; 
;  mdm_regs.asm:       1642 DEMHDIS0                                          .assign   221
;  mdm_regs.asm:       1643 DEMHDIS0_VAL                                      .assign     0 ;
;  mdm_regs.asm:       1644 
;  mdm_regs.asm:       1645 .endif ; _MDM_REGS_ASM_
;  mdm_regs.asm:       1646 ; eof
;  mce_ram_bank.asm:     30 .INCLUDE "../inc/mdmconf_iqdump_rom.asm"
;  mdmconf_iqdump_rom.asm:   1 ; -------------------------------------------------------------
;  mdmconf_iqdump_rom.asm:   2 ; This file is automatically generated by reg2conf script:
;  mdmconf_iqdump_rom.asm:   3 ;   /vobs/cc26xxAgamaFwDev/radio_domain/tools/topsm/regconf2asm.pl -reg /vobs/cc26xxIpDev/modules/cc26_rfcore_ig/doc/MCEregs.txt -conf /vobs/cc26xxAgamaFwDev/radio_domain/patch/topsm_iqdump/mce/doc/mdmconf_iqdump.txt ?packregs
;  mdmconf_iqdump_rom.asm:   4 ; File generated at 09-Mar-2021 17:46
;  mdmconf_iqdump_rom.asm:   5 ; -------------------------------------------------------------
;  mdmconf_iqdump_rom.asm:   6 
;  mdmconf_iqdump_rom.asm:   7 
;  mdmconf_iqdump_rom.asm:   8         ;; Register bank data for configuration:
;  mdmconf_iqdump_rom.asm:   9 
;  mdmconf_iqdump_rom.asm:  10         ;; MDMCONF_IQDUMP
;  mdmconf_iqdump_rom.asm:  11         ;; Modem Config IQDUMP
;  mdmconf_iqdump_rom.asm:  12 
;  mdmconf_iqdump_rom.asm:  13 
;  mdmconf_iqdump_rom.asm:  14 ;;; First and last destination register
;  mdmconf_iqdump_rom.asm:  15 .DEFINE MDMCONF_IQDUMP_FIRST_REG 43 		; ADCDIGCONF
;  mdmconf_iqdump_rom.asm:  16 .DEFINE MDMCONF_IQDUMP_LAST_REG  78 		; DEMSWQU0
;  mdmconf_iqdump_rom.asm:  17 
;  mdmconf_iqdump_rom.asm:  18 ;;; Length of configuration (number of .DATA words)
;  mdmconf_iqdump_rom.asm:  19 .DEFINE MDMCONF_IQDUMP_LENGTH    36
;  mdmconf_iqdump_rom.asm:  20 
;  mdmconf_iqdump_rom.asm:  21 
;  mdmconf_iqdump_rom.asm:  22 ;;; Start of MDMCONF_IQDUMP configuration data
;  mdmconf_iqdump_rom.asm:  23 ;;; (each data word contains one register value, each register value is 16 bits)
;  mdmconf_iqdump_rom.asm:  24 
;  mdmconf_iqdump_rom.asm:  25 .ORG MDMCONF_IQDUMP
;  mdmconf_iqdump_rom.asm:  26 
;  mdmconf_iqdump_rom.asm:  27 .DATA 0x0003                                        ; ADCDIGCONF 
;  mdmconf_iqdump_rom.asm:  28 .DATA 0x0017                                        ; MODPRECTRL 
;  mdmconf_iqdump_rom.asm:  29 .DATA 0x3D1F                                        ; MODSYMMAP0 
;  mdmconf_iqdump_rom.asm:  30 .DATA 0x0000                                        ; MODSYMMAP1 
;  mdmconf_iqdump_rom.asm:  31 .DATA 0x0000                                        ; MODSOFTTX 
;  mdmconf_iqdump_rom.asm:  32 .DATA 0x0800                                        ; MDMBAUD 
;  mdmconf_iqdump_rom.asm:  33 .DATA 0x000F                                        ; MDMBAUDPRE 
;  mdmconf_iqdump_rom.asm:  34 .DATA 0x0000                                        ; MODMAIN 
;  mdmconf_iqdump_rom.asm:  35 .DATA 0x0387                                        ; DEMMISC0 
;  mdmconf_iqdump_rom.asm:  36 .DATA 0x0000                                        ; DEMMISC1 
;  mdmconf_iqdump_rom.asm:  37 .DATA 0x4074                                        ; DEMMISC2 
;  mdmconf_iqdump_rom.asm:  38 .DATA 0x0043                                        ; DEMMISC3 
;  mdmconf_iqdump_rom.asm:  39 .DATA 0x8000                                        ; DEMIQMC0 
;  mdmconf_iqdump_rom.asm:  40 .DATA 0x0082                                        ; DEMDSBU 
;  mdmconf_iqdump_rom.asm:  41 .DATA 0x0080                                        ; DEMDSBU2 
;  mdmconf_iqdump_rom.asm:  42 .DATA 0x06F0                                        ; DEMCODC0 
;  mdmconf_iqdump_rom.asm:  43 .DATA 0x0000                                        ; DEMFIDC0 
;  mdmconf_iqdump_rom.asm:  44 .DATA 0x091E                                        ; DEMFEXB0 
;  mdmconf_iqdump_rom.asm:  45 .DATA 0x0510                                        ; DEMDSXB0 
;  mdmconf_iqdump_rom.asm:  46 .DATA 0x0054                                        ; DEMD2XB0 
;  mdmconf_iqdump_rom.asm:  47 .DATA 0x0007                                        ; DEMFIFE0 
;  mdmconf_iqdump_rom.asm:  48 .DATA 0x0000                                        ; DEMMAFI0 
;  mdmconf_iqdump_rom.asm:  49 .DATA 0x5014                                        ; DEMMAFI1 
;  mdmconf_iqdump_rom.asm:  50 .DATA 0x0050                                        ; DEMMAFI2 
;  mdmconf_iqdump_rom.asm:  51 .DATA 0x0000                                        ; DEMMAFI3 
;  mdmconf_iqdump_rom.asm:  52 .DATA 0xC02F                                        ; DEMC1BE0 
;  mdmconf_iqdump_rom.asm:  53 .DATA 0x0C30                                        ; DEMC1BE1 
;  mdmconf_iqdump_rom.asm:  54 .DATA 0x017F                                        ; DEMC1BE2 
;  mdmconf_iqdump_rom.asm:  55 .DATA 0x0000                                        ; DEMC1BE10 
;  mdmconf_iqdump_rom.asm:  56 .DATA 0x0000                                        ; DEMC1BE11 
;  mdmconf_iqdump_rom.asm:  57 .DATA 0x0000                                        ; DEMC1BE12 
;  mdmconf_iqdump_rom.asm:  58 .DATA 0x0000                                        ; MDMSYNC0 
;  mdmconf_iqdump_rom.asm:  59 .DATA 0x0000                                        ; MDMSYNC1 
;  mdmconf_iqdump_rom.asm:  60 .DATA 0x0000                                        ; MDMSYNC2 
;  mdmconf_iqdump_rom.asm:  61 .DATA 0xAA00                                        ; MDMSYNC3 
;  mdmconf_iqdump_rom.asm:  62 .DATA 0x0000                                        ; DEMSWQU0 
;  mdmconf_iqdump_rom.asm:  63 
;  mdmconf_iqdump_rom.asm:  64 MDMCONF_IQDUMP_END:
;  mdmconf_iqdump_rom.asm:  65 ;;; End of configuration
;  mdmconf_iqdump_rom.asm:  66 
;  mce_ram_bank.asm:     31 
;  mce_ram_bank.asm:     32 ;;; --------------------------------------------------------------------------------
;  mce_ram_bank.asm:     33 ;;; Memory Map
;  mce_ram_bank.asm:     34 ;;; 
;  mce_ram_bank.asm:     35 .ORG 0
;  mce_ram_bank.asm:     36   jmp START_PROCESS
;  mce_ram_bank.asm:     37         
;  mce_ram_bank.asm:     38 .DEFINE LMD_DATA_SPACE         1           ;; LMD Data Space (Tables)
;  mce_ram_bank.asm:     39 .DEFINE MDMCONF_IQDUMP        12           ;; Configuration Information
;  mce_ram_bank.asm:     40 .DEFINE MAIN                  48           ;; Main Program
;  mce_ram_bank.asm:     41 
;  mce_ram_bank.asm:     42 ;;; --------------------------------------------------------------------------------
;  mce_ram_bank.asm:     43 ;;; Iqdump Data
;  mce_ram_bank.asm:     44 ;;; 
;  mce_ram_bank.asm:     45 .ORG LMD_DATA_SPACE
;  mce_ram_bank.asm:     46 
;  mce_ram_bank.asm:     47 DEMENABLE0_RX_IQDUMP:
;  mce_ram_bank.asm:     48         .DATA 0x2FCF            ; DEMENABLE0 settings (felp, frac,fidc,chfi,bdec,iqmc,mge2,codc,cmix)
;  mce_ram_bank.asm:     49 DEMENABLE1_RX_IQDUMP:
;  mce_ram_bank.asm:     50         .DATA 0x3F9D            ; DEMENABLE1
;  mce_ram_bank.asm:     51 
;  mce_ram_bank.asm:     52 VITACCCTRL_REG_DEFAULT:             ; Transp, downsample + IIR filter setting
;  mce_ram_bank.asm:     53         .DATA 0x0001            ; [7:0]=0:  no filter 
;  mce_ram_bank.asm:     54                                 ; [7:0]=1:  k=1/2
;  mce_ram_bank.asm:     55                                 ; [7:0]=2:  k=1/4         
;  mce_ram_bank.asm:     56                                 ; [7:0]=3:  k=1/8
;  mce_ram_bank.asm:     57                                 ; [15: 8]=0, no transparent downsample
;  mce_ram_bank.asm:     58                                 ; [15: 8]=1, transparent downsample by two
;  mce_ram_bank.asm:     59                                 ; [15: 8]=2, transparent downsample by four
;  mce_ram_bank.asm:     60                                 ; [15: 8]=3, transparent downsample by eight
;  mce_ram_bank.asm:     61                                 ; [15: 8]=4, transparent downsample by sixteen      
;  mce_ram_bank.asm:     62                 
;  mce_ram_bank.asm:     63 DEMC1BE0_MASKA_BITS:    ; Various bit masks
;  mce_ram_bank.asm:     64   .DATA 0x003F
;  mce_ram_bank.asm:     65 IQDUMP_MASK_BITS_15_8:  
;  mce_ram_bank.asm:     66   .DATA 0xFF00  
;  mce_ram_bank.asm:     67  
;  mce_ram_bank.asm:     68 IQDUMP_TEST_MAX_VAL:  
;  mce_ram_bank.asm:     69   .DATA 0x0FFF
;  mce_ram_bank.asm:     70 IQDUMP_MAX_POS_VAL:    
;  mce_ram_bank.asm:     71   .DATA 0x07FF    ; 2^11 - 1 = 2047
;  mce_ram_bank.asm:     72 IQDUMP_MIN_NEG_VAL:    
;  mce_ram_bank.asm:     73   .DATA 0xF800    ; -2048
;  mce_ram_bank.asm:     74 TRANSPARENT_CAPT:
;  mce_ram_bank.asm:     75   .DATA 0x0300    ; Combined RDCAPT0_DEMPDIF0 and RDCAPT0_DEMFIFE2
;  mce_ram_bank.asm:     76 CORR_DEFG_THR:  
;  mce_ram_bank.asm:     77   .DATA 0x8080
;  mce_ram_bank.asm:     78 TX_TONE_COUNT:
;  mce_ram_bank.asm:     79         .DATA 0x06            ; Default number of clock ticks for tone in front of preamble
;  mce_ram_bank.asm:     80 
;  mce_ram_bank.asm:     81 ;;; --------------------------------------------------------------------------------
;  mce_ram_bank.asm:     82 ;;; Start of the Program itself
;  mce_ram_bank.asm:     83 .ORG MAIN
;  mce_ram_bank.asm:     84         
;  mce_ram_bank.asm:     85 START_PROCESS:
;  mce_ram_bank.asm:     86         ;; Do hard initialization of all submodules of the modem
;  mce_ram_bank.asm:     87         outclr RFESEND    ; Clear RFE send
;  mce_ram_bank.asm:     88         jsr   MODCTRL_CLR          ; 
;  mce_ram_bank.asm:     89         outbclr DEMMISC2_MLSERUN,DEMMISC2 ;  Make sure MLSE can be stopped
;  mce_ram_bank.asm:     90         outbclr DEMSWQU0_RUN, DEMSWQU0    ; Make sure door is open for init        
;  mce_ram_bank.asm:     91         outset DEMENABLE0       ;
;  mce_ram_bank.asm:     92         outset DEMINIT0         ;
;  mce_ram_bank.asm:     93         outclr DEMENABLE0       ;
;  mce_ram_bank.asm:     94         outset DEMENABLE1       ;
;  mce_ram_bank.asm:     95         outset DEMINIT1         ;
;  mce_ram_bank.asm:     96         outclr DEMENABLE1       ;
;  mce_ram_bank.asm:     97         outset TIMCTRL          ;
;  mce_ram_bank.asm:     98         outclr TIMCTRL          ;
;  mce_ram_bank.asm:     99         outbset MDMENABLE_FB2PLL, MDMENABLE    ; enable fb2pll module so that can be reset
;  mce_ram_bank.asm:    100         lli    0x3FC, r0        ; dont't touch fifo and topsm        
;  mce_ram_bank.asm:    101         output r0, MDMINIT      ;
;  mce_ram_bank.asm:    102         outbclr MDMENABLE_FB2PLL, MDMENABLE    ; disable fb2pll module again
;  mce_ram_bank.asm:    103         outclr MCEEVENTMSK0     ;
;  mce_ram_bank.asm:    104         outclr MCEEVENTMSK1     ;
;  mce_ram_bank.asm:    105         outclr MCEEVENTMSK2     ;   
;  mce_ram_bank.asm:    106         outclr MCEEVENTMSK3     ;   
;  mce_ram_bank.asm:    107 
;  mce_ram_bank.asm:    108 ;;; Move into Command processing
;  mce_ram_bank.asm:    109 ;;; --------------------------------------------------------------------------------
;  mce_ram_bank.asm:    110 ;;; Step 1. Main Command Processing Loop
;  mce_ram_bank.asm:    111         
;  mce_ram_bank.asm:    112 CMD_PROC:
;  mce_ram_bank.asm:    113         outbset MCEEVENT0_MDMAPI_WR, MCEEVENTMSK0  ; Enable event 0 = MDMAPI write
;  mce_ram_bank.asm:    114         wait            ; Waits until a command arrives
;  mce_ram_bank.asm:    115         outbset MCEEVENT0_MDMAPI_WR, MCEEVENTCLR0  ; Clear the event 0
;  mce_ram_bank.asm:    116         outbclr MCEEVENT0_MDMAPI_WR, MCEEVENTMSK0  ; Clear the event 0        
;  mce_ram_bank.asm:    117         outclr  MDMSTATUS       ; 
;  mce_ram_bank.asm:    118         input   MDMAPI, r2      ; Protocol ID [15:8] API [7:0] put together as [4:3][2:0]
;  mce_ram_bank.asm:    119         mov     r2, r0          ; Copy first into R0
;  mce_ram_bank.asm:    120         sr0     5, r2           ; Shift 5 positions R2
;  mce_ram_bank.asm:    121         and     7, r0           ; Clear all above bit 2 in R0
;  mce_ram_bank.asm:    122         or      r2, r0          ; Put them together
;  mce_ram_bank.asm:    123         add     3, r0           ; offset +3
;  mce_ram_bank.asm:    124         mov     pc, r1
;  mce_ram_bank.asm:    125         add     r0, r1
;  mce_ram_bank.asm:    126         jmp     (r1)
;  mce_ram_bank.asm:    127         jmp     MNOP_Entry           ; Jump tables Prot 0 Call 0 (MNOP)
;  mce_ram_bank.asm:    128         jmp     MCFG_Entry           ; Jump tables Prot 0 Call 1 (MCFG) 
;  mce_ram_bank.asm:    129         jmp     MTX_Entry            ; Jump tables Prot 0 Call 2 (MTX) 
;  mce_ram_bank.asm:    130         jmp     MRX_Entry_REG_BLIND  ; Jump tables Prot 0 Call 3 (MRX-BLIND-REGISTER MODE)
;  mce_ram_bank.asm:    131         jmp     MNOP_Entry           ; Jump tables Prot 0 Call 4 
;  mce_ram_bank.asm:    132         jmp     MNOP_Entry           ; Jump tables Prot 0 Call 5 
;  mce_ram_bank.asm:    133         jmp     MNOP_Entry           ; Jump tables Prot 0 Call 6 
;  mce_ram_bank.asm:    134         jmp     MNOP_Entry           ; Jump tables Prot 0 Call 7 
;  mce_ram_bank.asm:    135         jmp     MNOP_Entry           ; Jump tables Prot 1 Call 0
;  mce_ram_bank.asm:    136         jmp     MCFG_Entry           ; Jump tables Prot 1 Call 1 (MCFG) 
;  mce_ram_bank.asm:    137         jmp     MTX_Entry            ; Jump tables Prot 1 Call 2 (MTX)
;  mce_ram_bank.asm:    138         jmp     MRX_Entry_REG_SYNC   ; Jump tables Prot 1 Call 3 (MRX-SYNC-REGISTER MODE) 
;  mce_ram_bank.asm:    139         jmp     MNOP_Entry           ; Jump tables Prot 1 Call 4 
;  mce_ram_bank.asm:    140         jmp     MNOP_Entry           ; Jump tables Prot 1 Call 5 
;  mce_ram_bank.asm:    141         jmp     MNOP_Entry           ; Jump tables Prot 1 Call 6 
;  mce_ram_bank.asm:    142         jmp     MNOP_Entry           ; Jump tables Prot 1 Call 7 
;  mce_ram_bank.asm:    143         jmp     MNOP_Entry           ; Jump tables Prot 2 Call 0
;  mce_ram_bank.asm:    144         jmp     MCFG_Entry           ; Jump tables Prot 2 Call 1 (MCFG) 
;  mce_ram_bank.asm:    145         jmp     MTX_Entry            ; Jump tables Prot 2 Call 2 (MTX)
;  mce_ram_bank.asm:    146         jmp     MRX_Entry_FIFO_BLIND ; Jump tables Prot 2 Call 3 (MRX-BLIND-RFC FIFO MODE) 
;  mce_ram_bank.asm:    147         jmp     MNOP_Entry           ; Jump tables Prot 2 Call 4 
;  mce_ram_bank.asm:    148         jmp     MNOP_Entry           ; Jump tables Prot 2 Call 5 
;  mce_ram_bank.asm:    149         jmp     MNOP_Entry           ; Jump tables Prot 2 Call 6 
;  mce_ram_bank.asm:    150         jmp     MNOP_Entry           ; Jump tables Prot 2 Call 7 
;  mce_ram_bank.asm:    151         jmp     MNOP_Entry           ; Jump tables Prot 3 Call 0
;  mce_ram_bank.asm:    152         jmp     MCFG_Entry           ; Jump tables Prot 3 Call 1 (MCFG) 
;  mce_ram_bank.asm:    153         jmp     MTX_Entry            ; Jump tables Prot 3 Call 2 (MTX)
;  mce_ram_bank.asm:    154         jmp     MRX_Entry_FIFO_SYNC  ; Jump tables Prot 3 Call 3 (MRX-SYNC-RFC FIFO MODE)
;  mce_ram_bank.asm:    155         jmp     MNOP_Entry           ; Jump tables Prot 3 Call 4 
;  mce_ram_bank.asm:    156         jmp     MNOP_Entry           ; Jump tables Prot 3 Call 5 
;  mce_ram_bank.asm:    157         jmp     MNOP_Entry           ; Jump tables Prot 3 Call 6 
;  mce_ram_bank.asm:    158         jmp     MNOP_Entry           ; Jump tables Prot 3 Call 7 
;  mce_ram_bank.asm:    159         jmp     MNOP_Entry           ; Jump tables Prot 4 Call 0
;  mce_ram_bank.asm:    160         jmp     MCFG_Entry           ; Jump tables Prot 4 Call 1 (MCFG) 
;  mce_ram_bank.asm:    161         jmp     MTX_Entry            ; Jump tables Prot 4 Call 2 (MTX)
;  mce_ram_bank.asm:    162         jmp     MRX_Entry_TRANSPARENT_FIFO  ; Jump tables Prot 4 Call 3 (MRX-TRANSPARENT-RFC FIFO MODE)
;  mce_ram_bank.asm:    163 	jmp     MNOP_Entry           ; Jump tables Prot 4 Call 5 
;  mce_ram_bank.asm:    164         jmp     MNOP_Entry           ; Jump tables Prot 4 Call 6 
;  mce_ram_bank.asm:    165         jmp     MNOP_Entry           ; Jump tables Prot 4 Call 7
;  mce_ram_bank.asm:    166 	jmp     MNOP_Entry           ; Jump tables Prot 5 Call 0
;  mce_ram_bank.asm:    167         jmp     MCFG_Entry           ; Jump tables Prot 5 Call 1 (MCFG) 
;  mce_ram_bank.asm:    168         jmp     MTX_MFSK             ; Jump tables Prot 5 Call 2 (MTX multi mode)
;  mce_ram_bank.asm:    169 	jmp     MRX_Entry_FIFO_BLIND ; Jump tables Prot 5 Call 3 (MRX-BLIND-RFC FIFO MODE)
;  mce_ram_bank.asm:    170 
;  mce_ram_bank.asm:    171    
;  mce_ram_bank.asm:    172 
;  mce_ram_bank.asm:    173 ;;; End of Command Processing, start of the commands themselves
;  mce_ram_bank.asm:    174 
;  mce_ram_bank.asm:    175 ;;; --------------------------------------------------------------------------------
;  mce_ram_bank.asm:    176 ;;; General end of command routine
;  mce_ram_bank.asm:    177 ;;; 
;  mce_ram_bank.asm:    178 CMD_OK_END:
;  mce_ram_bank.asm:    179         mov     CMD_OK, r0  ; Normal end of command
;  mce_ram_bank.asm:    180 CPE_NOTIFY:        
;  mce_ram_bank.asm:    181         outclr  RFESEND    ; Clear RFE send
;  mce_ram_bank.asm:    182         outset  MCEEVENTCLR0    ; Clear all events: NOTE, this will BREAK command pipelining!
;  mce_ram_bank.asm:    183         outset  MCEEVENTCLR1    ; Clear all events
;  mce_ram_bank.asm:    184         outset  MCEEVENTCLR2    ; Clear all events
;  mce_ram_bank.asm:    185         input   MDMSTATUS, r1   ;
;  mce_ram_bank.asm:    186         or      r1, r0          ; 
;  mce_ram_bank.asm:    187         output  r0, MDMSTATUS
;  mce_ram_bank.asm:    188         outbset 0, MCESTROBES0  ; Notify CPE of completion
;  mce_ram_bank.asm:    189         jmp     CMD_PROC  ; Ready for another command
;  mce_ram_bank.asm:    190 
;  mce_ram_bank.asm:    191 ;;; --------------------------------------------------------------------------------
;  mce_ram_bank.asm:    192 ;;; MNOP
;  mce_ram_bank.asm:    193 ;;; 
;  mce_ram_bank.asm:    194        
;  mce_ram_bank.asm:    195 MNOP_Entry:
;  mce_ram_bank.asm:    196         jmp     CMD_OK_END
;  mce_ram_bank.asm:    197 
;  mce_ram_bank.asm:    198 
;  mce_ram_bank.asm:    199 ;;; --------------------------------------------------------------------------------
;  mce_ram_bank.asm:    200 ;;; iqdump IQDUMP (Generic FSK)
;  mce_ram_bank.asm:    201 ;;; 
;  mce_ram_bank.asm:    202 ;;; This iqdump supports a Generic 2(G)FSK modem in which most of the parameters
;  mce_ram_bank.asm:    203 ;;; are configured by the upper layer.
;  mce_ram_bank.asm:    204 ;;; In general, it uses the standard 2(G)FSK configuration, and supports three FECs
;  mce_ram_bank.asm:    205 ;;; Option 1) No FEC (use MLSE in RX)
;  mce_ram_bank.asm:    206 ;;; Option 2) 1/2 K=4 FEC, as defined in the 802.15.4g FSK standard 
;  mce_ram_bank.asm:    207 ;;; Option 3) TBD
;  mce_ram_bank.asm:    208 ;;; 
;  mce_ram_bank.asm:    209 ;;; --------------------------------------------------------------------------------
;  mce_ram_bank.asm:    210 
;  mce_ram_bank.asm:    211 ;;; --------------------------------------------------------------------------------
;  mce_ram_bank.asm:    212 ;;; MCFG
;  mce_ram_bank.asm:    213 ;;; --------------------------------------------------------------------------------
;  mce_ram_bank.asm:    214         
;  mce_ram_bank.asm:    215 MCFG_Entry:
;  mce_ram_bank.asm:    216         DBG_PRINT0 "MCFG - IQ Dump Configuration"
;  mce_ram_bank.asm:    217         lli     MDMCONF_IQDUMP, r1                 ; Points R1 to the WMBUS data
;  mce_ram_bank.asm:    218         lli     MDMCONF_IQDUMP_FIRST_REG, r2       ; Points to the first IO address for configiration
;  mce_ram_bank.asm:    219         lli     MDMCONF_IQDUMP_LAST_REG, r0        ; Points to the last of the IO address
;  mce_ram_bank.asm:    220         sub     r2,r0           ; R0 now holds number of iterations for CONF_LOOP, r0 implitly used by loop instruction
;  mce_ram_bank.asm:    221 MCFG_Iqdump_Loop:
;  mce_ram_bank.asm:    222         lmd     (r1), r3        ; Load ROM data
;  mce_ram_bank.asm:    223         output  r3, (r2)        ; Send to register bank
;  mce_ram_bank.asm:    224         add     1, r1           ; Increase memory pointer
;  mce_ram_bank.asm:    225         add     1, r2           ; Increase regbank pointer
;  mce_ram_bank.asm:    226         loop    MCFG_Iqdump_Loop   ;
;  mce_ram_bank.asm:    227 
;  mce_ram_bank.asm:    228         lmd  VITACCCTRL_REG_DEFAULT,r0
;  mce_ram_bank.asm:    229         output  r0,VITACCCTRL        
;  mce_ram_bank.asm:    230 
;  mce_ram_bank.asm:    231         lmd     CORR_DEFG_THR, r0
;  mce_ram_bank.asm:    232         output  r0, DEMC1BE11
;  mce_ram_bank.asm:    233         output  r0, DEMC1BE12
;  mce_ram_bank.asm:    234 
;  mce_ram_bank.asm:    235         lli     DEMFB2P0, r2    ; First register to clear
;  mce_ram_bank.asm:    236         lli     VITCTRL, r0  ; Last register to clear
;  mce_ram_bank.asm:    237         sub     r2,r0           ; R0 now holds number of iterations for first zero loop, r0 implitly used by loop instruction
;  mce_ram_bank.asm:    238         beq     ZERO_DONE       ; No values to write
;  mce_ram_bank.asm:    239         mov     0, r3           ; Set all regs to 0
;  mce_ram_bank.asm:    240 ZERO_LOOP:      
;  mce_ram_bank.asm:    241         output  r3, (r2)  ; Send to register bank
;  mce_ram_bank.asm:    242         add     1, r2    ; Increase regbank pointer
;  mce_ram_bank.asm:    243         loop    ZERO_LOOP       ;
;  mce_ram_bank.asm:    244 ZERO_DONE:
;  mce_ram_bank.asm:    245 
;  mce_ram_bank.asm:    246   ;; Set tone duration in BRMACC0
;  mce_ram_bank.asm:    247         lmd     TX_TONE_COUNT, r0                          ;
;  mce_ram_bank.asm:    248         output  r0, BRMACC0    ; 
;  mce_ram_bank.asm:    249         
;  mce_ram_bank.asm:    250   ;; Set Collision restart for CDC FIFO
;  mce_ram_bank.asm:    251         outclr  MODCTRL               ;
;  mce_ram_bank.asm:    252         outbset MODCTRL_CDC_COL_RESTART, MODCTRL  ; 
;  mce_ram_bank.asm:    253 
;  mce_ram_bank.asm:    254         jmp     CMD_OK_END      ; Done
;  mce_ram_bank.asm:    255 
;  mce_ram_bank.asm:    256 ;;; --------------------------------------------------------------------------------
;  mce_ram_bank.asm:    257 ;;; MTX Common Entry
;  mce_ram_bank.asm:    258 ;;; --------------------------------------------------------------------------------
;  mce_ram_bank.asm:    259 
;  mce_ram_bank.asm:    260 ;;; --------------------------------------------------------------------------
;  mce_ram_bank.asm:    261 ;;; MTX GenericFSK Send Preamble and Sync Word function
;  mce_ram_bank.asm:    262 ;;; 
;  mce_ram_bank.asm:    263 MTX_Iqdump_Common_Preamble:       
;  mce_ram_bank.asm:    264         ;; Fetch information from MDMPAR0|2: Preamble settings
;  mce_ram_bank.asm:    265         input   MDMCMDPAR2, r0
;  mce_ram_bank.asm:    266         output  r0, MODPREAMBLE                       ; Send directly to MODPREAMBLE
;  mce_ram_bank.asm:    267         input   MDMCMDPAR0, r0
;  mce_ram_bank.asm:    268         sr0     8, r0                                 ; [15:8] => Sync Word Length
;  mce_ram_bank.asm:    269         bclr    7, r0
;  mce_ram_bank.asm:    270         mov     r0, r1                                ; R1 = SyncWordLength
;  mce_ram_bank.asm:    271         add     1, r1                                 ; In [32..1] format
;  mce_ram_bank.asm:    272         ;; We are now going to process the SyncWord, and prepare it for later
;  mce_ram_bank.asm:    273         ;; In general this is where we are putting things:
;  mce_ram_bank.asm:    274         ;; R2 = MDMSYNC0, R3 = 15, R4 = MDMSYNC1, R5 = 15
;  mce_ram_bank.asm:    275         ;; This would apply to a full 32-bit sync word. If the syncword is
;  mce_ram_bank.asm:    276         ;; between 32 to 17 bits, we would transmit both. If is 16 or less
;  mce_ram_bank.asm:    277         ;; only the second one (R4) would be transmitted.
;  mce_ram_bank.asm:    278         ;; Also, those syncwords come left-aligned. We need to bit-shift to be
;  mce_ram_bank.asm:    279         ;; right aligned.
;  mce_ram_bank.asm:    280         ;; Step 0. General Case (32-bit case)
;  mce_ram_bank.asm:    281         input   MDMSYNC0, r2
;  mce_ram_bank.asm:    282         input   MDMSYNC1, r4
;  mce_ram_bank.asm:    283         lli     15, r3
;  mce_ram_bank.asm:    284         lli     15, r5
;  mce_ram_bank.asm:    285         ;; Step 1. Check if SyncWord is 32 bits
;  mce_ram_bank.asm:    286         lli     32, r0
;  mce_ram_bank.asm:    287         cmp     r0, r1                                ; Special case, 32 bits 
;  mce_ram_bank.asm:    288         beq     MTX_Iqdump_Common_Preamble_RFESEND    ; if yes, we are done
;  mce_ram_bank.asm:    289         ;; Step 2. Check if in [31..17] bits range
;  mce_ram_bank.asm:    290         lli     16, r0
;  mce_ram_bank.asm:    291         cmp     r1, r0              
;  mce_ram_bank.asm:    292         beq     MTX_Iqdump_Common_Preamble_16bitSyncWord
;  mce_ram_bank.asm:    293         bpl     MTX_Iqdump_Common_Preamble_ShortSyncWord
;  mce_ram_bank.asm:    294   ;; R2 = MDMSYNC0-right-aligned, R3 = num of bits, R4 = MDMSYNC1, R5 = 15
;  mce_ram_bank.asm:    295 MTX_Iqdump_Common_Preamble_LongSyncWord:
;  mce_ram_bank.asm:    296         mov     r1, r3                                ; R3 = [32..17]
;  mce_ram_bank.asm:    297         sub  r0, r3                          ; R3 = R3-16 
;  mce_ram_bank.asm:    298         sub     r3, r0                                ; R0 = 16-R3
;  mce_ram_bank.asm:    299         sub     1, r3                                 ; R3 = # bits to send
;  mce_ram_bank.asm:    300         sub     1, r0                                 ; R0 = # bits to shift down
;  mce_ram_bank.asm:    301 MTX_Iqdump_Common_Preamble_SyncWord_ShiftLoop1:
;  mce_ram_bank.asm:    302         sr0  1, r2                                 ; MDMSYNC0-right-aligned
;  mce_ram_bank.asm:    303         loop  MTX_Iqdump_Common_Preamble_SyncWord_ShiftLoop1
;  mce_ram_bank.asm:    304         jmp MTX_Iqdump_Common_Preamble_RFESEND
;  mce_ram_bank.asm:    305         ;; Step 3. Must be in [16..1] bits range
;  mce_ram_bank.asm:    306 MTX_Iqdump_Common_Preamble_16bitSyncWord:
;  mce_ram_bank.asm:    307         mov  0x1F, r3                              ; Illegal value to indicate 16 bit or shorter sw
;  mce_ram_bank.asm:    308         jmp     MTX_Iqdump_Common_Preamble_RFESEND
;  mce_ram_bank.asm:    309 MTX_Iqdump_Common_Preamble_ShortSyncWord:       
;  mce_ram_bank.asm:    310   ;; Results, R2 = XXX, R3 = 0, R4 = MDMSYNC1, R5 = num of bits
;  mce_ram_bank.asm:    311         mov  0x1F, r3                              ; Illegal value to indicate 16 bit or shorter sw
;  mce_ram_bank.asm:    312         mov     r1, r5                                ; R5 = [16..1]
;  mce_ram_bank.asm:    313         lli     16, r0                                ; R0 = 16
;  mce_ram_bank.asm:    314         sub     r5, r0                                ; R0 = 16-R5
;  mce_ram_bank.asm:    315         sub     1, r5                                 ; R5 = # bits to send
;  mce_ram_bank.asm:    316         sub  1, r0                                ; R0 = # bits to shift down
;  mce_ram_bank.asm:    317 MTX_Iqdump_Common_Preamble_SyncWord_ShiftLoop2:
;  mce_ram_bank.asm:    318         sr0  1, r4                                 ; MDMSYNC0-right-aligned
;  mce_ram_bank.asm:    319         loop  MTX_Iqdump_Common_Preamble_SyncWord_ShiftLoop2
;  mce_ram_bank.asm:    320   ;; and done with SyncWordProcessing
;  mce_ram_bank.asm:    321 MTX_Iqdump_Common_Preamble_RFESEND:     
;  mce_ram_bank.asm:    322         ;; ============================================
;  mce_ram_bank.asm:    323         ;; Wait for RAT event
;  mce_ram_bank.asm:    324         outbset MCEEVENT1_RAT_EVENT0, MCEEVENTMSK1    ; enable wait for RAT
;  mce_ram_bank.asm:    325         wait                                       
;  mce_ram_bank.asm:    326         outbset MCEEVENT1_RAT_EVENT0, MCEEVENTCLR1    ; Clear event again
;  mce_ram_bank.asm:    327         outbclr MCEEVENT1_RAT_EVENT0, MCEEVENTMSK1    ; disable wait for RAT
;  mce_ram_bank.asm:    328         ;; Send message to RFE that modulation is starting
;  mce_ram_bank.asm:    329         outbset  0,RFESEND
;  mce_ram_bank.asm:    330 
;  mce_ram_bank.asm:    331   ;; Set up timer for tone in front of preamble
;  mce_ram_bank.asm:    332         outbset TIMCTRL_ENABLETIMER, TIMCTRL                      ; 
;  mce_ram_bank.asm:    333         input   BRMACC0, r0                          ; Tone count
;  mce_ram_bank.asm:    334         output  r0, TIMPERIOD   ; 
;  mce_ram_bank.asm:    335         outbset MCEEVENT0_TIMER_IRQ, MCEEVENTCLR0          ; Clear IRQ
;  mce_ram_bank.asm:    336         ;; A delay to precisely time the start of the Preamble
;  mce_ram_bank.asm:    337         outbset MCEEVENT0_TIMER_IRQ, MCEEVENTMSK0          ; Enable the mask!
;  mce_ram_bank.asm:    338         wait
;  mce_ram_bank.asm:    339 
;  mce_ram_bank.asm:    340         ;; Enable modulator and timebase now
;  mce_ram_bank.asm:    341         outbset MDMENABLE_TIMEBASE, MDMENABLE
;  mce_ram_bank.asm:    342         outbset MDMINIT_TIMEBASE, MDMINIT
;  mce_ram_bank.asm:    343 
;  mce_ram_bank.asm:    344         outbset MCEEVENT0_TIMER_IRQ, MCEEVENTCLR0          ; Clear IRQ
;  mce_ram_bank.asm:    345         outbclr MCEEVENT0_TIMER_IRQ, MCEEVENTMSK0          ; Disable Mask
;  mce_ram_bank.asm:    346         outclr  TIMCTRL                                    ; Switch off timer
;  mce_ram_bank.asm:    347 
;  mce_ram_bank.asm:    348         ;; Step 2. Go to Preamble insert, Send MDMSYNC0, MDMSYNC1
;  mce_ram_bank.asm:    349         outbset MODCTRL_PREAMBLEINSERT, MODCTRL       ; Go to preamble insert mode
;  mce_ram_bank.asm:    350         outbset MDMENABLE_MODULATOR, MDMENABLE
;  mce_ram_bank.asm:    351         outbset MDMINIT_MODULATOR, MDMINIT
;  mce_ram_bank.asm:    352         ;; Preamble insert mode from start
;  mce_ram_bank.asm:    353 MTX_Iqdump_FirstBit:
;  mce_ram_bank.asm:    354         outclr  MODPRECTRL                            ; Send ONE bit        
;  mce_ram_bank.asm:    355         outbset MCEEVENT1_PREAMBLE_DONE, MCEEVENTMSK1 ; wait for preamble done
;  mce_ram_bank.asm:    356         wait
;  mce_ram_bank.asm:    357         outbset MCEEVENT1_PREAMBLE_DONE, MCEEVENTCLR1 ; Clear Preamble Done
;  mce_ram_bank.asm:    358         ;; Reload MOCPRECTRL with proper value now
;  mce_ram_bank.asm:    359         input   MDMCMDPAR0, r0
;  mce_ram_bank.asm:    360         output  r0, MODPRECTRL                        ; Send directly to MODPRECTRL again
;  mce_ram_bank.asm:    361 MTX_Iqdump_Common_Preamble_Loop:        
;  mce_ram_bank.asm:    362         wait
;  mce_ram_bank.asm:    363         outbset MCEEVENT1_PREAMBLE_DONE, MCEEVENTCLR1 ; Clear Preamble Done
;  mce_ram_bank.asm:    364         ;; Infinite preamble? Indicated by MSB of MDMCMDPAR0
;  mce_ram_bank.asm:    365         input   MDMCMDPAR0, r0
;  mce_ram_bank.asm:    366         btst    15, r0
;  mce_ram_bank.asm:    367         bne     MTX_Iqdump_Common_Preamble_Loop
;  mce_ram_bank.asm:    368         ;; Preamble is done now, start with SyncWord. Use the R2, R3, R4, R5 values from above
;  mce_ram_bank.asm:    369         mov     0x1F, r0        ; 
;  mce_ram_bank.asm:    370         cmp  r0, r3          ;  check if less than 16 bit SW
;  mce_ram_bank.asm:    371         beq  MTX_Iqdump_Common_Preamble_Send_One_SW
;  mce_ram_bank.asm:    372 MTX_Iqdump_Common_Preamble_Send_Two_SW:
;  mce_ram_bank.asm:    373         output  r3, MODPRECTRL
;  mce_ram_bank.asm:    374         output  r2, MODPREAMBLE
;  mce_ram_bank.asm:    375         wait
;  mce_ram_bank.asm:    376         outbset MCEEVENT1_PREAMBLE_DONE, MCEEVENTCLR1 ; Clear Preamble Done
;  mce_ram_bank.asm:    377 MTX_Iqdump_Common_Preamble_Send_One_SW:
;  mce_ram_bank.asm:    378         output  r5, MODPRECTRL
;  mce_ram_bank.asm:    379         output  r4, MODPREAMBLE
;  mce_ram_bank.asm:    380         wait
;  mce_ram_bank.asm:    381         outbset MCEEVENT1_PREAMBLE_DONE, MCEEVENTCLR1 ; Clear Preamble Done
;  mce_ram_bank.asm:    382         outbset MCEEVENT1_PREAMBLE_DONE, MCEEVENTMSK1 ; Disable PREAMBLE_DONE from now on
;  mce_ram_bank.asm:    383         outbclr MODCTRL_PREAMBLEINSERT, MODCTRL       ; No more preamble insert
;  mce_ram_bank.asm:    384         rts
;  mce_ram_bank.asm:    385 
;  mce_ram_bank.asm:    386 ;;; --------------------------------------------------------------------------
;  mce_ram_bank.asm:    387 ;;; MTX GenericFSK Termination
;  mce_ram_bank.asm:    388 ;;; 
;  mce_ram_bank.asm:    389 MTX_Iqdump_Termination:
;  mce_ram_bank.asm:    390         ;; Termination, Step 2. wait 4 clock baud periods before switching off
;  mce_ram_bank.asm:    391         outbclr MCEEVENT1_CLKEN_BAUD, MCEEVENTMSK1   ; Disable CLKEN_BAUD events
;  mce_ram_bank.asm:    392         lli     0x03,r0                              ; Wait for 4 baud periods before switching
;  mce_ram_bank.asm:    393         output  r0, TIMCTRL                          ; the modulator off
;  mce_ram_bank.asm:    394         lli     0x04, r0                             ; Four periods
;  mce_ram_bank.asm:    395         output  r0, TIMPERIOD
;  mce_ram_bank.asm:    396         outbset MCEEVENT0_TIMER_IRQ, MCEEVENTCLR0    ; Clear IRQ
;  mce_ram_bank.asm:    397         outbset MCEEVENT0_TIMER_IRQ, MCEEVENTMSK0    ; Enable the mask!
;  mce_ram_bank.asm:    398         wait
;  mce_ram_bank.asm:    399         outbset MCEEVENT0_TIMER_IRQ, MCEEVENTCLR0    ; Clear IRQ
;  mce_ram_bank.asm:    400         outbclr MCEEVENT0_TIMER_IRQ, MCEEVENTMSK0    ; Disable Mask
;  mce_ram_bank.asm:    401         outclr  TIMCTRL                              ; Switch off counter
;  mce_ram_bank.asm:    402         outbclr MDMENABLE_MODULATOR, MDMENABLE       ; Disable modulator, timebase
;  mce_ram_bank.asm:    403         outbclr MDMENABLE_TIMEBASE, MDMENABLE
;  mce_ram_bank.asm:    404         ;; Send message to RFE that modulation is stopping
;  mce_ram_bank.asm:    405         outbclr 0, RFESEND      ;
;  mce_ram_bank.asm:    406         rts
;  mce_ram_bank.asm:    407         
;  mce_ram_bank.asm:    408 ;;; --------------------------------------------------------------------------
;  mce_ram_bank.asm:    409 ;;; No FEC, directly read data from FIFO and send out. TOPsm is mostly free 
;  mce_ram_bank.asm:    410 ;;;           
;  mce_ram_bank.asm:    411 MTX_Entry:
;  mce_ram_bank.asm:    412         outset  MCEEVENTCLR0    
;  mce_ram_bank.asm:    413         outset  MCEEVENTCLR1
;  mce_ram_bank.asm:    414 
;  mce_ram_bank.asm:    415         ;; Normal mode (1bit per symbol) proceeds here
;  mce_ram_bank.asm:    416         DBG_PRINT0 "IQDump::: NoFEC, TX Started"
;  mce_ram_bank.asm:    417         lli     0x10, r0                                   ; MDMFIFORDCTRL, 1 bits reads, from modem
;  mce_ram_bank.asm:    418         output  r0, MDMFIFORDCTRL
;  mce_ram_bank.asm:    419         jsr     MTX_Iqdump_Common_Preamble                 ; Send Preamble
;  mce_ram_bank.asm:    420 
;  mce_ram_bank.asm:    421         outbset MODCTRL_FECENABLE, MODCTRL                 ; And enable the noFEC-"FEC"
;  mce_ram_bank.asm:    422         outbset MCEEVENT0_FIFO_ERR_UNDERFLOW, MCEEVENTCLR0 ; clear any previous
;  mce_ram_bank.asm:    423         outbset MCEEVENT0_FIFO_ERR_UNDERFLOW, MCEEVENTMSK0 ; allow FIFO UNDERFLOW errors
;  mce_ram_bank.asm:    424         wait                                               ; WAITS for FIFO underflow here
;  mce_ram_bank.asm:    425         outbclr MCEEVENT0_FIFO_ERR_UNDERFLOW, MCEEVENTMSK0 ; Remove FIFO UNDERFLOW events
;  mce_ram_bank.asm:    426         jsr     MTX_Iqdump_Termination
;  mce_ram_bank.asm:    427         jmp     CMD_OK_END
;  mce_ram_bank.asm:    428 
;  mce_ram_bank.asm:    429 ;;; --------------------------------------------------------------------------
;  mce_ram_bank.asm:    430 ;;; Multi-level FSK modulation, directly feed 4-bits into SOFT TX register, at baud rate 
;  mce_ram_bank.asm:    431 ;;;           
;  mce_ram_bank.asm:    432 MTX_MFSK:
;  mce_ram_bank.asm:    433 	outset  MCEEVENTCLR0    
;  mce_ram_bank.asm:    434         outset  MCEEVENTCLR1
;  mce_ram_bank.asm:    435 	
;  mce_ram_bank.asm:    436         DBG_PRINT0 "IQDump::: Multi-level FSK TX Mode"
;  mce_ram_bank.asm:    437         lli     0x03, r0                  ; 4 bit reads, from register
;  mce_ram_bank.asm:    438         output  r0, MDMFIFORDCTRL
;  mce_ram_bank.asm:    439 	;; Set modctrl to read from modsofftx:
;  mce_ram_bank.asm:    440 	outbset	MODCTRL_SOFTTXENABLE, MODCTRL
;  mce_ram_bank.asm:    441         ;; ============================================
;  mce_ram_bank.asm:    442         ;; Wait for RAT event
;  mce_ram_bank.asm:    443         outbset MCEEVENT1_RAT_EVENT0, MCEEVENTMSK1    ; enable wait for RAT
;  mce_ram_bank.asm:    444         wait                                       
;  mce_ram_bank.asm:    445         outbset MCEEVENT1_RAT_EVENT0, MCEEVENTCLR1    ; Clear event again
;  mce_ram_bank.asm:    446         outbclr MCEEVENT1_RAT_EVENT0, MCEEVENTMSK1    ; disable wait for RAT
;  mce_ram_bank.asm:    447         ;; Send message to RFE that modulation is starting
;  mce_ram_bank.asm:    448         outbset  0,RFESEND
;  mce_ram_bank.asm:    449         ;; Enable modulator and timebase now
;  mce_ram_bank.asm:    450         outbset MDMENABLE_TIMEBASE, MDMENABLE
;  mce_ram_bank.asm:    451         outbset MDMINIT_TIMEBASE, MDMINIT
;  mce_ram_bank.asm:    452 	outbset MDMENABLE_MODULATOR, MDMENABLE
;  mce_ram_bank.asm:    453         outbset MDMINIT_MODULATOR, MDMINIT
;  mce_ram_bank.asm:    454 	
;  mce_ram_bank.asm:    455         ;; This mode uses no preamble or SW, just direct symbols from the FIFO. 
;  mce_ram_bank.asm:    456         ;; It starts by waiting if no symbols are present
;  mce_ram_bank.asm:    457         mov     0, r0                          ; Start by sending symbol 0
;  mce_ram_bank.asm:    458         output  r0, MODSOFTTX                  ; ready to go
;  mce_ram_bank.asm:    459         outbset MCEEVENT1_CLKEN_BAUD, MCEEVENTCLR1 ; Clear CLKEN Baud 
;  mce_ram_bank.asm:    460         outbset MCEEVENT1_CLKEN_BAUD, MCEEVENTMSK1 ; will iterate on CLKEN baud ticks 
;  mce_ram_bank.asm:    461 MTX_MFSK_ToneLoop:
;  mce_ram_bank.asm:    462         wait
;  mce_ram_bank.asm:    463         outbset MCEEVENT1_CLKEN_BAUD, MCEEVENTCLR1 ; Clear CLKEN Baud 
;  mce_ram_bank.asm:    464         input   MDMFIFOSTA, r0
;  mce_ram_bank.asm:    465         and     2, r0                              ; Check with bit 1 (data present)
;  mce_ram_bank.asm:    466         cmp     2, r0
;  mce_ram_bank.asm:    467         bne     MTX_MFSK_ToneLoop
;  mce_ram_bank.asm:    468         ;; At this point, we can actually read data from the FIFO, 4 bits at a time
;  mce_ram_bank.asm:    469         DBG_PRINT0 "Starting MFSK Symbol Loop"
;  mce_ram_bank.asm:    470 MTX_MFSK_SymbolLoop:
;  mce_ram_bank.asm:    471         wait
;  mce_ram_bank.asm:    472         outbset MCEEVENT1_CLKEN_BAUD, MCEEVENTCLR1 ; Clear CLKEN Baud 
;  mce_ram_bank.asm:    473         input   MDMFIFORD, r1                      ; get new nibble
;  mce_ram_bank.asm:    474         output  r1, MODSOFTTX                      ; send to MODISF
;  mce_ram_bank.asm:    475         nop
;  mce_ram_bank.asm:    476         nop
;  mce_ram_bank.asm:    477         nop
;  mce_ram_bank.asm:    478         input   MDMFIFOSTA, r2
;  mce_ram_bank.asm:    479         and     2, r2                              ; check with bit 1 (data present)
;  mce_ram_bank.asm:    480 	;; DEBUG:
;  mce_ram_bank.asm:    481 	;sl0	8, r1				   ; Make signed
;  mce_ram_bank.asm:    482 	;sl0	4, r1
;  mce_ram_bank.asm:    483 	;srx	8, r1				   ; make signed
;  mce_ram_bank.asm:    484 	;srx	4, r1
;  mce_ram_bank.asm:    485 	;DBG_PRINT1 "Payload: %d", r1
;  mce_ram_bank.asm:    486 	;; END OF DEBUG
;  mce_ram_bank.asm:    487         cmp     2, r2
;  mce_ram_bank.asm:    488         beq     MTX_MFSK_SymbolLoop
;  mce_ram_bank.asm:    489         ;; 
;  mce_ram_bank.asm:    490         ;; FIFO is now empty, so terminate 
;  mce_ram_bank.asm:    491         DBG_PRINT0 "Stopping MFSK Symbol Loop"
;  mce_ram_bank.asm:    492 	outbclr	MODCTRL_SOFTTXENABLE, MODCTRL
;  mce_ram_bank.asm:    493         jsr     MTX_Iqdump_Termination
;  mce_ram_bank.asm:    494         jmp     CMD_OK_END
;  mce_ram_bank.asm:    495 
;  mce_ram_bank.asm:    496 ;;; --------------------------------------------------------------------------
;  mce_ram_bank.asm:    497 ;;; MRX IQdump REGISTER Blind MODE, update the following registers DEMFRAC4/DEMFRAC5/DEMPDIF0
;  mce_ram_bank.asm:    498 ;;;  Infinite, must be end by abort command
;  mce_ram_bank.asm:    499 ;;; 
;  mce_ram_bank.asm:    500 MRX_Entry_REG_BLIND:
;  mce_ram_bank.asm:    501   ;;; Just to be sure those interrupts are disabled, there is no normal termination. 
;  mce_ram_bank.asm:    502         outbclr MCEEVENT0_CLKEN_4BAUD, MCEEVENTMSK0     ; disable the clkenbaud_4f event        
;  mce_ram_bank.asm:    503         outbclr MCEEVENT2_C1BE_A_POS_PEAK, MCEEVENTMSK2 ; disable correlation event
;  mce_ram_bank.asm:    504         outbclr MCEEVENT2_C1BE_B_POS_PEAK, MCEEVENTMSK2 ; disable correlation event
;  mce_ram_bank.asm:    505         outset  MCEEVENTCLR0    
;  mce_ram_bank.asm:    506         outset  MCEEVENTCLR1        
;  mce_ram_bank.asm:    507         jsr  MRX_SETUP
;  mce_ram_bank.asm:    508     
;  mce_ram_bank.asm:    509         DBG_PRINT0 "########################### Blind REGISTER MODE -> IQ Dump starting at once  ########################"
;  mce_ram_bank.asm:    510         outbset MCEEVENT0_CLKEN_4BAUD, MCEEVENTMSK0  ; enable the clkenbaud_4f event        
;  mce_ram_bank.asm:    511         lli     3, r5                                ; to trigger capture of I and Q
;  mce_ram_bank.asm:    512 
;  mce_ram_bank.asm:    513 LOOP_SAMPLES_BLIND:           
;  mce_ram_bank.asm:    514         wait
;  mce_ram_bank.asm:    515         output  r5, RDCAPT1                             ; capture I + Q from FRAC
;  mce_ram_bank.asm:    516         outbset RDCAPT0_DEMPDIF0, RDCAPT0               ; capture instantaneous frequency
;  mce_ram_bank.asm:    517         outbset MCESTROBES0_EVENT0, MCESTROBES0         ; signal 4BAUD  
;  mce_ram_bank.asm:    518         outbset MCEEVENT0_CLKEN_4BAUD, MCEEVENTCLR0     ; clear the clkenbaud_4f event
;  mce_ram_bank.asm:    519 
;  mce_ram_bank.asm:    520         jmp     LOOP_SAMPLES_BLIND                            ; 
;  mce_ram_bank.asm:    521   
;  mce_ram_bank.asm:    522 ;;; --------------------------------------------------------------------------
;  mce_ram_bank.asm:    523 ;;; MRX IQdump blind FIFO MODE started where IQ samples are moved into RFC FIFO
;  mce_ram_bank.asm:    524 ;;;   - Packet size can be programmed by the API
;  mce_ram_bank.asm:    525 ;;; 
;  mce_ram_bank.asm:    526 MRX_Entry_FIFO_BLIND:
;  mce_ram_bank.asm:    527   ;;; Just to be sure those interrupts are disabled, there is no normal termination. 
;  mce_ram_bank.asm:    528         outbclr MCEEVENT0_CLKEN_4BAUD, MCEEVENTMSK0     ; disable the clkenbaud_4f event        
;  mce_ram_bank.asm:    529         outbclr MCEEVENT2_C1BE_A_POS_PEAK, MCEEVENTMSK2 ; disable correlation event
;  mce_ram_bank.asm:    530         outbclr MCEEVENT2_C1BE_B_POS_PEAK, MCEEVENTMSK2 ; disable correlation event
;  mce_ram_bank.asm:    531         outset  MCEEVENTCLR0    
;  mce_ram_bank.asm:    532         outset  MCEEVENTCLR1        
;  mce_ram_bank.asm:    533         jsr  MRX_SETUP
;  mce_ram_bank.asm:    534         
;  mce_ram_bank.asm:    535         lli  24, r11          ; Set Word Counter 
;  mce_ram_bank.asm:    536         lli     0x0, r0          ; MDMFIFOWRCTRL, 1 bits write, from modem
;  mce_ram_bank.asm:    537         output  r0, MDMFIFOWRCTRL
;  mce_ram_bank.asm:    538         mov  0, r12          ; Clear bit counter
;  mce_ram_bank.asm:    539         mov  1, r8          ; preload register for known pattern generation 
;  mce_ram_bank.asm:    540         lmd  IQDUMP_TEST_MAX_VAL, r10    ; Test pattern wrap value 
;  mce_ram_bank.asm:    541         lmd  IQDUMP_MAX_POS_VAL, r13      ; Positive Saturation value for 12 bit resolution 
;  mce_ram_bank.asm:    542         lmd  IQDUMP_MIN_NEG_VAL, r14      ; Negative Saturation value for 12 bit resolution
;  mce_ram_bank.asm:    543         mov  r10, r9          ; preload register for known pattern generation
;  mce_ram_bank.asm:    544   
;  mce_ram_bank.asm:    545         outbset MCESTROBES0_EVENT0, MCESTROBES0         ; signal Sync Found immediately
;  mce_ram_bank.asm:    546         outbset MCEEVENT0_CLKEN_4BAUD, MCEEVENTMSK0     ; enable the clkenbaud_4 event        
;  mce_ram_bank.asm:    547 
;  mce_ram_bank.asm:    548 ;;; Add delay between sync found is signalled and first RFC FIFO write.
;  mce_ram_bank.asm:    549 ;;; Wait loop for cm0 to be ready to do full speed readout from RFC FIFO (otherwise longer delay than 8.4us has been observed!)
;  mce_ram_bank.asm:    550         lli  5, r0
;  mce_ram_bank.asm:    551 LOOP_SAMPLES_FIFO_BLIND_WAIT:
;  mce_ram_bank.asm:    552         outbset MCEEVENT0_CLKEN_4BAUD, MCEEVENTCLR0     ; clear the clkenbaud_4 event
;  mce_ram_bank.asm:    553         wait
;  mce_ram_bank.asm:    554         loop  LOOP_SAMPLES_FIFO_BLIND_WAIT
;  mce_ram_bank.asm:    555   
;  mce_ram_bank.asm:    556          
;  mce_ram_bank.asm:    557         DBG_PRINT0 "########################### Blind RFC FIFO Mode -> IQ Dump starting at once  (DataRate <= 12,5 kbps) ########################"
;  mce_ram_bank.asm:    558         lli     3, r5                                ; to trigger capture of I and Q
;  mce_ram_bank.asm:    559 
;  mce_ram_bank.asm:    560 LOOP_SAMPLES_FIFO_BLIND:
;  mce_ram_bank.asm:    561         outbset MCEEVENT0_CLKEN_4BAUD, MCEEVENTCLR0     ; clear the clkenbaud_4 event
;  mce_ram_bank.asm:    562         wait            ; Only 4baud event wakes up TopSM 
;  mce_ram_bank.asm:    563         output  r5, RDCAPT1                             ; capture I + Q from FRAC
;  mce_ram_bank.asm:    564         input  DEMFRAC4, r0
;  mce_ram_bank.asm:    565 
;  mce_ram_bank.asm:    566         jsr  SignExt_and_Saturate      ; Saturate to 12 bit word 
;  mce_ram_bank.asm:    567   
;  mce_ram_bank.asm:    568         input  MDMSPAR2, r1        ; MDMSPAR2[0] 0-> IQ data, 1 -> Known Test pattern (counter value)
;  mce_ram_bank.asm:    569         btst  0, r1
;  mce_ram_bank.asm:    570         beq  LOOP_SAMPLES_FIFO_BLIND_DEMFRAC4WR
;  mce_ram_bank.asm:    571         mov  r8, r0          ; Known link test pattern
;  mce_ram_bank.asm:    572         cmp  r10, r8
;  mce_ram_bank.asm:    573         bne  TEST_PATTERN_ADD_BLIND
;  mce_ram_bank.asm:    574         mov  0, r8
;  mce_ram_bank.asm:    575 TEST_PATTERN_ADD_BLIND:    
;  mce_ram_bank.asm:    576         add  1, r8
;  mce_ram_bank.asm:    577 LOOP_SAMPLES_FIFO_BLIND_DEMFRAC4WR:  
;  mce_ram_bank.asm:    578         jsr  MDMFIFOWR_AND_WAIT10
;  mce_ram_bank.asm:    579   
;  mce_ram_bank.asm:    580 
;  mce_ram_bank.asm:    581         input  DEMFRAC5, r0
;  mce_ram_bank.asm:    582         jsr  SignExt_and_Saturate      ; Saturate to 12 bit word
;  mce_ram_bank.asm:    583         input  MDMSPAR2, r1        ; MDMSPAR2[0] 0-> IQ data, 1 -> Known Test pattern (counter value)
;  mce_ram_bank.asm:    584         btst  0, r1
;  mce_ram_bank.asm:    585         beq  LOOP_SAMPLES_FIFO_BLIND_DEMFRAC5WR
;  mce_ram_bank.asm:    586         mov  r9, r0          ; Known link test pattern
;  mce_ram_bank.asm:    587         sub  1, r9
;  mce_ram_bank.asm:    588         cmp  0, r9
;  mce_ram_bank.asm:    589         bne  LOOP_SAMPLES_FIFO_BLIND_DEMFRAC5WR
;  mce_ram_bank.asm:    590         mov  r10, r9
;  mce_ram_bank.asm:    591 LOOP_SAMPLES_FIFO_BLIND_DEMFRAC5WR:  
;  mce_ram_bank.asm:    592         jsr  MDMFIFOWR_AND_WAIT10
;  mce_ram_bank.asm:    593   
;  mce_ram_bank.asm:    594         input   MDMCMDPAR1, r4                          ; check if length has been given
;  mce_ram_bank.asm:    595         cmp     0, r4                                   ; if length is zero, infinite length is assumed
;  mce_ram_bank.asm:    596         beq     LOOP_SAMPLES_FIFO_BLIND
;  mce_ram_bank.asm:    597         add     r11, r12                                ; increment bit counter
;  mce_ram_bank.asm:    598         cmp     r4, r12                                 ; End if rxbits - pktLen >= 0
;  mce_ram_bank.asm:    599         bpl     MRX_GenFSK_CommonEnd                    ; if so jump to end
;  mce_ram_bank.asm:    600         jmp     LOOP_SAMPLES_FIFO_BLIND                 ; 
;  mce_ram_bank.asm:    601 
;  mce_ram_bank.asm:    602   
;  mce_ram_bank.asm:    603 ;;; --------------------------------------------------------------------------
;  mce_ram_bank.asm:    604 ;;; MRX Transparent FIFO MODE started where pdiff hard decisions are moved into FIFO
;  mce_ram_bank.asm:    605 ;;;   - Packet size and stop AGC can be programmed by the API
;  mce_ram_bank.asm:    606 ;;; 
;  mce_ram_bank.asm:    607 MRX_Entry_TRANSPARENT_FIFO:
;  mce_ram_bank.asm:    608   ;;; Just to be sure those interrupts are disabled, there is no normal termination. 
;  mce_ram_bank.asm:    609         outbclr MCEEVENT0_CLKEN_4BAUD, MCEEVENTMSK0     ; disable the clkenbaud_4f event        
;  mce_ram_bank.asm:    610         outbclr MCEEVENT2_C1BE_A_POS_PEAK, MCEEVENTMSK2 ; disable correlation event
;  mce_ram_bank.asm:    611         outbclr MCEEVENT2_C1BE_B_POS_PEAK, MCEEVENTMSK2 ; disable correlation event
;  mce_ram_bank.asm:    612         outset  MCEEVENTCLR0    
;  mce_ram_bank.asm:    613         outset  MCEEVENTCLR1        
;  mce_ram_bank.asm:    614         jsr  MRX_SETUP
;  mce_ram_bank.asm:    615         
;  mce_ram_bank.asm:    616         outclr  MDMFIFOWRCTRL        ; MDMFIFOWRCTRL, 1 bits write, from modem
;  mce_ram_bank.asm:    617         mov  0, r12          ; Clear bit counter
;  mce_ram_bank.asm:    618         mov  0, r5          ; Data filtered soft samples 
;  mce_ram_bank.asm:    619   
;  mce_ram_bank.asm:    620         outbset MCESTROBES0_EVENT0, MCESTROBES0         ; signal Sync Found immediately
;  mce_ram_bank.asm:    621         outbset MCEEVENT0_CLKEN_4BAUD, MCEEVENTMSK0     ; enable the clkenbaud_4 event        
;  mce_ram_bank.asm:    622 
;  mce_ram_bank.asm:    623 ;;; Add delay between sync found is signalled and first RFC FIFO write.
;  mce_ram_bank.asm:    624 ;;; Wait loop for cm0 to be ready to do full speed readout from RFC FIFO (otherwise longer delay than 8.4us has been observed!)
;  mce_ram_bank.asm:    625         lli  5, r0
;  mce_ram_bank.asm:    626 LOOP_SAMPLES_TRANSPARENT_FIFO_WAIT:
;  mce_ram_bank.asm:    627         outbset MCEEVENT0_CLKEN_4BAUD, MCEEVENTCLR0     ; clear the clkenbaud_4 event
;  mce_ram_bank.asm:    628         wait
;  mce_ram_bank.asm:    629         loop  LOOP_SAMPLES_TRANSPARENT_FIFO_WAIT
;  mce_ram_bank.asm:    630   
;  mce_ram_bank.asm:    631         DBG_PRINT0 "########################### Transparent FIFO Mode -> PDIFF streaming starting at once  ########################"
;  mce_ram_bank.asm:    632   
;  mce_ram_bank.asm:    633         lmd  TRANSPARENT_CAPT, r13      ; Combined RDCAPT0_DEMPDIF0 and RDCAPT0_DEMFIFE2
;  mce_ram_bank.asm:    634         input   VITACCCTRL, r14        ; Capture for later use, time optimization
;  mce_ram_bank.asm:    635 
;  mce_ram_bank.asm:    636 LOOP_SAMPLES_TRANSPARENT_FIFO:
;  mce_ram_bank.asm:    637         outbset MCEEVENT0_CLKEN_4BAUD, MCEEVENTCLR0     ; clear the clkenbaud_4 event
;  mce_ram_bank.asm:    638         wait            ; Only 4baud event wakes up TopSM 
;  mce_ram_bank.asm:    639         input  MDMSPAR1, r0
;  mce_ram_bank.asm:    640         btst  0, r0
;  mce_ram_bank.asm:    641         beq  CAPT_FREQUENCY
;  mce_ram_bank.asm:    642         input  RFESEND, r0
;  mce_ram_bank.asm:    643         btst  1, r0
;  mce_ram_bank.asm:    644         bne  CAPT_FREQUENCY  
;  mce_ram_bank.asm:    645         outbset 1, RFESEND                              ; Notify by bit 1 in RFESEND (i.e. Stop AGC)
;  mce_ram_bank.asm:    646         DBG_PRINT0 "########################### Transparent FIFO Mode Stop AGC  ########################"
;  mce_ram_bank.asm:    647 
;  mce_ram_bank.asm:    648   
;  mce_ram_bank.asm:    649 CAPT_FREQUENCY:  
;  mce_ram_bank.asm:    650         output  r13, RDCAPT0        ; capture instantaneous frequency and fife
;  mce_ram_bank.asm:    651         input  DEMPDIF0, r2
;  mce_ram_bank.asm:    652         sl0  8, r2          ; Sign Extend
;  mce_ram_bank.asm:    653         srx  8, r2
;  mce_ram_bank.asm:    654         input  DEMFIFE2,r0
;  mce_ram_bank.asm:    655         sl0     8, r0          ; Sign Extend
;  mce_ram_bank.asm:    656         srx     8, r0          ;
;  mce_ram_bank.asm:    657         ;mov  r0, r9          ; For debug only 
;  mce_ram_bank.asm:    658         sub  r0, r2          ; Subtract Frequency offset 
;  mce_ram_bank.asm:    659   
;  mce_ram_bank.asm:    660         and     3, r14          ; extract lower two bits
;  mce_ram_bank.asm:    661         cmp     0, r14          ;
;  mce_ram_bank.asm:    662         beq     NO_IIR_FILTER        ;
;  mce_ram_bank.asm:    663         cmp     2, r14          ;
;  mce_ram_bank.asm:    664         beq     IIR_K4          ;
;  mce_ram_bank.asm:    665         cmp     3, r14          ;
;  mce_ram_bank.asm:    666         beq     IIR_K8          ;                
;  mce_ram_bank.asm:    667 IIR_K2:         
;  mce_ram_bank.asm:    668         ;; make a simple IIR   y[n] = y[n-1]/2 + x[n]/2
;  mce_ram_bank.asm:    669         ;; r5 = y
;  mce_ram_bank.asm:    670         ;; first calculate y[n-1]*2
;  mce_ram_bank.asm:    671         mov  r5, r6            ; y[n-1] into r6
;  mce_ram_bank.asm:    672         add  r2, r6            ; add new sample
;  mce_ram_bank.asm:    673         srx  1, r6             ; scale back to normal again                
;  mce_ram_bank.asm:    674         mov  r6, r5            ; copy to r5
;  mce_ram_bank.asm:    675         jmp  HARD_DECISION        ;
;  mce_ram_bank.asm:    676 IIR_K4:         
;  mce_ram_bank.asm:    677         ;; make a simple IIR   y[n] = y[n-1]3/4 + x[n]/4
;  mce_ram_bank.asm:    678         ;; r5 = y
;  mce_ram_bank.asm:    679         ;; first calculate y[n-1]*3/4
;  mce_ram_bank.asm:    680         mov  r5, r6            ; y[n-1] into r6
;  mce_ram_bank.asm:    681         sl0  2, r6             ; multiply by 4
;  mce_ram_bank.asm:    682         sub  r5,r6             ; sub x1 to get multiply by 3
;  mce_ram_bank.asm:    683         add  r2, r6            ; add new sample
;  mce_ram_bank.asm:    684         srx  2, r6             ; scale back to normal again                
;  mce_ram_bank.asm:    685         mov  r6, r5            ; copy to r5
;  mce_ram_bank.asm:    686         jmp  HARD_DECISION        ;        
;  mce_ram_bank.asm:    687 IIR_K8:         
;  mce_ram_bank.asm:    688         ;; make a simple IIR   y[n] = y[n-1]7/8 + x[n]/8
;  mce_ram_bank.asm:    689         ;; r5 = y
;  mce_ram_bank.asm:    690         ;; first calculate y[n-1]*7/8
;  mce_ram_bank.asm:    691         mov  r5, r6            ; y[n-1] into r6
;  mce_ram_bank.asm:    692         sl0  3, r6             ; multiply by 8
;  mce_ram_bank.asm:    693         sub  r5,r6             ; sub x1 to get multiply by 7
;  mce_ram_bank.asm:    694         add  r2, r6            ; add new sample
;  mce_ram_bank.asm:    695         srx  3, r6             ; scale back to normal again                
;  mce_ram_bank.asm:    696         mov  r6, r5            ; copy to r5
;  mce_ram_bank.asm:    697         jmp  HARD_DECISION        ;                  
;  mce_ram_bank.asm:    698 NO_IIR_FILTER:          
;  mce_ram_bank.asm:    699         mov     r2, r6         ;                        
;  mce_ram_bank.asm:    700   
;  mce_ram_bank.asm:    701 HARD_DECISION:
;  mce_ram_bank.asm:    702         ;mov  r6, r8          ; For debugging only
;  mce_ram_bank.asm:    703         sr0  7, r6
;  mce_ram_bank.asm:    704         output  r6,  MDMFIFOWR        ; Send hard decision to FIFO 
;  mce_ram_bank.asm:    705 	;DBG_PRINT1 "Sample: %d", r8
;  mce_ram_bank.asm:    706 	input   MDMCMDPAR1, r4                          ; check if length has been given
;  mce_ram_bank.asm:    707         cmp     0, r4                                   ; if length is zero, infinite length is assumed
;  mce_ram_bank.asm:    708         beq     LOOP_SAMPLES_TRANSPARENT_FIFO
;  mce_ram_bank.asm:    709         add     1, r12                                ; increment bit counter
;  mce_ram_bank.asm:    710         cmp     r4, r12                                 ; End if rxbits - pktLen >= 0
;  mce_ram_bank.asm:    711         bpl     MRX_GenFSK_CommonEnd                    ; if so jump to end
;  mce_ram_bank.asm:    712         jmp     LOOP_SAMPLES_TRANSPARENT_FIFO                 ; 
;  mce_ram_bank.asm:    713 
;  mce_ram_bank.asm:    714 ;;; --------------------------------------------------------------------------
;  mce_ram_bank.asm:    715 ;;; Sub-routine wirte to FIFO and wait
;  mce_ram_bank.asm:    716 ;;;  
;  mce_ram_bank.asm:    717 ;;; 
;  mce_ram_bank.asm:    718 MDMFIFOWR_AND_WAIT10:
;  mce_ram_bank.asm:    719         mov  r0, r1
;  mce_ram_bank.asm:    720         lli  11, r0  
;  mce_ram_bank.asm:    721 LOOP_MDMFIFOWR:    
;  mce_ram_bank.asm:    722         output  r1,  MDMFIFOWR
;  mce_ram_bank.asm:    723         sr0  1,  r1
;  mce_ram_bank.asm:    724         mov  r0, r0          ; 
;  mce_ram_bank.asm:    725         mov  r0, r0          ; 
;  mce_ram_bank.asm:    726         mov  r0, r0          ; 
;  mce_ram_bank.asm:    727         loop  LOOP_MDMFIFOWR
;  mce_ram_bank.asm:    728         rts
;  mce_ram_bank.asm:    729   
;  mce_ram_bank.asm:    730   
;  mce_ram_bank.asm:    731 ;;; --------------------------------------------------------------------------
;  mce_ram_bank.asm:    732 ;;; Sub-routine doing sign extension and Saturate to 12 bits
;  mce_ram_bank.asm:    733 ;;;  
;  mce_ram_bank.asm:    734 ;;; 
;  mce_ram_bank.asm:    735 SignExt_and_Saturate:
;  mce_ram_bank.asm:    736         sl0  3, r0
;  mce_ram_bank.asm:    737         srx  3, r0          ; Sign extend to 16 bits 
;  mce_ram_bank.asm:    738         
;  mce_ram_bank.asm:    739         cmp     r13, r0          ; 
;  mce_ram_bank.asm:    740         bpl     Pos_Sat                ; if r0 is > MAX_VAL, saturate to MAX_VAL
;  mce_ram_bank.asm:    741         cmp     r14,  r0           
;  mce_ram_bank.asm:    742         bmi     Neg_Sat                ; if r0 is < MIN_VAL, saturate to MIN_VAL
;  mce_ram_bank.asm:    743         rts  
;  mce_ram_bank.asm:    744 
;  mce_ram_bank.asm:    745 Pos_Sat:
;  mce_ram_bank.asm:    746         mov  r13, r0
;  mce_ram_bank.asm:    747         rts 
;  mce_ram_bank.asm:    748     
;  mce_ram_bank.asm:    749 Neg_Sat:
;  mce_ram_bank.asm:    750         mov  r14, r0
;  mce_ram_bank.asm:    751         rts
;  mce_ram_bank.asm:    752           
;  mce_ram_bank.asm:    753 ;;; --------------------------------------------------------------------------
;  mce_ram_bank.asm:    754 ;;; MRX IQdump REGISTER Sync MODE, update the following registers DEMFRAC4/DEMFRAC5/DEMPDIF0
;  mce_ram_bank.asm:    755 ;;;  Infinite, must be end by abort command
;  mce_ram_bank.asm:    756 ;;;  IQ dump start after SFD detection
;  mce_ram_bank.asm:    757 ;;; 
;  mce_ram_bank.asm:    758 MRX_Entry_REG_SYNC:
;  mce_ram_bank.asm:    759         DBG_PRINT0 "########################### IQ Dump REGISTER MODE, RX started, Wait for Sync ########################"
;  mce_ram_bank.asm:    760   ;;; Just to be sure those interrupts are disabled, there is no normal termination. 
;  mce_ram_bank.asm:    761         outbclr MCEEVENT0_CLKEN_4BAUD, MCEEVENTMSK0     ; disable the clkenbaud_4f event        
;  mce_ram_bank.asm:    762         outbclr MCEEVENT2_C1BE_A_POS_PEAK, MCEEVENTMSK2 ; disable correlation event
;  mce_ram_bank.asm:    763         outbclr MCEEVENT2_C1BE_B_POS_PEAK, MCEEVENTMSK2 ; disable correlation event
;  mce_ram_bank.asm:    764         outset  MCEEVENTCLR0    
;  mce_ram_bank.asm:    765         outset  MCEEVENTCLR1
;  mce_ram_bank.asm:    766         jsr  MRX_SETUP
;  mce_ram_bank.asm:    767   
;  mce_ram_bank.asm:    768   ;; Enable Correlator event
;  mce_ram_bank.asm:    769         outbset MCEEVENT2_C1BE_A_POS_PEAK, MCEEVENTCLR2 ; Clear correlator event 
;  mce_ram_bank.asm:    770         outbset MCEEVENT2_C1BE_A_POS_PEAK, MCEEVENTMSK2 ; enable correlation event
;  mce_ram_bank.asm:    771   
;  mce_ram_bank.asm:    772         
;  mce_ram_bank.asm:    773 SYNC_SEARCH:
;  mce_ram_bank.asm:    774         wait
;  mce_ram_bank.asm:    775         input   MCEEVENT2, r0                           ;
;  mce_ram_bank.asm:    776         btst    MCEEVENT2_C1BE_A_POS_PEAK, r0           ; check if correlator peak
;  mce_ram_bank.asm:    777         bne     DUMP_SAMPLES                            ;
;  mce_ram_bank.asm:    778         jmp  SYNC_SEARCH        ; otherwise continue sync search 
;  mce_ram_bank.asm:    779         
;  mce_ram_bank.asm:    780   
;  mce_ram_bank.asm:    781 DUMP_SAMPLES:
;  mce_ram_bank.asm:    782         outbset 1, RFESEND                              ; Notify by bit 1 in RFESEND (sync found)
;  mce_ram_bank.asm:    783         
;  mce_ram_bank.asm:    784   DBG_PRINT0 "########################### Sync Found REGISTER MODE -> IQ Dump starting ########################"
;  mce_ram_bank.asm:    785         outbset MCEEVENT2_C1BE_A_POS_PEAK, MCEEVENTCLR2 ;  clear the event flag
;  mce_ram_bank.asm:    786         outbclr MCEEVENT2_C1BE_A_POS_PEAK, MCEEVENTMSK2 ; disable correlation event
;  mce_ram_bank.asm:    787         outbset MCEEVENT0_CLKEN_4BAUD, MCEEVENTMSK0     ; enable the clkenbaud_4f event        
;  mce_ram_bank.asm:    788         lli     3, r5                                   ; to trigger capture of I and Q
;  mce_ram_bank.asm:    789 
;  mce_ram_bank.asm:    790   
;  mce_ram_bank.asm:    791 LOOP_SAMPLES:           
;  mce_ram_bank.asm:    792         wait
;  mce_ram_bank.asm:    793         output  r5, RDCAPT1                             ; capture I + Q from FRAC
;  mce_ram_bank.asm:    794         outbset RDCAPT0_DEMPDIF0, RDCAPT0               ; capture instantaneous frequency
;  mce_ram_bank.asm:    795         outbset MCESTROBES0_EVENT0, MCESTROBES0         ; signal 4BAUD to cm0/cm3  
;  mce_ram_bank.asm:    796         outbset MCEEVENT0_CLKEN_4BAUD, MCEEVENTCLR0     ; clear the clkenbaud_4f event
;  mce_ram_bank.asm:    797         jmp     LOOP_SAMPLES                            ; 
;  mce_ram_bank.asm:    798 
;  mce_ram_bank.asm:    799 ;;; --------------------------------------------------------------------------
;  mce_ram_bank.asm:    800 ;;; MRX IQdump Sync FIFO MODE started where IQ samples are moved into RFC FIFO
;  mce_ram_bank.asm:    801 ;;;   - Packet size can be programmed by the API
;  mce_ram_bank.asm:    802 ;;;   - IQ dump start after SFD detection
;  mce_ram_bank.asm:    803 ;;; 
;  mce_ram_bank.asm:    804 MRX_Entry_FIFO_SYNC:
;  mce_ram_bank.asm:    805         DBG_PRINT0 "########################### IQ Dump through RFC FIFO, RX started, Wait for Sync (DataRate <= 12.5 kbps) ########################"
;  mce_ram_bank.asm:    806   ;;; Just to be sure those interrupts are disabled, there is no normal termination. 
;  mce_ram_bank.asm:    807         outbclr MCEEVENT0_CLKEN_4BAUD, MCEEVENTMSK0     ; disable the clkenbaud_4f event        
;  mce_ram_bank.asm:    808         outbclr MCEEVENT2_C1BE_A_POS_PEAK, MCEEVENTMSK2 ; disable correlation event
;  mce_ram_bank.asm:    809         outbclr MCEEVENT2_C1BE_B_POS_PEAK, MCEEVENTMSK2 ; disable correlation event
;  mce_ram_bank.asm:    810         outset  MCEEVENTCLR0    
;  mce_ram_bank.asm:    811         outset  MCEEVENTCLR1
;  mce_ram_bank.asm:    812         jsr  MRX_SETUP
;  mce_ram_bank.asm:    813   
;  mce_ram_bank.asm:    814         lli  24, r11          ; Set Word Counter 
;  mce_ram_bank.asm:    815         lli     0x0, r0          ; MDMFIFOWRCTRL, 1 bits write, from modem
;  mce_ram_bank.asm:    816         output  r0, MDMFIFOWRCTRL
;  mce_ram_bank.asm:    817         mov  0, r12          ; Clear bit counter
;  mce_ram_bank.asm:    818         mov  1, r8          ; preload register for known pattern generation 
;  mce_ram_bank.asm:    819         lmd  IQDUMP_TEST_MAX_VAL, r10    ; Test pattern wrap value 
;  mce_ram_bank.asm:    820         lmd  IQDUMP_MAX_POS_VAL, r13      ; Positive Saturation value for 12 bit resolution 
;  mce_ram_bank.asm:    821         lmd  IQDUMP_MIN_NEG_VAL, r14      ; Negative Saturation value for 12 bit resolution
;  mce_ram_bank.asm:    822         mov  r10, r9          ; preload register for known pattern generation
;  mce_ram_bank.asm:    823 
;  mce_ram_bank.asm:    824   
;  mce_ram_bank.asm:    825   ;; Enable Correlator event
;  mce_ram_bank.asm:    826         outbset MCEEVENT2_C1BE_A_POS_PEAK, MCEEVENTCLR2 ; Clear correlator event 
;  mce_ram_bank.asm:    827         outbset MCEEVENT2_C1BE_A_POS_PEAK, MCEEVENTMSK2 ; enable correlation event
;  mce_ram_bank.asm:    828   
;  mce_ram_bank.asm:    829         
;  mce_ram_bank.asm:    830 SYNC_SEARCH_FIFO:
;  mce_ram_bank.asm:    831         wait
;  mce_ram_bank.asm:    832         input   MCEEVENT2, r0                           ;
;  mce_ram_bank.asm:    833         btst    MCEEVENT2_C1BE_A_POS_PEAK, r0           ; check if correlator peak
;  mce_ram_bank.asm:    834         bne     DUMP_SAMPLES_FIFO                       ;
;  mce_ram_bank.asm:    835         jmp  SYNC_SEARCH_FIFO      ; otherwise continue sync search 
;  mce_ram_bank.asm:    836         
;  mce_ram_bank.asm:    837   
;  mce_ram_bank.asm:    838 DUMP_SAMPLES_FIFO:
;  mce_ram_bank.asm:    839         outbset MCESTROBES0_EVENT0, MCESTROBES0         ; signal Sync Found
;  mce_ram_bank.asm:    840         outbset 1, RFESEND                              ; Notify by bit 1 in RFESEND (sync found)
;  mce_ram_bank.asm:    841         
;  mce_ram_bank.asm:    842         DBG_PRINT0 "########################### Sync Found RFC FIFO MODE-> IQ samples through FIFO starting ########################"
;  mce_ram_bank.asm:    843         outbset MCEEVENT2_C1BE_A_POS_PEAK, MCEEVENTCLR2 ; clear the event flag
;  mce_ram_bank.asm:    844         outbclr MCEEVENT2_C1BE_A_POS_PEAK, MCEEVENTMSK2 ; disable correlation event
;  mce_ram_bank.asm:    845         outbset MCEEVENT0_CLKEN_4BAUD, MCEEVENTMSK0     ; enable the clkenbaud_4 event
;  mce_ram_bank.asm:    846 
;  mce_ram_bank.asm:    847 ;;; Add delay between sync found is signalled and first RFC FIFO write.
;  mce_ram_bank.asm:    848 ;;; Wait loop for cm0 to be ready to do full speed readout from RFC FIFO (otherwise longer delay than 8.4us has been observed!)
;  mce_ram_bank.asm:    849         lli  2, r0
;  mce_ram_bank.asm:    850 LOOP_SAMPLES_FIFO_SYNC_WAIT:
;  mce_ram_bank.asm:    851         outbset MCEEVENT0_CLKEN_4BAUD, MCEEVENTCLR0     ; clear the clkenbaud_4 event
;  mce_ram_bank.asm:    852         wait
;  mce_ram_bank.asm:    853         loop  LOOP_SAMPLES_FIFO_SYNC_WAIT
;  mce_ram_bank.asm:    854   
;  mce_ram_bank.asm:    855         lli     3, r5                                   ; to trigger capture of I and Q
;  mce_ram_bank.asm:    856 
;  mce_ram_bank.asm:    857 LOOP_SAMPLES_FIFO_SYNC:
;  mce_ram_bank.asm:    858         outbset MCEEVENT0_CLKEN_4BAUD, MCEEVENTCLR0     ; clear the clkenbaud_4 event
;  mce_ram_bank.asm:    859         wait            ; Only 4baud event wakes up TopSM 
;  mce_ram_bank.asm:    860         output  r5, RDCAPT1                             ; capture I + Q from FRAC
;  mce_ram_bank.asm:    861         input  DEMFRAC4, r0
;  mce_ram_bank.asm:    862         jsr  SignExt_and_Saturate      ; Saturate to 12 bit word 
;  mce_ram_bank.asm:    863   
;  mce_ram_bank.asm:    864         input  MDMSPAR2, r1        ; MDMSPAR2[0] 0-> IQ data, 1 -> Known Test pattern (counter value)
;  mce_ram_bank.asm:    865         btst  0, r1
;  mce_ram_bank.asm:    866         beq  LOOP_SAMPLES_FIFO_SYNC_DEMFRAC4WR
;  mce_ram_bank.asm:    867         mov  r8, r0          ; Known link test pattern
;  mce_ram_bank.asm:    868         cmp  r10, r8
;  mce_ram_bank.asm:    869         bne  TEST_PATTERN_ADD_SYNC
;  mce_ram_bank.asm:    870         mov  0, r8
;  mce_ram_bank.asm:    871 TEST_PATTERN_ADD_SYNC:    
;  mce_ram_bank.asm:    872         add  1, r8
;  mce_ram_bank.asm:    873 LOOP_SAMPLES_FIFO_SYNC_DEMFRAC4WR:  
;  mce_ram_bank.asm:    874         jsr  MDMFIFOWR_AND_WAIT10
;  mce_ram_bank.asm:    875   
;  mce_ram_bank.asm:    876 
;  mce_ram_bank.asm:    877         input  DEMFRAC5, r0
;  mce_ram_bank.asm:    878         jsr  SignExt_and_Saturate      ; Saturate to 12 bit word 
;  mce_ram_bank.asm:    879         input  MDMSPAR2, r1        ; MDMSPAR2[0] 0-> IQ data, 1 -> Known Test pattern (counter value)
;  mce_ram_bank.asm:    880         btst  0, r1
;  mce_ram_bank.asm:    881         beq  LOOP_SAMPLES_FIFO_SYNC_DEMFRAC5WR
;  mce_ram_bank.asm:    882         mov  r9, r0          ; Known link test pattern
;  mce_ram_bank.asm:    883         sub  1, r9
;  mce_ram_bank.asm:    884         cmp  0, r9
;  mce_ram_bank.asm:    885         bne  LOOP_SAMPLES_FIFO_SYNC_DEMFRAC5WR
;  mce_ram_bank.asm:    886         mov  r10, r9
;  mce_ram_bank.asm:    887 LOOP_SAMPLES_FIFO_SYNC_DEMFRAC5WR:  
;  mce_ram_bank.asm:    888         jsr  MDMFIFOWR_AND_WAIT10
;  mce_ram_bank.asm:    889   
;  mce_ram_bank.asm:    890         input   MDMCMDPAR1, r4                          ; check if length has been given
;  mce_ram_bank.asm:    891         cmp     0, r4                                   ; if length is zero, infinite length is assumed
;  mce_ram_bank.asm:    892         beq     LOOP_SAMPLES_FIFO_SYNC
;  mce_ram_bank.asm:    893         add     r11, r12                                ; increment bit counter
;  mce_ram_bank.asm:    894         cmp     r4, r12                                 ; End if rxbits - pktLen >= 0
;  mce_ram_bank.asm:    895         bpl     MRX_GenFSK_CommonEnd                    ; if so jump to end
;  mce_ram_bank.asm:    896         jmp     LOOP_SAMPLES_FIFO_SYNC                 ; 
;  mce_ram_bank.asm:    897   
;  mce_ram_bank.asm:    898 
;  mce_ram_bank.asm:    899 
;  mce_ram_bank.asm:    900 MRX_SETUP:
;  mce_ram_bank.asm:    901 
;  mce_ram_bank.asm:    902        ;; Wait for RFE to finish enabling Rx chain
;  mce_ram_bank.asm:    903         input   RFERCEV, r0     ;
;  mce_ram_bank.asm:    904         btst    3, r0           ;
;  mce_ram_bank.asm:    905         bne     RFE_Started     ;
;  mce_ram_bank.asm:    906         
;  mce_ram_bank.asm:    907         outbset MCEEVENT0_RFECMD_IRQ, MCEEVENTMSK0
;  mce_ram_bank.asm:    908         wait                    ; Wait for RFE to be done
;  mce_ram_bank.asm:    909         outbset MCEEVENT0_RFECMD_IRQ, MCEEVENTCLR0
;  mce_ram_bank.asm:    910 
;  mce_ram_bank.asm:    911         ;; Disable event
;  mce_ram_bank.asm:    912         outbclr MCEEVENT0_RFECMD_IRQ, MCEEVENTMSK0
;  mce_ram_bank.asm:    913 
;  mce_ram_bank.asm:    914         jmp   MRX_SETUP    ; Go back to test received event
;  mce_ram_bank.asm:    915 
;  mce_ram_bank.asm:    916 RFE_Started:    
;  mce_ram_bank.asm:    917         DBG_PRINT0 "########################### RX Started ########################"
;  mce_ram_bank.asm:    918         outbset MCEEVENT0_CPEFWEVENT0, MCEEVENTCLR0        ; Clear any pending CPEFWEVENT0
;  mce_ram_bank.asm:    919 
;  mce_ram_bank.asm:    920 
;  mce_ram_bank.asm:    921         ;; Enable Demodulator, ADCDIG, Timebase and submodules
;  mce_ram_bank.asm:    922         ;;; Enable ADCDIG, and start sync search
;  mce_ram_bank.asm:    923         outbset MDMENABLE_ADCDIG, MDMENABLE
;  mce_ram_bank.asm:    924         outbset MDMINIT_ADCDIG, MDMINIT
;  mce_ram_bank.asm:    925         ;;; Enable RX, and start sync search
;  mce_ram_bank.asm:    926         outbset MDMENABLE_DEMODULATOR, MDMENABLE
;  mce_ram_bank.asm:    927         outbset MDMINIT_DEMODULATOR, MDMINIT
;  mce_ram_bank.asm:    928         ;; Enable timebase now.
;  mce_ram_bank.asm:    929         outbset MDMENABLE_TIMEBASE, MDMENABLE
;  mce_ram_bank.asm:    930         outbset MDMINIT_TIMEBASE, MDMINIT
;  mce_ram_bank.asm:    931 
;  mce_ram_bank.asm:    932 
;  mce_ram_bank.asm:    933   ;; Compute MASKA+MASKB for SyncWords < 32 bits
;  mce_ram_bank.asm:    934         ;; (the threshold adjusted automatically by the CPE)
;  mce_ram_bank.asm:    935         input   DEMC1BE0, r0                     ; Load DEMC1BE0
;  mce_ram_bank.asm:    936         lmd  DEMC1BE0_MASKA_BITS, r2     ; Clear only bits [15:6], keep rest
;  mce_ram_bank.asm:    937         and     r2, r0                           ; 
;  mce_ram_bank.asm:    938         input   MDMCMDPAR0, r3                   ; Get number of bits in SyncWord again
;  mce_ram_bank.asm:    939         sr0     8, r3                            ; MDMCMDPAR0[15:8]
;  mce_ram_bank.asm:    940         bclr    7, r3                            ; Ignore MSB always
;  mce_ram_bank.asm:    941         output  r3, DEMSWQU0                     ; set SyncWordBits-1 in DEMSWQU0 for future reference
;  mce_ram_bank.asm:    942         lli     31, r2                           ; Compute 31-X
;  mce_ram_bank.asm:    943         sub     r3, r2                           ; R2 = 31-SyncWordBits
;  mce_ram_bank.asm:    944         sl0     DEMC1BE0_MASKA, r2               ; Shift to proper position
;  mce_ram_bank.asm:    945         mov     r2, r1                           ; copy
;  mce_ram_bank.asm:    946         sl0     5, r1                            ; shift to mask b position
;  mce_ram_bank.asm:    947         or      r1, r2                           ; combine mask a + mask b
;  mce_ram_bank.asm:    948         or      r2, r0                           ; put together
;  mce_ram_bank.asm:    949         output  r0, DEMC1BE0                     ; and done
;  mce_ram_bank.asm:    950 
;  mce_ram_bank.asm:    951   ;; IQDUMP use running sum hardware in DSBU for frequency offset estimation, FOE (for supporting non random data)
;  mce_ram_bank.asm:    952   ;; The DSBU delay shall be the synw word length+a few samples for processing delay
;  mce_ram_bank.asm:    953   ;; DSBBU avg length shall be set to 8, 16 or 32 symbols (rounded down from the sync word length) due to division needed
;  mce_ram_bank.asm:    954   ;;; Start calculating DSBU.LEN 
;  mce_ram_bank.asm:    955         mov  r3, r0        ; Load r0 with SyncWordBits-1
;  mce_ram_bank.asm:    956         add  1,r0        ; Calculate SyncWordBits
;  mce_ram_bank.asm:    957         sr0  3,r0        ; Floor(SyncWordBits/8) (number of whole bytes in sw)
;  mce_ram_bank.asm:    958 
;  mce_ram_bank.asm:    959         btst    1, r0                           ; we don't allow 3 bytes averaging, set this to two bytes
;  mce_ram_bank.asm:    960         beq     GEN_FSK_AVG_LEN_CORRECT       
;  mce_ram_bank.asm:    961         mov     2, r0                           ; force a 16 bit avg length
;  mce_ram_bank.asm:    962 GEN_FSK_AVG_LEN_CORRECT:                
;  mce_ram_bank.asm:    963         sl0  5,r0        ; 4*8*Floor(SyncWordBits/8), i.e. osr = 4 (number of samples in DSBU averaging)        
;  mce_ram_bank.asm:    964         mov  r0, r3        ; DSBUAVGLENGTH for future use
;  mce_ram_bank.asm:    965               
;  mce_ram_bank.asm:    966         sl0  8, r0        ; Shift to proper position 
;  mce_ram_bank.asm:    967         add  3,r0        ; DSBUDELAY = DSBUAVGLENGTH+3
;  mce_ram_bank.asm:    968         output  r0, DEMDSBU
;  mce_ram_bank.asm:    969 
;  mce_ram_bank.asm:    970 
;  mce_ram_bank.asm:    971         ;; Find imbalance in that part of sync word which is used in dsbu averaging
;  mce_ram_bank.asm:    972   ;; Implement this equation:   DEMSWIMBAL = (sum(sw)-DEMDSBU.dsbuavglength/2)*4*32/DEMDSBU.dsbuavglength
;  mce_ram_bank.asm:    973         mov     0, r2                           ;
;  mce_ram_bank.asm:    974         mov     0, r4                           ;        
;  mce_ram_bank.asm:    975 GEN_FSK_DSBU_AVG_LEN_32_SYMBOLS_CHECK:        
;  mce_ram_bank.asm:    976         btst    7, r3                           ; Check if we got 128 sample averaging
;  mce_ram_bank.asm:    977         beq     GEN_FSK_DSBU_AVG_LEN_16_SYMBOLS_CHECK ;
;  mce_ram_bank.asm:    978 GEN_FSK_DSBU_AVG_LEN_32_SYMBOLS:                    
;  mce_ram_bank.asm:    979         input   MDMSYNC0, r0      ; 16 first symbols of sw A is in MDMSYNC0
;  mce_ram_bank.asm:    980         output  r0, COUNT1IN      ; Find number of ones 
;  mce_ram_bank.asm:    981         input   COUNT1RES, r2      ; r2 is keeping the number of 1s in the sw A
;  mce_ram_bank.asm:    982         sub     8, r2                           ; subtract 8 to get imbalance between 1's and 0's in this 16 bits part of SW
;  mce_ram_bank.asm:    983         input   MDMSYNC2, r0      ; 16 first symbols of sw A is in MDMSYNC2
;  mce_ram_bank.asm:    984         output  r0, COUNT1IN      ; Find number of ones 
;  mce_ram_bank.asm:    985         input   COUNT1RES, r4      ; r4 is keeping the number of 1s in the sw B
;  mce_ram_bank.asm:    986         sub     8, r4                           ; subtract 8 to get imbalance between 1's and 0's in this 16 bits part of SW        
;  mce_ram_bank.asm:    987         jmp     GEN_FSK_DSBU_AVG_LEN_16_SYMBOLS ; For 32 bit sync use both SYNC0 and SYNC1
;  mce_ram_bank.asm:    988 GEN_FSK_DSBU_AVG_LEN_16_SYMBOLS_CHECK:          
;  mce_ram_bank.asm:    989         btst    6, r3                           ; Check if DSBU memory is 16 symbols (or 64 samples)        
;  mce_ram_bank.asm:    990         beq     GEN_FSK_DSBU_AVG_LEN_8_SYMBOLS ;
;  mce_ram_bank.asm:    991 GEN_FSK_DSBU_AVG_LEN_16_SYMBOLS:                  
;  mce_ram_bank.asm:    992         input   MDMSYNC1, r0      ; 16 Last transmitted sync bits of sw A is located in SYNC1, swlen>=16
;  mce_ram_bank.asm:    993         output  r0, COUNT1IN      ; Find number of ones in the sw and store in DEMSWIMBAL for future reference
;  mce_ram_bank.asm:    994         input   COUNT1RES, r0      ;
;  mce_ram_bank.asm:    995         sub     8, r0                           ; subtract 8 to get imbalance in this 16 bit part of sw A
;  mce_ram_bank.asm:    996         add     r0, r2        ; load r2 = sum(x)
;  mce_ram_bank.asm:    997         input   MDMSYNC3, r0      ; 16 Last transmitted sync bits of sw B is located in SYNC1, swlen>=16
;  mce_ram_bank.asm:    998         output  r0, COUNT1IN      ; Find number of ones in the sw and store in DEMSWIMBAL for future reference
;  mce_ram_bank.asm:    999         input   COUNT1RES, r0      ;
;  mce_ram_bank.asm:   1000         sub     8, r0                           ; subtract 8 to get imbalance in this 16 bit part of sw B
;  mce_ram_bank.asm:   1001         add     r0, r4        ; load r4 = sum(x)        
;  mce_ram_bank.asm:   1002         jmp  GEN_FSK_CALC_DEMSWIMBAL    ; sum(sw) done for 32 symbols FOE
;  mce_ram_bank.asm:   1003 GEN_FSK_DSBU_AVG_LEN_8_SYMBOLS:
;  mce_ram_bank.asm:   1004         input   MDMSYNC1, r0            ;8 Last transmitted sync bits of SW A is located in SYNC1(31:24), swlen>=8
;  mce_ram_bank.asm:   1005         lmd  IQDUMP_MASK_BITS_15_8, r1        
;  mce_ram_bank.asm:   1006         and  r1,r0
;  mce_ram_bank.asm:   1007         output  r0, COUNT1IN      ; Find number of ones in the sw A and store in DEMSWIMBAL for future reference
;  mce_ram_bank.asm:   1008         input   COUNT1RES, r2      ; load r2 = sum(x)        
;  mce_ram_bank.asm:   1009         sub     4, r2                           ; subtract 4 to get imbalance in this byte of SW A
;  mce_ram_bank.asm:   1010         input   MDMSYNC3, r0            ;8 Last transmitted sync bits of SW B is located in SYNC3(31:24), swlen>=8
;  mce_ram_bank.asm:   1011         lmd  IQDUMP_MASK_BITS_15_8, r1        
;  mce_ram_bank.asm:   1012         and  r1,r0
;  mce_ram_bank.asm:   1013         output  r0, COUNT1IN      ; Find number of ones in the sw B and store in DEMSWIMBAL for future reference
;  mce_ram_bank.asm:   1014         input   COUNT1RES, r4      ; load r4 = sum(x)        
;  mce_ram_bank.asm:   1015         sub     4, r4                           ; subtract 4 to get imbalance in this byte of SW B
;  mce_ram_bank.asm:   1016 GEN_FSK_CALC_DEMSWIMBAL:
;  mce_ram_bank.asm:   1017         ;; balance between 1's and 0's in SW will have to be scaled with the dsbu avg length
;  mce_ram_bank.asm:   1018         ;; 32 bit avg length we shall multiply by 4
;  mce_ram_bank.asm:   1019         ;; 16 bit avg length we shall multiply by 8
;  mce_ram_bank.asm:   1020         ;; 8  bit avg length we shall multiply by 16
;  mce_ram_bank.asm:   1021         ;; to make a more efficient shift below we start with a multiply by 32
;  mce_ram_bank.asm:   1022         sl0     5, r2           ; always multiply sw a imbalance by 32
;  mce_ram_bank.asm:   1023         sl0     5, r4           ; always multiply sw b imbalance by 32        
;  mce_ram_bank.asm:   1024         sr0     6, r3           ; shift avg length down
;  mce_ram_bank.asm:   1025         and     3, r3           ; mask other bits
;  mce_ram_bank.asm:   1026         add     1, r3           ; 
;  mce_ram_bank.asm:   1027         sr0     r3, r2          ; divide with 2 or 4 or 8 depending on avg length
;  mce_ram_bank.asm:   1028         sr0     r3, r4          ; divide with 2 or 4 or 8 depending on avg length
;  mce_ram_bank.asm:   1029         sl0     8, r2           ;
;  mce_ram_bank.asm:   1030         sr0     8, r2           ;
;  mce_ram_bank.asm:   1031         sl0     8, r4           ; 
;  mce_ram_bank.asm:   1032         or      r4, r2          ; combine swA and sw b
;  mce_ram_bank.asm:   1033         output  r2, DEMSWIMBAL ;         
;  mce_ram_bank.asm:   1034 GEN_FSK_CALC_DEMSWIMBAL_DONE:  
;  mce_ram_bank.asm:   1035 
;  mce_ram_bank.asm:   1036   ;; Copy all sync registers to new correlator registers
;  mce_ram_bank.asm:   1037         input   MDMSYNC0, r0
;  mce_ram_bank.asm:   1038         output  r0, DEMC1BEREF0  
;  mce_ram_bank.asm:   1039         input   MDMSYNC1, r0
;  mce_ram_bank.asm:   1040         output  r0, DEMC1BEREF1  
;  mce_ram_bank.asm:   1041         input   MDMSYNC2, r0
;  mce_ram_bank.asm:   1042         output  r0, DEMC1BEREF2  
;  mce_ram_bank.asm:   1043         input   MDMSYNC3, r0
;  mce_ram_bank.asm:   1044         output  r0, DEMC1BEREF3  
;  mce_ram_bank.asm:   1045     
;  mce_ram_bank.asm:   1046         ;; Initial Module Enables  
;  mce_ram_bank.asm:   1047         lmd     DEMENABLE0_RX_IQDUMP, r0
;  mce_ram_bank.asm:   1048         output  r0, DEMENABLE0  ; cmix, ctil, bdec, chfi, fidc, frac ,iqmc, enable
;  mce_ram_bank.asm:   1049         output  r0, DEMINIT0
;  mce_ram_bank.asm:   1050         lmd     DEMENABLE1_RX_IQDUMP, r0
;  mce_ram_bank.asm:   1051         output  r0, DEMENABLE1  ;        
;  mce_ram_bank.asm:   1052         output  r0, DEMINIT1
;  mce_ram_bank.asm:   1053         outbset 5, RFESEND                              ; send message to rfe that reception is starting
;  mce_ram_bank.asm:   1054 
;  mce_ram_bank.asm:   1055         lli     0xD9, r0        ;
;  mce_ram_bank.asm:   1056         output  r0, MDMCMDPAR0  ; 
;  mce_ram_bank.asm:   1057         rts
;  mce_ram_bank.asm:   1058 
;  mce_ram_bank.asm:   1059 ;;; ============================================================================================
;  mce_ram_bank.asm:   1060 ;;; Common End of RX function
;  mce_ram_bank.asm:   1061         
;  mce_ram_bank.asm:   1062 MRX_GenFSK_CommonEnd:  
;  mce_ram_bank.asm:   1063         outbclr 5, RFESEND      ; tell RFE packet is ending
;  mce_ram_bank.asm:   1064   ;;; Wait to let RFE end 
;  mce_ram_bank.asm:   1065         outbset MCEEVENT0_CLKEN_4BAUD, MCEEVENTCLR0     ; clear the clkenbaud_4 event
;  mce_ram_bank.asm:   1066         wait
;  mce_ram_bank.asm:   1067     
;  mce_ram_bank.asm:   1068         outbclr MCEEVENT0_CLKEN_4BAUD, MCEEVENTMSK0  ; disable the clkenbaud_4f event        
;  mce_ram_bank.asm:   1069         outbset MCEEVENT0_CLKEN_4BAUD, MCEEVENTCLR0     ; clear the clkenbaud_4f event
;  mce_ram_bank.asm:   1070         outbset RDCAPT0_DEMLQIE0, RDCAPT0               ; Capture LQI into MDMSTATUS[15:8]
;  mce_ram_bank.asm:   1071         input  MDMSTATUS, r0
;  mce_ram_bank.asm:   1072         input   DEMLQIE0, r4
;  mce_ram_bank.asm:   1073         sr0     2, r4          ; Divide by 4 first
;  mce_ram_bank.asm:   1074         sl0     8, r4
;  mce_ram_bank.asm:   1075         or  r0,r4
;  mce_ram_bank.asm:   1076         output  r4, MDMSTATUS        ; Warning: CPE use MDMSTATUS[1:0] for CMD_DONE checking
;  mce_ram_bank.asm:   1077         DBG_PRINT0 "All bits received, MCE Ending"
;  mce_ram_bank.asm:   1078         ;; Hard init of all modules except FIFO
;  mce_ram_bank.asm:   1079         outset  TIMCTRL          ;
;  mce_ram_bank.asm:   1080         outclr  TIMCTRL          ;
;  mce_ram_bank.asm:   1081         jsr    MODCTRL_CLR      ; 
;  mce_ram_bank.asm:   1082   
;  mce_ram_bank.asm:   1083         outclr  MDMENABLE_ADCDIG, MDMENABLE      ; 
;  mce_ram_bank.asm:   1084         outclr  MDMENABLE_TIMEBASE, MDMENABLE    ;
;  mce_ram_bank.asm:   1085         outclr  MDMENABLE_DEMODULATOR, MDMENABLE ;
;  mce_ram_bank.asm:   1086         outset  DEMINIT0         ;
;  mce_ram_bank.asm:   1087         outset  DEMINIT1         ;
;  mce_ram_bank.asm:   1088         jmp     CMD_OK_END
;  mce_ram_bank.asm:   1089 
;  mce_ram_bank.asm:   1090   
;  mce_ram_bank.asm:   1091   ;; clear all bits in MODCTRL exept bit 12 (keep bit 12)
;  mce_ram_bank.asm:   1092 MODCTRL_CLR:
;  mce_ram_bank.asm:   1093         input   MODCTRL, r0     ; 
;  mce_ram_bank.asm:   1094         lli     0x80, r1        ;
;  mce_ram_bank.asm:   1095         sl0     5, r1           ; set bit 12 to 1
;  mce_ram_bank.asm:   1096         and     r1, r0          ;
;  mce_ram_bank.asm:   1097         output  r0, MODCTRL     ; 
;  mce_ram_bank.asm:   1098         rts
;  mce_ram_bank.asm:   1099   
;  mce_ram_bank.asm:   1100 ;    
;  mce_ram_bank.asm:   1101 ;;; --------------------------------------------------------------------------------
;  mce_ram_bank.asm:   1102 ;;; Function for handling debug print
;  mce_ram_bank.asm:   1103 ;;; 
;  mce_ram_bank.asm:   1104         DBG_FUNC       
*/
