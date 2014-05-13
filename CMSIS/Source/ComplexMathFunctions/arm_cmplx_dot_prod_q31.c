/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_cmplx_dot_prod_q31.c      
*      
* Description:	Q31 complex dot product      
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
 * @brief  Q31 complex dot product      
 * @param  *pSrcA points to the first input vector      
 * @param  *pSrcB points to the second input vector      
 * @param  numSamples number of complex samples in each vector      
 * @param  *realResult real part of the result returned here      
 * @param  *imagResult imaginary part of the result returned here      
 * @return none.      
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function is implemented using an internal 64-bit accumulator.      
 * The intermediate 1.31 by 1.31 multiplications are performed with 64-bit precision and then shifted to 16.48 format.      
 * The internal real and imaginary accumulators are in 16.48 format and provide 15 guard bits.      
 * Additions are nonsaturating and no overflow will occur as long as <code>numSamples</code> is less than 32768.      
 * The return results <code>realResult</code> and <code>imagResult</code> are in 16.48 format.      
 * Input down scaling is not required.      
 */     
     
void arm_cmplx_dot_prod_q31(     
  q31_t * pSrcA,     
  q31_t * pSrcB,     
  uint32_t numSamples,     
  q63_t * realResult,     
  q63_t * imagResult)     
{     
  q63_t real_sum = 0, imag_sum = 0;              /* Temporary result storage */     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t realA1, realB1;  
  q31_t imagA1, imagB1;    
  q63_t mul1, mul2;  
     
  /*loop Unrolling */     
  blkCnt = numSamples >> 2u;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 3 samples. */     
  while(blkCnt > 0u)     
  {     
	/* read real input from sourceA */  
	realA1 = pSrcA[0];  
	/* read real input from sourecB */  
	realB1 = pSrcB[0];  
	  
	/* multiply real(sourceA) * real(sourceB) inputs */  
	mul1 = ((q63_t)realA1 * realB1);  
  
	/* read imaginary input from sourceA */  
	imagA1 = pSrcA[1];  
	/* read imaginary input from sourceB */  
	imagB1 = pSrcB[1];  
  
	/* multiply imaginary(sourceA) * imaginary(sourceB) inputs */  
	mul2 = ((q63_t)imagA1 * imagB1);  
  
	/* read real input from sourceA */  
	realA1 = pSrcA[2];  
	/* read real input from sourecB */  
	realB1 = pSrcB[2];  
  
	/* shift the result to get 16.48 format */  
	mul1 = mul1 >> 14u;  
	mul2 = mul2 >> 14u;  
  
	/* accumulate real result */  
	real_sum += mul1;  
	/* accumulate imaginary result */  
	imag_sum += mul2;  
  
	/* multiply real(sourceA) * real(sourceB) inputs */  
	mul1 = ((q63_t)realA1 * realB1);  
  
	/* read imaginary input from sourceA */  
	imagA1 = pSrcA[3];  
	/* read imaginary input from sourceB */  
	imagB1 = pSrcB[3];  
  
	/* multiply imaginary(sourceA) * imaginary(sourceB) inputs */  
	mul2 = ((q63_t)imagA1 * imagB1);  
  
	/* read real input from sourceA */  
	realA1 = pSrcA[4];  
	/* read real input from sourecB */  
	realB1 = pSrcB[4];  
  
	/* shift the result to get 16.48 format */  
	mul1 = mul1 >> 14u;  
	mul2 = mul2 >> 14u;  
  
	/* accumulate real result */  
	real_sum += mul1;  
	/* accumulate imaginary result */  
	imag_sum += mul2;  
  
	/* multiply real(sourceA) * real(sourceB) inputs */  
	mul1 = ((q63_t)realA1 * realB1);  
  
	/* read imaginary input from sourceA */  
	imagA1 = pSrcA[5];  
	/* read imaginary input from sourceB */  
	imagB1 = pSrcB[5];  
  
	/* multiply imaginary(sourceA) * imaginary(sourceB) inputs */  
	mul2 = ((q63_t)imagA1 * imagB1);  
  
	/* shift the result to get 16.48 format */  
	mul1 = mul1 >> 14u;  
	mul2 = mul2 >> 14u;  
  
	/* read real input from sourceA */  
	realA1 = pSrcA[6];  
	/* read real input from sourecB */  
	realB1 = pSrcB[6];  
  
	/* accumulate real result */  
	real_sum += mul1;  
	/* accumulate imaginary result */  
	imag_sum += mul2;  
  
	/* multiply real(sourceA) * real(sourceB) inputs */  
	mul1 = ((q63_t)realA1 * realB1);  
  
	/* read imaginary input from sourceA */  
	imagA1 = pSrcA[7];  
	/* read imaginary input from sourceB */  
	imagB1 = pSrcB[7];  
  
	/* multiply imaginary(sourceA) * imaginary(sourceB) inputs */  
	mul2 = ((q63_t)imagA1 * imagB1);  
  
	/* increment pointers by 8 to process next samples */  
	pSrcA += 8u;  
	pSrcB += 8u;  
  
	/* shift the result to get 16.48 format */  
	mul1 = mul1 >> 14u;  
	mul2 = mul2 >> 14u;  
  
	/* accumulate real result */  
	real_sum += mul1;  
	/* accumulate imaginary result */  
	imag_sum += mul2;  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the numSamples  is not a multiple of 4, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = numSamples % 0x4u;     
     
  while(blkCnt > 0u)     
  {     
    /* CReal = A[0]* B[0] + A[2]* B[2] + A[4]* B[4] + .....+ A[numSamples-2]* B[numSamples-2] */     
    real_sum += (q63_t) * pSrcA++ * (*pSrcB++) >> 14;     
    /* CImag = A[1]* B[1] + A[3]* B[3] + A[5]* B[5] + .....+ A[numSamples-1]* B[numSamples-1] */     
    imag_sum += (q63_t) * pSrcA++ * (*pSrcB++) >> 14;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Store the real and imaginary results in 16.48 format  */     
  *realResult = real_sum;     
  *imagResult = imag_sum;     
}     
     
/**      
 * @} end of cmplx_dot_prod group      
 */     
