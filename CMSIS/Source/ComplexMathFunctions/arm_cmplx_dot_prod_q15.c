/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_cmplx_dot_prod_q15.c      
*      
* Description:	Processing function for the Q15 Complex Dot product      
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
 * @addtogroup cmplx_dot_prod      
 * @{      
 */     
     
/**      
 * @brief  Q15 complex dot product      
 * @param  *pSrcA points to the first input vector      
 * @param  *pSrcB points to the second input vector      
 * @param  numSamples number of complex samples in each vector      
 * @param  *realResult real part of the result returned here      
 * @param  *imagResult imaginary part of the result returned here      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function is implemented using an internal 64-bit accumulator.      
 * The intermediate 1.15 by 1.15 multiplications are performed with full precision and yield a 2.30 result.      
 * These are accumulated in a 64-bit accumulator with 34.30 precision.      
 * As a final step, the accumulators are converted to 8.24 format.      
 * The return results <code>realResult</code> and <code>imagResult</code> are in 8.24 format.      
 */     
     
void arm_cmplx_dot_prod_q15(     
  q15_t * pSrcA,     
  q15_t * pSrcB,     
  uint32_t numSamples,     
  q31_t * realResult,     
  q31_t * imagResult)     
{     
  q63_t real_sum = 0, imag_sum = 0;              /* Temporary result storage */     
  q31_t inA1, inA2;								 /* Temporary input variables */  
  q31_t inB1, inB2;								 /* Temporary input variables */  
  q31_t real1, real2, imag1, imag2;				 /* Temporary variables */  
  
  uint32_t blkCnt;                               /* loop counter */     
#ifndef ARM_MATH_BIG_ENDIAN  
  
  q15_t imagA1, imagB1;							 /* Temporary input variables */  
  
#else  
  
  q15_t realA1, realB1;							 /* Temporary input variables */  
  
#endif	  //	#ifndef ARM_MATH_BIG_ENDIAN  
     
     
  /*loop Unrolling */     
  blkCnt = numSamples >> 2u;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 3 samples. */     
  while(blkCnt > 0u)     
  {  
  	/* load two numbers from sourceA buffer at a time */  
	inA1 = _SIMD32_OFFSET(pSrcA);  
  	/* load two numbers from sourceA buffer at a time */  
	inA2 = _SIMD32_OFFSET(pSrcA + 2);  
  
  	/* load two numbers from sourceA buffer at a time */  
	inB1 = _SIMD32_OFFSET(pSrcB);  
  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* pack two real numbers */  
	real1 = __PKHBT((q15_t)inA1, (q15_t)inA2, 16);  
  
#else  
  
	/* pack two imaginary numbers */  
	imag1 = __PKHBT((q15_t)inA1, (q15_t)inA2, 16);  
  
#endif	  //	#ifndef ARM_MATH_BIG_ENDIAN  
  
  	/* load two samples from sourceB buffer at a time */  
	inB2 = _SIMD32_OFFSET(pSrcB + 2);  
  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* load imaginary number from soruceA */  
	imagA1 = *(pSrcA + 1);  
	/* pack two real numbers */  
	real2 = __PKHBT((q15_t)inB1, (q15_t)inB2, 16);  
	/* load imagniary number from sorceB */  
	imagB1 = *(pSrcB + 1);  
	/* pack two imaginary numbers */  
	imag1 = __PKHBT(imagA1, (q15_t)(inA2 >> 16), 16);  
  
#else  
  
	/* load real number from soruceA */  
	realA1 = *(pSrcA);  
	/* pack two imagnianry numbers */  
	imag2 = __PKHBT((q15_t)inB1, (q15_t)inB2, 16);  
	/* load real number from sourceB */  
	realB1 = *(pSrcB);  
	/* pack two real numbers */  
	real1 = __PKHBT(realA1, (q15_t)(inA2 >> 16), 16);  
  
#endif	  //	#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* load two numbers at a time from soruceA */  
	inA1 = _SIMD32_OFFSET(pSrcA + 4);  
  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* pack two imaginary numbers */  
	imag2 = __PKHBT(imagB1, (q15_t)(inB2 >> 16), 16);  
  
#else  
  
	/* pack two real numbers */  
	real2 = __PKHBT(realB1, (q15_t)(inB2 >> 16), 16);  
  
#endif	  //	#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* multiply accumulate imaginary numbers */  
	imag_sum = __SMLALD(imag1, imag2, imag_sum);
  
	/* load two numbers at a time from sourceA */  
	inA2 = _SIMD32_OFFSET(pSrcA + 6);  
	/* multiply accumulate real numbers */  
	real_sum = __SMLALD(real1, real2, real_sum);
	/* laod two numbers at a time from sourceB */  
	inB1 = _SIMD32_OFFSET(pSrcB + 4);  
  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* pack two real numbers */  
	real1 = __PKHBT((q15_t)inA1, (q15_t)inA2, 16);  
  
#else  
  
	/* pack two imagninary numbers */  
	imag1 = __PKHBT((q15_t)inA1, (q15_t)inA2, 16);  
  
#endif	  //	#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* load two numbers at a time from sourceB */  
	inB2 = _SIMD32_OFFSET(pSrcB + 6);  
  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* load imagniary number from sourceA */  
	imagA1 = *(pSrcA + 5);  
	/* pack two real numbers */  
	real2 = __PKHBT((q15_t)inB1, (q15_t)inB2, 16);  
	/* load imaginary numnber from sourceB */  
	imagB1 = *(pSrcB + 5);  
	/* pack two imaginary numbers */  
	imag1 = __PKHBT(imagA1, (q15_t)(inA2 >> 16), 16);  
	imag2 = __PKHBT(imagB1, (q15_t)(inB2 >> 16), 16);  
  
#else  
  
	/* load real number from soruceA */  
	realA1 = *(pSrcA + 4);  
	/* pack two imaginary numbers */  
	imag2 = __PKHBT((q15_t)inB1, (q15_t)inB2, 16);  
	/* load real number from sourceB */  
	realB1 = *(pSrcB + 4);  
	/* pack two real numbers */  
	real1 = __PKHBT(realA1, (q15_t)(inA2 >> 16), 16);  
	real2 = __PKHBT(realB1, (q15_t)(inB2 >> 16), 16);  
  
#endif	  //	#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* multiply and accumulate imaginary numbers */  
	imag_sum = __SMLALD(imag1, imag2, imag_sum);
	/* multiply and accumulate real numbers */  
	real_sum = __SMLALD(real1, real2, real_sum);
  
	/* increment sourceA buffer */  
	pSrcA += 8u;  
	/* increment sourceB buffer */  
	pSrcB += 8u;  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the numSamples is not a multiple of 4, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = numSamples % 0x4u;     
     
  while(blkCnt > 0u)     
  {     
    /* CReal = A[0]* B[0] + A[2]* B[2] + A[4]* B[4] + .....+ A[numSamples-2]* B[numSamples-2] */     
    real_sum += ((q31_t) * pSrcA++ * *pSrcB++);     
    /* CImag = A[1]* B[1] + A[3]* B[3] + A[5]* B[5] + .....+ A[numSamples-1]* B[numSamples-1] */     
    imag_sum += ((q31_t) * pSrcA++ * *pSrcB++);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Store the real and imaginary results in 8.24 format  */     
  /* Convert real data in 34.30 to 8.24 by 6 right shifts */     
  *realResult = (q31_t) (real_sum) >> 6;     
  /* Convert imaginary data in 34.30 to 8.24 by 6 right shifts */     
  *imagResult = (q31_t) (imag_sum) >> 6;     
}     
     
/**      
 * @} end of cmplx_dot_prod group      
 */     
