;/*****************************************************************************/
;/* TMS570.S: Startup file for Texas Instruments TMS570 device series         */
;/*****************************************************************************/
;/* <<< Use Configuration Wizard in Context Menu >>>                          */ 
;/*****************************************************************************/
;/* This file is part of the uVision/ARM development tools.                   */
;/* Copyright (c) 2005-2010 Keil Software. All rights reserved.               */
;/* This software may only be used under the terms of a valid, current,       */
;/* end user licence from KEIL for a compatible version of KEIL software      */
;/* development tools. Nothing else gives you the right to use this software. */
;/*****************************************************************************/


; The Startup code is executed after CPU Reset.


; Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs

Mode_USR        EQU     0x0010
Mode_FIQ        EQU     0x0011
Mode_IRQ        EQU     0x0012
Mode_SVC        EQU     0x0013
Mode_ABT        EQU     0x0017
Mode_UND        EQU     0x001B
Mode_SYS        EQU     0x001F

I_Bit           EQU     0x0080          ; when I bit is set, IRQ is disabled
F_Bit           EQU     0x0040          ; when F bit is set, FIQ is disabled
E_Bit           EQU     0x0200          ; when E bit is set, data is big endian


;// <h> Stack Configuration (Stack Sizes in Bytes)
;//   <o0> Undefined Mode      <0x0-0xFFFFFFFF:8>
;//   <o1> Supervisor Mode     <0x0-0xFFFFFFFF:8>
;//   <o2> Abort Mode          <0x0-0xFFFFFFFF:8>
;//   <o3> Fast Interrupt Mode <0x0-0xFFFFFFFF:8>
;//   <o4> Interrupt Mode      <0x0-0xFFFFFFFF:8>
;//   <o5> User/System Mode    <0x0-0xFFFFFFFF:8>
;// </h>

UND_Stack_Size  EQU     0x00000000
SVC_Stack_Size  EQU     0x00000008
ABT_Stack_Size  EQU     0x00000000
FIQ_Stack_Size  EQU     0x00000000
IRQ_Stack_Size  EQU     0x00000080
USR_Stack_Size  EQU     0x00001400

ISR_Stack_Size  EQU     (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
                         FIQ_Stack_Size + IRQ_Stack_Size)

                AREA    STACK, NOINIT, READWRITE, ALIGN=3

Stack_Mem       SPACE   USR_Stack_Size
__initial_sp    SPACE   ISR_Stack_Size
Stack_Top


;// <h> Heap Configuration
;//   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF>
;// </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

;----------------------- CODE --------------------------------------------------

                PRESERVE8
                

; Area Definition and Entry Point
;  Startup Code must be linked first at Address at which it expects to run.

                AREA    RESET, CODE, READONLY
                ARM

                IF      :DEF:__RTX
                IMPORT  SWI_Handler
                ENDIF

; Exception Vectors
;  Mapped to Address 0.
;  Absolute addressing mode must be used.
;  Dummy Handlers are implemented as infinite loops which can be modified.

Vectors         LDR     PC,Reset_Addr         
                LDR     PC,Undef_Addr
                LDR     PC,SWI_Addr
                LDR     PC,PAbt_Addr
                LDR     PC,DAbt_Addr
                B       .
                LDR     PC,[PC,#-0x1b0]
                LDR     PC,[PC,#-0x1b0]

Reset_Addr      DCD     Reset_Handler
Undef_Addr      DCD     Undef_Handler
SWI_Addr        DCD     SWI_Handler
PAbt_Addr       DCD     PAbt_Handler
DAbt_Addr       DCD     DAbt_Handler
                DCD     0               ; Reserved Address
IRQ_Addr        DCD     IRQ_Handler
FIQ_Addr        DCD     FIQ_Handler

Undef_Handler   B       Undef_Handler
                IF      :LNOT::DEF:__RTX
SWI_Handler     B       SWI_Handler
                ENDIF
PAbt_Handler    B       PAbt_Handler
DAbt_Handler    B       DAbt_Handler
IRQ_Handler     B       IRQ_Handler
FIQ_Handler     B       FIQ_Handler


; Reset Handler

                EXPORT  Reset_Handler
Reset_Handler   
                MRC     p15,   #0x00, r0, c1, c0, #0x02
                ORR     r0,    r0, #0xF00000
                MCR     p15,   #0x00, r0, c1, c0, #0x02
                MOV     r0,    #0x40000000
                FMXR    fpexc, r0

                MOV     r0,  #0x0000   ; Initialization of R4F core registers
                MOV     r1,  #0x0000   ; necessary for lock-step device
                MOV     r2,  #0x0000
                MOV     r3,  #0x0000
                MOV     r4,  #0x0000
                MOV     r5,  #0x0000
                MOV     r6,  #0x0000
                MOV     r7,  #0x0000
                MOV     r8,  #0x0000
                MOV     r9,  #0x0000
                MOV     r10, #0x0000
                MOV     r11, #0x0000
                MOV     r12, #0x0000

                FMDRR   d0,  r1, r1    ; Initialization of FPU registers
                FMDRR   d1,  r1, r1
                FMDRR   d2,  r1, r1
                FMDRR   d3,  r1, r1
                FMDRR   d4,  r1, r1
                FMDRR   d5,  r1, r1
                FMDRR   d6,  r1, r1
                FMDRR   d7,  r1, r1
                FMDRR   d8,  r1, r1
                FMDRR   d9,  r1, r1
                FMDRR   d10, r1, r1
                FMDRR   d11, r1, r1
                FMDRR   d12, r1, r1
                FMDRR   d13, r1, r1
                FMDRR   d14, r1, r1
                FMDRR   d15, r1, r1

                BL      .+4            ; Initialization of return stack
                BL      .+4
                BL      .+4
                BL      .+4

; Setup Stack for each mode ----------------------------------------------------

                LDR     R0, =Stack_Top

;  Enter Undefined Instruction Mode and set its Stack Pointer
                MOV     R1, #Mode_UND:OR:I_Bit:OR:F_Bit:OR:E_Bit
                MSR     CPSR_cxsf, R1
                MOV     SP, R0
                MOV     R14, #0x0000
                MSR     SPSR_cxsf, R1
                SUB     R0, R0, #UND_Stack_Size

;  Enter Abort Mode and set its Stack Pointer
                MOV     R1, #Mode_ABT:OR:I_Bit:OR:F_Bit:OR:E_Bit
                MSR     CPSR_cxsf, R1
                MOV     SP, R0
                MOV     R14, #0x0000
                MSR     SPSR_cxsf, R1
                SUB     R0, R0, #ABT_Stack_Size

;  Enter FIQ Mode and set its Stack Pointer
                MOV     R1, #Mode_FIQ:OR:I_Bit:OR:F_Bit:OR:E_Bit
                MSR     CPSR_cxsf, R1
                MOV     SP, R0
                MOV     R8,  #0x0000
                MOV     R9,  #0x0000
                MOV     R10, #0x0000
                MOV     R11, #0x0000
                MOV     R12, #0x0000
                MOV     R14, #0x0000
                MSR     SPSR_cxsf, R1
                SUB     R0, R0, #FIQ_Stack_Size

;  Enter IRQ Mode and set its Stack Pointer
                MOV     R1, #Mode_IRQ:OR:I_Bit:OR:F_Bit:OR:E_Bit
                MSR     CPSR_cxsf, R1
                MOV     SP, R0
                MOV     R14, #0x0000
                MSR     SPSR_cxsf, R1
                SUB     R0, R0, #IRQ_Stack_Size

;  Enter Supervisor Mode and set its Stack Pointer
                MOV     R1, #Mode_SVC:OR:I_Bit:OR:F_Bit:OR:E_Bit
                MSR     CPSR_cxsf, R1
                MOV     SP, R0
                MOV     R14, #0x0000
                MSR     SPSR_cxsf, R1
                SUB     R0, R0, #SVC_Stack_Size

;  Enter User Mode and set its Stack Pointer
                MOV     R1, #Mode_SYS:OR:E_Bit
                MSR     CPSR_cxsf, R1
                MOV     R14, #0x0000

                IF      :DEF:__MICROLIB

                EXPORT __initial_sp

                ELSE

                MOV     SP, R0
                SUB     SL, SP, #USR_Stack_Size

                ENDIF

; Enter the C code -------------------------------------------------------------


                IMPORT  systemInit
                LDR     R0, =systemInit
                BLX     R0

                IMPORT  __main
                LDR     R0, =__main
                BX      R0



                IF      :DEF:__MICROLIB

                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE
; User Initial Stack & Heap
                AREA    |.text|, CODE, READONLY

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + USR_Stack_Size)
                LDR     R2, = (Heap_Mem +      Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDIF


                END
