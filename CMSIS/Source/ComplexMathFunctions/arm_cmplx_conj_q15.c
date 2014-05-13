/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_cmplx_conj_q15.c      
*      
* Description:	Q15 complex conjugate.      
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
 * @ingroup groupCmplxMath      
 */     
     
/**      
 * @addtogroup cmplx_conj      
 * @{      
 */     
     
/**      
 * @brief  Q15 complex conjugate.      
 * @param  *pSrc points to the input vector      
 * @param  *pDst points to the output vector      
 * @param  numSamples number of complex samples in each vector      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function uses saturating arithmetic.      
 * The Q15 value -1 (0x8000) will be saturated to the maximum allowable positive value 0x7FFF.      
 */     
     
void arm_cmplx_conj_q15(     
  q15_t * pSrc,     
  q15_t * pDst,     
  uint32_t numSamples)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t in1, in2, in3, in4;						 /* temporary variables */  
  q31_t zero = 0;  
     
  /*loop Unrolling */     
  blkCnt = numSamples >> 2u;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 3 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C[0]+jC[1] = A[0]+ j (-1) A[1] */     
    /* Calculate Complex Conjugate and then store the results in the destination buffer. */     
	/* read real and imaginary inputs at a time */  
	in1 = _SIMD32_OFFSET(pSrc);  
	in2 = _SIMD32_OFFSET(pSrc + 2);  
  
	/* exchange real and imaginary, subtract imaginary and add real to zero */  
#ifndef ARM_MATH_BIG_ENDIAN	

	in1 = __QASX(zero, in1);  
  
#else

	in1 = __QSAX(zero, in1);  

#endif //	#ifndef ARM_MATH_BIG_ENDIAN

	/* read real and imaginary inputs at a time */  
	in3 = _SIMD32_OFFSET(pSrc + 4);  
  
	/* exchange real and imaginary, subtract imaginary and add real to zero */  
#ifndef ARM_MATH_BIG_ENDIAN	

	in2 = __QASX(zero, in2);  
  
#else

	in2 = __QSAX(zero, in2);  

#endif //	#ifndef ARM_MATH_BIG_ENDIAN

	/* read real and imaginary inputs at a time */  
	in4 = _SIMD32_OFFSET(pSrc + 6);  
  
	/* exchange upper and lower */  
	in1 = ((uint32_t)in1 >> 16) | ((uint32_t)in1 << 16);  
	in2 = ((uint32_t)in2 >> 16) | ((uint32_t)in2 << 16);  
  
	/* exchange real and imaginary, subtract imaginary and add real to zero */  
#ifndef ARM_MATH_BIG_ENDIAN	
	
	in3 = __QASX(zero, in3);  
	in4 = __QASX(zero, in4);  
  
#else

	in3 = __QSAX(zero, in3);  
	in4 = __QSAX(zero, in4);  

#endif //	#ifndef ARM_MATH_BIG_ENDIAN

	/* store result to destination buffer both real and imaginay at a time */  
	_SIMD32_OFFSET(pDst) = in1;  
	_SIMD32_OFFSET(pDst + 2) = in2;  
  
	/* exchange upper and lower */  
	in3 = ((uint32_t)in3 >> 16) | ((uint32_t)in3 << 16);  
	in4 = ((uint32_t)in4 >> 16) | ((uint32_t)in4 << 16);  
	  
	/* store result to destination buffer both real and imaginay at a time */  
	_SIMD32_OFFSET(pDst + 4) = in3;  
	  
	/* increment source pointer by 8 to process next samples */  
	pSrc += 8u;  
	  
	/* store result to destination buffer both real and imaginay at a time */  
	_SIMD32_OFFSET(pDst + 6) = in4;  
	/* increment destination pointer by 8 to process next samples */  
	pDst += 8u;  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the numSamples is not a multiple of 4, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = numSamples % 0x4u;     
     
  while(blkCnt > 0u)     
  {     
    /* C[0]+jC[1] = A[0]+ j (-1) A[1] */     
    /* Calculate Complex Conjugate and then store the results in the destination buffer. */     
    *pDst++ = *pSrc++;     
#ifdef CCS   
    *pDst++ = __SSATA(-*pSrc++, 0, 16);     
#else   
    *pDst++ = __SSAT(-*pSrc++, 16);     
#endif	   
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of cmplx_conj group      
 */     
