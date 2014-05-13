/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_cmplx_mult_real_q15.c      
*      
* Description:	Q15 complex by real multiplication      
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
 * @ingroup groupCmplxMath      
 */     
     
/**      
 * @addtogroup CmplxByRealMult      
 * @{      
 */     
     
     
/**      
 * @brief  Q15 complex-by-real multiplication      
 * @param[in]  *pSrcCmplx points to the complex input vector      
 * @param[in]  *pSrcReal points to the real input vector      
 * @param[out]  *pCmplxDst points to the complex output vector      
 * @param[in]  numSamples number of samples in each vector      
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
     
void arm_cmplx_mult_real_q15(     
  q15_t * pSrcCmplx,     
  q15_t * pSrcReal,     
  q15_t * pCmplxDst,     
  uint32_t numSamples)     
{     
  q15_t in;                                      /* Temporary variable to store input value */     
  uint32_t blkCnt;                               /* loop counters */     
  q31_t inA1, inA2;								 /* Temporary variables to hold input data */  
  q31_t inB1;									 /* Temporary variables to hold input data */  
  q15_t out1, out2, out3, out4;					 /* Temporary variables to hold output data */  
  q31_t mul1, mul2, mul3, mul4;					 /* Temporary variables to hold intermediate data */  
  
  /* loop Unrolling */     
  blkCnt = numSamples >> 2u;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 3 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C[2 * i] = A[2 * i] * B[i].            */     
    /* C[2 * i + 1] = A[2 * i + 1] * B[i].        */     
	/* read complex number both real and imaginary from complex input buffer */  
	inA1 = _SIMD32_OFFSET(pSrcCmplx);  
	/* read two real values at a time from real input buffer */  
	inB1 = _SIMD32_OFFSET(pSrcReal);  
	/* read complex number both real and imaginary from complex input buffer */  
	inA2 = _SIMD32_OFFSET(pSrcCmplx + 2);  
  
	/* multiply complex number with real numbers */ 
#ifndef ARM_MATH_BIG_ENDIAN
	
	mul1 = (q31_t)((q15_t)(inA1)* (q15_t)(inB1));  
	mul2 = (q31_t)((q15_t)(inA1 >> 16) * (q15_t)(inB1));  
	mul3 = (q31_t)((q15_t)(inA2)* (q15_t)(inB1 >> 16));  
	mul4 = (q31_t)((q15_t)(inA2 >> 16) * (q15_t)(inB1 >> 16));  
	  
#else
	
	mul2 = (q31_t)((q15_t)(inA1 >> 16)* (q15_t)(inB1>> 16));  
	mul1 = (q31_t)((q15_t)inA1 * (q15_t)(inB1>> 16));  
	mul4 = (q31_t)((q15_t)(inA2 >> 16)* (q15_t)inB1);  
	mul3 = (q31_t)((q15_t)inA2 * (q15_t)inB1);  
	  
#endif	//	#ifndef ARM_MATH_BIG_ENDIAN
	
	/* saturate the result */  
#ifdef CCS  
  
//	out1 = (q15_t) __SSATA(mul1, 15u, 16);  
//	out2 = (q15_t) __SSATA(mul2, 15u, 16);  
//	out3 = (q15_t) __SSATA(mul3, 15u, 16);  
//	out4 = (q15_t) __SSATA(mul4, 15u, 16);  
	out1 = (q15_t) __SSATA(mul1 >> 15u, 0, 16);	//JMM August 15 2012  
	out2 = (q15_t) __SSATA(mul2 >> 15u, 0, 16);	//JMM August 15 2012  
	out3 = (q15_t) __SSATA(mul3 >> 15u, 0, 16);  	//JMM August 15 2012
	out4 = (q15_t) __SSATA(mul4 >> 15u, 0, 16);  	//JMM August 15 2012
  
#else  
  
	out1 = (q15_t) __SSAT(mul1 >> 15u, 16);  
	out2 = (q15_t) __SSAT(mul2 >> 15u, 16);  
	out3 = (q15_t) __SSAT(mul3 >> 15u, 16);  
	out4 = (q15_t) __SSAT(mul4 >> 15u, 16);  
  
#endif 	//	#ifdef CCS  
	  
	/* pack real and imaginary outputs and store them to destination */  
  
 	_SIMD32_OFFSET(pCmplxDst) = __PKHBT(out1, out2, 16);  
 	_SIMD32_OFFSET(pCmplxDst + 2) = __PKHBT(out3, out4, 16);  
  
	inA1 = _SIMD32_OFFSET(pSrcCmplx + 4);  
	inB1 = _SIMD32_OFFSET(pSrcReal + 2);  
	inA2 = _SIMD32_OFFSET(pSrcCmplx + 6);  
  
#ifndef ARM_MATH_BIG_ENDIAN
	
	mul1 = (q31_t)((q15_t)(inA1)* (q15_t)(inB1));  
	mul2 = (q31_t)((q15_t)(inA1 >> 16) * (q15_t)(inB1));  
	mul3 = (q31_t)((q15_t)(inA2) * (q15_t)(inB1 >> 16));  
	mul4 = (q31_t)((q15_t)(inA2 >> 16) * (q15_t)(inB1 >> 16));  
  
#else
	
	mul2 = (q31_t)((q15_t)(inA1 >> 16)* (q15_t)(inB1>> 16));  
	mul1 = (q31_t)((q15_t)inA1 * (q15_t)(inB1>> 16));  
	mul4 = (q31_t)((q15_t)(inA2 >> 16)* (q15_t)inB1);  
	mul3 = (q31_t)((q15_t)inA2 * (q15_t)inB1);  
  
#endif	//	#ifndef ARM_MATH_BIG_ENDIAN
	
#ifdef CCS  
  
	out1 = (q15_t) __SSATA(mul1 >> 15u, 0, 16);  
	out2 = (q15_t) __SSATA(mul2 >> 15u, 0, 16);  
	out3 = (q15_t) __SSATA(mul3 >> 15u, 0, 16);  
	out4 = (q15_t) __SSATA(mul4 >> 15u, 0, 16);  
  
#else  
  
	out1 = (q15_t) __SSAT(mul1 >> 15u, 16);  
	out2 = (q15_t) __SSAT(mul2 >> 15u, 16);  
	out3 = (q15_t) __SSAT(mul3 >> 15u, 16);  
	out4 = (q15_t) __SSAT(mul4 >> 15u, 16);  
  
#endif 	//	#ifdef CCS  
	  

 	_SIMD32_OFFSET(pCmplxDst + 4) = __PKHBT(out1, out2, 16);  
 	_SIMD32_OFFSET(pCmplxDst + 6) = __PKHBT(out3, out4, 16);  
  
	/* update pointer to process next samples */
 	pSrcCmplx += 8u;  
	pSrcReal += 4u;  
	pCmplxDst += 8u;  
  
    /* Decrement the numSamples loop counter */     
    blkCnt--;     
  }     
     
  /* If the numSamples is not a multiple of 4, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = numSamples % 0x4u;     
     
  while(blkCnt > 0u)     
  {     
    /* C[2 * i] = A[2 * i] * B[i].            */     
    /* C[2 * i + 1] = A[2 * i + 1] * B[i].        */     
    in = *pSrcReal++;     
    /* store the result in the destination buffer. */    
#ifdef CCS   
//    *pCmplxDst++ = (q15_t) __SSATA(((q31_t) (*pSrcCmplx++) * (in)), 15, 16);     
//    *pCmplxDst++ = (q15_t) __SSATA(((q31_t) (*pSrcCmplx++) * (in)), 15, 16);     
    *pCmplxDst++ = (q15_t) __SSATA((((q31_t) (*pSrcCmplx++) * (in)) >> 15), 0, 16);     //JMM August 15 2012
    *pCmplxDst++ = (q15_t) __SSATA((((q31_t) (*pSrcCmplx++) * (in)) >> 15), 0, 16);     //JMM August 15 2012     
#else   
    *pCmplxDst++ = (q15_t) __SSAT((((q31_t) (*pSrcCmplx++) * (in)) >> 15), 16);     
    *pCmplxDst++ = (q15_t) __SSAT((((q31_t) (*pSrcCmplx++) * (in)) >> 15), 16);     
#endif   
	   
    /* Decrement the numSamples loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of CmplxByRealMult group      
 */     
