/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_sub_q31.c      
*      
* Description:	Q31 vector subtraction.      
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
 * @addtogroup BasicSub      
 * @{      
 */     
     
/**      
 * @brief Q31 vector subtraction.      
 * @param[in]       *pSrcA points to the first input vector      
 * @param[in]       *pSrcB points to the second input vector      
 * @param[out]      *pDst points to the output vector      
 * @param[in]       blockSize number of samples in each vector      
 * @return none.      
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function uses saturating arithmetic.      
 * Results outside of the allowable Q31 range [0x80000000 0x7FFFFFFF] will be saturated.      
 */     
     
void arm_sub_q31(     
  q31_t * pSrcA,     
  q31_t * pSrcB,     
  q31_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t inA1, inA2, inA3, inA4;	 				 /* temporary input variables */  
  q31_t inB1, inB2, inB3, inB4;					 /* temporary input variables */  
  q31_t out1, out2, out3, out4;					 /* temporary output variables */  
  q63_t inA, inB, inC, inD;   					 /* temporary input variables */  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A - B */     
    /* Subtract and then store the results in the destination buffer. */     
#ifndef ARM_MATH_BIG_ENDIAN  
  
	inA = _SIMD64_OFFSET(pSrcA);  
	inA1 = (q31_t)inA;  
	inA2 = (q31_t)(inA >> 32);  
	inB = _SIMD64_OFFSET(pSrcB);  
	inB1 = (q31_t)inB;  
	inB2 = (q31_t)(inB >> 32);  
  
#else  
  
	inA = _SIMD64_OFFSET(pSrcA);  
	inA1 = (q31_t)(inA >> 32);  
	inA2 = (q31_t)inA;  
	inB = _SIMD64_OFFSET(pSrcB);  
	inB1 = (q31_t)(inB >> 32);  
	inB2 = (q31_t)inB;  
  
#endif		//	#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* out = saturate(sorceA - sourceB) */  
	out1 = __QSUB(inA1, inB1);  
  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	inC = _SIMD64_OFFSET(pSrcA + 2);  
	inA3 = (q31_t)inC;  
	inA4 = (q31_t)(inC >> 32);  
  
#else  
  
	inC = _SIMD64_OFFSET(pSrcA + 2);  
	inA3 = (q31_t)(inC >> 32);  
	inA4 = (q31_t)inC;  
  
#endif	//	#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* out = saturate(sorceA - sourceB) */  
	out2 = __QSUB(inA2, inB2);  
  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	inD = _SIMD64_OFFSET(pSrcB + 2);  
	inB3 = (q31_t)inD;  
	inB4 = (q31_t)(inD >> 32);  
  
#else  
  
	inD = _SIMD64_OFFSET(pSrcB + 2);  
	inB3 = (q31_t)(inD >> 32);  
 	inB4 = (q31_t)inD;  
  
#endif	//	#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* out = saturate(sorceA - sourceB) */  
	out3 = __QSUB(inA3, inB3);  
  
	/* store result to destination buffer */  
	*pDst = out1;  
	*(pDst + 1) = out2;  
  
	/* out = saturate(sorceA - sourceB) */  
	out4 = __QSUB(inA4, inB4);  
  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	inA = _SIMD64_OFFSET(pSrcA+4);  
	inA1 = (q31_t)inA;  
	inA2 = (q31_t)(inA >> 32);  
  
#else  
  
	inA = _SIMD64_OFFSET(pSrcA+4);  
	inA1 = (q31_t)(inA >> 32);  
	inA2 = (q31_t)inA;  
  
#endif	//	#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* store result to destination buffer */  
	*(pDst + 2) = out3;  
	*(pDst + 3) = out4;  
  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	inB = _SIMD64_OFFSET(pSrcB+4);  
	inB1 = (q31_t)inB;  
	inB2 = (q31_t)(inB >> 32);  
  
#else  
  
	inB = _SIMD64_OFFSET(pSrcB+4);  
	inB1 = (q31_t)(inB >> 32);  
	inB2 = (q31_t)inB;  
  
#endif	//	#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* out = saturate(sorceA - sourceB) */  
	out1 = __QSUB(inA1, inB1);  
  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	inC = _SIMD64_OFFSET(pSrcA+6);  
	inA3 = (q31_t)inC;  
	inA4 = (q31_t)(inC >> 32);  
  
  
	inD = _SIMD64_OFFSET(pSrcB+6);  
	inB3 = (q31_t)inD;  
	inB4 = (q31_t)(inD >> 32);  
  
#else  
  
	inC = _SIMD64_OFFSET(pSrcA+6);  
	inA3 = (q31_t)(inC >> 32);  
	inA4 = (q31_t)inC;  
  
  
	inD = _SIMD64_OFFSET(pSrcB+6);  
	inB3 = (q31_t)(inD >> 32);  
	inB4 = (q31_t)inD;  
  
  
#endif	//	#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* out = saturate(sorceA - sourceB) */  
	out2 = __QSUB(inA2, inB2);  
  
	/* store result to destination buffer */  
	*(pDst + 4) = out1;  
  
	/* out = saturate(sorceA - sourceB) */  
	out3 = __QSUB(inA3, inB3);  
  
	/* increment sourceA pointer by 8 to process next sampels */  
	pSrcA += 8u;  
  
	/* store result to destination buffer */  
	*(pDst + 5) = out2;  
  
	/* out = saturate(sorceA - sourceB) */  
	out4 = __QSUB(inA4, inB4);  
  
	/* store result to destination buffer */  
	*(pDst + 6) = out3;  
	  
	/* Update source pointer to process next sampels */  
	pSrcB += 8u;  
	  
	/* store result to destination buffer */  
	*(pDst + 7) = out4;  
  
	/* Update destination pointer to process next sampels */  
	pDst += 8u;  
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A - B */     
    /* Subtract and then store the result in the destination buffer. */     
	inA1 = *pSrcA++;  
	inB1 = *pSrcB++;  
  
    *pDst++ = __QSUB(inA1, inB1);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of BasicSub group      
 */     
