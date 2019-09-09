#include "Can_PBcfg.h"
#include "Can_Cfg.h"

//CAN0 configuration, Can 0 is used in transmission
Can_ControllerConfigType Can0ControllerConfig = {
	0, //Clock Source = oscillator clock (40 MHz)
	0, //Not used
	0, //Not used
	16, //PB0 (TX)
	17, //PB1 (RX)
	2 //PB1 as source signal
};

//CAN1 configuration, Can 1 is used in reception
Can_ControllerConfigType Can1ControllerConfig = {
	0, //Clock Source = oscillator clock (40 MHz)
	4, //Message buffer number
	0x555, //Target ID
	42, //PC10 (TX)
	43, //PC11 (RX)
	3 //PC11 as source signal
};

Can_ControllerConfigType *CanControllersConfigs[2] = {&Can0ControllerConfig, &Can1ControllerConfig};
Can_ConfigType CanConfig = {CanControllersConfigs};
