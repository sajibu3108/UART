/*******************************************************************************
* File Name: ResetTimer.c  
* Version 1.80
*
* Description:
*  This file contains API to enable firmware control of a Control Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "ResetTimer.h"

/* Check for removal by optimization */
#if !defined(ResetTimer_Sync_ctrl_reg__REMOVED)

    
/*******************************************************************************
* Function Name: ResetTimer_Write
********************************************************************************
*
* Summary:
*  Write a byte to the Control Register.
*
* Parameters:
*  control:  The value to be assigned to the Control Register.
*
* Return:
*  None.
*
*******************************************************************************/
void ResetTimer_Write(uint8 control) 
{
    ResetTimer_Control = control;
}


/*******************************************************************************
* Function Name: ResetTimer_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Control Register.
*
* Parameters:
*  None.
*
* Return:
*  Returns the current value in the Control Register.
*
*******************************************************************************/
uint8 ResetTimer_Read(void) 
{
    return ResetTimer_Control;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
