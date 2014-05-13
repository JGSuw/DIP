/* ----------------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_q7_to_q15.c      
*      
* Description:	Converts the elements of the Q7 vector to Q15 vector.      
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
 * @ingroup groupSupport      
 */     
     
/**      
 * @addtogroup q7_to_x      
 * @{      
 */     
     
     
     
     
/**      
 * @brief Converts the elements of the Q7 vector to Q15 vector.      
 * @param[in]       *pSrc points to the Q7 input vector      
 * @param[out]      *pDst points to the Q15 output vector     
 * @param[in]       blockSize length of the input vector      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 * \par Description:      
 *      
 * The equation used for the conversion process is:      
 *     
 * <pre>      
 * 	pDst[n] = (q15_t) pSrc[n] << 8;   0 <= n < blockSize.      
 * </pre>      
 *     
 */     
     
     
void arm_q7_to_q15(     
  q7_t * pSrc,     
  q15_t * pDst,     
  uint32_t blockSize)     
{     
  q7_t *pIn = pSrc;                              /* Src pointer */     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t in;  
  q31_t in1, in2;  
  q31_t out1, out2;  
  q31_t and = 0xFF00FF00;  
  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = (q15_t) A << 8 */     
    /* convert from q7 to q15 and then store the results in the destination buffer */  
	/* read 4 samples at a time */     
	in = *__SIMD32(pIn)++;  
  
#ifdef CCS  
  
	/* rotatate in by 8 and extend two q7_t values to q15_t values */  
	in1 = __SXTB16(in, 8);  
  
	/* extend remainig two q7_t values to q15_t values */  
	in2 = __SXTB16(in, 0);  
  
#else  
  
	/* rotatate in by 8 and extend two q7_t values to q15_t values */  
	in1 = __SXTB16(__ROR(in, 8));  
  
	/* extend remainig two q7_t values to q15_t values */  
	in2 = __SXTB16(in);  
  
  
#endif	/* shift in1 by 8 to convert q7_t value to q15_t value (ex: 0x00ff00ff ==> 0xff00ff00*/  
	in1 = in1 << 8u;  
	in2 = in2 << 8u;  
  
	/* read next 4 sampels */  
	in = *__SIMD32(pIn)++;  
  
	/* anding with 0xff00ff00 */  
	in1 =  in1 & and;  
	out2 = in2 & and;  
  
	/* pack two 16 bit values */  
	out1 = __PKHTB(in1, out2, 16);  
	out2 = __PKHBT(out2, in1, 16);  
  
#ifndef ARM_MATH_BIG_ENDIAN	  
	  
	/* store two q15_t samples at a time to destination */  
	_SIMD32_OFFSET(pDst + 2) = out1;  
  
#ifdef CCS  
  
	/* rotatate in by 8 and extend two q7_t values to q15_t values */  
	in1 = __SXTB16(in, 8);  
  
#else  
  
	/* rotatate in by 8 and extend two q7_t values to q15_t values */  
	in1 = __SXTB16(__ROR(in, 8));  
  
#endif  
  
	/* store two q15_t samples at a time to destination */  
	_SIMD32_OFFSET(pDst) = out2;  
  
#else  
  
	/* store two q15_t samples at a time to destination */  
	_SIMD32_OFFSET(pDst) = out1;  
  
#ifdef CCS  
  
	/* rotatate in by 8 and extend two q7_t values to q15_t values */  
	in1 = __SXTB16(in, 8);  
  
#else  
  
	/* rotatate in by 8 and extend two q7_t values to q15_t values */  
	in1 = __SXTB16(__ROR(in, 8));  
  
#endif  
  
	/* store two q15_t samples at a time to destination */  
	_SIMD32_OFFSET(pDst + 2) = out2;  
  
#endif	 	//	#ifndef ARM_MATH_BIG_ENDIAN  
  
#ifdef CCS  
  
	/* rotatate in by 8 and extend two q7_t values to q15_t values */  
	in2 = __SXTB16(in, 0);  
  
#else  
  
	/* rotatate in by 8 and extend two q7_t values to q15_t values */  
	in2 = __SXTB16(in);  
  
#endif  
  
	/* shift in1 by 8 to convert q7_t value to q15_t value (ex: 0x00ff00ff ==> 0xff00ff00*/  
	in1 = in1 << 8u;  
	in2 = in2 << 8u;  
  
	/* anding with 0xff00ff00 */  
	out1 = in1 & and;  
	out2 = in2 & and;  
  
	/* pack two 16 bit values */  
	out1 = __PKHTB(in1, out2, 16);  
	out2 = __PKHBT(out2, in1, 16);  
  
	/* store two q15_t samples at a time to destination */  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	_SIMD32_OFFSET(pDst + 6) = out1;  
	_SIMD32_OFFSET(pDst + 4) = out2;  
  
#else  
  
	_SIMD32_OFFSET(pDst + 4) = out1;  
	_SIMD32_OFFSET(pDst + 6) = out2;  
  
#endif	 	//	#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* incremnet destination pointer */  
	pDst += 8u;  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = (q15_t) A << 8 */     
    /* convert from q7 to q15 and then store the results in the destination buffer */     
    *pDst++ = (q15_t) * pIn++ << 8;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
}     
     
/**      
 * @} end of q7_to_x group      
 */     
