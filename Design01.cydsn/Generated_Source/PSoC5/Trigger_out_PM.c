/*******************************************************************************
* File Name: Trigger_out_PM.c
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

#include "Trigger_out.h"

/* Check for removal by optimization */
#if !defined(Trigger_out_Sync_ctrl_reg__REMOVED)

static Trigger_out_BACKUP_STRUCT  Trigger_out_backup = {0u};

    
/*******************************************************************************
* Function Name: Trigger_out_SaveConfig
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
void Trigger_out_SaveConfig(void) 
{
    Trigger_out_backup.controlState = Trigger_out_Control;
}


/*******************************************************************************
* Function Name: Trigger_out_RestoreConfig
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
void Trigger_out_RestoreConfig(void) 
{
     Trigger_out_Control = Trigger_out_backup.controlState;
}


/*******************************************************************************
* Function Name: Trigger_out_Sleep
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
void Trigger_out_Sleep(void) 
{
    Trigger_out_SaveConfig();
}


/*******************************************************************************
* Function Name: Trigger_out_Wakeup
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
void Trigger_out_Wakeup(void)  
{
    Trigger_out_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
