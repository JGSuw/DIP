/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_biquad_cascade_df1_f32.c      
*      
* Description:	Processing function for the      
*               floating-point Biquad cascade DirectFormI(DF1) filter.      
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
 * @defgroup BiquadCascadeDF1 Biquad Cascade IIR Filters Using Direct Form I Structure      
 *      
 * This set of functions implements arbitrary order recursive (IIR) filters.      
 * The filters are implemented as a cascade of second order Biquad sections.      
 * The functions support Q15, Q31 and floating-point data types. Fast version of Q15 and Q31 also supported.      
 *      
 * The functions operate on blocks of input and output data and each call to the function      
 * processes <code>blockSize</code> samples through the filter.      
 * <code>pSrc</code> points to the array of input data and      
 * <code>pDst</code> points to the array of output data.      
 * Both arrays contain <code>blockSize</code> values.      
 *      
 * \par Algorithm      
 * Each Biquad stage implements a second order filter using the difference equation:      
 * <pre>      
 *     y[n] = b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2]      
 * </pre>      
 * A Direct Form I algorithm is used with 5 coefficients and 4 state variables per stage.      
 * \image html Biquad.gif "Single Biquad filter stage"      
 * Coefficients <code>b0, b1 and b2 </code> multiply the input signal <code>x[n]</code> and are referred to as the feedforward coefficients.      
 * Coefficients <code>a1</code> and <code>a2</code> multiply the output signal <code>y[n]</code> and are referred to as the feedback coefficients.      
 * Pay careful attention to the sign of the feedback coefficients.      
 * Some design tools use the difference equation      
 * <pre>      
 *     y[n] = b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] - a1 * y[n-1] - a2 * y[n-2]      
 * </pre>      
 * In this case the feedback coefficients <code>a1</code> and <code>a2</code> must be negated when used with the Cortex-R4 DSP Library.      
 *      
 * \par      
 * Higher order filters are realized as a cascade of second order sections.      
 * <code>numStages</code> refers to the number of second order stages used.      
 * For example, an 8th order filter would be realized with <code>numStages=4</code> second order stages.      
 * \image html BiquadCascade.gif "8th order filter using a cascade of Biquad stages"      
 * A 9th order filter would be realized with <code>numStages=5</code> second order stages with the coefficients for one of the stages configured as a first order filter (<code>b2=0</code> and <code>a2=0</code>).      
 *      
 * \par      
 * The <code>pState</code> points to state variables array.      
 * Each Biquad stage has 4 state variables <code>x[n-1], x[n-2], y[n-1],</code> and <code>y[n-2]</code>.      
 * The state variables are arranged in the <code>pState</code> array as:      
 * <pre>      
 *     {x[n-1], x[n-2], y[n-1], y[n-2]}      
 * </pre>      
 *      
 * \par      
 * The 4 state variables for stage 1 are first, then the 4 state variables for stage 2, and so on.      
 * The state array has a total length of <code>4*numStages</code> values.      
 * The state variables are updated after each block of data is processed, the coefficients are untouched.      
 *      
 * \par Instance Structure      
 * The coefficients and state variables for a filter are stored together in an instance data structure.      
 * A separate instance structure must be defined for each filter.      
 * Coefficient arrays may be shared among several instances while state variable arrays cannot be shared.      
 * There are separate instance structure declarations for each of the 3 supported data types.      
 *      
 * \par Init Functions      
 * There is also an associated initialization function for each data type.      
 * The initialization function performs following operations:      
 * - Sets the values of the internal structure fields.      
 * - Zeros out the values in the state buffer.      
 *      
 * \par      
 * Use of the initialization function is optional.      
 * However, if the initialization function is used, then the instance structure cannot be placed into a const data section.      
 * To place an instance structure into a const data section, the instance structure must be manually initialized.      
 * Set the values in the state buffer to zeros before static initialization.      
 * The code below statically initializes each of the 3 different data type filter instance structures      
 * <pre>      
 *     arm_biquad_casd_df1_inst_f32 S1 = {numStages, pState, pCoeffs};      
 *     arm_biquad_casd_df1_inst_q15 S2 = {numStages, pState, pCoeffs, postShift};      
 *     arm_biquad_casd_df1_inst_q31 S3 = {numStages, pState, pCoeffs, postShift};      
 * </pre>      
 * where <code>numStages</code> is the number of Biquad stages in the filter; <code>pState</code> is the address of the state buffer;      
 * <code>pCoeffs</code> is the address of the coefficient buffer; <code>postShift</code> shift to be applied.      
 *      
 * \par Fixed-Point Behavior      
 * Care must be taken when using the Q15 and Q31 versions of the Biquad Cascade filter functions.      
 * Following issues must be considered:      
 * - Scaling of coefficients      
 * - Filter gain      
 * - Overflow and saturation      
 *      
 * \par      
 * <b>Scaling of coefficients: </b>      
 * Filter coefficients are represented as fractional values and      
 * coefficients are restricted to lie in the range <code>[-1 +1)</code>.      
 * The fixed-point functions have an additional scaling parameter <code>postShift</code>      
 * which allow the filter coefficients to exceed the range <code>[+1 -1)</code>.      
 * At the output of the filter's accumulator is a shift register which shifts the result by <code>postShift</code> bits.      
 * \image html BiquadPostshift.gif "Fixed-point Biquad with shift by postShift bits after accumulator"      
 * This essentially scales the filter coefficients by <code>2^postShift</code>.      
 * For example, to realize the coefficients      
 * <pre>      
 *    {1.5, -0.8, 1.2, 1.6, -0.9}      
 * </pre>      
 * set the pCoeffs array to:      
 * <pre>      
 *    {0.75, -0.4, 0.6, 0.8, -0.45}      
 * </pre>      
 * and set <code>postShift=1</code>      
 *      
 * \par      
 * <b>Filter gain: </b>      
 * The frequency response of a Biquad filter is a function of its coefficients.      
 * It is possible for the gain through the filter to exceed 1.0 meaning that the filter increases the amplitude of certain frequencies.      
 * This means that an input signal with amplitude < 1.0 may result in an output > 1.0 and these are saturated or overflowed based on the implementation of the filter.      
 * To avoid this behavior the filter needs to be scaled down such that its peak gain < 1.0 or the input signal must be scaled down so that the combination of input and filter are never overflowed.      
 *      
 * \par      
 * <b>Overflow and saturation: </b>      
 * For Q15 and Q31 versions, it is described separately as part of the function specific documentation below.      
 */     
     
/**      
 * @addtogroup BiquadCascadeDF1      
 * @{      
 */     
     
/**      
 * @param[in]  *S         points to an instance of the floating-point Biquad cascade structure.      
 * @param[in]  *pSrc      points to the block of input data.      
 * @param[out] *pDst      points to the block of output data.      
 * @param[in]  blockSize  number of samples to process per call.      
 * @return     none.      
 *      
 */     
     
void arm_biquad_cascade_df1_f32(     
  const arm_biquad_casd_df1_inst_f32 * S,     
  float32_t * pSrc,     
  float32_t * pDst,     
  uint32_t blockSize)     
{     
  float32_t *pIn = pSrc;                         /*  source pointer            */     
  float32_t *pOut = pDst;                        /*  destination pointer       */     
  float32_t *pState = S->pState;                 /*  pState pointer            */     
  float32_t *pCoeffs = S->pCoeffs;               /*  coefficient pointer       */     
  float32_t acc;                                 /*  Simulates the accumulator */     
  float32_t b0, b1, b2, a1, a2;                  /*  Filter coefficients       */     
  float32_t Xn1, Xn2, Yn1, Yn2;                  /*  Filter pState variables   */     
  float32_t Xn;                                  /*  temporary input           */     
  uint32_t sample, stage = S->numStages;         /*  loop counters             */     
  float32_t X0, X1, X2;     					 /* Temporary variables to read inputs */  
  float32_t Y0, Y1, Y2, Y3, Y4, Y5, Y6, Y7;	   /* Temporary variables to write outputs */  
  
	do  
	{  
		/* Reading the coefficients */  
		b0 = *pCoeffs++;  
		b1 = *pCoeffs++;  
		b2 = *pCoeffs++;  
		a1 = *pCoeffs++;  
		a2 = *pCoeffs++;  
  
		/* Reading the pState values */  
		Xn2 = pState[0];  
		Xn1 = pState[1];  
		Yn2 = pState[2];  
		Yn1 = pState[3];  
  
		/*; Equation to calculate output of the filter is as follows:  
		; y[n] = b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2]  
		; y[0] = b0*x[0] + b1*x[-1] + b2*x[-2] + a1*y[-1] + a2*y[-2]  
		; y[1] = b0*x[1] + b1*x[0] + b2*x[-1] + a1*y[0] + a2*y[-1]  
		; y[2] = b0*x[2] + b1*x[1] + b2*x[0] + a1*y[1] + a2*y[0]  
		; y[3] = b0*x[3] + b1*x[2] + b2*x[1] + a1*y[2] + a2*y[1]  
		;  
		; y[4] = b0*x[4] + b1*x[3] + b2*x[2] + a1*y[3] + a2*y[2]  
		; y[5] = b0*x[5] + b1*x[4] + b2*x[3] + a1*y[4] + a2*y[3]  
		; y[6] = b0*x[6] + b1*x[5] + b2*x[4] + a1*y[5] + a2*y[4]  
		; y[7] = b0*x[7] + b1*x[6] + b2*x[5] + a1*y[6] + a2*y[5]*/  
   
		/* First part of the processing with loop unrolling.  Compute 8 outputs at a time.    
		** a second loop below computes the remaining 1 to 7 samples. */   
		sample = blockSize >> 3u;  
      
		if(sample > 0)  
		{  
			/* 8 samples calculation is done before and after loop processing */   
			sample = sample - 1u;		  
  
			/*  
			;y[0] = b0*x[0] + b1*x[-1] + b2*x[-2] + a2*y[-2] + a1 * y[-1] //ch1:0  
			;y[1] = b0*x[1] + b1*x[0] + b2*x[-1] + a2 * y[-1]   
			;y[2] = b0*x[2] + b1*x[1] + b2*x[0]   
			;y[3] = b0*x[3] + b1*x[2] + b2*x[1] */			  
  
			/* Read x[0] */  
			X2 = *pIn++;  
			  
  
			/* y[0] = b2*x[-2] */  
			Y0 = (Xn2 * b2);  
			/* y[1] = b2*x[-1] */  
			Y1 = (Xn1 * b2);  
			/* y[2] = b2*x[0] */  
			Y2 = (X2 * b2);  
  
			/* Read x[1] */  
			X0 = *pIn++;  
			  
  
			/* y[3] =  b2*x[1] */  
			Y3 = (X0 * b2);  
  
			/* y[0] += b1*x[-1] */  
			Y0 += (Xn1 * b1);  
			/* y[1] += b1*x[0] */  
			Y1 += (X2 * b1);  
			/* y[2] += b1*x[1] */  
			Y2 += (X0 * b1);  
  
			/* Read x[2] */  
			X1 = *pIn++;  
				  
  
			/* y[0] += b0*x[0] */  
			Y0 += (X2 * b0);  
			/* y[3] += b1*x[2] */  
			Y3 += (X1 * b1);  
			/* y[1] += b0*x[0] */  
			Y1 += (X0 * b0);  
			/* y[2] += b0*x[2] */  
			Y2 += (X1 * b0);  
  
  
			/* y[0] += b1*x[-1] */  
			Y0 += (Yn2 * a2);  
  
			/* Read x[3] */  
			X2 = *pIn++;  
				  
  
			/* y[3] += b0*x[3] */  
			Y3 += (X2 * b0);  
			/* y[1] += a2*y[-1] */  
			Y1 += (Yn1 * a2);  
			/* y[0] += a1*y[-1] */  
			Y0 += (Yn1 * a1);  
  
			while(sample > 0u)   
			{  
  
				/*  
				;y[1] += a1*y[0]				  
				;y[2] += a1*y[1] + a2*y[0]				  
				;y[3] += a1*y[2] + a2*y[1]				       
				;y[4] = b0*x[4] + b1*x[3] + b2*x[2] + a2*y[2]				  
				;y[5] = b0*x[5] + b1*x[4] + b2*x[3] //x in eq of y is for ch1:0				   
				;y[6] = b0*x[6] + b1*x[5] + b2*x[4]  
				;y[7] = b0*x[7] + b1*x[6] + b2*x[5]  
				*/  
		          
				/* Read x[4] */			      
				X0 = *pIn++;  
								  
  
				/* y[4] = b2*x[2] */  
				Y4 = (X1 * b2);  
				/* y[5] = b2*x[3] */  
				Y5 = (X2 * b2);  
				/* y[6] = b2*x[4] */  
				Y6 = (X0 * b2);  
  
				/* Read x[5] */	  
				X1 = *pIn++;  
					  
				  
				Y1 += (Y0 * a1);  
				Y2 += (Y0 * a2);  
				  
				/* y[4] += b1*x[3] */  
				Y4 += (X2 * b1);  
				/* y[5] += b1*x[4] */  
				Y5 += (X0 * b1);  
				/* y[6] += b1*x[5] */  
				Y6 += (X1 * b1);  
  
				Y7 = (X1 * b2);  
  
				/* Read x[6] */				      
				X2 = *pIn++;  
					  
				  
				/* Write y[0] */  
				*pOut++ = Y0;  
				  
				/* y[3] += a2*y[0] */  
				Y3 += (Y1 * a2);  
				/* y[2] += a1*y[1] */  
				Y2 += (Y1 * a1);  
				  
				/* y[4] += b0*x[4] */  
				Y4 += (X0 * b0);  
				/* y[5] += b0*x[5] */  
				Y5 += (X1 * b0);  
				/* y[6] += b0*x[6] */  
				Y6 += (X2 * b0);  
				  
				/* y[3] += a1*y[2] */  
				Y3 += (Y2 * a1);  
				/* y[4] += a2*y[2] */  
				Y4 += (Y2 * a2);  
				/* y[7] += b1*x[6] */  
				Y7 += (X2 * b1);  
				  
				X1 = X2;  
  
				/* Read x[7] */				      
				X2 = *pIn++;  
					  
  
				/* Write y[1] */  
				*pOut++ = Y1;  
				  
				/* y[4] += a1*y[3] */  
				Y4 += (Y3 * a1);  
				/* y[5] += a2*y[3] */  
				Y5 += (Y3 * a2);  
				/* y[7] += b0*x[7] */  
				Y7 += (X2 * b0);    
				  
				/* Write y[2] */  
				*pOut++ = Y2;  
				  
				  
				/* Write y[3] */  
				*pOut++ = Y3;  
				  
				  
				X0 = *pIn++;  
				  
  
				/*  
				;y[0] = b0*x[0] + b1*x[-1] + b2*x[-2] + a2*y[-2] + a1 * y[-1] //ch1:0  
				;y[1] = b0*x[1] + b1*x[0] + b2*x[-1] + a2 * y[-1]   
				;y[2] = b0*x[2] + b1*x[1] + b2*x[0]   
				;y[3] = b0*x[3] + b1*x[2] + b2*x[1] */  
  
				Y0 = (X1 * b2);  
				Y1 = (X2 * b2);  
				Y2 = (X0 * b2);  
				  
				X1 = *pIn++;  
				  
				  
				Y5 += (Y4 * a1);  
				Y6 += (Y4 * a2);   
				  
				Y0 += (X2 * b1);  
				Y1 += (X0 * b1);  
				Y2 += (X1 * b1);  
				  
     			Y3 = (X1 * b2);  
				  
				X2 = *pIn++;  
				  
				  
				/* Write y[4] */  
				*pOut++ = Y4;  
				  
				  
				Y7 += (Y5 * a2);  
				Y6 += (Y5 * a1);  
				  
				Y0 += (X0 * b0);  
				Y1 += (X1 * b0);  
				Y2 += (X2 * b0);  
				  
				Y7 += (Y6 * a1);  
				Y0 += (Y6 * a2);  
				Y3 += (X2 * b1);  
				  
				X1 = X2;  
				  
				X2 = *pIn++;  
				  
				  
				/* Write y[5] */  
				*pOut++ = Y5;  
				  
				  
				Y0 += (Y7 * a1);  
				Y1 += (Y7 * a2);  
				Y3 += (X2 * b0);  
				  
				/* Write y[6] */  
				*pOut++ = Y6;  
				  
				  
				/* Write y[7] */  
				*pOut++ = Y7;  
				   
				  
				  
				/* decrement the loop counter */   
				sample--;   
				  
				  
			}  
  
			/*  
			;y[1] += a1*y[0]				  
			;y[2] += a1*y[1] + a2*y[0]				  
			;y[3] += a1*y[2] + a2*y[1]				       
			;y[4] = b0*x[4] + b1*x[3] + b2*x[2] + a2*y[2]				  
			;y[5] = b0*x[5] + b1*x[4] + b2*x[3] //x in eq of y is for ch1:0				   
			;y[6] = b0*x[6] + b1*x[5] + b2*x[4]  
			;y[7] = b0*x[7] + b1*x[6] + b2*x[5]  
			*/  
  
			X0 = *pIn++;  
			  
  
			Y4 = (X1 * b2);  
			Y5 = (X2 * b2);  
			Y6 = (X0 * b2);  
  
  
			X1 = *pIn++;  
			  
  
			Y1 += (Y0 * a1);  
			Y2 += (Y0 * a2);  
  
			Y4 += (X2 * b1);  
			Y5 += (X0 * b1);  
			Y6 += (X1 * b1);  
  
			Y7 = (X1 * b2);  
  
			X2 = *pIn++;  
			  
  
			*pOut++ = Y0;  
				  
  
			Y3 += (Y1 * a2);  
			Y2 += (Y1 * a1);  
  
			Y4 += (X0 * b0);  
			Y5 += (X1 * b0);  
			Y6 += (X2 * b0);  
  
			Y3 += (Y2 * a1);  
			Y4 += (Y2 * a2);  
  
			Y7 += (X2 * b1);  
  
			X1 = X2;  
  
			X2 = *pIn++;  
				  
  
			*pOut++ = Y1;  
			  
  
			Y4 += (Y3 * a1);  
			Y5 += (Y3 * a2);  
			Y7 += (X2 * b0);    
  
			*pOut++ = Y2;  
			  
  
			*pOut++ = Y3;  
			  
  
			Y5 += (Y4 * a1);  
			Y6 += (Y4 * a2);   
			Y6 += (Y5 * a1);  
			Y7 += (Y5 * a2);   
			Y7 += (Y6 * a1);  
  
			*pOut++ = Y4;  
			  
  
			*pOut++ = Y5;  
			  
  
			*pOut++ = Y6;  
			  
  
			*pOut++ = Y7;  
			   
  
  
			Xn2 = X1;  
			Xn1 = X2;  
			Yn2 = Y6;  
			Yn1 = Y7;  
  
		}  
  
		/* If the blockSize is not a multiple of 8, compute any remaining output samples here.     
			** No loop unrolling is used. */  
		sample = (blockSize & 0x7u);   
  
		while(sample > 0u)  
		{  
			/* Read the input */  
			Xn = *pIn++;  
  
			/* acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2] */  
			acc = (b0 * Xn) + (b1 * Xn1) + (b2 * Xn2) + (a1 * Yn1) + (a2 * Yn2);  
  
			/* Store the result in the accumulator in the destination buffer. */  
			*pOut++ = acc;  
  
			/* Every time after the output is computed state should be updated. */  
			/* The states should be updated as:    */  
			/* Xn2 = Xn1    */  
			/* Xn1 = Xn     */  
			/* Yn2 = Yn1    */  
			/* Yn1 = acc   */  
			Xn2 = Xn1;  
			Xn1 = Xn;  
			Yn2 = Yn1;  
			Yn1 = acc;  
  
			/* decrement the loop counter */  
			sample--;  
  
		}  
  
		/*  Store the updated state variables back into the pState array */  
		*pState++ = Xn2;  
		*pState++ = Xn1;  
		*pState++ = Yn2;  
		*pState++ = Yn1;  
  
		/*  The first stage goes from the input buffer to the output buffer. */  
		/*  Subsequent numStages  occur in-place in the output buffer */  
		pIn = pDst;  
  
		/* Reset the output pointer */  
		pOut = pDst;  
  
		/* decrement the loop counter */  
		stage--;  
  
	} while(stage > 0u);  
  
  
     
}     
     
     
  /**      
   * @} end of BiquadCascadeDF1 group      
   */     
