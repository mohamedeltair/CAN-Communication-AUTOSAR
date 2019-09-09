/** incomplete Com Types header file used as a test to PDUR module */

#ifndef COM_TYPES_H_INCLUDED
#define COM_TYPES_H_INCLUDED

#include "ComStack_Types.h"

/** Configuration structure for an I-PDU. */
typedef struct {

	/** The outgoing local PDU id. For polite PDU id handling. */
	const PduIdType IPduHandleId;

	/** Reference to the "global" PDU structure to allow harmonization of handle
	 *  IDs in the COM-Stack. */
	void *PduIdRef;

} ComIPdu_type;


/** Top-level configuration container for COM. Exists once per configuration. */
typedef struct {

	/** IPDU definitions */
	const ComIPdu_type *ComIPdu;
	/** Maximum number of IPDU's */
	uint16_t ComMaxIPduCnt;

} Com_ConfigType;


#endif // COM_TYPES_H_INCLUDED
