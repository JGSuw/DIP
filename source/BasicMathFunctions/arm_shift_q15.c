/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_shift_q15.c      
*      
* Description:	Shifts the elements of a Q15 vector by a specified number of bits.      
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
 * @addtogroup shift      
 * @{      
 */     
     
/**      
 * @brief  Shifts the elements of a Q15 vector a specified number of bits.      
 * @param[in]  *pSrc points to the input vector      
 * @param[in]  shiftBits number of bits to shift.  A positive value shifts left; a negative value shifts right.      
 * @param[out]  *pDst points to the output vector      
 * @param[in]  blockSize number of samples in the vector      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function uses saturating arithmetic.      
 * Results outside of the allowable Q15 range [0x8000 0x7FFF] will be saturated.      
 */     
     
void arm_shift_q15(     
  q15_t * pSrc,     
  int8_t shiftBits,     
  q15_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  uint8_t sign;                                  /* Sign of shiftBits */     
  q15_t in1, in2, in3, in4;                      /* Temporary variables */     
     
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* Getting the sign of shiftBits */     
  sign = (shiftBits & 0x80);     
     
  /* If the shift value is positive then do right shift else left shift */     
  if(sign == 0u)     
  {     
    /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
     ** a second loop below computes the remaining 1 to 7 samples. */     
    while(blkCnt > 0u)     
    {     
      /* Read 2 inputs */     
      in1 = *pSrc;     
      in2 = *(pSrc + 1);     
      in3 = *(pSrc + 2);     
      in4 = *(pSrc + 3);     
  
      /* C = A << shiftBits */     
      /* Shift the inputs and then store the results in the destination buffer. */     
#ifndef  ARM_MATH_BIG_ENDIAN   
   
#ifdef CCS   
      *__SIMD32(pDst)++ = __PKHBT(__SSATA((in1 << shiftBits), 0, 16),     
                                  __SSATA((in2 << shiftBits), 0, 16), 16);     
      *__SIMD32(pDst)++ = __PKHBT(__SSATA((in3 << shiftBits), 0, 16),     
                                  __SSATA((in4 << shiftBits), 0, 16), 16);     
#else   
      *__SIMD32(pDst)++ = __PKHBT(__SSAT((in1 << shiftBits), 16),     
                                  __SSAT((in2 << shiftBits), 16), 16);     
      *__SIMD32(pDst)++ = __PKHBT(__SSAT((in3 << shiftBits), 16),     
                                  __SSAT((in4 << shiftBits), 16), 16);     
#endif	//	#ifdef CCS     
   
#else   
   
#ifdef CCS   
      *__SIMD32(pDst)++ = __PKHBT(__SSATA((in2 << shiftBits), 0, 16),
                                  __SSATA((in1 << shiftBits), 0, 16), 16);
      *__SIMD32(pDst)++ = __PKHBT(__SSATA((in4 << shiftBits), 0, 16),
                                  __SSATA((in3 << shiftBits), 0, 16), 16);
#else   
      *__SIMD32(pDst)++ = __PKHBT(__SSAT((in2 << shiftBits), 16),   
                                  __SSAT((in1 << shiftBits), 16), 16);   
      *__SIMD32(pDst)++ = __PKHBT(__SSAT((in4 << shiftBits), 16),   
                                  __SSAT((in3 << shiftBits), 16), 16);   
#endif //	#ifdef CCS   
   
#endif /* #ifndef  ARM_MATH_BIG_ENDIAN    */  
      in1 = *(pSrc + 4);      
      in2 = *(pSrc + 5);     
      in3 = *(pSrc + 6);     
      in4 = *(pSrc + 7);     
  
      /* C = A << shiftBits */     
      /* Shift the inputs and then store the results in the destination buffer. */     
#ifndef  ARM_MATH_BIG_ENDIAN   
   
#ifdef CCS   
      *__SIMD32(pDst)++ = __PKHBT(__SSATA((in1 << shiftBits), 0, 16),     
                                  __SSATA((in2 << shiftBits), 0, 16), 16);     
      *__SIMD32(pDst)++ = __PKHBT(__SSATA((in3 << shiftBits), 0, 16),     
                                  __SSATA((in4 << shiftBits), 0, 16), 16);     
#else   
      *__SIMD32(pDst)++ = __PKHBT(__SSAT((in1 << shiftBits), 16),     
                                  __SSAT((in2 << shiftBits), 16), 16);     
      *__SIMD32(pDst)++ = __PKHBT(__SSAT((in3 << shiftBits), 16),     
                                  __SSAT((in4 << shiftBits), 16), 16);     
#endif	//	#ifdef CCS     
   
#else   
   
#ifdef CCS   
      *__SIMD32(pDst)++ = __PKHBT(__SSATA((in2 << shiftBits), 0, 16),
                                  __SSATA((in1 << shiftBits), 0, 16), 16);
      *__SIMD32(pDst)++ = __PKHBT(__SSATA((in4 << shiftBits), 0, 16),
                                  __SSATA((in3 << shiftBits), 0, 16), 16);
#else   
      *__SIMD32(pDst)++ = __PKHBT(__SSAT((in2 << shiftBits), 16),   
                                  __SSAT((in1 << shiftBits), 16), 16);   
      *__SIMD32(pDst)++ = __PKHBT(__SSAT((in4 << shiftBits), 16),   
                                  __SSAT((in3 << shiftBits), 16), 16);   
#endif //	#ifdef CCS   
   
#endif /* #ifndef  ARM_MATH_BIG_ENDIAN    */     
  
	  /* Update source pointer to process next sampels */  
	  pSrc += 8u;  
  
      /* Decrement the loop counter */     
      blkCnt--;     
    }     
     
    /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
     ** No loop unrolling is used. */     
    blkCnt = blockSize % 0x8u;     
     
    while(blkCnt > 0u)     
    {     
      /* C = A << shiftBits */     
      /* Shift and then store the results in the destination buffer. */    
#ifdef CCS   
      *pDst++ = __SSATA((*pSrc++ << shiftBits), 0, 16);
#else	     
      *pDst++ = __SSAT((*pSrc++ << shiftBits), 16);     
#endif	//	#ifdef CCS     
      /* Decrement the loop counter */     
      blkCnt--;     
    }     
  }     
  else     
  {     
    shiftBits = -shiftBits;  
  
    /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
     ** a second loop below computes the remaining 1 to 7 samples. */     
    while(blkCnt > 0u)     
    {     
      /* Read 2 inputs */     
      in1 = *pSrc;     
      in2 = *(pSrc + 1);     
      in3 = *(pSrc + 2);     
      in4 = *(pSrc + 3);     
  
      /* C = A >> shiftBits */     
      /* Shift the inputs and then store the results in the destination buffer. */  
	       
#ifndef  ARM_MATH_BIG_ENDIAN   
  
      *__SIMD32(pDst)++ = __PKHBT((in1 >> shiftBits),     
    		  	  	  	  	  	  (in2 >> shiftBits), 16);
      *__SIMD32(pDst)++ = __PKHBT((in3 >> shiftBits),     
    		  	  	  	  	  	  (in4 >> shiftBits), 16);
#else   
   
      *__SIMD32(pDst)++ = __PKHBT((in2 >> shiftBits),
    		  	  	  	  	  	  (in1 >> shiftBits), 16);
      *__SIMD32(pDst)++ = __PKHBT((in4 >> shiftBits),
    		  	  	  	  	  	  (in3 >> shiftBits), 16);
   
#endif /* #ifndef  ARM_MATH_BIG_ENDIAN    */   
  
      in1 = *(pSrc + 4);      
      in2 = *(pSrc + 5);     
      in3 = *(pSrc + 6);     
      in4 = *(pSrc + 7);     
  
      /* C = A >> shiftBits */     
      /* Shift the inputs and then store the results in the destination buffer. */  
	       
#ifndef  ARM_MATH_BIG_ENDIAN   
  
      *__SIMD32(pDst)++ = __PKHBT((in1 >> shiftBits),     
                                  (in2 >> shiftBits), 16);     
      *__SIMD32(pDst)++ = __PKHBT((in3 >> shiftBits),     
                                  (in4 >> shiftBits), 16);     
#else   
   
      *__SIMD32(pDst)++ = __PKHBT((in2 >> shiftBits),
    		  	  	  	  	  	  (in1 >> shiftBits), 16);
      *__SIMD32(pDst)++ = __PKHBT((in4 >> shiftBits),
    		  	  	  	  	  	  (in3 >> shiftBits), 16);
   
#endif /* #ifndef  ARM_MATH_BIG_ENDIAN    */   
  
	  pSrc += 8u;  
  
      /* Decrement the loop counter */     
      blkCnt--;     
    }     
     
    /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
     ** No loop unrolling is used. */     
    blkCnt = blockSize % 0x8u;     
     
    while(blkCnt > 0u)     
    {     
      /* C = A >> shiftBits */     
      /* Shift the inputs and then store the results in the destination buffer. */     
	  in1 = *pSrc++;  
  
      *pDst++ = (in1 >> shiftBits);
     
      /* Decrement the loop counter */     
      blkCnt--;     
    }     
  }     
}     
     
/**      
 * @} end of shift group      
 */     
