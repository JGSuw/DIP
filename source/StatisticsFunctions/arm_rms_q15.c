/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_rms_q15.c      
*      
* Description:	Root Mean Square of the elements of a Q15 vector.    
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
 * @addtogroup RMS      
 * @{      
 */     
     
/**      
 * @brief Root Mean Square of the elements of a Q15 vector.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       blockSize length of the input vector      
 * @param[out]      *pResult rms value returned here      
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
     
void arm_rms_q15(     
  q15_t * pSrc,     
  uint32_t blockSize,     
  q15_t * pResult)     
{     
  q63_t sum = 0;                                 /* accumulator */     
  q31_t in1;                                     /* temporary variable to store the input value */     
  q15_t in;                                      /* temporary variable to store the input value */     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t in2, in3, in4;							 /* temporary variabels to store input valeus */  
     
  /* loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1]) */     
    /* Compute sum of the squares and then store the results in a temporary variable, sum */     
	/* read two samples from source buffer */  
    in1 = _SIMD32_OFFSET(pSrc);     
    in2 = _SIMD32_OFFSET(pSrc + 2);     
  
	/* calculate power and accumulate to accumulator */  
    sum = __SMLALD(in1, in1, sum);     
  
	/* read two samples from source buffer */  
    in3 = _SIMD32_OFFSET(pSrc + 4);     
  
	/* calculate power and accumulate to accumulator */  
    sum = __SMLALD(in2, in2, sum);     
  
	/* read two samples from source buffer */  
    in4 = _SIMD32_OFFSET(pSrc + 6);     
  
	/* calculate power and accumulate to accumulator */  
    sum = __SMLALD(in3, in3, sum);     
    sum = __SMLALD(in4, in4, sum);   
  
	/* update source buffer to process next sampels */  
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
    /* Compute sum of the squares and then store the results in a temporary variable, sum */     
    in = *pSrc++;     
    sum = __SMLALD(in, in, sum);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Truncating and saturating the accumulator to 1.15 format */     
#ifdef CCS   
//  sum = __SSATA((q31_t) (sum), 15, 16);
  sum = __SSATA((q31_t) (sum>>15u), 0u, 16u);

#else   
  sum = __SSAT((q31_t) (sum >> 15), 16);     
#endif   
     
  in1 = (q15_t) (sum / blockSize);     
     
  /* Store the result in the destination */     
  arm_sqrt_q15(in1, pResult);     
}     
     
/**      
 * @} end of RMS group      
 */     
