/*******************************************************************************
* File Name: Trigger_out.h  
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

#if !defined(CY_CONTROL_REG_Trigger_out_H) /* CY_CONTROL_REG_Trigger_out_H */
#define CY_CONTROL_REG_Trigger_out_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} Trigger_out_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    Trigger_out_Write(uint8 control) ;
uint8   Trigger_out_Read(void) ;

void Trigger_out_SaveConfig(void) ;
void Trigger_out_RestoreConfig(void) ;
void Trigger_out_Sleep(void) ; 
void Trigger_out_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define Trigger_out_Control        (* (reg8 *) Trigger_out_Sync_ctrl_reg__CONTROL_REG )
#define Trigger_out_Control_PTR    (  (reg8 *) Trigger_out_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_Trigger_out_H */


/* [] END OF FILE */