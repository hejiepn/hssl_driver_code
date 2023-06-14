/**********************************************************************************************************************
 * \file SchM_Hssl.c
 * \brief Export Header for Schm functions of HSSL driver. Functions to protect critical sections
 * The SchM module is a part of the RTE that manages the BSW scheduler. The HSSL driver uses the exclusive
areas defined in SchM_Hssl.h to protect the SFRs and variables from concurrent accesses from different
threads. The SchMs identified for the HSSL driver are:
- Channel status lock
- Activate slave
- Deactivate slave
- DMA operated command queues
The SchM_Hssl.h and SchM_Hssl.c files are provided in the MCAL package as an example code and needs
to updated by the integrator. The user must implement the SchM functions defined by the HSSL driver as
suspend/resume of interrupts for the CPU on which the API is invoked. A sample implementation of the
SchM functions is as follows:
 ********************************************************************************************************************
/* sample implementation of SchM_Hssl.c */

#include "SchM_Hssl.h"

void SchM_Enter_Hssl_ChannelStatusLock(void)
{
 /* Start of Critical Section */


 SuspendAllInterrupts();/* Suspend CPU core interrupt */
}


void SchM_Exit_Hssl_ChannelStatusLock(void)
{
 /* Start of Critical Section */


 ResumeAllInterrupts();/* Suspend CPU core interrupt */
}


void SchM_Enter_Hssl_ActivateSlave(void)
{
 /* Start of Critical Section */
 SuspendAllInterrupts();/* Suspend CPU core interrupt */
}


void SchM_Exit_Hssl_ActivateSlave(void)
{
 /* Start of Critical Section */
 ResumeAllInterrupts();/* Suspend CPU core interrupt */
}


void SchM_Enter_Hssl_DeactivateSlave(void)
{
 /* Start of Critical Section */
 SuspendAllInterrupts();/* Suspend CPU core interrupt */
}


void SchM_Exit_Hssl_DeactivateSlave(void)
{
 /* Start of Critical Section */
 ResumeAllInterrupts();/* Suspend CPU core interrupt */
}


void SchM_Enter_Hssl_DmaOperatedCmdQueue(void)
{
 SuspendAllInterrupts();/* Suspend CPU core interrupt */
}


void SchM_Exit_Hssl_DmaOperatedCmdQueue(void)
{ 
 ResumeAllInterrupts();/* Suspend CPU core interrupt */
}