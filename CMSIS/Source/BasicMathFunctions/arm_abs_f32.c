/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_abs_f32.c      
*      
* Description:	Vector absolute value.      
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
#include <math.h>     
     
/**      
 * @ingroup groupMath      
 */     
     
/**      
 * @defgroup BasicAbs Vector Absolute Value      
 *      
 * Computes the absolute value of a vector on an element-by-element basis.      
 *      
 * <pre>      
 *     pDst[n] = abs(pSrcA[n]),   0 <= n < blockSize.      
 * </pre>      
 *      
 * The operation can be done in-place by setting the input and output pointers to the same buffer.      
 * There are separate functions for floating-point, Q7, Q15, and Q31 data types.      
 */     
     
/**      
 * @addtogroup BasicAbs      
 * @{      
 */     
     
/**      
 * @brief Floating-point vector absolute value.      
 * @param[in]       *pSrc points to the input buffer      
 * @param[out]      *pDst points to the output buffer      
 * @param[in]       blockSize number of samples in each vector      
 * @return none.      
 */     
     
void arm_abs_f32(     
  float32_t * pSrc,     
  float32_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  float32_t in1, in2, in3, in4;		 			 /* temporary variables */  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = |A| */     
    /* Calculate absolute and then store the results in the destination buffer. */     
	/* read sample from source */  
	in1 = *pSrc;  
	in2 = *(pSrc + 1);  
	in3 = *(pSrc + 2);  
  
	/* find absolute value */  
	in1 = fabsf(in1);  
  
	/* read sample from source */  
	in4 = *(pSrc + 3);  
  
	/* find absolute value */  
	in2 = fabsf(in2);  
  
	/* read sample from source */  
	*pDst = in1;   
  
	/* find absolute value */  
	in3 = fabsf(in3);  
  
	/* read sample from source */  
	in1 = *(pSrc + 4);  
  
	/* find absolute value */  
	in4 = fabsf(in4);  
  
	/* store result to destination */  
	*(pDst + 1) = in2;  
	  
	/* read sample from source */  
	in2 = *(pSrc + 5);  
  
	/* find absolute value */  
	in1 = fabsf(in1);  
  
	/* store result to destination */  
	*(pDst + 2) = in3;  
  
	/* read sample from source */  
	in3 = *(pSrc + 6);  
  
	/* find absolute value */  
	in2 = fabsf(in2);  
  
	/* store result to destination */  
	*(pDst + 3) = in4;  
  
	/* read sample from source */  
	in4 = *(pSrc + 7);  
  
	/* find absolute value */  
	in3 = fabsf(in3);  
  
	/* store result to destination */  
	*(pDst + 4) = in1;  
  
	/* find absolute value */  
 	in4 = fabsf(in4);  
  
	/* store result to destination */  
	*(pDst + 5) = in2;  
	*(pDst + 6) = in3;  
  
	/* Update source pointer to process next sampels */  
	pSrc += 8u;  
  
	/* store result to destination */  
	*(pDst + 7) = in4;  
  
	/* Update destination pointer to process next sampels */  
	pDst += 8u;	  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = |A| */     
    /* Calculate absolute and then store the results in the destination buffer. */     
    *pDst++ = fabsf(*pSrc++);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of BasicAbs group      
 */     
