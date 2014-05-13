/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_mean_f32.c      
*      
* Description:	Mean value of a floating-point vector.     
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
 * @defgroup mean Mean      
 *      
 * Calculates the mean of the input vector. Mean is defined as the average of the elements in the vector.      
 * The underlying algorithm is used:      
 *      
 * <pre>      
 * 	Result = (pSrc[0] + pSrc[1] + pSrc[2] + ... + pSrc[blockSize-1]) / blockSize;      
 * </pre>      
 *      
 * There are separate functions for floating-point, Q31, Q15, and Q7 data types.      
 */     
     
/**      
 * @addtogroup mean      
 * @{      
 */     
     
     
/**      
 * @brief Mean value of a floating-point vector.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       blockSize length of the input vector      
 * @param[out]      *pResult mean value returned here      
 * @return none.      
 */     
     
     
void arm_mean_f32(     
  float32_t * pSrc,     
  uint32_t blockSize,     
  float32_t * pResult)     
{     
  float32_t sum1 = 0.0f;                         /* Temporary result storage */     
  float32_t sum2 = 0.0f;  						 /* Temporary result storage */  
  uint32_t blkCnt;                               /* loop counter */     
  float32_t in1, in2, in3, in4;		   			 /* Temporary variabels to hold input data */  
  float32_t in5, in6, in7, in8;					 /* Temporary variabels to hold input data */  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) */     
	/* read inputs from source buffer */  
	in1 = pSrc[0];  
	in2 = pSrc[1];  
	in3 = pSrc[2];  
  
	/* accumulate to sum1 */  
	sum1 += in1;  
  
	/* read input from source buffer */  
	in4 = pSrc[3];  
  
	/* accumulate to sum2 */  
	sum2 += in2;  
  
	/* read input from source buffer */  
	in5 = pSrc[4];  
  
	/* accumulate to sum1 */  
	sum1 += in3;  
  
	/* read input from source buffer */  
	in6 = pSrc[5];  
  
	/* accumulate to sum1 */  
	sum2 += in4;  
  
	/* read input from source buffer */  
	in7 = pSrc[6];  
  
	/* accumulate to sum1 */  
	sum1 += in5;  
  
	/* read input from source buffer */  
	in8 = pSrc[7];  
  
	/* update source buffer to process next sampels */  
	pSrc += 8u;  
  
	/* accumulate to sum2 */  
	sum2 += in6;  
  
	/* accumulate to sum1 */  
	sum1 += in7;  
  
	/* accumulate to sum2 */  
	sum2 += in8;  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
    
  /* add two accumulators */  
  sum1 = sum2 + sum1;   
    
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) */     
    sum1 += *pSrc++;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) / blockSize  */     
  /* Store the result to the destination */     
  *pResult = sum1 / (float32_t) blockSize;     
}     
     
/**      
 * @} end of mean group      
 */     
