/* ----------------------------------------------------------------------    
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*    
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*    
* Project:      Cortex-R DSP Library 
* Title:	    arm_common_tables.h    
*    
* Description:	This file has extern declaration for common tables like Bitreverse, reciprocal etc which are used across different functions    
*    
* Target Processor:          Cortex-R4/R5
*
* Version 1.0.0 2011/03/08
*     Alpha release.
*
* Version 1.0.1 2011/09/30
*     Beta release.
*
* Version 2.0.0 2011/12/15
*     Final release. 
* 
* -------------------------------------------------------------------- */    
#ifndef _ARM_COMMON_TABLES_H    
#define _ARM_COMMON_TABLES_H    
    
#include "arm_math.h"    
    
extern const uint16_t armBitRevTable[1024];    
extern q15_t armRecipTableQ15[64];    
extern q31_t armRecipTableQ31[64];    
    
#endif /*  ARM_COMMON_TABLES_H */    
