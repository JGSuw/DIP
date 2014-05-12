/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_power_q15.c      
*      
* Description:	Sum of the squares of the elements of a Q15 vector.      
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
#include "arm_math.h"     
     
/**      
 * @ingroup groupStats      
 */     
     
/**      
 * @addtogroup power      
 * @{      
 */     
     
/**      
 * @brief Sum of the squares of the elements of a Q15 vector.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       blockSize length of the input vector      
 * @param[out]      *pResult sum of the squares value returned here      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 * @details      
 * <b>Scaling and Overflow Behavior:</b>      
 *      
 * \par      
 * The function is implemented using a 64-bit internal accumulator.       
 * The input is represented in 1.15 format.     
 * Intermediate multiplication yields a 2.30 format, and this      
 * result is added without saturation to a 64-bit accumulator in 34.30 format.      
 * With 33 guard bits in the accumulator, there is no risk of overflow, and the      
 * full precision of the intermediate multiplication is preserved.      
 * Finally, the return result is in 34.30 format.       
 *      
 */     
     
void arm_power_q15(     
  q15_t * pSrc,     
  uint32_t blockSize,     
  q63_t * pResult)     
{     
  q63_t acc = 0;                                 /* Temporary result storage */     
  q15_t in16;                                    /* Temporary variable to store input value */     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t in1, in2, in3, in4;						 /* Temporary variable to store input value */  
     
     
  /* loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A[0] * A[0] + A[1] * A[1] + A[2] * A[2] + ... + A[blockSize-1] * A[blockSize-1] */     
    /* Compute Power and then store the result in a temporary variable, acc. */   
	/* read two inputs at a time from source */    
	in1 = _SIMD32_OFFSET(pSrc);     
    in2 = _SIMD32_OFFSET(pSrc + 2);     
  
	/* caluculate power and accumulate it ot accumulator */  
    acc = __SMLALD(in1, in1, acc);     
  
	/* read two inputs at a time from source */    
    in3 = _SIMD32_OFFSET(pSrc + 4);     
  
	/* caluculate power and accumulate it ot accumulator */  
    acc = __SMLALD(in2, in2, acc);     
  
	/* read two inputs at a time from source */    
    in4 = _SIMD32_OFFSET(pSrc + 6);     
  
	/* caluculate power and accumulate it ot accumulator */  
    acc = __SMLALD(in3, in3, acc);     
    acc = __SMLALD(in4, in4, acc);     
  
	/* update source pointer to process next sampels */  
	pSrc += 8u;  
	  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A[0] * A[0] + A[1] * A[1] + A[2] * A[2] + ... + A[blockSize-1] * A[blockSize-1] */     
    /* Compute Power and then store the result in a temporary variable, acc. */     
    in16 = *pSrc++;     
    acc = __SMLALD(in16, in16, acc);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Store the results in 34.30 format  */     
  *pResult = acc;     
}     
     
/**      
 * @} end of power group      
 */     
