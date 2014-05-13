/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_cmplx_mag_f32.c      
*      
* Description:	Floating-point complex magnitude.      
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
 * @defgroup cmplx_mag Complex Magnitude      
 *      
 * Computes the magnitude of the elements of a complex data vector.      
 *     
 * The <code>pSrc</code> points to the source data and      
 * <code>pDst</code> points to the where the result should be written.      
 * <code>numSamples</code> specifies the number of complex samples      
 * in the input array and the data is stored in an interleaved fashion      
 * (real, imag, real, imag, ...).      
 * The input array has a total of <code>2*numSamples</code> values;      
 * the output array has a total of <code>numSamples</code> values.      
 * The underlying algorithm is used:      
 *      
 * <pre>      
 * for(n=0; n<numSamples; n++) {      
 *     pDst[n] = sqrt(pSrc[(2*n)+0]^2 + pSrc[(2*n)+1]^2);      
 * }      
 * </pre>      
 *      
 * There are separate functions for floating-point, Q15, and Q31 data types.      
 */     
     
/**      
 * @addtogroup cmplx_mag      
 * @{      
 */     
/**      
 * @brief Floating-point complex magnitude.      
 * @param[in]       *pSrc points to complex input buffer      
 * @param[out]      *pDst points to real output buffer      
 * @param[in]       numSamples number of complex samples in the input vector      
 * @return none.      
 *      
 */     
     
     
void arm_cmplx_mag_f32(     
  float32_t * pSrc,     
  float32_t * pDst,     
  uint32_t numSamples)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  float32_t realIn1, realIn2; 					 /* Temporary variable to hold real input values */  
  float32_t imagIn1, imagIn2;  					 /* Temporary variables to hold imaginary input values */     
  float32_t mult1, mult2, mult3, mult4;			 /* Temporary variables to hold power of value */  
  float32_t add1, add2;							 /* Temporary variables */  
     
     
  /*loop Unrolling */     
  blkCnt = numSamples >> 2u;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 3 samples. */     
  while(blkCnt > 0u)     
  {     
	/* C[0] = sqrt(A[0] * A[0] + A[1] * A[1]) */     
	/* read complex input from source */  
    realIn1 = *pSrc;     
    imagIn1 = *(pSrc + 1);   
    realIn2 = *(pSrc + 2);     
    imagIn2 = *(pSrc + 3);   
  
	/* C = A * A calculate power of real and imaginary individually */  
	mult1 = realIn1 * realIn1;    
	mult2 = imagIn1 * imagIn1;  
	mult3 = realIn2 * realIn2;    
	mult4 = imagIn2 * imagIn2;  
  
    /* read real input from source */  
	realIn1 = *(pSrc + 4);     
  
	/* added real and imaginary powers */  
	add1 = mult1 + mult2;  
	add2 = mult3 + mult4;  
  
    /* read imaginary input from source */  
	imagIn1 = *(pSrc + 5);   
	  
	/* calculate power of real input */  
	mult1 = realIn1 * realIn1;    
      
	/* read real input from source */  
	realIn2 = *(pSrc + 6);     
	  
	/* calculate power of imaginary input */  
	mult2 = imagIn1 * imagIn1;  
      
	/* read imaginary input from source */  
	imagIn2 = *(pSrc + 7);   
	  
	/* calulate power of value */  
	mult3 = realIn2 * realIn2;    
	mult4 = imagIn2 * imagIn2;  
  
	/* calculate square root */  
	arm_sqrt_f32(add1, &pDst[0]);  
	  
	/* increment source pointer by 8 to process next samples */  
	pSrc += 8;  
  
	/* calculate square root */  
	arm_sqrt_f32(add2, &pDst[1]);  
  
	/* added real and imaginary powers */  
	add1 = mult1 + mult2;  
	add2 = mult3 + mult4;  
  
	/* calculate square root */  
	arm_sqrt_f32(add1, &pDst[2]);  
	arm_sqrt_f32(add2, &pDst[3]);  
  
	/* increment destination pointer by 4 to process next samples */  
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
    realIn1 = *pSrc++;     
    imagIn1 = *pSrc++;     
    /* store the result in the destination buffer. */     
    arm_sqrt_f32((realIn1 * realIn1) + (imagIn1 * imagIn1), pDst++);    
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of cmplx_mag group      
 */     
