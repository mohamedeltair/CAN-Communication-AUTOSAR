#ifndef CANIF_H_INCLUDED
#define CANIF_H_INCLUDED

#include "CanIf_Types.h"
#include "CanIf_Cfg.h"
#include "Can_GeneralTypes.h"
#include "PduR_CanIf.h"

// CANIF interface for PDUR
extern const CanIf_ConfigType* canIf_ConfigPtr;

void CanIf_Init(const CanIf_ConfigType *ConfigPtr);
Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr); ///tested
void CanIf_TxConfirmation(PduIdType CanTxPduId);
void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr);
Std_ReturnType CanIf_INF_GetPduHandleId(Pdu_Type* Pdu, PduIdType* PduHandleIdPtr);
Std_ReturnType CanIf_GetControllerMode(uint8 ControllerId, CanIf_ControllerModeType *ControllerModePtr);
//Std_ReturnType CanIf_SetControllerMode(uint8 ControllerId, CanIf_ControllerModeType ControllerMode);
//Std_ReturnType CanIf_CancelTransmit(PduIdType TxPduId);
//Std_ReturnType CanIf_GetControllerErrorState(uint8 ControllerId, Can_ErrorStateType *ErrorStatePtr); ///tested
//#if (CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON)
//Std_ReturnType CanIf_ReadRxPduData(PduIdType CanIfRxSduId, PduInfoType* CanIfRxInfoPtr);
//#endif
//Std_ReturnType CanIf_SetPduMode(uint8 ControllerId, CanIf_PduModeType PduModeRequest); ///tested
//Std_ReturnType CanIf_GetPduMode(uint8 ControllerId, CanIf_PduModeType * PduModePtr); ///tested
////#if ( CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_ON )
//void CanIf_SetDynamicTxId(PduIdType CanIfTxSduId, Can_IdType CanId);
////#endif

//Std_ReturnType CanIf_SetTrcvMode(uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode); ///tested
//Std_ReturnType CanIf_GetTrcvMode(uint8 TransceiverId, CanTrcv_TrcvModeType * TransceiverModePtr); ///tested
//Std_ReturnType CanIf_GetTrcvWakeupReason(uint8 TransceiverId, CanTrcv_TrcvWakeupReasonType * TrcvWuReasonPtr); ///tested
//Std_ReturnType CanIf_SetTrcvWakeupMode(uint8 TransceiverId, CanTrcv_TrcvWakeupModeType TrcvWakeupMode); ///tested

//#if (CANIF_INF_WAKEUP_SUPPORT == STD_ON)
//Std_ReturnType CanIf_CheckWakeup(EcuM_WakeupSourceType WakeupSource); ///tested
//#endif
//#if (CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_ON)
//Std_ReturnType CanIf_CheckValidation(EcuM_WakeupSourceType WakeupSource); ///tested
//#endif
//#if ( CANIF_INF_PUBLIC_TX_CONFIRMATION_POLLING_SUPPORT == STD_ON )
//CanIf_NotifStatusType CanIf_GetTxConfirmationState(uint8 ControllerId); ///tested
//#endif
//#if (CANIF_INF_CAN_TRCV_SUPPORT == STD_ON && CANIF_PUBLIC_PN_SUPPORT == STD_ON )
//Std_ReturnType CanIf_ClearTrcvWufFlag(uint8 TransceiverId); ///tested
//Std_ReturnType CanIf_CheckTrcvWakeFlag(uint8 TransceiverId); ///tested
//#endif
//#if(CANIF_SET_BAUDRATE_API == STD_ON)
//Std_ReturnType CanIf_SetBaudrate(uint8 ControllerId, uint16 BaudRateConfigID); ///tested
//#endif
//#if(CANIF_PUBLIC_ICOM_SUPPORT == STD_ON)
//Std_ReturnType CanIf_SetIcomConfiguration(uint8 ControllerId, IcomConfigIdType ConfigurationId); ///tested

#endif