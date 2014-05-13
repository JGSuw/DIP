/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_cmplx_mult_cmplx_q15.c      
*      
* Description:	Q15 complex-by-complex multiplication      
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
 * @addtogroup CmplxByCmplxMult      
 * @{      
 */     
     
/**      
 * @brief  Q15 complex-by-complex multiplication      
 * @param[in]  *pSrcA points to the first input vector      
 * @param[in]  *pSrcB points to the second input vector      
 * @param[out]  *pDst  points to the output vector      
 * @param[in]  numSamples number of complex samples in each vector      
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
     
void arm_cmplx_mult_cmplx_q15(     
  q15_t * pSrcA,     
  q15_t * pSrcB,     
  q15_t * pDst,     
  uint32_t numSamples)     
{  
  q15_t a1, b1, c1, d1;                          /* Temporary variables to store real and imaginary values */     
  q15_t a2, b2, c2, d2;                          /* Temporary variables to store real and imaginary values */     
  q15_t out1, out2, out3, out4;  
    
  uint32_t blkCnt;                               /* loop counters */     
     
  /* loop Unrolling */     
  blkCnt = numSamples >> 2u;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 3 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C[2 * i] = A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1].  */     
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i].  */   
    a1 = *pSrcA;     
    c1 = *pSrcB;     
    b1 = *(pSrcA + 1);     
    d1 = *(pSrcB + 1);     
     
    /* store the result in 3.13 format in the destination buffer. */     
    out1 =     
      (q15_t) (q31_t) (((q31_t) a1 * c1) >> 17) - (((q31_t) b1 * d1) >> 17);     
    /* store the result in 3.13 format in the destination buffer. */     
    out2 =     
      (q15_t) (q31_t) (((q31_t) a1 * d1) >> 17) + (((q31_t) b1 * c1) >> 17);     
     
    a2 = *(pSrcA + 2);     
    c2 = *(pSrcB + 2);     
    b2 = *(pSrcA + 3);     
    d2 = *(pSrcB + 3);     
     
    /* store the result in 3.13 format in the destination buffer. */     
    out3 =     
      (q15_t) (q31_t) (((q31_t) a2 * c2) >> 17) - (((q31_t) b2 * d2) >> 17);     
    /* store the result in 3.13 format in the destination buffer. */     
    out4 =     
      (q15_t) (q31_t) (((q31_t) a2 * d2) >> 17) + (((q31_t) b2 * c2) >> 17);     
     
    a1 = *(pSrcA + 4);     
    c1 = *(pSrcB + 4);     
    b1 = *(pSrcA + 5);     
    d1 = *(pSrcB + 5);   
	  
	*pDst = out1;  
	*(pDst + 1) = out2;  
	*(pDst + 2) = out3;  
	*(pDst + 3) = out4;		    
     
    /* store the result in 3.13 format in the destination buffer. */     
    out1 =     
      (q15_t) (q31_t) (((q31_t) a1 * c1) >> 17) - (((q31_t) b1 * d1) >> 17);     
    /* store the result in 3.13 format in the destination buffer. */     
    out2 =     
      (q15_t) (q31_t) (((q31_t) a1 * d1) >> 17) + (((q31_t) b1 * c1) >> 17);     
     
    a2 = *(pSrcA + 6);     
    c2 = *(pSrcB + 6);     
    b2 = *(pSrcA + 7);     
    d2 = *(pSrcB + 7);     
     
    /* store the result in 3.13 format in the destination buffer. */     
    out3 =     
      (q15_t) (q31_t) (((q31_t) a2 * c2) >> 17) - (((q31_t) b2 * d2) >> 17);     
    /* store the result in 3.13 format in the destination buffer. */     
    out4 =     
      (q15_t) (q31_t) (((q31_t) a2 * d2) >> 17) + (((q31_t) b2 * c2) >> 17);     
  
	  
	*(pDst + 4) = out1;  
	*(pDst + 5) = out2;  
	pSrcA += 8u;  
	*(pDst + 6) = out3;  
	*(pDst + 7) = out4;  
	pSrcB += 8u;  
	pDst += 8u;  
  
    /* Decrement the blockSize loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = numSamples % 0x4u;     
     
  while(blkCnt > 0u)     
  {     
    /* C[2 * i] = A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1].  */     
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i].  */     
    a1 = *pSrcA++;     
    b1 = *pSrcA++;     
    c1 = *pSrcB++;     
    d1 = *pSrcB++;     
     
    /* store the result in 3.13 format in the destination buffer. */     
    *pDst++ =     
      (q15_t) (q31_t) (((q31_t) a1 * c1) >> 17) - (((q31_t) b1 * d1) >> 17);     
    /* store the result in 3.13 format in the destination buffer. */     
    *pDst++ =     
      (q15_t) (q31_t) (((q31_t) a1 * d1) >> 17) + (((q31_t) b1 * c1) >> 17);     
     
    /* Decrement the blockSize loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of CmplxByCmplxMult group      
 */     
