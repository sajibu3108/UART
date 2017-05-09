/*******************************************************************************
* File Name: TEST2.h  
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

#if !defined(CY_PINS_TEST2_H) /* Pins TEST2_H */
#define CY_PINS_TEST2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TEST2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TEST2__PORT == 15 && ((TEST2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    TEST2_Write(uint8 value);
void    TEST2_SetDriveMode(uint8 mode);
uint8   TEST2_ReadDataReg(void);
uint8   TEST2_Read(void);
void    TEST2_SetInterruptMode(uint16 position, uint16 mode);
uint8   TEST2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the TEST2_SetDriveMode() function.
     *  @{
     */
        #define TEST2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define TEST2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define TEST2_DM_RES_UP          PIN_DM_RES_UP
        #define TEST2_DM_RES_DWN         PIN_DM_RES_DWN
        #define TEST2_DM_OD_LO           PIN_DM_OD_LO
        #define TEST2_DM_OD_HI           PIN_DM_OD_HI
        #define TEST2_DM_STRONG          PIN_DM_STRONG
        #define TEST2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define TEST2_MASK               TEST2__MASK
#define TEST2_SHIFT              TEST2__SHIFT
#define TEST2_WIDTH              1u

/* Interrupt constants */
#if defined(TEST2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TEST2_SetInterruptMode() function.
     *  @{
     */
        #define TEST2_INTR_NONE      (uint16)(0x0000u)
        #define TEST2_INTR_RISING    (uint16)(0x0001u)
        #define TEST2_INTR_FALLING   (uint16)(0x0002u)
        #define TEST2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define TEST2_INTR_MASK      (0x01u) 
#endif /* (TEST2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TEST2_PS                     (* (reg8 *) TEST2__PS)
/* Data Register */
#define TEST2_DR                     (* (reg8 *) TEST2__DR)
/* Port Number */
#define TEST2_PRT_NUM                (* (reg8 *) TEST2__PRT) 
/* Connect to Analog Globals */                                                  
#define TEST2_AG                     (* (reg8 *) TEST2__AG)                       
/* Analog MUX bux enable */
#define TEST2_AMUX                   (* (reg8 *) TEST2__AMUX) 
/* Bidirectional Enable */                                                        
#define TEST2_BIE                    (* (reg8 *) TEST2__BIE)
/* Bit-mask for Aliased Register Access */
#define TEST2_BIT_MASK               (* (reg8 *) TEST2__BIT_MASK)
/* Bypass Enable */
#define TEST2_BYP                    (* (reg8 *) TEST2__BYP)
/* Port wide control signals */                                                   
#define TEST2_CTL                    (* (reg8 *) TEST2__CTL)
/* Drive Modes */
#define TEST2_DM0                    (* (reg8 *) TEST2__DM0) 
#define TEST2_DM1                    (* (reg8 *) TEST2__DM1)
#define TEST2_DM2                    (* (reg8 *) TEST2__DM2) 
/* Input Buffer Disable Override */
#define TEST2_INP_DIS                (* (reg8 *) TEST2__INP_DIS)
/* LCD Common or Segment Drive */
#define TEST2_LCD_COM_SEG            (* (reg8 *) TEST2__LCD_COM_SEG)
/* Enable Segment LCD */
#define TEST2_LCD_EN                 (* (reg8 *) TEST2__LCD_EN)
/* Slew Rate Control */
#define TEST2_SLW                    (* (reg8 *) TEST2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TEST2_PRTDSI__CAPS_SEL       (* (reg8 *) TEST2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TEST2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TEST2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TEST2_PRTDSI__OE_SEL0        (* (reg8 *) TEST2__PRTDSI__OE_SEL0) 
#define TEST2_PRTDSI__OE_SEL1        (* (reg8 *) TEST2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TEST2_PRTDSI__OUT_SEL0       (* (reg8 *) TEST2__PRTDSI__OUT_SEL0) 
#define TEST2_PRTDSI__OUT_SEL1       (* (reg8 *) TEST2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TEST2_PRTDSI__SYNC_OUT       (* (reg8 *) TEST2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(TEST2__SIO_CFG)
    #define TEST2_SIO_HYST_EN        (* (reg8 *) TEST2__SIO_HYST_EN)
    #define TEST2_SIO_REG_HIFREQ     (* (reg8 *) TEST2__SIO_REG_HIFREQ)
    #define TEST2_SIO_CFG            (* (reg8 *) TEST2__SIO_CFG)
    #define TEST2_SIO_DIFF           (* (reg8 *) TEST2__SIO_DIFF)
#endif /* (TEST2__SIO_CFG) */

/* Interrupt Registers */
#if defined(TEST2__INTSTAT)
    #define TEST2_INTSTAT            (* (reg8 *) TEST2__INTSTAT)
    #define TEST2_SNAP               (* (reg8 *) TEST2__SNAP)
    
	#define TEST2_0_INTTYPE_REG 		(* (reg8 *) TEST2__0__INTTYPE)
#endif /* (TEST2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TEST2_H */


/* [] END OF FILE */
