/**
 * \file IfxGtm_Tim.h
 * \brief GTM  basic functionality
 * \ingroup IfxLld_Gtm
 *
 * \version iLLD_1_0_1_12_0
 * \copyright Copyright (c) 2019 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 * Use of this file is subject to the terms of use agreed between (i) you or
 * the company in which ordinary course of business you are acting and (ii)
 * Infineon Technologies AG or its licensees. If and as long as no such terms
 * of use are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 *
 *
 * \defgroup IfxLld_Gtm_Std_Tim Tim Basic Functionality
 * \ingroup IfxLld_Gtm_Std
 * \defgroup IfxLld_Gtm_Std_Tim_Enumerations TIM Enumerations
 * \ingroup IfxLld_Gtm_Std_Tim
 * \defgroup IfxLld_Gtm_Std_Tim_Channel_Functions TIM Channel Functions
 * \ingroup IfxLld_Gtm_Std_Tim
 */

#ifndef IFXGTM_TIM_H
#define IFXGTM_TIM_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "_Impl/IfxGtm_cfg.h"
#include "Src/Std/IfxSrc.h"
#include "IfxGtm.h"
#include "IfxGtm_Cmu.h"
#include "IfxGtm_bf.h"
#include "Cpu/Std/IfxCpu_Intrinsics.h"

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Gtm_Std_Tim_Enumerations
 * \{ */
typedef enum
{
    IfxGtm_Tim_CntsSel_cntReg = 0,
    IfxGtm_Tim_CntsSel_tbuTs0
} IfxGtm_Tim_CntsSel;

/** \brief Enum for Filter counter
 */
typedef enum
{
    IfxGtm_Tim_FilterCounter_upDown = 0,
    IfxGtm_Tim_FilterCounter_hold
} IfxGtm_Tim_FilterCounter;

/** \brief Enum for Filter counter Frequency Selection
 */
typedef enum
{
    IfxGtm_Tim_FilterCounterFreqSel_cmuClk0 = 0,  /**< \brief FLT_CNT counts with CMU_CLK0 */
    IfxGtm_Tim_FilterCounterFreqSel_cmuClk1 = 1,  /**< \brief FLT_CNT counts with CMU_CLK1 */
    IfxGtm_Tim_FilterCounterFreqSel_cmuClk6 = 2,  /**< \brief FLT_CNT counts with CMU_CLK6 */
    IfxGtm_Tim_FilterCounterFreqSel_cmuClk7 = 3   /**< \brief FLT_CNT counts with CMU_CLK7 */
} IfxGtm_Tim_FilterCounterFreqSel;

/** \brief Enum for Filter mode
 */
typedef enum
{
    IfxGtm_Tim_FilterMode_immediateEdgePropagation = 0,  /**< \brief Immediate edge Propagation mode */
    IfxGtm_Tim_FilterMode_individualDeglitchTime         /**< \brief Individual deglitch mode */
} IfxGtm_Tim_FilterMode;

typedef enum
{
    IfxGtm_Tim_GprSel_tbuTs0 = 0,
    IfxGtm_Tim_GprSel_tbuTs1,
    IfxGtm_Tim_GprSel_tbuTs2,
    IfxGtm_Tim_GprSel_cnts
} IfxGtm_Tim_GprSel;

typedef enum
{
    IfxGtm_Tim_Input_currentChannel = 0,
    IfxGtm_Tim_Input_adjacentChannel
} IfxGtm_Tim_Input;

typedef enum
{
    IfxGtm_Tim_IrqMode_level = 0,        /**< \brief Level Mode */
    IfxGtm_Tim_IrqMode_pulse,            /**< \brief Pulse Mode */
    IfxGtm_Tim_IrqMode_pulseNotify,      /**< \brief pulse notify Mode */
    IfxGtm_Tim_IrqMode_singlePulseMode,  /**< \brief Single Pulse Mode */
    IfxGtm_Tim_IrqMode_none = -1         /**< \brief none */
} IfxGtm_Tim_IrqMode;

typedef enum
{
    IfxGtm_Tim_IrqType_newVal        = 0,  /**< \brief New measurement value detected by SMU of channel */
    IfxGtm_Tim_IrqType_ecntOverflow  = 1,  /**< \brief ECNT counter overflow of channel */
    IfxGtm_Tim_IrqType_cntOverflow   = 2,  /**< \brief CNT counter overflow of channel */
    IfxGtm_Tim_IrqType_gprOverflow   = 3,  /**< \brief GPR0 and GPR1 data overflow */
    IfxGtm_Tim_IrqType_timeoutDetect = 4,  /**< \brief Time out reached for input signal of channel */
    IfxGtm_Tim_IrqType_glitchDetect  = 5   /**< \brief A glitch was detected by the TIM filter of channel */
} IfxGtm_Tim_IrqType;

typedef enum
{
    IfxGtm_Tim_Mode_pwmMeasurement = 0,  /**< \brief TPWM */
    IfxGtm_Tim_Mode_pulseIntegration,    /**< \brief TPIM */
    IfxGtm_Tim_Mode_inputEvent,          /**< \brief TIEM */
    IfxGtm_Tim_Mode_inputPrescaler,      /**< \brief TIPM */
    IfxGtm_Tim_Mode_bitCompression       /**< \brief TBCM */
} IfxGtm_Tim_Mode;

/** \brief Enum for Timeout control
 */
typedef enum
{
    IfxGtm_Tim_Timeout_disabled,     /**< \brief Timeout feature disabled */
    IfxGtm_Tim_Timeout_risingEdge,   /**< \brief Timeout feature enabled for rising edge only */
    IfxGtm_Tim_Timeout_fallingEdge,  /**< \brief Timeout feature enabled for falling edge only */
    IfxGtm_Tim_Timeout_bothEdge      /**< \brief Timeout feature enabled for both edges */
} IfxGtm_Tim_Timeout;

/** \} */

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/** \brief Channel control
 */
typedef struct
{
    boolean         enable;                                             /**< \brief TIM channel enable */
    IfxGtm_Tim_Mode mode;                                               /**< \brief TIM channel Mode */
    boolean         enableOneShotMode;                                  /**< \brief enable OneShot Mode (disable - continous operation mode) */
    boolean         enableAruRouting;                                   /**< \brief GPR0 and GPR1 register values routed to ARU.
                                                                         * 0- Registers content not routed.
                                                                         * 1- Registers content routed */
    boolean            channelInputControl;                             /**< \brief 0- use signal TIM_IN(x) as input for channel .
                                                                         * 1- use signal TIM_IN(x-1) as input for channel x (or TIM_IN(m-1) if x is 0) */
    IfxGtm_Tim_GprSel  gpr0Sel;                                         /**< \brief Selection for GPR0 register */
    IfxGtm_Tim_GprSel  gpr1Sel;                                         /**< \brief Selection for GPR1 register */
    IfxGtm_Tim_CntsSel cntsSel;                                         /**< \brief Selection for CNTS register */
    boolean            signalLevelControl;                              /**< \brief Signal level control
                                                                         * 0- Measurement starts with falling edge (low level measurement).
                                                                         * 1- Measurement starts with rising edge (high level measurement)
                                                                         * In TIM_MODE=0b110 (TSSM) the bit field DSL defines the shift direction.
                                                                         * 0- Shift left
                                                                         * 1- Shift right */
    boolean ignoreSignalLevel;                                          /**< \brief ignore Signal Level.
                                                                         * 0- use DSL bit for selecting active signal level (TIEM).
                                                                         * 1- ignore DSL and treat both edges as active edge (TIEM). */
    boolean enableCounterReset;                                         /**< \brief Enables resetting of counter in certain modes ( TIM_MODE=0b101 (TGPS) / TIM_MODE=0b000 (TPWM))
                                                                         * 0- ECNT counter operating in wrap around mode / ECNT counter operating in wrap around mode, CNT is reset on active input edge defined by DSL
                                                                         * 1 - ECNT counter is reset with periodic sampling / ECNT counter operating in wrap around mode, CNT is reset on active and inactive input edge else ECNT counter operating in wrap around mode;
                                                                         * In TIM_MODE=0b110 (TSSM) the bit field ECNT_RESET defines the initial polarity for the shift register. */
    boolean                         enableFilter;                       /**< \brief enable Filter */
    IfxGtm_Tim_FilterCounterFreqSel filterCounterFrequency;             /**< \brief Filter counter frequency select */
    boolean                         enableExternalCaptureMode;          /**< \brief Enables external capture mode */
    IfxGtm_Tim_FilterMode           filterModeRisingEdge;               /**< \brief Filter mode for rising edge */
    IfxGtm_Tim_FilterCounter        filterCounterModeRisingEdge;        /**< \brief Filter counter mode for rising edge */
    IfxGtm_Tim_FilterMode           filterModeFallingEdge;              /**< \brief Filter mode for falling edge */
    IfxGtm_Tim_FilterCounter        filterCounterModeFallingEdge;       /**< \brief Filter counter mode for falling edge */
    IfxGtm_Cmu_Clk                  clkSel;                             /**< \brief CMU clock source select for channel */
    boolean                         extendEdgeCounterOverflow;          /**< \brief Extended Edge counter overflow behavior
                                                                         * 0- Overflow will be signaled on ECNT bit width = 8
                                                                         * 1- Overflow will be signaled on EECNT bit width (full range) */
    boolean            egpr0Sel;                                        /**< \brief Extension of GPR0_SEL bit field */
    boolean            egpr1Sel;                                        /**< \brief Extension of GPR1_SEL bit field */
    IfxGtm_Tim_Timeout timeoutControl;                                  /**< \brief Timeout control */
} IfxGtm_Tim_ChannelControl;

typedef struct
{
    uint8 mode;        /**< \brief Input source to Channel. multi-core encoding in use (MODE_x(1) defines the state of the signal)
                        * 00- State is 0 (ignore write access)
                        * 01- Change state to 0
                        * 10- Change state to 1
                        * 11- State is 1 (ignore write access) */
    uint8 value;
} IfxGtm_Tim_InputSourceSelect;

/** \addtogroup IfxLld_Gtm_Std_Tim_Channel_Functions
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief This function clears the Aux input Source selection for the  given channel
 * \param gtm Pointer to GTM module
 * \param timIndex TIM instance number
 * \param channel Channel index
 * \return None
 */
IFX_INLINE void IfxGtm_Tim_Ch_clearAuxInputSourceSelection(Ifx_GTM *gtm, IfxGtm_Tim timIndex, IfxGtm_Tim_Ch channel);

/** \brief Clears the counter overflow flag
 * \param channel TIM channel pointer
 * \return None
 */
IFX_INLINE void IfxGtm_Tim_Ch_clearCntOverflowEvent(Ifx_GTM_TIM_CH *channel);

/** \brief Clears the data lost flag
 * \param channel TIM channel pointer
 * \return None
 */
IFX_INLINE void IfxGtm_Tim_Ch_clearDataLostEvent(Ifx_GTM_TIM_CH *channel);

/** \brief Clears the event counter overflow flag
 * \param channel TIM channel pointer
 * \return None
 */
IFX_INLINE void IfxGtm_Tim_Ch_clearEcntOverflowEvent(Ifx_GTM_TIM_CH *channel);

/** \brief Clears the glitch flag
 * \param channel TIM channel pointer
 * \return None
 */
IFX_INLINE void IfxGtm_Tim_Ch_clearGlitchEvent(Ifx_GTM_TIM_CH *channel);

/** \brief Clears the new value flag
 * \param channel TIM channel pointer
 * \return None
 */
IFX_INLINE void IfxGtm_Tim_Ch_clearNewValueEvent(Ifx_GTM_TIM_CH *channel);

/** \brief Clear the interrupt notification.
 * \param channel TIM channel pointer
 * \param irqType Interrupt type
 * \return None
 */
IFX_INLINE void IfxGtm_Tim_Ch_clearNotification(Ifx_GTM_TIM_CH *channel, IfxGtm_Tim_IrqType irqType);

/** \brief Returns the status of channel  notification
 * \param channel TIM channel pointer
 * \param irqType Interrupt type
 * \return Status of channel notification
 */
IFX_INLINE boolean IfxGtm_Tim_Ch_getNotification(Ifx_GTM_TIM_CH *channel, IfxGtm_Tim_IrqType irqType);

/** \brief Returns a pointer to the TIM channel SRC
 * \param gtm Pointer to GTM module
 * \param tim Specifies the tim module no
 * \param channel Channel index
 * \return Pointer to the TIM channel SRC
 */
IFX_INLINE volatile Ifx_SRC_SRCR *IfxGtm_Tim_Ch_getSrcPointer(Ifx_GTM *gtm, IfxGtm_Tim tim, IfxGtm_Tim_Ch channel);

/** \brief Test the counter overflow flag
 * \param channel TIM channel pointer
 * \return TRUE if the flag is set, else FALSE
 */
IFX_INLINE boolean IfxGtm_Tim_Ch_isCntOverflowEvent(Ifx_GTM_TIM_CH *channel);

/** \brief Test the data lost flag
 * \param channel TIM channel pointer
 * \return TRUE if the flag is set, else FALSE
 */
IFX_INLINE boolean IfxGtm_Tim_Ch_isDataLostEvent(Ifx_GTM_TIM_CH *channel);

/** \brief Test the event counter overflow flag
 * \param channel TIM channel pointer
 * \return TRUE if the flag is set, else FALSE
 */
IFX_INLINE boolean IfxGtm_Tim_Ch_isEcntOverflowEvent(Ifx_GTM_TIM_CH *channel);

/** \brief Test the glitch flag
 * \param channel TIM channel pointer
 * \return TRUE if the flag is set, else FALSE
 */
IFX_INLINE boolean IfxGtm_Tim_Ch_isGlitchEvent(Ifx_GTM_TIM_CH *channel);

/** \brief Test the new value flag
 * \param channel TIM channel pointer
 * \return TRUE if the flag is set, else FALSE
 */
IFX_INLINE boolean IfxGtm_Tim_Ch_isNewValueEvent(Ifx_GTM_TIM_CH *channel);

/** \brief set the Auxilary input source selection of a particular channel.
 * \param gtm Pointer to GTM module
 * \param timIndex TIM instance number
 * \param channel Channel index
 * \return None
 */
IFX_INLINE void IfxGtm_Tim_Ch_setAuxInputSourceSelection(Ifx_GTM *gtm, IfxGtm_Tim timIndex, IfxGtm_Tim_Ch channel);

/** \brief This function configures the Edge counter register.
 * \param channel TIM channel pointer
 * \param edgeCounter Edge counter value
 * \return None
 */
IFX_INLINE void IfxGtm_Tim_Ch_setEdgeCounter(Ifx_GTM_TIM_CH *channel, uint8 edgeCounter);

/** \brief This function configures the Falling edge Filter Parameter.
 * \param channel TIM channel pointer
 * \param filterTime Falling edge Filter Parameter.
 * \return None
 */
IFX_INLINE void IfxGtm_Tim_Ch_setFallingEdgeFilterTime(Ifx_GTM_TIM_CH *channel, uint32 filterTime);

/** \brief This function configures the Input source selection register.
 * \param tim TIM instance number
 * \param channel Channel index
 * \param inputSource Input source to Channel
 * \return None
 */
IFX_INLINE void IfxGtm_Tim_Ch_setInputSourceSelection(Ifx_GTM_TIM *tim, IfxGtm_Tim_Ch channel, IfxGtm_Tim_InputSourceSelect inputSource);

/** \brief set the Interrupt Notification
 * \param channel TIM channel pointer
 * \param irqType Interrupt type
 * \return None
 */
IFX_INLINE void IfxGtm_Tim_Ch_setNotification(Ifx_GTM_TIM_CH *channel, IfxGtm_Tim_IrqType irqType);

/** \brief This function configures theRaising edge Filter Parameter.
 * \param channel TIM channel pointer
 * \param filterTime Raising edge Filter Parameter.
 * \return None
 */
IFX_INLINE void IfxGtm_Tim_Ch_setRisingEdgeFilterTime(Ifx_GTM_TIM_CH *channel, uint32 filterTime);

/** \brief This function configures the Shadow counter register.
 * \param channel TIM channel pointer
 * \param shadowCounter Shadow counter value
 * \return None
 */
IFX_INLINE void IfxGtm_Tim_Ch_setShadowCounter(Ifx_GTM_TIM_CH *channel, uint32 shadowCounter);

/** \brief Returns the pointer to the TIM channel
 * \param tim Pointer to Tim base
 * \param channel TIM channel
 * \return Pointer to TIM channel base
 */
IFX_INLINE Ifx_GTM_TIM_CH *IfxGtm_Tim_getChannel(Ifx_GTM_TIM *tim, IfxGtm_Tim_Ch channel);

/** \brief Reset the specified TIM channel
 * \param tim Pointer to GTM TIM instance
 * \param channel Channel index
 * \return None
 */
IFX_INLINE void IfxGtm_Tim_Ch_resetChannel(Ifx_GTM_TIM *tim, IfxGtm_Tim_Ch channel);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Returns the Capture Clock Frequency
 * \param gtm Pointer to GTM module
 * \param channel Pointer to TIM channel base
 * \return Capture clock frequency
 */
IFX_EXTERN float32 IfxGtm_Tim_Ch_getCaptureClockFrequency(Ifx_GTM *gtm, Ifx_GTM_TIM_CH *channel);

/** \brief Returns the capture clock source selected
 * \param channel TIM channel pointer
 * \return capture clock source
 */
IFX_EXTERN IfxGtm_Cmu_Clk IfxGtm_Tim_Ch_getCaptureClockSource(Ifx_GTM_TIM_CH *channel);

/** \brief Returns the Filter Clock Frequency
 * \param gtm Pointer to GTM module
 * \param channel Pointer to TIM channel base
 * \return Filter clock frequency
 */
IFX_EXTERN float32 IfxGtm_Tim_Ch_getFilterClockFrequency(Ifx_GTM *gtm, Ifx_GTM_TIM_CH *channel);

/** \brief Returns the Filter clock source selected
 * \param channel TIM channel pointer
 * \return Filter clock source
 */
IFX_EXTERN IfxGtm_Cmu_Tim_Filter_Clk IfxGtm_Tim_Ch_getFilterClockSource(Ifx_GTM_TIM_CH *channel);

/** \brief Returns the Timeout Clock Frequency
 * \param gtm Pointer to GTM module
 * \param channel Pointer to TIM channel base
 * \return Timeout clock frequency
 */
IFX_EXTERN float32 IfxGtm_Tim_Ch_getTimeoutClockFrequency(Ifx_GTM *gtm, Ifx_GTM_TIM_CH *channel);

/** \brief Returns the Timeout clock source selected
 * \param channel TIM channel pointer
 * \return Timeout clock source
 */
IFX_EXTERN IfxGtm_Cmu_Clk IfxGtm_Tim_Ch_getTimeoutClockSource(Ifx_GTM_TIM_CH *channel);

/** \brief Set the channel notification
 * \param channel TIM channel pointer
 * \param irqOnNewVal If TRUE, the interrupt on new value is enabled
 * \param irqOnCntOverflow If TRUE, the interrupt on CNT overflow is enabled
 * \param irqOnEcntOverflow If TRUE, the interrupt on ECNT overflow is enabled
 * \param irqOnDatalost If TRUE, the interrupt on data lost (GPR0, GPR1) is enabled
 * \return None
 */
IFX_EXTERN void IfxGtm_Tim_Ch_setChannelNotification(Ifx_GTM_TIM_CH *channel, boolean irqOnNewVal, boolean irqOnCntOverflow, boolean irqOnEcntOverflow, boolean irqOnDatalost);

/** \brief Set the channel clock source
 * \param channel TIM channel pointer
 * \param clock Selected clock
 * \return None
 */
IFX_EXTERN void IfxGtm_Tim_Ch_setClockSource(Ifx_GTM_TIM_CH *channel, IfxGtm_Cmu_Clk clock);

/** \brief This function configures the TIM channel Control register
 * \param channel TIM channel pointer
 * \param control channel control configuration
 * \return None
 */
IFX_EXTERN void IfxGtm_Tim_Ch_setControl(Ifx_GTM_TIM_CH *channel, IfxGtm_Tim_ChannelControl control);

/** \brief Set the filter notification
 * \param channel TIM channel pointer
 * \param irqOnGlitch If TRUE, the interrupt on glitch is enabled
 * \return None
 */
IFX_EXTERN void IfxGtm_Tim_Ch_setFilterNotification(Ifx_GTM_TIM_CH *channel, boolean irqOnGlitch);

/** \brief This function configures the TIM channel IRQ mode
 * \param channel TIM channel pointer
 * \param mode Notification Mode
 * \return None
 */
IFX_EXTERN void IfxGtm_Tim_Ch_setNotificationMode(Ifx_GTM_TIM_CH *channel, IfxGtm_IrqMode mode);

/** \brief Set the timeout notification
 * \param channel TIM channel pointer
 * \param irqOnTimeout If TRUE, the interrupt on timeout is enabled
 * \return None
 */
IFX_EXTERN void IfxGtm_Tim_Ch_setTimeoutNotification(Ifx_GTM_TIM_CH *channel, boolean irqOnTimeout);

/** \} */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief sets the TIMINSEL register with the required mux setting
 * \param timIndex Index of TIM module
 * \param channelIndex index of TIM channel
 * \param tinSel MUX value selection
 * \return None
 */
IFX_INLINE void IfxGtm_Tim_Ch_setTimTin(IfxGtm_Tim timIndex, IfxGtm_Tim_Ch channelIndex, uint32 tinSel);

/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/

IFX_INLINE void IfxGtm_Tim_Ch_clearAuxInputSourceSelection(Ifx_GTM *gtm, IfxGtm_Tim timIndex, IfxGtm_Tim_Ch channel)
{
    Ifx_GTM_AUX_IN_SRC src;
    src.TIM[timIndex].U             = gtm->AUX_IN_SRC.TIM[timIndex].U;
    src.TIM[timIndex].U            &= ~(1 << (uint8)channel);
    gtm->AUX_IN_SRC.TIM[timIndex].U = src.TIM[timIndex].U;
}


IFX_INLINE void IfxGtm_Tim_Ch_clearCntOverflowEvent(Ifx_GTM_TIM_CH *channel)
{
    channel->IRQ.NOTIFY.U = 0x1 << IFX_GTM_TIM_CH_IRQ_NOTIFY_CNTOFL_OFF;
}


IFX_INLINE void IfxGtm_Tim_Ch_clearDataLostEvent(Ifx_GTM_TIM_CH *channel)
{
    channel->IRQ.NOTIFY.U = 0x1 << IFX_GTM_TIM_CH_IRQ_NOTIFY_GPROFL_OFF;
}


IFX_INLINE void IfxGtm_Tim_Ch_clearEcntOverflowEvent(Ifx_GTM_TIM_CH *channel)
{
    channel->IRQ.NOTIFY.U = 0x1 << IFX_GTM_TIM_CH_IRQ_NOTIFY_ECNTOFL_OFF;
}


IFX_INLINE void IfxGtm_Tim_Ch_clearGlitchEvent(Ifx_GTM_TIM_CH *channel)
{
    channel->IRQ.NOTIFY.U = 0x1 << IFX_GTM_TIM_CH_IRQ_NOTIFY_GLITCHDET_OFF;
}


IFX_INLINE void IfxGtm_Tim_Ch_clearNewValueEvent(Ifx_GTM_TIM_CH *channel)
{
    channel->IRQ.NOTIFY.U = 0x1 << IFX_GTM_TIM_CH_IRQ_NOTIFY_NEWVAL_OFF;
}


IFX_INLINE void IfxGtm_Tim_Ch_clearNotification(Ifx_GTM_TIM_CH *channel, IfxGtm_Tim_IrqType irqType)
{
    channel->IRQ.EN.U    &= ~(1 << irqType);
    channel->IRQ.NOTIFY.U = (1 << irqType);
}


IFX_INLINE boolean IfxGtm_Tim_Ch_getNotification(Ifx_GTM_TIM_CH *channel, IfxGtm_Tim_IrqType irqType)
{
    boolean result;
    result = ((channel->IRQ.NOTIFY.U >> irqType) & 0x1);
    return result;
}


IFX_INLINE volatile Ifx_SRC_SRCR *IfxGtm_Tim_Ch_getSrcPointer(Ifx_GTM *gtm, IfxGtm_Tim tim, IfxGtm_Tim_Ch channel)
{
    IFX_UNUSED_PARAMETER(gtm)
    return &MODULE_SRC.GTM_TIM[tim][channel];
}


IFX_INLINE boolean IfxGtm_Tim_Ch_isCntOverflowEvent(Ifx_GTM_TIM_CH *channel)
{
    return channel->IRQ.NOTIFY.B.CNTOFL == 1;
}


IFX_INLINE boolean IfxGtm_Tim_Ch_isDataLostEvent(Ifx_GTM_TIM_CH *channel)
{
    return channel->IRQ.NOTIFY.B.GPROFL == 1;
}


IFX_INLINE boolean IfxGtm_Tim_Ch_isEcntOverflowEvent(Ifx_GTM_TIM_CH *channel)
{
    return channel->IRQ.NOTIFY.B.ECNTOFL == 1;
}


IFX_INLINE boolean IfxGtm_Tim_Ch_isGlitchEvent(Ifx_GTM_TIM_CH *channel)
{
    return channel->IRQ.NOTIFY.B.GLITCHDET == 1;
}


IFX_INLINE boolean IfxGtm_Tim_Ch_isNewValueEvent(Ifx_GTM_TIM_CH *channel)
{
    return channel->IRQ.NOTIFY.B.NEWVAL == 1;
}


IFX_INLINE void IfxGtm_Tim_Ch_setAuxInputSourceSelection(Ifx_GTM *gtm, IfxGtm_Tim timIndex, IfxGtm_Tim_Ch channel)
{
    Ifx_GTM_AUX_IN_SRC src;
    src.TIM[timIndex].U             = gtm->AUX_IN_SRC.TIM[timIndex].U;
    src.TIM[timIndex].U            |= (1 << (uint8)channel);
    gtm->AUX_IN_SRC.TIM[timIndex].U = src.TIM[timIndex].U;
}


IFX_INLINE void IfxGtm_Tim_Ch_setEdgeCounter(Ifx_GTM_TIM_CH *channel, uint8 edgeCounter)
{
    channel->CNTS.B.ECNT = edgeCounter;
}


IFX_INLINE void IfxGtm_Tim_Ch_setFallingEdgeFilterTime(Ifx_GTM_TIM_CH *channel, uint32 filterTime)
{
    channel->FLT_FE.B.FLT_FE = filterTime;
}


IFX_INLINE void IfxGtm_Tim_Ch_setInputSourceSelection(Ifx_GTM_TIM *tim, IfxGtm_Tim_Ch channel, IfxGtm_Tim_InputSourceSelect inputSource)
{
    uint8 bitPos = 1U << ((uint8)channel);

    __imaskldmst((void *)&tim->IN_SRC.U, inputSource.mode, bitPos, 2);
    __imaskldmst((void *)&tim->IN_SRC.U, inputSource.value, (bitPos + 2), 2);
}


IFX_INLINE void IfxGtm_Tim_Ch_setNotification(Ifx_GTM_TIM_CH *channel, IfxGtm_Tim_IrqType irqType)
{
    channel->IRQ.EN.U     |= 1 << irqType;
    channel->IRQ.NOTIFY.U |= 1 << irqType;
}


IFX_INLINE void IfxGtm_Tim_Ch_setRisingEdgeFilterTime(Ifx_GTM_TIM_CH *channel, uint32 filterTime)
{
    channel->FLT_RE.B.FLT_RE = filterTime;
}


IFX_INLINE void IfxGtm_Tim_Ch_setShadowCounter(Ifx_GTM_TIM_CH *channel, uint32 shadowCounter)
{
    channel->CNTS.B.CNTS = shadowCounter;
}


IFX_INLINE Ifx_GTM_TIM_CH *IfxGtm_Tim_getChannel(Ifx_GTM_TIM *tim, IfxGtm_Tim_Ch channel)
{
    return (Ifx_GTM_TIM_CH *)((uint32)&tim->CH0.GPR0.U + ((uint32)&tim->CH1 - (uint32)&tim->CH0) * channel);
}


IFX_INLINE void IfxGtm_Tim_Ch_resetChannel(Ifx_GTM_TIM *tim, IfxGtm_Tim_Ch channel)
{
    tim->RST.U |= (uint32)1 << (uint32)channel;
}


IFX_INLINE void IfxGtm_Tim_Ch_setTimTin(IfxGtm_Tim timIndex, IfxGtm_Tim_Ch channelIndex, uint32 tinSel)
{
    uint32 shift = channelIndex * 4;

    __ldmst_c(&(MODULE_GTM.TIMINSEL[timIndex].U), (0xFU << shift), (tinSel) << shift);
}


#endif /* IFXGTM_TIM_H */
