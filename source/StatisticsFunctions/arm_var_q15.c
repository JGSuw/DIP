/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_var_q15.c      
*      
* Description:	Variance of an array of Q15 type.      
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
 * @addtogroup variance      
 * @{      
 */     
     
/**      
 * @brief Variance of the elements of a Q15 vector.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       blockSize length of the input vector      
 * @param[out]      *pResult variance value returned here      
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
 * Finally, the 34.30 result is truncated to 34.15 format by discarding the lower       
 * 15 bits, and then saturated to yield a result in 1.15 format.      
 *      
 */     
     
     
void arm_var_q15(     
  q15_t * pSrc,     
  uint32_t blockSize,     
  q31_t * pResult)     
{     
  q63_t sum = 0;                                 /* Accumulator */     
  q31_t meanOfSquares, squareOfMean;             /* Mean of square and square of mean */     
  q15_t mean;                                    /* mean */     
  q31_t in1, in2;                                /* Input variable */     
  q15_t in;                                      /* Temporary variable */     
  uint32_t blkCnt;                               /* loop counter */     
  q15_t t;                                       /* Temporary variable */     
  q15_t *pIn;									 /* Temporary pointer */     
  q31_t one = 0x7FFF7FFF;  
     
  pIn = pSrc;     
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 3 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1])  */     
    /* Compute Sum of squares of the input samples      
     * and then store the result in a temporary variable, sum. */     
	/* read two samples at a time from source buffer */  
    in1 = _SIMD32_OFFSET(pSrc);     
    in2 = _SIMD32_OFFSET(pSrc + 2);     
  
    /* calculate square of input and accumulate ot accumulator */  
	sum = __SMLALD(in1, in1, sum);     
  
	/* read two samples at a time from source buffer */  
    in1 = _SIMD32_OFFSET(pSrc + 4);     
  
    /* calculate square of input and accumulate ot accumulator */  
    sum = __SMLALD(in2, in2, sum);     
  
	/* read two samples at a time from source buffer */  
    in2 = _SIMD32_OFFSET(pSrc + 6);     
  
    /* calculate square of input and accumulate ot accumulator */  
    sum = __SMLALD(in1, in1, sum);     
    sum = __SMLALD(in2, in2, sum);   
	  
	/* update source pointer to process next samples */  
	pSrc += 8u;    
    
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1]) */     
    /* Compute Sum of squares of the input samples      
     * and then store the result in a temporary variable, sum. */     
    in = *pSrc++;     
    sum = __SMLALD(in, in, sum);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Compute Mean of squares of the input samples      
   * and then store the result in a temporary variable, meanOfSquares. */     
  t = (q15_t) ((1.0f / (float32_t) (blockSize - 1u)) * 16384);     
  
#ifdef CCS   
  sum = __SSATA((sum), 15u, 16u);
//  sum = __SSATA((sum>>15u), 0u, 16u);
#else   
  sum = __SSAT((sum >> 15u), 16u);     
#endif   
     
  meanOfSquares = (q31_t) ((sum * t) >> 14u);     
     
  /* Reset the accumulator */     
  sum = 0;     
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* Reset the input working pointer */     
  pSrc = pIn;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 3 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) */     
    /* Compute sum of all input values and then store the result in a temporary variable, sum. */     
	/* load two samples at a time fro source */  
    in1 = _SIMD32_OFFSET(pSrc);     
    in2 = _SIMD32_OFFSET(pSrc + 2);     
  
	/* calculate sum of inputs */  
    sum = __SMLALD(in1, one, sum);  
  
	/* load two samples at a time fro source */  
    in1 = _SIMD32_OFFSET(pSrc + 4);     
  
	/* calculate power of input and accumulate to accumulator */  
    sum = __SMLALD(in2, one, sum);     
  
	/* load two samples at a time fro source */  
    in2 = _SIMD32_OFFSET(pSrc + 6);     
  
	/* calculate power of input and accumulate to accumulator */  
    sum = __SMLALD(in1, one, sum);     
    sum = __SMLALD(in2, one, sum);  
  
	/* update source buffer to process next sampels */  
	pSrc += 8u;     
    
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) */     
    /* Compute sum of all input values and then store the result in a temporary variable, sum. */     
    in = *pSrc++;     
    sum = __SMLALD(in, one, sum);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Compute mean of all input values */     
  t = (q15_t) ((1.0f / (float32_t) (blockSize * (blockSize - 1u))) * 32768);  
       
#ifdef CCS   
    mean = __SSATA(sum, 15u, 16u);     
#else   
	mean = __SSAT(sum >> 15u, 16u);     
#endif   
     
  /* Compute square of mean */     
  squareOfMean = ((q31_t) mean * mean) >> 15;     
  squareOfMean = (q31_t) (((q63_t) squareOfMean * t) >> 15);     
     
  /* Compute variance and then store the result to the destination */     
  *pResult = (meanOfSquares - squareOfMean);     
     
}     
     
/**      
 * @} end of variance group      
 */     
