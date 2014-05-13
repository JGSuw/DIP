/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_cmplx_mag_q31.c      
*      
* Description:	Q31 complex magnitude      
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
 * @addtogroup cmplx_mag      
 * @{      
 */     
     
/**      
 * @brief  Q31 complex magnitude      
 * @param  *pSrc points to the complex input vector      
 * @param  *pDst points to the real output vector      
 * @param  numSamples number of complex samples in the input vector      
 * @return none.      
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function implements 1.31 by 1.31 multiplications and finally output is converted into 2.30 format.      
 * Input down scaling is not required.      
 */     
     
void arm_cmplx_mag_q31(     
  q31_t * pSrc,     
  q31_t * pDst,     
  uint32_t numSamples)     
{     
  q31_t real1, real2, imag1, imag2;              /* Temporary variables to hold input values */     
  q31_t out1, out2, out3, out4;                  /* Accumulators */     
  q63_t mul1, mul2, mul3, mul4;					 /* Temporary variables */  
  uint32_t blkCnt;                               /* loop counter */     
    
     
  /*loop Unrolling */     
  blkCnt = numSamples >> 2u;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 3 samples. */     
  while(blkCnt > 0u)     
  {   
	/* read complex input from source buffer */  
	real1 = pSrc[0];  
	imag1 = pSrc[1];  
	real2 = pSrc[2];  
	imag2 = pSrc[3];  
	  
	/* calculate power of input values */  
	mul1 = (q63_t) real1 * real1;  
	mul2 = (q63_t) imag1 * imag1;  
	mul3 = (q63_t) real2 * real2;  
	mul4 = (q63_t) imag2 * imag2;  
  
	/* get the result to 3.29 format */  
	out1 = (q31_t)(mul1 >> 33);  
	out2 = (q31_t)(mul2 >> 33);  
	out3 = (q31_t)(mul3 >> 33);  
	out4 = (q31_t)(mul4 >> 33);  
  
	/* add real and imaginary accumulators */  
	out1 = out1 + out2;  
	out3 = out3 + out4;  
  
	/* read complex input from source buffer */  
	real1 = pSrc[4];  
	imag1 = pSrc[5];  
	real2 = pSrc[6];  
	imag2 = pSrc[7];  
  
	/* calculate square root */  
	arm_sqrt_q31(out1, &pDst[0]);  
  
	/* calculate power of input values */  
	mul1 = (q63_t) real1 * real1;  
  
	/* calculate square root */  
	arm_sqrt_q31(out3, &pDst[1]);    
	  
	/* calculate power of input values */  
	mul2 = (q63_t) imag1 * imag1;  
	mul3 = (q63_t) real2 * real2;  
	mul4 = (q63_t) imag2 * imag2;  
  
	/* get the result to 3.29 format */  
	out1 = (q31_t)(mul1 >> 33);  
	out2 = (q31_t)(mul2 >> 33);  
	out3 = (q31_t)(mul3 >> 33);  
	out4 = (q31_t)(mul4 >> 33);  
  
	/* add real and imaginary accumulators */  
	out1 = out1 + out2;  
	out3 = out3 + out4;  
  
	/* calculate square root */  
	arm_sqrt_q31(out1, &pDst[2]);  
  
	/* increment destination by 8 to process next samples */  
	pSrc += 8u;		  
  
	/* calculate square root */  
	arm_sqrt_q31(out3, &pDst[3]);  
  
	/* increment destination by 4 to process next samples */  
	pDst += 4u;  
    
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the numSamples is not a multiple of 4, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = numSamples % 0x4u;     
     
  while(blkCnt > 0u)     
  {     
    /* C[0] = sqrt(A[0] * A[0] + A[1] * A[1]) */     
    real1 = *pSrc++;     
    imag1 = *pSrc++;     
    out1 = (q31_t) (((q63_t) real1 * real1) >> 33);     
    out2 = (q31_t) (((q63_t) imag1 * imag1) >> 33);     
    /* store the result in 2.30 format in the destination buffer. */     
    arm_sqrt_q31(out1 + out2, pDst++);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of cmplx_mag group      
 */     
