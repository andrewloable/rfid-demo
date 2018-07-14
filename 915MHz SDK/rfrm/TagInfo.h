#pragma once

namespace techwin
{

// CTagInfo command target

class CTagInfo// : public CObject
{
public:
	CTagInfo();
	virtual ~CTagInfo();

protected:
//	CString			m_strTagId;		// Tag ID
	INT16U*			m_hEPCData;	// EPC
	INT16U			m_hPCData;		// PC

	BYTE			m_bFlag;			// Filter Flag
	long			m_TotalCount;	// Total Read Count
	int				m_ReadCount;		// read Count
	INT16U			m_TrialCount;	// Trial Count
	INT16U			m_rssi;
	INT16U			m_anaCtrl;
	int				m_Antenna;	// Antenna Number
	int				m_Channel;			// Channel Infomation
	COleDateTime	m_oleRecvTime;		// Receive Time

	CString			ByteArrayToString(const INT8U *bytes, int length, INT8U mode = 0);

public:
	CString			GetTagAsciiString();
	CString			GetTagString();
	CString			GetTagPCString();
	INT16U*			GetTagPC();
	INT16U*			GetTagEPC();
	BYTE			GetTagFilterFlag();
	int				GetTagReadCount();
	int				GetTagTotalReadCount();
	INT16U			GetTagTrialCount();
	int				GetTagAntenna();
	int				GetTagChannel();
	INT16U			GetTagRSSI();
	INT8U			GetTagNarrowBandRSSI();
	INT8U			GetTagWideBandRSSI();
	INT16U				GetTagLNAGain();
	COleDateTime	GetTagReceiveTime();
	INT16U			GetTagLength();
	BOOL			GetTagUMI();
	BOOL			GetTagXI();
	BOOL			GetTagToggle();
	INT8U			GetTagAFI();

	BOOL			IsValid();

	BOOL			SetTagMemory(const INT32U* tagMemory);
	void			SetTagPC(INT16U* pc);
	void			SetTagEPC(INT16U* epc);
	void			SetTagFilterFlag(BYTE flag);
	void			SetTagReadCount(int count);
	void			AddReadCount(int count);
	void			SetTagTrialCount(INT16U tcount);
	void			SetTagAntenna(int antenna);
	void			SetTagChannel(int channel);
	void			SetTagRSSI(INT16U rssi);
	void			SetTagLNAGain(INT16U ana_ctrl);
	void			SetTagReveiveTime(COleDateTime time);
//	void			SetTagPC(INT16U pc);
};

};
