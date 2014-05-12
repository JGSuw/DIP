/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_mult_q7.c      
*      
* Description:	Q7 vector multiplication.      
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
 * @brief           Q7 vector multiplication      
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
     
void arm_mult_q7(     
  q7_t * pSrcA,     
  q7_t * pSrcB,     
  q7_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counters */     
  q7_t inA1, inA2, inA3, inA4; 					 /* temporary input variables */  
  q7_t inB1, inB2, inB3, inB4;					 /* temporary input variables */  
  q15_t out1, out2, out3, out4;					 /* temporary output variables */  
     
  /* loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {  
    /* C = A * B */     
    /* Multiply the inputs and store the results in temporary variables */     
	/* read sample from sourceA */  
 	inA1 = *pSrcA;  
	/* read sample from sourceB */  
	inB1 = *pSrcB;  
	/* read sample from sourceA */  
	inA2 = *(pSrcA + 1);  
	/* read sample from sourceB */  
	inB2 = *(pSrcB + 1);  
  
    /* out = sourceA * sourceB output in q15_t format */  
	out1 = (q15_t)((q7_t) (inA1) * (inB1));     
  
	/* read sample from sourceA */  
	inA3 = *(pSrcA + 2);  
	/* read sample from sourceB */  
	inB3 = *(pSrcB + 2);  
  
    /* out = sourceA * sourceB output in q15_t format */  
    out2 = (q15_t)((q7_t) (inA2) * (inB2));     
  
	/* read sample from sourceA */  
	inA4 = *(pSrcA + 3);  
  
	/* convert output to 1.7 format */  
	out1 = out1 >> 7u;  
  
	/* read sample from sourceB */  
	inB4 = *(pSrcB + 3);  
  
    /* out = sourceA * sourceB output in q15_t format */  
    out3 = (q15_t)((q7_t) (inA3) * (inB3));     
    out4 = (q15_t)((q7_t) (inA4) * (inB4));     
  
	/* convert output to 1.7 format */  
	out2 = out2 >> 7u;  
  
	/* read sample from sourceA */  
	inA1 = *(pSrcA + 4);  
  
	/* convert output to 1.7 format */  
	out3 = out3 >> 7u;  
  
	/* read sample from sourceB */  
	inB1 = *(pSrcB + 4);  
  
	/* convert output to 1.7 format */  
	out4 = out4 >> 7u;  
  
	/* saturate the result */  
#ifdef CCS  
  
	inA3 = (q7_t) __SSATA(out1, 0, 8);  
	inA4 = (q7_t) __SSATA(out2, 0, 8);  
	inB3 = (q7_t) __SSATA(out3, 0, 8);  
	inB4 = (q7_t) __SSATA(out4, 0, 8);  
  
#else  
  
	inA3 = (q7_t) __SSAT(out1, 8);  
	inA4 = (q7_t) __SSAT(out2, 8);  
	inB3 = (q7_t) __SSAT(out3, 8);  
	inB4 = (q7_t) __SSAT(out4, 8);  
  
#endif	 //	#ifdef CCS  
  
    /* Store the results of 4 inputs in the destination buffer in single cycle by packing */     
    *__SIMD32(pDst)++ = __PACKq7(inA3, inA4, inB3, inB4);  
  
	/* read sample from sourceA */  
	inA2 = *(pSrcA + 5);  
	/* read sample from sourceB */  
	inB2 = *(pSrcB + 5);  
  
    /* out = sourceA * sourceB output in q15_t format */  
    out1 = (q15_t)((q7_t) (inA1) * (inB1));     
  
	/* read sample from sourceA */  
	inA3 = *(pSrcA + 6);  
	/* read sample from sourceB */  
	inB3 = *(pSrcB + 6);  
  
    /* out = sourceA * sourceB output in q15_t format */  
    out2 = (q15_t)((q7_t) (inA2) * (inB2));     
  
	/* read sample from sourceA */  
	inA4 = *(pSrcA + 7);  
  
	/* convert output to 1.7 format */  
	out1 = out1 >> 7u;  
  
	/* read sample from sourceB */  
	inB4 = *(pSrcB + 7);  
  
    /* out = sourceA * sourceB output in q15_t format */  
    out3 = (q15_t)((q7_t) (inA3) * (inB3));     
    out4 = (q15_t)((q7_t) (inA4) * (inB4));     
  
	/* convert output to 1.7 format */  
	out2 = out2 >> 7u;  
	out3 = out3 >> 7u;  
	out4 = out4 >> 7u;  
  
	/* saturate the result */  
#ifdef CCS  
  
	inA1 = (q7_t) __SSATA(out1, 0, 8);  
	inA2 = (q7_t) __SSATA(out2, 0, 8);  
	inA3 = (q7_t) __SSATA(out3, 0, 8);  
	inA4 = (q7_t) __SSATA(out4, 0, 8);  
  
#else  
  
	inA1 = (q7_t) __SSAT(out1, 8);  
	inA2 = (q7_t) __SSAT(out2, 8);  
	inA3 = (q7_t) __SSAT(out3, 8);  
	inA4 = (q7_t) __SSAT(out4, 8);  
  
#endif	//	#ifdef CCS  
  
    /* Store the results of 4 inputs in the destination buffer in single cycle by packing */     
    *__SIMD32(pDst)++ = __PACKq7(inA1, inA2, inA3, inA4);  
  
	/* increment sourceA by 8 to process next samples */  
	pSrcA += 8u;  
	/* increment sourceB by 8 to process next samples */  
	pSrcB += 8u;     
     
    /* Decrement the blockSize loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A * B */     
    /* Multiply the inputs and store the result in the destination buffer */     
    *pDst++ = (q7_t) (((q15_t) (*pSrcA++) * (*pSrcB++)) >> 7);     
     
    /* Decrement the blockSize loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of BasicMult group      
 */     
