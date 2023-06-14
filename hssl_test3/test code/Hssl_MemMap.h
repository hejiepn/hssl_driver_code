/**********************************************************************************************************************
 * \file Hssl_MemMap.h
 * \brief Memmap file is used to define the section of memory to which variables or constants will be placed
 * Memory mapping is a concept from AUTOSAR that allows relocation of text, variables, constants and
configuration data to user-specific memory regions. To achieve this, all the relocatable elements of
the driver are encapsulated in different memory-section macros. These macros are defined in the
Hssl_MemMap.h file. The Hssl_MemMap.h file is provided in the MCAL package as a stub code. The integrator
must place the appropriate compiler pragmas within the memory-section macros. The pragmas ensure that the
elements are relocated to the correct memory region. A sample implementation listing the
memory-section macros is as follows.

* \link https://github.com/marshallma21/MyAUTOSARProject-ECU/blob/master/MCAL/MCAL_Integration/Base/include/Port_MemMap.h
from here i got the template on how to write the pragma with the greenhills compiler

* \link
 https://github.com/autoas/as/blob/master/com/as.infrastructure/include/MemMap.h
 other link where it is described the way in autosar to do so memmap pragmas
 
  *********************************************************************************************************************/
/*

     IfxHssl_ChannelId chanID[] =  {IfxHssl_ChannelId_0, IfxHssl_ChannelId_1, IfxHssl_ChannelId_2, IfxHssl_ChannelId_3};
     const Ifx_HSCT *hsct = &MODULE_HSCT0;
const Ifx_HSSL *hssl = &MODULE_HSSL0;
uint32 sourceBuffer[NUM_LINKED_LIST_ITEMS][NUM_TRANSFERED_WORDS] = {
    {0xC0CAC01A, 0xFF0A0000, 0x70000000},
    {0xBA5EBA11, 0xFF0A0000, 0x70000010},
    {0xDEADBEEF, 0xFF0A0000, 0x70000020}
    };
const uint32 destinationAddresses[NUM_LINKED_LIST_ITEMS] = {
    (uint32)&HSSL0_I0_IWD,
    (uint32)&HSSL0_I0_IWD,
    (uint32)&HSSL0_I0_IWD
    };
    #define NUM_TRANSFERED_WORDS 3
    #define NUM_LINKED_LIST_ITEMS 3


*/

/*

    static IfxHssl_Hssl hssl;
    static IfxHssl_Hsct hsct;
    IfxHssl_Hssl_Channel hsslChannel[4];
    __attribute__((aligned(256))) uint32 txData[80];
    IfxHssl_Hsct_Config hsctConfig;
            IfxScuCcu_Config IfxScuCcu_sampleClockConfig;
                IfxHssl_Hssl_Config hsslConfig;
    IfxHssl_Hssl_ChannelConfig hsslChannelConfig;
    uint32 dataL = IfxHssl_Hssl_getReadData(&hsslChannel[channelNm]);
    IfxDma_Dma_Channel chn;
    __attribute__((aligned(64))) Ifx_DMA_CH linkedList[NUM_LINKED_LIST_ITEMS];
        IfxDma_Dma_Config dmaConfig;
    IfxDma_Dma dma;
    IfxDma_Dma_ChannelConfig cfg;
*/

/*To be used for all global or static variables.*/
#if defined HSSL_START_SEC_VAR_CLEARED_QM_LOCAL_8
/* User Pragma here */
#pragma ghs section bss = "hssl_bss_8"
#undef HSSL_START_SEC_VAR_CLEARED_QM_LOCAL_8
#undef MEMMAP_ERROR

#elif defined HSSL_STOP_SEC_VAR_CLEARED_QM_LOCAL_8
/* User Pragma here */
#pragma ghs section
#undef HSSL_STOP_SEC_VAR_CLEARED_QM_LOCAL_8
#undef MEMMAP_ERROR

#elif defined HSSL_START_SEC_VAR_INIT_QM_LOCAL_8
/* User Pragma here */
#pragma ghs section data = "hssl_data_8"

#undef HSSL_START_SEC_VAR_INIT_QM_LOCAL_8
#undef MEMMAP_ERROR

#elif defined HSSL_STOP_SEC_VAR_INIT_QM_LOCAL_8
/* User Pragma here */
#pragma ghs section
#undef HSSL_STOP_SEC_VAR_INIT_QM_LOCAL_8
#undef MEMMAP_ERROR

#elif defined HSSL_START_SEC_VAR_INIT_QM_LOCAL_32
/* User Pragma here */
#pragma ghs section data = "hssl_data_32"

#undef HSSL_START_SEC_VAR_INIT_QM_LOCAL_32
#undef MEMMAP_ERROR

#elif defined HSSL_STOP_SEC_VAR_INIT_QM_LOCAL_32
/* User Pragma here */
#pragma ghs section
#undef HSSL_STOP_SEC_VAR_INIT_QM_LOCAL_32
#undef MEMMAP_ERROR

#elif defined HSSL_START_SEC_VAR_CLEARED_QM_LOCAL_32
/* User Pragma here */
#pragma ghs section bss = "hssl_bss_32"

#undef HSSL_START_SEC_VAR_CLEARED_QM_LOCAL_32
#undef MEMMAP_ERROR

#elif defined HSSL_STOP_SEC_VAR_CLEARED_QM_LOCAL_32
/* User Pragma here */
#pragma ghs section
#undef HSSL_STOP_SEC_VAR_CLEARED_QM_LOCAL_32
#undef MEMMAP_ERROR

#elif defined HSSL_START_SEC_CONST_QM_LOCAL_32
/* User Pragma here */
#pragma ghs section rodata = "hssl_const_32"
#undef HSSL_START_SEC_CONST_QM_LOCAL_32
#undef MEMMAP_ERROR

#elif defined HSSL_STOP_SEC_CONST_QM_LOCAL_32
/* User Pragma here */
#pragma ghs section
#undef HSSL_STOP_SEC_CONST_QM_LOCAL_32
#undef MEMMAP_ERROR

/* Code Section */
#elif defined HSSL_START_SEC_CODE_QM_LOCAL
/* User Pragma here */
#pragma ghs section text = "hssl_text_code_unspecified"

#undef HSSL_START_SEC_CODE_QM_LOCAL
#undef MEMMAP_ERROR

#elif defined HSSL_STOP_SEC_CODE_QM_LOCAL
/* User Pragma here */
#pragma ghs section

#undef HSSL_STOP_SEC_CODE_QM_LOCAL
#undef MEMMAP_ERROR

#endif

#if defined MEMMAP_ERROR
#error "Hssl_MemMap.h, wrong pragma command"
#endif