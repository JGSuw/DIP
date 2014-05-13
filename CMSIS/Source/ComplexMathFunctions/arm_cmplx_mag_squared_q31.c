/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_cmplx_mag_squared_q31.c      
*      
* Description:	Q31 complex magnitude squared.      
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
 * @addtogroup cmplx_mag_squared      
 * @{      
 */     
     
     
/**      
 * @brief  Q31 complex magnitude squared      
 * @param  *pSrc points to the complex input vector      
 * @param  *pDst points to the real output vector      
 * @param  numSamples number of complex samples in the input vector      
 * @return none.      
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function implements 1.31 by 1.31 multiplications and finally output is converted into 3.29 format.      
 * Input down scaling is not required.      
 */     
     
void arm_cmplx_mag_squared_q31(     
  q31_t * pSrc,     
  q31_t * pDst,     
  uint32_t numSamples)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t real1, real2, imag1, imag2;				 /* temporary variables to hold input data */  
  q31_t real3, real4, imag3, imag4;				 /* Temporary variables to hold input data */  
  q31_t out1, out2;								 /* temporary variabels to hold output data */  
  
  /* loop Unrolling */     
  blkCnt = numSamples >> 2u;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 3 samples. */     
  while(blkCnt > 0u)     
  {  
	/* read complex data from soruce buffer */  
	real1 = pSrc[0];  
	imag1 = pSrc[1];  
	real2 = pSrc[2];  
	imag2 = pSrc[3];  
  
	/* calculate power in 2.30 format */  
	real1 = (q31_t)(((q63_t) real1 * real1) >> 32);  
	imag1 = (q31_t)(((q63_t) imag1 * imag1) >> 32);  
	real2 = (q31_t)(((q63_t) real2 * real2) >> 32);  
	imag2 = (q31_t)(((q63_t) imag2 * imag2) >> 32);  
  
	/* read complex data from soruce buffer */  
	real3 = pSrc[4];  
	imag3 = pSrc[5];  
	real4 = pSrc[6];  
	imag4 = pSrc[7];  
  
	/* calculate power in 2.30 format */  
	real3 = (q31_t)(((q63_t) real3 * real3) >> 32);  
	imag3 = (q31_t)(((q63_t) imag3 * imag3) >> 32);  
	real4 = (q31_t)(((q63_t) real4 * real4) >> 32);  
	imag4 = (q31_t)(((q63_t) imag4 * imag4) >> 32);  
  
	/* get the result in 3.29 format */  
	real1 = (real1 >> 1);  
	imag1 = (imag1 >> 1);  
	real2 = (real2 >> 1);  
	imag2 = (imag2 >> 1);  
  
	/* accumulate real and imaginary powers */  
	out1 = real1 + imag1;  
	out2 = real2 + imag2;  
  
  
	/* get the result in 3.29 format */  
	real3 = (real3 >> 1);  
	imag3 = (imag3 >> 1);  
	real4 = (real4 >> 1);  
  
	/* store the result to destination buffer */  
	pDst[0] = out1;  
	  
	/* get the result in 3.29 format */  
	imag4 = (imag4 >> 1);  
	  
	/* store the result to destination buffer */  
	pDst[1] = out2;  
  
	/* accumulate real and imaginary powers */  
	out1 = real3 + imag3;  
	out2 = real4 + imag4;  
  
	/* store the result to destination buffer */  
	pDst[2] = out1;  
	  
	/* increment destination buffer by 8 to process next samples */  
	pSrc += 8u;  
	  
	/* store the result to destination buffer */  
	pDst[3] = out2;  
  
	/* increment destination buffer by 4 to process next samples */  
	pDst += 4u;  
   
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the numSamples is not a multiple of 4, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = numSamples % 0x4u;     
     
  while(blkCnt > 0u)     
  {     
    /* C[0] = (A[0] * A[0] + A[1] * A[1]) */     
    real1 = *pSrc++;     
    imag1 = *pSrc++;     
    real1 = (q31_t) (((q63_t) real1 * real1) >> 33);     
    imag1 = (q31_t) (((q63_t) imag1 * imag1) >> 33);     
    /* store the result in 3.29 format in the destination buffer. */     
    *pDst++ = real1 + imag1;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of cmplx_mag_squared group      
 */     
