/*******************************************************************************
* File Name: Enable_t.h  
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

#if !defined(CY_PINS_Enable_t_H) /* Pins Enable_t_H */
#define CY_PINS_Enable_t_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Enable_t_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Enable_t__PORT == 15 && ((Enable_t__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Enable_t_Write(uint8 value);
void    Enable_t_SetDriveMode(uint8 mode);
uint8   Enable_t_ReadDataReg(void);
uint8   Enable_t_Read(void);
void    Enable_t_SetInterruptMode(uint16 position, uint16 mode);
uint8   Enable_t_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Enable_t_SetDriveMode() function.
     *  @{
     */
        #define Enable_t_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Enable_t_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Enable_t_DM_RES_UP          PIN_DM_RES_UP
        #define Enable_t_DM_RES_DWN         PIN_DM_RES_DWN
        #define Enable_t_DM_OD_LO           PIN_DM_OD_LO
        #define Enable_t_DM_OD_HI           PIN_DM_OD_HI
        #define Enable_t_DM_STRONG          PIN_DM_STRONG
        #define Enable_t_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Enable_t_MASK               Enable_t__MASK
#define Enable_t_SHIFT              Enable_t__SHIFT
#define Enable_t_WIDTH              1u

/* Interrupt constants */
#if defined(Enable_t__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Enable_t_SetInterruptMode() function.
     *  @{
     */
        #define Enable_t_INTR_NONE      (uint16)(0x0000u)
        #define Enable_t_INTR_RISING    (uint16)(0x0001u)
        #define Enable_t_INTR_FALLING   (uint16)(0x0002u)
        #define Enable_t_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Enable_t_INTR_MASK      (0x01u) 
#endif /* (Enable_t__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Enable_t_PS                     (* (reg8 *) Enable_t__PS)
/* Data Register */
#define Enable_t_DR                     (* (reg8 *) Enable_t__DR)
/* Port Number */
#define Enable_t_PRT_NUM                (* (reg8 *) Enable_t__PRT) 
/* Connect to Analog Globals */                                                  
#define Enable_t_AG                     (* (reg8 *) Enable_t__AG)                       
/* Analog MUX bux enable */
#define Enable_t_AMUX                   (* (reg8 *) Enable_t__AMUX) 
/* Bidirectional Enable */                                                        
#define Enable_t_BIE                    (* (reg8 *) Enable_t__BIE)
/* Bit-mask for Aliased Register Access */
#define Enable_t_BIT_MASK               (* (reg8 *) Enable_t__BIT_MASK)
/* Bypass Enable */
#define Enable_t_BYP                    (* (reg8 *) Enable_t__BYP)
/* Port wide control signals */                                                   
#define Enable_t_CTL                    (* (reg8 *) Enable_t__CTL)
/* Drive Modes */
#define Enable_t_DM0                    (* (reg8 *) Enable_t__DM0) 
#define Enable_t_DM1                    (* (reg8 *) Enable_t__DM1)
#define Enable_t_DM2                    (* (reg8 *) Enable_t__DM2) 
/* Input Buffer Disable Override */
#define Enable_t_INP_DIS                (* (reg8 *) Enable_t__INP_DIS)
/* LCD Common or Segment Drive */
#define Enable_t_LCD_COM_SEG            (* (reg8 *) Enable_t__LCD_COM_SEG)
/* Enable Segment LCD */
#define Enable_t_LCD_EN                 (* (reg8 *) Enable_t__LCD_EN)
/* Slew Rate Control */
#define Enable_t_SLW                    (* (reg8 *) Enable_t__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Enable_t_PRTDSI__CAPS_SEL       (* (reg8 *) Enable_t__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Enable_t_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Enable_t__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Enable_t_PRTDSI__OE_SEL0        (* (reg8 *) Enable_t__PRTDSI__OE_SEL0) 
#define Enable_t_PRTDSI__OE_SEL1        (* (reg8 *) Enable_t__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Enable_t_PRTDSI__OUT_SEL0       (* (reg8 *) Enable_t__PRTDSI__OUT_SEL0) 
#define Enable_t_PRTDSI__OUT_SEL1       (* (reg8 *) Enable_t__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Enable_t_PRTDSI__SYNC_OUT       (* (reg8 *) Enable_t__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Enable_t__SIO_CFG)
    #define Enable_t_SIO_HYST_EN        (* (reg8 *) Enable_t__SIO_HYST_EN)
    #define Enable_t_SIO_REG_HIFREQ     (* (reg8 *) Enable_t__SIO_REG_HIFREQ)
    #define Enable_t_SIO_CFG            (* (reg8 *) Enable_t__SIO_CFG)
    #define Enable_t_SIO_DIFF           (* (reg8 *) Enable_t__SIO_DIFF)
#endif /* (Enable_t__SIO_CFG) */

/* Interrupt Registers */
#if defined(Enable_t__INTSTAT)
    #define Enable_t_INTSTAT            (* (reg8 *) Enable_t__INTSTAT)
    #define Enable_t_SNAP               (* (reg8 *) Enable_t__SNAP)
    
	#define Enable_t_0_INTTYPE_REG 		(* (reg8 *) Enable_t__0__INTTYPE)
#endif /* (Enable_t__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Enable_t_H */


/* [] END OF FILE */
