/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_cmplx_mult_cmplx_q31.c      
*      
* Description:	Q31 complex-by-complex multiplication      
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
 * @brief  Q31 complex-by-complex multiplication      
 * @param[in]  *pSrcA points to the first input vector      
 * @param[in]  *pSrcB points to the second input vector      
 * @param[out]  *pDst  points to the output vector      
 * @param[in]  numSamples number of complex samples in each vector      
 * @return none.      
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function implements 1.31 by 1.31 multiplications and finally output is converted into 3.29 format.      
 * Input down scaling is not required.      
 */     
     
void arm_cmplx_mult_cmplx_q31(     
  q31_t * pSrcA,     
  q31_t * pSrcB,     
  q31_t * pDst,     
  uint32_t numSamples)     
{     
  q31_t a1, b1, c1, d1;                              /* Temporary variables to store real and imaginary values */     
  q31_t a2, b2, c2, d2;                              /* Temporary variables to store real and imaginary values */     
  q31_t out1, out2;  
  q31_t mul1, mul2, mul3, mul4;  
  uint32_t blkCnt;                               /* loop counters */     
     
  /* loop Unrolling */     
  blkCnt = numSamples >> 2u;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 3 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C[2 * i] = A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1].  */     
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i].  */     
	a1 = pSrcA[0];  
	b1 = pSrcA[1];  
	c1 = pSrcB[0];  
	d1 = pSrcB[1];  
  
	mul1 = (q31_t)(((q63_t)a1 * c1) >> 32);  
	mul2 = (q31_t)(((q63_t)b1 * d1) >> 32);  
	mul3 = (q31_t)(((q63_t)a1 * d1) >> 32);  
	mul4 = (q31_t)(((q63_t)b1 * c1) >> 32);  
  
	a2 = pSrcA[2];  
	b2 = pSrcA[3];  
	c2 = pSrcB[2];  
	a1 = (mul1 >> 1);  
	d2 = pSrcB[3];  
  
	b1 = (mul2 >> 1);  
	c1 = (mul3 >> 1);  
	d1 = (mul4 >> 1);  
  
	mul1 = (q31_t)(((q63_t)a2 * c2) >> 32);  
	mul2 = (q31_t)(((q63_t)b2 * d2) >> 32);  
	mul3 = (q31_t)(((q63_t)a2 * d2) >> 32);  
	mul4 = (q31_t)(((q63_t)b2 * c2) >> 32);  
  
	out1 = a1 - b1;  
	a1 = pSrcA[4];  
	out2 = c1 + d1;  
	b1 = pSrcA[5];  
	c1 = pSrcB[4];  
	d1 = pSrcB[5];  
  
	pDst[0] = out1;  
  
	a2 = (mul1 >> 1);  
	pDst[1] = out2;  
	b2 = (mul2 >> 1);  
	c2 = (mul3 >> 1);  
	d2 = (mul4 >> 1);  
  
	out1 = a2 - b2;  
	a2 = pSrcA[6];  
	out2 = c2 + d2;  
  
	mul1 = (q31_t)(((q63_t)a1 * c1) >> 32);  
	mul2 = (q31_t)(((q63_t)b1 * d1) >> 32);  
	mul3 = (q31_t)(((q63_t)a1 * d1) >> 32);  
	mul4 = (q31_t)(((q63_t)b1 * c1) >> 32);  
  
	b2 = pSrcA[7];  
	c2 = pSrcB[6];  
	d2 = pSrcB[7];  
  
	pDst[2] = out1;  
	a1 = (mul1 >> 1);  
	pDst[3] = out2;  
	b1 = (mul2 >> 1);  
	c1 = (mul3 >> 1);  
	d1 = (mul4 >> 1);  
  
	out1 = a1 - b1;  
	out2 = c1 + d1;  
  
	mul1 = (q31_t)(((q63_t)a2 * c2) >> 32);  
	mul2 = (q31_t)(((q63_t)b2 * d2) >> 32);  
	mul3 = (q31_t)(((q63_t)a2 * d2) >> 32);  
	mul4 = (q31_t)(((q63_t)b2 * c2) >> 32);  
  
	pDst[4] = out1;  
	pSrcA += 8u;  
	pDst[5] = out2;  
	pSrcB += 8u;  
  
	a2 = (mul1 >> 1);  
	b2 = (mul2 >> 1);  
	c2 = (mul3 >> 1);  
	d2 = (mul4 >> 1);  
  
	out1 = a2 - b2;  
	out2 = c2 + d2;  
  
	pDst[6] = out1;  
	pDst[7] = out2;  
  
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
     
    /* store the result in 3.29 format in the destination buffer. */     
    *pDst++ = (q31_t) ((((q63_t) a1 * c1) >> 33) - (((q63_t) b1 * d1) >> 33));     
    /* store the result in 3.29 format in the destination buffer. */     
    *pDst++ = (q31_t) ((((q63_t) a1 * d1) >> 33) + (((q63_t) b1 * c1) >> 33));     
     
    /* Decrement the blockSize loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of CmplxByCmplxMult group      
 */     
