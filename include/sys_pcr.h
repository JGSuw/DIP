/** @file sys_pcr.h
*   @brief PCR Driver Header File
*   @date 15.Aug.2012
*   @version 03.02.00
*   
*   This file contains:
*   - Definitions
*   - Types
*   .
*   which are relevant for the System driver.
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

#ifndef __SYS_PCR_H__
#define __SYS_PCR_H__

#include "sys_common.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* PCR General Definitions */

typedef uint8_t peripheralFrame_CS;

#define PeripheralFrame_CS0 0U
#define PeripheralFrame_CS1 1U
#define PeripheralFrame_CS2 2U
#define PeripheralFrame_CS3 3U
#define PeripheralFrame_CS4 4U
#define PeripheralFrame_CS5 5U
#define PeripheralFrame_CS6 6U
#define PeripheralFrame_CS7 7U
#define PeripheralFrame_CS8 8U
#define PeripheralFrame_CS9 9U
#define PeripheralFrame_CS10 10U
#define PeripheralFrame_CS11 11U
#define PeripheralFrame_CS12 12U
#define PeripheralFrame_CS13 13U
#define PeripheralFrame_CS14 14U
#define PeripheralFrame_CS15 15U
#define PeripheralFrame_CS16 16U
#define PeripheralFrame_CS17 17U
#define PeripheralFrame_CS18 18U
#define PeripheralFrame_CS19 19U
#define PeripheralFrame_CS20 20U
#define PeripheralFrame_CS21 21U
#define PeripheralFrame_CS22 22U
#define PeripheralFrame_CS23 23U
#define PeripheralFrame_CS24 24U
#define PeripheralFrame_CS25 25U
#define PeripheralFrame_CS26 26U
#define PeripheralFrame_CS27 27U
#define PeripheralFrame_CS28 28U
#define PeripheralFrame_CS29 29U
#define PeripheralFrame_CS30 30U
#define PeripheralFrame_CS31 31U

/* USER CODE BEGIN (1) */
/* USER CODE END */


typedef uint8_t quadrant_Select;
#define Quadrant0 1U
#define Quadrant1 2U
#define Quadrant2 4U
#define Quadrant3 8U

/* USER CODE BEGIN (2) */
/* USER CODE END */

/** @typedef peripheral_Frame_t
*   @brief PCR Peripheral Frame Type Definition
*
*   This type is used to access the PCR peripheral Frame configuration register.
*/
typedef struct
{
	peripheralFrame_CS Peripheral_CS;
	quadrant_Select Peripheral_Quadrant;
}peripheral_Frame_t;

/* USER CODE BEGIN (3) */
/* USER CODE END */

/** @typedef peripheral_Quad_ChipSelect_t
*   @brief PCR Peripheral Frame registers Type Definition
*
*   This type is used to access all the PCR peripheral Frame configuration registers.
*/
typedef struct
{
	uint32_t Peripheral_Quad0_3_CS0_7;
	uint32_t Peripheral_Quad4_7_CS8_15;
	uint32_t Peripheral_Quad8_11_CS16_23;
	uint32_t Peripheral_Quad12_15_CS24_31;
}peripheral_Quad_ChipSelect_t;

/* USER CODE BEGIN (4) */
/* USER CODE END */

/** @typedef peripheral_Memory_ChipSelect_t
*   @brief PCR Peripheral Memory Frame registers Type Definition
*
*   This type is used to access all the PCR peripheral Memory Frame configuration registers.
*/
typedef struct
{
	uint32_t Peripheral_Mem_CS0_31;
	uint32_t Peripheral_Mem_CS32_63;
}peripheral_Memory_ChipSelect_t;

/* USER CODE BEGIN (5) */
/* USER CODE END */

typedef uint8_t peripheral_MemoryFrame_CS;

#define PeripheralMemoryFrame_CS0 0U
#define PeripheralMemoryFrame_CS1 1U
#define PeripheralMemoryFrame_CS2 2U
#define PeripheralMemoryFrame_CS3 3U
#define PeripheralMemoryFrame_CS4 4U
#define PeripheralMemoryFrame_CS5 5U
#define PeripheralMemoryFrame_CS6 6U
#define PeripheralMemoryFrame_CS7 7U
#define PeripheralMemoryFrame_CS8 8U
#define PeripheralMemoryFrame_CS9 9U
#define PeripheralMemoryFrame_CS10 10U
#define PeripheralMemoryFrame_CS11 11U
#define PeripheralMemoryFrame_CS12 12U
#define PeripheralMemoryFrame_CS13 13U
#define PeripheralMemoryFrame_CS14 14U
#define PeripheralMemoryFrame_CS15 15U
#define PeripheralMemoryFrame_CS16 16U
#define PeripheralMemoryFrame_CS17 17U
#define PeripheralMemoryFrame_CS18 18U
#define PeripheralMemoryFrame_CS19 19U
#define PeripheralMemoryFrame_CS20 20U
#define PeripheralMemoryFrame_CS21 21U
#define PeripheralMemoryFrame_CS22 22U
#define PeripheralMemoryFrame_CS23 23U
#define PeripheralMemoryFrame_CS24 24U
#define PeripheralMemoryFrame_CS25 25U
#define PeripheralMemoryFrame_CS26 26U
#define PeripheralMemoryFrame_CS27 27U
#define PeripheralMemoryFrame_CS28 28U
#define PeripheralMemoryFrame_CS29 29U
#define PeripheralMemoryFrame_CS30 30U
#define PeripheralMemoryFrame_CS31 31U
#define PeripheralMemoryFrame_CS32 32U
#define PeripheralMemoryFrame_CS33 33U
#define PeripheralMemoryFrame_CS34 34U
#define PeripheralMemoryFrame_CS35 35U
#define PeripheralMemoryFrame_CS36 36U
#define PeripheralMemoryFrame_CS37 37U
#define PeripheralMemoryFrame_CS38 38U
#define PeripheralMemoryFrame_CS39 39U
#define PeripheralMemoryFrame_CS40 40U
#define PeripheralMemoryFrame_CS41 41U
#define PeripheralMemoryFrame_CS42 42U
#define PeripheralMemoryFrame_CS43 43U
#define PeripheralMemoryFrame_CS44 44U
#define PeripheralMemoryFrame_CS45 45U
#define PeripheralMemoryFrame_CS46 46U
#define PeripheralMemoryFrame_CS47 47U
#define PeripheralMemoryFrame_CS48 48U
#define PeripheralMemoryFrame_CS49 49U
#define PeripheralMemoryFrame_CS50 50U
#define PeripheralMemoryFrame_CS51 51U
#define PeripheralMemoryFrame_CS52 52U
#define PeripheralMemoryFrame_CS53 53U
#define PeripheralMemoryFrame_CS54 54U
#define PeripheralMemoryFrame_CS55 55U
#define PeripheralMemoryFrame_CS56 56U
#define PeripheralMemoryFrame_CS57 57U
#define PeripheralMemoryFrame_CS58 58U
#define PeripheralMemoryFrame_CS59 59U
#define PeripheralMemoryFrame_CS60 60U
#define PeripheralMemoryFrame_CS61 61U
#define PeripheralMemoryFrame_CS62 62U
#define PeripheralMemoryFrame_CS63 63U

/* USER CODE BEGIN (6) */
/* USER CODE END */

/** @struct pcrBase
*   @brief Pcr Register Frame Definition
*
*   This type is used to access the Pcr Registers.
*/
/** @typedef pcrBASE_t
*   @brief PCR Register Frame Type Definition
*
*   This type is used to access the PCR Registers.
*/
typedef volatile struct pcrBase
{
    uint32_t PMPROTSET0;    /* 0x0000 */
    uint32_t PMPROTSET1;    /* 0x0004 */
    uint32_t : 32U;         /* 0x0008 */
    uint32_t : 32U;         /* 0x000C */
    uint32_t PMPROTCLR0;    /* 0x0010 */
    uint32_t PMPROTCLR1;    /* 0x0014 */
    uint32_t : 32U;         /* 0x0018 */
    uint32_t : 32U;         /* 0x001C */
    uint32_t PPROTSET0;     /* 0x0020 */
    uint32_t PPROTSET1;     /* 0x0024 */
    uint32_t PPROTSET2;     /* 0x0028 */
    uint32_t PPROTSET3;     /* 0x002C */
    uint32_t : 32U;         /* 0x0030 */
    uint32_t : 32U;         /* 0x0034 */
    uint32_t : 32U;         /* 0x0038 */
    uint32_t : 32U;         /* 0x003C */
    uint32_t PPROTCLR0;     /* 0x0040 */
    uint32_t PPROTCLR1;     /* 0x0044 */
    uint32_t PPROTCLR2;     /* 0x0048 */
    uint32_t PPROTCLR3;     /* 0x004C */
    uint32_t : 32U;         /* 0x0050 */
    uint32_t : 32U;         /* 0x0054 */
    uint32_t : 32U;         /* 0x0058 */
    uint32_t : 32U;         /* 0x005C */
    uint32_t PCSPWRDWNSET0; /* 0x0060 */
    uint32_t PCSPWRDWNSET1; /* 0x0064 */
    uint32_t : 32U;         /* 0x0068 */
    uint32_t : 32U;         /* 0x006C */
    uint32_t PCSPWRDWNCLR0; /* 0x0070 */
    uint32_t PCSPWRDWNCLR1; /* 0x0074 */
    uint32_t : 32U;         /* 0x0078 */
    uint32_t : 32U;         /* 0x007C */
    uint32_t PSPWRDWNSET0;  /* 0x0080 */
    uint32_t PSPWRDWNSET1;  /* 0x0084 */
    uint32_t PSPWRDWNSET2;  /* 0x0088 */
    uint32_t PSPWRDWNSET3;  /* 0x008C */
    uint32_t : 32U;         /* 0x0090 */
    uint32_t : 32U;         /* 0x0094 */
    uint32_t : 32U;         /* 0x0098 */
    uint32_t : 32U;         /* 0x009C */
    uint32_t PSPWRDWNCLR0;  /* 0x00A0 */
    uint32_t PSPWRDWNCLR1;  /* 0x00A4 */
    uint32_t PSPWRDWNCLR2;  /* 0x00A8 */
    uint32_t PSPWRDWNCLR3;  /* 0x00AC */
} pcrBASE_t;

/** @def pcrREG
*   @brief Pcr Register Frame Pointer
*
*   This pointer is used by the system driver to access the Pcr registers.
*/
#define pcrREG ((pcrBASE_t *)0xFFFFE000U)

/* USER CODE BEGIN (7) */
/* USER CODE END */

/* PCR Interface Functions */

void peripheral_Frame_Protection_Set(peripheral_Frame_t peripheral_Frame);
void peripheral_Frame_Protection_Clr(peripheral_Frame_t peripheral_Frame);
void peripheral_Frame_Powerdown_Set(peripheral_Frame_t peripheral_Frame);
void peripheral_Frame_Powerdown_Clr(peripheral_Frame_t peripheral_Frame);

void peripheral_Protection_Set(peripheral_Quad_ChipSelect_t peripheral_Quad_CS);
void peripheral_Protection_Clr(peripheral_Quad_ChipSelect_t peripheral_Quad_CS);
peripheral_Quad_ChipSelect_t peripheral_Protection_Status();
void peripheral_Powerdown_Set(peripheral_Quad_ChipSelect_t peripheral_Quad_CS);
void peripheral_Powerdown_Clr(peripheral_Quad_ChipSelect_t peripheral_Quad_CS);
peripheral_Quad_ChipSelect_t peripheral_Powerdown_Status();

void peripheral_Memory_Protection_Set(peripheral_Memory_ChipSelect_t peripheral_Memory_CS);
void peripheral_Memory_Protection_Clr(peripheral_Memory_ChipSelect_t peripheral_Memory_CS);
peripheral_Memory_ChipSelect_t peripheral_Memory_Protection_Status();
void peripheral_Memory_Powerdown_Set(peripheral_Memory_ChipSelect_t peripheral_Memory_CS);
void peripheral_Memory_Powerdown_Clr(peripheral_Memory_ChipSelect_t peripheral_Memory_CS);
peripheral_Memory_ChipSelect_t Periipheral_Memory_Powerdown_Status();

void peripheral_Memory_Frame_Protection_Set(peripheral_MemoryFrame_CS peripheral_Memory_Frame_CS);
void peripheral_Memory_Frame_Protection_Clr(peripheral_MemoryFrame_CS peripheral_Memory_Frame_CS);
void peripheral_Memory_Frame_Powerdown_Set(peripheral_MemoryFrame_CS peripheral_Memory_Frame_CS);
void peripheral_Memory_Frame_Powerdown_Clr(peripheral_MemoryFrame_CS peripheral_Memory_Frame_CS);

/* USER CODE BEGIN (8) */
/* USER CODE END */

#endif
