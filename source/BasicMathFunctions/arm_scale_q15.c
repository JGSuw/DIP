/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_scale_q15.c      
*      
* Description:	Multiplies a Q15 vector by a scalar.      
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
 * @ingroup groupMath      
 */     
     
/**      
 * @addtogroup scale      
 * @{      
 */     
     
/**      
 * @brief Multiplies a Q15 vector by a scalar.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       scaleFract fractional portion of the scale value      
 * @param[in]       shift number of bits to shift the result by      
 * @param[out]      *pDst points to the output vector      
 * @param[in]       blockSize number of samples in the vector      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The input data <code>*pSrc</code> and <code>scaleFract</code> are in 1.15 format.      
 * These are multiplied to yield a 2.30 intermediate result and this is shifted with saturation to 1.15 format.      
 */     
     
     
void arm_scale_q15(     
  q15_t * pSrc,     
  q15_t scaleFract,     
  int8_t shift,     
  q15_t * pDst,     
  uint32_t blockSize)     
{     
  int8_t kShift = 15 - shift;                    /* shift to apply after scaling */     
  uint32_t blkCnt;                               /* loop counter */     
  q15_t in1, in2, in3, in4;  
  q31_t inA1, inA2;                                /* Temporary variables */     
  q31_t out1, out2, out3, out4;  
     
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 2u;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 3 samples. */     
  while(blkCnt > 0u)     
  {     
    /* Reading 2 inputs from memory */     
    inA1 = *__SIMD32(pSrc)++;     
    inA2 = *__SIMD32(pSrc)++;   
	    
    /* C = A * scale */     
    /* Scale the inputs and then store the 2 results in the destination buffer      
     * in single cycle by packing the outputs */     
 	out1 = (q31_t)((q15_t)(inA1 >> 16) * scaleFract);  
	out2 = (q31_t)((q15_t)inA1 * scaleFract);  
	out3 = (q31_t)((q15_t)(inA2 >> 16) * scaleFract);  
	out4 = (q31_t)((q15_t)inA2 * scaleFract);  
  
	/* apply shifting */  
	out1 = out1 >> kShift;  
	out2 = out2 >> kShift;  
	out3 = out3 >> kShift;  
	out4 = out4 >> kShift;  
  
	/* saturate the output */  
#ifdef CCS  
  
	in1 = (q15_t)(__SSATA(out1, 0, 16));  
	in2 = (q15_t)(__SSATA(out2, 0, 16));  
	in3 = (q15_t)(__SSATA(out3, 0, 16));  
	in4 = (q15_t)(__SSATA(out4, 0, 16));  
  
#else  
  
	in1 = (q15_t)(__SSAT(out1, 16));  
	in2 = (q15_t)(__SSAT(out2, 16));  
	in3 = (q15_t)(__SSAT(out3, 16));  
	in4 = (q15_t)(__SSAT(out4, 16));  
  
#endif  
  
	/* store the result to destination */  
 	*__SIMD32(pDst)++ = __PKHBT(in2, in1,16);  
 	*__SIMD32(pDst)++ = __PKHBT(in4, in3,16);  
					  
   /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x4u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A * scale */     
    /* Scale the input and then store the result in the destination buffer. */     
#ifdef CCS	   
    *pDst++ = (q15_t) (__SSATA(((*pSrc++) * scaleFract) >> kShift, 0, 16));     
#else   
    *pDst++ = (q15_t) (__SSAT(((*pSrc++) * scaleFract) >> kShift, 16));     
#endif     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of scale group      
 */     
