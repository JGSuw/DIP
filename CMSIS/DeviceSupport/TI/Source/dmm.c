/** @file dmm.c 
*   @brief DMM Driver Implementation File
*   @date 15.December.2011
*   @version 03.00.00
*
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */

#include "dmm.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @fn void dmmInit(void)
*   @brief Initializes the DMM Driver
*
*   This function initializes the DMM module.
*/
void dmmInit(void)
{

/* USER CODE BEGIN (2) */
/* USER CODE END */

    /** @b intalise @b DMM */

    /** @b initalise @b DMM @b Port */
    dmmREG->PC3 =  0           /* DATA[0] */
                | (0 << 1)     /* DATA[1] */
                | (0 << 2)     /* DATA[2] */
                | (0 << 3)     /* DATA[3] */
                | (0 << 4)     /* DATA[4] */
                | (0 << 5)     /* DATA[5] */
                | (0 << 6)     /* DATA[6] */
                | (0 << 7)     /* DATA[7] */
                | (0 << 8)     /* DATA[8] */
                | (0 << 9)     /* DATA[9] */
                | (0 << 10)    /* DATA[10] */
                | (0 << 11)    /* DATA[11] */
                | (0 << 12)    /* DATA[12] */
                | (0 << 13)    /* DATA[13] */
                | (0 << 14)    /* DATA[14] */
                | (0 << 15)    /* DATA[15] */
                | (0 << 16)    /* DMM SYNC */
                | (0 << 17)    /* DMM CLK */
                | (0 << 18);   /* DMM ENA */

    /** - DMM Port direction */
    dmmREG->PC1 =  1           /* DATA[0] */
                | (1 << 1)     /* DATA[1] */
                | (1 << 2)     /* DATA[2] */
                | (1 << 3)     /* DATA[3] */
                | (0 << 4)     /* DATA[4] */
                | (1 << 5)     /* DATA[5] */
                | (1 << 6)     /* DATA[6] */
                | (0 << 7)     /* DATA[7] */
                | (0 << 8)     /* DATA[8] */
                | (1 << 9)     /* DATA[9] */
                | (1 << 10)    /* DATA[10] */
                | (0 << 11)    /* DATA[11] */
                | (0 << 12)    /* DATA[12] */
                | (1 << 13)    /* DATA[13] */
                | (1 << 14)    /* DATA[14] */
                | (0 << 15)    /* DATA[15] */
                | (0 << 16)    /* DMM SYNC */
                | (1 << 17)    /* DMM CLK */
                | (1 << 18);   /* DMM ENA */

    /** - DMM Port open drain enable */
    dmmREG->PC6 =  0           /* DATA[0] */
                | (0 << 1)     /* DATA[1] */
                | (0 << 2)     /* DATA[2] */
                | (0 << 3)     /* DATA[3] */
                | (0 << 4)     /* DATA[4] */
                | (0 << 5)     /* DATA[5] */
                | (0 << 6)     /* DATA[6] */
                | (0 << 7)     /* DATA[7] */
                | (0 << 8)     /* DATA[8] */
                | (0 << 9)     /* DATA[9] */
                | (0 << 10)    /* DATA[10] */
                | (0 << 11)    /* DATA[11] */
                | (0 << 12)    /* DATA[12] */
                | (0 << 13)    /* DATA[13] */
                | (0 << 14)    /* DATA[14] */
                | (0 << 15)    /* DATA[15] */
                | (0 << 16)    /* DMM SYNC */
                | (0 << 17)    /* DMM CLK */
                | (0 << 18);   /* DMM ENA */


    /** - DMM Port pullup / pulldown selection */
    dmmREG->PC8 =  1           /* DATA[0] */
                | (1 << 1)     /* DATA[1] */
                | (1 << 2)     /* DATA[2] */
                | (1 << 3)     /* DATA[3] */
                | (1 << 4)     /* DATA[4] */
                | (1 << 5)     /* DATA[5] */
                | (1 << 6)     /* DATA[6] */
                | (1 << 7)     /* DATA[7] */
                | (1 << 8)     /* DATA[8] */
                | (1 << 9)     /* DATA[9] */
                | (1 << 10)    /* DATA[10] */
                | (1 << 11)    /* DATA[11] */
                | (1 << 12)    /* DATA[12] */
                | (1 << 13)    /* DATA[13] */
                | (1 << 14)    /* DATA[14] */
                | (1 << 15)    /* DATA[15] */
                | (1 << 16)    /* DMM SYNC */
                | (1 << 17)    /* DMM CLK */
                | (1 << 18);   /* DMM ENA */


    /** - DMM Port pullup / pulldown enable*/
    dmmREG->PC7 =  0           /* DATA[0] */
                | (0 << 1)     /* DATA[1] */
                | (0 << 2)     /* DATA[2] */
                | (0 << 3)     /* DATA[3] */
                | (0 << 4)     /* DATA[4] */
                | (0 << 5)     /* DATA[5] */
                | (0 << 6)     /* DATA[6] */
                | (0 << 7)     /* DATA[7] */
                | (0 << 8)     /* DATA[8] */
                | (0 << 9)     /* DATA[9] */
                | (0 << 10)    /* DATA[10] */
                | (0 << 11)    /* DATA[11] */
                | (0 << 12)    /* DATA[12] */
                | (0 << 13)    /* DATA[13] */
                | (0 << 14)    /* DATA[14] */
                | (0 << 15)    /* DATA[15] */
                | (0 << 16)    /* DMM SYNC */
                | (0 << 17)    /* DMM CLK */
                | (0 << 18);   /* DMM ENA */

    /* DMM set all pins to functional */
    dmmREG->PC0 =  1           /* DATA[0] */
                | (1 << 1)     /* DATA[1] */
                | (1 << 2)     /* DATA[2] */
                | (1 << 3)     /* DATA[3] */
                | (1 << 4)     /* DATA[4] */
                | (1 << 5)     /* DATA[5] */
                | (1 << 6)     /* DATA[6] */
                | (1 << 7)     /* DATA[7] */
                | (1 << 8)     /* DATA[8] */
                | (1 << 9)     /* DATA[9] */
                | (1 << 10)    /* DATA[10] */
                | (1 << 11)    /* DATA[11] */
                | (1 << 12)    /* DATA[12] */
                | (1 << 13)    /* DATA[13] */
                | (1 << 14)    /* DATA[14] */
                | (1 << 15)    /* DATA[15] */
                | (1 << 16)    /* DMM SYNC */
                | (1 << 17)    /* DMM CLK */
                | (1 << 18);   /* DMM ENA */

/* USER CODE BEGIN (3) */
/* USER CODE END */

}
