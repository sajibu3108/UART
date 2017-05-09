/*******************************************************************************
* File Name: ResetTimer.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_ResetTimer_H) /* CY_CONTROL_REG_ResetTimer_H */
#define CY_CONTROL_REG_ResetTimer_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} ResetTimer_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    ResetTimer_Write(uint8 control) ;
uint8   ResetTimer_Read(void) ;

void ResetTimer_SaveConfig(void) ;
void ResetTimer_RestoreConfig(void) ;
void ResetTimer_Sleep(void) ; 
void ResetTimer_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define ResetTimer_Control        (* (reg8 *) ResetTimer_Sync_ctrl_reg__CONTROL_REG )
#define ResetTimer_Control_PTR    (  (reg8 *) ResetTimer_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_ResetTimer_H */


/* [] END OF FILE */
