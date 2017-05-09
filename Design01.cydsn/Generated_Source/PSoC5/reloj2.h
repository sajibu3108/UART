/*******************************************************************************
* File Name: reloj2.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_reloj2_H)
#define CY_CLOCK_reloj2_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void reloj2_Start(void) ;
void reloj2_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void reloj2_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void reloj2_StandbyPower(uint8 state) ;
void reloj2_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 reloj2_GetDividerRegister(void) ;
void reloj2_SetModeRegister(uint8 modeBitMask) ;
void reloj2_ClearModeRegister(uint8 modeBitMask) ;
uint8 reloj2_GetModeRegister(void) ;
void reloj2_SetSourceRegister(uint8 clkSource) ;
uint8 reloj2_GetSourceRegister(void) ;
#if defined(reloj2__CFG3)
void reloj2_SetPhaseRegister(uint8 clkPhase) ;
uint8 reloj2_GetPhaseRegister(void) ;
#endif /* defined(reloj2__CFG3) */

#define reloj2_Enable()                       reloj2_Start()
#define reloj2_Disable()                      reloj2_Stop()
#define reloj2_SetDivider(clkDivider)         reloj2_SetDividerRegister(clkDivider, 1u)
#define reloj2_SetDividerValue(clkDivider)    reloj2_SetDividerRegister((clkDivider) - 1u, 1u)
#define reloj2_SetMode(clkMode)               reloj2_SetModeRegister(clkMode)
#define reloj2_SetSource(clkSource)           reloj2_SetSourceRegister(clkSource)
#if defined(reloj2__CFG3)
#define reloj2_SetPhase(clkPhase)             reloj2_SetPhaseRegister(clkPhase)
#define reloj2_SetPhaseValue(clkPhase)        reloj2_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(reloj2__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define reloj2_CLKEN              (* (reg8 *) reloj2__PM_ACT_CFG)
#define reloj2_CLKEN_PTR          ((reg8 *) reloj2__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define reloj2_CLKSTBY            (* (reg8 *) reloj2__PM_STBY_CFG)
#define reloj2_CLKSTBY_PTR        ((reg8 *) reloj2__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define reloj2_DIV_LSB            (* (reg8 *) reloj2__CFG0)
#define reloj2_DIV_LSB_PTR        ((reg8 *) reloj2__CFG0)
#define reloj2_DIV_PTR            ((reg16 *) reloj2__CFG0)

/* Clock MSB divider configuration register. */
#define reloj2_DIV_MSB            (* (reg8 *) reloj2__CFG1)
#define reloj2_DIV_MSB_PTR        ((reg8 *) reloj2__CFG1)

/* Mode and source configuration register */
#define reloj2_MOD_SRC            (* (reg8 *) reloj2__CFG2)
#define reloj2_MOD_SRC_PTR        ((reg8 *) reloj2__CFG2)

#if defined(reloj2__CFG3)
/* Analog clock phase configuration register */
#define reloj2_PHASE              (* (reg8 *) reloj2__CFG3)
#define reloj2_PHASE_PTR          ((reg8 *) reloj2__CFG3)
#endif /* defined(reloj2__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define reloj2_CLKEN_MASK         reloj2__PM_ACT_MSK
#define reloj2_CLKSTBY_MASK       reloj2__PM_STBY_MSK

/* CFG2 field masks */
#define reloj2_SRC_SEL_MSK        reloj2__CFG2_SRC_SEL_MASK
#define reloj2_MODE_MASK          (~(reloj2_SRC_SEL_MSK))

#if defined(reloj2__CFG3)
/* CFG3 phase mask */
#define reloj2_PHASE_MASK         reloj2__CFG3_PHASE_DLY_MASK
#endif /* defined(reloj2__CFG3) */

#endif /* CY_CLOCK_reloj2_H */


/* [] END OF FILE */
