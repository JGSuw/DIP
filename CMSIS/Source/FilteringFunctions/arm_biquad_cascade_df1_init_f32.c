/*-----------------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:        arm_biquad_cascade_df1_init_f32.c      
*      
* Description:  floating-point Biquad cascade DirectFormI(DF1) filter initialization function.      
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
 * @addtogroup BiquadCascadeDF1      
 * @{      
 */     
     
/**      
 * @details      
 * @brief  Initialization function for the floating-point Biquad cascade filter.      
 * @param[in,out] *S           points to an instance of the floating-point Biquad cascade structure.      
 * @param[in]     numStages    number of 2nd order stages in the filter.      
 * @param[in]     *pCoeffs     points to the filter coefficients array.      
 * @param[in]     *pState      points to the state array.      
 * @return        none      
 *      
 *      
 * <b>Coefficient and State Ordering:</b>      
 *      
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
 * Each Biquad stage has 4 state variables <code>x[n-1], x[n-2], y[n-1],</code> and <code>y[n-2]</code>.      
 * The state variables are arranged in the <code>pState</code> array as:      
 * <pre>      
 *     {x[n-1], x[n-2], y[n-1], y[n-2]}      
 * </pre>      
 * The 4 state variables for stage 1 are first, then the 4 state variables for stage 2, and so on.      
 * The state array has a total length of <code>4*numStages</code> values.      
 * The state variables are updated after each block of data is processed; the coefficients are untouched.      
 *      
 */     
     
void arm_biquad_cascade_df1_init_f32(     
  arm_biquad_casd_df1_inst_f32 * S,     
  uint8_t numStages,     
  float32_t * pCoeffs,     
  float32_t * pState)     
{     
  /* Assign filter stages */     
  S->numStages = numStages;     
     
  /* Assign coefficient pointer */     
  S->pCoeffs = pCoeffs;     
     
  /* Clear state buffer and size is always 4 * numStages */     
  memset(pState, 0, (4u * (uint32_t) numStages) * sizeof(float32_t));     
     
  /* Assign state pointer */     
  S->pState = pState;     
}     
     
/**      
 * @} end of BiquadCascadeDF1 group      
 */     
