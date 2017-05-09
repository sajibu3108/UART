/*******************************************************************************
* File Name: T100.h
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

#if !defined(CY_Timer_v2_60_T100_H)
#define CY_Timer_v2_60_T100_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 T100_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define T100_Resolution                 16u
#define T100_UsingFixedFunction         0u
#define T100_UsingHWCaptureCounter      0u
#define T100_SoftwareCaptureMode        0u
#define T100_SoftwareTriggerMode        0u
#define T100_UsingHWEnable              0u
#define T100_EnableTriggerMode          0u
#define T100_InterruptOnCaptureCount    0u
#define T100_RunModeUsed                0u
#define T100_ControlRegRemoved          0u

#if defined(T100_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define T100_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (T100_UsingFixedFunction)
    #define T100_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define T100_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End T100_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!T100_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (T100_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!T100_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}T100_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    T100_Start(void) ;
void    T100_Stop(void) ;

void    T100_SetInterruptMode(uint8 interruptMode) ;
uint8   T100_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define T100_GetInterruptSource() T100_ReadStatusRegister()

#if(!T100_UDB_CONTROL_REG_REMOVED)
    uint8   T100_ReadControlRegister(void) ;
    void    T100_WriteControlRegister(uint8 control) ;
#endif /* (!T100_UDB_CONTROL_REG_REMOVED) */

uint16  T100_ReadPeriod(void) ;
void    T100_WritePeriod(uint16 period) ;
uint16  T100_ReadCounter(void) ;
void    T100_WriteCounter(uint16 counter) ;
uint16  T100_ReadCapture(void) ;
void    T100_SoftwareCapture(void) ;

#if(!T100_UsingFixedFunction) /* UDB Prototypes */
    #if (T100_SoftwareCaptureMode)
        void    T100_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!T100_UsingFixedFunction) */

    #if (T100_SoftwareTriggerMode)
        void    T100_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (T100_SoftwareTriggerMode) */

    #if (T100_EnableTriggerMode)
        void    T100_EnableTrigger(void) ;
        void    T100_DisableTrigger(void) ;
    #endif /* (T100_EnableTriggerMode) */


    #if(T100_InterruptOnCaptureCount)
        void    T100_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (T100_InterruptOnCaptureCount) */

    #if (T100_UsingHWCaptureCounter)
        void    T100_SetCaptureCount(uint8 captureCount) ;
        uint8   T100_ReadCaptureCount(void) ;
    #endif /* (T100_UsingHWCaptureCounter) */

    void T100_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void T100_Init(void)          ;
void T100_Enable(void)        ;
void T100_SaveConfig(void)    ;
void T100_RestoreConfig(void) ;
void T100_Sleep(void)         ;
void T100_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define T100__B_TIMER__CM_NONE 0
#define T100__B_TIMER__CM_RISINGEDGE 1
#define T100__B_TIMER__CM_FALLINGEDGE 2
#define T100__B_TIMER__CM_EITHEREDGE 3
#define T100__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define T100__B_TIMER__TM_NONE 0x00u
#define T100__B_TIMER__TM_RISINGEDGE 0x04u
#define T100__B_TIMER__TM_FALLINGEDGE 0x08u
#define T100__B_TIMER__TM_EITHEREDGE 0x0Cu
#define T100__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define T100_INIT_PERIOD             239u
#define T100_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << T100_CTRL_CAP_MODE_SHIFT))
#define T100_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << T100_CTRL_TRIG_MODE_SHIFT))
#if (T100_UsingFixedFunction)
    #define T100_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << T100_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << T100_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define T100_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << T100_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << T100_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << T100_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (T100_UsingFixedFunction) */
#define T100_INIT_CAPTURE_COUNT      (2u)
#define T100_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << T100_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (T100_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define T100_STATUS         (*(reg8 *) T100_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define T100_STATUS_MASK    (*(reg8 *) T100_TimerHW__SR0 )
    #define T100_CONTROL        (*(reg8 *) T100_TimerHW__CFG0)
    #define T100_CONTROL2       (*(reg8 *) T100_TimerHW__CFG1)
    #define T100_CONTROL2_PTR   ( (reg8 *) T100_TimerHW__CFG1)
    #define T100_RT1            (*(reg8 *) T100_TimerHW__RT1)
    #define T100_RT1_PTR        ( (reg8 *) T100_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define T100_CONTROL3       (*(reg8 *) T100_TimerHW__CFG2)
        #define T100_CONTROL3_PTR   ( (reg8 *) T100_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define T100_GLOBAL_ENABLE  (*(reg8 *) T100_TimerHW__PM_ACT_CFG)
    #define T100_GLOBAL_STBY_ENABLE  (*(reg8 *) T100_TimerHW__PM_STBY_CFG)

    #define T100_CAPTURE_LSB         (* (reg16 *) T100_TimerHW__CAP0 )
    #define T100_CAPTURE_LSB_PTR       ((reg16 *) T100_TimerHW__CAP0 )
    #define T100_PERIOD_LSB          (* (reg16 *) T100_TimerHW__PER0 )
    #define T100_PERIOD_LSB_PTR        ((reg16 *) T100_TimerHW__PER0 )
    #define T100_COUNTER_LSB         (* (reg16 *) T100_TimerHW__CNT_CMP0 )
    #define T100_COUNTER_LSB_PTR       ((reg16 *) T100_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define T100_BLOCK_EN_MASK                     T100_TimerHW__PM_ACT_MSK
    #define T100_BLOCK_STBY_EN_MASK                T100_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define T100_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define T100_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define T100_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define T100_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define T100_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define T100_CTRL_ENABLE                        ((uint8)((uint8)0x01u << T100_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define T100_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define T100_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << T100_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define T100_CTRL_MODE_SHIFT                 0x01u
        #define T100_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << T100_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define T100_CTRL_RCOD_SHIFT        0x02u
        #define T100_CTRL_ENBL_SHIFT        0x00u
        #define T100_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define T100_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << T100_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define T100_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << T100_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define T100_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << T100_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define T100_CTRL_RCOD       ((uint8)((uint8)0x03u << T100_CTRL_RCOD_SHIFT))
        #define T100_CTRL_ENBL       ((uint8)((uint8)0x80u << T100_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define T100_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define T100_RT1_MASK                        ((uint8)((uint8)0x03u << T100_RT1_SHIFT))
    #define T100_SYNC                            ((uint8)((uint8)0x03u << T100_RT1_SHIFT))
    #define T100_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define T100_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << T100_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define T100_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << T100_SYNCDSI_SHIFT))

    #define T100_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << T100_CTRL_MODE_SHIFT))
    #define T100_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << T100_CTRL_MODE_SHIFT))
    #define T100_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << T100_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define T100_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define T100_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define T100_STATUS_TC_INT_MASK_SHIFT        (T100_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define T100_STATUS_CAPTURE_INT_MASK_SHIFT   (T100_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define T100_STATUS_TC                       ((uint8)((uint8)0x01u << T100_STATUS_TC_SHIFT))
    #define T100_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << T100_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define T100_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << T100_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define T100_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << T100_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define T100_STATUS              (* (reg8 *) T100_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define T100_STATUS_MASK         (* (reg8 *) T100_TimerUDB_rstSts_stsreg__MASK_REG)
    #define T100_STATUS_AUX_CTRL     (* (reg8 *) T100_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define T100_CONTROL             (* (reg8 *) T100_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(T100_Resolution <= 8u) /* 8-bit Timer */
        #define T100_CAPTURE_LSB         (* (reg8 *) T100_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define T100_CAPTURE_LSB_PTR       ((reg8 *) T100_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define T100_PERIOD_LSB          (* (reg8 *) T100_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define T100_PERIOD_LSB_PTR        ((reg8 *) T100_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define T100_COUNTER_LSB         (* (reg8 *) T100_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define T100_COUNTER_LSB_PTR       ((reg8 *) T100_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(T100_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define T100_CAPTURE_LSB         (* (reg16 *) T100_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define T100_CAPTURE_LSB_PTR       ((reg16 *) T100_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define T100_PERIOD_LSB          (* (reg16 *) T100_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define T100_PERIOD_LSB_PTR        ((reg16 *) T100_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define T100_COUNTER_LSB         (* (reg16 *) T100_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define T100_COUNTER_LSB_PTR       ((reg16 *) T100_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define T100_CAPTURE_LSB         (* (reg16 *) T100_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define T100_CAPTURE_LSB_PTR       ((reg16 *) T100_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define T100_PERIOD_LSB          (* (reg16 *) T100_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define T100_PERIOD_LSB_PTR        ((reg16 *) T100_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define T100_COUNTER_LSB         (* (reg16 *) T100_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define T100_COUNTER_LSB_PTR       ((reg16 *) T100_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(T100_Resolution <= 24u)/* 24-bit Timer */
        #define T100_CAPTURE_LSB         (* (reg32 *) T100_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define T100_CAPTURE_LSB_PTR       ((reg32 *) T100_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define T100_PERIOD_LSB          (* (reg32 *) T100_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define T100_PERIOD_LSB_PTR        ((reg32 *) T100_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define T100_COUNTER_LSB         (* (reg32 *) T100_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define T100_COUNTER_LSB_PTR       ((reg32 *) T100_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define T100_CAPTURE_LSB         (* (reg32 *) T100_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define T100_CAPTURE_LSB_PTR       ((reg32 *) T100_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define T100_PERIOD_LSB          (* (reg32 *) T100_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define T100_PERIOD_LSB_PTR        ((reg32 *) T100_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define T100_COUNTER_LSB         (* (reg32 *) T100_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define T100_COUNTER_LSB_PTR       ((reg32 *) T100_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define T100_CAPTURE_LSB         (* (reg32 *) T100_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define T100_CAPTURE_LSB_PTR       ((reg32 *) T100_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define T100_PERIOD_LSB          (* (reg32 *) T100_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define T100_PERIOD_LSB_PTR        ((reg32 *) T100_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define T100_COUNTER_LSB         (* (reg32 *) T100_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define T100_COUNTER_LSB_PTR       ((reg32 *) T100_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define T100_COUNTER_LSB_PTR_8BIT       ((reg8 *) T100_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (T100_UsingHWCaptureCounter)
        #define T100_CAP_COUNT              (*(reg8 *) T100_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define T100_CAP_COUNT_PTR          ( (reg8 *) T100_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define T100_CAPTURE_COUNT_CTRL     (*(reg8 *) T100_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define T100_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) T100_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (T100_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define T100_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define T100_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define T100_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define T100_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define T100_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define T100_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << T100_CTRL_INTCNT_SHIFT))
    #define T100_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << T100_CTRL_TRIG_MODE_SHIFT))
    #define T100_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << T100_CTRL_TRIG_EN_SHIFT))
    #define T100_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << T100_CTRL_CAP_MODE_SHIFT))
    #define T100_CTRL_ENABLE                    ((uint8)((uint8)0x01u << T100_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define T100_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define T100_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define T100_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define T100_STATUS_TC_INT_MASK_SHIFT       T100_STATUS_TC_SHIFT
    #define T100_STATUS_CAPTURE_INT_MASK_SHIFT  T100_STATUS_CAPTURE_SHIFT
    #define T100_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define T100_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define T100_STATUS_FIFOFULL_INT_MASK_SHIFT T100_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define T100_STATUS_TC                      ((uint8)((uint8)0x01u << T100_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define T100_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << T100_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define T100_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << T100_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define T100_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << T100_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define T100_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << T100_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define T100_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << T100_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define T100_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << T100_STATUS_FIFOFULL_SHIFT))

    #define T100_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define T100_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define T100_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define T100_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define T100_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define T100_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_T100_H */


/* [] END OF FILE */
