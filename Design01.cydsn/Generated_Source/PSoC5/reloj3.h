/*******************************************************************************
* File Name: reloj3.h
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

#if !defined(CY_CLOCK_reloj3_H)
#define CY_CLOCK_reloj3_H

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

void reloj3_Start(void) ;
void reloj3_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void reloj3_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void reloj3_StandbyPower(uint8 state) ;
void reloj3_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 reloj3_GetDividerRegister(void) ;
void reloj3_SetModeRegister(uint8 modeBitMask) ;
void reloj3_ClearModeRegister(uint8 modeBitMask) ;
uint8 reloj3_GetModeRegister(void) ;
void reloj3_SetSourceRegister(uint8 clkSource) ;
uint8 reloj3_GetSourceRegister(void) ;
#if defined(reloj3__CFG3)
void reloj3_SetPhaseRegister(uint8 clkPhase) ;
uint8 reloj3_GetPhaseRegister(void) ;
#endif /* defined(reloj3__CFG3) */

#define reloj3_Enable()                       reloj3_Start()
#define reloj3_Disable()                      reloj3_Stop()
#define reloj3_SetDivider(clkDivider)         reloj3_SetDividerRegister(clkDivider, 1u)
#define reloj3_SetDividerValue(clkDivider)    reloj3_SetDividerRegister((clkDivider) - 1u, 1u)
#define reloj3_SetMode(clkMode)               reloj3_SetModeRegister(clkMode)
#define reloj3_SetSource(clkSource)           reloj3_SetSourceRegister(clkSource)
#if defined(reloj3__CFG3)
#define reloj3_SetPhase(clkPhase)             reloj3_SetPhaseRegister(clkPhase)
#define reloj3_SetPhaseValue(clkPhase)        reloj3_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(reloj3__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define reloj3_CLKEN              (* (reg8 *) reloj3__PM_ACT_CFG)
#define reloj3_CLKEN_PTR          ((reg8 *) reloj3__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define reloj3_CLKSTBY            (* (reg8 *) reloj3__PM_STBY_CFG)
#define reloj3_CLKSTBY_PTR        ((reg8 *) reloj3__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define reloj3_DIV_LSB            (* (reg8 *) reloj3__CFG0)
#define reloj3_DIV_LSB_PTR        ((reg8 *) reloj3__CFG0)
#define reloj3_DIV_PTR            ((reg16 *) reloj3__CFG0)

/* Clock MSB divider configuration register. */
#define reloj3_DIV_MSB            (* (reg8 *) reloj3__CFG1)
#define reloj3_DIV_MSB_PTR        ((reg8 *) reloj3__CFG1)

/* Mode and source configuration register */
#define reloj3_MOD_SRC            (* (reg8 *) reloj3__CFG2)
#define reloj3_MOD_SRC_PTR        ((reg8 *) reloj3__CFG2)

#if defined(reloj3__CFG3)
/* Analog clock phase configuration register */
#define reloj3_PHASE              (* (reg8 *) reloj3__CFG3)
#define reloj3_PHASE_PTR          ((reg8 *) reloj3__CFG3)
#endif /* defined(reloj3__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define reloj3_CLKEN_MASK         reloj3__PM_ACT_MSK
#define reloj3_CLKSTBY_MASK       reloj3__PM_STBY_MSK

/* CFG2 field masks */
#define reloj3_SRC_SEL_MSK        reloj3__CFG2_SRC_SEL_MASK
#define reloj3_MODE_MASK          (~(reloj3_SRC_SEL_MSK))

#if defined(reloj3__CFG3)
/* CFG3 phase mask */
#define reloj3_PHASE_MASK         reloj3__CFG3_PHASE_DLY_MASK
#endif /* defined(reloj3__CFG3) */

#endif /* CY_CLOCK_reloj3_H */


/* [] END OF FILE */
