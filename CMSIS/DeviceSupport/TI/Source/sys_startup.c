/** @file sys_startup.c 
*   @brief Startup Source File
*   @date 15.December.2011
*   @version 03.00.00
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
#include "sys_memory.h"

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
    t_isrFuncPTR ISR[VIM_CHANNELS];
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
};


/* Startup Routine */

/* USER CODE BEGIN (4) */
/* USER CODE END */

#pragma INTERRUPT(_c_int00, RESET)

void _c_int00()
{
	register uint32_t temp;
	
/* USER CODE BEGIN (5) */
/* USER CODE END */

    /* Enable VFP Unit */
    _coreEnableVfp_();

    /* Initialize Core Registers */
    _coreInitRegisters_();

/* USER CODE BEGIN (6) */
/* USER CODE END */
	
	/* read the system exception status register */
	temp = systemREG1->SYSESR;

/* USER CODE BEGIN (7) */
/* USER CODE END */

	/* check for power-on reset condition */
	if (temp & 0x8000)
	{
		/* clear all reset status flags */
		systemREG1->SYSESR = 0xFFFF;

/* USER CODE BEGIN (8) */
/* USER CODE END */

		/* continue with normal start-up sequence */
	}
	else if (temp & 0x4000)
	{
		/* Reset caused due to oscillator failure.
		Add user code here to handle oscillator failure */

/* USER CODE BEGIN (9) */
/* USER CODE END */
	}
	else if (temp & 0x2000)
	{
		/* Reset caused due to windowed watchdog violation.
		Add user code here to handle watchdog violation */

/* USER CODE BEGIN (10) */
/* USER CODE END */
	}
	else if (temp & 0x20)
	{
		/* Reset caused due to CPU reset.
		CPU reset can be caused by CPU self-test completion, or
		by toggling the "CPU RESET" bit of the CPU Reset Control Register.
		Add user code to handle CPU reset:
		check for selftest completion without any error and continue start-up. */

/* USER CODE BEGIN (11) */
/* USER CODE END */
	}
	else if (temp & 0x10)
	{
		/* Reset caused due to software reset.
		Add user code to handle software reset. */

/* USER CODE BEGIN (12) */
/* USER CODE END */
	}
	else
	{
		/* Reset caused by nRST being driven low externally.
		Add user code to handle external reset. */

/* USER CODE BEGIN (13) */
/* USER CODE END */
	}
	
    /* Initialize Stack Pointers */
    _coreInitStackPointer_();
	
    /* Enable IRQ offset via Vic controller */
    _coreEnableIrqVicOffset_();
	
    /* Initialize System */
    systemInit();
	
    /* Initialize memory */
//    _memoryInit_();

	/* Enable CPU Event Export */
    /* This allows the CPU to signal any single-bit or double-bit errors detected
     * by its ECC logic for accesses to program flash or data RAM.
     */

//    _coreEnableEventBusExport_();

    /* Enable ECC checking for TCRAM accesses.
	 * This function enables the CPU's ECC logic for accesses to B0TCM and B1TCM.
	 */
//	_coreEnableRamEcc_();




    /* Initialize VIM table */
    {
        uint32_t i;

        for (i = 0; i < 90U; i++)
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
                    | (SYS_IRQ << 25U);


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
                        | (0U << 25U);



    /* initalise copy table */
    if ((uint32_t *)&__binit__ != (uint32_t *)0xFFFFFFFFU)
    {
        extern void copy_in(void *binit);
        copy_in((void *)&__binit__);
    }

    /* initalise the C global variables */
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

    /* initalise contructors */
    if (__TI_PINIT_Base < __TI_PINIT_Limit)
    {
        void (**p0)() = (void *)__TI_PINIT_Base;

        while ((uint32_t)p0 < __TI_PINIT_Limit)
        {
            void (*p)() = *p0++;
            p();
        }
    }

/* USER CODE BEGIN (14) */
/* USER CODE END */

    /* configure muxed pins */
    muxInit();

    /* call the application */
    main();
    exit();
}


/* USER CODE BEGIN (15) */
void esmGroup1Notification(uint32_t x)
{

}

void esmGroup2Notification(uint32_t x)
{

}

/* USER CODE END */
