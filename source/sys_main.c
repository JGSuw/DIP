/** @file sys_main.c 
*   @brief Application main file
*   @date 25.April.2014
*   @version 03.09.00
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */
#include "sys_common.h"
#include "system.h"
#include "eqep.h"
#include "sys_core.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */
	/* INITIALIZE EQEP MODULES */
	QEPInit();

	/* Enable Position Counter */
    eqepEnableCounter(eqepREG1);
    eqepEnableCounter(eqepREG2);

    /* Enable Unit Timer. */
    eqepEnableUnitTimer(eqepREG1);
    eqepEnableUnitTimer(eqepREG2);

    /* Enable capture timer and capture period latch. */
    eqepEnableCapture(eqepREG1);
    eqepEnableCapture(eqepREG2);

    /* Set software initialization of counter */
	eqepSetSoftInit  (eqepREG1,QEPCTL_Swi_Auto_Init_Counter);
	eqepSetSoftInit  (eqepREG2,QEPCTL_Swi_Auto_Init_Counter);

	/*infinity loop*/
	while(1)
	{
		/* Status flag is set to indicate that a new value is latched in the QCPRD register. */
		 if((eqepREG1->QEPSTS & 0x80U) !=0U)
		 {
			 /*Read position counter*/
			 uint32 count1 = eqepReadPosnCount(eqepREG1);
			 /* Clear the Status flag. */
			 eqepREG1->QEPSTS |= 0x80U;
		 }
		 if((eqepREG2->QEPSTS & 0x80U) !=0U)
		 {
			 /*Read position counter*/
			 uint32 count2 = eqepReadPosnCount(eqepREG2);
		 	/* Clear the Status flag. */
		 	eqepREG2->QEPSTS |= 0x80U;
		 }
	}
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */
