/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_mult_q15.c      
*      
* Description:	Q15 vector multiplication.      
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
 * @addtogroup BasicMult      
 * @{      
 */     
     
     
/**      
 * @brief           Q15 vector multiplication      
 * @param[in]       *pSrcA points to the first input vector      
 * @param[in]       *pSrcB points to the second input vector      
 * @param[out]      *pDst points to the output vector      
 * @param[in]       blockSize number of samples in each vector      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function uses saturating arithmetic.      
 * Results outside of the allowable Q15 range [0x8000 0x7FFF] will be saturated.      
 */     
     
void arm_mult_q15(     
  q15_t * pSrcA,     
  q15_t * pSrcB,     
  q15_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counters */     
  q31_t inA1, inA2, inB1, inB2;					 /* temporary input variables */  
  q15_t out1, out2, out3, out4;					 /* temporary output variables */  
  q31_t mul1, mul2, mul3, mul4;					 /* temporary variables */  
     
  /* loop Unrolling */     
  blkCnt = blockSize >> 2u;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 3 samples. */     
  while(blkCnt > 0u)     
  {  
    /* read two samples at a time from sourceA */  
	inA1 = *__SIMD32(pSrcA)++;  
	/* read two samples at a time from sourceB */  
	inB1 = *__SIMD32(pSrcB)++;  
    /* read two samples at a time from sourceA */  
    inA2 = *__SIMD32(pSrcA)++;  
	/* read two samples at a time from sourceB */  
	inB2 = *__SIMD32(pSrcB)++;  
  
	/* multiply mul = sourceA * sourceB */  
	mul1 = (q31_t)((q15_t)(inA1 >> 16)* (q15_t)(inB1>> 16));  
	mul2 = (q31_t)((q15_t)inA1 * (q15_t)inB1);  
	mul3 = (q31_t)((q15_t)(inA2 >> 16)* (q15_t)(inB2>> 16));  
	mul4 = (q31_t)((q15_t)inA2 * (q15_t)inB2);  
  
	/* shift result by 15 to get 16 bit result */  
	mul1 = mul1 >> 15;  
	mul2 = mul2 >> 15;  
	mul3 = mul3 >> 15;  
	mul4 = mul4 >> 15;  
  
	/* saturate result to 16 bit */  
#ifdef CCS  
  
	out1 = (q15_t) __SSATA(mul1, 0, 16);  
	out2 = (q15_t) __SSATA(mul2, 0, 16);  
	out3 = (q15_t) __SSATA(mul3, 0, 16);  
	out4 = (q15_t) __SSATA(mul4, 0, 16);  
  
#else  
  
	out1 = (q15_t) __SSAT(mul1, 16);  
	out2 = (q15_t) __SSAT(mul2, 16);  
	out3 = (q15_t) __SSAT(mul3, 16);  
	out4 = (q15_t) __SSAT(mul4, 16);  
  
#endif 	//	#ifdef CCS  
  
	/* store the result */  
#ifndef ARM_MATH_BIG_ENDIAN  
  
 	*__SIMD32(pDst)++ = __PKHBT(out2, out1, 16);  
 	*__SIMD32(pDst)++ = __PKHBT(out4, out3, 16);  
  
#else  
  
 	*__SIMD32(pDst)++ = __PKHBT(out2, out1, 16);  
 	*__SIMD32(pDst)++ = __PKHBT(out4, out3, 16);  
  
#endif		//	#ifndef ARM_MATH_BIG_ENDIAN  
  
    /* Decrement the blockSize loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x4u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A * B */     
    /* Multiply the inputs and store the result in the destination buffer */     
#ifdef CCS	   
    *pDst++ = (q15_t) __SSATA(((q31_t) ((*pSrcA++) * (*pSrcB++)) >> 15), 0, 16);
#else   
    *pDst++ = (q15_t) __SSAT((((q31_t) (*pSrcA++) * (*pSrcB++)) >> 15), 16);     
#endif	//	#ifdef CCS     
    /* Decrement the blockSize loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of BasicMult group      
 */     
