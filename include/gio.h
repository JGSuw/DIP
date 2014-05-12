/** @file gio.h
*   @brief GIO Driver Definition File
*   @date 15.Mar.2012
*   @version 03.01.00
*   
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

#include "sys_common.h"

#ifndef __GIO_H__
#define __GIO_H__

/** @struct gioBase
*   @brief GIO Base Register Definition
*
*   This structure is used to access the GIO module registers.
*/
/** @typedef gioBASE_t
*   @brief GIO Register Frame Type Definition
*
*   This type is used to access the GIO Registers.
*/
typedef volatile struct gioBase
{
    uint32_t GCR0;      /**< 0x0000: Global Control Register */
    uint32_t PWDN;      /**< 0x0004: Power Down Register */
    uint32_t INTDET;    /**< 0x0008: Interrupt Detect Register*/
    uint32_t POL;       /**< 0x000C: Interrupt Polarity Register */
    uint32_t INTENASET; /**< 0x0010: Interrupt Enable Set Register */
    uint32_t INTENACLR; /**< 0x0014: Interrupt Enable Clear Register */
    uint32_t LVLSET;    /**< 0x0018: Interrupt Priority Set Register */
    uint32_t LVLCLR;    /**< 0x001C: Interrupt Priority Clear Register */
    uint32_t FLG;       /**< 0x0020: Interrupt Flag Register */
    uint32_t OFFSET0;   /**< 0x0024: Interrupt Offset A Register */
    uint32_t OFFSET1;   /**< 0x0028: Interrupt Offset B Register */
} gioBASE_t;


/** @struct gioPort
*   @brief GIO Port Register Definition
*/
/** @typedef gioPORT_t
*   @brief GIO Port Register Type Definition
*
*   This type is used to access the GIO Port Registers.
*/
typedef volatile struct gioPort
{
    uint32_t DIR;    /**< 0x0000: Data Direction Register */
    uint32_t DIN;    /**< 0x0004: Data Input Register */
    uint32_t DOUT;   /**< 0x0008: Data Output Register */
    uint32_t DSET;   /**< 0x000C: Data Output Set Register */
    uint32_t DCLR;   /**< 0x0010: Data Output Clear Register */
    uint32_t PDR;    /**< 0x0014: Open Drain Register */
    uint32_t PULDIS; /**< 0x0018: Pullup Disable Register */
    uint32_t PSL;    /**< 0x001C: Pull Up/Down Selection Register */
} gioPORT_t;


/** @def gioREG
*   @brief GIO Register Frame Pointer
*
*   This pointer is used by the GIO driver to access the gio module registers.
*/
#define gioREG   ((gioBASE_t *)0xFFF7BC00U)

/** @def gioPORTA
*   @brief GIO Port (A) Register Pointer
*
*   Pointer used by the GIO driver to access PORTA
*/
#define gioPORTA ((gioPORT_t *)0xFFF7BC34U)

/** @def gioPORTB
*   @brief GIO Port (B) Register Pointer
*
*   Pointer used by the GIO driver to access PORTB
*/
#define gioPORTB ((gioPORT_t *)0xFFF7BC54U)


/* GIO Interface Functions */
void gioInit(void);
void gioSetDirection(gioPORT_t *port, uint32_t dir);
void gioSetBit(gioPORT_t *port, uint32_t bit, uint32_t value);
void gioSetPort(gioPORT_t *port, uint32_t value);
uint32_t gioGetBit(gioPORT_t *port, uint32_t bit);
uint32_t gioGetPort(gioPORT_t *port);
void gioToggleBit(gioPORT_t *port, uint32_t bit);
void gioEnableNotification(uint32_t bit);
void gioDisableNotification(uint32_t bit);
void gioNotification(uint32_t bit);

#endif
