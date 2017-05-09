/*******************************************************************************
* File Name: T1_PM.c
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

#include "T1.h"

static T1_backupStruct T1_backup;


/*******************************************************************************
* Function Name: T1_SaveConfig
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
*  T1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void T1_SaveConfig(void) 
{
    #if (!T1_UsingFixedFunction)
        T1_backup.TimerUdb = T1_ReadCounter();
        T1_backup.InterruptMaskValue = T1_STATUS_MASK;
        #if (T1_UsingHWCaptureCounter)
            T1_backup.TimerCaptureCounter = T1_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!T1_UDB_CONTROL_REG_REMOVED)
            T1_backup.TimerControlRegister = T1_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: T1_RestoreConfig
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
*  T1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void T1_RestoreConfig(void) 
{   
    #if (!T1_UsingFixedFunction)

        T1_WriteCounter(T1_backup.TimerUdb);
        T1_STATUS_MASK =T1_backup.InterruptMaskValue;
        #if (T1_UsingHWCaptureCounter)
            T1_SetCaptureCount(T1_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!T1_UDB_CONTROL_REG_REMOVED)
            T1_WriteControlRegister(T1_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: T1_Sleep
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
*  T1_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void T1_Sleep(void) 
{
    #if(!T1_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(T1_CTRL_ENABLE == (T1_CONTROL & T1_CTRL_ENABLE))
        {
            /* Timer is enabled */
            T1_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            T1_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    T1_Stop();
    T1_SaveConfig();
}


/*******************************************************************************
* Function Name: T1_Wakeup
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
*  T1_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void T1_Wakeup(void) 
{
    T1_RestoreConfig();
    #if(!T1_UDB_CONTROL_REG_REMOVED)
        if(T1_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                T1_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
