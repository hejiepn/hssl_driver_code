/**********************************************************************************************************************
 * \file HSSL_TEST.c
 * \copyright Copyright (C) Infineon Technologies AG 2019
 *
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are solely in the form of
 * machine-executable object code generated by a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *********************************************************************************************************************/

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/

#include "HSSL_TEST.h"
#include "HSSL_interrupt.h"
#include "Libraries\iLLD\TC37A\Tricore\Hssl\Hssl\IfxHssl_Hssl.h"
#include "Libraries\iLLD\TC37A\Tricore\_Impl\IfxHssl_cfg.h"
#include "Libraries\iLLD\TC37A\Tricore\Hssl\Std\IfxHssl.h"
#include "Libraries\iLLD\TC37A\Tricore\Port\Std\IfxPort.h"
#include "Libraries\iLLD\TC37A\Tricore\Scu\Std\IfxScuCcu.h"
#include "Libraries\Infra\Sfr\TC37A\_Reg\IfxHsct_reg.h"
#include "Libraries\iLLD\TC37A\Tricore\Dma\Dma\IfxDma_Dma.h"
#include "Libraries\iLLD\TC37A\Tricore\Scu\Std\IfxScuWdt.h"
// #include "SchM_Hssl.h"
#include "stdbool.h"
#include "stdint.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
// used globally test
static IfxHssl_Hssl hssl;
static IfxHssl_Hsct hsct;
int setHighSpeedMode = 0;
int setLoopBack = 0;
IfxHssl_Hssl_Channel hsslChannel[4];
__attribute__((aligned(256))) uint32 txData[80]; // for streaming used


static IfxScuCcu_PllStepConfig IfxScuCcu_testPllConfigSteps[] = {
    IFXSCU_CFG_PLL_STEPS};

static const IfxScuCcu_FlashWaitstateConfig IfxScuCcu_defaultFlashWaitstateConfig = IFXSCU_CFG_FLASH_WAITSTATE;
IfxScuCcu_Config IfxScuCcu_testClockConfig = {
    IFXSCU_CFG_PLL_INITIAL_STEP,
    {
        sizeof(IfxScuCcu_testPllConfigSteps) / sizeof(IfxScuCcu_PllStepConfig),
        IfxScuCcu_testPllConfigSteps},
    IFXSCU_CFG_CLK_DISTRIBUTION,
    &IfxScuCcu_defaultFlashWaitstateConfig,
    &IfxScuCcu_defaultModConfig};

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/



void initHSSL(char ifMode, char sMode, int loopBackMode) // s = slave mode, m = master mode
{

    IfxScuCcu_init(&IfxScuCcu_testClockConfig);

    IfxHssl_Hsct_Config hsctConfig;
    IfxHssl_Hssl_initHsctModuleConfig(&hsctConfig, &MODULE_HSCT0);

    if (ifMode == 's')
    {
        hsctConfig.interfaceMode = IfxHssl_InterfaceMode_slave;
    }

    if (ifMode == 'm')
    {
        if (sMode == 'h')
        {
            hsctConfig.highSpeedMode = TRUE;
            setHighSpeedMode = 1;
        }
        if (loopBackMode == 1)
        {
            hsctConfig.loopBack = TRUE;
            setLoopBack = 1;
        }
    }

    IfxHssl_Hssl_initHsctModule(&hsct, &hsctConfig);

    if (ifMode == 's')
    {
        IfxScuCcu_initConfig(&IfxScuCcu_testClockConfig);
        IfxScuCcu_testClockConfig.pllInitialStepConfig.pllsParameters.pllInputClockSelection = IfxScuCcu_PllInputClockSelection_fSysclk;
        IfxScuCcu_init(&IfxScuCcu_testClockConfig);

        if (hsct.hsct->IRQ.B.PLER == 0x1 && hsct.hsct->STATPHY.B.PLOCK == 0x1)
        {
            hsct.hsct->IRQ.B.PLER = 0x0;
        }
    }
    IfxHssl_Hssl_Config hsslConfig;
    IfxHssl_Hssl_initHsslModuleConfig(&hsslConfig, &MODULE_HSSL0);

    IfxHssl_Hssl_initHsslModule(&hssl, &hsslConfig);

    IfxHssl_Hssl_ChannelConfig hsslChannelConfig;
    IfxHssl_Hssl_initChannelConfig(&hsslChannelConfig, &hssl, &hsct);
    for (int i = 0; i < 4; ++i)
    {
        hsslChannelConfig.channelId = (IfxHssl_ChannelId)i;
        IfxHssl_Hssl_initChannel(&hsslChannel[i], &hsslChannelConfig);
    }

}


void simpleTransferHSSL(int channelNm, uint32 address, uint32 data)
{
    IfxHssl_Hssl_write(&hsslChannel[channelNm], address, data, IfxHssl_DataLength_32bit);

    while (IfxHssl_Hssl_waitAcknowledge(&hsslChannel[channelNm]) != IfxHssl_Hssl_Status_ok)
    {
        if (IfxHssl_Hssl_waitAcknowledge(&hsslChannel[channelNm]) == IfxHssl_Hssl_Status_error)
        {
            IfxHssl_Hssl_checkErrors(&hssl);
            break;
        }
    }
}

void simpleReadHSSL(int channelNm, uint32 address)
{
    IfxHssl_Hssl_read(&hsslChannel[channelNm], address, IfxHssl_DataLength_32bit);

    while (IfxHssl_Hssl_waitAcknowledge(&hsslChannel[channelNm]) != IfxHssl_Hssl_Status_ok)
    {
        if (IfxHssl_Hssl_waitAcknowledge(&hsslChannel[channelNm]) == IfxHssl_Hssl_Status_error)
        {
            IfxHssl_Hssl_checkErrors(&hssl);
            break;
        }
    }

    uint32 dataL = IfxHssl_Hssl_getReadData(&hsslChannel[channelNm]);
}


void streamingTransfer(int channelNm)
{
    IfxHssl_Hssl_prepareStream(&hsslChannel[channelNm], 0x70000000, 10);

    IfxHssl_Hssl_writeStream(&hssl, txData, 10);

    while (IfxHssl_Hssl_waitAcknowledge(&hsslChannel[2]) != IfxHssl_Hssl_Status_ok)
    {
    }
}

void speedMode(char speedMode) // h= highSpeed and l = lowSpeed
{
    if (hsct.hsct->INIT.B.IFM == IfxHssl_InterfaceMode_master)
    {
        switch (speedMode)
        {
        case 'h':
            // Set the Tx link speed of the master to Low speed
            IfxHssl_setHsctTxLinkSpeed(&(*hsct.hsct), IfxHssl_MasterModeTxSpeed_lowSpeed);

            // Enable reception at the Slave
            IfxHssl_Hssl_sendControlCommand(&hsct, IfxHssl_ControlCommand_enableReception);

            // Send interface commmand to change Rx to High speed at the target
            IfxHssl_Hssl_sendControlCommand(&hsct, IfxHssl_ControlCommand_highSpeedReception);

            // Send interface commmand to change Tx to High speed at the target
            IfxHssl_Hssl_sendControlCommand(&hsct, IfxHssl_ControlCommand_highSpeedTransmission);

            // Set the Tx link speed of the master to High speed
            IfxHssl_setHsctTxLinkSpeed(&(*hsct.hsct), IfxHssl_MasterModeTxSpeed_highSpeed);

            // Set the Rx link speed of the master to High speed
            IfxHssl_setHsctRxLinkSpeed(&(*hsct.hsct), IfxHssl_MasterModeRxSpeed_highSpeed);
            break;

        case 'l':
            // Set the Tx link speed of master to Low speed
            IfxHssl_setHsctTxLinkSpeed(&(*hsct.hsct), IfxHssl_MasterModeTxSpeed_lowSpeed);

            // Enable reception at the Slave
            IfxHssl_Hssl_sendControlCommand(&hsct, IfxHssl_ControlCommand_enableReception);

            // Send interface command to change Rx to low speed at the target
            IfxHssl_Hssl_sendControlCommand(&hsct, IfxHssl_ControlCommand_lowSpeedReception);

            // Set the Rx link speed of master to Low speed
            IfxHssl_setHsctRxLinkSpeed(&(*hsct.hsct), IfxHssl_MasterModeRxSpeed_lowSpeed);

            // Send interface command to change Tx to low speed at the target
            IfxHssl_Hssl_sendControlCommand(&hsct, IfxHssl_ControlCommand_lowSpeedTransmission);
            break;

        default: // highspeed mode
            // Set the Tx link speed of the master to Low speed
            IfxHssl_setHsctTxLinkSpeed(&(*hsct.hsct), IfxHssl_MasterModeTxSpeed_lowSpeed);

            // Enable reception at the Slave
            IfxHssl_Hssl_sendControlCommand(&hsct, IfxHssl_ControlCommand_enableReception);

            // Send interface commmand to change Rx to High speed at the target
            IfxHssl_Hssl_sendControlCommand(&hsct, IfxHssl_ControlCommand_highSpeedReception);

            // Send interface commmand to change Tx to High speed at the target
            IfxHssl_Hssl_sendControlCommand(&hsct, IfxHssl_ControlCommand_highSpeedTransmission);

            // Set the Tx link speed of the master to High speed
            IfxHssl_setHsctTxLinkSpeed(&(*hsct.hsct), IfxHssl_MasterModeTxSpeed_highSpeed);

            // Set the Rx link speed of the master to High speed
            IfxHssl_setHsctRxLinkSpeed(&(*hsct.hsct), IfxHssl_MasterModeRxSpeed_highSpeed);
            break;
        }
    }
}

void setSlave(void)
{
        IfxHssl_setHsctTxLinkSpeed(&(*hsct.hsct), IfxHssl_MasterModeTxSpeed_lowSpeed);

        IfxHssl_Hssl_sendControlCommand(&hsct, IfxHssl_ControlCommand_enableReception);

        IfxHssl_Hssl_sendControlCommand(&hsct, IfxHssl_ControlCommand_highSpeedClockStart);

        IfxHssl_Hssl_sendControlCommand(&hsct, IfxHssl_ControlCommand_highSpeedReception);

        IfxHssl_Hssl_sendControlCommand(&hsct, IfxHssl_ControlCommand_highSpeedTransmission);

        IfxHssl_setHsctTxLinkSpeed(&(*hsct.hsct), IfxHssl_MasterModeTxSpeed_highSpeed);
}

void sendPing(void)
{
    IfxHssl_Hssl_sendControlCommand(&hsct, IfxHssl_ControlCommand_ping);
}

void setClockTest(void)
{
    IfxHssl_Hssl_sendControlCommand(&hsct, IfxHssl_ControlCommand_turnOnClockTestMode);
}
