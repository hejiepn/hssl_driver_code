/**
 * \file SpiIf.c
 * \brief SPI interface
 *
 * \copyright Copyright (c) 2013 Infineon Technologies AG. All rights reserved.
 *
 * $Date: 2014-02-27 20:08:21 GMT$
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

#include "SpiIf.h"

void SpiIf_initConfig(SpiIf_Config *config)
{
    config->mode            = SpiIf_Mode_master;
    config->rxPriority      = 0;
    config->txPriority      = 0;
    config->erPriority      = 0;
    config->isrProvider     = IfxSrc_Tos_cpu0;
    config->bufferSize      = 0;
    config->buffer          = NULL_PTR;
    config->maximumBaudrate = 0;
}


void SpiIf_initChannelConfig(SpiIf_ChConfig *config, SpiIf *driver)
{
    config->driver               = driver;
    config->baudrate             = 0;
    config->mode.enabled         = 1;
    config->mode.autoCS          = 1;
    config->mode.loopback        = 0;
    config->mode.clockPolarity   = SpiIf_ClockPolarity_idleLow;
    config->mode.shiftClock      = SpiIf_ShiftClock_shiftTransmitDataOnLeadingEdge;
    config->mode.dataHeading     = SpiIf_DataHeading_msbFirst;
    config->mode.dataWidth       = 8;
    config->mode.csActiveLevel   = Ifx_ActiveState_low;
    config->mode.csLeadDelay     = SpiIf_SlsoTiming_0;
    config->mode.csTrailDelay    = SpiIf_SlsoTiming_0;
    config->mode.csInactiveDelay = SpiIf_SlsoTiming_0;
    config->mode.parityCheck     = 0;
    config->mode.parityMode      = Ifx_ParityMode_even;
    config->errorChecks.baudrate = 0;
    config->errorChecks.phase    = 0;
    config->errorChecks.receive  = 0;
    config->errorChecks.transmit = 0;
}
