/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_mean_q7.c      
*      
* Description:	Mean value of a Q7 vector.     
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
 * @addtogroup mean      
 * @{      
 */     
     
/**      
 * @brief Mean value of a Q7 vector.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       blockSize length of the input vector      
 * @param[out]      *pResult mean value returned here      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 * @details      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function is implemented using a 32-bit internal accumulator.       
 * The input is represented in 1.7 format and is accumulated in a 32-bit      
 * accumulator in 25.7 format.      
 * There is no risk of internal overflow with this approach, and the       
 * full precision of intermediate result is preserved.       
 * Finally, the accumulator is truncated to yield a result of 1.7 format.      
 *      
 */     
     
     
void arm_mean_q7(     
  q7_t * pSrc,     
  uint32_t blockSize,     
  q7_t * pResult)     
{     
  q31_t sum = 0;                                 /* Temporary result storage */     
  uint32_t blkCnt;                               /* loop counter */     
  q7_t in1, in2, in3, in4;  
  q31_t sum1 = 0;  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 16 outputs at a time.      
   ** a second loop below computes the remaining 1 to 15 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) */     
	/* read four samples from source buffer */  
	in1 = pSrc[0];  
	in2 = pSrc[1];  
	in3 = pSrc[2];  
	in4 = pSrc[3];  
  
	/* calculate sum of inputs */  
	sum += in1;  
	sum += in2;  
	sum += in3;  
	sum += in4;  
  
	/* read four samples from source buffer */  
	in1 = pSrc[4];  
	in2 = pSrc[5];  
	in3 = pSrc[6];  
	in4 = pSrc[7];  
  
	/* calculate sum of inputs */  
	sum += in1;  
	sum += in2;  
	sum += in3;  
	sum += in4;  
  
	/* update source pointer to process next sampels */  
	pSrc += 8u;  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }  
    
  /* add accumulators */  
  sum = sum + sum1;   
    
  /* If the blockSize is not a multiple of 16, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) */     
    sum += *pSrc++;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) / blockSize  */     
  /* Store the result to the destination */     
  *pResult = (q7_t) (sum / (int32_t) blockSize);     
}     
     
/**      
 * @} end of mean group      
 */     
