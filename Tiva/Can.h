#ifndef CAN_H
#define CAN_H

#include "Can_Cfg.h"
#include "Can_GeneralTypes.h"
#include "ComStack_Types.h"

/** @req 4.0.3/CAN416 */
// uint16: if only Standard IDs are used
// uint32: if also Extended IDs are used
typedef uint32 Can_IdType;

Can_ReturnType Can_Write(Can_HwHandleType hth, Can_PduType *pduInfo);

void Can_InitController(Can_ControllerConfigType *canx_config);
void Can_Init(const Can_ConfigType* Config);
void Can_MainFunction_Write(void);
void Can_MainFunction_Read(void);
Can_ReturnType Can_Write(Can_HwHandleType hth, Can_PduType *pduInfo);

#endif