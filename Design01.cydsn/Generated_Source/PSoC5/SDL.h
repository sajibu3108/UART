/*******************************************************************************
* File Name: SDL.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_SDL_H) /* Pins SDL_H */
#define CY_PINS_SDL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SDL_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SDL__PORT == 15 && ((SDL__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    SDL_Write(uint8 value) ;
void    SDL_SetDriveMode(uint8 mode) ;
uint8   SDL_ReadDataReg(void) ;
uint8   SDL_Read(void) ;
uint8   SDL_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SDL_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define SDL_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define SDL_DM_RES_UP          PIN_DM_RES_UP
#define SDL_DM_RES_DWN         PIN_DM_RES_DWN
#define SDL_DM_OD_LO           PIN_DM_OD_LO
#define SDL_DM_OD_HI           PIN_DM_OD_HI
#define SDL_DM_STRONG          PIN_DM_STRONG
#define SDL_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define SDL_MASK               SDL__MASK
#define SDL_SHIFT              SDL__SHIFT
#define SDL_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SDL_PS                     (* (reg8 *) SDL__PS)
/* Data Register */
#define SDL_DR                     (* (reg8 *) SDL__DR)
/* Port Number */
#define SDL_PRT_NUM                (* (reg8 *) SDL__PRT) 
/* Connect to Analog Globals */                                                  
#define SDL_AG                     (* (reg8 *) SDL__AG)                       
/* Analog MUX bux enable */
#define SDL_AMUX                   (* (reg8 *) SDL__AMUX) 
/* Bidirectional Enable */                                                        
#define SDL_BIE                    (* (reg8 *) SDL__BIE)
/* Bit-mask for Aliased Register Access */
#define SDL_BIT_MASK               (* (reg8 *) SDL__BIT_MASK)
/* Bypass Enable */
#define SDL_BYP                    (* (reg8 *) SDL__BYP)
/* Port wide control signals */                                                   
#define SDL_CTL                    (* (reg8 *) SDL__CTL)
/* Drive Modes */
#define SDL_DM0                    (* (reg8 *) SDL__DM0) 
#define SDL_DM1                    (* (reg8 *) SDL__DM1)
#define SDL_DM2                    (* (reg8 *) SDL__DM2) 
/* Input Buffer Disable Override */
#define SDL_INP_DIS                (* (reg8 *) SDL__INP_DIS)
/* LCD Common or Segment Drive */
#define SDL_LCD_COM_SEG            (* (reg8 *) SDL__LCD_COM_SEG)
/* Enable Segment LCD */
#define SDL_LCD_EN                 (* (reg8 *) SDL__LCD_EN)
/* Slew Rate Control */
#define SDL_SLW                    (* (reg8 *) SDL__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SDL_PRTDSI__CAPS_SEL       (* (reg8 *) SDL__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SDL_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SDL__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SDL_PRTDSI__OE_SEL0        (* (reg8 *) SDL__PRTDSI__OE_SEL0) 
#define SDL_PRTDSI__OE_SEL1        (* (reg8 *) SDL__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SDL_PRTDSI__OUT_SEL0       (* (reg8 *) SDL__PRTDSI__OUT_SEL0) 
#define SDL_PRTDSI__OUT_SEL1       (* (reg8 *) SDL__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SDL_PRTDSI__SYNC_OUT       (* (reg8 *) SDL__PRTDSI__SYNC_OUT) 


#if defined(SDL__INTSTAT)  /* Interrupt Registers */

    #define SDL_INTSTAT                (* (reg8 *) SDL__INTSTAT)
    #define SDL_SNAP                   (* (reg8 *) SDL__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SDL_H */


/* [] END OF FILE */
