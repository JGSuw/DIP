/** @file etpwm.h
*   @brief ETPWM Driver Header File
*   @date 22.June.2012
*   @version 03.02.00
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the ETPWM driver.
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

#ifndef __ETPWM_H__
#define __ETPWM_H__

// **************************************************************************
// the includes

#include "sys_common.h"


//!
//! \defgroup ETPWM

//!
//! \ingroup ETPWM
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines


//! \brief Defines the base address of the pulse width modulation (ETPWM) 1 registers
//!
#define ETPWM_ETPWM1_BASE_ADDR          (0x00006800)

//! \brief Defines the base address of the pulse width modulation (ETPWM) 2 registers
//!
#define ETPWM_ETPWM2_BASE_ADDR          (0x00006840)

//! \brief Defines the base address of the pulse width modulation (ETPWM) 3 registers
//!
#define ETPWM_ETPWM3_BASE_ADDR          (0x00006880)

//! \brief Defines the base address of the pulse width modulation (ETPWM) 4 registers
//!
#define ETPWM_ETPWM4_BASE_ADDR          (0x000068C0)

//! \brief Defines the base address of the pulse width modulation (ETPWM) 5 registers
//!
#define ETPWM_ETPWM5_BASE_ADDR          (0x00006900)

//! \brief Defines the base address of the pulse width modulation (ETPWM) 6 registers
//!
#define ETPWM_ETPWM6_BASE_ADDR          (0x00006940)

//! \brief Defines the base address of the pulse width modulation (ETPWM) 7 registers
//!
#define ETPWM_ETPWM7_BASE_ADDR          (0x00006980)


//! \brief Defines the location of the ZRO bits in the AQCTL register
//!
#define ETPWM_AQCTL_ZRO_BITS              (3 << 0)

//! \brief Defines the location of the PRD bits in the AQCTL register
//!
#define ETPWM_AQCTL_PRD_BITS              (3 << 2)

//! \brief Defines the location of the CAU bits in the AQCTL register
//!
#define ETPWM_AQCTL_CAU_BITS              (3 << 4)

//! \brief Defines the location of the CAD bits in the AQCTL register
//!
#define ETPWM_AQCTL_CAD_BITS              (3 << 6)

//! \brief Defines the location of the CBU bits in the AQCTL register
//!
#define ETPWM_AQCTL_CBU_BITS              (3 << 8)

//! \brief Defines the location of the CBD bits in the AQCTL register
//!
#define ETPWM_AQCTL_CBD_BITS              (3 << 10)


//! \brief Defines the location of the LOADAMODE bits in the CMPCTL register
//!
#define ETPWM_CMPCTL_LOADAMODE_BITS       (3 << 0)

//! \brief Defines the location of the LOADBMODE bits in the CMPCTL register
//!
#define ETPWM_CMPCTL_LOADBMODE_BITS       (3 << 2)

//! \brief Defines the location of the SHDWAMODE bits in the CMPCTL register
//!
#define ETPWM_CMPCTL_SHDWAMODE_BITS       (1 << 4)

//! \brief Defines the location of the SHDWBMODE bits in the CMPCTL register
//!
#define ETPWM_CMPCTL_SHDWBMODE_BITS       (1 << 6)

//! \brief Defines the location of the SHDWAFULL bits in the CMPCTL register
//!
#define ETPWM_CMPCTL_SHDWAFULL_BITS       (1 << 8)

//! \brief Defines the location of the SHDWBFULL bits in the CMPCTL register
//!
#define ETPWM_CMPCTL_SHDWBFULL_BITS       (1 << 9)


//! \brief Defines the location of the OUTMODE bits in the DBCTL register
//!
#define ETPWM_DBCTL_OUTMODE_BITS          (3 << 0)

//! \brief Defines the location of the POLSEL bits in the DBCTL register
//!
#define ETPWM_DBCTL_POLSEL_BITS           (3 << 2)

//! \brief Defines the location of the INMODE bits in the DBCTL register
//!
#define ETPWM_DBCTL_INMODE_BITS           (3 << 4)

//! \brief Defines the location of the HALFCYCLE bits in the DBCTL register
//!
#define ETPWM_DBCTL_HALFCYCLE_BITS        (1 << 15)


//! \brief Defines the location of the ETCR bits in the ETCLR register
//!
#define ETPWM_ETCLR_INT_BITS              (1 << 0)

//! \brief Defines the location of the SOCA bits in the ETCLR register
//!
#define ETPWM_ETCLR_SOCA_BITS             (1 << 2)

//! \brief Defines the location of the SOCB bits in the ETCLR register
//!
#define ETPWM_ETCLR_SOCB_BITS             (1 << 3)


//! \brief Defines the location of the INTPRD bits in the ETPS register
//!
#define ETPWM_ETPS_INTPRD_BITS            (3 << 0)

//! \brief Defines the location of the INTCNT bits in the ETPS register
//!
#define ETPWM_ETPS_INTCNT_BITS            (3 << 2)

//! \brief Defines the location of the SOCAPRD bits in the ETPS register
//!
#define ETPWM_ETPS_SOCAPRD_BITS           (3 << 8)

//! \brief Defines the location of the SOCACNT bits in the ETPS register
//!
#define ETPWM_ETPS_SOCACNT_BITS           (3 << 10)

//! \brief Defines the location of the SOCBPRD bits in the ETPS register
//!
#define ETPWM_ETPS_SOCBPRD_BITS           (3 << 12)

//! \brief Defines the location of the SOCBCNT bits in the ETPS register
//!
#define ETPWM_ETPS_SOCBCNT_BITS           (3 << 14)


//! \brief Defines the location of the INTSEL bits in the ETSEL register
//!
#define ETPWM_ETSEL_INTSEL_BITS           (7 << 0)

//! \brief Defines the location of the INTEN bits in the ETSEL register
//!
#define ETPWM_ETSEL_INTEN_BITS            (1 << 3)

//! \brief Defines the location of the SOCASEL bits in the ETSEL register
//!
#define ETPWM_ETSEL_SOCASEL_BITS          (7 << 8)

//! \brief Defines the location of the SOCAEN bits in the ETSEL register
//!
#define ETPWM_ETSEL_SOCAEN_BITS           (1 << 11)

//! \brief Defines the location of the SOCBSEL bits in the ETSEL register
//!
#define ETPWM_ETSEL_SOCBSEL_BITS          (7 << 12)

//! \brief Defines the location of the SOCBEN bits in the ETSEL register
//!
#define ETPWM_ETSEL_SOCBEN_BITS           (1 << 15)


//! \brief Defines the location of the CHPEN bits in the PCCTL register
//!
#define ETPWM_PCCTL_CHPEN_BITS            (1 << 0)

//! \brief Defines the location of the OSHTWTH bits in the PCCTL register
//!
#define ETPWM_PCCTL_OSHTWTH_BITS          (15 << 1)

//! \brief Defines the location of the CHPFREQ bits in the PCCTL register
//!
#define ETPWM_PCCTL_CHPFREQ_BITS          (7 << 5)

//! \brief Defines the location of the CHPDUTY bits in the PCCTL register
//!
#define ETPWM_PCCTL_CHPDUTY_BITS          (7 << 8)



//! \brief Defines the location of the CTRMODE bits in the TBCTL register
//!
#define ETPWM_TBCTL_CTRMODE_BITS          (3 << 0)

//! \brief Defines the location of the PHSEN bits in the TBCTL register
//!
#define ETPWM_TBCTL_PHSEN_BITS            (1 << 2)

//! \brief Defines the location of the PRDLD bits in the TBCTL register
//!
#define ETPWM_TBCTL_PRDLD_BITS            (1 << 3)

//! \brief Defines the location of the SYNCOSEL bits in the TBCTL register
//!
#define ETPWM_TBCTL_SYNCOSEL_BITS         (3 << 4)

//! \brief Defines the location of the SWFSYNC bits in the TBCTL register
//!
#define ETPWM_TBCTL_SWFSYNC_BITS          (1 << 6)

//! \brief Defines the location of the HSPCLKDIV bits in the TBCTL register
//!
#define ETPWM_TBCTL_HSPCLKDIV_BITS        (7 << 7)

//! \brief Defines the location of the CLKDIV bits in the TBCTL register
//!
#define ETPWM_TBCTL_CLKDIV_BITS           (7 << 10)

//! \brief Defines the location of the PHSDIR bits in the TBCTL register
//!
#define ETPWM_TBCTL_PHSDIR_BITS           (1 << 13)

//! \brief Defines the location of the FREESOFT bits in the TBCTL register
//!
#define ETPWM_TBCTL_FREESOFT_BITS         (3 << 14)


//! \brief Defines the location of the INT bits in the TXCLR register
//!
#define ETPWM_TZCLR_INT_BITS              (1 << 0)

//! \brief Defines the location of the CBC bits in the TXCLR register
//!
#define ETPWM_TZCLR_CBC_BITS              (1 << 1)

//! \brief Defines the location of the OST bits in the TXCLR register
//!
#define ETPWM_TZCLR_OST_BITS              (1 << 2)

//! \brief Defines the location of the DCAEVT1 bits in the TXCLR register
//!
#define ETPWM_TZCLR_DCAEVT1_BITS          (1 << 3)

//! \brief Defines the location of the DCAEVT2 bits in the TXCLR register
//!
#define ETPWM_TZCLR_DCAEVT2_BITS          (1 << 4)

//! \brief Defines the location of the DCBEVT1 bits in the TXCLR register
//!
#define ETPWM_TZCLR_DCBEVT1_BITS          (1 << 5)

//! \brief Defines the location of the DCBEVT2 bits in the TXCLR register
//!
#define ETPWM_TZCLR_DCBEVT2_BITS          (1 << 6)


//! \brief Defines the location of the TZA bits in the TZCTL register
//!
#define ETPWM_TZCTL_TZA_BITS              (3 << 0)

//! \brief Defines the location of the  TZB bits in the TZCTL register
//!
#define ETPWM_TZCTL_TZB_BITS              (3 << 2)

//! \brief Defines the location of the DCAEVT1 bits in the TZCTL register
//!
#define ETPWM_TZCTL_DCAEVT1_BITS          (3 << 4)

//! \brief Defines the location of the DCAEVT2 bits in the TZCTL register
//!
#define ETPWM_TZCTL_DCAEVT2_BITS          (3 << 6)

//! \brief Defines the location of the DCBEVT1 bits in the TZCTL register
//!
#define ETPWM_TZCTL_DCBEVT1_BITS          (3 << 8)

//! \brief Defines the location of the DCBEVT2 bits in the TZCTL register
//!
#define ETPWM_TZCTL_DCBEVT2_BITS          (3 << 10)


//! \brief Defines the location of the CBC bits in the TZFRC register
//!
#define ETPWM_TZFRC_CBC_BITS              (1 << 1)

//! \brief Defines the location of the OST bits in the TZFRC register
//!
#define ETPWM_TZFRC_OST_BITS              (1 << 2)

//! \brief Defines the location of the DCAEVT1 bits in the TZFRC register
//!
#define ETPWM_TZFRC_DCAEVT1_BITS          (1 << 3)

//! \brief Defines the location of the DCAEVT2 bits in the TZFRC register
//!
#define ETPWM_TZFRC_DCAEVT2_BITS          (1 << 4)

//! \brief Defines the location of the DCBEVT1 bits in the TZFRC register
//!
#define ETPWM_TZFRC_DCBEVT1_BITS          (1 << 5)

//! \brief Defines the location of the DCBEVT2 bits in the TZFRC register
//!
#define ETPWM_TZFRC_DCBEVT2_BITS          (1 << 6)


// **************************************************************************
// the typedefs

//! \brief Enumeration to define the pulse width modulation (ETPWM) action qualifiers
//!
typedef enum
{
  ETPWM_ActionQual_Disabled=0,
  ETPWM_ActionQual_Clear,
  ETPWM_ActionQual_Set,
  ETPWM_ActionQual_Toggle
} ETPWM_ActionQual_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) clock dividers
//!
typedef enum
{
  ETPWM_ClkDiv_by_1=(0 << 10),
  ETPWM_ClkDiv_by_2=(1 << 10),
  ETPWM_ClkDiv_by_4=(2 << 10),
  ETPWM_ClkDiv_by_8=(3 << 10),
  ETPWM_ClkDiv_by_16=(4 << 10),
  ETPWM_ClkDiv_by_32=(5 << 10),
  ETPWM_ClkDiv_by_64=(6 << 10),
  ETPWM_ClkDiv_by_128=(7 << 10)
} ETPWM_ClkDiv_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) chopping clock frequencies
//!
typedef enum
{
  ETPWM_ChoppingClkFreq_SysClkOut_by_1=(0 << 5),
  ETPWM_ChoppingClkFreq_SysClkOut_by_2=(1 << 5),
  ETPWM_ChoppingClkFreq_SysClkOut_by_3=(2 << 5),
  ETPWM_ChoppingClkFreq_SysClkOut_by_4=(3 << 5),
  ETPWM_ChoppingClkFreq_SysClkOut_by_5=(4 << 5),
  ETPWM_ChoppingClkFreq_SysClkOut_by_6=(5 << 5),
  ETPWM_ChoppingClkFreq_SysClkOut_by_7=(6 << 5),
  ETPWM_ChoppingClkFreq_SysClkOut_by_8=(7 << 5)
} ETPWM_ChoppingClkFreq_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) chopping clock duty cycles
//!
typedef enum
{
  ETPWM_ChoppingDutyCycle_One_Eighth=(0 << 8),
  ETPWM_ChoppingDutyCycle_Two_Eighths=(1 << 8),
  ETPWM_ChoppingDutyCycle_Three_Eighths=(2 << 8),
  ETPWM_ChoppingDutyCycle_Four_Eighths=(3 << 8),
  ETPWM_ChoppingDutyCycle_Five_Eighths=(4 << 8),
  ETPWM_ChoppingDutyCycle_Six_Eighths=(5 << 8),
  ETPWM_ChoppingDutyCycle_Seven_Eighths=(6 << 8)
} ETPWM_ChoppingDutyCycle_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) chopping clock pulse widths
//!
typedef enum
{
  ETPWM_ChoppingPulseWidth_One_Eighth_SysClkOut=(0 << 1),
  ETPWM_ChoppingPulseWidth_Two_Eighths_SysClkOut=(1 << 1),
  ETPWM_ChoppingPulseWidth_Three_Eighths_SysClkOut=(2 << 1),
  ETPWM_ChoppingPulseWidth_Four_Eighths_SysClkOut=(3 << 1),
  ETPWM_ChoppingPulseWidth_Five_Eighths_SysClkOut=(4 << 1),
  ETPWM_ChoppingPulseWidth_Six_Eighths_SysClkOut=(5 << 1),
  ETPWM_ChoppingPulseWidth_Seven_Eighths_SysClkOut=(6 << 1),
  ETPWM_ChoppingPulseWidth_Eight_Eighths_SysClkOut=(7 << 1),
  ETPWM_ChoppingPulseWidth_Nine_Eighths_SysClkOut=(8 << 1),
  ETPWM_ChoppingPulseWidth_Ten_Eighths_SysClkOut=(9 << 1),
  ETPWM_ChoppingPulseWidth_Eleven_Eighths_SysClkOut=(10 << 1),
  ETPWM_ChoppingPulseWidth_Twelve_Eighths_SysClkOut=(11 << 1),
  ETPWM_ChoppingPulseWidth_Thirteen_Eighths_SysClkOut=(12 << 1),
  ETPWM_ChoppingPulseWidth_Fourteen_Eighths_SysClkOut=(13 << 1),
  ETPWM_ChoppingPulseWidth_Fifteen_Eighths_SysClkOut=(14 << 1),
  ETPWM_ChoppingPulseWidth_Sixteen_Eighths_SysClkOut=(15 << 1)
} ETPWM_ChoppingPulseWidth_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) counter modes
//!
typedef enum
{
  ETPWM_CounterMode_Up=(0 << 0),
  ETPWM_Countermode_Down=(1 << 0),
  ETPWM_CounterMode_UpDown=(2 << 0),
  ETPWM_CounterMode_Stop=(3 << 0)
} ETPWM_CounterMode_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) deadband options
//!
typedef enum
{
  ETPWM_DeadBandInputMode_ETPWMxA_Rising_and_Falling=(0 << 4),
  ETPWM_DeadBandInputMode_ETPWMxA_Falling_ETPWMxB_Rising=(1 << 4),
  ETPWM_DeadBandInputMode_ETPWMxA_Rising_ETPWMxB_Falling=(2 << 4),
  ETPWM_DeadBandInputMode_ETPWMxB_Rising_and_Falling=(3 << 4)
} ETPWM_DeadBandInputMode_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) deadband output modes
//!
typedef enum
{
  ETPWM_DeadBandOutputMode_Bypass=(0 << 0),
  ETPWM_DeadBandOutputMode_ETPWMxA_Disable_ETPWMxB_Falling=(1 << 0),
  ETPWM_DeadBandOutputMode_ETPWMxA_Rising_ETPWMxB_Disable=(2 << 0),
  ETPWM_DeadBandOutputMode_ETPWMxA_Rising_ETPWMxB_Falling=(3 << 0)
} ETPWM_DeadBandOutputMode_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) deadband polarity
//!
typedef enum
{
  ETPWM_DeadBandPolarity_ETPWMxA_ETPWMxB=(0 << 2),
  ETPWM_DeadBandPolarity_ETPWMxA_Inverted=(1 << 2),
  ETPWM_DeadBandPolarity_ETPWMxB_Inverted=(2 << 2),
  ETPWM_DeadBandPolarity_ETPWMxA_Inverted_ETPWMxB_Inverted=(3 << 2)
} ETPWM_DeadBandPolarity_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) high speed clock divide options
//!
typedef enum
{
  ETPWM_HspClkDiv_by_1=(0 << 7),
  ETPWM_HspClkDiv_by_2=(1 << 7),
  ETPWM_HspClkDiv_by_4=(2 << 7),
  ETPWM_HspClkDiv_by_6=(3 << 7),
  ETPWM_HspClkDiv_by_8=(4 << 7),
  ETPWM_HspClkDiv_by_10=(5 << 7),
  ETPWM_HspClkDiv_by_12=(6 << 7),
  ETPWM_HspClkDiv_by_14=(7 << 7)
} ETPWM_HspClkDiv_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) interrupt generation modes
//!
typedef enum
{
  ETPWM_IntMode_CounterEqualZero=(1 << 0),
  ETPWM_IntMode_CounterEqualPeriod=(2 << 0),
  ETPWM_IntMode_CounterEqualZeroOrPeriod=(3 << 0),
  ETPWM_IntMode_CounterEqualCmpAIncr=(4 << 0),
  ETPWM_IntMode_CounterEqualCmpADecr=(5 << 0),
  ETPWM_IntMode_CounterEqualCmpBIncr=(6 << 0),
  ETPWM_IntMode_CounterEqualCmpBDecr=(7 << 0)
} ETPWM_IntMode_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) interrupt period options
//!
typedef enum
{
  ETPWM_IntPeriod_Disable=(0 << 0),
  ETPWM_IntPeriod_FirstEvent=(1 << 0),
  ETPWM_IntPeriod_SecondEvent=(2 << 0),
  ETPWM_IntPeriod_ThirdEvent=(3 << 0)
} ETPWM_IntPeriod_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) load modes
//!
typedef enum
{
  ETPWM_LoadMode_Zero=0,
  ETPWM_LoadMode_Period,
  ETPWM_LoadMode_Either,
  ETPWM_LoadMode_Freeze
} ETPWM_LoadMode_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) numbers
//!
typedef enum
{
  ETPWM_Number_1=0,
  ETPWM_Number_2,
  ETPWM_Number_3,
  ETPWM_Number_4,
  ETPWM_Number_5,
  ETPWM_Number_6,
  ETPWM_Number_7
} ETPWM_Number_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) period load options
//!
typedef enum
{
  ETPWM_PeriodLoad_Shadow=(0 << 3),
  ETPWM_PeriodLoad_Immediate=(1 << 3)
} ETPWM_PeriodLoad_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) phase direction modes
//!
typedef enum
{
  ETPWM_PhaseDir_CountDown=(0 << 13),
  ETPWM_PhaseDir_CountUp=(1 << 13)
} ETPWM_PhaseDir_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) run modes
//!
typedef enum
{
  ETPWM_RunMode_SoftStopAfterIncr=(0 << 14),
  ETPWM_RunMode_SoftStopAfterDecr=(0 << 14),
  ETPWM_RunMode_SoftStopAfterCycle=(1 << 14),
  ETPWM_RunMode_FreeRun=(2 << 14)
} ETPWM_RunMode_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) shadow modes
//!
typedef enum
{
  ETPWM_ShadowMode_Shadow=0,
  ETPWM_ShadowMode_Immediate
} ETPWM_ShadowMode_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) shadow status options
//!
typedef enum
{
  ETPWM_ShadowStatus_NotFull=0,
  ETPWM_ShadowStatus_Full
} ETPWM_ShadowStatus_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) start of conversion (SOC) period options
//!
typedef enum
{
  ETPWM_SocPeriod_Disable=0,
  ETPWM_SocPeriod_FirstEvent,
  ETPWM_SocPeriod_SecondEvent,
  ETPWM_SocPeriod_ThirdEvent
} ETPWM_SocPeriod_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) start of conversion (SOC) sources
//!
typedef enum
{
  ETPWM_SocPulseSrc_DcEvt=0,
  ETPWM_SocPulseSrc_CounterEqualZero,
  ETPWM_SocPulseSrc_CounterEqualPeriod,
  ETPWM_SocPulseSrc_CounterEqualZeroOrPeriod,
  ETPWM_SocPulseSrc_CounterEqualCmpAIncr,
  ETPWM_SocPulseSrc_CounterEqualCmpADecr,
  ETPWM_SocPulseSrc_CounterEqualCmpBIncr,
  ETPWM_SocPulseSrc_CounterEqualCmpBDecr
} ETPWM_SocPulseSrc_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) sync modes
//!
typedef enum
{
  ETPWM_SyncMode_ETPWMxSYNC=(0 << 4),
  ETPWM_SyncMode_CounterEqualZero=(1 << 4),
  ETPWM_SyncMode_CounterEqualCounterCompareZero=(2 << 4),
  ETPWM_SyncMode_Disable=(3 << 4)
} ETPWM_SyncMode_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) trip zone sources
//!
typedef enum
{
  ETPWM_TripZoneSrc_CycleByCycle_TZ1_NOT=(1 << 0),
  ETPWM_TripZoneSrc_CycleByCycle_TZ2_NOT=(1 << 1),
  ETPWM_TripZoneSrc_CycleByCycle_TZ3_NOT=(1 << 2),
  ETPWM_TripZoneSrc_CycleByCycle_TZ4_NOT=(1 << 3),
  ETPWM_TripZoneSrc_CycleByCycle_TZ5_NOT=(1 << 4),
  ETPWM_TripZoneSrc_CycleByCycle_TZ6_NOT=(1 << 5),
  ETPWM_TripZoneSrc_CycleByCycle_CmpA=(1 << 6),
  ETPWM_TripZoneSrc_CycleByCycle_CmpB=(1 << 7),
  ETPWM_TripZoneSrc_OneShot_TZ1_NOT=(1 << 8),
  ETPWM_TripZoneSrc_OneShot_TZ2_NOT=(1 << 9),
  ETPWM_TripZoneSrc_OneShot_TZ3_NOT=(1 << 10),
  ETPWM_TripZoneSrc_OneShot_TZ4_NOT=(1 << 11),
  ETPWM_TripZoneSrc_OneShot_TZ5_NOT=(1 << 12),
  ETPWM_TripZoneSrc_OneShot_TZ6_NOT=(1 << 13),
  ETPWM_TripZoneSrc_OneShot_CmpA=(1 << 14),
  ETPWM_TripZoneSrc_OneShot_CmpB=(1 << 15)
} ETPWM_TripZoneSrc_e;


//! \brief Enumeration to define the pulse width modulation (ETPWM) trip zone states
//!
typedef enum
{
  ETPWM_TripZoneState_HighImp=0,
  ETPWM_TripZoneState_ETPWM_High,
  ETPWM_TripZoneState_ETPWM_Low,
  ETPWM_TripZoneState_DoNothing
} ETPWM_TripZoneState_e;


typedef enum
{
  NO_EVENT=0,
  CTR_ZERO=1,
  CTR_PRD=2,
  CTR_ZERO_PRD=3,
  CTR_UP_CMPA=4,
  CTR_D0WM_CMPA=5,
  CTR_UP_CMPB=6,
  CTR_D0WM_CMPB=7
} ETPWM_Event_e;

typedef enum
{
  DCAEVT1=0,
  DCBEVT1=0
} ETPWM_DCEvent_e;

typedef enum
{
  PWMA_RED_FED=0,
  PWMA_FED_PWMB_RED=1,
  PWMA_RED_PWMB_FED=2,
  PWMB_RED_FED=3
} ETPWM_DeadBandInput_e;

typedef enum
{
  PWMA_PWMB_NIL=0,
  PWMA_NIL_PWMB_FED=1,
  PWMA_RED_PWMB_NIL=2,
  PWMB_FED_PWMA_RED=3
} ETPWM_DeadBandOutput_e;

//! \brief Defines the pulse width modulation (ETPWM) object
//!

#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1)) 

typedef struct _etpwmBASE_t_
{

    uint16_t TBCTL;           /**<  0x0000 Time-Base Control Register*/
    uint16_t TBSTS;           /**<  0x0002 Time-Base Status Register*/
    uint16_t TBPHSHR;         /**<  0x0004 Extension for HRPWM Phase Register*/
    uint16_t TBPHS;           /**<  0x0006 Time-Base Phase Register*/
    uint16_t TBCTR;           /**<  0x0008 Time-Base Counter Register*/
    uint16_t TBPRD;           /**<  0x000A Time-Base Period Register*/
    uint16_t TBPRDHR;         /**<  0x000C Time Base Period High Resolution Register*/
    uint16_t CMPCTL;          /**<  0x000E Counter-Compare Control Register*/
    uint16_t CMPAHR;          /**<  0x0010 Extension for HRPWM Counter-Compare A Register*/
    uint16_t CMPA;            /**<  0x0012 Counter-Compare A Register*/
    uint16_t CMPB;            /**<  0x0014 Counter-Compare B Register*/
    uint16_t AQCTLA;          /**<  0x0016 Action-Qualifier Control Register for Output A (ETPWMxA)*/
    uint16_t AQCTLB;          /**<  0x0018 Action-Qualifier Control Register for Output B (ETPWMxB)*/
    uint16_t AQSFRC;          /**<  0x001A Action-Qualifier Software Force Register*/
    uint16_t AQCSFRC;         /**<  0x001C Action-Qualifier Continuous S/W Force Register Set*/
    uint16_t DBCTL;           /**<  0x001E Dead-Band Generator Control Register*/
    uint16_t DBRED;           /**<  0x0020 Dead-Band Generator Rising Edge Delay Count Register*/
    uint16_t DBFED;           /**<  0x0022 Dead-Band Generator Falling Edge Delay Count Register*/
    uint16_t TZSEL;           /**<  0x0024 Trip-Zone Select Register*/
    uint16_t TZDCSEL;         /**<  0x0026 Trip Zone Digital Compare Select Register*/
    uint16_t TZCTL;           /**<  0x0028 Trip-Zone Control Register*/
    uint16_t TZEINT;          /**<  0x002A Trip-Zone Enable Interrupt Register*/
    uint16_t TZFLG;           /**<  0x002C Trip-Zone Flag Register*/
    uint16_t TZCLR;           /**<  0x002E Trip-Zone Clear Register*/
    uint16_t TZFRC;           /**<  0x0030 Trip-Zone Force Register*/
    uint16_t ETSEL;           /**<  0x0032 Event-Trigger Selection Register*/
    uint16_t ETPS;            /**<  0x0034 Event-Trigger Pre-Scale Register*/
    uint16_t ETFLG;           /**<  0x0036 Event-Trigger Flag Register*/
    uint16_t ETCLR;           /**<  0x0038 Event-Trigger Clear Register*/
    uint16_t ETFRC;           /**<  0x003A Event-Trigger Force Register*/
    uint16_t PCCTL;           /**<  0x003C PWM-Chopper Control Register*/
    uint16_t   rsvd_1;        /**<  0x003C Reserved*/
    uint16_t HRCNFG;          /**<  0x003E HRPWM Configuration Register*/
    uint16_t HRPWR;           /**<  0x0040 HRPWM Power Register*/
    uint16_t   rsvd_2;        /**<  0x0042 Reserved*/
    uint16_t   rsvd_3;        /**<  0x0044 Reserved*/
    uint16_t   rsvd_4;        /**<  0x0046 Reserved*/
    uint16_t   rsvd_5;        /**<  0x0048 Reserved*/
    uint16_t HRMSTEP;         /**<  0x004A HRPWM MEP Step Register*/
    uint16_t   rsvd_6;        /**<  0x004C Reserved*/
    uint16_t HRPCTL;          /**<  0x004E High Resolution Period Control Register*/
    uint16_t   rsvd_7;        /**<  0x0050 Reserved*/
    uint16_t TBPRDHRM;        /**<  0x0052 Time Base Period High Resolution Register Mirror*/
    uint16_t TBPRDM;          /**<  0x0054 Time Base Period Register Mirror*/
    uint16_t CMPAHRM;         /**<  0x0056 Compare A High Resolution Register Mirror*/
    uint16_t CMPAM;           /**<  0x0058 Compare A Register Mirror*/
    uint16_t DCTRIPSEL;       /**<  0x005A Digital Compare Trip Select Register*/
    uint16_t DCACTL;          /**<  0x005C Digital Compare A Control Register*/
    uint16_t DCBCTL;          /**<  0x005E Digital Compare B Control Register*/
    uint16_t DCFCTL;          /**<  0x0060 Digital Compare Filter Control Register*/
    uint16_t DCCAPCTL;        /**<  0x0062 Digital Compare Capture Control Register*/
    uint16_t DCFOFFSET;       /**<  0x0064 Digital Compare Filter Offset Register*/
    uint16_t DCFOFFSETCNT;    /**<  0x0066 Digital Compare Filter Offset Counter Register*/
    uint16_t DCFWINDOW;       /**<  0x0068 Digital Compare Filter Window Register*/
    uint16_t DCFWINDOWCNT;    /**<  0x006A Digital Compare Filter Window Counter Register*/
    uint16_t DCCAP;           /**<  0x006C Digital Compare Counter Capture Register*/

} etpwmBASE_t;

#else

typedef struct _etpwmBASE_t_
{

    uint16_t TBSTS;           /**<  0x0002 Time-Base Status Register*/
    uint16_t TBCTL;           /**<  0x0000 Time-Base Control Register*/
    uint16_t TBPHS;           /**<  0x0006 Time-Base Phase Register*/
    uint16_t TBPHSHR;         /**<  0x0004 Extension for HRPWM Phase Register*/
    uint16_t TBPRD;           /**<  0x000A Time-Base Period Register*/
    uint16_t TBCTR;           /**<  0x0008 Time-Base Counter Register*/
    uint16_t CMPCTL;          /**<  0x000E Counter-Compare Control Register*/
    uint16_t TBPRDHR;         /**<  0x000C Time Base Period High Resolution Register*/
    uint16_t CMPA;            /**<  0x0012 Counter-Compare A Register*/
    uint16_t CMPAHR;          /**<  0x0010 Extension for HRPWM Counter-Compare A Register*/
    uint16_t AQCTLA;          /**<  0x0016 Action-Qualifier Control Register for Output A (ETPWMxA)*/
    uint16_t CMPB;            /**<  0x0014 Counter-Compare B Register*/
    uint16_t AQSFRC;          /**<  0x001A Action-Qualifier Software Force Register*/
    uint16_t AQCTLB;          /**<  0x0018 Action-Qualifier Control Register for Output B (EETPWMxB)*/
    uint16_t DBCTL;           /**<  0x001E Dead-Band Generator Control Register*/
    uint16_t AQCSFRC;         /**<  0x001C Action-Qualifier Continuous S/W Force Register Set*/
    uint16_t DBFED;           /**<  0x0022 Dead-Band Generator Falling Edge Delay Count Register*/
    uint16_t DBRED;           /**<  0x0020 Dead-Band Generator Rising Edge Delay Count Register*/
    uint16_t TZDCSEL;         /**<  0x0026 Trip Zone Digital Compare Select Register*/
    uint16_t TZSEL;           /**<  0x0024 Trip-Zone Select Register*/
    uint16_t TZEINT;          /**<  0x002A Trip-Zone Enable Interrupt Register*/
    uint16_t TZCTL;           /**<  0x0028 Trip-Zone Control Register*/
    uint16_t TZCLR;           /**<  0x002E Trip-Zone Clear Register*/
    uint16_t TZFLG;           /**<  0x002C Trip-Zone Flag Register*/
    uint16_t ETSEL;           /**<  0x0032 Event-Trigger Selection Register*/
    uint16_t TZFRC;           /**<  0x0030 Trip-Zone Force Register*/
    uint16_t ETFLG;           /**<  0x0036 Event-Trigger Flag Register*/
    uint16_t ETPS;            /**<  0x0034 Event-Trigger Pre-Scale Register*/
    uint16_t ETFRC;           /**<  0x003A Event-Trigger Force Register*/
    uint16_t ETCLR;           /**<  0x0038 Event-Trigger Clear Register*/
    uint16_t   rsvd_1;        /**<  0x003C Reserved*/
    uint16_t PCCTL;           /**<  0x003C PWM-Chopper Control Register*/
    uint16_t HRPWR;           /**<  0x0040 HRPWM Power Register*/
    uint16_t HRCNFG;          /**<  0x003E HRPWM Configuration Register*/
    uint16_t   rsvd_3;        /**<  0x0044 Reserved*/
    uint16_t   rsvd_2;        /**<  0x0042 Reserved*/
    uint16_t   rsvd_5;        /**<  0x0048 Reserved*/
    uint16_t   rsvd_4;        /**<  0x0046 Reserved*/
    uint16_t   rsvd_6;        /**<  0x004C Reserved*/
    uint16_t HRMSTEP;         /**<  0x004A HRPWM MEP Step Register*/
    uint16_t   rsvd_7;        /**<  0x0050 Reserved*/
    uint16_t HRPCTL;          /**<  0x004E High Resolution Period Control Register*/
    uint16_t TBPRDM;          /**<  0x0054 Time Base Period Register Mirror*/
    uint16_t TBPRDHRM;        /**<  0x0052 Time Base Period High Resolution Register Mirror*/
    uint16_t CMPAM;           /**<  0x0058 Compare A Register Mirror*/
    uint16_t CMPAHRM;         /**<  0x0056 Compare A High Resolution Register Mirror*/
    uint16_t DCACTL;          /**<  0x005C Digital Compare A Control Register*/
    uint16_t DCTRIPSEL;       /**<  0x005A Digital Compare Trip Select Register*/
    uint16_t DCFCTL;          /**<  0x0060 Digital Compare Filter Control Register*/
    uint16_t DCBCTL;          /**<  0x005E Digital Compare B Control Register*/
    uint16_t DCFOFFSET;       /**<  0x0064 Digital Compare Filter Offset Register*/
    uint16_t DCCAPCTL;        /**<  0x0062 Digital Compare Capture Control Register*/
    uint16_t DCFWINDOW;       /**<  0x0068 Digital Compare Filter Window Register*/
    uint16_t DCFOFFSETCNT;    /**<  0x0066 Digital Compare Filter Offset Counter Register*/
    uint16_t DCCAP;           /**<  0x006C Digital Compare Counter Capture Register*/
    uint16_t DCFWINDOWCNT;    /**<  0x006A Digital Compare Filter Window Counter Register*/

} etpwmBASE_t;

#endif



/** @def etpwmREG1
*   @brief ETPWM1 Register Frame Pointer
*
*   This pointer is used by the ETPWM driver to access the ETPWM1 registers.
*/
#define etpwmREG1 ((etpwmBASE_t *)0xFCF78C00U)

/** @def etpwmREG2
*   @brief ETPWM2 Register Frame Pointer
*
*   This pointer is used by the ETPWM driver to access the ETPWM2 registers.
*/
#define etpwmREG2 ((etpwmBASE_t *)0xFCF78D00U)

/** @def etpwmREG3
*   @brief ETPWM3 Register Frame Pointer
*
*   This pointer is used by the ETPWM driver to access the ETPWM3 registers.
*/
#define etpwmREG3 ((etpwmBASE_t *)0xFCF78E00U)

/** @def etpwmREG4
*   @brief ETPWM4 Register Frame Pointer
*
*   This pointer is used by the ETPWM driver to access the ETPWM4 registers.
*/
#define etpwmREG4 ((etpwmBASE_t *)0xFCF78F00U)

/** @def etpwmREG5
*   @brief ETPWM5 Register Frame Pointer
*
*   This pointer is used by the ETPWM driver to access the ETPWM5 registers.
*/
#define etpwmREG5 ((etpwmBASE_t *)0xFCF79000U)

/** @def etpwmREG6
*   @brief ETPWM6 Register Frame Pointer
*
*   This pointer is used by the ETPWM driver to access the ETPWM6 registers.
*/
#define etpwmREG6 ((etpwmBASE_t *)0xFCF79100U)

/** @def etpwmREG7
*   @brief ETPWM7 Register Frame Pointer
*
*   This pointer is used by the ETPWM driver to access the ETPWM7 registers.
*/
#define etpwmREG7 ((etpwmBASE_t *)0xFCF79200U)



// **************************************************************************
// the globals


// **************************************************************************
// the function prototypes

//! \brief     Initializes the ETPWM module
void ETPWM_init(void);

//! \brief     Clears the pulse width modulation (ETPWM) interrupt flag
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
inline void ETPWM_clearIntFlag(etpwmBASE_t *etpwm)
{
  


  // set the bits
  etpwm->ETCLR = ETPWM_ETCLR_INT_BITS;

  return;
} // end of ETPWM_clearIntFlag() function


//! \brief     Clears the pulse width modulation (ETPWM) one shot trip
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
inline void ETPWM_clearOneShotTrip(etpwmBASE_t *etpwm)
{
  




  // set the bits
  etpwm->TZCLR = ETPWM_TZCLR_OST_BITS;



  return;
} // end of ETPWM_clearOneShotTrip() function


//! \brief     Clears the pulse width modulation (ETPWM) start of conversion (SOC) A flag
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
inline void ETPWM_clearSocAFlag(etpwmBASE_t *etpwm)
{
  


  // set the bits
  etpwm->ETCLR = ETPWM_ETCLR_SOCA_BITS;

  return;
} // end of ETPWM_clearSocAFlag() function


//! \brief     Clears the pulse width modulation (ETPWM) start of conversion (SOC) B flag
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
inline void ETPWM_clearSocBFlag(etpwmBASE_t *etpwm)
{
  


  // set the bits
  etpwm->ETCLR = ETPWM_ETCLR_SOCB_BITS;

  return;
} // end of ETPWM_clearSocBFlag() function


//! \brief     Disables the pulse width modulation (ETPWM) chopping
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
void ETPWM_disableChopping(etpwmBASE_t *etpwm);


//! \brief     Disables the pulse width modulation (ETPWM) counter loading from the phase register
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
void ETPWM_disableCounterLoad(etpwmBASE_t *etpwm);


//! \brief     Disables the pulse width modulation (ETPWM) deadband
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
void ETPWM_disableDeadBand(etpwmBASE_t *etpwm);


//! \brief     Disables the pulse width modulation (ETPWM) deadband half cycle clocking
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
void ETPWM_disableDeadBandHalfCycle(etpwmBASE_t *etpwm);


//! \brief     Disables the pulse width modulation (ETPWM) interrupt
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
void ETPWM_disableInt(etpwmBASE_t *etpwm);


//! \brief     Disables the pulse width modulation (ETPWM) start of conversion (SOC) B pulse generation
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
void ETPWM_disableSocAPulse(etpwmBASE_t *etpwm);


//! \brief     Disables the pulse width modulation (ETPWM) start of conversion (SOC) B pulse generation
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
void ETPWM_disableSocBPulse(etpwmBASE_t *etpwm);


//! \brief     Disables the pulse width modulation (ETPWM) trip zones
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
void ETPWM_disableTripZones(etpwmBASE_t *etpwm);


//! \brief     Disable the pulse width modulation (ETPWM) trip zone source
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] src        The pulse width modulation (ETPWM) trip zone source
void ETPWM_disableTripZoneSrc(etpwmBASE_t *etpwm,const ETPWM_TripZoneSrc_e src);


//! \brief     Enables the pulse width modulation (ETPWM) chopping
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
void ETPWM_enableChopping(etpwmBASE_t *etpwm);


//! \brief     Enables the pulse width modulation (ETPWM) counter loading from the phase register
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
void ETPWM_enableCounterLoad(etpwmBASE_t *etpwm);


//! \brief     Enables the pulse width modulation (ETPWM) deadband half cycle clocking
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
void ETPWM_enableDeadBandHalfCycle(etpwmBASE_t *etpwm);


//! \brief     Enables the pulse width modulation (ETPWM) interrupt
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
void ETPWM_enableInt(etpwmBASE_t *etpwm);


//! \brief     Enables the pulse width modulation (ETPWM) start of conversion (SOC) A pulse generation
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
void ETPWM_enableSocAPulse(etpwmBASE_t *etpwm);


//! \brief     Enables the pulse width modulation (ETPWM) start of conversion (SOC) B pulse generation
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
void ETPWM_enableSocBPulse(etpwmBASE_t *etpwm);


//! \brief     Enable the pulse width modulation (ETPWM) trip zone source
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] src        The pulse width modulation (ETPWM) trip zone source
void ETPWM_enableTripZoneSrc(etpwmBASE_t *etpwm,const ETPWM_TripZoneSrc_e src);


//! \brief     Gets the pulse width modulation (ETPWM) interrupt event count
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \return    The interrupt event count
uint16_t ETPWM_getIntCount(etpwmBASE_t *etpwm);


//! \brief     Gets the pulse width modulation (ETPWM) start of conversion (SOC) A count
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \return    The SOC A count
uint16_t ETPWM_getSocACount(etpwmBASE_t *etpwm);


//! \brief     Gets the pulse width modulation (ETPWM) start of conversion (SOC) B count
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \return    The SOC B count
uint16_t ETPWM_getSocBCount(etpwmBASE_t *etpwm);



//! \brief     Sets the pulse width modulation (ETPWM) object action for ETPWM A when the counter equals CMPA and the counter is decrementing
//! \param[in] etpwm   The pulse width modulation (ETPWM) object handle
//! \param[in] actionQual  The action qualifier
void ETPWM_setActionQual_CntDown_CmpA_PwmA(etpwmBASE_t *etpwm,const ETPWM_ActionQual_e actionQual);


//! \brief     Sets the pulse width modulation (ETPWM) object action for ETPWM B when the counter equals CMPA and the counter is decrementing
//! \param[in] etpwm   The pulse width modulation (ETPWM) object handle
//! \param[in] actionQual  The action qualifier
void ETPWM_setActionQual_CntDown_CmpA_PwmB(etpwmBASE_t *etpwm,const ETPWM_ActionQual_e actionQual);


//! \brief     Sets the pulse width modulation (ETPWM) object action for ETPWM A when the counter equals CMPB and the counter is decrementing
//! \param[in] etpwm   The pulse width modulation (ETPWM) object handle
//! \param[in] actionQual  The action qualifier
void ETPWM_setActionQual_CntDown_CmpB_PwmA(etpwmBASE_t *etpwm,const ETPWM_ActionQual_e actionQual);


//! \brief     Sets the pulse width modulation (ETPWM) object action for ETPWM B when the counter equals CMPB and the counter is decrementing
//! \param[in] etpwm   The pulse width modulation (ETPWM) object handle
//! \param[in] actionQual  The action qualifier
void ETPWM_setActionQual_CntDown_CmpB_PwmB(etpwmBASE_t *etpwm,const ETPWM_ActionQual_e actionQual);


//! \brief     Sets the pulse width modulation (ETPWM) object action for ETPWM A when the counter equals CMPA and the counter is incrementing
//! \param[in] etpwm   The pulse width modulation (ETPWM) object handle
//! \param[in] actionQual  The action qualifier
void ETPWM_setActionQual_CntUp_CmpA_PwmA(etpwmBASE_t *etpwm,const ETPWM_ActionQual_e actionQual);


//! \brief     Sets the pulse width modulation (ETPWM) object action for ETPWM B when the counter equals CMPA and the counter is incrementing
//! \param[in] etpwm   The pulse width modulation (ETPWM) object handle
//! \param[in] actionQual  The action qualifier
void ETPWM_setActionQual_CntUp_CmpA_PwmB(etpwmBASE_t *etpwm,const ETPWM_ActionQual_e actionQual);


//! \brief     Sets the pulse width modulation (ETPWM) object action for ETPWM A when the counter equals CMPB and the counter is incrementing
//! \param[in] etpwm   The pulse width modulation (ETPWM) object handle
//! \param[in] actionQual  The action qualifier
void ETPWM_setActionQual_CntUp_CmpB_PwmA(etpwmBASE_t *etpwm,const ETPWM_ActionQual_e actionQual);


//! \brief     Sets the pulse width modulation (ETPWM) object action for ETPWM B when the counter equals CMPB and the counter is incrementing
//! \param[in] etpwm   The pulse width modulation (ETPWM) object handle
//! \param[in] actionQual  The action qualifier
void ETPWM_setActionQual_CntUp_CmpB_PwmB(etpwmBASE_t *etpwm,const ETPWM_ActionQual_e actionQual);


//! \brief     Sets the pulse width modulation (ETPWM) object action for ETPWM A when the counter equals the period
//! \param[in] etpwm   The pulse width modulation (ETPWM) object handle
//! \param[in] actionQual  The action qualifier
void ETPWM_setActionQual_Period_PwmA(etpwmBASE_t *etpwm,const ETPWM_ActionQual_e actionQual);


//! \brief     Sets the pulse width modulation (ETPWM) object action for ETPWM B when the counter equals the period
//! \param[in] etpwm   The pulse width modulation (ETPWM) object handle
//! \param[in] actionQual  The action qualifier
void ETPWM_setActionQual_Period_PwmB(etpwmBASE_t *etpwm,const ETPWM_ActionQual_e actionQual);


//! \brief     Sets the pulse width modulation (ETPWM) object action for ETPWM A when the counter equals the zero
//! \param[in] etpwm   The pulse width modulation (ETPWM) object handle
//! \param[in] actionQual  The action qualifier
void ETPWM_setActionQual_Zero_PwmA(etpwmBASE_t *etpwm,const ETPWM_ActionQual_e actionQual);


//! \brief     Sets the pulse width modulation (ETPWM) object action for ETPWM B when the counter equals the zero
//! \param[in] etpwm   The pulse width modulation (ETPWM) object handle
//! \param[in] actionQual  The action qualifier
void ETPWM_setActionQual_Zero_PwmB(etpwmBASE_t *etpwm,const ETPWM_ActionQual_e actionQual);


//! \brief     Sets the pulse width modulation (ETPWM) chopping clock frequency
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] clkFreq    The clock frequency
void ETPWM_setChoppingClkFreq(etpwmBASE_t *etpwm,const ETPWM_ChoppingClkFreq_e clkFreq);


//! \brief     Sets the pulse width modulation (ETPWM) chopping clock duty cycle
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] dutyCycle  The duty cycle
void ETPWM_setChoppingDutyCycle(etpwmBASE_t *etpwm,const ETPWM_ChoppingDutyCycle_e dutyCycle);


//! \brief     Sets the pulse width modulation (ETPWM) chopping clock pulse width
//! \param[in] etpwm   The pulse width modulation (ETPWM) object handle
//! \param[in] pulseWidth  The pulse width
void ETPWM_setChoppingPulseWidth(etpwmBASE_t *etpwm,const ETPWM_ChoppingPulseWidth_e pulseWidth);


//! \brief     Sets the pulse width modulation (ETPWM) clock divisor
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] clkDiv     The clock divisor
void ETPWM_setClkDiv(etpwmBASE_t *etpwm,const ETPWM_ClkDiv_e clkDiv);


//! \brief     Sets the pulse width modulation (ETPWM) count
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] count      The count
void ETPWM_setCount(etpwmBASE_t *etpwm,const uint16_t count);


//! \brief     Sets the pulse width modulation (ETPWM) counter mode
//! \param[in] etpwm    The pulse width modulation (ETPWM) object handle
//! \param[in] counterMode  The count mode
void ETPWM_setCounterMode(etpwmBASE_t *etpwm,const ETPWM_CounterMode_e counterMode);


//! \brief     Sets the pulse width modulation (ETPWM) deadband falling edge delay
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] delay      The delay
void ETPWM_setDeadBandFallingEdgeDelay(etpwmBASE_t *etpwm,const uint8_t delay);


//! \brief     Sets the pulse width modulation (ETPWM) deadband input mode
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] inputMode  The input mode
void ETPWM_setDeadBandInputMode(etpwmBASE_t *etpwm,const ETPWM_DeadBandInputMode_e inputMode);


//! \brief     Sets the pulse width modulation (ETPWM) deadband output mode
//! \param[in] etpwm   The pulse width modulation (ETPWM) object handle
//! \param[in] outputMode  The output mode
void ETPWM_setDeadBandOutputMode(etpwmBASE_t *etpwm,const ETPWM_DeadBandOutputMode_e outputMode);


//! \brief     Sets the pulse width modulation (ETPWM) deadband polarity
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] polarity   The polarity
void ETPWM_setDeadBandPolarity(etpwmBASE_t *etpwm,const ETPWM_DeadBandPolarity_e polarity);


//! \brief     Sets the pulse width modulation (ETPWM) deadband rising edge delay
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] delay      The delay
void ETPWM_setDeadBandRisingEdgeDelay(etpwmBASE_t *etpwm,const uint8_t delay);


//! \brief     Sets the pulse width modulation (ETPWM) period
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] period     The period
void ETPWM_setPeriod(etpwmBASE_t *etpwm,const uint16_t period);


//! \brief     Sets the pulse width modulation (ETPWM) high speed clock divisor
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] clkDiv     The clock divisor
void ETPWM_setHighSpeedClkDiv(etpwmBASE_t *etpwm,const ETPWM_HspClkDiv_e clkDiv);


//! \brief     Sets the pulse width modulation (ETPWM) interrupt mode
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] intMode    The interrupt mode
void ETPWM_setIntMode(etpwmBASE_t *etpwm,const ETPWM_IntMode_e intMode);


//! \brief     Sets the pulse width modulation (ETPWM) interrupt period
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] intPeriod  The interrupt period
void ETPWM_setIntPeriod(etpwmBASE_t *etpwm,const ETPWM_IntPeriod_e intPeriod);


//! \brief     Sets the pulse width modulation (ETPWM) load mode for CMPA
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] loadMode   The load mode
void ETPWM_setLoadMode_CmpA(etpwmBASE_t *etpwm,const ETPWM_LoadMode_e loadMode);


//! \brief     Sets the pulse width modulation (ETPWM) load mode for CMPB
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] loadMode   The load mode
void ETPWM_setLoadMode_CmpB(etpwmBASE_t *etpwm,const ETPWM_LoadMode_e loadMode);


//! \brief     Sets the pulse width modulation (ETPWM) period load mode
//! \param[in] etpwm   The pulse width modulation (ETPWM) object handle
//! \param[in] periodLoad  The period load mode
void ETPWM_setPeriodLoad(etpwmBASE_t *etpwm,const ETPWM_PeriodLoad_e periodLoad);


//! \brief     Sets the pulse width modulation (ETPWM) one shot trip
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
inline void ETPWM_setOneShotTrip(etpwmBASE_t *etpwm)
{
  




  // set the bits
  etpwm->TZFRC |= ETPWM_TZFRC_OST_BITS;



  return;
} // end of ETPWM_setOneShotTrip() function


//! \brief     Sets the pulse width modulation (ETPWM) phase
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] phase      The phase
void ETPWM_setPhase(etpwmBASE_t *etpwm,const uint16_t phase);


//! \brief     Sets the pulse width modulation (ETPWM) phase direction
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] phaseDir   The phase direction
void ETPWM_setPhaseDir(etpwmBASE_t *etpwm,const ETPWM_PhaseDir_e phaseDir);


//! \brief     Sets the pulse width modulation (ETPWM) run mode
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] runMode    The run mode
void ETPWM_setRunMode(etpwmBASE_t *etpwm,const ETPWM_RunMode_e runMode);


//! \brief     Sets the pulse width modulation (ETPWM) start of conversion (SOC) A interrupt period
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] intPeriod  The interrupt period
void ETPWM_setSocAPeriod(etpwmBASE_t *etpwm,const ETPWM_SocPeriod_e intPeriod);


//! \brief     Sets the pulse width modulation (ETPWM) start of conversion (SOC) A interrupt pulse source
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] pulseSrc   The interrupt pulse source
void ETPWM_setSocAPulseSrc(etpwmBASE_t *etpwm,const ETPWM_SocPulseSrc_e pulseSrc);


//! \brief     Sets the pulse width modulation (ETPWM) start of conversion (SOC) B interrupt period
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] intPeriod  The interrupt period
void ETPWM_setSocBPeriod(etpwmBASE_t *etpwm,const ETPWM_SocPeriod_e intPeriod);


//! \brief     Sets the pulse width modulation (ETPWM) start of conversion (SOC) B interrupt pulse source
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] pulseSrc   The interrupt pulse source
void ETPWM_setSocBPulseSrc(etpwmBASE_t *etpwm,const ETPWM_SocPulseSrc_e pulseSrc);


//! \brief     Sets the pulse width modulation (ETPWM) shadow mode for CMPA
//! \param[in] etpwm   The pulse width modulation (ETPWM) object handle
//! \param[in] shadowMode  The shadow mode
void ETPWM_setShadowMode_CmpA(etpwmBASE_t *etpwm,const ETPWM_ShadowMode_e shadowMode);


//! \brief     Sets the pulse width modulation (ETPWM) shadow mode for CMPB
//! \param[in] etpwm   The pulse width modulation (ETPWM) object handle
//! \param[in] shadowMode  The shadow mode
void ETPWM_setShadowMode_CmpB(etpwmBASE_t *etpwm,const ETPWM_ShadowMode_e shadowMode);


//! \brief     Sets the pulse width modulation (ETPWM) software sync
//! \param[in] etpwm   The pulse width modulation (ETPWM) object handle
void ETPWM_setSwSync(etpwmBASE_t *etpwm);


//! \brief     Sets the pulse width modulation (ETPWM) sync mode
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] syncMode   The sync mode
void ETPWM_setSyncMode(etpwmBASE_t *etpwm,const ETPWM_SyncMode_e syncMode);


//! \brief     Sets the pulse width modulation (ETPWM) trip zone state for Digital Compare Output A Event 1 (DCAEVT1)
//! \param[in] etpwm      The pulse width modulation (ETPWM) object handle
//! \param[in] tripZoneState  The trip zone state
void ETPWM_setTripZoneState_DCAEVT1(etpwmBASE_t *etpwm,const ETPWM_TripZoneState_e tripZoneState);


//! \brief     Sets the pulse width modulation (ETPWM) trip zone state for Digital Compare Output A Event 2 (DCAEVT1)
//! \param[in] etpwm      The pulse width modulation (ETPWM) object handle
//! \param[in] tripZoneState  The trip zone state
void ETPWM_setTripZoneState_DCAEVT2(etpwmBASE_t *etpwm,const ETPWM_TripZoneState_e tripZoneState);


//! \brief     Sets the pulse width modulation (ETPWM) trip zone state for Digital Compare Output B Event 1 (DCBEVT1)
//! \param[in] etpwm      The pulse width modulation (ETPWM) object handle
//! \param[in] tripZoneState  The trip zone state
void ETPWM_setTripZoneState_DCBEVT1(etpwmBASE_t *etpwm,const ETPWM_TripZoneState_e tripZoneState);


//! \brief     Sets the pulse width modulation (ETPWM) trip zone state for Digital Compare Output B Event 2 (DCBEVT1)
//! \param[in] etpwm      The pulse width modulation (ETPWM) object handle
//! \param[in] tripZoneState  The trip zone state
void ETPWM_setTripZoneState_DCBEVT2(etpwmBASE_t *etpwm,const ETPWM_TripZoneState_e tripZoneState);


//! \brief     Sets the pulse width modulation (ETPWM) trip zone state for Output A (TZA)
//! \param[in] etpwm      The pulse width modulation (ETPWM) object handle
//! \param[in] tripZoneState  The trip zone state
void ETPWM_setTripZoneState_TZA(etpwmBASE_t *etpwm,const ETPWM_TripZoneState_e tripZoneState);


//! \brief     Sets the pulse width modulation (ETPWM) trip zone state for Output B (TZB)
//! \param[in] etpwm      The pulse width modulation (ETPWM) object handle
//! \param[in] tripZoneState  The trip zone state
void ETPWM_setTripZoneState_TZB(etpwmBASE_t *etpwm,const ETPWM_TripZoneState_e tripZoneState);


//! \brief     Writes the pulse width modulation (ETPWM) data value to the Counter Compare A hardware
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] etpwmData    The ETPWM compare value for A
inline void ETPWM_write_CmpA(etpwmBASE_t *etpwm,const uint16_t etpwmData)
{
  
  etpwm->CMPA = etpwmData;

  return;
} // end of ETPWM_write_CmpA() function


//! \brief     Writes the pulse width modulation (ETPWM) data value to the Counter Compare B hardware
//! \param[in] etpwm  The pulse width modulation (ETPWM) object handle
//! \param[in] etpwmData    The ETPWM compare value for B
inline void ETPWM_write_CmpB(etpwmBASE_t *etpwm,const uint16_t etpwmData)
{
  
  etpwm->CMPB = etpwmData;

  return;
} // end of ETPWM_write_CmpB() function

//! \brief     Notification for ETPWMx Interrupts
//! \param[in] node  The pulse width modulation (ETPWM) object handle
//! \param[in] flags  Event and Interrupt flag.
void etpwmNotification(etpwmBASE_t *node,uint16_t flags);

//! \brief     Notification for ETPWM Trip zone Interrupts
//! \param[in] node  The pulse width modulation (ETPWM) object handle
//! \param[in] flags  Event and Interrupt flag.
void etpwmTripNotification(etpwmBASE_t *node,uint16_t flags);


#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup


#endif  // end of _ETPWM_H_ definition

