/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_iir_lattice_q15.c      
*      
* Description:	Q15 IIR lattice filter processing function.      
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
 * @ingroup groupFilters      
 */     
     
/**      
 * @addtogroup IIR_Lattice      
 * @{      
 */     
     
/**      
 * @brief Processing function for the Q15 IIR lattice filter.      
 * @param[in] *S points to an instance of the Q15 IIR lattice structure.      
 * @param[in] *pSrc points to the block of input data.      
 * @param[out] *pDst points to the block of output data.      
 * @param[in] blockSize number of samples to process.      
 * @return none.      
 *      
 * @details      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function is implemented using a 64-bit internal accumulator.      
 * Both coefficients and state variables are represented in 1.15 format and multiplications yield a 2.30 result.      
 * The 2.30 intermediate results are accumulated in a 64-bit accumulator in 34.30 format.      
 * There is no risk of internal overflow with this approach and the full precision of intermediate multiplications is preserved.      
 * After all additions have been performed, the accumulator is truncated to 34.15 format by discarding low 15 bits.      
 * Lastly, the accumulator is saturated to yield a result in 1.15 format.      
 */    
   
void arm_iir_lattice_q15(     
  const arm_iir_lattice_instance_q15 * S,     
  q15_t * pSrc,     
  q15_t * pDst,     
  uint32_t blockSize)   
{     
    
  q63_t acc;                                     /* Accumlator */       
  q15_t k1, k2, v;  
  q31_t fnext1, gcurr1 = 0, gnext;          /* Temporary variables for lattice stages */   
  uint32_t blkCnt, tapCnt;                       /* Temporary variables for counts */     
  q15_t *px1, *px2, *pk, *pv;                    /* Temporary pointers for state and coef */     
  uint32_t numStages = S->numStages;             /* number of stages */     
  q15_t *pState;                                 /* State pointer */     
  q15_t *pStateCurnt;                            /* State current pointer */     
  q31_t gcurr2, fnext2;  
  
  
  
  /* initialise loop count */    
  blkCnt = blockSize;     
     
  /* initialise state pointer */   
  pState = &S->pState[0];     
     
  /* Sample processing */     
  while(blkCnt > 0u)     
  {     
    /* Read Sample from input buffer */     
    /* fN(n) = x(n) */     
    fnext2 = *pSrc++;     
     
    /* Initialize state read pointer */     
    px1 = pState;     
    /* Initialize state write pointer */     
    px2 = pState;     
    /* Set accumulator to zero */     
    acc = 0;     
     
	/* Initialize Ladder coeff pointer */     
    pv = &S->pvCoeffs[0];     
    /* Initialize Reflection coeff pointer */     
    pk = &S->pkCoeffs[0]; 	 	  
   
     
    /* Loop unrolling.  Process 4 taps at a time. */     
    tapCnt = (numStages) >> 2;     
     
    while(tapCnt > 0u)     
    {     
      /* Read gN-1(n-1) from state buffer */     
      gcurr1 = *px1;  
  
	  /* read reflection coefficient kN */  
	  k1 = *pk;  
	  	       
      /* fN-1(n) = fN(n) - kN * gN-1(n-1) */     
      fnext1 = (q31_t)(((q63_t) gcurr1 * (k1)) >> 16);  
	    
#ifdef CCS  
  
	  fnext1 = __SDSUB(fnext2, fnext1);  
	    
#elif __GNUC__  
  
	  fnext1 = __QDSUB(fnext2, fnext1);  
  
#else  
  
	  fnext1 = __QSUB(fnext2, __QDBL(fnext1));   	    
  
#endif  
	  /* read next reflection coefficient kN-1 */  
	  k2 = *(pk + 1u);  
  
#ifdef CCS	     
      fnext1 = __SSATA(fnext1, 0, 16);     
#else   
	  fnext1 = __SSAT(fnext1, 16);     
#endif  
  
      /* Read gN-2(n-1) from state buffer */     
      gcurr2 = *(px1 + 1u);  
  
	  /* fN-2(n) = fN-1(n) - kN-1 * gN-2(n-1) */  
	  fnext2 = (q31_t)(((q63_t) gcurr2 * (k2)) >> 16);  
  
	  /* gN(n)   = kN * fN-1(n) + gN-1(n-1) */  
	  gnext = (q31_t)(((q63_t) fnext1 * (k1)) >> 16);  
  
#ifdef CCS  
  
	  fnext2 = __SDSUB(fnext1, fnext2);        
	  gnext = __SDADD(gcurr1, gnext);  
	    
#elif __GNUC__  
  
	  fnext2 = __QDSUB(fnext1, fnext2);        
	  gnext = __QDADD(gcurr1, gnext);  
  
#else  
  
	  fnext2 = __QSUB(fnext1, __QDBL(fnext2));        
	  gnext = __QADD(gcurr1, __QDBL(gnext));  
  
#endif  
  
	  /* read reflection coefficient kN-2 */  
	  k1 = *(pk + 2u);  
  
#ifdef CCS  
	  gnext = __SSATA(gnext, 0, 16);     
#else   
	  gnext = __SSAT(gnext, 16);     
#endif  
  
	  /* read ladder coefficient vN */  
	  v = *pv++;  
  
	  /* write gN-1(n) into state for next sample processing */     
      *px2++ = gnext;  
  
      /* Read gN-3(n-1) from state buffer */     
      gcurr1 = *(px1 + 2u);   
  
#ifdef CCS	     
      fnext2 = __SSATA(fnext2, 0, 16);  
    
#else   
	  fnext2 = __SSAT(fnext2, 16);  
#endif	  
    
	  /* y(n) += gN(n) * vN  */     
	  acc = __SMLALD(gnext, v, acc);  
    
	  /* fN-3(n) = fN-2(n) - kN-2 * gN-3(n-1) */     
      fnext1 = (q31_t)(((q63_t) gcurr1 * (k1)) >> 16);  
  
	  /* gN-1(n)   = kN-1 * fN-2(n) + gN-2(n-1) */  
	  gnext = (q31_t)(((q63_t) fnext2 * (k2)) >> 16);  
  
#ifdef CCS  
  
	  fnext1 = __SDSUB(fnext2, fnext1);  
	  gnext = __SDADD(gcurr2, gnext);  
	    
#elif __GNUC__  
  
	  fnext1 = __QDSUB(fnext2, fnext1);  
	  gnext = __QDADD(gcurr2, gnext);  
  
#else  
  
	  fnext1 = __QSUB(fnext2, __QDBL(fnext1));  
	  gnext = __QADD(gcurr2, __QDBL(gnext));  
  
#endif  
  
	  /* read ladder coefficient vN-1 */  
	  v = *pv++;  
  
#ifdef CCS	     
      fnext1 = __SSATA(fnext1, 0, 16);  
	  gnext = __SSATA(gnext, 0, 16);     
#else   
	  fnext1 = __SSAT(fnext1, 16);  
	  gnext = __SSAT(gnext, 16);     
#endif  
  
      /* Read gN-4(n-1) from state buffer */     
      gcurr2 = *(px1 + 3u);    
  
	  /* y(n) += gN-1(n) * vN-1  */     
	  acc = __SMLALD(gnext, v, acc);  
	    
  	  /* read reflection coefficient kN-3 */    
	  k2 = *(pk + 3u);  
		      
      /* write gN-1(n) into state for next sample processing */     
      *px2++ = gnext;   
	    
      /* fN-4(n) = fN-3(n) - kN-3 * gN-4(n-1) */     
	  fnext2 = (q31_t)(((q63_t) gcurr2 * (k2)) >> 16);  
  
	  /* gN-2(n) = kN-2 * fN-3(n) + gN-3(n-1) */  
	  gnext = (q31_t)(((q63_t) fnext1 * (k1)) >> 16);  
  
#ifdef CCS  
  
	  fnext2 = __SDSUB(fnext1, fnext2);  
	  gnext = __SDADD(gcurr1, gnext);  
	    
#elif __GNUC__  
  
	  fnext2 = __QDSUB(fnext1, fnext2);  
	  gnext = __QDADD(gcurr1, gnext);  
  
#else  
  
	  fnext2 = __QSUB(fnext1, __QDBL(fnext2));  
	  gnext = __QADD(gcurr1, __QDBL(gnext));  
  
#endif  
  
	  /* read ladder coefficient vN-2 */  
	  v = *pv++;  
  
#ifdef CCS	     
      fnext2 = __SSATA(fnext2, 0, 16);  
	  gnext = __SSATA(gnext, 0, 16);     
#else   
	  fnext2 = __SSAT(fnext2, 16);  
	  gnext = __SSAT(gnext, 16);     
#endif  
  
	  /* y(n) += gN-2(n) * vN-2  */     
	  acc = __SMLALD(gnext, v, acc);  
  
	  /* write gN-2(n) into state for next sample processing */     
      *px2++ = gnext;  
	    
	  /* update pointer */  
	  pk += 4u;   
	     
	   /* gN-3(n) = kN-3 * fN-4(n) + gN-4(n-1) */     
	   gnext = (q31_t)(((q63_t) fnext2 * (k2)) >> 16);  
  
#ifdef CCS  
  
	   gnext = __SDADD(gcurr2, gnext);  
	    
#elif __GNUC__  
  
	   gnext = __QDADD(gcurr2, gnext);  
  
#else  
  
	   gnext = __QADD(gcurr2, __QDBL(gnext));  
  
#endif  
  
	  /* read next ladder coefficient vN-3*/   
   	  v = *pv++;  
  
#ifdef CCS	     
	  gnext = __SSATA(gnext, 0, 16);     
#else   
	  gnext = __SSAT(gnext, 16);     
#endif  
      /* y(n) += gN-4(n) * vN-4  */     
	  acc = __SMLALD(gnext, v, acc);  
  
	  /* write gN-3(n) into state for next sample processing */     
      *px2++ = gnext;   
  
	  /* update pointers */  
	  px1 += 4u;  
    
     
      tapCnt--;     
     
    }  
	     
    /* If the filter length is not a multiple of 4, compute the remaining filter taps */     
    tapCnt = (numStages) % 0x4u;   
	 while(tapCnt > 0u)     
    {     
      gcurr1 = *px1++;     
      /* Process sample for last taps */     
      fnext1 = __QSUB(fnext2, (q31_t) (((q63_t) gcurr1 * (*pk)) >> 15));     
   
#ifdef CCS	     
      fnext1 = __SSATA(fnext1, 0, 16);     
#else   
      fnext1 = __SSAT(fnext1, 16);     
#endif	     
      gnext = __QADD(gcurr1, (q31_t) (((q63_t) fnext1 * (*pk++)) >> 15));     
   
#ifdef CCS   
      gnext = __SSATA(gnext, 0, 16);     
#else   
      gnext = __SSAT(gnext, 16);     
#endif   
   
      /* Output samples for last taps */     
      acc += (q31_t) (((q31_t) gnext * (*pv++)));     
      *px2++ = (q15_t) gnext;     
   	  fnext2 = fnext1;  
     
      tapCnt--;     
    }    
   
    /* y(n) += g0(n) * v0 */     
	acc = __SMLALD(fnext2, *pv++, acc);  
     
    *px2++ = fnext2;     
     
    /* write out into pDst */     
    *pDst++ = (q31_t) (acc >> 15u);     
     
    /* Advance the state pointer by 4 to process the next group of 4 samples */     
    pState = pState + 1u;     
    blkCnt--;     
     
  }     
     
  /* Processing is complete. Now copy last S->numStages samples to start of the buffer      
     for the preperation of next frame process */     
     
  /* Points to the start of the state buffer */     
  pStateCurnt = &S->pState[0];     
  pState = &S->pState[blockSize];     
     
  tapCnt = numStages >> 2u;     
     
  /* copy data */     
  while(tapCnt > 0u)     
  {  
  
      *pStateCurnt++ = *pState++;  
	  *pStateCurnt++ = *pState++;  
	  *pStateCurnt++ = *pState++;      
	  *pStateCurnt++ = *pState++;  
  
	  
	/* Decrement the loop counter */     
	tapCnt--;     
     
  }     
     
  /* Calculate remaining number of copies */     
  tapCnt = (numStages) % 0x4u;     
     
  /* Copy the remaining q31_t data */     
  while(tapCnt > 0u)     
  {     
    *pStateCurnt++ = *pState++;     
     
    /* Decrement the loop counter */     
    tapCnt--;     
  }     
     
}     
     
     
/**      
 * @} end of IIR_Lattice group      
 */     
