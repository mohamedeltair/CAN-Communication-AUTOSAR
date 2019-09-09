
//Can driver includes
#include "Can.h"
#include "CanIf_Cbk.h"
#include "EcuM_Cbk.h"
#include "Os.h"
#include "Spi.h"
#include "SchM_Can.h"
#include "MemMap.h"
#include "Det.h"
#include "Dem.h"
#include "Can_PBcfg.h"

//#include <stdlib.h>
//#include <string.h>
#include "Calypso.h"

void Can_DisableControllerInterrupts(uint8 controller) {
}

void Can0_Write(uint32 id, uint32 length, uint8 *sdu) {
    uint8 i;
    CAN_0.MB[0].CS.B.IDE = 0; /* Use standard ID length */
    CAN_0.MB[0].ID.B.ID_STD = id;/* Transmit ID */
    CAN_0.MB[0].CS.B.RTR = 0; /* Data frame, not remote Tx request frame */
    CAN_0.MB[0].CS.B.DLC = length; /*#bytes to transmit */
    for (i = 0; i < length; i++) {
        CAN_0.MB[0].DATA.B[i] = sdu[i]; /* Data to be transmitted */
    }
    CAN_0.MB[0].CS.B.SRR = 1; /* Tx frame (not req'd for standard frame)*/
    CAN_0.MB[0].CS.B.CODE = 0xC; /* Activate msg. buf. to transmit data frame */
}

void Can1_Write(uint32 id, uint32 length, uint8 *sdu) {
    uint8 i;
    CAN_1.MB[0].CS.B.IDE = 0; /* Use standard ID length */
    CAN_1.MB[0].ID.B.ID_STD = id;/* Transmit ID */
    CAN_1.MB[0].CS.B.RTR = 0; /* Data frame, not remote Tx request frame */
    CAN_1.MB[0].CS.B.DLC = length; /*#bytes to transmit */
    for (i = 0; i < length; i++) {
        CAN_1.MB[0].DATA.B[i] = sdu[i]; /* Data to be transmitted */
    }
    CAN_1.MB[0].CS.B.SRR = 1; /* Tx frame (not req'd for standard frame)*/
    CAN_1.MB[0].CS.B.CODE = 0xC; /* Activate msg. buf. to transmit data frame */
}

Can_ReturnType Can_Write(Can_HwHandleType Hth, Can_PduType* pduInfo) {
	
	//Build the CAN message
	uint32 id = pduInfo->id;
  uint32 length = pduInfo->length;
  uint8 *sdu = pduInfo->sdu;
	
	//Check the controller to use for sending
	if(Hth == 0) {
		Can0_Write(id, length, sdu);
	}
	else if(Hth == 1) {
		Can1_Write(id, length, sdu);
	}
	return CAN_OK;
}

/**
 * @param Msg[] 					----- 1 to 8 bytes received message
 * @param SduLength  			----- Message length
 * @param id  						----- Can Id
 * @param hoh 						----- Pin Id
 * @param ControllerID  	----- Id of controller on which message is received
 */
void Can_To_CanIf(uint8_t Msg[], PduLengthType SduLength, uint32_t id , uint16 hoh , uint8 ControllerID) {
	//uint8_t Msg[] = "from CAN drv to CANIF";
	const PduInfoType L_PDU = {
		.SduDataPtr = Msg,
		.SduLength = SduLength
	};
	Can_HwType Mailbox;
	Mailbox.CanId = (uint16)id;
	Mailbox.Hoh = hoh;
	Mailbox.ControllerId = ControllerID;
	CanIf_RxIndication(&Mailbox, &L_PDU);
}

void Can_MainFunction_Read_0(void) {
    uint8 i;
    uint32 Timer;
    while (CAN_0.IFLAG1.B.BUF4TO1I != 8) {}; /* Wait for CAN 0 MB 4 flag */
    uint32 Code = CAN_0.MB[4].CS.B.CODE; /* Read CODE, ID, LENGTH, DATA, TIMESTAMP*/
    uint32 Id = CAN_0.MB[4].ID.B.ID_STD;
    uint32 Length = CAN_0.MB[4].CS.B.DLC;
    uint8 Data[8];
		for (i = 0; i < Length; i++) {
        Data[i] = CAN_0.MB[4].DATA.B[i];
    }
    uint32 TimeStamp = CAN_0.MB[4].CS.B.TIMESTAMP;
    Timer = CAN_0.TIMER.R; /* Read TIMER to unlock message buffers */
    CAN_0.IFLAG1.R = 0x00000010; /* Clear CAN 1 MB 4 flag */
		//Forward to CanIf
		Can_To_CanIf(Data, Length, Id, 0, 0);
}

void Can_MainFunction_Read_1(void) {
    uint8 i;
    uint32 Timer;
    while (CAN_1.IFLAG1.B.BUF4TO1I != 8); /* Wait for CAN 1 MB 4 flag */
    uint32 Code = CAN_1.MB[4].CS.B.CODE; /* Read CODE, ID, LENGTH, DATA, TIMESTAMP*/
    uint32 Id = CAN_1.MB[4].ID.B.ID_STD;
    uint32 Length = CAN_1.MB[4].CS.B.DLC;
		uint8 Data[8];  
		for (i = 0; i < Length; i++) {
        Data[i] = CAN_1.MB[4].DATA.B[i];
    }
    uint32 TimeStamp = CAN_1.MB[4].CS.B.TIMESTAMP;
    Timer = CAN_1.TIMER.R; /* Read TIMER to unlock message buffers */
    CAN_1.IFLAG1.R = 0x00000010; /* Clear CAN 1 MB 4 flag */
		//Forward to CanIf
		Can_To_CanIf(Data, Length, Id, 1, 1);
}

/**
 * Initialize software and hardware configurations for CAN0 controller, which is used for transmission.
 *
 * @param canx_config			----- CAN0 controller configuration
 */
void Can0_InitController(Can_ControllerConfigType *canx_config) {
	
	uint8 i;
	
	CAN_0.MCR.B.MDIS = 1; /* Disable module before selecting clock source*/
	CAN_0.CTRL1.B.CLKSRC = canx_config->clockSource; /* Clock Source = clockSource */
	CAN_0.MCR.B.MDIS = 0; /* Enable module for config. (Sets FRZ, HALT)*/
	while (!CAN_0.MCR.B.FRZACK); /* Wait for freeze acknowledge to set */
	CAN_0.CTRL1.R = 0x04DB0086; /* CAN bus: 40 MHz clksrc, 500K bps with 16 tq */
	for (i = 0; i < 96; i++) { /* MPC574xG has 96 buffers after rev 0 */
			//CAN_0.MB[i].CS.B.CODE = 0; /* Deactivate all message buffers */
	}
	//CAN_0.MB[0].CS.B.CODE = 8; /* Message Buffer 0 set to TX INACTIVE */
	uint32 port_TX = canx_config->port_TX; 
	SIUL2.MSCR[port_TX].B.SSS = 1; /* Pad port_TX: Source signal is CAN0_TX */
	SIUL2.MSCR[port_TX].B.OBE = 1; /* Pad port_TX: Output Buffer Enable */
	SIUL2.MSCR[port_TX].B.SRC = 3; /* Pad port_TX: Maximum slew rate */
	SIUL2.MSCR[canx_config->port_RX].B.IBE = 1; /* Pad port_RX: Enable pad for input - CAN0_RX */
	SIUL2.IMCR[188].B.SSS = canx_config->port_RX_SS; /* CAN0_RX: connected to pad port_RX */
	CAN_0.MCR.R = 0x0000003F; /* Negate FlexCAN 0 halt state for 64 MB */
	while (CAN_0.MCR.B.FRZACK & CAN_0.MCR.B.NOTRDY); /* Wait to clear */
}

/**
 * Initialize software and hardware configurations for CAN1 controller, which is used for reception.
 *
 * @param canx_config			----- CAN1 controller configuration
 */
void Can1_InitController(Can_ControllerConfigType *canx_config) {
	
	uint8 i;
	
	CAN_1.MCR.B.MDIS = 1; /* Disable module before selecting clock source*/
	CAN_1.CTRL1.B.CLKSRC = canx_config->clockSource; /* Clock Source = clockSource */
	CAN_1.MCR.B.MDIS = 0; /* Enable module for config. (Sets FRZ, HALT)*/
	while (!CAN_1.MCR.B.FRZACK); /* Wait for freeze acknowledge to set */
	CAN_1.CTRL1.R = 0x04DB0086; /* Can bus: Same as CAN_0*/
	for (i = 0; i < 96; i++) { /* MPC574xG has 96 buffers after rev 0 */
			CAN_1.MB[i].CS.B.CODE = 0; /* Deactivate all message buffers */
	}
	uint32 msgBuffer = canx_config->msgBuffer;
	CAN_1.MB[msgBuffer].CS.B.IDE = 0; /* Message Buffer msgBuffer will look for a standard ID */
	CAN_1.MB[msgBuffer].ID.B.ID_STD = canx_config->targetId; /* Message Buffer msgBuffer will look for ID = targetId */
	CAN_1.MB[msgBuffer].CS.B.CODE = 4; /* Message Buffer msgBuffer set to RX EMPTY */
	CAN_1.RXMGMASK.R = 0x1FFFFFFF; /* Global acceptance mask */
	uint32 port_TX = canx_config->port_TX;
	SIUL2.MSCR[port_TX].B.SSS = 1; /* Pad port_TX: Source signal is CAN1_TX */
	SIUL2.MSCR[port_TX].B.SRC = 3; /* Pad port_TX: Maximum slew rate */
	SIUL2.MSCR[port_TX].B.OBE = 1; /* Pad port_TX: Output Buffer Enable */
	SIUL2.MSCR[canx_config->port_RX].B.IBE = 1; /* Pad port_RX: Enable pad for input -CAN1_RX */
	SIUL2.IMCR[189].B.SSS = canx_config->port_RX_SS; /* CAN1_RX : connected to pad port_RX */
	CAN_1.MCR.R = 0x0000003F; /* Negate FlexCAN 1 halt state for 64 MBs */
	while (CAN_1.MCR.B.FRZACK & CAN_1.MCR.B.NOTRDY); /* Wait to clear */
}

/**
 * Initialize software and hardware configurations for all attached CAN controllers.
 *
 * @param Config			----- CAN driver configuration
 */
void Can_Init(const Can_ConfigType *Config) {
	/* Do initial configuration of layer here */
	Can0_InitController(Config->canx_config[0]);
	Can1_InitController(Config->canx_config[1]);
}

void Can_EnableControllerInterrupts(uint8 controller) {
}
