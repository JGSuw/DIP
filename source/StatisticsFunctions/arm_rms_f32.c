/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_rms_f32.c      
*      
* Description:	Root mean square value of an array of F32 type      
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
* ---------------------------------------------------------------------------- */     
#include "arm_math.h"     
     
/**      
 * @ingroup groupStats      
 */     
     
/**      
 * @defgroup RMS Root mean square (RMS)      
 *      
 *       
 * Calculates the Root Mean Sqaure of the elements in the input vector.      
 * The underlying algorithm is used:      
 *      
 * <pre>      
 * 	Result = sqrt(((pSrc[0] * pSrc[0] + pSrc[1] * pSrc[1] + ... + pSrc[blockSize-1] * pSrc[blockSize-1]) / blockSize));      
 * </pre>      
 *     
 * There are separate functions for floating point, Q31, and Q15 data types.       
 */     
     
/**      
 * @addtogroup RMS      
 * @{      
 */     
     
     
/**      
 * @brief Root Mean Square of the elements of a floating-point vector.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       blockSize length of the input vector      
 * @param[out]      *pResult rms value returned here      
 * @return none.      
 *      
 */     
     
void arm_rms_f32(     
  float32_t * pSrc,     
  uint32_t blockSize,     
  float32_t * pResult)     
{     
  float32_t in;                                  /* Tempoprary variable to store input value */     
  uint32_t blkCnt;                               /* loop counter */     
  float32_t in1, in2, in3, in4;					 /* Temporary input variables */  
  float32_t sum1= 0, sum2 = 0, sum3 = 0, sum4 = 0;/* Accumulators */  
     
  /* loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A[0] * A[0] + A[1] * A[1] + A[2] * A[2] + ... + A[blockSize-1] * A[blockSize-1] */     
    /* Compute sum of the squares and then store the result in a temporary variable, sum  */     
	/* read four samples from source buffer */  
	in1 = pSrc[0];  
	in2 = pSrc[1];  
	in3 = pSrc[2];  
	in4 = pSrc[3];  
  
	/* calculate square and accumulate to accumulator */  
	sum1 += in1 * in1;  
	sum2 += in2 * in2;  
 	sum3 += in3 * in3;  
	sum4 += in4 * in4;  
  
	/* read four samples from source buffer */  
	in1 = pSrc[4];  
	in2 = pSrc[5];  
	in3 = pSrc[6];  
	in4 = pSrc[7];  
  
	/* calculate square and accumulate to accumulator */  
	sum1 += in1 * in1;  
	sum2 += in2 * in2;  
	sum3 += in3 * in3;  
	sum4 += in4 * in4;  
  
	/* update source buffer to process next samples */  
	pSrc += 8u;  
   
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* add accumulators */  
  sum1 = sum1 + sum2 + sum3 + sum4;  
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A[0] * A[0] + A[1] * A[1] + A[2] * A[2] + ... + A[blockSize-1] * A[blockSize-1] */     
    /* Compute sum of the squares and then store the results in a temporary variable, sum  */     
    in = *pSrc++;     
    sum1 += in * in;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Compute Rms and store the result in the destination */     
  arm_sqrt_f32(sum1 / (float32_t) blockSize, pResult);     
}     
     
/**      
 * @} end of RMS group      
 */     
