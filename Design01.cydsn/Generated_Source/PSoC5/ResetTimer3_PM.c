/*******************************************************************************
* File Name: ResetTimer3_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "ResetTimer3.h"

/* Check for removal by optimization */
#if !defined(ResetTimer3_Sync_ctrl_reg__REMOVED)

static ResetTimer3_BACKUP_STRUCT  ResetTimer3_backup = {0u};

    
/*******************************************************************************
* Function Name: ResetTimer3_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResetTimer3_SaveConfig(void) 
{
    ResetTimer3_backup.controlState = ResetTimer3_Control;
}


/*******************************************************************************
* Function Name: ResetTimer3_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void ResetTimer3_RestoreConfig(void) 
{
     ResetTimer3_Control = ResetTimer3_backup.controlState;
}


/*******************************************************************************
* Function Name: ResetTimer3_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResetTimer3_Sleep(void) 
{
    ResetTimer3_SaveConfig();
}


/*******************************************************************************
* Function Name: ResetTimer3_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResetTimer3_Wakeup(void)  
{
    ResetTimer3_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
