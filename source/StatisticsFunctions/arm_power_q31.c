/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_power_q31.c      
*      
* Description:	Sum of the squares of the elements of a Q31 vector.     
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
 * @brief Sum of the squares of the elements of a Q31 vector.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       blockSize length of the input vector      
 * @param[out]      *pResult sum of the squares value returned here      
 * @return none.      
 *      
 * @details      
 * <b>Scaling and Overflow Behavior:</b>      
 *      
 * \par      
 * The function is implemented using a 64-bit internal accumulator.      
 * The input is represented in 1.31 format.      
 * Intermediate multiplication yields a 2.62 format, and this      
 * result is truncated to 2.48 format by discarding the lower 14 bits.      
 * The 2.48 result is then added without saturation to a 64-bit accumulator in 16.48 format.      
 * With 15 guard bits in the accumulator, there is no risk of overflow, and the      
 * full precision of the intermediate multiplication is preserved.      
 * Finally, the return result is in 16.48 format.       
 *      
 */     
     
void arm_power_q31(     
  q31_t * pSrc,     
  uint32_t blockSize,     
  q63_t * pResult)     
{     
  q63_t acc1 = 0, acc2 = 0;                      /* Temporary result storage */     
  q31_t in;   									 /* Temporary variable to store input data */  
  uint32_t blkCnt;                               /* loop counter */     
  q31_t in1 ,in2, in3, in4;						 /* Temporary variable to store input data */  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A[0] * A[0] + A[1] * A[1] + A[2] * A[2] + ... + A[blockSize-1] * A[blockSize-1] */     
    /* Compute Power then shift intermediate results by 14 bits to maintain 16.48 format and then store the result in a temporary variable acc, providing 15 guard bits. */     
	/* read four sampels from source buffer */  
    in1 = pSrc[0];     
	in2 = pSrc[1];     
    in3 = pSrc[2];     
	in4 = pSrc[3];   
  
    /* calculate square and accumulate to accumulator in 16.48 format */  
	acc1 += ((q63_t) in1 * in1) >> 14u;     
	acc2 += ((q63_t) in2 * in2) >> 14u;     
    acc1 += ((q63_t) in3 * in3) >> 14u;     
	acc2 += ((q63_t) in4 * in4) >> 14u;     
  
	/* read four sampels from source buffer */  
    in1 = pSrc[4];     
	in2 = pSrc[5];  
    in3 = pSrc[6];     
 	in4 = pSrc[7];  
   
    /* calculate square and accumulate to accumulator in 16.48 format */  
    acc1 += ((q63_t) in1 * in1) >> 14u;        
	acc2 += ((q63_t) in2 * in2) >> 14u;     
    acc1 += ((q63_t) in3 * in3) >> 14u;     
	acc2 += ((q63_t) in4 * in4) >> 14u;     
  
	/* increment source pointer */  
	pSrc += 8u;  
   
    /* Decrement the loop counter */     
    blkCnt--;     
  }    
    
  /* add accumulators */  
  acc1 = acc1 + acc2;   
    
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A[0] * A[0] + A[1] * A[1] + A[2] * A[2] + ... + A[blockSize-1] * A[blockSize-1] */     
    /* Compute Power and then store the result in a temporary variable, acc. */     
    in = *pSrc++;     
    acc1 += ((q63_t) in * in) >> 14u;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Store the results in 16.48 format  */     
  *pResult = acc1;     
}     
     
/**      
 * @} end of power group      
 */     
