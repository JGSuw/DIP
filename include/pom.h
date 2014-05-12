/** @file pom.h
*   @brief POM Driver Definition File
*   @date 15.Mar.2012
*   @version 03.01.00
*   
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

#include "sys_common.h"

#ifndef __POM_H__
#define __POM_H__

/* USER CODE BEGIN (0) */
/* USER CODE END */


/** @enum pom_region_size
*   @brief Alias names for pom region size
*   This enumeration is used to provide alias names for POM region size:
*/
enum pom_region_size
{
        SIZE_32BYTES    = 0,
        SIZE_64BYTES    = 1,
        SIZE_128BYTES   = 2,
        SIZE_256BYTES   = 3,
        SIZE_512BYTES   = 4,
        SIZE_1KB        = 5,
        SIZE_2KB        = 6,
        SIZE_4KB        = 7,
        SIZE_8KB        = 8,
        SIZE_16KB       = 9,
        SIZE_32KB       = 10,
        SIZE_64KB       = 11,
        SIZE_128KB      = 12,
        SIZE_256KB      = 13
};

/** @def INTERNAL_RAM 
*   @brief Alias name for Internal RAM
*/   
#define INTERNAL_RAM    0x08000000U

/** @def SDRAM 
*   @brief Alias name for SD RAM
*/   
#define SDRAM   0x80000000U

/** @def ASYNC_MEMORY 
*   @brief Alias name for Async RAM
*/   
#define ASYNC_MEMORY   0x60000000


typedef uint32_t REGION;

/** @struct REGION_CONFIG_ST
*   @brief POM region configuration
*/
typedef struct
{       
        uint32_t Prog_Reg_Sta_Addr;
        uint32_t Ovly_Reg_Sta_Addr;
        uint32_t Reg_Size;
}REGION_CONFIG_ST;

/** @struct POMBase
*   @brief POM Register Frame Definition
*
*   This structure is used to access the POM module registers(POM Register Map).
*/
typedef struct
{
  uint32_t POMGLBCTRL_UL;   /* 0x00      */
  uint32_t POMREV_UL;       /* 0x04      */
  uint32_t POMCLKCTRL_UL;   /* 0x08      */
  uint32_t POMFLG_UL;       /* 0x0C      */
  struct
  {
    uint32_t Reserved_Reg_B32: 32;
  }RESERVED_REG[124];
  struct                    /* 0x200 ...    */
  {
    uint32_t POMPROGSTART_UL; 
    uint32_t POMOVLSTART_UL; 
    uint32_t POMREGSIZE_UL; 
    uint32_t : 32; 
  }POMRGNCONF_ST[32];
}pomBASE_t;


/** @struct POM_CORESIGHT_ST
*   @brief POM_CORESIGHT_ST Register Definition
*
*   This structure is used to access the POM module registers(POM CoreSight Registers ).
*/
typedef struct
{
    uint32_t POMITCTRL_UL;                  /* 0xF00            */
    struct                                  /* 0xF04 to 0xF9C   */                     
    {
        uint32_t Reserved_Reg_UL;
    }Reserved1_ST[39];
    uint32_t POMCLAIMSET_UL;                /* 0xFA0      */
    uint32_t POMCLAIMCLR_UL;                /* 0xFA4      */
    uint32_t : 32;                          /* 0xFA8      */
    uint32_t : 32;                          /* 0xFAC      */
    uint32_t POMLOCKACCESS_UL;              /* 0xFB0      */
    uint32_t POMLOCKSTATUS_UL;              /* 0xFB4      */
    uint32_t POMAUTHSTATUS_UL;              /* 0xFB8      */
    uint32_t : 32;                          /* 0xFBC      */
    uint32_t : 32;                          /* 0xFC0      */
    uint32_t : 32;                          /* 0xFC4      */
    uint32_t POMDEVID_UL;                   /* 0xFC8      */
    uint32_t POMDEVTYPE_UL;                 /* 0xFCC      */
    uint32_t POMPERIPHERALID4_UL;           /* 0xFD0      */
    uint32_t POMPERIPHERALID5_UL;           /* 0xFD4      */
    uint32_t POMPERIPHERALID6_UL;           /* 0xFD8      */
    uint32_t POMPERIPHERALID7_UL;           /* 0xFDC      */
    uint32_t POMPERIPHERALID0_UL;           /* 0xFE0      */
    uint32_t POMPERIPHERALID1_UL;           /* 0xFE4      */
    uint32_t POMPERIPHERALID2_UL;           /* 0xFE8      */
    uint32_t POMPERIPHERALID3_UL;           /* 0xFEC      */            
    uint32_t POMCOMPONENTID0_UL;            /* 0xFF0      */
    uint32_t POMCOMPONENTID1_UL;            /* 0xFF4      */
    uint32_t POMCOMPONENTID2_UL;            /* 0xFF8      */
    uint32_t POMCOMPONENTID3_UL;            /* 0xFFC      */
}POM_CORESIGHT_ST;


#define pomREG ((pomBASE_t *)0xFFA04000U)
/* USER CODE BEGIN (1) */
/* USER CODE END */

/* POM Interface Functions */
void POM_Init(void);
void POM_Disable(void);
void POM_Reset(void);

#endif /* __POM_H_*/
