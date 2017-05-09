/*******************************************************************************
* File Name: T2.h
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

#if !defined(CY_Timer_v2_60_T2_H)
#define CY_Timer_v2_60_T2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 T2_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define T2_Resolution                 8u
#define T2_UsingFixedFunction         0u
#define T2_UsingHWCaptureCounter      0u
#define T2_SoftwareCaptureMode        0u
#define T2_SoftwareTriggerMode        0u
#define T2_UsingHWEnable              0u
#define T2_EnableTriggerMode          1u
#define T2_InterruptOnCaptureCount    0u
#define T2_RunModeUsed                0u
#define T2_ControlRegRemoved          0u

#if defined(T2_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define T2_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (T2_UsingFixedFunction)
    #define T2_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define T2_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End T2_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!T2_UsingFixedFunction)

        uint8 TimerUdb;
        uint8 InterruptMaskValue;
        #if (T2_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!T2_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}T2_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    T2_Start(void) ;
void    T2_Stop(void) ;

void    T2_SetInterruptMode(uint8 interruptMode) ;
uint8   T2_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define T2_GetInterruptSource() T2_ReadStatusRegister()

#if(!T2_UDB_CONTROL_REG_REMOVED)
    uint8   T2_ReadControlRegister(void) ;
    void    T2_WriteControlRegister(uint8 control) ;
#endif /* (!T2_UDB_CONTROL_REG_REMOVED) */

uint8  T2_ReadPeriod(void) ;
void    T2_WritePeriod(uint8 period) ;
uint8  T2_ReadCounter(void) ;
void    T2_WriteCounter(uint8 counter) ;
uint8  T2_ReadCapture(void) ;
void    T2_SoftwareCapture(void) ;

#if(!T2_UsingFixedFunction) /* UDB Prototypes */
    #if (T2_SoftwareCaptureMode)
        void    T2_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!T2_UsingFixedFunction) */

    #if (T2_SoftwareTriggerMode)
        void    T2_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (T2_SoftwareTriggerMode) */

    #if (T2_EnableTriggerMode)
        void    T2_EnableTrigger(void) ;
        void    T2_DisableTrigger(void) ;
    #endif /* (T2_EnableTriggerMode) */


    #if(T2_InterruptOnCaptureCount)
        void    T2_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (T2_InterruptOnCaptureCount) */

    #if (T2_UsingHWCaptureCounter)
        void    T2_SetCaptureCount(uint8 captureCount) ;
        uint8   T2_ReadCaptureCount(void) ;
    #endif /* (T2_UsingHWCaptureCounter) */

    void T2_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void T2_Init(void)          ;
void T2_Enable(void)        ;
void T2_SaveConfig(void)    ;
void T2_RestoreConfig(void) ;
void T2_Sleep(void)         ;
void T2_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define T2__B_TIMER__CM_NONE 0
#define T2__B_TIMER__CM_RISINGEDGE 1
#define T2__B_TIMER__CM_FALLINGEDGE 2
#define T2__B_TIMER__CM_EITHEREDGE 3
#define T2__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define T2__B_TIMER__TM_NONE 0x00u
#define T2__B_TIMER__TM_RISINGEDGE 0x04u
#define T2__B_TIMER__TM_FALLINGEDGE 0x08u
#define T2__B_TIMER__TM_EITHEREDGE 0x0Cu
#define T2__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define T2_INIT_PERIOD             99u
#define T2_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << T2_CTRL_CAP_MODE_SHIFT))
#define T2_INIT_TRIGGER_MODE       ((uint8)((uint8)1u << T2_CTRL_TRIG_MODE_SHIFT))
#if (T2_UsingFixedFunction)
    #define T2_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << T2_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << T2_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define T2_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << T2_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << T2_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << T2_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (T2_UsingFixedFunction) */
#define T2_INIT_CAPTURE_COUNT      (2u)
#define T2_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << T2_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (T2_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define T2_STATUS         (*(reg8 *) T2_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define T2_STATUS_MASK    (*(reg8 *) T2_TimerHW__SR0 )
    #define T2_CONTROL        (*(reg8 *) T2_TimerHW__CFG0)
    #define T2_CONTROL2       (*(reg8 *) T2_TimerHW__CFG1)
    #define T2_CONTROL2_PTR   ( (reg8 *) T2_TimerHW__CFG1)
    #define T2_RT1            (*(reg8 *) T2_TimerHW__RT1)
    #define T2_RT1_PTR        ( (reg8 *) T2_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define T2_CONTROL3       (*(reg8 *) T2_TimerHW__CFG2)
        #define T2_CONTROL3_PTR   ( (reg8 *) T2_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define T2_GLOBAL_ENABLE  (*(reg8 *) T2_TimerHW__PM_ACT_CFG)
    #define T2_GLOBAL_STBY_ENABLE  (*(reg8 *) T2_TimerHW__PM_STBY_CFG)

    #define T2_CAPTURE_LSB         (* (reg16 *) T2_TimerHW__CAP0 )
    #define T2_CAPTURE_LSB_PTR       ((reg16 *) T2_TimerHW__CAP0 )
    #define T2_PERIOD_LSB          (* (reg16 *) T2_TimerHW__PER0 )
    #define T2_PERIOD_LSB_PTR        ((reg16 *) T2_TimerHW__PER0 )
    #define T2_COUNTER_LSB         (* (reg16 *) T2_TimerHW__CNT_CMP0 )
    #define T2_COUNTER_LSB_PTR       ((reg16 *) T2_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define T2_BLOCK_EN_MASK                     T2_TimerHW__PM_ACT_MSK
    #define T2_BLOCK_STBY_EN_MASK                T2_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define T2_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define T2_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define T2_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define T2_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define T2_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define T2_CTRL_ENABLE                        ((uint8)((uint8)0x01u << T2_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define T2_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define T2_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << T2_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define T2_CTRL_MODE_SHIFT                 0x01u
        #define T2_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << T2_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define T2_CTRL_RCOD_SHIFT        0x02u
        #define T2_CTRL_ENBL_SHIFT        0x00u
        #define T2_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define T2_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << T2_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define T2_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << T2_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define T2_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << T2_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define T2_CTRL_RCOD       ((uint8)((uint8)0x03u << T2_CTRL_RCOD_SHIFT))
        #define T2_CTRL_ENBL       ((uint8)((uint8)0x80u << T2_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define T2_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define T2_RT1_MASK                        ((uint8)((uint8)0x03u << T2_RT1_SHIFT))
    #define T2_SYNC                            ((uint8)((uint8)0x03u << T2_RT1_SHIFT))
    #define T2_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define T2_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << T2_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define T2_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << T2_SYNCDSI_SHIFT))

    #define T2_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << T2_CTRL_MODE_SHIFT))
    #define T2_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << T2_CTRL_MODE_SHIFT))
    #define T2_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << T2_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define T2_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define T2_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define T2_STATUS_TC_INT_MASK_SHIFT        (T2_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define T2_STATUS_CAPTURE_INT_MASK_SHIFT   (T2_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define T2_STATUS_TC                       ((uint8)((uint8)0x01u << T2_STATUS_TC_SHIFT))
    #define T2_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << T2_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define T2_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << T2_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define T2_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << T2_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define T2_STATUS              (* (reg8 *) T2_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define T2_STATUS_MASK         (* (reg8 *) T2_TimerUDB_rstSts_stsreg__MASK_REG)
    #define T2_STATUS_AUX_CTRL     (* (reg8 *) T2_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define T2_CONTROL             (* (reg8 *) T2_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(T2_Resolution <= 8u) /* 8-bit Timer */
        #define T2_CAPTURE_LSB         (* (reg8 *) T2_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define T2_CAPTURE_LSB_PTR       ((reg8 *) T2_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define T2_PERIOD_LSB          (* (reg8 *) T2_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define T2_PERIOD_LSB_PTR        ((reg8 *) T2_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define T2_COUNTER_LSB         (* (reg8 *) T2_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define T2_COUNTER_LSB_PTR       ((reg8 *) T2_TimerUDB_sT8_timerdp_u0__A0_REG )
    #elif(T2_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define T2_CAPTURE_LSB         (* (reg16 *) T2_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define T2_CAPTURE_LSB_PTR       ((reg16 *) T2_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define T2_PERIOD_LSB          (* (reg16 *) T2_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define T2_PERIOD_LSB_PTR        ((reg16 *) T2_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define T2_COUNTER_LSB         (* (reg16 *) T2_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define T2_COUNTER_LSB_PTR       ((reg16 *) T2_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define T2_CAPTURE_LSB         (* (reg16 *) T2_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define T2_CAPTURE_LSB_PTR       ((reg16 *) T2_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define T2_PERIOD_LSB          (* (reg16 *) T2_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define T2_PERIOD_LSB_PTR        ((reg16 *) T2_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define T2_COUNTER_LSB         (* (reg16 *) T2_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
            #define T2_COUNTER_LSB_PTR       ((reg16 *) T2_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(T2_Resolution <= 24u)/* 24-bit Timer */
        #define T2_CAPTURE_LSB         (* (reg32 *) T2_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define T2_CAPTURE_LSB_PTR       ((reg32 *) T2_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define T2_PERIOD_LSB          (* (reg32 *) T2_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define T2_PERIOD_LSB_PTR        ((reg32 *) T2_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define T2_COUNTER_LSB         (* (reg32 *) T2_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define T2_COUNTER_LSB_PTR       ((reg32 *) T2_TimerUDB_sT8_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define T2_CAPTURE_LSB         (* (reg32 *) T2_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define T2_CAPTURE_LSB_PTR       ((reg32 *) T2_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define T2_PERIOD_LSB          (* (reg32 *) T2_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define T2_PERIOD_LSB_PTR        ((reg32 *) T2_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define T2_COUNTER_LSB         (* (reg32 *) T2_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define T2_COUNTER_LSB_PTR       ((reg32 *) T2_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define T2_CAPTURE_LSB         (* (reg32 *) T2_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define T2_CAPTURE_LSB_PTR       ((reg32 *) T2_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define T2_PERIOD_LSB          (* (reg32 *) T2_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define T2_PERIOD_LSB_PTR        ((reg32 *) T2_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define T2_COUNTER_LSB         (* (reg32 *) T2_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
            #define T2_COUNTER_LSB_PTR       ((reg32 *) T2_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define T2_COUNTER_LSB_PTR_8BIT       ((reg8 *) T2_TimerUDB_sT8_timerdp_u0__A0_REG )
    
    #if (T2_UsingHWCaptureCounter)
        #define T2_CAP_COUNT              (*(reg8 *) T2_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define T2_CAP_COUNT_PTR          ( (reg8 *) T2_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define T2_CAPTURE_COUNT_CTRL     (*(reg8 *) T2_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define T2_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) T2_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (T2_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define T2_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define T2_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define T2_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define T2_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define T2_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define T2_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << T2_CTRL_INTCNT_SHIFT))
    #define T2_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << T2_CTRL_TRIG_MODE_SHIFT))
    #define T2_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << T2_CTRL_TRIG_EN_SHIFT))
    #define T2_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << T2_CTRL_CAP_MODE_SHIFT))
    #define T2_CTRL_ENABLE                    ((uint8)((uint8)0x01u << T2_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define T2_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define T2_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define T2_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define T2_STATUS_TC_INT_MASK_SHIFT       T2_STATUS_TC_SHIFT
    #define T2_STATUS_CAPTURE_INT_MASK_SHIFT  T2_STATUS_CAPTURE_SHIFT
    #define T2_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define T2_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define T2_STATUS_FIFOFULL_INT_MASK_SHIFT T2_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define T2_STATUS_TC                      ((uint8)((uint8)0x01u << T2_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define T2_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << T2_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define T2_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << T2_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define T2_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << T2_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define T2_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << T2_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define T2_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << T2_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define T2_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << T2_STATUS_FIFOFULL_SHIFT))

    #define T2_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define T2_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define T2_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define T2_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define T2_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define T2_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_T2_H */


/* [] END OF FILE */
