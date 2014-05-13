/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_cmplx_mult_real_q31.c      
*      
* Description:	Q31 complex by real multiplication      
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
 * @brief  Q31 complex-by-real multiplication      
 * @param[in]  *pSrcCmplx points to the complex input vector      
 * @param[in]  *pSrcReal points to the real input vector      
 * @param[out]  *pCmplxDst points to the complex output vector      
 * @param[in]  numSamples number of samples in each vector      
 * @return none.      
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function uses saturating arithmetic.      
 * Results outside of the allowable Q31 range[0x80000000 0x7FFFFFFF] will be saturated.      
 */     
     
void arm_cmplx_mult_real_q31(     
  q31_t * pSrcCmplx,     
  q31_t * pSrcReal,     
  q31_t * pCmplxDst,     
  uint32_t numSamples)     
{     
  q31_t in;                                      /* Temporary variable to store input value */     
  uint32_t blkCnt;                               /* loop counters */     
  q31_t inA1, inA2, inA3, inA4;					 /* Temporary variables to hold input data */  
  q31_t inB1, inB2;								 /* Temporary variabels to hold input data */  
  q31_t out1, out2, out3, out4;					 /* Temporary variables to hold output data */  
     
  /* loop Unrolling */     
  blkCnt = numSamples >> 2u;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 3 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C[2 * i] = A[2 * i] * B[i].            */     
    /* C[2 * i + 1] = A[2 * i + 1] * B[i].        */   
	/* read real input from complex input buffer */  
	inA1 = pSrcCmplx[0];  
	/* read input from real input bufer */  
	inB1 = pSrcReal[0];  
	/* read imaginary input from complex input buffer */  
	inA2 = pSrcCmplx[1];  
	  
	/* multiply complex input with real input */  
	out1 = ((q63_t) inA1 * inB1) >> 32;  
	inA3 = pSrcCmplx[2];  
	out2 = ((q63_t) inA2 * inB1) >> 32;  
	inB2 = pSrcReal[1];  
	inA4 = pSrcCmplx[3];  
	out3 = ((q63_t) inA3 * inB2) >> 32;  
	out4 = ((q63_t) inA4 * inB2) >> 32;  
  
	/* sature the result */  
#if CCS  
  
	out1 = __SSATA(out1, 0, 31);  
	out2 = __SSATA(out2, 0, 31);  
	out3 = __SSATA(out3, 0, 31);  
	out4 = __SSATA(out4, 0, 31);  
  
#else  
  
	out1 = __SSAT(out1, 31);  
	out2 = __SSAT(out2, 31);  
	out3 = __SSAT(out3, 31);  
	out4 = __SSAT(out4, 31);  
  
#endif	//	#ifdef CCS  
  
	inA1 = pSrcCmplx[4];  
	  
	/* get result in 1.31 format */  
	  
	out1 = out1 << 1;  
	inB1 = pSrcReal[2];  
	out2 = out2 << 1;  
	pCmplxDst[0] = out1;  
	out3 = out3 << 1;  
	pCmplxDst[1] = out2;  
	out4 = out4 << 1;  
  
	pCmplxDst[2] = out3;  
	pCmplxDst[3] = out4;  
  
	inA2 = pSrcCmplx[5];  
	out1 = ((q63_t) inA1 * inB1) >> 32;  
	inA3 = pSrcCmplx[6];  
	out2 = ((q63_t) inA2 * inB1) >> 32;  
	inB2 = pSrcReal[3];  
	inA4 = pSrcCmplx[7];  
  
	out3 = ((q63_t) inA3 * inB2) >> 32;  
	out4 = ((q63_t) inA4 * inB2) >> 32;  
  
#if CCS  
  
	out1 = __SSATA(out1, 0, 31);  
	out2 = __SSATA(out2, 0, 31);  
	out3 = __SSATA(out3, 0, 31);  
	out4 = __SSATA(out4, 0, 31);  
  
#else  
  
	out1 = __SSAT(out1, 31);  
	out2 = __SSAT(out2, 31);  
	out3 = __SSAT(out3, 31);  
	out4 = __SSAT(out4, 31);  
  
#endif	//	#ifdef CCS  
  
	out1 = out1 << 1;  
	out2 = out2 << 1;  
	pCmplxDst[4] = out1;  
	out3 = out3 << 1;  
	pCmplxDst[5] = out2;  
	out4 = out4 << 1;  
  
	pCmplxDst[6] = out3;  
	pSrcCmplx += 8u;  
	pCmplxDst[7] = out4;  
  
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
    *pCmplxDst++ = (q31_t) clip_q63_to_q31(((q63_t) * pSrcCmplx++ * in) >> 31);     
    *pCmplxDst++ = (q31_t) clip_q63_to_q31(((q63_t) * pSrcCmplx++ * in) >> 31);     
     
    /* Decrement the numSamples loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of CmplxByRealMult group      
 */     
