// ../OperationMode.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "OperationMode.h"

#include "RFIDRadio.h"

IMPLEMENT_SERIAL(COperationMode, CObject, 0) 
// COperationMode

COperationMode::COperationMode()
: m_radioOperationMode(RFID_RADIO_OPERATION_MODE_NONCONTINUOUS)
{
}

COperationMode::~COperationMode()
{
}


// COperationMode member functions
RFID_STATUS COperationMode::Load(CRFIDRadio* pRadio)
{
	RFID_STATUS result = RFID_STATUS_OK;

	if(RFID_STATUS_OK !=
		(result = pRadio->GetRadioOperationMode(&m_radioOperationMode)))
	{
		TRACE1("GetRadioOperationMode failed:  RC = %d\n", result);
		return result;
	}

	return result;
}

RFID_STATUS COperationMode::Store(CRFIDRadio* pRadio)
{
	RFID_STATUS result = RFID_STATUS_OK;

	if(RFID_STATUS_OK !=
		(result = pRadio->SetRadioOperationMode(m_radioOperationMode)))
	{
		TRACE1("SetRadioOperationMode failed:  RC = %d\n", result);
		return result;
	}

	return result;
}