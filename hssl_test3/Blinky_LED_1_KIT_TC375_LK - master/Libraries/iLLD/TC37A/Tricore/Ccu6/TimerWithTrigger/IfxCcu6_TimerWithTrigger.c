/**
 * \file IfxCcu6_TimerWithTrigger.c
 * \brief CCU6 TIMERWITHTRIGGER details
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
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxCcu6_TimerWithTrigger.h"
#include "_Utilities/Ifx_Assert.h"
#include "stddef.h"
#include "string.h"

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

boolean IfxCcu6_TimerWithTrigger_acknowledgeTimerIrq(IfxCcu6_TimerWithTrigger *driver)
{
    boolean event;
    event = IfxCcu6_isT12OneNotification(driver->ccu6);

    if (event)
    {
        IfxCcu6_clearT12OneNotification(driver->ccu6);
    }
    else
    {}

    return event;
}


boolean IfxCcu6_TimerWithTrigger_acknowledgeTriggerIrq(IfxCcu6_TimerWithTrigger *driver)
{
    boolean event;
    event = IfxCcu6_isT13CompareNotification(driver->ccu6);

    if (event)
    {
        IfxCcu6_clearT13CompareNotification(driver->ccu6);
    }
    else
    {}

    return event;
}


void IfxCcu6_TimerWithTrigger_applyUpdate(IfxCcu6_TimerWithTrigger *driver)
{
    IfxCcu6_enableShadowTransfer(driver->ccu6, TRUE, TRUE);
}


void IfxCcu6_TimerWithTrigger_disableUpdate(IfxCcu6_TimerWithTrigger *driver)
{
    IFX_UNUSED_PARAMETER(driver)
}


float32 IfxCcu6_TimerWithTrigger_getFrequency(IfxCcu6_TimerWithTrigger *driver)
{
    return 1.0 / IfxStdIf_Timer_tickToS(driver->base.clockFreq, driver->base.period);
}


float32 IfxCcu6_TimerWithTrigger_getInputFrequency(IfxCcu6_TimerWithTrigger *driver)
{
    return driver->base.clockFreq;
}


Ifx_TimerValue IfxCcu6_TimerWithTrigger_getPeriod(IfxCcu6_TimerWithTrigger *driver)
{
    return driver->base.period;
}


volatile uint32 *IfxCcu6_TimerWithTrigger_getPointer(IfxCcu6_TimerWithTrigger *driver)
{
    return IfxCcu6_getT12TimerPointer(driver->ccu6);
}


float32 IfxCcu6_TimerWithTrigger_getResolution(IfxCcu6_TimerWithTrigger *driver)
{
    return 1.0 / driver->base.clockFreq;
}


boolean IfxCcu6_TimerWithTrigger_init(IfxCcu6_TimerWithTrigger *driver, IfxCcu6_TimerWithTrigger_Config *config)
{
    boolean                        result = TRUE;
    IfxCcu6_TimerWithTrigger_Base *base   = &driver->base;
    Ifx_CCU6                      *module;

    driver->ccu6         = config->ccu6;
    module               = driver->ccu6;

    base->triggerEnabled = config->base.trigger.enabled;

    /** - Enable/initialise the CCU6 if it has not been enabled. See IfxCcu6_isModuleEnabled() */
    if (IfxCcu6_isModuleEnabled(module) == FALSE)
    {
        IfxCcu6_enableModule(module);
    }

    /* Initialize the timer part */
    IfxCcu6_setT12CountMode(module, (config->base.countDir == IfxStdIf_Timer_CountDir_upAndDown) ? IfxCcu6_T12CountMode_centerAligned : IfxCcu6_T12CountMode_edgeAligned);

    driver->base.countDir = config->base.countDir;

    uint16  prescaler;
    float32 freqT12 = 0, periodT12;
    float32 freqCC6 = (float32)IfxScuCcu_getSpbFrequency();

    for (prescaler = 0; prescaler < 16; prescaler++)
    {
        freqT12   = freqCC6 / (1U << prescaler);
        periodT12 = freqT12 / config->base.frequency;

        if ((periodT12 <= 16386.0) && (periodT12 > config->base.minResolution))
        {
            break;
        }
    }

    if (prescaler < 16)
    {
        Ifx_CCU6_TCTR0 tctr0;
        tctr0.U         = module->TCTR0.U;
        tctr0.B.T12CLK  = (prescaler & 0x7U);
        tctr0.B.T12PRE  = ((prescaler & 0x8U) != 0);
        module->TCTR0.U = tctr0.U;
    }
    else
    {
        /** \retval IfxCcu6_Stat_wrongPwmFreq if the T12 prescaler can't fulfill the
         * required frequency */
        result = FALSE;
    }

    IfxCcu6_TimerWithTrigger_updateInputFrequency(driver);

    if ((config->base.minResolution > 0) && ((1.0 / base->clockFreq) > config->base.minResolution))
    {
        result = FALSE;
        IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, FALSE);
    }
    else
    {}

    IfxCcu6_TimerWithTrigger_setFrequency(driver, config->base.frequency);
    /* Initialize the trigger part */

    /** - The T13 is used to generate additional PWM for internal trigger purpose (e.g.
     *  ADC) or external trigger purpose (e.g. sensor synchronisation). */

    if (base->triggerEnabled)
    {
        Ifx_CCU6_TCTR0 tctr0 = module->TCTR0;
        module->TCTR0.B.T13CLK = tctr0.B.T12CLK;
        module->TCTR0.B.T13PRE = tctr0.B.T12PRE;
        IfxCcu6_setT13PeriodValue(module, (uint16)(base->period - 1));

        module->MODCTR.B.T13MODEN = 0;
        IfxCcu6_enableModulationOutput(module, IfxCcu6_TimerId_t13, IfxCcu6_ChannelOut_cout3);

        IfxCcu6_setOutputPassiveLevel(module, IfxCcu6_ChannelOut_cout3, config->base.trigger.risingEdgeAtPeriod);

        IfxCcu6_setSingleShotModeEnable(module, FALSE, TRUE);

        IfxCcu6_setT13TriggerEventMode(module, IfxCcu6_T13TriggerEvent_onT12Zero);
        IfxCcu6_setT13TriggerEventDirection(module, IfxCcu6_T13TriggerDirection_onT12CountingUp);

        if (config->base.trigger.outputEnabled)
        {
            if (config->triggerOut != NULL_PTR)
            {
                /*Initialize the port */
                IfxCcu6_initCout63Pin(config->triggerOut, config->base.trigger.outputMode, config->base.trigger.outputDriver);
            }
            else
            {
                result = FALSE;
            }
        }
        else
        {}

        IfxCcu6_TimerWithTrigger_setTrigger(driver, config->base.trigger.triggerPoint);
    }
    else
    {}

    /* Interrupt configuration */
    {
        boolean timerHasIrq   = config->base.isrPriority > 0;
        boolean triggerHasIrq = (config->base.trigger.isrPriority > 0) && base->triggerEnabled;

        if (timerHasIrq || triggerHasIrq)
        {
            volatile Ifx_SRC_SRCR *src;

            IfxCcu6_clearInterruptStatusFlag(module, IfxCcu6_InterruptSource_t12PeriodMatch);
            IfxCcu6_clearInterruptStatusFlag(module, IfxCcu6_InterruptSource_t12OneMatch);
            IfxCcu6_clearInterruptStatusFlag(module, IfxCcu6_InterruptSource_t13CompareMatch);

            if (timerHasIrq)
            {
                if (config->base.countDir == IfxStdIf_Timer_CountDir_upAndDown)
                {
                    IfxCcu6_enableInterrupt(module, IfxCcu6_InterruptSource_t12OneMatch); /* full period */
                }
                else
                {
                    IfxCcu6_enableInterrupt(module, IfxCcu6_InterruptSource_t12PeriodMatch); /* half-period*/
                }

                module->INP.B.INPT12 = config->serviceReqNrPeriod;
                src                  = IfxCcu6_getSrcAddress(module, config->serviceReqNrPeriod);
                IfxSrc_init(src, config->base.isrProvider, config->base.isrPriority);
                IfxSrc_enable(src);
            }

            if (triggerHasIrq)
            {
                IfxCcu6_enableInterrupt(module, IfxCcu6_InterruptSource_t13CompareMatch); /* trigger event */
                module->INP.B.INPT13 = config->serviceReqNrTrigger;

                src                  = IfxCcu6_getSrcAddress(module, config->serviceReqNrTrigger);
                IfxSrc_init(src, config->base.trigger.isrProvider, config->base.trigger.isrPriority);
                IfxSrc_enable(src);
            }
        }
    }

    /* Transfer the shadow registers */
    IfxCcu6_TimerWithTrigger_applyUpdate(driver);
    return result;
}


void IfxCcu6_TimerWithTrigger_initConfig(IfxCcu6_TimerWithTrigger_Config *config, Ifx_CCU6 *ccu6)
{
    IfxStdIf_Timer_initConfig(&config->base);
    config->ccu6                = ccu6;
    config->serviceReqNrPeriod  = IfxCcu6_ServiceRequest_0;
    config->serviceReqNrTrigger = IfxCcu6_ServiceRequest_1;
    config->triggerOut          = NULL_PTR;
}


void IfxCcu6_TimerWithTrigger_run(IfxCcu6_TimerWithTrigger *driver)
{
    IfxCcu6_startTimer(driver->ccu6, TRUE, FALSE);
}


boolean IfxCcu6_TimerWithTrigger_setFrequency(IfxCcu6_TimerWithTrigger *driver, float32 frequency)
{
    Ifx_TimerValue period = IfxStdIf_Timer_sToTick(driver->base.clockFreq, 1.0 / frequency);

    return IfxCcu6_TimerWithTrigger_setPeriod(driver, period);
}


boolean IfxCcu6_TimerWithTrigger_setPeriod(IfxCcu6_TimerWithTrigger *driver, Ifx_TimerValue period)
{
    driver->base.period = period;
    IfxCcu6_setT12PeriodValue(driver->ccu6, (uint16)((driver->ccu6->TCTR0.B.CTM == 1) ?
                                                     ((period / 2) - 1) : (period - 1)));

    return TRUE;
}


void IfxCcu6_TimerWithTrigger_setSingleMode(IfxCcu6_TimerWithTrigger *driver, boolean enabled)
{
    if (enabled)
    {
        IfxCcu6_enableSingleShotMode(driver->ccu6, IfxCcu6_TimerId_t12);
    }
    else
    {
        IfxCcu6_disableSingleShotMode(driver->ccu6, IfxCcu6_TimerId_t12);
    }
}


void IfxCcu6_TimerWithTrigger_setTrigger(IfxCcu6_TimerWithTrigger *driver, Ifx_TimerValue triggerPoint)
{
    driver->ccu6->CC63SR.U = triggerPoint;
}


boolean IfxCcu6_TimerWithTrigger_stdIfTimerInit(IfxStdIf_Timer *stdif, IfxCcu6_TimerWithTrigger *driver)
{
    /* Ensure the stdif is reset to zeros */
    memset(stdif, 0, sizeof(IfxStdIf_Timer));

    /* *INDENT-OFF* Note: this file was indented manually by the author. */
    /* Set the API link */
    stdif->driver               = driver;
    stdif->getFrequency         =(IfxStdIf_Timer_GetFrequency        )&IfxCcu6_TimerWithTrigger_getFrequency;
    stdif->getPeriod            =(IfxStdIf_Timer_GetPeriod           )&IfxCcu6_TimerWithTrigger_getPeriod;
    stdif->getResolution        =(IfxStdIf_Timer_GetResolution       )&IfxCcu6_TimerWithTrigger_getResolution;
    stdif->setFrequency         =(IfxStdIf_Timer_SetFrequency        )&IfxCcu6_TimerWithTrigger_setFrequency;
    stdif->updateInputFrequency =(IfxStdIf_Timer_UpdateInputFrequency)&IfxCcu6_TimerWithTrigger_updateInputFrequency;
    stdif->applyUpdate          =(IfxStdIf_Timer_ApplyUpdate         )&IfxCcu6_TimerWithTrigger_applyUpdate;
    stdif->disableUpdate        =(IfxStdIf_Timer_DisableUpdate       )&IfxCcu6_TimerWithTrigger_disableUpdate;
    stdif->getInputFrequency    =(IfxStdIf_Timer_GetInputFrequency   )&IfxCcu6_TimerWithTrigger_getInputFrequency;
    stdif->run                  =(IfxStdIf_Timer_Run                 )&IfxCcu6_TimerWithTrigger_run;
    stdif->setPeriod            =(IfxStdIf_Timer_SetPeriod           )&IfxCcu6_TimerWithTrigger_setPeriod;
    stdif->setSingleMode        =(IfxStdIf_Timer_SetSingleMode       )&IfxCcu6_TimerWithTrigger_setSingleMode;
    stdif->setTrigger           =(IfxStdIf_Timer_SetTrigger          )&IfxCcu6_TimerWithTrigger_setTrigger;
    stdif->stop                 =(IfxStdIf_Timer_Stop                )&IfxCcu6_TimerWithTrigger_stop;
    stdif->ackTimerIrq          =(IfxStdIf_Timer_AckTimerIrq         )&IfxCcu6_TimerWithTrigger_acknowledgeTimerIrq;
    stdif->ackTriggerIrq        =(IfxStdIf_Timer_AckTriggerIrq       )&IfxCcu6_TimerWithTrigger_acknowledgeTriggerIrq;
    /* *INDENT-ON* */

    return TRUE;
}


void IfxCcu6_TimerWithTrigger_stop(IfxCcu6_TimerWithTrigger *driver)
{
    IfxCcu6_stopTimer(driver->ccu6, TRUE, TRUE);
}


void IfxCcu6_TimerWithTrigger_updateInputFrequency(IfxCcu6_TimerWithTrigger *driver)
{
    uint16 prescaler;
    prescaler              = driver->ccu6->TCTR0.B.T12CLK;

    driver->base.clockFreq = IfxScuCcu_getSpbFrequency() / (1U << prescaler);
}
