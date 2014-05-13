/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_std_q15.c      
*      
* Description:	Standard deviation of an array of Q15 type.      
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
 * @addtogroup STD      
 * @{      
 */     
     
/**      
 * @brief Standard deviation of the elements of a Q15 vector.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       blockSize length of the input vector      
 * @param[out]      *pResult standard deviation value returned here      
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
 */     
     
void arm_std_q15(     
  q15_t * pSrc,     
  uint32_t blockSize,     
  q15_t * pResult)     
{     
  q63_t sum = 0;                                 /* Accumulator */     
  q31_t meanOfSquares, squareOfMean;             /* square of mean and mean of square */     
  q15_t mean;                                    /* mean */     
  q31_t in1, in2, in3, in4;                      /* temporary variables to hold input value */     
  q15_t in;                                      /* temporary input value */     
  uint32_t blkCnt;                               /* loop counter */     
  q15_t t;                                       /* Temporary variable */     
  q63_t sumSquare = 0;  
  q31_t one = 0x7FFF7FFF;  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1])  */     
    /* Compute Sum of squares of the input samples      
     * and then store the result in a temporary variable, sum. */  
	/* read two samples from source buffer */     
    in1 = _SIMD32_OFFSET(pSrc);     
    in2 = _SIMD32_OFFSET(pSrc + 2);     
  
	/* calculate square and accumulate to accumulator */  
    sumSquare = __SMLALD(in1, in1, sumSquare);  
	/* calculate sum of inputs by multiplying input with 1 and accumulate to accumulator */  
	sum = __SMLALD(in1, one, sum);  
  
	/* calculate square and accumulate to accumulator */  
    sumSquare = __SMLALD(in2, in2, sumSquare);     
      
	/* read two samples from source buffer */     
	in3 = _SIMD32_OFFSET(pSrc + 4);     
   
 	/* calculate sum of inputs by multiplying input with 1 and accumulate to accumulator */  
	sum = __SMLALD(in2, one, sum);  
  
	/* read two samples from source buffer */     
    in4 = _SIMD32_OFFSET(pSrc + 6);     
  
	/* calculate square and accumulate to accumulator */  
    sumSquare = __SMLALD(in3, in3, sumSquare);     
  
	/* calculate sum of inputs by multiplying input with 1 and accumulate to accumulator */  
	sum = __SMLALD(in3, one, sum);  
  
	/* calculate square and accumulate to accumulator */  
    sumSquare = __SMLALD(in4, in4, sumSquare);     
  
	/* calculate sum of inputs by multiplying input with 1 and accumulate to accumulator */  
	sum = __SMLALD(in4, one, sum);  
	  
	/* update pointer to process next samples */  
	pSrc += 8u;  
    
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1]) */     
    /* Compute Sum of squares of the input samples      
     * and then store the result in a temporary variable, sum. */     
    in = *pSrc++;     
    sumSquare = __SMLALD(in, in, sumSquare);     
	sum = __SMLALD(in, one, sum);  
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Compute Mean of squares of the input samples      
   * and then store the result in a temporary variable, meanOfSquares. */     
  t = (q15_t) ((1.0 / (blockSize - 1)) * 16384LL);     
     
#ifdef CCS   
  meanOfSquares = __SSATA((sumSquare), 15u, 16u);     
#else   
  meanOfSquares = __SSAT((sumSquare >> 15u), 16u);     
#endif     
     
  meanOfSquares = (q31_t) ((meanOfSquares * t) >> 14u);     
     
  /* Compute mean of all input values */     
  t = (q15_t) ((1.0 / (blockSize * (blockSize - 1))) * 32768LL);  
       
#ifdef CCS   
  mean = (q15_t) __SSATA(sum, 15u, 16u);     
#else   
  mean = (q15_t) __SSAT(sum >> 15u, 16u);     
#endif   
     
  /* Compute square of mean */     
  squareOfMean = ((q31_t) mean * mean) >> 15;     
  squareOfMean = (q31_t) (((q63_t) squareOfMean * t) >> 15);     
     
  /* mean of the squares minus the square of the mean. */     
  in1 = (q15_t) (meanOfSquares - squareOfMean);     
     
  /* Compute standard deviation and store the result to the destination */     
  arm_sqrt_q15(in1, pResult);     
}     
     
/**      
 * @} end of STD group      
 */     
