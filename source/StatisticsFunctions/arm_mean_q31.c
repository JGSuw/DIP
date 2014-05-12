/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_mean_q31.c      
*      
* Description:	Mean value of a Q31 vector.     
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
 * @brief Mean value of a Q31 vector.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       blockSize length of the input vector      
 * @param[out]      *pResult mean value returned here      
 * @return none.      
 *      
 * @details      
 * <b>Scaling and Overflow Behavior:</b>      
 *\par      
 * The function is implemented using a 64-bit internal accumulator.      
 * The input is represented in 1.31 format and is accumulated in a 64-bit      
 * accumulator in 33.31 format.      
 * There is no risk of internal overflow with this approach, and the       
 * full precision of intermediate result is preserved.       
 * Finally, the accumulator is truncated to yield a result of 1.31 format.      
 *      
 */     
     
     
void arm_mean_q31(     
  q31_t * pSrc,     
  uint32_t blockSize,     
  q31_t * pResult)     
{     
  q63_t sum = 0;       			               	 /* Temporary result storage */     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t in1, in2, in3, in4;	   					 /* Temporary variables to hold input data */  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  8 Computations at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) */     
	/* read four samples from source */  
	in1 = pSrc[0];  
	in2 = pSrc[1];  
	in3 = pSrc[2];  
	in4 = pSrc[3];  
  
	/* calculate sum of inputs */  
	sum += in1;  
	sum += in2;  
	sum += in3;  
	sum += in4;  
  
	/* read four samples from source */  
	in1 = pSrc[4];  
	in2 = pSrc[5];  
	in3 = pSrc[6];  
	in4 = pSrc[7];  
  
	/* calculate sum of inputs */  
	sum += in1;  
	sum += in2;  
	sum += in3;  
	sum += in4;  
  
	/* update source pointer to process next samples */  
	pSrc += 8u;  
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
  
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
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
  *pResult = (q31_t) (sum / (int32_t) blockSize);     
}     
     
/**      
 * @} end of mean group      
 */     
