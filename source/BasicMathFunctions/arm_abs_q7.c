/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_abs_q7.c      
*      
* Description:	Q7 vector absolute value.      
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
 * @brief Q7 vector absolute value.      
 * @param[in]       *pSrc points to the input buffer      
 * @param[out]      *pDst points to the output buffer      
 * @param[in]       blockSize number of samples in each vector      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function uses saturating arithmetic.      
 * The Q7 value -1 (0x80) will be saturated to the maximum allowable positive value 0x7F.      
 */     
     
void arm_abs_q7(     
  q7_t * pSrc,     
  q7_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t in1, in2, in3, in4;			 			 /* temporary input variables */  
  q31_t out1, out2, out3, out4;					 /* temporary output variables */  
   
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = |A| */     
    /* Read inputs */    
    in1 = (q31_t)*pSrc;     
    in2 = (q31_t)*(pSrc + 1);     
    in3 = (q31_t)*(pSrc + 2);  
	  
	/* find absolute value */     
	out1 = (in1 > 0) ? in1 : __QSUB(0, in1);   
  
    /* read input */  
	in4 = (q31_t)*(pSrc + 3);   		   
  
	/* find absolute value */     
 	out2 = (in2 > 0) ? in2 : __QSUB(0, in2);  
  
	/* store result to destination */  
    *pDst = (q7_t)out1;  
  
	/* find absolute value */     
	out3 = (in3 > 0) ? in3 : __QSUB(0, in3);  
  
    /* read input */  
	in1 = (q31_t)*(pSrc + 4);  
  
	/* find absolute value */     
	out4 = (in4 > 0) ? in4 : __QSUB(0, in4);  
  
	/* store result to destination */  
	*(pDst + 1) = (q7_t)out2;  
  
    /* read input */  
	in2 = (q31_t)*(pSrc + 5);  
  
	/* find absolute value */     
	out1 = (in1 > 0) ? in1 : __QSUB(0, in1);   
  
	/* store result to destination */  
	*(pDst + 2) = (q7_t)out3;  
  
	/* find absolute value */     
	out2 = (in2 > 0) ? in2 : __QSUB(0, in2);   
  
    /* read input */  
	in3 = (q31_t)*(pSrc + 6);  
  
	/* store result to destination */  
	*(pDst + 3) = (q7_t)out4;  
  
    /* read input */  
	in4 = (q31_t)*(pSrc + 7);  
  
	/* find absolute value */     
	out3 = (in3 > 0) ? in3 : __QSUB(0, in3);  
  
	/* store result to destination */  
	*(pDst + 4) = (q7_t)out1;   
  
	/* find absolute value */     
	out4 = (in4 > 0) ? in4 : __QSUB(0, in4);  
  
	/* store result to destination */  
	*(pDst + 5) = (q7_t)out2;  
	*(pDst + 6) = (q7_t)out3;  
  
	/* increment source pointer by 8 */  
	pSrc += 8u;  
  
	/* store result to destination */  
	*(pDst + 7) = (q7_t)out4;  
  
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
    /* Read the input */     
    in1 = *pSrc++;     
     
    /* Store the Absolute result in the destination buffer */     
    *pDst++ = (in1 > 0) ? in1 : __QSUB8(0, in1);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of BasicAbs group      
 */     
