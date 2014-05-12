/** @file rti.c 
*   @brief RTI Driver Source File
*   @date 15.Aug.2012
*   @version 03.02.00
*
*   This file contains:
*   - API Functions
*   - Interrupt Handlers
*   .
*   which are relevant for the RTI driver.
*/

/* (c) Texas Instruments 2009-2011, All rights reserved. */


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "rti.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */


/** @fn void rtiInit(void)
*   @brief Initializes RTI Driver
*
*   This function initializes the RTI driver.
*
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void rtiInit(void)
{
/* USER CODE BEGIN (3) */
/* USER CODE END */
    /** @b Initialize @b RTI1: */

    /** - Setup NTU source, debug options and disable both counter blocks */
    rtiREG1->GCTRL = (1U << 16U) | 0x00000000U;

    /** - Setup timebase for free running counter 0 */
    rtiREG1->TBCTRL = 0x00000000U;

    /** - Enable/Disable capture event sources for both counter blocks */
    rtiREG1->CAPCTRL = 0U | 0U;

    /** - Setup input source compare 0-3 */
    rtiREG1->COMPCTRL = 0x00001000U | 0x00000100U | 0x00000000U | 0x00000000U;

    /** - Reset up counter 0 */
    rtiREG1->CNT[0U].UCx = 0x00000000U;

    /** - Reset free running counter 0 */
    rtiREG1->CNT[0U].FRCx = 0x00000000U;

    /** - Setup up counter 0 compare value 
    *     - 0x00000000: Divide by 2^32
    *     - 0x00000001-0xFFFFFFFF: Divide by (CPUC0 + 1)
    */
    rtiREG1->CNT[0U].CPUCx = 7U;

    /** - Reset up counter 1 */
    rtiREG1->CNT[1U].UCx = 0x00000000U;

    /** - Reset free running counter 1 */
    rtiREG1->CNT[1U].FRCx  = 0x00000000U;

    /** - Setup up counter 1 compare value 
    *     - 0x00000000: Divide by 2^32
    *     - 0x00000001-0xFFFFFFFF: Divide by (CPUC1 + 1)
    */
    rtiREG1->CNT[1U].CPUCx = 7U;

    /** - Setup compare 0 value. This value is compared with selected free running counter. */
    rtiREG1->CMP[0U].COMPx = 10000U;

    /** - Setup update compare 0 value. This value is added to the compare 0 value on each compare match. */
    rtiREG1->CMP[0U].UDCPx = 10000U;

    /** - Setup compare 1 value. This value is compared with selected free running counter. */
    rtiREG1->CMP[1U].COMPx = 50000U;

    /** - Setup update compare 1 value. This value is added to the compare 1 value on each compare match. */
    rtiREG1->CMP[1U].UDCPx = 50000U;

    /** - Setup compare 2 value. This value is compared with selected free running counter. */
    rtiREG1->CMP[2U].COMPx = 80000U;

    /** - Setup update compare 2 value. This value is added to the compare 2 value on each compare match. */
    rtiREG1->CMP[2U].UDCPx = 80000U;

    /** - Setup compare 3 value. This value is compared with selected free running counter. */
    rtiREG1->CMP[3U].COMPx = 100000U;

    /** - Setup update compare 3 value. This value is added to the compare 3 value on each compare match. */
    rtiREG1->CMP[3U].UDCPx = 100000U;

    /** - Clear all pending interrupts */
    rtiREG1->INTFLAG = 0x0007000FU;

    /** - Disable all interrupts */
    rtiREG1->CLEARINT = 0x00070F0FU;

    /**   @note This function has to be called before the driver can be used.\n
    *           This function has to be executed in privileged mode.\n
    *           This function does not start the counters.
    */

/* USER CODE BEGIN (4) */
/* USER CODE END */
}

/* USER CODE BEGIN (5) */
/* USER CODE END */


/** @fn void rtiStartCounter(uint32_t counter)
*   @brief Starts RTI Counter block
*   @param[in] counter Select counter block to be started:
*              - rtiCOUNTER_BLOCK0: RTI counter block 0 will be started
*              - rtiCOUNTER_BLOCK1: RTI counter block 1 will be started
*
*   This function starts selected counter block of the selected RTI module.
*/

/* USER CODE BEGIN (6) */
/* USER CODE END */

void rtiStartCounter(uint32_t counter)
{
/* USER CODE BEGIN (7) */
/* USER CODE END */

    rtiREG1->GCTRL |= (1U << (counter & 3U));

    /**   @note The function rtiInit has to be called before this function can be used.\n
    *           This function has to be executed in privileged mode.
    */

/* USER CODE BEGIN (8) */
/* USER CODE END */
}

/* USER CODE BEGIN (9) */
/* USER CODE END */


/** @fn void rtiStopCounter(uint32_t counter)
*   @brief Stops RTI Counter block
*   @param[in] counter Select counter to be stopped:
*              - rtiCOUNTER_BLOCK0: RTI counter block 0 will be stopped
*              - rtiCOUNTER_BLOCK1: RTI counter block 1 will be stopped
*
*   This function stops selected counter block of the selected RTI module.
*/

/* USER CODE BEGIN (10) */
/* USER CODE END */

void rtiStopCounter(uint32_t counter)
{
/* USER CODE BEGIN (11) */
/* USER CODE END */

    rtiREG1->GCTRL &= ~(1U << (counter & 3U));

    /**   @note The function rtiInit has to be called before this function can be used.\n
    *           This function has to be executed in privileged mode.
    */

/* USER CODE BEGIN (12) */
/* USER CODE END */
}

/* USER CODE BEGIN (13) */
/* USER CODE END */


/** @fn uint32_t rtiResetCounter(uint32_t counter)
*   @brief Reset RTI Counter block
*   @param[in] counter Select counter block to be reset:
*              - rtiCOUNTER_BLOCK0: RTI counter block 0 will be reset
*              - rtiCOUNTER_BLOCK1: RTI counter block 1 will be reset
*   @return The function will return:
*           - 0: When the counter reset wasn't successful   
*           - 1: When the counter reset was successful   
*
*   This function resets selected counter block of the selected RTI module.
*/

/* USER CODE BEGIN (14) */
/* USER CODE END */

uint32_t rtiResetCounter(uint32_t counter)
{
    uint32_t success = 0U;

/* USER CODE BEGIN (15) */
/* USER CODE END */

    if (!(rtiREG1->GCTRL & (1U << (counter & 3U))))
    {
        rtiREG1->CNT[counter].UCx = 0x00000000U;
        rtiREG1->CNT[counter].FRCx = 0x00000000U;

        success = 1U;
    }

    /**   @note The function rtiInit has to be called before this function can be used.\n
    *           This function has to be executed in privileged mode.\n
    *           The selected counter block has to be stopped before it can reset.
    */

/* USER CODE BEGIN (16) */
/* USER CODE END */

    return success;
}

/* USER CODE BEGIN (17) */
/* USER CODE END */


/** @fn void rtiSetPeriod(uint32_t compare, uint32_t period)
*   @brief Set new period of RTI compare
*   @param[in] compare Select compare to change period:
*              - rtiCOMPARE0: RTI compare 0 will change the period
*              - rtiCOMPARE1: RTI compare 1 will change the period
*              - rtiCOMPARE2: RTI compare 2 will change the period
*              - rtiCOMPARE3: RTI compare 3 will change the period
*   @param[in] period new period in [ticks - 1]:
*              - 0x00000000: Divide by 1
*              - n: Divide by n + 1
*
*   This function will change the period of the selected compare.
*/

/* USER CODE BEGIN (18) */
/* USER CODE END */

void rtiSetPeriod(uint32_t compare, uint32_t period)
{
/* USER CODE BEGIN (19) */
/* USER CODE END */

    rtiREG1->CMP[compare].UDCPx = period;

    /**   @note The function rtiInit has to be called before this function can be used.\n
    *           This function has to be executed in privileged mode.\n
    *           When the corresponding counter block is not stopped,\n
    *           the period will change on the next compare match of the old period.
    */

/* USER CODE BEGIN (20) */
/* USER CODE END */
}

/* USER CODE BEGIN (21) */
/* USER CODE END */


/** @fn uint32_t rtiGetPeriod(uint32_t compare)
*   @brief Get current period of RTI compare
*   @param[in] compare Select compare to return the current period:
*              - rtiCOMPARE0: RTI compare 0 will return the current period
*              - rtiCOMPARE1: RTI compare 1 will return the current period
*              - rtiCOMPARE2: RTI compare 2 will return the current period
*              - rtiCOMPARE3: RTI compare 3 will return the current period
*   @return Current period of selected compare in [ticks - 1]:
*           - 0x00000000: Divide by 1
*           - n: Divide by n + 1
*
*   This function will change the period of the selected compare.
*/

/* USER CODE BEGIN (22) */
/* USER CODE END */

uint32_t rtiGetPeriod(uint32_t compare)
{
    uint32_t period;

/* USER CODE BEGIN (23) */
/* USER CODE END */

    period = rtiREG1->CMP[compare].UDCPx;

    /**   @note The function rtiInit has to be called before this function can be used.
    */

/* USER CODE BEGIN (24) */
/* USER CODE END */

    return period;
}

/* USER CODE BEGIN (25) */
/* USER CODE END */


/** @fn uint32_t rtiGetCurrentTick(uint32_t compare)
*   @brief Get current tick of RTI compare
*   @param[in] compare Select compare to return the current tick:
*              - rtiCOMPARE0: RTI compare 0 will return the current period
*              - rtiCOMPARE1: RTI compare 1 will return the current period
*              - rtiCOMPARE2: RTI compare 2 will return the current period
*              - rtiCOMPARE3: RTI compare 3 will return the current period
*   @return Current tick of selected compare
*
*   This function will change the period of the selected compare.
*/

/* USER CODE BEGIN (26) */
/* USER CODE END */

uint32_t rtiGetCurrentTick(uint32_t compare)
{
    uint32_t tick;
    uint32_t counter = (rtiREG1->COMPCTRL & (1U << (compare << 2U))) ? 1U : 0U;

/* USER CODE BEGIN (27) */
/* USER CODE END */

    tick = rtiREG1->CNT[counter].FRCx - (rtiREG1->CMP[compare].COMPx - rtiREG1->CMP[compare].UDCPx);

    /**   @note The function rtiInit has to be called before this function can be used.
    */

/* USER CODE BEGIN (28) */
/* USER CODE END */

    return tick;
}

/* USER CODE BEGIN (29) */
/* USER CODE END */

/** @fn void dwdInit(uint16_t dwdPreload)
*   @brief Initialize DWD Expiration Period 
*   @param[in] DWD Preload value for expiration time.
*              - Texp = (dwdPreload +1) / RTICLK
*              - n: Divide by n + 1
*
*   This function can be called to set the DWD expiration
*   
*/
void dwdInit(uint16_t dwdPreload)
{
/* USER CODE BEGIN (30) */
/* USER CODE END */

    /* Clear the violations if already present */
	rtiREG1->WDSTATUS = 0xFF;
	
	rtiREG1->DWDPRLD = dwdPreload;
	
/* USER CODE BEGIN (31) */
/* USER CODE END */
}

/* USER CODE BEGIN (32) */
/* USER CODE END */

/** @fn void dwdInit(uint16_t dwdPreload)
*   @brief Initialize DWD Expiration Period 
*   @param[in] DWWD reaction if the watchdog is serviced outside the time window.
*              - Generate_Reset  
*              - Generate_NMI
*   @param[in] DWWD Preload value for the watchdog expiration time.
*              - Texp = (dwdPreload +1) / RTICLK
*              - n: Divide by n + 1
*   @param[in] DWWD Preload value for expiration time.
*              - Texp = (dwdPreload +1) / RTICLK
*              - n: Divide by n + 1
*
*   This function can be called to set the DWD expiration
*   
*/
void dwwdInit(dwwdReaction Reaction, uint16_t dwdPreload, dwwdWindowSize Window_Size)
{
/* USER CODE BEGIN (33) */
/* USER CODE END */

    /* Clear the violations if already present */
	rtiREG1->WDSTATUS = 0xFF;

    rtiREG1->WWDSIZECTRL = (uint32_t) Window_Size;
	rtiREG1->DWDPRLD     = (uint32_t) dwdPreload;
	rtiREG1->WWDRXNCTRL  = (uint32_t) Reaction;

/* USER CODE BEGIN (34) */
/* USER CODE END */
}

/* USER CODE BEGIN (35) */
/* USER CODE END */

/** @fn uint32_t dwwdGetCurrentDownCounter()
*   @brief Get the current DWWD Down Counter 
*   @return Current tick of selected compare
*
*   This function will get the current DWWD down counter value.
*   
*/
uint32_t dwwdGetCurrentDownCounter()
{
/* USER CODE BEGIN (36) */
/* USER CODE END */

    return (rtiREG1->DWDCNTR);

/* USER CODE BEGIN (37) */
/* USER CODE END */
}

/* USER CODE BEGIN (38) */
/* USER CODE END */

/** @fn void dwdCounterEnable()
*   @brief Enable DWD
*
*   This function will Enable the DWD counter.
*   
*/
void dwdCounterEnable()
{
/* USER CODE BEGIN (39) */
/* USER CODE END */

	rtiREG1->DWDCTRL = 0xA98559DAU;
	
/* USER CODE BEGIN (40) */
/* USER CODE END */
}

/* USER CODE BEGIN (41) */
/* USER CODE END */

/** @fn void dwdCounterDisable()
*   @brief Disable DWD
*
*   This function will Disable the DWD counter.
*   
*/
void dwdCounterDisable()
{
/* USER CODE BEGIN (42) */
/* USER CODE END */
	rtiREG1->DWDCTRL = 0x5312ACEDU;
/* USER CODE BEGIN (43) */
/* USER CODE END */
}

/* USER CODE BEGIN (44) */
/* USER CODE END */

/** @fn void dwdSetPreload(uint16_t dwdPreload)
*   @brief Initialize DWD Expiration Period 
*   @param[in] DWD Preload value for the watchdog expiration time.
*              - Texp = (dwdPreload +1) / RTICLK
*              - n: Divide by n + 1
*
*   This function can be called to set the Preload value for the watchdog expiration time.
*   
*/
void dwdSetPreload(uint16_t dwdPreload)
{
/* USER CODE BEGIN (45) */
/* USER CODE END */
	rtiREG1->DWDPRLD = dwdPreload;
/* USER CODE BEGIN (46) */
/* USER CODE END */
}

/* USER CODE BEGIN (47) */
/* USER CODE END */

/** @fn void dwdReset()
*   @brief Reset Digital Watchdog 
*
*   This function can be called to reset Digital Watchdog.
*   
*/
void dwdReset()
{
/* USER CODE BEGIN (48) */
/* USER CODE END */
	rtiREG1->WDKEY = 0x0000E51AU;
	rtiREG1->WDKEY = 0x0000A35CU;
/* USER CODE BEGIN (49) */
/* USER CODE END */
}

/** @fn void dwdGenerateSysReset()
*   @brief Generate System Reset through DWD
*
*   This function can be called to generate system reset using DWD.
*   
*/
void dwdGenerateSysReset()
{
/* USER CODE BEGIN (50) */
/* USER CODE END */
	rtiREG1->WDKEY = 0x0000E51AU;
	rtiREG1->WDKEY = 0x00002345U;
/* USER CODE BEGIN (51) */
/* USER CODE END */
}

/* USER CODE BEGIN (52) */
/* USER CODE END */

/** @fn boolean_t IsdwdKeySequenceCorrect()
*   @brief Check if DWD Key sequence correct.
*   @return The function will return:
*           - TRUE: When the DWD key sequence is written correctly.
*           - FALSE: When the DWD key sequence is written incorrectly / not written.
*
*   This function will get status of the DWD Key sequence.
*   
*/
boolean_t IsdwdKeySequenceCorrect()
{
	boolean_t Status;

/* USER CODE BEGIN (53) */
/* USER CODE END */

	if((rtiREG1->WDSTATUS & 0x4) == 0x4)
	{
		Status = FALSE;
	}
	else
	{
		Status = TRUE;
	}

/* USER CODE BEGIN (54) */
/* USER CODE END */

	return Status;
}

/* USER CODE BEGIN (55) */
/* USER CODE END */

/** @fn dwdResetStatus dwdGetStatus()
*   @brief Check if Reset is generated due to DWD.
*   @return The function will return:
*           - Reset_Generated: When the Reset is generated due to DWD.
*           - No_Reset_Generated: No Reset is generated due to DWD.
*
*   This function will get dwd Reset status.
*   
*/
dwdResetStatus dwdGetStatus()
{
/* USER CODE BEGIN (56) */
/* USER CODE END */
	dwdResetStatus Reset_Status;
	if((rtiREG1->WDSTATUS & 0x2) == 0x2)
	{
		Reset_Status = Reset_Generated;
	}
	else
	{
		Reset_Status = No_Reset_Generated;
	}

/* USER CODE BEGIN (57) */
/* USER CODE END */
	return Reset_Status;
}

/* USER CODE BEGIN (58) */
/* USER CODE END */

/** @fn void dwdClearFlag()
*   @brief Clear the DWD violation flag.
*
*   This function will get dwd Reset status.
*   
*/
void dwdClearFlag()
{
/* USER CODE BEGIN (59) */
/* USER CODE END */

	rtiREG1->WDSTATUS = 0xFF;

/* USER CODE BEGIN (60) */
/* USER CODE END */
}

/* USER CODE BEGIN (61) */
/* USER CODE END */

/** @fn dwdViolation dwdGetViolationStatus()
*   @brief Check the status of the DWD or DWWD violation happened.
*   @return The function will return one of following violations occured:
*           - NoTime_Violation
*           - Key_Seq_Violation
*           - Time_Window_Violation
*           - EndTime_Window_Violation
*           - StartTime_Window_Violation
*
*   This function will get status of the DWD or DWWD violation status.
*   
*/
dwdViolation dwdGetViolationStatus()
{
/* USER CODE BEGIN (62) */
/* USER CODE END */
	dwdViolation Violation_Status;

	if ((rtiREG1->WDSTATUS & 0x20) == 0x20)
	{
		Violation_Status = Time_Window_Violation;
	}
	else if ((rtiREG1->WDSTATUS & 0x04) == 0x04)
	{
		Violation_Status = Key_Seq_Violation;
	}	
	else if((rtiREG1->WDSTATUS & 0x8) == 0x8)
	{
		Violation_Status = StartTime_Window_Violation;
	}
	else if ((rtiREG1->WDSTATUS & 0x10) == 0x10)
	{
		Violation_Status = EndTime_Window_Violation;
	}
	else
	{
		Violation_Status = NoTime_Violation;
	}
	
/* USER CODE BEGIN (63) */
/* USER CODE END */

	return Violation_Status;
}

/* USER CODE BEGIN (64) */
/* USER CODE END */

/** @fn void rtiEnableNotification(uint32_t notification)
*   @brief Enable notification of RTI module
*   @param[in] notification Select notification of RTI module:
*              - rtiNOTIFICATION_COMPARE0: RTI compare 0 notification
*              - rtiNOTIFICATION_COMPARE1: RTI compare 1 notification
*              - rtiNOTIFICATION_COMPARE2: RTI compare 2 notification
*              - rtiNOTIFICATION_COMPARE3: RTI compare 3 notification
*              - rtiNOTIFICATION_TIMEBASE: RTI Timebase notification
*              - rtiNOTIFICATION_COUNTER0: RTI counter 0 overflow notification
*              - rtiNOTIFICATION_COUNTER1: RTI counter 1 overflow notification
*
*   This function will enable the selected notification of a RTI module.
*   It is possible to enable multiple notifications masked.
*/

/* USER CODE BEGIN (65) */
/* USER CODE END */

void rtiEnableNotification(uint32_t notification)
{
/* USER CODE BEGIN (66) */
/* USER CODE END */

    rtiREG1->INTFLAG &= ~notification;
    rtiREG1->SETINT   = notification;

    /**   @note The function rtiInit has to be called before this function can be used.\n
    *           This function has to be executed in privileged mode.
    */

/* USER CODE BEGIN (67) */
/* USER CODE END */
}

/* USER CODE BEGIN (68) */
/* USER CODE END */

/** @fn void rtiDisableNotification(uint32_t notification)
*   @brief Disable notification of RTI module
*   @param[in] notification Select notification of RTI module:
*              - rtiNOTIFICATION_COMPARE0: RTI compare 0 notification
*              - rtiNOTIFICATION_COMPARE1: RTI compare 1 notification
*              - rtiNOTIFICATION_COMPARE2: RTI compare 2 notification
*              - rtiNOTIFICATION_COMPARE3: RTI compare 3 notification
*              - rtiNOTIFICATION_TIMEBASE: RTI Timebase notification
*              - rtiNOTIFICATION_COUNTER0: RTI counter 0 overflow notification
*              - rtiNOTIFICATION_COUNTER1: RTI counter 1 overflow notification
*
*   This function will disable the selected notification of a RTI module.
*   It is possible to disable multiple notifications masked.
*/

/* USER CODE BEGIN (69) */
/* USER CODE END */

void rtiDisableNotification(uint32_t notification)
{
/* USER CODE BEGIN (70) */
/* USER CODE END */

    rtiREG1->CLEARINT = notification;

    /**   @note The function rtiInit has to be called before this function can be used.\n
    *           This function has to be executed in privileged mode.
    */

/* USER CODE BEGIN (71) */
/* USER CODE END */
}

/* USER CODE BEGIN (72) */
/* USER CODE END */







