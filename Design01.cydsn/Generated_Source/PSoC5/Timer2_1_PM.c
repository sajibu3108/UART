/*******************************************************************************
* File Name: Timer2_1_PM.c
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

#include "Timer2_1.h"

static Timer2_1_backupStruct Timer2_1_backup;


/*******************************************************************************
* Function Name: Timer2_1_SaveConfig
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
*  Timer2_1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer2_1_SaveConfig(void) 
{
    #if (!Timer2_1_UsingFixedFunction)
        Timer2_1_backup.TimerUdb = Timer2_1_ReadCounter();
        Timer2_1_backup.InterruptMaskValue = Timer2_1_STATUS_MASK;
        #if (Timer2_1_UsingHWCaptureCounter)
            Timer2_1_backup.TimerCaptureCounter = Timer2_1_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer2_1_UDB_CONTROL_REG_REMOVED)
            Timer2_1_backup.TimerControlRegister = Timer2_1_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer2_1_RestoreConfig
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
*  Timer2_1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer2_1_RestoreConfig(void) 
{   
    #if (!Timer2_1_UsingFixedFunction)

        Timer2_1_WriteCounter(Timer2_1_backup.TimerUdb);
        Timer2_1_STATUS_MASK =Timer2_1_backup.InterruptMaskValue;
        #if (Timer2_1_UsingHWCaptureCounter)
            Timer2_1_SetCaptureCount(Timer2_1_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer2_1_UDB_CONTROL_REG_REMOVED)
            Timer2_1_WriteControlRegister(Timer2_1_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer2_1_Sleep
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
*  Timer2_1_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer2_1_Sleep(void) 
{
    #if(!Timer2_1_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer2_1_CTRL_ENABLE == (Timer2_1_CONTROL & Timer2_1_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer2_1_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer2_1_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer2_1_Stop();
    Timer2_1_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer2_1_Wakeup
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
*  Timer2_1_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer2_1_Wakeup(void) 
{
    Timer2_1_RestoreConfig();
    #if(!Timer2_1_UDB_CONTROL_REG_REMOVED)
        if(Timer2_1_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer2_1_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
