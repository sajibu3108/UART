/*******************************************************************************
* File Name: TimeDistMeas_PM.c
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

#include "TimeDistMeas.h"

static TimeDistMeas_backupStruct TimeDistMeas_backup;


/*******************************************************************************
* Function Name: TimeDistMeas_SaveConfig
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
*  TimeDistMeas_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TimeDistMeas_SaveConfig(void) 
{
    #if (!TimeDistMeas_UsingFixedFunction)
        TimeDistMeas_backup.TimerUdb = TimeDistMeas_ReadCounter();
        TimeDistMeas_backup.InterruptMaskValue = TimeDistMeas_STATUS_MASK;
        #if (TimeDistMeas_UsingHWCaptureCounter)
            TimeDistMeas_backup.TimerCaptureCounter = TimeDistMeas_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!TimeDistMeas_UDB_CONTROL_REG_REMOVED)
            TimeDistMeas_backup.TimerControlRegister = TimeDistMeas_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TimeDistMeas_RestoreConfig
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
*  TimeDistMeas_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TimeDistMeas_RestoreConfig(void) 
{   
    #if (!TimeDistMeas_UsingFixedFunction)

        TimeDistMeas_WriteCounter(TimeDistMeas_backup.TimerUdb);
        TimeDistMeas_STATUS_MASK =TimeDistMeas_backup.InterruptMaskValue;
        #if (TimeDistMeas_UsingHWCaptureCounter)
            TimeDistMeas_SetCaptureCount(TimeDistMeas_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!TimeDistMeas_UDB_CONTROL_REG_REMOVED)
            TimeDistMeas_WriteControlRegister(TimeDistMeas_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TimeDistMeas_Sleep
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
*  TimeDistMeas_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void TimeDistMeas_Sleep(void) 
{
    #if(!TimeDistMeas_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(TimeDistMeas_CTRL_ENABLE == (TimeDistMeas_CONTROL & TimeDistMeas_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TimeDistMeas_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TimeDistMeas_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TimeDistMeas_Stop();
    TimeDistMeas_SaveConfig();
}


/*******************************************************************************
* Function Name: TimeDistMeas_Wakeup
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
*  TimeDistMeas_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TimeDistMeas_Wakeup(void) 
{
    TimeDistMeas_RestoreConfig();
    #if(!TimeDistMeas_UDB_CONTROL_REG_REMOVED)
        if(TimeDistMeas_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TimeDistMeas_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
