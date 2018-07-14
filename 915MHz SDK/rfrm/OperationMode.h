#pragma once

// COperationMode command target
class CRFIDRadio;
class COperationMode : public CObject
{
public:
	COperationMode();
	virtual ~COperationMode();

	RFID_STATUS Load(CRFIDRadio* pRadio);
	RFID_STATUS Store(CRFIDRadio* pRadio);

	inline void SetOperationMode(RFID_RADIO_OPERATION_MODE mode) { m_radioOperationMode = mode; }
	inline RFID_RADIO_OPERATION_MODE GetOperationMode() { return m_radioOperationMode; }

protected:
	RFID_RADIO_OPERATION_MODE	m_radioOperationMode;

	DECLARE_SERIAL(COperationMode)
};


