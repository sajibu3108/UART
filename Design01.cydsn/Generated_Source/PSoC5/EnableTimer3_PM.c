/*******************************************************************************
* File Name: EnableTimer3_PM.c
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

#include "EnableTimer3.h"

/* Check for removal by optimization */
#if !defined(EnableTimer3_Sync_ctrl_reg__REMOVED)

static EnableTimer3_BACKUP_STRUCT  EnableTimer3_backup = {0u};

    
/*******************************************************************************
* Function Name: EnableTimer3_SaveConfig
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
void EnableTimer3_SaveConfig(void) 
{
    EnableTimer3_backup.controlState = EnableTimer3_Control;
}


/*******************************************************************************
* Function Name: EnableTimer3_RestoreConfig
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
void EnableTimer3_RestoreConfig(void) 
{
     EnableTimer3_Control = EnableTimer3_backup.controlState;
}


/*******************************************************************************
* Function Name: EnableTimer3_Sleep
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
void EnableTimer3_Sleep(void) 
{
    EnableTimer3_SaveConfig();
}


/*******************************************************************************
* Function Name: EnableTimer3_Wakeup
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
void EnableTimer3_Wakeup(void)  
{
    EnableTimer3_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
