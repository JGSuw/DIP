/** @file sys_startup.c 
*   @brief Startup Source File
*   @date 15.Aug.2012
*   @version 03.02.00
*
*   This file contains:
*   - Include Files
*   - Type Definitions
*   - External Functions
*   - VIM RAM Setup
*   - Startup Routine
*   .
*   which are relevant for the Startup.
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */


/* Include Files */

#include "sys_common.h"
#include "system.h"
#include "sys_vim.h"
#include "sys_core.h"
#include "sys_selftest.h"
#include "esm.h"
#include "mibspi.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */


/* Type Definitions */

typedef void (*handler_fptr)(const uint8_t *in, uint8_t *out);

/* USER CODE BEGIN (2) */
/* USER CODE END */


/* External Functions */

#pragma WEAK(__TI_Handler_Table_Base)
#pragma WEAK(__TI_Handler_Table_Limit)
#pragma WEAK(__TI_CINIT_Base)
#pragma WEAK(__TI_CINIT_Limit)

extern uint32_t   __TI_Handler_Table_Base;
extern uint32_t   __TI_Handler_Table_Limit;
extern uint32_t   __TI_CINIT_Base;
extern uint32_t   __TI_CINIT_Limit;
extern uint32_t   __TI_PINIT_Base;
extern uint32_t   __TI_PINIT_Limit;
extern uint32_t * __binit__;

extern void main(void);
extern void exit(void);

extern void muxInit(void);

/* USER CODE BEGIN (3) */
/* USER CODE END */


/* Vim Ram Definition */
/** @struct vimRam
*   @brief Vim Ram Definition
*
*   This type is used to access the Vim Ram.
*/
/** @typedef vimRAM_t
*   @brief Vim Ram Type Definition
*
*   This type is used to access the Vim Ram.
*/
typedef volatile struct vimRam
{
    t_isrFuncPTR ISR[VIM_CHANNELS + 1];
} vimRAM_t;

#define vimRAM ((vimRAM_t *)0xFFF82000U)

static const t_isrFuncPTR s_vim_init[] =
{
    &phantomInterrupt,
    &esmHighInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
};


/* Startup Routine */

/* USER CODE BEGIN (4) */
/* USER CODE END */

#pragma CODE_STATE(_c_int00, 32)
#pragma INTERRUPT(_c_int00, RESET)

void _c_int00()
{
	
/* USER CODE BEGIN (5) */
/* USER CODE END */

    /* Initialize Core Registers to avoid CCM Error */
    _coreInitRegisters_();

/* USER CODE BEGIN (6) */
/* USER CODE END */

    /* Initialize Stack Pointers */
    _coreInitStackPointer_();

/* USER CODE BEGIN (7) */
/* USER CODE END */


    /* Enable CPU Event Export */
    /* This allows the CPU to signal any single-bit or double-bit errors detected
     * by its ECC logic for accesses to program flash or data RAM.
     */
	_coreEnableEventBusExport_();


/* USER CODE BEGIN (11) */
/* USER CODE END */

    /* Reset handler: the following instructions read from the system exception status register
     * to identify the cause of the CPU reset.
     */

	/* check for power-on reset condition */
	if ((SYS_EXCEPTION & POWERON_RESET) != 0)
	{
/* USER CODE BEGIN (12) */
/* USER CODE END */
	    
		/* clear all reset status flags */
		SYS_EXCEPTION = 0xFFFF;

/* USER CODE BEGIN (13) */
/* USER CODE END */

/* Work Around for Errata CORTEX-R4#66:
 * 
 * Errata Description:            
 *            Register Corruption During A Load-Multiple Instruction At An Exception Vector
 * Workaround:
 *            Disable out-of-order completion for divide instructions in Auxiliary Control register */
        asm(" push {r0}");
        asm(" mrc p15, #0, r0, c1, c0, #1"); /* Read Auxiliary Control register */
  	    asm(" orr r0, r0, #0x80");           /* Set BIT 7 (Disable out-of-order completion for divide instructions.) */
   	    asm(" mcr p15, #0, r0, c1, c0, #1"); /* Write Auxiliary Control register */
        asm(" pop {r0}");
	
/* USER CODE BEGIN (14) */
/* USER CODE END */

/* Work Around for Errata CORTEX-R4#57:
 * 
 * Errata Description: 
 *            Conditional VMRS APSR_Nzcv, FPSCR May Evaluate With Incorrect Flags
 * Workaround:
 *            Disable out-of-order single-precision floating point multiply-accumulate instruction completion */
        asm(" push {r0}");
	    asm(" mrc p15, #0, r0, c15, c0, #0"); /* Read Secondary Auxiliary Control Register */
        asm(" orr r0, r0, #0x10000");         /* Set BIT 16 (Set DOOFMACS) */
        asm(" mcr p15, #0, r0, c15, c0, #0"); /* Write Secondary Auxiliary Control Register */    	
        asm(" pop {r0}");
	
/* USER CODE BEGIN (15) */
/* USER CODE END */

		/* continue with normal start-up sequence */
	}
	else if ((SYS_EXCEPTION & OSC_FAILURE_RESET) != 0)
	{
		/* Reset caused due to oscillator failure.
		Add user code here to handle oscillator failure */

/* USER CODE BEGIN (16) */
/* USER CODE END */
	}
	else if ((SYS_EXCEPTION & WATCHDOG_RESET) !=0 )
	{
		/* Reset caused due 
		 *  1) windowed watchdog violation - Add user code here to handle watchdog violation.
		 *  2) ICEPICK Reset - After loading code via CCS / System Reset through CCS
		 */
		/* Check the WatchDog Status register */
	    if(WATCHDOG_STATUS != 0U)
		{
		    /* Add user code here to handle watchdog violation. */ 
/* USER CODE BEGIN (17) */
/* USER CODE END */

		    /* Clear the Watchdog reset flag in Exception Status register */ 
		    SYS_EXCEPTION = WATCHDOG_RESET;
		
/* USER CODE BEGIN (18) */
/* USER CODE END */
		}
		else
		{
		    /* Clear the ICEPICK reset flag in Exception Status register */ 
		    SYS_EXCEPTION = ICEPICK_RESET;
/* USER CODE BEGIN (19) */
/* USER CODE END */
		}
	}
	else if ((SYS_EXCEPTION & CPU_RESET) !=0 )
	{
		/* Reset caused due to CPU reset.
		CPU reset can be caused by CPU self-test completion, or
		by toggling the "CPU RESET" bit of the CPU Reset Control Register. */

/* USER CODE BEGIN (20) */
/* USER CODE END */

		/* clear all reset status flags */
		SYS_EXCEPTION = CPU_RESET;

/* USER CODE BEGIN (21) */
/* USER CODE END */

	}
	else if ((SYS_EXCEPTION & SW_RESET) != 0)
	{
		/* Reset caused due to software reset.
		Add user code to handle software reset. */

/* USER CODE BEGIN (22) */
/* USER CODE END */
	}
	else
	{
		/* Reset caused by nRST being driven low externally.
		Add user code to handle external reset. */

/* USER CODE BEGIN (23) */
/* USER CODE END */
	}

	/* Check if there were ESM group3 errors during power-up.
	 * These could occur during eFuse auto-load or during reads from flash OTP
	 * during power-up. Device operation is not reliable and not recommended
	 * in this case.
	 * An ESM group3 error only drives the nERROR pin low. An external circuit
	 * that monitors the nERROR pin must take the appropriate action to ensure that
	 * the system is placed in a safe state, as determined by the application.
	 */
	if (esmREG->ESTATUS1[2])
	{
	/* while(1) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (24) */
/* USER CODE END */
        while(1);
/* USER CODE BEGIN (25) */
/* USER CODE END */
	}

/* USER CODE BEGIN (26) */
/* USER CODE END */

    /* Initialize System - Clock, Flash settings with Efuse self check */
	systemInit();


/* USER CODE BEGIN (29) */
/* USER CODE END */


	/* Run a diagnostic check on the memory self-test controller.
	 * This function chooses a RAM test algorithm and runs it on an on-chip ROM.
	 * The memory self-test is expected to fail. The function ensures that the PBIST controller
	 * is capable of detecting and indicating a memory self-test failure.
	 */
	pbistSelfCheck();

/* USER CODE BEGIN (31) */
/* USER CODE END */


	/* Run PBIST on CPU RAM.
	 * The PBIST controller needs to be configured separately for single-port and dual-port SRAMs.
	 * The CPU RAM is a single-port memory. The actual "RAM Group" for all on-chip SRAMs is defined in the
	 * device datasheet.
	 */
	pbistRun(0x08300020, /* ESRAM Single Port PBIST */
             PBIST_March13N_SP);

/* USER CODE BEGIN (32) */
/* USER CODE END */

	/* Wait for PBIST for CPU RAM to be completed */
	while(!pbistIsTestCompleted());

/* USER CODE BEGIN (33) */
/* USER CODE END */

	/* Check if CPU RAM passed the self-test */
	if( pbistIsTestPassed() != TRUE)
	{
		/* CPU RAM failed the self-test.
		 * Need custom handler to check the memory failure
		 * and to take the appropriate next step.
		 */
		if(pbistPortTestStatus(PBIST_PORT0) != TRUE)
		{
            memoryPort0TestFailNotification(pbistREG->RGS, pbistREG->RDS, pbistREG->FSRA0, pbistREG->FSRDL0);
		}
        else if(pbistPortTestStatus(PBIST_PORT1) != TRUE)
		{
            memoryPort1TestFailNotification(pbistREG->RGS, pbistREG->RDS, pbistREG->FSRA1, pbistREG->FSRDL1);
		}
		else
		{
		/* while(1) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (34) */
/* USER CODE END */
		   while(1);
/* USER CODE BEGIN (35) */
/* USER CODE END */
		}
	}

/* USER CODE BEGIN (36) */
/* USER CODE END */

	/* Disable PBIST clocks and disable memory self-test mode */
	pbistStop();
	

/* USER CODE BEGIN (37) */
/* USER CODE END */


	/* Initialize CPU RAM.
	 * This function uses the system module's hardware for auto-initialization of memories and their
	 * associated protection schemes. The CPU RAM is initialized by setting bit 0 of the MSIENA register.
	 * Hence the value 0x1 passed to the function.
	 * This function will initialize the entire CPU RAM and the corresponding ECC locations.
	 */
	_memoryInit_(0x1);

/* USER CODE BEGIN (38) */
/* USER CODE END */
	
	/* Enable ECC checking for TCRAM accesses.
	 * This function enables the CPU's ECC logic for accesses to B0TCM and B1TCM.
	 */
	_coreEnableRamEcc_();

/* USER CODE BEGIN (39) */
/* USER CODE END */


	/* Start PBIST on all dual-port memories */
	/* NOTE : Please Refer DEVICE DATASHEET for the list of Supported Dual port Memories.
	   PBIST test perfomed only on the user selected memories in HALCoGen's GUI SAFETY INIT tab.
	 */
	
    pbistRun(  0x00000000   
             | 0x00000000         
			 | 0x00000800    
             | 0x00000200   
             | 0x00000040
             | 0x00000080
             | 0x00000100
             | 0x00000004   
             | 0x00000008   
             | 0x00000010   
             | 0x00000400   
             | 0x00020000   
             | 0x00001000   
             | 0x00040000   
             | 0x00002000   
             | 0x00080000   
             | 0x00000000    
			 | 0x00000000    
			 | 0x00000000   
			 , PBIST_March13N_DP);

/* USER CODE BEGIN (40) */
/* USER CODE END */


	/* Test the CPU ECC mechanism for RAM accesses.
	 * The checkBxRAMECC functions cause deliberate single-bit and double-bit errors in TCRAM accesses
	 * by corrupting 1 or 2 bits in the ECC. Reading from the TCRAM location with a 2-bit error
	 * in the ECC causes a data abort exception. The data abort handler is written to look for
	 * deliberately caused exception and to return the code execution to the instruction
	 * following the one that caused the abort.
	 */
	checkB0RAMECC();
	tcram1REG->RAMCTRL &= ~(0x00000100);				/* disable writes to ECC RAM */
	tcram2REG->RAMCTRL &= ~(0x00000100);

	checkB1RAMECC();
	tcram1REG->RAMCTRL &= ~(0x00000100);				/* disable writes to ECC RAM */
	tcram2REG->RAMCTRL &= ~(0x00000100);

/* USER CODE BEGIN (41) */
/* USER CODE END */


/* USER CODE BEGIN (43) */
/* USER CODE END */

	/* Wait for PBIST for CPU RAM to be completed */
	while(!pbistIsTestCompleted());

/* USER CODE BEGIN (44) */
/* USER CODE END */

	/* Check if CPU RAM passed the self-test */
	if( pbistIsTestPassed() != TRUE)
	{

/* USER CODE BEGIN (45) */
/* USER CODE END */

        /* CPU RAM failed the self-test.
		 * Need custom handler to check the memory failure
		 * and to take the appropriate next step.
		 */
		if(pbistPortTestStatus(PBIST_PORT0) != TRUE)
		{
            memoryPort0TestFailNotification(pbistREG->RGS, pbistREG->RDS, pbistREG->FSRA0, pbistREG->FSRDL0);
		}
        else if(pbistPortTestStatus(PBIST_PORT1) != TRUE)
		{
            memoryPort1TestFailNotification(pbistREG->RGS, pbistREG->RDS, pbistREG->FSRA1, pbistREG->FSRDL1);
		}
		else
		{
		/* while(1) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (46) */
/* USER CODE END */
		   while(1);
/* USER CODE BEGIN (47) */
/* USER CODE END */
		}
	}

/* USER CODE BEGIN (48) */
/* USER CODE END */

	/* Disable PBIST clocks and disable memory self-test mode */
	pbistStop();
	


/* USER CODE BEGIN (56) */
/* USER CODE END */

	/* Release the MibSPI1 modules from local reset.
	 * This will cause the MibSPI1 RAMs to get initialized along with the parity memory.
	 */
	 mibspiREG1->GCR0 = 0x1;
	 
	/* Release the MibSPI3 modules from local reset.
	 * This will cause the MibSPI3 RAMs to get initialized along with the parity memory.
	 */
	mibspiREG3->GCR0 = 0x1;
	
	/* Release the MibSPI5 modules from local reset.
	 * This will cause the MibSPI5 RAMs to get initialized along with the parity memory.
	 */
	mibspiREG5->GCR0 = 0x1;
	
/* USER CODE BEGIN (57) */
/* USER CODE END */

    /* Initialize all on-chip SRAMs except for MibSPIx RAMs
     * The MibSPIx modules have their own auto-initialization mechanism which is triggered
     * as soon as the modules are brought out of local reset.
     */
	/* The system module auto-init will hang on the MibSPI RAM if the module is still in local reset.
	 */
	/* NOTE : Please Refer DEVICE DATASHEET for the list of Supported Memories and their channel numbers.
		      Memory Initialization is perfomed only on the user selected memories in HALCoGen's GUI SAFETY INIT tab.
	 */
	_memoryInit_(  1 << 1   
                 | 1 << 2  
                 | 1 << 5  
                 | 1 << 6  
                 | 1 << 10 
                 | 1 << 8  
                 | 1 << 14 
                 | 1 << 3  
                 | 1 << 4  
                 | 1 << 15 
                 | 1 << 16 
                 | 0 << 13);

	/* Test the parity protection mechanism for peripheral RAMs
	   NOTE : Please Refer DEVICE DATASHEET for the list of Supported Memories with parity.
	   	      Parity Self check is perfomed only on the user selected memories in HALCoGen's GUI SAFETY INIT tab.
	*/

/* USER CODE BEGIN (58) */
/* USER CODE END */
	 
	het1ParityCheck();
	
/* USER CODE BEGIN (59) */
/* USER CODE END */

	htu1ParityCheck();
	
/* USER CODE BEGIN (60) */
/* USER CODE END */

	het2ParityCheck();
	
/* USER CODE BEGIN (61) */
/* USER CODE END */

	htu2ParityCheck();
	
/* USER CODE BEGIN (62) */
/* USER CODE END */

	adc1ParityCheck();
	
/* USER CODE BEGIN (63) */
/* USER CODE END */

	adc2ParityCheck();
	
/* USER CODE BEGIN (64) */
/* USER CODE END */

	can1ParityCheck();
	
/* USER CODE BEGIN (65) */
/* USER CODE END */

	can2ParityCheck();
	
/* USER CODE BEGIN (66) */
/* USER CODE END */

	can3ParityCheck();
	
/* USER CODE BEGIN (67) */
/* USER CODE END */

	vimParityCheck();
	
/* USER CODE BEGIN (68) */
/* USER CODE END */

	dmaParityCheck();


/* USER CODE BEGIN (69) */
/* USER CODE END */

	while (mibspiREG1->BUFINIT);		/* wait for MibSPI1 RAM to complete initialization */
	while (mibspiREG3->BUFINIT);		/* wait for MibSPI3 RAM to complete initialization */ 
	while (mibspiREG5->BUFINIT);		/* wait for MibSPI5 RAM to complete initialization */

/* USER CODE BEGIN (70) */
/* USER CODE END */

	mibspi1ParityCheck();
	
/* USER CODE BEGIN (71) */
/* USER CODE END */

	mibspi3ParityCheck();
	
/* USER CODE BEGIN (72) */
/* USER CODE END */
	
	mibspi5ParityCheck();
	

/* USER CODE BEGIN (73) */
/* USER CODE END */
	
    /* Enable IRQ offset via Vic controller */
    _coreEnableIrqVicOffset_();
	

/* USER CODE BEGIN (74) */
/* USER CODE END */

	
    /* Initialize VIM table */
    {
        uint32_t i;

        for (i = 0; i < (VIM_CHANNELS + 1); i++)
        {
            vimRAM->ISR[i] = s_vim_init[i];
        }
    }

    /* set IRQ/FIQ priorities */
    vimREG->FIRQPR0 =  SYS_FIQ
                    | (SYS_FIQ <<  1U)
                    | (SYS_IRQ <<  2U)
                    | (SYS_IRQ <<  3U)
                    | (SYS_IRQ <<  4U)
                    | (SYS_IRQ <<  5U)
                    | (SYS_IRQ <<  6U)
                    | (SYS_IRQ <<  7U)
                    | (SYS_IRQ <<  8U)
                    | (SYS_IRQ <<  9U)
                    | (SYS_IRQ << 10U)
                    | (SYS_IRQ << 11U)
                    | (SYS_IRQ << 12U)
                    | (SYS_IRQ << 13U)
                    | (SYS_IRQ << 14U)
                    | (SYS_IRQ << 15U)
                    | (SYS_IRQ << 16U)
                    | (SYS_IRQ << 17U)
                    | (SYS_IRQ << 18U)
                    | (SYS_IRQ << 19U)
                    | (SYS_IRQ << 20U)
                    | (SYS_IRQ << 21U)
                    | (SYS_IRQ << 22U)
                    | (SYS_IRQ << 23U)
                    | (SYS_IRQ << 24U)
                    | (SYS_IRQ << 25U)
                    | (SYS_IRQ << 26U)
                    | (SYS_IRQ << 27U)
                    | (SYS_IRQ << 28U)
                    | (SYS_IRQ << 29U)
                    | (SYS_IRQ << 30U)
                    | (SYS_IRQ << 31U);

    vimREG->FIRQPR1 =  SYS_IRQ
                    | (SYS_IRQ <<  1U)
                    | (SYS_IRQ <<  2U)
                    | (SYS_IRQ <<  3U)
                    | (SYS_IRQ <<  4U)
                    | (SYS_IRQ <<  5U)
                    | (SYS_IRQ <<  6U)
                    | (SYS_IRQ <<  7U)
                    | (SYS_IRQ <<  8U)
                    | (SYS_IRQ <<  9U)
                    | (SYS_IRQ << 10U)
                    | (SYS_IRQ << 11U)
                    | (SYS_IRQ << 12U)
                    | (SYS_IRQ << 13U)
                    | (SYS_IRQ << 14U)
                    | (SYS_IRQ << 15U)
                    | (SYS_IRQ << 16U)
                    | (SYS_IRQ << 17U)
                    | (SYS_IRQ << 18U)
                    | (SYS_IRQ << 19U)
                    | (SYS_IRQ << 20U)
                    | (SYS_IRQ << 21U)
                    | (SYS_IRQ << 22U)
                    | (SYS_IRQ << 23U)
                    | (SYS_IRQ << 24U)
                    | (SYS_IRQ << 25U)
                    | (SYS_IRQ << 26U)
                    | (SYS_IRQ << 27U)
                    | (SYS_IRQ << 28U)
                    | (SYS_IRQ << 29U)
                    | (SYS_IRQ << 30U)
                    | (SYS_IRQ << 31U);


    vimREG->FIRQPR2 =  SYS_IRQ
                    | (SYS_IRQ << 1U)
                    | (SYS_IRQ << 2U)
                    | (SYS_IRQ << 3U)
                    | (SYS_IRQ << 4U)
                    | (SYS_IRQ << 5U)
                    | (SYS_IRQ << 6U)
                    | (SYS_IRQ << 7U)
                    | (SYS_IRQ << 8U)
                    | (SYS_IRQ << 9U)
                    | (SYS_IRQ << 10U)
                    | (SYS_IRQ << 11U)
                    | (SYS_IRQ << 12U)
                    | (SYS_IRQ << 13U)
                    | (SYS_IRQ << 14U)
                    | (SYS_IRQ << 15U)
                    | (SYS_IRQ << 16U)
                    | (SYS_IRQ << 17U)
                    | (SYS_IRQ << 18U)
                    | (SYS_IRQ << 19U)
                    | (SYS_IRQ << 20U)
                    | (SYS_IRQ << 21U)
                    | (SYS_IRQ << 22U)
                    | (SYS_IRQ << 23U)
                    | (SYS_IRQ << 24U)
                    | (SYS_IRQ << 25U)
					| (SYS_IRQ << 26U)
                    | (SYS_IRQ << 27U)
                    | (SYS_IRQ << 28U)
                    | (SYS_IRQ << 29U)
                    | (SYS_IRQ << 30U)
                    | (SYS_IRQ << 31U);

    vimREG->FIRQPR3 =  SYS_IRQ
                    | (SYS_IRQ << 1U)
                    | (SYS_IRQ << 2U)
                    | (SYS_IRQ << 3U)
                    | (SYS_IRQ << 4U)
                    | (SYS_IRQ << 5U)
                    | (SYS_IRQ << 6U)
                    | (SYS_IRQ << 7U)
                    | (SYS_IRQ << 8U)
                    | (SYS_IRQ << 9U)
                    | (SYS_IRQ << 10U)
                    | (SYS_IRQ << 11U)
                    | (SYS_IRQ << 12U)
                    | (SYS_IRQ << 13U)
                    | (SYS_IRQ << 14U)
                    | (SYS_IRQ << 15U)
                    | (SYS_IRQ << 16U)
                    | (SYS_IRQ << 17U)
                    | (SYS_IRQ << 18U)
                    | (SYS_IRQ << 19U)
                    | (SYS_IRQ << 20U)
                    | (SYS_IRQ << 21U)
                    | (SYS_IRQ << 22U)
                    | (SYS_IRQ << 23U)
                    | (SYS_IRQ << 24U)
                    | (SYS_IRQ << 25U)
					| (SYS_IRQ << 26U)
                    | (SYS_IRQ << 27U)
                    | (SYS_IRQ << 28U)
                    | (SYS_IRQ << 29U)
                    | (SYS_IRQ << 30U)
                    | (SYS_IRQ << 31U);

					
    /* enable interrupts */
    vimREG->REQMASKSET0 = 1U
                        | (1U << 1U)
                        | (0U << 2U)
                        | (0U << 3U)
                        | (0U << 4U)
                        | (0U << 5U)
                        | (0U << 6U)
                        | (0U << 7U)
                        | (0U << 8U)
                        | (0U << 9U)
                        | (0U << 10U)
                        | (0U << 11U)
                        | (0U << 12U)
                        | (0U << 13U)
                        | (0U << 14U)
                        | (0U << 15U)
                        | (0U << 16U)
                        | (0U << 17U)
                        | (0U << 18U)
                        | (0U << 19U)
                        | (0U << 20U)
                        | (0U << 21U)
                        | (0U << 22U)
                        | (0U << 23U)
                        | (0U << 24U)
                        | (0U << 25U)
                        | (0U << 26U)
                        | (0U << 27U)
                        | (0U << 28U)
                        | (0U << 29U)
                        | (0U << 30U)
                        | (0U << 31U);

    vimREG->REQMASKSET1 = 0U
                        | (0U << 1U)
                        | (0U << 2U)
                        | (0U << 3U)
                        | (0U << 4U)
                        | (0U << 5U)
                        | (0U << 6U)
                        | (0U << 7U)
                        | (0U << 8U)
                        | (0U << 9U)
                        | (0U << 10U)
                        | (0U << 11U)
                        | (0U << 12U)
                        | (0U << 13U)
                        | (0U << 14U)
                        | (0U << 15U)
                        | (0U << 16U)
                        | (0U << 17U)
                        | (0U << 18U)
                        | (0U << 19U)
                        | (0U << 20U)
                        | (0U << 21U)
                        | (0U << 22U)
                        | (0U << 23U)
                        | (0U << 24U)
                        | (0U << 25U)
                        | (0U << 26U)
                        | (0U << 27U)
                        | (0U << 28U)
                        | (0U << 29U)
                        | (0U << 30U)
                        | (0U << 31U);

    vimREG->REQMASKSET2 = 0U
                        | (0U << 1U)
                        | (0U << 2U)
                        | (0U << 3U)
                        | (0U << 4U)
                        | (0U << 5U)
                        | (0U << 6U)
                        | (0U << 7U)
                        | (0U << 8U)
                        | (0U << 9U)
                        | (0U << 10U)
                        | (0U << 11U)
                        | (0U << 12U)
                        | (0U << 13U)
                        | (0U << 14U)
                        | (0U << 15U)
                        | (0U << 16U)
                        | (0U << 17U)
                        | (0U << 18U)
                        | (0U << 19U)
                        | (0U << 20U)
                        | (0U << 21U)
                        | (0U << 22U)
                        | (0U << 23U)
                        | (0U << 24U)
                        | (0U << 25U)
					    | (0U << 26U)
                        | (0U << 27U)
                        | (0U << 28U)
                        | (0U << 29U)
                        | (0U << 30U)
                        | (0U << 31U);
						
    vimREG->REQMASKSET3 =  0U
                        | (0U << 1U)
                        | (0U << 2U)
                        | (0U << 3U)
                        | (0U << 4U)
                        | (0U << 5U)
                        | (0U << 6U)
                        | (0U << 7U)
                        | (0U << 8U)
                        | (0U << 9U)
                        | (0U << 10U)
                        | (0U << 11U)
                        | (0U << 12U)
                        | (0U << 13U)
                        | (0U << 14U)
                        | (0U << 15U)
                        | (0U << 16U)
                        | (0U << 17U)
                        | (0U << 18U)
                        | (0U << 19U)
                        | (0U << 20U)
                        | (0U << 21U)
                        | (0U << 22U)
                        | (0U << 23U)
                        | (0U << 24U)
                        | (0U << 25U)
						| (0U << 26U)
                        | (0U << 27U)
                        | (0U << 28U)
                        | (0U << 29U)
                        | (0U << 30U)
                        | (0U << 31U);	

/* USER CODE BEGIN (75) */
/* USER CODE END */

	/* Configure system response to error conditions signaled to the ESM group1 */
	/* This function can be configured from the ESM tab of HALCoGen */
	esmInit();

    /* initialize copy table */
    if ((uint32_t *)&__binit__ != (uint32_t *)0xFFFFFFFFU)
    {
        extern void copy_in(void *binit);
        copy_in((void *)&__binit__);
    }

    /* initialize the C global variables */
    if (&__TI_Handler_Table_Base < &__TI_Handler_Table_Limit)
    {
        uint8_t **tablePtr   = (uint8_t **)&__TI_CINIT_Base;
        uint8_t **tableLimit = (uint8_t **)&__TI_CINIT_Limit;

        while (tablePtr < tableLimit)
        {
            uint8_t *loadAdr = *tablePtr++;
            uint8_t *runAdr  = *tablePtr++;
            uint8_t  idx     = *loadAdr++;
            handler_fptr   handler = (handler_fptr)(&__TI_Handler_Table_Base)[idx];

            (*handler)((const uint8_t *)loadAdr, runAdr);
        }
    }

    /* initialize constructors */
    if (__TI_PINIT_Base < __TI_PINIT_Limit)
    {
        void (**p0)() = (void *)__TI_PINIT_Base;

        while ((uint32_t)p0 < __TI_PINIT_Limit)
        {
            void (*p)() = *p0++;
            p();
        }
    }

/* USER CODE BEGIN (76) */
/* USER CODE END */
	
    /* call the application */
    main();

/* USER CODE BEGIN (77) */
/* USER CODE END */

    exit();
/* USER CODE BEGIN (78) */
/* USER CODE END */
}

/* USER CODE BEGIN (79) */
/* USER CODE END */
