/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_scale_q7.c      
*      
* Description:	Multiplies a Q7 vector by a scalar.      
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
 * @addtogroup scale      
 * @{      
 */     
     
/**      
 * @brief Multiplies a Q7 vector by a scalar.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       scaleFract fractional portion of the scale value      
 * @param[in]       shift number of bits to shift the result by      
 * @param[out]      *pDst points to the output vector      
 * @param[in]       blockSize number of samples in the vector      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The input data <code>*pSrc</code> and <code>scaleFract</code> are in 1.7 format.      
 * These are multiplied to yield a 2.14 intermediate result and this is shifted with saturation to 1.7 format.      
 */     
     
void arm_scale_q7(     
  q7_t * pSrc,     
  q7_t scaleFract,     
  int8_t shift,     
  q7_t * pDst,     
  uint32_t blockSize)     
{     
  int8_t kShift = 7 - shift;                     /* shift to apply after scaling */     
  uint32_t blkCnt;                               /* loop counter */     
  q7_t in1, in2, in3, in4, in5, in6; 			 /* temporary input variables */  
  q15_t out1, out2, out3, out4;      			 /* Temporary variables to store input & output */     
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* Reading 8 inputs from memory */     
	/* read inputs from source */  
 	in1 = pSrc[0];  
	in2 = pSrc[1];  
  
	/* multiply with scaling factor */  
    out1 = (q15_t)((q7_t) (in1) * (scaleFract));     
  
	/* read input from source */  
	in3 = pSrc[2];  
  
	/* multiply with scaling factor */  
    out2 = (q15_t)((q7_t) (in2) * (scaleFract));     
  
	/* read input from source */  
	in4 = pSrc[3];  
  
	/* multiply with scaling factor */  
    out3 = (q15_t)((q7_t) (in3) * (scaleFract));     
    out4 = (q15_t)((q7_t) (in4) * (scaleFract));     
  
	/* apply shifting */  
	out1 = out1 >> kShift;  
	out2 = out2 >> kShift;  
  
	/* read input from source */  
 	in1 = pSrc[4];  
  
	/* apply shifting */  
	out3 = out3 >> kShift;  
	out4 = out4 >> kShift;  
  
	/* saturate the output */  
#ifdef CCS	   
  
	in3 = (q7_t) __SSATA(out1, 0, 8);  
	in4 = (q7_t) __SSATA(out2, 0, 8);  
	in5 = (q7_t) __SSATA(out3, 0, 8);  
	in6 = (q7_t) __SSATA(out4, 0, 8);  
  
#else  
  
	in3 = (q7_t) __SSAT(out1, 8);  
	in4 = (q7_t) __SSAT(out2, 8);  
	in5 = (q7_t) __SSAT(out3, 8);  
	in6 = (q7_t) __SSAT(out4, 8);  
  
#endif  
  
   /* Store the results of 4 inputs in the destination buffer in single cycle by packing */     
    *__SIMD32(pDst)++ = __PACKq7(in3, in4, in5, in6);  
  
	/* read input from source */  
	in2 = pSrc[5];  
  
	/* multiply with scaling factor */  
    out1 = (q15_t)((q7_t) (in1) * (scaleFract));     
  
	/* read input from source */  
	in3 = pSrc[6];  
  
	/* multiply with scaling factor */  
    out2 = (q15_t)((q7_t) (in2) * (scaleFract));     
  
	/* read input from source */  
	in4 = pSrc[7];  
  
	/* multiply with scaling factor */  
    out3 = (q15_t)((q7_t) (in3) * (scaleFract));     
    out4 = (q15_t)((q7_t) (in4) * (scaleFract));     
  
	/* apply shifting */  
	out1 = out1 >> kShift;  
	out2 = out2 >> kShift;  
	out3 = out3 >> kShift;  
	out4 = out4 >> kShift;  
  
	/* saturate the output */  
#ifdef CCS	   
  
	in1 = (q7_t) __SSATA(out1, 0, 8);  
	in2 = (q7_t) __SSATA(out2, 0, 8);  
	in3 = (q7_t) __SSATA(out3, 0, 8);  
	in4 = (q7_t) __SSATA(out4, 0, 8);  
  
#else  
  
	in1 = (q7_t) __SSAT(out1, 8);  
	in2 = (q7_t) __SSAT(out2, 8);  
	in3 = (q7_t) __SSAT(out3, 8);  
	in4 = (q7_t) __SSAT(out4, 8);  
  
#endif  
  
    /* Store the results of 4 inputs in the destination buffer in single cycle by packing */     
    *__SIMD32(pDst)++ = __PACKq7(in1, in2, in3, in4);  
 
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
    /* C = A * scale */     
    /* Scale the input and then store the result in the destination buffer. */     
#ifdef CCS	   
    *pDst++ = (q7_t) (__SSATA(((*pSrc++) * scaleFract) >> kShift, 0, 8));     
#else   
    *pDst++ = (q7_t) (__SSAT(((*pSrc++) * scaleFract) >> kShift, 8));     
#endif     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of scale group      
 */     
