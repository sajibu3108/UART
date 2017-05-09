/*******************************************************************************
* File Name: TimerInt_PM.c
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

#include "TimerInt.h"

static TimerInt_backupStruct TimerInt_backup;


/*******************************************************************************
* Function Name: TimerInt_SaveConfig
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
*  TimerInt_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TimerInt_SaveConfig(void) 
{
    #if (!TimerInt_UsingFixedFunction)
        TimerInt_backup.TimerUdb = TimerInt_ReadCounter();
        TimerInt_backup.InterruptMaskValue = TimerInt_STATUS_MASK;
        #if (TimerInt_UsingHWCaptureCounter)
            TimerInt_backup.TimerCaptureCounter = TimerInt_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!TimerInt_UDB_CONTROL_REG_REMOVED)
            TimerInt_backup.TimerControlRegister = TimerInt_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TimerInt_RestoreConfig
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
*  TimerInt_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TimerInt_RestoreConfig(void) 
{   
    #if (!TimerInt_UsingFixedFunction)

        TimerInt_WriteCounter(TimerInt_backup.TimerUdb);
        TimerInt_STATUS_MASK =TimerInt_backup.InterruptMaskValue;
        #if (TimerInt_UsingHWCaptureCounter)
            TimerInt_SetCaptureCount(TimerInt_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!TimerInt_UDB_CONTROL_REG_REMOVED)
            TimerInt_WriteControlRegister(TimerInt_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TimerInt_Sleep
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
*  TimerInt_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void TimerInt_Sleep(void) 
{
    #if(!TimerInt_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(TimerInt_CTRL_ENABLE == (TimerInt_CONTROL & TimerInt_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TimerInt_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TimerInt_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TimerInt_Stop();
    TimerInt_SaveConfig();
}


/*******************************************************************************
* Function Name: TimerInt_Wakeup
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
*  TimerInt_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TimerInt_Wakeup(void) 
{
    TimerInt_RestoreConfig();
    #if(!TimerInt_UDB_CONTROL_REG_REMOVED)
        if(TimerInt_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TimerInt_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
