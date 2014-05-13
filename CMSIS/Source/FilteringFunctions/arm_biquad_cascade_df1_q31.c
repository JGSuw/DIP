/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_biquad_cascade_df1_q31.c      
*      
* Description:	Processing function for the      
*				Q31 Biquad cascade filter      
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
 * @addtogroup BiquadCascadeDF1     
 * @{     
 */    
    
/**     
 * @brief Processing function for the Q31 Biquad cascade filter.     
 * @param[in]  *S         points to an instance of the Q31 Biquad cascade structure.     
 * @param[in]  *pSrc      points to the block of input data.     
 * @param[out] *pDst      points to the block of output data.     
 * @param[in]  blockSize  number of samples to process per call.     
 * @return none.     
 *     
 * <b>Scaling and Overflow Behavior:</b>     
 * \par     
 * The function is implemented using an internal 64-bit accumulator.     
 * The accumulator has a 2.62 format and maintains full precision of the intermediate multiplication results but provides only a single guard bit.     
 * Thus, if the accumulator result overflows it wraps around rather than clip.     
 * In order to avoid overflows completely the input signal must be scaled down by 2 bits and lie in the range [-0.25 +0.25).     
 * After all 5 multiply-accumulates are performed, the 2.62 accumulator is shifted by <code>postShift</code> bits and the result truncated to     
 * 1.31 format by discarding the low 32 bits.     
 *     
 * \par     
 * Refer to the function <code>arm_biquad_cascade_df1_fast_q31()</code> for a faster but less precise implementation of this filter.     
 */    
    
void arm_biquad_cascade_df1_q31(    
  const arm_biquad_casd_df1_inst_q31 * S,    
  q31_t * pSrc,    
  q31_t * pDst,    
  uint32_t blockSize)    
{    
  q63_t acc;                                     /*  accumulator                   */    
  uint32_t uShift = ((uint32_t) S->postShift + 1u);    
  uint32_t lShift = 32u - uShift;				 /*  Shift to be applied to the output */    
  q31_t *pIn = pSrc;                             /*  input pointer initialization  */    
  q31_t *pOut = pDst;                            /*  output pointer initialization */    
  q31_t *pState = S->pState;                     /*  pState pointer initialization */    
  q31_t *pCoeffs = S->pCoeffs;                   /*  coeff pointer initialization  */    
  q31_t Xn1, Xn2, Yn1, Yn2;                      /*  Filter state variables        */    
  q31_t b0, b1, b2, a1, a2;                      /*  Filter coefficients           */    
  q31_t Xn;    
  q31_t acc_l, acc_h;                            /*  temporary input               */    
  uint32_t sample, stage = S->numStages;         /*  loop counters                     */    
     
  do    
  {    
    /* Reading the coefficients */    
    b0 = *pCoeffs++;    
    b1 = *pCoeffs++;    
    b2 = *pCoeffs++;    
    a1 = *pCoeffs++;    
    a2 = *pCoeffs++;    
    
    /* Reading the state values */    
    Xn1 = pState[0];    
    Xn2 = pState[1];    
    Yn1 = pState[2];    
    Yn2 = pState[3];    
    
    /* Apply loop unrolling and compute 4 output values simultaneously. */    
    /*      The variable acc hold output values that are being computed:     
     *     
     *    acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2]     
     */    
    
    sample = blockSize >> 2u;    
    
    /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.     
     ** a second loop below computes the remaining 1 to 3 samples. */    
    while(sample > 0u)    
    {    
      /* Read the input */    
      Xn = *pIn;    
    
      /* acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2] */    
    
      /* acc =  b0 * x[n] */    
      acc = (q63_t) b1 * Xn1;    
      /* acc +=  b1 * x[n-1] */    
      acc += (q63_t) b0 *Xn;    
      /* acc +=  b[2] * x[n-2] */    
      acc += (q63_t) b2 *Xn2;    
      /* acc +=  a1 * y[n-1] */    
      acc += (q63_t) a1 *Yn1;    
      /* acc +=  a2 * y[n-2] */    
      acc += (q63_t) a2 *Yn2;    
   
      /* The result is converted to 1.31 , Yn2 variable is reused */   
   
	  /* Calc lower part of acc */   
	  acc_l = acc & 0xffffffff;   
   
	  /* Calc upper part of acc */   
	  acc_h = (acc >> 32) & 0xffffffff;   
   
	  /* Read the second input */    
	  Xn2 = *(pIn + 1u);  
  
	  /* Apply shift for lower part of acc and upper part of acc */   
	  Yn2 = (uint32_t)acc_l >> lShift | acc_h << uShift;    
	     
	  /* Store the output in the destination buffer. */    
      *pOut = Yn2;    
    
      /* acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2] */    
    
      /* acc =  b0 * x[n] */    
      acc = (q63_t) b0 *Xn2;    
      /* acc +=  b1 * x[n-1] */    
      acc += (q63_t) b1 *Xn;    
      /* acc +=  b[2] * x[n-2] */    
      acc += (q63_t) b2 *Xn1;    
      /* acc +=  a1 * y[n-1] */    
      acc += (q63_t) a1 *Yn2;    
      /* acc +=  a2 * y[n-2] */    
      acc += (q63_t) a2 *Yn1;    
    
      /* The result is converted to 1.31, Yn1 variable is reused  */    
   
	  /* Calc lower part of acc */   
	  acc_l = acc & 0xffffffff;   
   
	  /* Calc upper part of acc */   
	  acc_h = (acc >> 32) & 0xffffffff;   
   
	   /* Read the third input  */    
	  Xn1 = *(pIn + 2u);   
  
	  /* Apply shift for lower part of acc and upper part of acc */   
	  Yn1 = (uint32_t)acc_l >> lShift | acc_h << uShift;   
 	  	     
      /* Store the output in the destination buffer. */    
      *(pOut + 1u) = Yn1;  
	      
      /* acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2] */    
    
      /* acc =  b0 * x[n] */    
      acc = (q63_t) b0 *Xn1;    
      /* acc +=  b1 * x[n-1] */    
      acc += (q63_t) b1 *Xn2;    
      /* acc +=  b[2] * x[n-2] */    
      acc += (q63_t) b2 *Xn;    
      /* acc +=  a1 * y[n-1] */    
      acc += (q63_t) a1 *Yn1;    
      /* acc +=  a2 * y[n-2] */    
      acc += (q63_t) a2 *Yn2;    
   
   
      /* The result is converted to 1.31, Yn2 variable is reused  */    
   
	  /* Calc lower part of acc */   
	  acc_l = acc & 0xffffffff;   
   
	  /* Calc upper part of acc */   
	  acc_h = (acc >> 32) & 0xffffffff;   
   
      /* Read the forth input */   
      Xn = *(pIn + 3u);   
  
	  /* Apply shift for lower part of acc and upper part of acc */   
	  Yn2 = (uint32_t)acc_l >> lShift | acc_h << uShift;  
	     
	  /* Store the output in the destination buffer. */    
      *(pOut + 2u) = Yn2;   
	    
	  pIn += 4u;   
    
      /* acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2] */    
    
      /* acc =  b0 * x[n] */    
      acc = (q63_t) b0 *Xn;    
      /* acc +=  b1 * x[n-1] */    
      acc += (q63_t) b1 *Xn1;    
      /* acc +=  b[2] * x[n-2] */    
      acc += (q63_t) b2 *Xn2;    
      /* acc +=  a1 * y[n-1] */    
      acc += (q63_t) a1 *Yn2;    
      /* acc +=  a2 * y[n-2] */    
      acc += (q63_t) a2 *Yn1;    
   
      /* The result is converted to 1.31, Yn1 variable is reused  */    
	     
	  /* Calc lower part of acc */   
	  acc_l = acc & 0xffffffff;   
   
	  /* Calc upper part of acc */   
	  acc_h = (acc >> 32) & 0xffffffff;   
   
	  /* Every time after the output is computed state should be updated. */    
      /* The states should be updated as:  */    
      /* Xn2 = Xn1    */    
      /* Xn1 = Xn     */    
      /* Yn2 = Yn1    */    
      /* Yn1 = acc    */    
      Xn2 = Xn1;    
      Xn1 = Xn;    
  
	  /* Apply shift for lower part of acc and upper part of acc */   
	  Yn1 = (uint32_t)acc_l >> lShift | acc_h << uShift;   
    
      /* Store the output in the destination buffer. */    
      *(pOut + 3u) = Yn1;    
  
	  pOut += 4u;  
    
      /* decrement the loop counter */    
      sample--;    
    }    
    
    /* If the blockSize is not a multiple of 4, compute any remaining output samples here.     
     ** No loop unrolling is used. */    
    sample = (blockSize & 0x3u);    
    
    while(sample > 0u)    
    {    
      /* Read the input */    
      Xn = *pIn++;    
    
      /* acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2] */    
    
      /* acc =  b0 * x[n] */    
      acc = (q63_t) b0 *Xn;    
      /* acc +=  b1 * x[n-1] */    
      acc += (q63_t) b1 *Xn1;    
      /* acc +=  b[2] * x[n-2] */    
      acc += (q63_t) b2 *Xn2;    
      /* acc +=  a1 * y[n-1] */    
      acc += (q63_t) a1 *Yn1;    
      /* acc +=  a2 * y[n-2] */    
      acc += (q63_t) a2 *Yn2;    
    
      /* The result is converted to 1.31  */    
      acc = acc >> lShift;         
    
      /* Every time after the output is computed state should be updated. */    
      /* The states should be updated as:  */    
      /* Xn2 = Xn1    */    
      /* Xn1 = Xn     */    
      /* Yn2 = Yn1    */    
      /* Yn1 = acc    */    
      Xn2 = Xn1;    
      Xn1 = Xn;    
      Yn2 = Yn1;    
      Yn1 = (q31_t) acc;    
    
      /* Store the output in the destination buffer. */    
      *pOut++ = (q31_t) acc;    
    
      /* decrement the loop counter */    
      sample--;    
    }    
    
    /*  The first stage goes from the input buffer to the output buffer. */    
    /*  Subsequent stages occur in-place in the output buffer */    
    pIn = pDst;    
    
    /* Reset to destination pointer */    
    pOut = pDst;    
    
    /*  Store the updated state variables back into the pState array */    
    *pState++ = Xn1;    
    *pState++ = Xn2;    
    *pState++ = Yn1;    
    *pState++ = Yn2;    
    
  } while(--stage);    
}    
    
/**     
  * @} end of BiquadCascadeDF1 group     
  */    
