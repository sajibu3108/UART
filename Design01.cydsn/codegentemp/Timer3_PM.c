/*******************************************************************************
* File Name: Timer3_PM.c
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

#include "Timer3.h"

static Timer3_backupStruct Timer3_backup;


/*******************************************************************************
* Function Name: Timer3_SaveConfig
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
*  Timer3_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer3_SaveConfig(void) 
{
    #if (!Timer3_UsingFixedFunction)
        Timer3_backup.TimerUdb = Timer3_ReadCounter();
        Timer3_backup.InterruptMaskValue = Timer3_STATUS_MASK;
        #if (Timer3_UsingHWCaptureCounter)
            Timer3_backup.TimerCaptureCounter = Timer3_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer3_UDB_CONTROL_REG_REMOVED)
            Timer3_backup.TimerControlRegister = Timer3_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer3_RestoreConfig
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
*  Timer3_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer3_RestoreConfig(void) 
{   
    #if (!Timer3_UsingFixedFunction)

        Timer3_WriteCounter(Timer3_backup.TimerUdb);
        Timer3_STATUS_MASK =Timer3_backup.InterruptMaskValue;
        #if (Timer3_UsingHWCaptureCounter)
            Timer3_SetCaptureCount(Timer3_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer3_UDB_CONTROL_REG_REMOVED)
            Timer3_WriteControlRegister(Timer3_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer3_Sleep
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
*  Timer3_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer3_Sleep(void) 
{
    #if(!Timer3_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer3_CTRL_ENABLE == (Timer3_CONTROL & Timer3_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer3_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer3_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer3_Stop();
    Timer3_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer3_Wakeup
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
*  Timer3_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer3_Wakeup(void) 
{
    Timer3_RestoreConfig();
    #if(!Timer3_UDB_CONTROL_REG_REMOVED)
        if(Timer3_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer3_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
