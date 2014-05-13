/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_mult_q31.c      
*      
* Description:	Q31 vector multiplication.      
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
 * @brief Q31 vector multiplication.      
 * @param[in]       *pSrcA points to the first input vector      
 * @param[in]       *pSrcB points to the second input vector      
 * @param[out]      *pDst points to the output vector      
 * @param[in]       blockSize number of samples in each vector      
 * @return none.      
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function uses saturating arithmetic.      
 * Results outside of the allowable Q31 range[0x80000000 0x7FFFFFFF] will be saturated.      
 */     
     
void arm_mult_q31(     
  q31_t * pSrcA,     
  q31_t * pSrcB,     
  q31_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counters */     
  q31_t inA1, inA2, inA3, inA4;	 				 /* temporary input variables */  
  q31_t inB1, inB2, inB3, inB4;					 /* temporary input variables */  
  q31_t out1, out2, out3, out4;					 /* temporary output variables */  
     
  /* loop Unrolling */     
  blkCnt = blockSize >> 2u;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 3 samples. */     
  while(blkCnt > 0u)     
  {     
  	/* read sample from sourceA */  
	inA1 = *pSrcA;  
  	/* read sample from sourceB */  
	inB1 = *pSrcB;			     
  	/* read sample from sourceA */  
	inA2 = *(pSrcA + 1);  
  	/* read sample from sourceB */  
	inB2 = *(pSrcB + 1);  
	  
	/* sourceA * sourceB */  
	inA1 = ((q63_t) inA1 * inB1) >> 32;  
  
  	/* read sample from sourceA */  
	inA3 = *(pSrcA + 2);  
  
	/* sourceA * sourceB */  
	inA2 = ((q63_t) inA2 * inB2) >> 32;  
  
  	/* read sample from sourceB */  
	inB3 = *(pSrcB + 2);  
  	/* read sample from sourceA */  
	inA4 = *(pSrcA + 3);  
  
	/* sourceA * sourceB */  
	inA3 = ((q63_t) inA3 * inB3) >> 32;  
  
  	/* read sample from sourceB */  
	inB4 = *(pSrcB + 3);  
  
	/* sourceA * sourceB */  
	inA4 = ((q63_t) inA4 * inB4) >> 32;  
  
  
	/* saturate the result */  
#ifdef CCS  
	out1 = __SSATA(inA1, 0, 31);  
	out2 = __SSATA(inA2, 0, 31);  
	out3 = __SSATA(inA3, 0, 31);  
	out4 = __SSATA(inA4, 0, 31);  
#else  
	out1 = __SSAT(inA1, 31);  
	out2 = __SSAT(inA2, 31);  
	out3 = __SSAT(inA3, 31);  
	out4 = __SSAT(inA4, 31);  
#endif 	//	#ifdef CCS  
  
	/* get the output to 1.31 format */  
	out1 = out1 << 1u;  
	out2 = out2 << 1u;  
  
	/* store result to destination buffer */  
	*pDst = out1;  
  
	/* get the output to 1.31 format */  
	out3 = out3 << 1u;  
  
	/* store result to destination buffer */  
	*(pDst + 1) = out2;  
  
	/* get the output to 1.31 format */  
	out4 = out4 << 1u;  
  
	/* store result to destination buffer */  
	*(pDst + 2) = out3;   
  
	/* incremnet sourceA buffer by 4 to process next samples */  
	pSrcA += 4u;  
  
	/* store result to destination buffer */  
	*(pDst + 3) = out4;   
	  
	/* incremnet sourceB buffer by 4 to process next samples */  
	pSrcB += 4u;  
	/* incremnet destination buffer by 4 to process next samples */  
	pDst += 4u;   
	 
    /* Decrement the blockSize loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x4u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A * B */     
    /* Multiply the inputs and then store the results in the destination buffer. */     
    *pDst++ = (q31_t) clip_q63_to_q31(((q63_t) (*pSrcA++) * (*pSrcB++)) >> 31);     
     
    /* Decrement the blockSize loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of BasicMult group      
 */     
