/* ----------------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_float_to_q7.c      
*      
* Description:	Converts the elements of the floating-point vector to Q7 vector.     
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
 * @ingroup groupSupport      
 */     
     
/**      
 * @addtogroup float_to_x      
 * @{      
 */     
     
/**      
 * @brief Converts the elements of the floating-point vector to Q7 vector.      
 * @param[in]       *pSrc points to the floating-point input vector      
 * @param[out]      *pDst points to the Q7 output vector     
 * @param[in]       blockSize length of the input vector      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 *\par Description:      
 * \par     
 * The equation used for the conversion process is:      
 * <pre>      
 * 	pDst[n] = (q7_t)(pSrc[n] * 128);   0 <= n < blockSize.      
 * </pre>      
 * \par Scaling and Overflow Behavior:      
 * \par      
 * The function uses saturating arithmetic.      
 * Results outside of the allowable Q7 range [0x80 0x7F] will be saturated.      
 * \note     
 * In order to apply rounding, the library should be rebuilt with the ROUNDING macro       
 * defined in the preprocessor section of project options.       
 */     
     
     
void arm_float_to_q7(     
  float32_t * pSrc,     
  q7_t * pDst,     
  uint32_t blockSize)     
{     
  float32_t *pIn = pSrc;                         /* Src pointer */     
  uint32_t blkCnt;                               /* loop counter */     
     
#ifdef ARM_MATH_ROUNDING     
     
  float32_t in;     
     
#endif     
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 4 samples. */     
  while(blkCnt > 0u)     
  {     
#ifdef ARM_MATH_ROUNDING     
    /* C = A * 128 */     
    /* convert from float to q7 and then store the results in the destination buffer */     
    in = *pIn++;     
    in = (in * 128);     
    in += in > 0 ? 0.5 : -0.5;     
#ifdef CCS   
    *pDst++ = (q7_t) (__SSATA((q15_t) (in), 0, 8));     
#else             
    *pDst++ = (q7_t) (__SSAT((q15_t) (in), 8));   
#endif  //	#ifdef CCS   
     
    in = *pIn++;     
    in = (in * 128);     
    in += in > 0 ? 0.5 : -0.5;     
#ifdef CCS   
    *pDst++ = (q7_t) (__SSATA((q15_t) (in), 0, 8));     
#else             
    *pDst++ = (q7_t) (__SSAT((q15_t) (in), 8));   
#endif  //	#ifdef CCS   
     
    in = *pIn++;     
    in = (in * 128);     
    in += in > 0 ? 0.5 : -0.5;     
#ifdef CCS   
    *pDst++ = (q7_t) (__SSATA((q15_t) (in), 0, 8));     
#else             
    *pDst++ = (q7_t) (__SSAT((q15_t) (in), 8));   
#endif  //	#ifdef CCS   
     
    in = *pIn++;     
    in = (in * 128);     
    in += in > 0 ? 0.5 : -0.5;     
#ifdef CCS   
    *pDst++ = (q7_t) (__SSATA((q15_t) (in), 0, 8));     
#else             
    *pDst++ = (q7_t) (__SSAT((q15_t) (in), 8));   
#endif  //	#ifdef CCS   
  
    in = *pIn++;     
    in = (in * 128);     
    in += in > 0 ? 0.5 : -0.5;     
#ifdef CCS   
    *pDst++ = (q7_t) (__SSATA((q15_t) (in), 0, 8));     
#else             
    *pDst++ = (q7_t) (__SSAT((q15_t) (in), 8));   
#endif  //	#ifdef CCS   
     
    in = *pIn++;     
    in = (in * 128);     
    in += in > 0 ? 0.5 : -0.5;     
#ifdef CCS   
    *pDst++ = (q7_t) (__SSATA((q15_t) (in), 0, 8));     
#else             
    *pDst++ = (q7_t) (__SSAT((q15_t) (in), 8));   
#endif  //	#ifdef CCS   
     
    in = *pIn++;     
    in = (in * 128);     
    in += in > 0 ? 0.5 : -0.5;     
#ifdef CCS   
    *pDst++ = (q7_t) (__SSATA((q15_t) (in), 0, 8));     
#else             
    *pDst++ = (q7_t) (__SSAT((q15_t) (in), 8));   
#endif  //	#ifdef CCS   
     
    in = *pIn++;     
    in = (in * 128);     
    in += in > 0 ? 0.5 : -0.5;     
#ifdef CCS   
    *pDst++ = (q7_t) (__SSATA((q15_t) (in), 0, 8));     
#else             
    *pDst++ = (q7_t) (__SSAT((q15_t) (in), 8));   
#endif  //	#ifdef CCS   
     
#else     
     
    /* C = A * 128 */     
    /* convert from float to q7 and then store the results in the destination buffer */   
#ifdef CCS   
    *pDst++ = __SSATA((q31_t) (*pIn++ * 128.0f), 0, 8);     
    *pDst++ = __SSATA((q31_t) (*pIn++ * 128.0f), 0, 8);     
    *pDst++ = __SSATA((q31_t) (*pIn++ * 128.0f), 0, 8);     
    *pDst++ = __SSATA((q31_t) (*pIn++ * 128.0f), 0, 8);     
    *pDst++ = __SSATA((q31_t) (*pIn++ * 128.0f), 0, 8);     
    *pDst++ = __SSATA((q31_t) (*pIn++ * 128.0f), 0, 8);     
    *pDst++ = __SSATA((q31_t) (*pIn++ * 128.0f), 0, 8);     
    *pDst++ = __SSATA((q31_t) (*pIn++ * 128.0f), 0, 8);     
#else     
    *pDst++ = __SSAT((q31_t) (*pIn++ * 128.0f), 8);     
    *pDst++ = __SSAT((q31_t) (*pIn++ * 128.0f), 8);     
    *pDst++ = __SSAT((q31_t) (*pIn++ * 128.0f), 8);     
    *pDst++ = __SSAT((q31_t) (*pIn++ * 128.0f), 8);   
    *pDst++ = __SSAT((q31_t) (*pIn++ * 128.0f), 8);     
    *pDst++ = __SSAT((q31_t) (*pIn++ * 128.0f), 8);     
    *pDst++ = __SSAT((q31_t) (*pIn++ * 128.0f), 8);     
    *pDst++ = __SSAT((q31_t) (*pIn++ * 128.0f), 8);   
#endif  //	#ifdef CCS   
     
#endif  //	#ifdef ARM_MATH_ROUNDING     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 48 compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
#ifdef ARM_MATH_ROUNDING     
    /* C = A * 128 */     
    /* convert from float to q7 and then store the results in the destination buffer */     
    in = *pIn++;     
    in = (in * 128);     
    in += in > 0 ? 0.5 : -0.5;   
#ifdef CCS   
    *pDst++ = (q7_t) (__SSATA((q15_t) (in), 0, 8));     
#else             
    *pDst++ = (q7_t) (__SSAT((q15_t) (in), 8));   
#endif  //	#ifdef CCS   
     
#else     
     
    /* C = A * 128 */     
    /* convert from float to q7 and then store the results in the destination buffer */     
#ifdef CCS   
    *pDst++ = __SSATA((q31_t) (*pIn++ * 128.0f), 0, 8);     
#else   
    *pDst++ = __SSAT((q31_t) (*pIn++ * 128.0f), 8);     
#endif  //	#ifdef CCS   
   
#endif  //	#ifdef ARM_MATH_ROUNDING     
   
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of float_to_x group      
 */     
