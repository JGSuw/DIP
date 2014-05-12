/** @file htu.h
*   @brief HTU Driver Definition File
*   @date 15.Mar.2012
*   @version 03.01.00
*   
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */


#ifndef __HTU_H__
#define __HTU_H__

/* HTU General Definitions */

/** @struct htuBase
*   @brief HTU Base Register Definition
*
*   This structure is used to access the HTU module registers.
*/
/** @typedef stcBASE_t
*   @brief HTU Register Frame Type Definition
*
*   This type is used to access the HTU Registers.
*/
typedef volatile struct htuBase
{
    uint32_t GC;				// 0x00
    uint32_t CPENA;				// 0x04
    uint32_t BUSY0;				// 0x08
    uint32_t BUSY1;				// 0x0C
    uint32_t BUSY2;				// 0x10
    uint32_t BUSY3;				// 0x14
	uint32_t ACPE;				// 0x18
    uint32_t : 32;				// 0x1C
    uint32_t RLBECTRL;			// 0x20
    uint32_t BFINTS;			// 0x24
    uint32_t BFINTC;			// 0x28
    uint32_t INTMAP;			// 0x2C
    uint32_t : 32;				// 0x30
    uint32_t INTOFF0;			// 0x34
    uint32_t INTOFF1;			// 0x38
    uint32_t BIM;				// 0x3C
    uint32_t RLOSTFL;			// 0x40
    uint32_t BFINTFL;			// 0x44
    uint32_t BERINTFL;			// 0x48
    uint32_t MP1S;				// 0x4C
    uint32_t MP1E;				// 0x50
    uint32_t DCTRL;				// 0x54
    uint32_t WPR;				// 0x58
    uint32_t WMR;				// 0x5C
    uint32_t ID;				// 0x60
    uint32_t PCR;				// 0x64
    uint32_t PAR;				// 0x68
    uint32_t : 32;				// 0x6C
    uint32_t MPCS;				// 0x70
    uint32_t MP0S;				// 0x74
    uint32_t MP0E;				// 0x78
} htuBASE_t;

typedef volatile struct htudcp
{
    uint32_t IFADDRA;			// 0x00
    uint32_t IFADDRB;			// 0x04
    uint32_t IHADDRCT;			// 0x08
    uint32_t ITCOUNT;			// 0x0C
} htudcp_t;

typedef volatile struct htucdcp
{
    uint32_t CFADDRA;			// 0x100
    uint32_t CFADDRB;			// 0x104
    uint32_t CFCOUNT;			// 0x108
} htucdcp_t;

#define htuREG1   ((htuBASE_t *)0xFFF7A400U)
#define htuREG2   ((htuBASE_t *)0xFFF7A500U)

#define htuDCP1   ((htudcp_t *)0xFF4E0000U)
#define htuDCP2   ((htudcp_t *)0xFF4C0000U)

#define htuCDCP1   ((htucdcp_t *)0xFF4E0100U)
#define htuCDCP2   ((htucdcp_t *)0xFF4C0100U)

#define HTU1PARLOC		(*(volatile uint32_t *)0xFF4E0200U)
#define HTU2PARLOC		(*(volatile uint32_t *)0xFF4C0200U)

#define HTU1RAMLOC		(*(volatile uint32_t *)0xFF4E0000U)
#define HTU2RAMLOC		(*(volatile uint32_t *)0xFF4C0000U)

#endif
