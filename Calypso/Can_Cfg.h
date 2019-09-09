#ifndef CAN_CFG_H
#define CAN_CFG_H

#include "Std_Types.h"

typedef struct {
	uint32 clockSource;
	uint32 msgBuffer; //In case of receive
	uint32 targetId; //In case of receive
	uint32 port_TX;
	uint32 port_RX;
	uint32 port_RX_SS; //port_RX as source signal

} Can_ControllerConfigType;

typedef struct {
	Can_ControllerConfigType **canx_config;
} Can_ConfigType;

#endif

