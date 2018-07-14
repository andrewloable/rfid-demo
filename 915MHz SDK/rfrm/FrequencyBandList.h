#pragma once

#define MAX_BAND 50

class CRFIDRadio;
class CFrequencyBand;
class CFrequencyBandList : 
	public CTypedPtrList<CObList, CFrequencyBand*>  
{
public:
	CFrequencyBandList(void);
	virtual ~CFrequencyBandList(void);

	RFID_STATUS Load(CRFIDRadio* pRadio);
	RFID_STATUS Store(CRFIDRadio* pRadio);
	CFrequencyBand* FindBand(INT32U band);
};
