/** incomplete Com configuration code file used as a test to PDUR module */

#include "Com.h"

/*
 * I-PDU definitions
 */
const ComIPdu_type ComIPdu[] = {

	{ // CanDB_Message_0
		//TX message
		.IPduHandleId = COM_PDU_ID_COM_TX_CANIF_MESSAGE_0,
		.PduIdRef = &Pdus[0]   //like SRC PDUR
	},
	{ // CanDB_Message_1
		//RX message
		.IPduHandleId = COM_PDU_ID_CANIF_RX_COM_MESSAGE_1,
		.PduIdRef = &Pdus[1]   //like DST PDUR
	},
	{ // CanDB_Message_2
		//TX message
		.IPduHandleId = COM_PDU_ID_COM_TX_CANTP_MESSAGE_2,
		.PduIdRef = &Pdus[2]   //like SRC PDUR
	},
	{ // CanDB_Message_3
		//RX message
		.IPduHandleId = COM_PDU_ID_CANTP_RX_COM_MESSAGE_3,
		.PduIdRef = &Pdus[3]   //like DST PDUR
	}
};

const Com_ConfigType ComConfiguration = {
	.ComIPdu = ComIPdu,
	.ComMaxIPduCnt = 4
};


