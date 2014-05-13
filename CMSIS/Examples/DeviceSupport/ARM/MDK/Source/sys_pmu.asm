;-------------------------------------------------------------------------------
; sys_pmu.asm
;
; (c) Texas Instruments 2010, All rights reserved.
;

    area |.text|, code, readonly
    arm


;-------------------------------------------------------------------------------
; Initialize Pmu
; Note: It will reset all counters

    export     _pmuInit_
    

_pmuInit_

        stmfd sp!, {r0}
        ; set control register
        mrc   p15, #0, r0, c9, c12, #0 
        orr   r0,  r0, #(1 << 4) + 6 + 1
        mcr   p15, #0, r0, c9, c12, #0
        ; clear flags
		mov   r0,  #0
		mcr   p15, #0, r0, c9, c12, #3 
        ; select counter 0 event
        mcr   p15, #0, r0, c9, c12, #5 ; select counter
        mov   r0,  #0x11
        mcr   p15, #0, r0, c9, c13, #1 ; select event
        ; select counter 1 event
		mov   r0,  #1
        mcr   p15, #0, r0, c9, c12, #5 ; select counter
        mov   r0,  #0x11
        mcr   p15, #0, r0, c9, c13, #1 ; select event
        ; select counter 2 event
		mov   r0,  #2
        mcr   p15, #0, r0, c9, c12, #5 ; select counter
        mov   r0,  #0x11
        mcr   p15, #0, r0, c9, c13, #1 ; select event
        ldmfd sp!, {r0}
        bx    lr

    


;-------------------------------------------------------------------------------
; Enable Counters Global [Cycle, Event [0..2]]
; Note: It will reset all counters

    export     _pmuEnableCountersGlobal_
    

_pmuEnableCountersGlobal_

        mrc   p15, #0, r0, c9, c12, #0 
        orr   r0,  r0, #7
        mcr   p15, #0, r0, c9, c12, #0
        bx    lr

    

;-------------------------------------------------------------------------------
; Disable Counters Global [Cycle, Event [0..2]]

    export     _pmuDisableCountersGlobal_
    

_pmuDisableCountersGlobal_

        mrc   p15, #0, r0, c9, c12, #0 
        bic   r0,  r0, #1
        mcr   p15, #0, r0, c9, c12, #0
        bx    lr
        
;-------------------------------------------------------------------------------
; Reset Cycle Counter

    export     _pmuResetCycleCounter_
    

_pmuResetCycleCounter_

        mrc   p15, #0, r0, c9, c12, #0 
        orr   r0,  r0, #4
        mcr   p15, #0, r0, c9, c12, #0
        bx    lr

    

;-------------------------------------------------------------------------------
; Reset Event Counters [0..2]

    export     _pmuResetEventCounters_
    

_pmuResetEventCounters_

        mrc   p15, #0, r0, c9, c12, #0 
        orr   r0,  r0, #2
        mcr   p15, #0, r0, c9, c12, #0
        bx    lr

    

;-------------------------------------------------------------------------------
; Reset Cycle Counter abd Event Counters [0..2]

    export     _pmuResetCounters_
    

_pmuResetCounters_

        mrc   p15, #0, r0, c9, c12, #0 
        orr   r0,  r0, #6
        mcr   p15, #0, r0, c9, c12, #0
        bx    lr

    

;-------------------------------------------------------------------------------
; Start Counters [Cycle, 0..2]

    export     _pmuStartCounters_
    

_pmuStartCounters_

        mcr   p15, #0, r0, c9, c12, #1
        bx    lr

    

;-------------------------------------------------------------------------------
; Stop Counters [Cycle, 0..2]

    export     _pmuStopCounters_
    

_pmuStopCounters_

        mcr   p15, #0, r0, c9, c12, #2
        bx    lr

    

;-------------------------------------------------------------------------------
; Set Count event

    export     _pmuSetCountEvent_
    

_pmuSetCountEvent_
 
        lsr   r0,  r0, #1
        mcr   p15, #0, r0, c9, c12, #5 ; select counter
        mcr   p15, #0, r1, c9, c13, #1 ; select event
        bx    lr

    

;-------------------------------------------------------------------------------
; Get Cycle Count

    export     _pmuGetCycleCount_
    

_pmuGetCycleCount_
 
        mrc   p15, #0, r0, c9, c13, #0
        bx    lr

    

;-------------------------------------------------------------------------------
; Get Event Counter Count Value

    export     _pmuGetEventCount_
    

_pmuGetEventCount_
 
        lsr   r0,  r0, #1
        mcr   p15, #0, r0, c9, c12, #5 ; select counter
        mrc   p15, #0, r0, c9, c13, #2 ; read event counter
        bx    lr

    

;-------------------------------------------------------------------------------
; Get Overflow Flags

    export     _pmuGetOverflow_
    

_pmuGetOverflow_
 
        mrc   p15, #0, r0, c9, c12, #3 ; read overflow
		mov   r1,  #0
		mcr   p15, #0, r1, c9, c12, #3 ; clear flags
        bx    lr

		
		
	export   Enable_Performance_Monitor	
Enable_Performance_Monitor
	MOV r0, #0
    MCR p15, #0, r0, c9, c12, #5 	; Write PMNXSEL Register = select performance monitor counter #0
	MOV r0, #0x01					; select I$ miss
	MCR p15, #0, r0, c9, c13, #1 	; Write EVTSELx Register

	MOV r0, #1
	MCR p15, #0, r0, c9, c12, #5 	; Write PMNXSEL Register = select performance monitor counter #1
	MOV r0, #0x03			    	; # D$ miss
	MCR p15, #0, r0, c9, c13, #1 	; Write EVTSELx Register

    MOV r0, #2
    MCR p15, #0, r0, c9, c12, #5 	; Write PMNXSEL Register = select performance monitor counter #2"
	MOV r0, #0x08					; Instruction architecturally executed
	MCR p15, #0, r0, c9, c13, #1 	; Write EVTSELx Register

	MRC p15, #0, r0, c9, c12, #0 	; Read PMNC Register
	ORR r0, r0, #7					; reset cycle + performance counters and enable
	MCR p15, #0, r0, c9, c12, #0 	; Write PMNC Register
    BX  LR
		
	export   Performance_Monitor_Start
Performance_Monitor_Start

	MRC p15, #0, r0, c9, c12, #1 	; Read CNTENS Register
	ORR r0, r0, #7					; Enable counters 0,1,2
	ORR r0, r0, #0x80000000			; Enable cycle counter
	MCR p15, #0, r0, c9, c12, #1 	; Write CNTENS Register
    BX LR;

    export   Performance_Monitor_Stop
Performance_Monitor_Stop
 
     MRC p15, #0, r0, c9, c12, #2 	; Read CNTENC Register 
	 ORR r0, r0, #7			    	; Disable counters 0,1,2 
	 ORR r0, r0, #0x80000000		; Disable cycle counter 
  	 MCR p15, #0, r0, c9, c12, #2 	; Write CNTENC Register");
	 BX  LR
	
    export   Performance_Monitor_Read_CycleCount
Performance_Monitor_Read_CycleCount
	
	 MRC p15, #0, r0, c9, c13, #0 	; Read CCNT Register   
     BX LR   		
    

    end

;-------------------------------------------------------------------------------

