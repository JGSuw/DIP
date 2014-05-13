/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_std_q31.c      
*      
* Description:	Standard deviation of an array of Q31 type.      
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
 * @brief Standard deviation of the elements of a Q31 vector.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       blockSize length of the input vector      
 * @param[out]      *pResult standard deviation value returned here      
 * @return none.      
 * @details      
 * <b>Scaling and Overflow Behavior:</b>      
 *      
 *\par      
 * The function is implemented using an internal 64-bit accumulator.      
 * The input is represented in 1.31 format, and intermediate multiplication      
 * yields a 2.62 format.      
 * The accumulator maintains full precision of the intermediate multiplication results,       
 * but provides only a single guard bit.      
 * There is no saturation on intermediate additions.      
 * If the accumulator overflows it wraps around and distorts the result.      
 * In order to avoid overflows completely the input signal must be scaled down by       
 * log2(blockSize) bits, as a total of blockSize additions are performed internally.       
 * Finally, the 2.62 accumulator is right shifted by 31 bits to yield a 1.31 format value.      
 *      
 */     
     
     
void arm_std_q31(     
  q31_t * pSrc,     
  uint32_t blockSize,     
  q31_t * pResult)     
{     
  q63_t sum = 0, sumSquare = 0;                                 /* Accumulator */     
  q31_t meanOfSquares, squareOfMean;             /* square of mean and mean of square */     
  q31_t mean;                                    /* mean */     
  q31_t in;                                      /* input value */     
  q31_t t;                                       /* Temporary variable */     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t in1, in2, in3, in4;						 /* Temporary input variables */  
  q63_t sumSquare1 = 0;  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1])  */     
    /* Compute Sum of squares of the input samples      
     * and then store the result in a temporary variable, sum. */     
	/* read input from source buffer */  
    in1 = pSrc[0];     
    in2 = pSrc[1];     
  
	/* calculate sum of inputs */  
	sum += in1;    
	/* calculate power of input and accumulate to accumulator */  
    sumSquare += ((q63_t) (in1) * (in1));   
  
	/* read input from source buffer */  
    in3 = pSrc[2];     
  
	/* calculate sum of inputs */  
	sum += in2;    
	/* calculate power of input and accumulate to accumulator */  
    sumSquare1 += ((q63_t) (in2) * (in2));   
  
	/* read input from source buffer */  
    in4 = pSrc[3];     
  
	/* calculate sum of inputs */  
 	sum += in3;    
	/* calculate power of input and accumulate to accumulator */  
    sumSquare += ((q63_t) (in3) * (in3));   
  
	/* read input from source buffer */  
    in1 = pSrc[4];     
  
	/* calculate sum of inputs */  
 	sum += in4;    
	/* calculate power of input and accumulate to accumulator */  
    sumSquare1 += ((q63_t) (in4) * (in4));   
  
	/* read input from source buffer */  
    in2 = pSrc[5];     
  
	/* calculate sum of inputs */  
	sum += in1;    
	/* calculate power of input and accumulate to accumulator */  
    sumSquare += ((q63_t) (in1) * (in1));   
  
	/* read input from source buffer */  
    in3 = pSrc[6];     
  
	/* calculate sum of inputs */  
	sum += in2;    
	/* calculate power of input and accumulate to accumulator */  
    sumSquare1 += ((q63_t) (in2) * (in2));   
  
	/* read input from source buffer */  
    in4 = pSrc[7];     
  
	/* calculate sum of inputs */  
	sum += in3;    
	/* calculate power of input and accumulate to accumulator */  
    sumSquare += ((q63_t) (in3) * (in3));   
  
	/* calculate sum of inputs */  
	sum += in4;    
	/* calculate power of input and accumulate to accumulator */  
    sumSquare1 += ((q63_t) (in4) * (in4));   
	  
	/* update source buffer pointer to process next samples */  
	pSrc += 8u;  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* add sum of square accumulators */  
  sumSquare = sumSquare + sumSquare1;  
    
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1]) */     
    /* Compute Sum of squares of the input samples      
     * and then store the result in a temporary variable, sum. */     
    in = *pSrc++;     
    sumSquare += ((q63_t) (in) * (in));   
	sum += in;    
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  t = (q31_t) ((1.0f / (float32_t) (blockSize - 1u)) * 1073741824.0f);     
     
  /* Compute Mean of squares of the input samples      
   * and then store the result in a temporary variable, meanOfSquares. */     
  sumSquare = (sumSquare >> 31);     
  meanOfSquares = (q31_t) ((sumSquare * t) >> 30);     
  
  /* Compute mean of all input values */     
  t = (q31_t) ((1.0f / (blockSize * (blockSize - 1u))) * 2147483648.0f);     
  mean = (q31_t) (sum);     
     
  /* Compute square of mean */     
  squareOfMean = (q31_t) (((q63_t) mean * mean) >> 31);     
  squareOfMean = (q31_t) (((q63_t) squareOfMean * t) >> 31);     
     
  /* Compute standard deviation and then store the result to the destination */     
  arm_sqrt_q31(meanOfSquares - squareOfMean, pResult);     
     
}     
     
/**      
 * @} end of STD group      
 */     
