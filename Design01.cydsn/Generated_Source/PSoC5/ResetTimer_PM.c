/*******************************************************************************
* File Name: ResetTimer_PM.c
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

#include "ResetTimer.h"

/* Check for removal by optimization */
#if !defined(ResetTimer_Sync_ctrl_reg__REMOVED)

static ResetTimer_BACKUP_STRUCT  ResetTimer_backup = {0u};

    
/*******************************************************************************
* Function Name: ResetTimer_SaveConfig
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
void ResetTimer_SaveConfig(void) 
{
    ResetTimer_backup.controlState = ResetTimer_Control;
}


/*******************************************************************************
* Function Name: ResetTimer_RestoreConfig
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
void ResetTimer_RestoreConfig(void) 
{
     ResetTimer_Control = ResetTimer_backup.controlState;
}


/*******************************************************************************
* Function Name: ResetTimer_Sleep
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
void ResetTimer_Sleep(void) 
{
    ResetTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: ResetTimer_Wakeup
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
void ResetTimer_Wakeup(void)  
{
    ResetTimer_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
