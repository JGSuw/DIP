/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_std_f32.c      
*      
* Description:	Standard deviation of the elements of a floating-point vector.    
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
 * @defgroup STD Standard deviation      
 *      
 * Calculates the standard deviation of the elements in the input vector.       
 * The underlying algorithm is used:      
 *     
 * <pre>      
 * 	Result = sqrt((sumOfSquares - sum<sup>2</sup> / blockSize) / (blockSize - 1))     
 *     
 *	   where, sumOfSquares = pSrc[0] * pSrc[0] + pSrc[1] * pSrc[1] + ... + pSrc[blockSize-1] * pSrc[blockSize-1]     
 *     
 *	                   sum = pSrc[0] + pSrc[1] + pSrc[2] + ... + pSrc[blockSize-1]     
 * </pre>     
 *      
 * There are separate functions for floating point, Q31, and Q15 data types.      
 */     
     
/**      
 * @addtogroup STD      
 * @{      
 */     
     
     
/**      
 * @brief Standard deviation of the elements of a floating-point vector.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       blockSize length of the input vector      
 * @param[out]      *pResult standard deviation value returned here      
 * @return none.      
 *      
 */     
     
     
void arm_std_f32(     
  float32_t * pSrc,     
  uint32_t blockSize,     
  float32_t * pResult)     
{     
  float32_t meanOfSquares = 0.0f, mean = 0.0f, in, squareOfMean;     
  uint32_t blkCnt;                                 /* loop counter */     
  float32_t in1, in2, in3, in4;					   /* Temporary input variables */  
  float32_t meanOfSquares1 = 0.0f; 				   /* Temporary intermediate variable */  
  float32_t meanOfSquares2 = 0.0f; 				   /* Temporary intermediate variable */  
  float32_t meanOfSquares3 = 0.0f; 				   /* Temporary intermediate variable */  
  float32_t mean1 = 0.0f; 				   		   /* Temporary intermediate variable */   
     
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1])  */     
    /* Compute Sum of squares of the input samples      
     * and then store the result in a temporary variable, sum. */     
	 /* read two inputs from source buffer */  
	in1 = pSrc[0];  
	in2 = pSrc[1];  
  
	/* calculate sum of inputs */  
	mean += in1;  
	/* calculate square of input and accumulate to accumulator */  
	meanOfSquares += in1 * in1;  
	  
	/* read input from source buffer */  
	in3 = pSrc[2];  
  
	/* calculate sum of inputs */  
	mean1 += in2;  
	/* calculate square of input and accumulate to accumulator */  
	meanOfSquares1 += in2 * in2;  
  
	/* read input from source buffer */  
	in4 = pSrc[3];  
  
	/* calculate sum of inputs */  
	mean += in3;  
	/* calculate square of input and accumulate to accumulator */  
	meanOfSquares2 += in3 * in3;  
  
	/* read input from source buffer */  
	in1 = pSrc[4];  
  
	/* calculate sum of inputs */  
	mean1 += in4;  
	/* calculate square of input and accumulate to accumulator */  
	meanOfSquares3 += in4 * in4;  
  
	/* read input from source buffer */  
	in2 = pSrc[5];  
  
	/* calculate sum of inputs */  
	mean += in1;  
	/* calculate square of input and accumulate to accumulator */  
	meanOfSquares += in1 * in1;  
  
	/* read input from source buffer */  
	in3 = pSrc[6];  
  
	/* calculate sum of inputs */  
	mean1 += in2;  
	/* calculate square of input and accumulate to accumulator */  
	meanOfSquares1 += in2 * in2;  
  
	/* read input from source buffer */  
	in4 = pSrc[7];  
  
	/* calculate sum of inputs */  
	mean += in3;  
	/* calculate square of input and accumulate to accumulator */  
	meanOfSquares2 += in3 * in3;  
  
	/* calculate sum of inputs */  
	mean1 += in4;  
	/* calculate square of input and accumulate to accumulator */  
	meanOfSquares3 += in4 * in4;  
  
	/* update source buffer to process next samples */  
	pSrc += 8u;  
    
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* add mean of square accumulators */  
  meanOfSquares = meanOfSquares + meanOfSquares1 + meanOfSquares2 + meanOfSquares3;  
    
  /* add mean accumulators */  
  mean += mean1;  
    
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
  
     
  while(blkCnt > 0u)     
  {     
    /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1]) */     
    /* Compute Sum of squares of the input samples      
     * and then store the result in a temporary variable, sum. */     
    in = *pSrc++;     
    meanOfSquares += in * in;     
	mean += in;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Compute Mean of squares of the input samples      
   * and then store the result in a temporary variable, meanOfSquares. */     
  meanOfSquares = meanOfSquares / ((float32_t) blockSize - 1.0f);     
     
  /* Compute mean of all input values */     
  mean = mean / (float32_t) blockSize;     
     
   /* Compute square of mean */     
  squareOfMean = (mean * mean) * (((float32_t) blockSize) /     
                                  ((float32_t) blockSize - 1.0f));     
     
  /* Compute standard deviation and then store the result to the destination */     
  arm_sqrt_f32((meanOfSquares - squareOfMean), pResult);  
}     
     
/**      
 * @} end of STD group      
 */     
