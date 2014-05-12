/** @file reg_ecap.h
*   @brief ECAP Register Layer Header File
*   @date 25.April.2014
*   @version 03.09.00
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the ECAP driver.
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */

#ifndef __REG_ECAP_H__
#define __REG_ECAP_H__

#include "sys_common.h"



/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Ecap Register Frame Definition */
/** @struct ecapBASE
*   @brief ECAP Register Frame Definition
*
*   This type is used to access the ECAP Registers.
*/
/** @typedef ecapBASE_t
*   @brief ECAP Register Frame Type Definition
*
*   This type is used to access the ECAP Registers.
*/
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1)) 

typedef volatile struct ecapBASE
 {
   uint32 TSCTR;     /**<  0x0000 Time stamp counter Register*/
   uint32 CTRPHS;    /**<  0x0004 Counter phase Register*/ 
   uint32 CAP1;      /**<  0x0008 Capture 1 Register*/
   uint32 CAP2;      /**<  0x000C Capture 2 Register*/
   uint32 CAP3;      /**<  0x0010 Capture 3 Register*/
   uint32 CAP4;      /**<  0x0014 Capture 4 Register*/
   uint16 rsvd1[8U]; /**<  0x0018 Reserved*/
   uint16 ECCTL1;    /**<  0x0028 Capture Control Reg 1 Register*/
   uint16 ECCTL2;    /**<  0x002A Capture Control Reg 2 Register*/
   uint16 ECEINT;    /**<  0x002C Interrupt enable Register*/
   uint16 ECFLG;     /**<  0x002E Interrupt flags Register*/ 
   uint16 ECCLR;     /**<  0x0030 Interrupt clear Register*/
   uint16 ECFRC;     /**<  0x0032 Interrupt force Register*/
   uint16 rsvd2[6U]; /**<  0x0034 Reserved*/

}ecapBASE_t;

#else

typedef volatile struct ecapBASE
 {
   uint32 TSCTR;     /**<  0x0000 Time stamp counter Register*/
   uint32 CTRPHS;    /**<  0x0004 Counter phase Register*/ 
   uint32 CAP1;      /**<  0x0008 Capture 1 Register*/
   uint32 CAP2;      /**<  0x000C Capture 2 Register*/
   uint32 CAP3;      /**<  0x0010 Capture 3 Register*/
   uint32 CAP4;      /**<  0x0014 Capture 4 Register*/
   uint16 rsvd1[8U]; /**<  0x0018 Reserved*/
   uint16 ECCTL2;    /**<  0x002A Capture Control Reg 2 Register*/
   uint16 ECCTL1;    /**<  0x0028 Capture Control Reg 1 Register*/
   uint16 ECFLG;     /**<  0x002E Interrupt flags Register*/ 
   uint16 ECEINT;    /**<  0x002C Interrupt enable Register*/
   uint16 ECFRC;     /**<  0x0032 Interrupt force Register*/
   uint16 ECCLR;     /**<  0x0030 Interrupt clear Register*/
   uint16 rsvd2[6U]; /**<  0x0034 Reserved*/

}ecapBASE_t;

#endif
/** @def ecapREG1
*   @brief ECAP1 Register Frame Pointer
*
*   This pointer is used by the ECAP driver to access the ECAP1 registers.
*/
#define ecapREG1 ((ecapBASE_t *)0xFCF79300U)

/** @def ecapREG2
*   @brief ECAP2 Register Frame Pointer
*
*   This pointer is used by the ECAP driver to access the ECAP2 registers.
*/
#define ecapREG2 ((ecapBASE_t *)0xFCF79400U)

/** @def ecapREG3
*   @brief ECAP3 Register Frame Pointer
*
*   This pointer is used by the ECAP driver to access the ECAP3 registers.
*/
#define ecapREG3 ((ecapBASE_t *)0xFCF79500U)

/** @def ecapREG4
*   @brief ECAP4 Register Frame Pointer
*
*   This pointer is used by the ECAP driver to access the ECAP4 registers.
*/
#define ecapREG4 ((ecapBASE_t *)0xFCF79600U)

/** @def ecapREG5
*   @brief ECAP5 Register Frame Pointer
*
*   This pointer is used by the ECAP driver to access the ECAP5 registers.
*/
#define ecapREG5 ((ecapBASE_t *)0xFCF79700U)

/** @def ecapREG6
*   @brief ECAP6 Register Frame Pointer
*
*   This pointer is used by the ECAP driver to access the ECAP6 registers.
*/
#define ecapREG6 ((ecapBASE_t *)0xFCF79800U)

/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
