/** @file system.c 
*   @brief System Driver Source File
*   @date 21.July.2009
*   @version 1.00.000
*
*   This file contains:
*   - API Funcions
*   .
*   which are relevant for the System driver.
*/

/* (c) Texas Instruments 2009, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */


/* Include Files */

#include <TMS570.h>

/* USER CODE BEGIN (1) */
/* USER CODE END */


/** @fn void systemInit(void)
*   @brief Initializes System Driver
*
*   This function initializes the System driver.
*
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void systemInit(void)
{
/* USER CODE BEGIN (3) */
/* USER CODE END */

    /** @b Initialize @b Flash @b Wrapper: */

    /** - Setup flash read mode, address wait states and data wait states */
    FLASHW->FRDCNTL =  0x01000000U 
                    | (3U << 8U) 
                    | (1U << 4U) 
                    |  1U;

    /** - Setup flash bank power modes */
    FLASHW->FBFALLBACK = (SYS_SLEEP << 14U) 
                       | (SYS_SLEEP << 12U) 
                       | (SYS_SLEEP << 10U) 
                       | (SYS_SLEEP << 8U) 
                       | (SYS_ACTIVE << 6U) 
                       | (SYS_ACTIVE << 4U) 
                       | (SYS_ACTIVE << 2U) 
                       |  SYS_ACTIVE;

    /** @b Initialize @b Pll: */

    /** - Setup pll control register 1:
    *     - Setup reset on oscillator slip 
    *     - Setup bypass on pll slip
    *     - Setup Pll output clock divider
    *     - Setup reset on oscillator fail
    *     - Setup reference clock divider 
    *     - Setup Pll multiplier          
    */
    SYSTEM_1->PLLCTL1 =  0x00000000U 
                      |  0x20000000U 
                      | (0U << 24U) 
                      |  0x00000000U 
                      | (5U << 16U) 
                      | (119U  << 8U);

    /** - Setup pll control register 1 
    *     - Enable/Disable frequency modulation
    *     - Setup spreading rate
    *     - Setup bandwidth adjustment
    *     - Setup internal Pll output divider
    *     - Setup spreading amount
    */
    SYSTEM_1->PLLCTL2 = 0x00000000U
                      | (255U << 22U)
                      | (0U << 12U)
                      | (1U << 9U)
                      |  61U;


    /** @b Initialize @b Clock @b Tree: */

    /** - Start clock source lock */
    SYSTEM_1->CSDIS = 0x00000000U 
                    | 0x00000000U 
                    | 0x00000000U 
                    | 0x00000008U 
                    | 0x00000004U 
                    | 0x00000000U 
                    | 0x00000000U;

    /** - Wait for until clocks are locked */
    while ((SYSTEM_1->CSVSTAT & ((SYSTEM_1->CSDIS ^ 0xFF) & 0xFF)) != ((SYSTEM_1->CSDIS ^ 0xFF) & 0xFF));

    /** - Setup GCLK, HCLK and VCLK clock source for normal operation, power down mode and after wakeup */
    SYSTEM_1->GHVSRC = (SYS_OSC << 24U) 
                     | (SYS_PLL << 16U) 
                     |  SYS_PLL;

    /** - Power-up all peripharals */
    pPCR->PSPWRDWNCLR0 = 0xFFFFFFFFU;
    pPCR->PSPWRDWNCLR1 = 0xFFFFFFFFU;
    pPCR->PSPWRDWNCLR2 = 0xFFFFFFFFU;
    pPCR->PSPWRDWNCLR3 = 0xFFFFFFFFU;

    /** - Setup synchronous peripheral clock dividers for VCLK1 and VCLK2 */
    SYSTEM_1->VCLKR  = 15U;
    SYSTEM_1->VCLK2R = 1U;
    SYSTEM_1->VCLKR  = 1U;

    /** - Setup RTICLK1 and RTICLK2 clocks */
    SYSTEM_1->RCLKSRC = (1U << 24U)
                      | (SYS_VCLK << 16U) 
                      | (1U << 8U)  
                      |  SYS_VCLK;

    /** - Setup asynchronous peripheral clock sources for AVCLK1 and AVCLK2 */
    SYSTEM_1->VCLKASRC = (SYS_VCLK << 8U)
                       |  SYS_VCLK;

    /** - Enable Peripherals */
    SYSTEM_1->PENA = 1U;

    /** @note: HCLK >= VCLK2 >= VCLK_sys */

/* USER CODE BEGIN (4) */
/* USER CODE END */
}

#if 0
void systemPowerDown(unsigned mode)
{
    unsigned source = SYSTEM_1->CSDIS;

    /* Disable clock sources */
    SYSTEM_1->CSDISSET = mode & 0x000000FFU;

    /* Disable clock domains */
    SYSTEM_1->CSDDIS = (mode >> 8U) & 0x000000FFU;

    /* Idle CPU */
    asm(" wfi");
    asm(" isb");

    SYSTEM_1->CSDIS = source;
}
#endif

/* USER CODE BEGIN (5) */
/* USER CODE END */
