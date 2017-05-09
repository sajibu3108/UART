/*******************************************************************************
* File Name: Jump.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Jump_H) /* Pins Jump_H */
#define CY_PINS_Jump_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Jump_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Jump__PORT == 15 && ((Jump__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Jump_Write(uint8 value);
void    Jump_SetDriveMode(uint8 mode);
uint8   Jump_ReadDataReg(void);
uint8   Jump_Read(void);
void    Jump_SetInterruptMode(uint16 position, uint16 mode);
uint8   Jump_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Jump_SetDriveMode() function.
     *  @{
     */
        #define Jump_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Jump_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Jump_DM_RES_UP          PIN_DM_RES_UP
        #define Jump_DM_RES_DWN         PIN_DM_RES_DWN
        #define Jump_DM_OD_LO           PIN_DM_OD_LO
        #define Jump_DM_OD_HI           PIN_DM_OD_HI
        #define Jump_DM_STRONG          PIN_DM_STRONG
        #define Jump_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Jump_MASK               Jump__MASK
#define Jump_SHIFT              Jump__SHIFT
#define Jump_WIDTH              1u

/* Interrupt constants */
#if defined(Jump__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Jump_SetInterruptMode() function.
     *  @{
     */
        #define Jump_INTR_NONE      (uint16)(0x0000u)
        #define Jump_INTR_RISING    (uint16)(0x0001u)
        #define Jump_INTR_FALLING   (uint16)(0x0002u)
        #define Jump_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Jump_INTR_MASK      (0x01u) 
#endif /* (Jump__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Jump_PS                     (* (reg8 *) Jump__PS)
/* Data Register */
#define Jump_DR                     (* (reg8 *) Jump__DR)
/* Port Number */
#define Jump_PRT_NUM                (* (reg8 *) Jump__PRT) 
/* Connect to Analog Globals */                                                  
#define Jump_AG                     (* (reg8 *) Jump__AG)                       
/* Analog MUX bux enable */
#define Jump_AMUX                   (* (reg8 *) Jump__AMUX) 
/* Bidirectional Enable */                                                        
#define Jump_BIE                    (* (reg8 *) Jump__BIE)
/* Bit-mask for Aliased Register Access */
#define Jump_BIT_MASK               (* (reg8 *) Jump__BIT_MASK)
/* Bypass Enable */
#define Jump_BYP                    (* (reg8 *) Jump__BYP)
/* Port wide control signals */                                                   
#define Jump_CTL                    (* (reg8 *) Jump__CTL)
/* Drive Modes */
#define Jump_DM0                    (* (reg8 *) Jump__DM0) 
#define Jump_DM1                    (* (reg8 *) Jump__DM1)
#define Jump_DM2                    (* (reg8 *) Jump__DM2) 
/* Input Buffer Disable Override */
#define Jump_INP_DIS                (* (reg8 *) Jump__INP_DIS)
/* LCD Common or Segment Drive */
#define Jump_LCD_COM_SEG            (* (reg8 *) Jump__LCD_COM_SEG)
/* Enable Segment LCD */
#define Jump_LCD_EN                 (* (reg8 *) Jump__LCD_EN)
/* Slew Rate Control */
#define Jump_SLW                    (* (reg8 *) Jump__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Jump_PRTDSI__CAPS_SEL       (* (reg8 *) Jump__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Jump_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Jump__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Jump_PRTDSI__OE_SEL0        (* (reg8 *) Jump__PRTDSI__OE_SEL0) 
#define Jump_PRTDSI__OE_SEL1        (* (reg8 *) Jump__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Jump_PRTDSI__OUT_SEL0       (* (reg8 *) Jump__PRTDSI__OUT_SEL0) 
#define Jump_PRTDSI__OUT_SEL1       (* (reg8 *) Jump__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Jump_PRTDSI__SYNC_OUT       (* (reg8 *) Jump__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Jump__SIO_CFG)
    #define Jump_SIO_HYST_EN        (* (reg8 *) Jump__SIO_HYST_EN)
    #define Jump_SIO_REG_HIFREQ     (* (reg8 *) Jump__SIO_REG_HIFREQ)
    #define Jump_SIO_CFG            (* (reg8 *) Jump__SIO_CFG)
    #define Jump_SIO_DIFF           (* (reg8 *) Jump__SIO_DIFF)
#endif /* (Jump__SIO_CFG) */

/* Interrupt Registers */
#if defined(Jump__INTSTAT)
    #define Jump_INTSTAT            (* (reg8 *) Jump__INTSTAT)
    #define Jump_SNAP               (* (reg8 *) Jump__SNAP)
    
	#define Jump_0_INTTYPE_REG 		(* (reg8 *) Jump__0__INTTYPE)
#endif /* (Jump__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Jump_H */


/* [] END OF FILE */
