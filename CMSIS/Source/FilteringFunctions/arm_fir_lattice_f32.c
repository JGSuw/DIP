/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_fir_lattice_f32.c      
*      
* Description:	Processing function for the floating-point FIR Lattice filter.      
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
 * @defgroup FIR_Lattice Finite Impulse Response (FIR) Lattice Filters      
 *      
 * This set of functions implements Finite Impulse Response (FIR) lattice filters      
 * for Q15, Q31 and floating-point data types.  Lattice filters are used in a       
 * variety of adaptive filter applications.  The filter structure is feedforward and      
 * the net impulse response is finite length.      
 * The functions operate on blocks      
 * of input and output data and each call to the function processes      
 * <code>blockSize</code> samples through the filter.  <code>pSrc</code> and      
 * <code>pDst</code> point to input and output arrays containing <code>blockSize</code> values.      
 *      
 * \par Algorithm:      
 * \image html FIRLattice.gif "Finite Impulse Response Lattice filter"      
 * The following difference equation is implemented:      
 * <pre>      
 *    f0[n] = g0[n] = x[n]      
 *    fm[n] = fm-1[n] + km * gm-1[n-1] for m = 1, 2, ...M      
 *    gm[n] = km * fm-1[n] + gm-1[n-1] for m = 1, 2, ...M      
 *    y[n] = fM[n]      
 * </pre>      
 * \par      
 * <code>pCoeffs</code> points to tha array of reflection coefficients of size <code>numStages</code>.      
 * Reflection Coefficients are stored in the following order.      
 * \par      
 * <pre>      
 *    {k1, k2, ..., kM}      
 * </pre>      
 * where M is number of stages      
 * \par      
 * <code>pState</code> points to a state array of size <code>numStages</code>.      
 * The state variables (g values) hold previous inputs and are stored in the following order.      
 * <pre>      
 *    {g0[n], g1[n], g2[n] ...gM-1[n]}      
 * </pre>      
 * The state variables are updated after each block of data is processed; the coefficients are untouched.      
 * \par Instance Structure      
 * The coefficients and state variables for a filter are stored together in an instance data structure.      
 * A separate instance structure must be defined for each filter.      
 * Coefficient arrays may be shared among several instances while state variable arrays cannot be shared.      
 * There are separate instance structure declarations for each of the 3 supported data types.      
 *      
 * \par Initialization Functions      
 * There is also an associated initialization function for each data type.      
 * The initialization function performs the following operations:      
 * - Sets the values of the internal structure fields.      
 * - Zeros out the values in the state buffer.      
 *      
 * \par      
 * Use of the initialization function is optional.      
 * However, if the initialization function is used, then the instance structure cannot be placed into a const data section.      
 * To place an instance structure into a const data section, the instance structure must be manually initialized.      
 * Set the values in the state buffer to zeros and then manually initialize the instance structure as follows:      
 * <pre>      
 *arm_fir_lattice_instance_f32 S = {numStages, pState, pCoeffs};      
 *arm_fir_lattice_instance_q31 S = {numStages, pState, pCoeffs};      
 *arm_fir_lattice_instance_q15 S = {numStages, pState, pCoeffs};      
 * </pre>      
 * \par      
 * where <code>numStages</code> is the number of stages in the filter; <code>pState</code> is the address of the state buffer;      
 * <code>pCoeffs</code> is the address of the coefficient buffer.      
 * \par Fixed-Point Behavior      
 * Care must be taken when using the fixed-point versions of the FIR Lattice filter functions.      
 * In particular, the overflow and saturation behavior of the accumulator used in each function must be considered.      
 * Refer to the function specific documentation below for usage guidelines.      
 */     
     
/**      
 * @addtogroup FIR_Lattice      
 * @{      
 */     
     
     
  /**      
   * @brief Processing function for the floating-point FIR lattice filter.      
   * @param[in]  *S        points to an instance of the floating-point FIR lattice structure.      
   * @param[in]  *pSrc     points to the block of input data.      
   * @param[out] *pDst     points to the block of output data      
   * @param[in]  blockSize number of samples to process.      
   * @return none.      
   */     
     
void arm_fir_lattice_f32(     
  const arm_fir_lattice_instance_f32 * S,     
  float32_t * pSrc,     
  float32_t * pDst,     
  uint32_t blockSize)     
{     
  float32_t *pState;                             /* State pointer */     
  float32_t *pCoeffs = S->pCoeffs;               /* Coefficient pointer */     
  float32_t *px;                                 /* temporary state pointer */     
  float32_t *pk, k;                              /* temporary coefficient pointer */     
  float32_t fcurr1, fnext1, gcurr1, gnext1;      /* temporary variables for first sample in loop unrolling */     
  float32_t fcurr2, fnext2, gnext2;              /* temporary variables for second sample in loop unrolling */     
  float32_t fcurr3, fnext3, gnext3;              /* temporary variables for third sample in loop unrolling */     
  float32_t fcurr4, fnext4, gnext4;              /* temporary variables for fourth sample in loop unrolling */     
  uint32_t numStages = S->numStages;             /* Number of stages in the filter */     
  uint32_t blkCnt, stageCnt;                     /* temporary variables for counts */     
     
  pState = &S->pState[0];     
     
  blkCnt = blockSize >> 2;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
     a second loop below computes the remaining 1 to 3 samples. */     
  while(blkCnt > 0u)     
  {     
     
    /* Read two samples from input buffer */     
    /* f0(n) = x(n) */     
    fcurr1 = *pSrc++;	     
    fcurr2 = *pSrc++;     
     
    /* Initialize coeff pointer */     
    pk = (pCoeffs);     
     
    /* Initialize state pointer */     
    px = pState;  
	  
	k = *pk++;     
     
    /* Read g0(n-1) from state */     
    gcurr1 = *px;     
     
    /* Process first sample for first tap */     
    /* f1(n) = f0(n) +  K1 * g0(n-1) */     
    fnext1 = fcurr1 + (k * gcurr1);   
	    
    /* g1(n) = f0(n) * K1  +  g0(n-1) */     
    gnext1 = (fcurr1 * k) + gcurr1;     
     
    /* Process second sample for first tap */     
    /* for sample 2 processing */     
    fnext2 = fcurr2 + (k * fcurr1);     
    gnext2 = (fcurr2 * k) + fcurr1;     
     
    /* Read next two samples from input buffer */     
    /* f0(n+2) = x(n+2) */     
    fcurr3 = *pSrc++;     
    fcurr4 = *pSrc++;     
     
    /* Copy only last input samples into the state buffer      
       which will be used for next four samples processing */     
    *px++ = fcurr4;     
     
    /* Process third sample for first tap */     
    fnext3 = fcurr3 + (k * fcurr2);     
    gnext3 = (fcurr3 * k) + fcurr2;     
     
    /* Process fourth sample for first tap */     
    fnext4 = fcurr4 + (k * fcurr3);     
    gnext4 = (fcurr4 * k) + fcurr3;     
     
    /* Update of f values for next coefficient set processing */     
    fcurr1 = fnext1;     
    fcurr2 = fnext2;     
    fcurr3 = fnext3;     
    fcurr4 = fnext4;     
     
    /* Loop unrolling.  Process 4 taps at a time . */     
    stageCnt = (numStages - 1u) >> 2u;     
     
    /* Loop over the number of taps.  Unroll by a factor of 4.      
     ** Repeat until we've computed numStages-3 coefficients. */     
     
    /* Process 2nd, 3rd, 4th and 5th taps ... here */     
    while(stageCnt > 0u)     
    {     
      /* Read g1(n-1), g3(n-1) .... from state */     
      gcurr1 = *px;     
     
	  /* Read the reflection coefficient */  
	  k = *pk;  
  
      /* save g1(n) in state buffer */     
      *px++ = gnext4;     
     
      /* Process first sample for 2nd, 6th .. tap */     
      /* Sample processing for K2, K6.... */     
      /* f2(n) = f1(n) +  K2 * g1(n-1) */     
      fnext1 = fcurr1 + (k * gcurr1);     
      /* Process second sample for 2nd, 6th .. tap */     
      /* for sample 2 processing */     
      fnext2 = fcurr2 + (k * gnext1);     
      /* Process third sample for 2nd, 6th .. tap */     
      fnext3 = fcurr3 + (k * gnext2);     
      /* Process fourth sample for 2nd, 6th .. tap */     
      fnext4 = fcurr4 + (k * gnext3);     
     
      /* g2(n) = f1(n) * K2  +  g1(n-1) */     
      /* Calculation of state values for next stage */     
      gnext4 = (fcurr4 * k) + gnext3;     
      gnext3 = (fcurr3 * k) + gnext2;     
      gnext2 = (fcurr2 * k) + gnext1;     
      gnext1 = (fcurr1 * k) + gcurr1;     
     
     
      /* Read g2(n-1), g4(n-1) .... from state */     
      gcurr1 = *px;     
     
	  /* Read the reflection coefficient */  
 	  k = *(pk + 1u);  
  
      /* save g2(n) in state buffer */     
      *px++ = gnext4;     
     
      /* Sample processing for K3, K7.... */     
      /* Process first sample for 3rd, 7th .. tap */     
      /* f3(n) = f2(n) +  K3 * g2(n-1) */     
      fcurr1 = fnext1 + (k * gcurr1);     
      /* Process second sample for 3rd, 7th .. tap */     
      fcurr2 = fnext2 + (k * gnext1);     
      /* Process third sample for 3rd, 7th .. tap */     
      fcurr3 = fnext3 + (k * gnext2);     
      /* Process fourth sample for 3rd, 7th .. tap */     
      fcurr4 = fnext4 + (k * gnext3);     
     
      /* Calculation of state values for next stage */     
      /* g3(n) = f2(n) * K3  +  g2(n-1) */     
      gnext4 = (fnext4 * k) + gnext3;     
      gnext3 = (fnext3 * k) + gnext2;     
      gnext2 = (fnext2 * k) + gnext1;     
      gnext1 = (fnext1 * k) + gcurr1;     
     
     
      /* Read g1(n-1), g3(n-1) .... from state */     
      gcurr1 = *px;   
	    
	  /* Read the reflection coefficient */  
	  k = *(pk + 2u);    
     
      /* save g3(n) in state buffer */     
      *px++ = gnext4;     
     
      /* Sample processing for K4, K8.... */     
      /* Process first sample for 4th, 8th .. tap */     
      /* f4(n) = f3(n) +  K4 * g3(n-1) */     
      fnext1 = fcurr1 + (k * gcurr1);     
      /* Process second sample for 4th, 8th .. tap */     
      /* for sample 2 processing */     
      fnext2 = fcurr2 + (k * gnext1);     
      /* Process third sample for 4th, 8th .. tap */     
      fnext3 = fcurr3 + (k * gnext2);     
      /* Process fourth sample for 4th, 8th .. tap */     
      fnext4 = fcurr4 + (k * gnext3);     
     
      /* g4(n) = f3(n) * K4  +  g3(n-1) */     
      /* Calculation of state values for next stage */     
      gnext4 = (fcurr4 * k) + gnext3;     
      gnext3 = (fcurr3 * k) + gnext2;     
      gnext2 = (fcurr2 * k) + gnext1;     
      gnext1 = (fcurr1 * k) + gcurr1;     
     
      /* Read g2(n-1), g4(n-1) .... from state */     
      gcurr1 = *px;  
	    
	  /* Read the reflection coefficient */  
	  k = *(pk + 3u);     
     
      /* save g4(n) in state buffer */     
      *px++ = gnext4;  
	    
	  /* update Coeff pointer */     
	  pk += 4u;     
  
      /* Sample processing for K5, K9.... */     
      /* Process first sample for 5th, 9th .. tap */     
      /* f5(n) = f4(n) +  K5 * g4(n-1) */     
      fcurr1 = fnext1 + (k * gcurr1);     
      /* Process second sample for 5th, 9th .. tap */     
      fcurr2 = fnext2 + (k * gnext1);     
      /* Process third sample for 5th, 9th .. tap */     
      fcurr3 = fnext3 + (k * gnext2);     
      /* Process fourth sample for 5th, 9th .. tap */     
      fcurr4 = fnext4 + (k * gnext3);     
     
      /* Calculation of state values for next stage */     
      /* g5(n) = f4(n) * K5  +  g4(n-1) */     
      gnext4 = (fnext4 * k) + gnext3;     
      gnext3 = (fnext3 * k) + gnext2;     
      gnext2 = (fnext2 * k) + gnext1;     
      gnext1 = (fnext1 * k) + gcurr1;     
  
  
     
      stageCnt--;     
    }     
     
    /* If the (filter length -1) is not a multiple of 4, compute the remaining filter taps */     
    stageCnt = (numStages - 1u) % 0x4u;     
     
    while(stageCnt > 0u)     
    {     
      gcurr1 = *px;     
     
      /* save g value in state buffer */     
      *px++ = gnext4;  
	    
	  /* Read the reflection coefficient */  
	  k = (*pk++);     
     
      /* Process four samples for last three taps here */     
      fnext1 = fcurr1 + (k * gcurr1);     
      fnext2 = fcurr2 + (k * gnext1);     
      fnext3 = fcurr3 + (k * gnext2);     
      fnext4 = fcurr4 + (k * gnext3);     
     
      /* g1(n) = f0(n) * K1  +  g0(n-1) */     
      gnext4 = (fcurr4 * k) + gnext3;     
      gnext3 = (fcurr3 * k) + gnext2;     
      gnext2 = (fcurr2 * k) + gnext1;     
      gnext1 = (fcurr1 * k) + gcurr1;     
     
      /* Update of f values for next coefficient set processing */     
      fcurr1 = fnext1;     
      fcurr2 = fnext2;     
      fcurr3 = fnext3;     
      fcurr4 = fnext4;     
     
      stageCnt--;     
     
    }     
     
    /* The results in the 4 accumulators, store in the destination buffer. */     
    /* y(n) = fN(n) */     
    *pDst++ = fcurr1;     
    *pDst++ = fcurr2;     
    *pDst++ = fcurr3;     
    *pDst++ = fcurr4;     
     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x4u;     
     
  while(blkCnt > 0u)     
  {     
    /* f0(n) = x(n) */     
    fcurr1 = *pSrc++;     
     
    /* Initialize coeff pointer */     
    pk = (pCoeffs);     
     
    /* Initialize state pointer */     
    px = pState;     
     
    /* read g2(n) from state buffer */     
    gcurr1 = *px;  
	  
	/* Read the reflection coefficient */  
	k = (*pk++);     
     
    /* for sample 1 processing */     
    /* f1(n) = f0(n) +  K1 * g0(n-1) */     
    fnext1 = fcurr1 + (k * gcurr1);     
    /* g1(n) = f0(n) * K1  +  g0(n-1) */     
    gnext1 = (fcurr1 * k) + gcurr1;     
     
    /* save g1(n) in state buffer */     
    *px++ = fcurr1;     
     
    /* f1(n) is saved in fcurr1      
       for next stage processing */     
    fcurr1 = fnext1;     
     
    stageCnt = (numStages - 1u);     
     
    /* stage loop */     
    while(stageCnt > 0u)     
    {     
      /* read g2(n) from state buffer */     
      gcurr1 = *px;   
	    
	  /* Read the reflection coefficient */  
	  k = (*pk++);    
     
      /* save g1(n) in state buffer */     
      *px++ = gnext1;     
     
      /* Sample processing for K2, K3.... */     
      /* f2(n) = f1(n) +  K2 * g1(n-1) */     
      fnext1 = fcurr1 + (k * gcurr1);     
      /* g2(n) = f1(n) * K2  +  g1(n-1) */     
      gnext1 = (fcurr1 * k) + gcurr1;     
     
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
