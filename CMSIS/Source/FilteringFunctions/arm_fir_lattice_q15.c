/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_fir_lattice_q15.c      
*      
* Description:	Q15 FIR lattice filter processing function.      
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
 * @addtogroup FIR_Lattice      
 * @{      
 */     
     
     
/**      
 * @brief Processing function for the Q15 FIR lattice filter.      
 * @param[in]  *S        points to an instance of the Q15 FIR lattice structure.      
 * @param[in]  *pSrc     points to the block of input data.      
 * @param[out] *pDst     points to the block of output data      
 * @param[in]  blockSize number of samples to process.      
 * @return none.      
 */     
     
void arm_fir_lattice_q15(     
  const arm_fir_lattice_instance_q15 * S,     
  q15_t * pSrc,     
  q15_t * pDst,     
  uint32_t blockSize)     
{     
  q15_t *pState;                                 /* State pointer */     
  q15_t *pCoeffs = S->pCoeffs;                   /* Coefficient pointer */     
  q15_t *px;                                     /* temporary state pointer */     
  q15_t *pk;                                     /* temporary coefficient pointer */     
  q31_t fcurr1, fnext1, gcurr1 = 0, gnext1;    /* temporary variables for first sample in loop unrolling */     
  q31_t fcurr2, fnext2, gnext2;                 /* temporary variables for second sample in loop unrolling */     
  uint32_t numStages = S->numStages;             /* Number of stages in the filter */     
  uint32_t blkCnt, stageCnt;                     /* temporary variables for counts */     
    
  q15_t k;  
     
  pState = &S->pState[0];     
    
  /* First part of the processing with loop unrolling.  Compute 2 outputs at a time.      
 a second loop below computes the remaining 1 sample. */   
	    
  blkCnt = blockSize >> 1u;    
     
  while(blkCnt > 0u)     
  {     
    /* f0(n) = x(n) */     
    fcurr1 = *pSrc++;  
	  
	/* f0(n) = x(n) */     
    fcurr2 = *pSrc++;       
     
    /* Initialize coeff pointer */     
    pk = (pCoeffs);     
     
    /* Initialize state pointer */     
    px = pState;     
     
    /* read g0(n - 1) from state buffer */     
    gcurr1 = *px;     
     
	k = *pk++;  
  
    /* for sample 1 processing */     
    /* f1(n) = f0(n) +  K1 * g0(n-1) */     
    fnext1 = (q31_t)(((q63_t) gcurr1 * k) >> 16);  
	fnext1 = fcurr1 + (fnext1 << 1u);  
  
    /* g1(n) = f0(n) * K1  +  g0(n-1) */     
    gnext1 = (q31_t)(((q63_t) fcurr1 * (k)) >> 16);  
    gnext1 = gcurr1 + (gnext1 << 1u);  
  
#ifndef CCS  
    fnext1 = __SSAT(fnext1, 16);  
#else  
    fnext1 = __SSATA(fnext1, 0, 16);    
#endif          
	  
	/* for sample 1 processing */     
    /* f1(n) = f0(n) +  K1 * g0(n-1) */     
    fnext2 = (q31_t)(((q63_t) fcurr1 * k) >> 16);  
	fnext2 = fcurr2 + (fnext2 << 1u);  
  
#ifndef CCS   
	gnext1 = __SSAT(gnext1, 16);  
#else	         
    gnext1 = __SSATA(gnext1, 0, 16);  
#endif 	     
  
    /* g1(n) = f0(n) * K1  +  g0(n-1) */     
    gnext2 = (q31_t)(((q63_t) fcurr2 * (k)) >> 16);  
    gnext2 = fcurr1 + (gnext2 << 1u);  
  
#ifndef CCS  
	fnext2 = __SSAT(fnext2, 16);  
	gnext2 = __SSAT(gnext2, 16);  
#else  
    fnext2 = __SSATA(fnext2, 0, 16);  
    gnext2 = __SSATA(gnext2, 0, 16);    
#endif     
	   
  
    /* save g1(n) in state buffer */     
    *px++ = fcurr2;     
     
    /* f1(n) is saved in fcurr1      
       for next stage processing */     
    fcurr1 = fnext1;  
	fcurr2 = fnext2;     
     
    stageCnt = (numStages - 1u);     
     
    /* stage loop */     
    while(stageCnt > 0u)     
    {  
	  
	  k = *pk++;  
  
      /* read g2(n) from state buffer */     
      gcurr1 = *px;     
     
      /* save g1(n) in state buffer */     
      *px++ = gnext2;     
     
      /* Sample processing for K2, K3.... */     
      /* f2(n) = f1(n) +  K2 * g1(n-1) */     
  
	  fnext1 = (q31_t)(((q63_t) gcurr1 * k) >> 16);   
	  fnext2 = (q31_t)(((q63_t) gnext1 * k) >> 16);  
	  gnext2 = (q31_t)(((q63_t) fcurr2 * (k)) >> 16);  
  
	  fnext1 = fcurr1 + (fnext1 << 1u);	   
	  fnext2 = fcurr2 + (fnext2 << 1u);  
  
#ifndef CCS  
	  fnext1 = __SSAT(fnext1, 16);  
	  fnext2 = __SSAT(fnext2, 16);	   
#else    
      fnext1 = __SSATA(fnext1, 0, 16);	   
      fnext2 = __SSATA(fnext2, 0, 16);	  
#endif     
	          
      /* g2(n) = f1(n) * K2  +  g1(n-1) */     
  
	  gnext2 = gnext1 + (gnext2 << 1u);   
  
  
	        /* g2(n) = f1(n) * K2  +  g1(n-1) */     
	  gnext1 = (q31_t)(((q63_t) fcurr1 * (k)) >> 16);  
	  gnext1 = gcurr1 + (gnext1 << 1u);  
  
#ifndef CCS  
	  gnext2 = __SSAT(gnext2, 16);  
	  gnext1 = __SSAT(gnext1, 16);   
#else  
      gnext2 = __SSATA(gnext2, 0, 16);	     
      gnext1 = __SSATA(gnext1, 0, 16);   
#endif   
	      
      /* f1(n) is saved in fcurr1      
         for next stage processing */     
      fcurr1 = fnext1;   
	  fcurr2 = fnext2;      
     
      stageCnt--;     
     
    }    
     
    /* y(n) = fN(n) */     
    *pDst++ = fcurr1;    
	*pDst++ = fcurr2;   
     
    blkCnt--;     
     
  }  
  
  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x2u;  
    
  while(blkCnt > 0u)     
  {     
    /* f0(n) = x(n) */     
    fcurr1 = *pSrc++;     
     
    /* Initialize coeff pointer */     
    pk = (pCoeffs);     
     
    /* Initialize state pointer */     
    px = pState;     
     
    /* read g0(n - 1) from state buffer */     
    gcurr1 = *px;     
     
	k = *pk++;  
  
    /* for sample 1 processing */     
    /* f1(n) = f0(n) +  K1 * g0(n-1) */     
    fnext1 = (q31_t)(((q63_t) gcurr1 * k) >> 16);  
	fnext1 = fcurr1 + (fnext1 << 1u);  
  
    /* g1(n) = f0(n) * K1  +  g0(n-1) */     
    gnext1 = (q31_t)(((q63_t) fcurr1 * (k)) >> 16);  
    gnext1 = gcurr1 + (gnext1 << 1u);  
  
#ifndef CCS  
	fnext1 = __SSAT(fnext1, 16);  
	gnext1 = __SSAT(gnext1, 16);  
#else   
	fnext1 = __SSATA(fnext1, 0, 16);	   
	gnext1 = __SSATA(gnext1, 0, 16);  
#endif     
  
  
    /* save g1(n) in state buffer */     
    *px++ = fcurr1;     
     
    /* f1(n) is saved in fcurr1      
       for next stage processing */     
    fcurr1 = fnext1;     
     
    stageCnt = (numStages - 1u);     
     
    /* stage loop */     
    while(stageCnt > 0u)     
    {  
	  
	  k = *pk++;  
  
      /* read g2(n) from state buffer */     
      gcurr1 = *px;     
     
      /* save g1(n) in state buffer */     
      *px++ = gnext1;     
     
      /* Sample processing for K2, K3.... */     
      /* f2(n) = f1(n) +  K2 * g1(n-1) */     
  
	  fnext1 = (q31_t)(((q63_t) gcurr1 * k) >> 16);  
	  fnext1 = fcurr1 + (fnext1 << 1u);  
	       
      /* g2(n) = f1(n) * K2  +  g1(n-1) */     
	  gnext1 = (q31_t)(((q63_t) fcurr1 * (k)) >> 16);  
	  gnext1 = gcurr1 + (gnext1 << 1u);   
  
#ifndef CCS	    
	  fnext1 = __SSAT(fnext1, 16);  
#else   
      fnext1 = __SSATA(fnext1, 0, 16);  
#endif     
  
  
#ifndef CCS  
	  gnext1 = __SSAT(gnext1, 16);  
#else   
   	  gnext1 = __SSATA(gnext1, 0, 16);  
#endif     
  
      /* f1(n) is saved in fcurr1      
         for next stage processing */     
      fcurr1 = fnext1;     
     
      stageCnt--;     
     
    }  
  
     
    /* y(n) = fN(n) */     
    *pDst++ = fcurr1;     
     
    blkCnt--;     
     
  }     
    
       
    
}     
     
/**      
 * @} end of FIR_Lattice group      
 */     
