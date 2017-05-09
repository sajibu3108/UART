/*******************************************************************************
* File Name: T1.h
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

#if !defined(CY_Timer_v2_60_T1_H)
#define CY_Timer_v2_60_T1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 T1_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define T1_Resolution                 16u
#define T1_UsingFixedFunction         1u
#define T1_UsingHWCaptureCounter      0u
#define T1_SoftwareCaptureMode        0u
#define T1_SoftwareTriggerMode        0u
#define T1_UsingHWEnable              0u
#define T1_EnableTriggerMode          0u
#define T1_InterruptOnCaptureCount    0u
#define T1_RunModeUsed                0u
#define T1_ControlRegRemoved          0u

#if defined(T1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define T1_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (T1_UsingFixedFunction)
    #define T1_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define T1_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End T1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!T1_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (T1_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!T1_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}T1_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    T1_Start(void) ;
void    T1_Stop(void) ;

void    T1_SetInterruptMode(uint8 interruptMode) ;
uint8   T1_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define T1_GetInterruptSource() T1_ReadStatusRegister()

#if(!T1_UDB_CONTROL_REG_REMOVED)
    uint8   T1_ReadControlRegister(void) ;
    void    T1_WriteControlRegister(uint8 control) ;
#endif /* (!T1_UDB_CONTROL_REG_REMOVED) */

uint16  T1_ReadPeriod(void) ;
void    T1_WritePeriod(uint16 period) ;
uint16  T1_ReadCounter(void) ;
void    T1_WriteCounter(uint16 counter) ;
uint16  T1_ReadCapture(void) ;
void    T1_SoftwareCapture(void) ;

#if(!T1_UsingFixedFunction) /* UDB Prototypes */
    #if (T1_SoftwareCaptureMode)
        void    T1_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!T1_UsingFixedFunction) */

    #if (T1_SoftwareTriggerMode)
        void    T1_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (T1_SoftwareTriggerMode) */

    #if (T1_EnableTriggerMode)
        void    T1_EnableTrigger(void) ;
        void    T1_DisableTrigger(void) ;
    #endif /* (T1_EnableTriggerMode) */


    #if(T1_InterruptOnCaptureCount)
        void    T1_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (T1_InterruptOnCaptureCount) */

    #if (T1_UsingHWCaptureCounter)
        void    T1_SetCaptureCount(uint8 captureCount) ;
        uint8   T1_ReadCaptureCount(void) ;
    #endif /* (T1_UsingHWCaptureCounter) */

    void T1_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void T1_Init(void)          ;
void T1_Enable(void)        ;
void T1_SaveConfig(void)    ;
void T1_RestoreConfig(void) ;
void T1_Sleep(void)         ;
void T1_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define T1__B_TIMER__CM_NONE 0
#define T1__B_TIMER__CM_RISINGEDGE 1
#define T1__B_TIMER__CM_FALLINGEDGE 2
#define T1__B_TIMER__CM_EITHEREDGE 3
#define T1__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define T1__B_TIMER__TM_NONE 0x00u
#define T1__B_TIMER__TM_RISINGEDGE 0x04u
#define T1__B_TIMER__TM_FALLINGEDGE 0x08u
#define T1__B_TIMER__TM_EITHEREDGE 0x0Cu
#define T1__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define T1_INIT_PERIOD             199u
#define T1_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << T1_CTRL_CAP_MODE_SHIFT))
#define T1_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << T1_CTRL_TRIG_MODE_SHIFT))
#if (T1_UsingFixedFunction)
    #define T1_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << T1_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << T1_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define T1_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << T1_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << T1_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << T1_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (T1_UsingFixedFunction) */
#define T1_INIT_CAPTURE_COUNT      (2u)
#define T1_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << T1_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (T1_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define T1_STATUS         (*(reg8 *) T1_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define T1_STATUS_MASK    (*(reg8 *) T1_TimerHW__SR0 )
    #define T1_CONTROL        (*(reg8 *) T1_TimerHW__CFG0)
    #define T1_CONTROL2       (*(reg8 *) T1_TimerHW__CFG1)
    #define T1_CONTROL2_PTR   ( (reg8 *) T1_TimerHW__CFG1)
    #define T1_RT1            (*(reg8 *) T1_TimerHW__RT1)
    #define T1_RT1_PTR        ( (reg8 *) T1_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define T1_CONTROL3       (*(reg8 *) T1_TimerHW__CFG2)
        #define T1_CONTROL3_PTR   ( (reg8 *) T1_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define T1_GLOBAL_ENABLE  (*(reg8 *) T1_TimerHW__PM_ACT_CFG)
    #define T1_GLOBAL_STBY_ENABLE  (*(reg8 *) T1_TimerHW__PM_STBY_CFG)

    #define T1_CAPTURE_LSB         (* (reg16 *) T1_TimerHW__CAP0 )
    #define T1_CAPTURE_LSB_PTR       ((reg16 *) T1_TimerHW__CAP0 )
    #define T1_PERIOD_LSB          (* (reg16 *) T1_TimerHW__PER0 )
    #define T1_PERIOD_LSB_PTR        ((reg16 *) T1_TimerHW__PER0 )
    #define T1_COUNTER_LSB         (* (reg16 *) T1_TimerHW__CNT_CMP0 )
    #define T1_COUNTER_LSB_PTR       ((reg16 *) T1_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define T1_BLOCK_EN_MASK                     T1_TimerHW__PM_ACT_MSK
    #define T1_BLOCK_STBY_EN_MASK                T1_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define T1_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define T1_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define T1_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define T1_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define T1_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define T1_CTRL_ENABLE                        ((uint8)((uint8)0x01u << T1_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define T1_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define T1_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << T1_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define T1_CTRL_MODE_SHIFT                 0x01u
        #define T1_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << T1_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define T1_CTRL_RCOD_SHIFT        0x02u
        #define T1_CTRL_ENBL_SHIFT        0x00u
        #define T1_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define T1_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << T1_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define T1_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << T1_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define T1_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << T1_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define T1_CTRL_RCOD       ((uint8)((uint8)0x03u << T1_CTRL_RCOD_SHIFT))
        #define T1_CTRL_ENBL       ((uint8)((uint8)0x80u << T1_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define T1_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define T1_RT1_MASK                        ((uint8)((uint8)0x03u << T1_RT1_SHIFT))
    #define T1_SYNC                            ((uint8)((uint8)0x03u << T1_RT1_SHIFT))
    #define T1_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define T1_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << T1_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define T1_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << T1_SYNCDSI_SHIFT))

    #define T1_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << T1_CTRL_MODE_SHIFT))
    #define T1_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << T1_CTRL_MODE_SHIFT))
    #define T1_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << T1_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define T1_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define T1_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define T1_STATUS_TC_INT_MASK_SHIFT        (T1_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define T1_STATUS_CAPTURE_INT_MASK_SHIFT   (T1_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define T1_STATUS_TC                       ((uint8)((uint8)0x01u << T1_STATUS_TC_SHIFT))
    #define T1_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << T1_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define T1_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << T1_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define T1_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << T1_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define T1_STATUS              (* (reg8 *) T1_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define T1_STATUS_MASK         (* (reg8 *) T1_TimerUDB_rstSts_stsreg__MASK_REG)
    #define T1_STATUS_AUX_CTRL     (* (reg8 *) T1_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define T1_CONTROL             (* (reg8 *) T1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(T1_Resolution <= 8u) /* 8-bit Timer */
        #define T1_CAPTURE_LSB         (* (reg8 *) T1_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define T1_CAPTURE_LSB_PTR       ((reg8 *) T1_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define T1_PERIOD_LSB          (* (reg8 *) T1_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define T1_PERIOD_LSB_PTR        ((reg8 *) T1_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define T1_COUNTER_LSB         (* (reg8 *) T1_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define T1_COUNTER_LSB_PTR       ((reg8 *) T1_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(T1_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define T1_CAPTURE_LSB         (* (reg16 *) T1_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define T1_CAPTURE_LSB_PTR       ((reg16 *) T1_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define T1_PERIOD_LSB          (* (reg16 *) T1_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define T1_PERIOD_LSB_PTR        ((reg16 *) T1_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define T1_COUNTER_LSB         (* (reg16 *) T1_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define T1_COUNTER_LSB_PTR       ((reg16 *) T1_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define T1_CAPTURE_LSB         (* (reg16 *) T1_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define T1_CAPTURE_LSB_PTR       ((reg16 *) T1_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define T1_PERIOD_LSB          (* (reg16 *) T1_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define T1_PERIOD_LSB_PTR        ((reg16 *) T1_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define T1_COUNTER_LSB         (* (reg16 *) T1_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define T1_COUNTER_LSB_PTR       ((reg16 *) T1_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(T1_Resolution <= 24u)/* 24-bit Timer */
        #define T1_CAPTURE_LSB         (* (reg32 *) T1_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define T1_CAPTURE_LSB_PTR       ((reg32 *) T1_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define T1_PERIOD_LSB          (* (reg32 *) T1_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define T1_PERIOD_LSB_PTR        ((reg32 *) T1_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define T1_COUNTER_LSB         (* (reg32 *) T1_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define T1_COUNTER_LSB_PTR       ((reg32 *) T1_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define T1_CAPTURE_LSB         (* (reg32 *) T1_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define T1_CAPTURE_LSB_PTR       ((reg32 *) T1_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define T1_PERIOD_LSB          (* (reg32 *) T1_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define T1_PERIOD_LSB_PTR        ((reg32 *) T1_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define T1_COUNTER_LSB         (* (reg32 *) T1_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define T1_COUNTER_LSB_PTR       ((reg32 *) T1_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define T1_CAPTURE_LSB         (* (reg32 *) T1_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define T1_CAPTURE_LSB_PTR       ((reg32 *) T1_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define T1_PERIOD_LSB          (* (reg32 *) T1_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define T1_PERIOD_LSB_PTR        ((reg32 *) T1_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define T1_COUNTER_LSB         (* (reg32 *) T1_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define T1_COUNTER_LSB_PTR       ((reg32 *) T1_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define T1_COUNTER_LSB_PTR_8BIT       ((reg8 *) T1_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (T1_UsingHWCaptureCounter)
        #define T1_CAP_COUNT              (*(reg8 *) T1_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define T1_CAP_COUNT_PTR          ( (reg8 *) T1_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define T1_CAPTURE_COUNT_CTRL     (*(reg8 *) T1_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define T1_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) T1_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (T1_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define T1_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define T1_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define T1_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define T1_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define T1_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define T1_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << T1_CTRL_INTCNT_SHIFT))
    #define T1_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << T1_CTRL_TRIG_MODE_SHIFT))
    #define T1_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << T1_CTRL_TRIG_EN_SHIFT))
    #define T1_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << T1_CTRL_CAP_MODE_SHIFT))
    #define T1_CTRL_ENABLE                    ((uint8)((uint8)0x01u << T1_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define T1_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define T1_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define T1_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define T1_STATUS_TC_INT_MASK_SHIFT       T1_STATUS_TC_SHIFT
    #define T1_STATUS_CAPTURE_INT_MASK_SHIFT  T1_STATUS_CAPTURE_SHIFT
    #define T1_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define T1_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define T1_STATUS_FIFOFULL_INT_MASK_SHIFT T1_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define T1_STATUS_TC                      ((uint8)((uint8)0x01u << T1_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define T1_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << T1_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define T1_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << T1_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define T1_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << T1_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define T1_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << T1_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define T1_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << T1_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define T1_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << T1_STATUS_FIFOFULL_SHIFT))

    #define T1_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define T1_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define T1_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define T1_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define T1_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define T1_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_T1_H */


/* [] END OF FILE */
