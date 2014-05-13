/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_add_q7.c      
*      
* Description:	Q7 vector addition.      
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
 * @addtogroup BasicAdd      
 * @{      
 */     
     
/**      
 * @brief Q7 vector addition.      
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
 * Results outside of the allowable Q7 range [0x80 0x7F] will be saturated.      
 */     
     
void arm_add_q7(     
  q7_t * pSrcA,     
  q7_t * pSrcB,     
  q7_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t inA1, inA2, inB2, inB1;					 /* temporary input variables */  
  q31_t out1, out2, out3, out4;					 /* temporary output variables */  
     
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 4u;  
    
  /* First part of the processing with loop unrolling.  Compute 16 outputs at a time.      
   ** a second loop below computes the remaining 1 to 15 samples. */     
  while(blkCnt)     
  {     
    /* C = A + B */     
    /* Add and then store the results in the destination buffer. */  
	/* read four input samples at a time from sourceA*/     
	inA1 = _SIMD32_OFFSET(pSrcA);  
	/* read four input samples at a time from sourceB*/     
	inB1 = _SIMD32_OFFSET(pSrcB);  
	/* read four input samples at a time from sourceA*/     
	inA2 = _SIMD32_OFFSET(pSrcA + 4);  
  
	/* add, saturate and store four samples to destination at a time*/  
	out1 = __QADD8(inA1, inB1);  
  
	/* read four input samples at a time */  
	inB2 = _SIMD32_OFFSET(pSrcB + 4);  
  
	/* store four samples at a time to destination */  
	_SIMD32_OFFSET(pDst) = out1;  
  
	/* add, saturate and store four samples to destination at a time*/  
	out2 = __QADD8(inA2, inB2);  
  
	/* read four input samples at a time from sourceA*/     
	inA1 = _SIMD32_OFFSET(pSrcA + 8);  
	/* read four input samples at a time from sourceA*/     
	inB1 = _SIMD32_OFFSET(pSrcB + 8);  
	/* read four input samples at a time from sourceA*/     
	inA2 = _SIMD32_OFFSET(pSrcA + 12);  
  
	/* add, saturate and store four samples to destination at a time*/  
	out3 = __QADD8(inA1, inB1);  
  
	/* read four input samples at a time from sourceB*/     
	inB2 = _SIMD32_OFFSET(pSrcB + 12);  
  
	/* increment sourceA pointer by 16 */  
	pSrcA += 16u;  
  
	/* store four samples at a time to destination */  
	_SIMD32_OFFSET(pDst + 4) = out2;  
  
	/* add, saturate and store four samples to destination at a time*/  
	out4 = __QADD8(inA2, inB2);  
  
	/* store four samples at a time to destination */  
	_SIMD32_OFFSET(pDst + 8) = out3;  
  
	/* increment sourecB pointer by 16 */  
	pSrcB += 16u;  
  
	/* store four samples at a time to destination */  
	_SIMD32_OFFSET(pDst + 12) = out4;  
  
	/* incremnet destination pointer by 16 */  
	pDst += 16u;						   
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }    
     
  /* If the blockSize is not a multiple of 16, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x10u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A + B */     
    /* Add and then store the results in the destination buffer. */     
#ifdef CCS   
    *pDst++ = (q7_t) __SSATA(*pSrcA++ + *pSrcB++, 0, 8);     
#else   
    *pDst++ = (q7_t) __SSAT(*pSrcA++ + *pSrcB++, 8);     
#endif // #ifdef CCS	   
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
}     
     
/**      
 * @} end of BasicAdd group      
 */     
