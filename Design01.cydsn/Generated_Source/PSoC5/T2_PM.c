/*******************************************************************************
* File Name: T2_PM.c
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

#include "T2.h"

static T2_backupStruct T2_backup;


/*******************************************************************************
* Function Name: T2_SaveConfig
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
*  T2_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void T2_SaveConfig(void) 
{
    #if (!T2_UsingFixedFunction)
        T2_backup.TimerUdb = T2_ReadCounter();
        T2_backup.InterruptMaskValue = T2_STATUS_MASK;
        #if (T2_UsingHWCaptureCounter)
            T2_backup.TimerCaptureCounter = T2_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!T2_UDB_CONTROL_REG_REMOVED)
            T2_backup.TimerControlRegister = T2_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: T2_RestoreConfig
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
*  T2_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void T2_RestoreConfig(void) 
{   
    #if (!T2_UsingFixedFunction)

        T2_WriteCounter(T2_backup.TimerUdb);
        T2_STATUS_MASK =T2_backup.InterruptMaskValue;
        #if (T2_UsingHWCaptureCounter)
            T2_SetCaptureCount(T2_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!T2_UDB_CONTROL_REG_REMOVED)
            T2_WriteControlRegister(T2_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: T2_Sleep
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
*  T2_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void T2_Sleep(void) 
{
    #if(!T2_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(T2_CTRL_ENABLE == (T2_CONTROL & T2_CTRL_ENABLE))
        {
            /* Timer is enabled */
            T2_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            T2_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    T2_Stop();
    T2_SaveConfig();
}


/*******************************************************************************
* Function Name: T2_Wakeup
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
*  T2_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void T2_Wakeup(void) 
{
    T2_RestoreConfig();
    #if(!T2_UDB_CONTROL_REG_REMOVED)
        if(T2_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                T2_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
