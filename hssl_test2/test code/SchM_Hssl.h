/**********************************************************************************************************************
 * \file SchM_Hssl.h
 * \brief Export Header for Schm functions of HSSL driver. Functions to protect critical sections
 *********************************************************************************************************************/

#ifndef SchM_Hssl_H_
#define Schm_Hssl_H_

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/

void SchM_Enter_Hssl_ChannelStatusLock(void);
void SchM_Exit_Hssl_ChannelStatusLock(void);
void SchM_Enter_Hssl_ActivateSlave(void);
void SchM_Exit_Hssl_ActivateSlave(void);
void SchM_Enter_Hssl_DeactivateSlave(void);
void SchM_Exit_Hssl_DeactivateSlave(void);
void SchM_Enter_Hssl_DmaOperatedCmdQueue(void);
void SchM_Exit_Hssl_DmaOperatedCmdQueue(void);

#endif /* SchmM_Hssl_H_ */
