
	EXPORT Enable_Performance_Monitor
	EXPORT Performance_Monitor_Start
	EXPORT Performance_Monitor_Stop
	EXPORT Performance_Monitor_Read_Counter0
	EXPORT Performance_Monitor_Read_Counter1
	EXPORT Performance_Monitor_Read_Counter2
	EXPORT Performance_Monitor_Read_CycleCount


                AREA    |.text|, CODE, READONLY
                ARM

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
	ORR r0, r0, #7				; reset cycle + performance counters and enable
	MCR p15, #0, r0, c9, c12, #0 	; Write PMNC Register
	BX  LR

Performance_Monitor_Start

	MRC p15, #0, r0, c9, c12, #1 	; Read CNTENS Register
	ORR r0, r0, #7				; Enable counters 0,1,2
	ORR r0, r0, #0x80000000		; Enable cycle counter
	MCR p15, #0, r0, c9, c12, #1 	; Write CNTENS Register
	BX LR;

Performance_Monitor_Stop
 

	MRC p15, #0, r0, c9, c12, #2 	; Read CNTENC Register 
	ORR r0, r0, #7				; Disable counters 0,1,2 
	ORR r0, r0, #0x80000000		; Disable cycle counter 
  	MCR p15, #0, r0, c9, c12, #2 	; Write CNTENC Register");
	BX  LR
 

Performance_Monitor_Read_Counter0
 
	MOV r0, #0 
	MCR p15, #0, r0, c9, c12, #5 	; Write PMNXSEL Register = select performance monitor counter #0 
	MRC p15, #0, r0, c9, c13, #2 	; Read current PMNx Register   
	BX LR;
 

Performance_Monitor_Read_Counter1
 
	MOV r0, #1 
	MCR p15, #0, r0, c9, c12, #5 	; Write PMNXSEL Register = select performance monitor counter #1 
	MRC p15, #0, r0, c9, c13, #2 	; Read current PMNx Register   
	BX LR
	
 

Performance_Monitor_Read_Counter2
 
	MOV r0, #2 
	MCR p15, #0, r0, c9, c12, #5 	; Write PMNXSEL Register = select performance monitor counter #2 
	MRC p15, #0, r0, c9, c13, #2 	; Read current PMNx Register   
	BX  LR
	
 


Performance_Monitor_Read_CycleCount
 
	
	MRC p15, #0, r0, c9, c13, #0 	; Read CCNT Register   
	BX LR
	
 				   END


