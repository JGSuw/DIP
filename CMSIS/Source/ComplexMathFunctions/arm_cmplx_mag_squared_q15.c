/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_cmplx_mag_squared_q15.c      
*      
* Description:	Q15 complex magnitude squared.      
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
 * @addtogroup cmplx_mag_squared      
 * @{      
 */     
     
/**      
 * @brief  Q15 complex magnitude squared      
 * @param  *pSrc points to the complex input vector      
 * @param  *pDst points to the real output vector      
 * @param  numSamples number of complex samples in the input vector      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function implements 1.15 by 1.15 multiplications and finally output is converted into 3.13 format.      
 */     
     
void arm_cmplx_mag_squared_q15(     
  q15_t * pSrc,     
  q15_t * pDst,     
  uint32_t numSamples)     
{     
  q31_t in1, in2, in3, in4;						 /* Temporary variables to hold input data */  
  q31_t acc1, acc2, acc3, acc4;					 /* Temporary accumulators */  
  q15_t out1, out2, out3, out4;					 /* Temporary variables to hold output data */  
  uint32_t blkCnt;                               /* loop counter */     
     
  /*loop Unrolling */     
  blkCnt = numSamples >> 2u;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 3 samples. */     
  while(blkCnt > 0u)     
  {    
	/* read complex input from source buffer */  
	in1 = _SIMD32_OFFSET(pSrc);  
	in2 = _SIMD32_OFFSET(pSrc + 2);  
	in3 = _SIMD32_OFFSET(pSrc + 4);  
	in4 = _SIMD32_OFFSET(pSrc + 6);  
  
	/* calculate powers of real and imaginary values and accumulate */  
	acc1 = __SMUAD(in1, in1);  
	acc2 = __SMUAD(in2, in2);  
	acc3 = __SMUAD(in3, in3);  
	acc4 = __SMUAD(in4, in4);  
  
	/* get the output to 3.13 format */  
	out1 = (q15_t)(acc1 >> 17);  
	out2 = (q15_t)(acc2 >> 17);  
	out3 = (q15_t)(acc3 >> 17);  
	out4 = (q15_t)(acc4 >> 17);  
  
	/* packed output data for SIMD store */  
#ifndef ARM_MATH_BIG_ENDIAN  
  
 	acc1 = __PKHBT(out1, out2, 16);  
	acc2 = __PKHBT(out3, out4, 16);  
  
#else  
	  
 	acc1 = __PKHBT(out2, out1, 16);  
	acc2 = __PKHBT(out4, out3, 16);  
  
#endif		//	#ifndef ARM_MATH_BIG_ENDIAN	    
  
	/* store result to destination buffer */  
	_SIMD32_OFFSET(pDst) = acc1;  
	_SIMD32_OFFSET(pDst + 2) = acc2;  
  
	/* increment source pointer by 8 to process next samples */  
	pSrc += 8u;  
	/* increment destination pointer by 4 to process next samples */  
	pDst += 4u;  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the numSamples is not a multiple of 4, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = numSamples % 0x4u;     
     
  while(blkCnt > 0u)     
  {     
    /* C[0] = (A[0] * A[0] + A[1] * A[1]) */     
	in1 = *__SIMD32(pSrc)++;  
	acc1 = __SMUAD(in1, in1);  
  
    out1 = (q15_t)(acc1 >> 17);  
	  
	/* store the result in 3.13 format in the destination buffer. */     
    *pDst++ = out1;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of cmplx_mag_squared group      
 */     
