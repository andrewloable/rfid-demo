#pragma once

class CPacket18K6CInventory;
class CTagData
{
public:
	CTagData(void);
	virtual ~CTagData(void);

protected:
	long			m_nSumofReadCount;
	COleDateTime	m_oleDateTimeRecv;
	UINT32*			m_epc;
	UINT			m_nReadCount;
	UINT			m_nTrialCount;
	UINT			m_nAntennaNumber;

	CString ByteArrayToCString(const INT8U *bytes, int length);

public:
	long			GetTagSumofReadCount();
	COleDateTime	GetTagReceiveTime();
	UINT32*			GetTagEPC();
	CString			GetTagEPCString();
	UINT			GetTagReadCount();
	UINT			GetTagTrialCount();

//	void			SetDatafromInventoru(CPacket18K6CInventory* inv);
	void			SetTagReadCount(UINT count);
	void			SetTagTrialCount(UINT count);
	void			SetTagEPC(UINT32* epc);
	void			SetTagReceiveTime(COleDateTime time);
};
