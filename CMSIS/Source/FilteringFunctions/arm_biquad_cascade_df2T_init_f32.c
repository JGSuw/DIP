/*-----------------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:        arm_biquad_cascade_df2T_init_f32.c      
*      
* Description:  Initialization function for the floating-point transposed     
*               direct form II Biquad cascade filter.     
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
* ---------------------------------------------------------------------------*/     
#include "arm_math.h"     
     
/**      
 * @ingroup groupFilters      
 */     
     
/**      
 * @addtogroup BiquadCascadeDF2T      
 * @{      
 */     
     
/**     
 * @brief  Initialization function for the floating-point transposed direct form II Biquad cascade filter.     
 * @param[in,out] *S           points to an instance of the filter data structure.     
 * @param[in]     numStages    number of 2nd order stages in the filter.     
 * @param[in]     *pCoeffs     points to the filter coefficients.     
 * @param[in]     *pState      points to the state buffer.     
 * @return        none     
 *      
 * <b>Coefficient and State Ordering:</b>      
 * \par      
 * The coefficients are stored in the array <code>pCoeffs</code> in the following order:      
 * <pre>      
 *     {b10, b11, b12, a11, a12, b20, b21, b22, a21, a22, ...}      
 * </pre>      
 *      
 * \par      
 * where <code>b1x</code> and <code>a1x</code> are the coefficients for the first stage,      
 * <code>b2x</code> and <code>a2x</code> are the coefficients for the second stage,      
 * and so on.  The <code>pCoeffs</code> array contains a total of <code>5*numStages</code> values.      
 *      
 * \par      
 * The <code>pState</code> is a pointer to state array.      
 * Each Biquad stage has 2 state variables <code>d1,</code> and <code>d2</code>.      
 * The 2 state variables for stage 1 are first, then the 2 state variables for stage 2, and so on.      
 * The state array has a total length of <code>2*numStages</code> values.      
 * The state variables are updated after each block of data is processed; the coefficients are untouched.      
 */     
     
void arm_biquad_cascade_df2T_init_f32(     
  arm_biquad_cascade_df2T_instance_f32 * S,     
  uint8_t numStages,     
  float32_t * pCoeffs,     
  float32_t * pState)     
{     
  /* Assign filter stages */     
  S->numStages = numStages;     
     
  /* Assign coefficient pointer */     
  S->pCoeffs = pCoeffs;     
     
  /* Clear state buffer and size is always 2 * numStages */     
  memset(pState, 0, (2u * (uint32_t) numStages) * sizeof(float32_t));     
     
  /* Assign state pointer */     
  S->pState = pState;     
}     
     
/**      
 * @} end of BiquadCascadeDF2T group      
 */     
