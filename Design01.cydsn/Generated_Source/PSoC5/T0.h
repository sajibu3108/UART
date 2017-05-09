/*******************************************************************************
* File Name: T0.h
* Version 2.70
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_60_T0_H)
#define CY_Timer_v2_60_T0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 T0_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define T0_Resolution                 16u
#define T0_UsingFixedFunction         0u
#define T0_UsingHWCaptureCounter      0u
#define T0_SoftwareCaptureMode        0u
#define T0_SoftwareTriggerMode        0u
#define T0_UsingHWEnable              0u
#define T0_EnableTriggerMode          0u
#define T0_InterruptOnCaptureCount    0u
#define T0_RunModeUsed                0u
#define T0_ControlRegRemoved          0u

#if defined(T0_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define T0_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (T0_UsingFixedFunction)
    #define T0_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define T0_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End T0_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!T0_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (T0_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!T0_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}T0_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    T0_Start(void) ;
void    T0_Stop(void) ;

void    T0_SetInterruptMode(uint8 interruptMode) ;
uint8   T0_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define T0_GetInterruptSource() T0_ReadStatusRegister()

#if(!T0_UDB_CONTROL_REG_REMOVED)
    uint8   T0_ReadControlRegister(void) ;
    void    T0_WriteControlRegister(uint8 control) ;
#endif /* (!T0_UDB_CONTROL_REG_REMOVED) */

uint16  T0_ReadPeriod(void) ;
void    T0_WritePeriod(uint16 period) ;
uint16  T0_ReadCounter(void) ;
void    T0_WriteCounter(uint16 counter) ;
uint16  T0_ReadCapture(void) ;
void    T0_SoftwareCapture(void) ;

#if(!T0_UsingFixedFunction) /* UDB Prototypes */
    #if (T0_SoftwareCaptureMode)
        void    T0_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!T0_UsingFixedFunction) */

    #if (T0_SoftwareTriggerMode)
        void    T0_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (T0_SoftwareTriggerMode) */

    #if (T0_EnableTriggerMode)
        void    T0_EnableTrigger(void) ;
        void    T0_DisableTrigger(void) ;
    #endif /* (T0_EnableTriggerMode) */


    #if(T0_InterruptOnCaptureCount)
        void    T0_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (T0_InterruptOnCaptureCount) */

    #if (T0_UsingHWCaptureCounter)
        void    T0_SetCaptureCount(uint8 captureCount) ;
        uint8   T0_ReadCaptureCount(void) ;
    #endif /* (T0_UsingHWCaptureCounter) */

    void T0_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void T0_Init(void)          ;
void T0_Enable(void)        ;
void T0_SaveConfig(void)    ;
void T0_RestoreConfig(void) ;
void T0_Sleep(void)         ;
void T0_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define T0__B_TIMER__CM_NONE 0
#define T0__B_TIMER__CM_RISINGEDGE 1
#define T0__B_TIMER__CM_FALLINGEDGE 2
#define T0__B_TIMER__CM_EITHEREDGE 3
#define T0__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define T0__B_TIMER__TM_NONE 0x00u
#define T0__B_TIMER__TM_RISINGEDGE 0x04u
#define T0__B_TIMER__TM_FALLINGEDGE 0x08u
#define T0__B_TIMER__TM_EITHEREDGE 0x0Cu
#define T0__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define T0_INIT_PERIOD             65535u
#define T0_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << T0_CTRL_CAP_MODE_SHIFT))
#define T0_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << T0_CTRL_TRIG_MODE_SHIFT))
#if (T0_UsingFixedFunction)
    #define T0_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << T0_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << T0_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define T0_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << T0_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << T0_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << T0_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (T0_UsingFixedFunction) */
#define T0_INIT_CAPTURE_COUNT      (2u)
#define T0_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << T0_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (T0_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define T0_STATUS         (*(reg8 *) T0_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define T0_STATUS_MASK    (*(reg8 *) T0_TimerHW__SR0 )
    #define T0_CONTROL        (*(reg8 *) T0_TimerHW__CFG0)
    #define T0_CONTROL2       (*(reg8 *) T0_TimerHW__CFG1)
    #define T0_CONTROL2_PTR   ( (reg8 *) T0_TimerHW__CFG1)
    #define T0_RT1            (*(reg8 *) T0_TimerHW__RT1)
    #define T0_RT1_PTR        ( (reg8 *) T0_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define T0_CONTROL3       (*(reg8 *) T0_TimerHW__CFG2)
        #define T0_CONTROL3_PTR   ( (reg8 *) T0_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define T0_GLOBAL_ENABLE  (*(reg8 *) T0_TimerHW__PM_ACT_CFG)
    #define T0_GLOBAL_STBY_ENABLE  (*(reg8 *) T0_TimerHW__PM_STBY_CFG)

    #define T0_CAPTURE_LSB         (* (reg16 *) T0_TimerHW__CAP0 )
    #define T0_CAPTURE_LSB_PTR       ((reg16 *) T0_TimerHW__CAP0 )
    #define T0_PERIOD_LSB          (* (reg16 *) T0_TimerHW__PER0 )
    #define T0_PERIOD_LSB_PTR        ((reg16 *) T0_TimerHW__PER0 )
    #define T0_COUNTER_LSB         (* (reg16 *) T0_TimerHW__CNT_CMP0 )
    #define T0_COUNTER_LSB_PTR       ((reg16 *) T0_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define T0_BLOCK_EN_MASK                     T0_TimerHW__PM_ACT_MSK
    #define T0_BLOCK_STBY_EN_MASK                T0_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define T0_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define T0_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define T0_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define T0_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define T0_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define T0_CTRL_ENABLE                        ((uint8)((uint8)0x01u << T0_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define T0_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define T0_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << T0_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define T0_CTRL_MODE_SHIFT                 0x01u
        #define T0_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << T0_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define T0_CTRL_RCOD_SHIFT        0x02u
        #define T0_CTRL_ENBL_SHIFT        0x00u
        #define T0_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define T0_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << T0_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define T0_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << T0_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define T0_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << T0_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define T0_CTRL_RCOD       ((uint8)((uint8)0x03u << T0_CTRL_RCOD_SHIFT))
        #define T0_CTRL_ENBL       ((uint8)((uint8)0x80u << T0_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define T0_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define T0_RT1_MASK                        ((uint8)((uint8)0x03u << T0_RT1_SHIFT))
    #define T0_SYNC                            ((uint8)((uint8)0x03u << T0_RT1_SHIFT))
    #define T0_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define T0_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << T0_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define T0_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << T0_SYNCDSI_SHIFT))

    #define T0_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << T0_CTRL_MODE_SHIFT))
    #define T0_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << T0_CTRL_MODE_SHIFT))
    #define T0_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << T0_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define T0_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define T0_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define T0_STATUS_TC_INT_MASK_SHIFT        (T0_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define T0_STATUS_CAPTURE_INT_MASK_SHIFT   (T0_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define T0_STATUS_TC                       ((uint8)((uint8)0x01u << T0_STATUS_TC_SHIFT))
    #define T0_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << T0_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define T0_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << T0_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define T0_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << T0_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define T0_STATUS              (* (reg8 *) T0_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define T0_STATUS_MASK         (* (reg8 *) T0_TimerUDB_rstSts_stsreg__MASK_REG)
    #define T0_STATUS_AUX_CTRL     (* (reg8 *) T0_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define T0_CONTROL             (* (reg8 *) T0_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(T0_Resolution <= 8u) /* 8-bit Timer */
        #define T0_CAPTURE_LSB         (* (reg8 *) T0_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define T0_CAPTURE_LSB_PTR       ((reg8 *) T0_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define T0_PERIOD_LSB          (* (reg8 *) T0_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define T0_PERIOD_LSB_PTR        ((reg8 *) T0_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define T0_COUNTER_LSB         (* (reg8 *) T0_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define T0_COUNTER_LSB_PTR       ((reg8 *) T0_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(T0_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define T0_CAPTURE_LSB         (* (reg16 *) T0_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define T0_CAPTURE_LSB_PTR       ((reg16 *) T0_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define T0_PERIOD_LSB          (* (reg16 *) T0_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define T0_PERIOD_LSB_PTR        ((reg16 *) T0_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define T0_COUNTER_LSB         (* (reg16 *) T0_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define T0_COUNTER_LSB_PTR       ((reg16 *) T0_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define T0_CAPTURE_LSB         (* (reg16 *) T0_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define T0_CAPTURE_LSB_PTR       ((reg16 *) T0_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define T0_PERIOD_LSB          (* (reg16 *) T0_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define T0_PERIOD_LSB_PTR        ((reg16 *) T0_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define T0_COUNTER_LSB         (* (reg16 *) T0_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define T0_COUNTER_LSB_PTR       ((reg16 *) T0_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(T0_Resolution <= 24u)/* 24-bit Timer */
        #define T0_CAPTURE_LSB         (* (reg32 *) T0_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define T0_CAPTURE_LSB_PTR       ((reg32 *) T0_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define T0_PERIOD_LSB          (* (reg32 *) T0_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define T0_PERIOD_LSB_PTR        ((reg32 *) T0_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define T0_COUNTER_LSB         (* (reg32 *) T0_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define T0_COUNTER_LSB_PTR       ((reg32 *) T0_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define T0_CAPTURE_LSB         (* (reg32 *) T0_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define T0_CAPTURE_LSB_PTR       ((reg32 *) T0_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define T0_PERIOD_LSB          (* (reg32 *) T0_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define T0_PERIOD_LSB_PTR        ((reg32 *) T0_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define T0_COUNTER_LSB         (* (reg32 *) T0_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define T0_COUNTER_LSB_PTR       ((reg32 *) T0_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define T0_CAPTURE_LSB         (* (reg32 *) T0_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define T0_CAPTURE_LSB_PTR       ((reg32 *) T0_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define T0_PERIOD_LSB          (* (reg32 *) T0_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define T0_PERIOD_LSB_PTR        ((reg32 *) T0_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define T0_COUNTER_LSB         (* (reg32 *) T0_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define T0_COUNTER_LSB_PTR       ((reg32 *) T0_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define T0_COUNTER_LSB_PTR_8BIT       ((reg8 *) T0_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (T0_UsingHWCaptureCounter)
        #define T0_CAP_COUNT              (*(reg8 *) T0_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define T0_CAP_COUNT_PTR          ( (reg8 *) T0_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define T0_CAPTURE_COUNT_CTRL     (*(reg8 *) T0_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define T0_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) T0_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (T0_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define T0_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define T0_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define T0_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define T0_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define T0_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define T0_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << T0_CTRL_INTCNT_SHIFT))
    #define T0_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << T0_CTRL_TRIG_MODE_SHIFT))
    #define T0_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << T0_CTRL_TRIG_EN_SHIFT))
    #define T0_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << T0_CTRL_CAP_MODE_SHIFT))
    #define T0_CTRL_ENABLE                    ((uint8)((uint8)0x01u << T0_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define T0_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define T0_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define T0_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define T0_STATUS_TC_INT_MASK_SHIFT       T0_STATUS_TC_SHIFT
    #define T0_STATUS_CAPTURE_INT_MASK_SHIFT  T0_STATUS_CAPTURE_SHIFT
    #define T0_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define T0_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define T0_STATUS_FIFOFULL_INT_MASK_SHIFT T0_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define T0_STATUS_TC                      ((uint8)((uint8)0x01u << T0_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define T0_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << T0_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define T0_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << T0_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define T0_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << T0_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define T0_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << T0_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define T0_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << T0_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define T0_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << T0_STATUS_FIFOFULL_SHIFT))

    #define T0_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define T0_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define T0_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define T0_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define T0_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define T0_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_T0_H */


/* [] END OF FILE */
