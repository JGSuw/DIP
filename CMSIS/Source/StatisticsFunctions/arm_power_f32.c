/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_power_f32.c      
*      
* Description:	Sum of the squares of the elements of a floating-point vector.      
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
 * @defgroup power Power      
 *      
 * Calculates the sum of the squares of the elements in the input vector.      
 * The underlying algorithm is used:      
 *      
 * <pre>      
 * 	Result = pSrc[0] * pSrc[0] + pSrc[1] * pSrc[1] + pSrc[2] * pSrc[2] + ... + pSrc[blockSize-1] * pSrc[blockSize-1];      
 * </pre>      
 *     
 * There are separate functions for floating point, Q31, Q15, and Q7 data types.       
 */     
     
/**      
 * @addtogroup power      
 * @{      
 */     
     
     
/**      
 * @brief Sum of the squares of the elements of a floating-point vector.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       blockSize length of the input vector      
 * @param[out]      *pResult sum of the squares value returned here      
 * @return none.      
 *      
 */     
     
     
void arm_power_f32(     
  float32_t * pSrc,     
  uint32_t blockSize,     
  float32_t * pResult)     
{     
  float32_t in;                                  /* Temporary variable to store input value */     
  uint32_t blkCnt;                               /* loop counter */     
  float32_t in1, in2, in3, in4;					 /* Temporary variables to hold input data */  
  float32_t acc1 = 0.0f, acc2 = 0.0f;			 /* accumulators */     
  float32_t acc3 = 0.0f, acc4 = 0.0f;			 /* accumulators */     
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A[0] * A[0] + A[1] * A[1] + A[2] * A[2] + ... + A[blockSize-1] * A[blockSize-1] */     
    /* Compute Power and then store the result in a temporary variable, acc. */     
	/* load four samples from source buffer */  
	in1 = pSrc[0];  
	in2 = pSrc[1];  
	in3 = pSrc[2];  
	in4 = pSrc[3];  
  
	/* calculate square of input and accumulate it to accumulator */  
	acc1 += in1 * in1;  
	acc2 += in2 * in2;  
	acc3 += in3 * in3;  
	acc4 += in4 * in4;  
  
	/* load four samples from source buffer */  
	in1 = pSrc[4];  
	in2 = pSrc[5];  
	in3 = pSrc[6];  
	in4 = pSrc[7];  
  
	/* calculate square of input and accumulate it to accumulator */  
	acc1 += in1 * in1;  
	acc2 += in2 * in2;  
	acc3 += in3 * in3;  
	acc4 += in4 * in4;  
  
	/* update source pointer to process next samples */  
	pSrc += 8u;  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }  
    
  /* add accumulators */     
  acc1 = acc1 + acc2 + acc3 + acc4;  
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A[0] * A[0] + A[1] * A[1] + A[2] * A[2] + ... + A[blockSize-1] * A[blockSize-1] */     
    /* compute power and then store the result in a temporary variable, acc. */     
    in = *pSrc++;     
    acc1 += in * in;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Store the result to the destination */     
  *pResult = acc1;     
}     
     
/**      
 * @} end of power group      
 */     
