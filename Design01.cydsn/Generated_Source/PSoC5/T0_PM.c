/*******************************************************************************
* File Name: T0_PM.c
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

#include "T0.h"

static T0_backupStruct T0_backup;


/*******************************************************************************
* Function Name: T0_SaveConfig
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
*  T0_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void T0_SaveConfig(void) 
{
    #if (!T0_UsingFixedFunction)
        T0_backup.TimerUdb = T0_ReadCounter();
        T0_backup.InterruptMaskValue = T0_STATUS_MASK;
        #if (T0_UsingHWCaptureCounter)
            T0_backup.TimerCaptureCounter = T0_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!T0_UDB_CONTROL_REG_REMOVED)
            T0_backup.TimerControlRegister = T0_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: T0_RestoreConfig
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
*  T0_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void T0_RestoreConfig(void) 
{   
    #if (!T0_UsingFixedFunction)

        T0_WriteCounter(T0_backup.TimerUdb);
        T0_STATUS_MASK =T0_backup.InterruptMaskValue;
        #if (T0_UsingHWCaptureCounter)
            T0_SetCaptureCount(T0_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!T0_UDB_CONTROL_REG_REMOVED)
            T0_WriteControlRegister(T0_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: T0_Sleep
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
*  T0_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void T0_Sleep(void) 
{
    #if(!T0_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(T0_CTRL_ENABLE == (T0_CONTROL & T0_CTRL_ENABLE))
        {
            /* Timer is enabled */
            T0_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            T0_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    T0_Stop();
    T0_SaveConfig();
}


/*******************************************************************************
* Function Name: T0_Wakeup
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
*  T0_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void T0_Wakeup(void) 
{
    T0_RestoreConfig();
    #if(!T0_UDB_CONTROL_REG_REMOVED)
        if(T0_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                T0_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
