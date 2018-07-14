#include "StdAfx.h"
#include "FrequencyBandList.h"
#include "FrequencyBand.h"

CFrequencyBandList::CFrequencyBandList(void)
{
}

CFrequencyBandList::~CFrequencyBandList(void)
{
}

RFID_STATUS CFrequencyBandList::Load(CRFIDRadio* pRadio)
{
	RFID_STATUS result = RFID_STATUS_OK;

	for ( register unsigned int band = 0; band < MAX_BAND ;  band++ )
	{
		CFrequencyBand* freqBand = new CFrequencyBand( band );

		result = freqBand->Load( pRadio );

		if(RFID_STATUS_OK == result)
		{
			this->AddTail(freqBand);
		}
		else if ( RFID_ERROR_INVALID_PARAMETER == result )
		{
			break; // in case max bands gets lowered in future e.g. european version
		}
		else if ( RFID_ERROR_EMULATION_MODE == result )
		{
			break; // in case library ( transport ) is in emulation mode
		}
		else
		{
			return result; // this rcv all other errors
		}
	}

	return result;
}

RFID_STATUS CFrequencyBandList::Store(CRFIDRadio* pRadio)
{
	RFID_STATUS result = RFID_STATUS_OK;

	POSITION pos = GetHeadPosition();

	while(pos)
	{
		CFrequencyBand* freqBand = GetNext(pos);

		if(RFID_STATUS_OK !=
			(result = freqBand->Store(pRadio)))
		{
			return result;
		}
	}

	return result;
}

CFrequencyBand* CFrequencyBandList::FindBand(INT32U band)
{

	POSITION pos = GetHeadPosition();

	while(pos)
	{
		CFrequencyBand* freqBand = GetNext(pos);

		if( freqBand->GetBand() == band)
		{
			return freqBand;
		}
	}

	return NULL;
}