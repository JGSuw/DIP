/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_abs_q31.c      
*      
* Description:	Q31 vector absolute value.      
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
 * @addtogroup BasicAbs      
 * @{      
 */     
     
     
/**      
 * @brief Q31 vector absolute value.      
 * @param[in]       *pSrc points to the input buffer      
 * @param[out]      *pDst points to the output buffer      
 * @param[in]       blockSize number of samples in each vector      
 * @return none.      
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function uses saturating arithmetic.      
 * The Q31 value -1 (0x80000000) will be saturated to the maximum allowable positive value 0x7FFFFFFF.      
 */     
     
void arm_abs_q31(     
  q31_t * pSrc,     
  q31_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t in1, in2, in3, in4;                      /* Input value */     
  q31_t out1, out2, out3, out4;					 /* Output value */  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = |A| */     
    /* Calculate absolute of input (if -1 then saturated to 0x7fffffff) and then store the results in the destination buffer. */     
    /* Read inputs */    
    in1 = *pSrc;     
    in2 = *(pSrc + 1);     
    in3 = *(pSrc + 2);     
	  
	/* find absolute value */     
	out1 = (in1 > 0) ? in1 : __QSUB(0, in1);   
  
    /* read input */  
    in4 = *(pSrc + 3);   		   
  
	/* find absolute value */     
 	out2 = (in2 > 0) ? in2 : __QSUB(0, in2);  
  
	/* store result to destination */  
   *pDst = out1;  
  
	/* find absolute value */     
	out3 = (in3 > 0) ? in3 : __QSUB(0, in3);  
  
    /* read input */  
	in1 = *(pSrc + 4);  
  
	/* find absolute value */     
	out4 = (in4 > 0) ? in4 : __QSUB(0, in4);  
  
	/* store result to destination */  
	*(pDst + 1) = out2;  
  
    /* read input */  
	in2 = *(pSrc + 5);  
  
	/* find absolute value */     
	out1 = (in1 > 0) ? in1 : __QSUB(0, in1);   
  
	/* store result to destination */  
	*(pDst + 2) = out3;  
  
	/* find absolute value */     
	out2 = (in2 > 0) ? in2 : __QSUB(0, in2);   
  
    /* read input */  
	in3 = *(pSrc + 6);  
  
	/* store result to destination */  
	*(pDst + 3) = out4;  
  
    /* read input */  
	in4 = *(pSrc + 7);  
  
	/* find absolute value */     
	out3 = (in3 > 0) ? in3 : __QSUB(0, in3);  
  
	/* store result to destination */  
	*(pDst + 4) = out1;   
  
	/* find absolute value */     
	out4 = (in4 > 0) ? in4 : __QSUB(0, in4);  
  
	/* store result to destination */  
	*(pDst + 5) = out2;  
	*(pDst + 6) = out3;  
  
	/* increment source pointer by 8 */  
	pSrc += 8u;  
  
	/* store result to destination */  
	*(pDst + 7) = out4;  
  
	/* increment destination pointer by 8 */  
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
    /* Calculate absolute value of the input (if -1 then saturated to 0x7fffffff) and then store the results in the destination buffer. */     
    in1 = *pSrc++;     
    *pDst++ = (in1 > 0) ? in1 : __QSUB(0, in1);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of BasicAbs group      
 */     
