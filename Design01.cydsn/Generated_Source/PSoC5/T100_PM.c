/*******************************************************************************
* File Name: T100_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "T100.h"

static T100_backupStruct T100_backup;


/*******************************************************************************
* Function Name: T100_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  T100_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void T100_SaveConfig(void) 
{
    #if (!T100_UsingFixedFunction)
        T100_backup.TimerUdb = T100_ReadCounter();
        T100_backup.InterruptMaskValue = T100_STATUS_MASK;
        #if (T100_UsingHWCaptureCounter)
            T100_backup.TimerCaptureCounter = T100_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!T100_UDB_CONTROL_REG_REMOVED)
            T100_backup.TimerControlRegister = T100_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: T100_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  T100_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void T100_RestoreConfig(void) 
{   
    #if (!T100_UsingFixedFunction)

        T100_WriteCounter(T100_backup.TimerUdb);
        T100_STATUS_MASK =T100_backup.InterruptMaskValue;
        #if (T100_UsingHWCaptureCounter)
            T100_SetCaptureCount(T100_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!T100_UDB_CONTROL_REG_REMOVED)
            T100_WriteControlRegister(T100_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: T100_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  T100_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void T100_Sleep(void) 
{
    #if(!T100_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(T100_CTRL_ENABLE == (T100_CONTROL & T100_CTRL_ENABLE))
        {
            /* Timer is enabled */
            T100_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            T100_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    T100_Stop();
    T100_SaveConfig();
}


/*******************************************************************************
* Function Name: T100_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  T100_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void T100_Wakeup(void) 
{
    T100_RestoreConfig();
    #if(!T100_UDB_CONTROL_REG_REMOVED)
        if(T100_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                T100_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
