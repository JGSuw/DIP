/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *                 TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *                 Property of Texas Instruments, Unauthorized reproduction and/or distribution
 *                 is strictly prohibited.  This product  is  protected  under  copyright  law
 *                 and  trade  secret law as an  unpublished work.
 *                 (C) Copyright Texas Instruments - 2012.  All rights reserved.
 *
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ti_fee_types.h
 *      Project:  Tms570_TIFEEDriver
 *       Module:  TIFEEDriver
 *    Generator:  None
 *
 *  Description:  This file implements the TI FEE Api.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  Vishwanath Reddy
 *---------------------------------------------------------------------------------------------------------------------
 * Revision History
 *---------------------------------------------------------------------------------------------------------------------
 * Version        Date         Author               Change ID        Description
 *---------------------------------------------------------------------------------------------------------------------
 * 03.00.00       31Aug2012    Vishwanath Reddy     0000000000000    Initial Version
 * 00.01.00       31Aug2012    Vishwanath Reddy     0000000000000    Initial Version
 * 00.01.02       30Nov2012    Vishwanath Reddy     SDOCM00097786    Misra Fixes, Memory segmentation changes.
 * 01.12.00		  13Dec2013    Vishwanath Reddy     SDOCM00105412    MISRA C fixes.
 *********************************************************************************************************************/


#ifndef TI_FEE_TYPES_H
#define TI_FEE_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Device_Header.h" 

#ifndef TI_Fee_None
#define TI_Fee_None 0x00U	/*Take no action on single bit errors, (respond with corrected data), */
							/*return error for uncorrectable error reads (multibit errors for ECC or parity failures)*/
							/*For devices with no ECC (they may have parity or not) the only valid option is none. */
#endif

#ifndef TI_Fee_Fix
#define TI_Fee_Fix 0x01U	/* single bit error will be fixed by reprogramming */
							/* return previous valid data for uncorrectable error reads (multi bit errors for ECC 
							   or parity failures). */
#endif

/*SAFETYMCUSW 74 S MR:18.4 <APPROVED> "Reason - union declaration is necessary here."*/
typedef	union 
{	
	uint16 Fee_u16StatusWord;
	struct
	{		
		/*SAFETYMCUSW 42 S MR:3.5 <APPROVED> "Reason - Bit field declaration is necessary here."*/
		/*SAFETYMCUSW 73 S MR:6.4 <APPROVED> "Reason - Bit field is declared as unsigned."*/
		uint16 Reserved: 5U;	
		/*SAFETYMCUSW 42 S MR:3.5 <APPROVED> "Reason - Bit field declaration is necessary here."*/
		/*SAFETYMCUSW 73 S MR:6.4 <APPROVED> "Reason - Bit field is declared as unsigned."*/
		uint16 Erase:1U;
		/*SAFETYMCUSW 42 S MR:3.5 <APPROVED> "Reason - Bit field declaration is necessary here."*/
		/*SAFETYMCUSW 73 S MR:6.4 <APPROVED> "Reason - Bit field is declared as unsigned."*/
		uint16 ReadSync:1U;
		/*SAFETYMCUSW 42 S MR:3.5 <APPROVED> "Reason - Bit field declaration is necessary here."*/
		/*SAFETYMCUSW 73 S MR:6.4 <APPROVED> "Reason - Bit field is declared as unsigned."*/
		uint16 ProgramFailed:1U;		
		/*SAFETYMCUSW 42 S MR:3.5 <APPROVED> "Reason - Bit field declaration is necessary here."*/
		/*SAFETYMCUSW 73 S MR:6.4 <APPROVED> "Reason - Bit field is declared as unsigned."*/
		uint16 Read:1U;		
		/*SAFETYMCUSW 42 S MR:3.5 <APPROVED> "Reason - Bit field declaration is necessary here."*/
		/*SAFETYMCUSW 73 S MR:6.4 <APPROVED> "Reason - Bit field is declared as unsigned."*/
		uint16 WriteSync:1U;		
		/*SAFETYMCUSW 42 S MR:3.5 <APPROVED> "Reason - Bit field declaration is necessary here."*/
		/*SAFETYMCUSW 73 S MR:6.4 <APPROVED> "Reason - Bit field is declared as unsigned."*/
		uint16 WriteAsync:1U;		
		/*SAFETYMCUSW 42 S MR:3.5 <APPROVED> "Reason - Bit field declaration is necessary here."*/
		/*SAFETYMCUSW 73 S MR:6.4 <APPROVED> "Reason - Bit field is declared as unsigned."*/
		uint16 EraseImmediate:1U;		
		/*SAFETYMCUSW 42 S MR:3.5 <APPROVED> "Reason - Bit field declaration is necessary here."*/
		/*SAFETYMCUSW 73 S MR:6.4 <APPROVED> "Reason - Bit field is declared as unsigned."*/
		uint16 InvalidateBlock:1U;		
		/*SAFETYMCUSW 42 S MR:3.5 <APPROVED> "Reason - Bit field declaration is necessary here."*/
		/*SAFETYMCUSW 73 S MR:6.4 <APPROVED> "Reason - Bit field is declared as unsigned."*/
		uint16 Copy:1U;				
		/*SAFETYMCUSW 42 S MR:3.5 <APPROVED> "Reason - Bit field declaration is necessary here."*/
		/*SAFETYMCUSW 73 S MR:6.4 <APPROVED> "Reason - Bit field is declared as unsigned."*/
		uint16 Initialized:1U;		
		/*SAFETYMCUSW 42 S MR:3.5 <APPROVED> "Reason - Bit field declaration is necessary here."*/
		/*SAFETYMCUSW 73 S MR:6.4 <APPROVED> "Reason - Bit field is declared as unsigned."*/
		uint16 SingleBitError:1U;
	}Fee_StatusWordType_ST;
}TI_Fee_StatusWordType_UN;

typedef enum
{
   UNINIT,
   IDLE,
   BUSY,
   BUSY_INTERNAL
}TI_FeeModuleStatusType;

typedef enum
{
    JOB_OK,
    JOB_FAILED,
    JOB_PENDING,
    JOB_CANCELLED,
    BLOCK_INCONSISTENT,
    BLOCK_INVALID
}TI_FeeJobResultType;

#endif /* TI_FEE_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: ti_fee_types.h
 *********************************************************************************************************************/
