/** @file emif.h
*   @brief emif Driver Definition File
*   @date 15.Feb.2012
*   @version 03.01.00
*   
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

#ifndef _EMIF_H_
#define _EMIF_H_

#include "sys_common.h"

/** @enum emif_pins
*   @brief Alias for emif pins
*
*/
enum emif_pins
{
    emif_wait_pin0 = 0,
    emif_wait_pin1 = 1
};


/** @enum emif_size
*   @brief Alias for emif page size
*
*/
enum emif_size
{
    elements_256 = 0,
    elements_512 = 1,
    elements_1024 = 2,
    elements_2048 = 3
};

/** @enum emif_port
*   @brief Alias for emif port
*
*/
enum emif_port
{
    emif_8_bit_port = 0,
    emif_16_bit_port = 1
};


/** @enum emif_pagesize
*   @brief Alias for emif pagesize
*
*/
enum emif_pagesize
{
    emif_4_words = 0,
    emif_8_words = 1
};

/** @enum emif_wait_polarity
*   @brief Alias for emif wait polarity
*
*/
enum emif_wait_polarity
{
    emif_pin_low = 0,
    emif_pin_high = 1
};


#define PTR (uint32_t *)(0x80000000)

/** @struct emifBASE_t
*   @brief emifBASE Register Definition
*
*   This structure is used to access the EMIF module registers.
*/
typedef volatile struct emifBase
{
    uint32_t MIDR;          /**< 0x0000 Module ID Register */
    uint32_t AWCC;          /**< 0x0004 Asynchronous wait cycle register*/
    uint32_t SDCR;          /**< 0x0008 SDRAM configuration register */
    uint32_t SDRCR ;        /**< 0x000C Set Interrupt Enable Register */
    uint32_t CE2CFG;        /**< 0x0010 Asynchronous 1 Configuration Register */
    uint32_t CE3CFG;        /**< 0x0014 Asynchronous 2 Configuration Register */
    uint32_t CE4CFG;        /**< 0x0018 Asynchronous 3 Configuration Register */
    uint32_t CE5CFG;        /**< 0x001C Asynchronous 4 Configuration Register */
    uint32_t SDTIMR;        /**< 0x0020 SDRAM Timing Register */
    uint32_t dummy1[6];     /** reserved **/
    uint32_t SDSRETR;       /**< 0x003c SDRAM Self Refresh Exit Timing Register */
    uint32_t INTRAW;        /**< 0x0040 0x0020 Interrupt Vector Offset*/
    uint32_t INTMSK;        /**< 0x0044 EMIF Interrupt Mask Register */
    uint32_t INTMSKSET;     /**< 48 EMIF Interrupt Mask Set Register */
    uint32_t INTMSKCLR;     /**< 0x004c EMIF Interrupt Mask Register */
    uint32_t dummy2[6];     /** reserved **/
    uint32_t PMCR;          /**< 0x0068 Page Mode Control Register*/

} emifBASE_t;

#define emifREG ((emifBASE_t *)0xFCFFE800U)

/* EMIF Interface Functions */

void emif_SDRAMInit(void);
void emif_ASYNC1Init(void);
void emif_ASYNC2Init(void);
void emif_ASYNC3Init(void);


#endif /*EMIF_H_*/
