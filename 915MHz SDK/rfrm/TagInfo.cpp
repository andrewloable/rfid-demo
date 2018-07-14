// TagInfo.cpp : implementation file
//

#include "stdafx.h"
#include "TagInfo.h"
#include <math.h>

namespace techwin
{

// CTagInfo

CTagInfo::CTagInfo()
: m_bFlag(0x00)
, m_TotalCount(0)
, m_ReadCount(0)
, m_TrialCount(0)
, m_Antenna(0)
, m_Channel(0)
, m_oleRecvTime(COleDateTime::GetCurrentTime())
, m_hEPCData(NULL)
{
	// Memory Allocation
	m_hEPCData = (INT16U*) malloc(sizeof(INT16U) * GetTagLength());

	// EPC Memory Allocation
	memset(m_hEPCData, 0x00, sizeof(INT16U) * GetTagLength());
}

CTagInfo::~CTagInfo()
{
	if(m_hEPCData != NULL)
		free(m_hEPCData);
}

// CTagInfo member functions

CString	CTagInfo::ByteArrayToString(const INT8U *bytes, int length, INT8U mode)
{
	int index;
	CString stemp, str; 
	str = "";

	for (index = 0; index < length; ++index)
	{
		if(mode == 1)
		{
			// 
			stemp.Format(_T("%c"), bytes[index]);
		}
		else
		{
			// stemp.Format(_T("%s%.2x"), (index && !(index % 4)) ? _T(" ") : _T(""), bytes[index]);
			stemp.Format(_T("%.2x"), bytes[index]);
		}

		str += stemp;
	}

	if(mode != 1)
		str.MakeUpper();

#ifdef _DEBUG
	CString temp = str + _T("\n");
	TRACE(temp);
#endif

	return str;
}

CString	CTagInfo::GetTagAsciiString()
{
	return ByteArrayToString((INT8U *)m_hEPCData, sizeof(INT16U) * GetTagLength(), 1);
}

CString	CTagInfo::GetTagString()
{
	return ByteArrayToString((INT8U *)m_hEPCData, sizeof(INT16U) * GetTagLength(), 0);
}

CString CTagInfo::GetTagPCString()
{
	return ByteArrayToString((INT8U *)&m_hPCData, sizeof(INT16U), 0);
}

INT16U* CTagInfo::GetTagPC()
{
	return &m_hPCData;
}

INT16U*	CTagInfo::GetTagEPC()
{
	return m_hEPCData;
}

BYTE CTagInfo::GetTagFilterFlag()
{
	return m_bFlag;
}

int	CTagInfo::GetTagTotalReadCount()
{
	return m_TotalCount;
}

int	CTagInfo::GetTagReadCount()
{
	return m_ReadCount;
}

INT16U	CTagInfo::GetTagTrialCount()
{
	return m_TrialCount;
}

int	CTagInfo::GetTagAntenna()
{
	return m_Antenna;
}

int	CTagInfo::GetTagChannel()
{
	return m_Channel;
}

INT16U CTagInfo::GetTagRSSI()
{
	return m_rssi;
}

INT8U CTagInfo::GetTagNarrowBandRSSI()
{
	return ((m_rssi & 0xFF00) >> 8);
}

INT8U CTagInfo::GetTagWideBandRSSI()
{
	return (m_rssi & 0x00FF);
}

INT16U	CTagInfo::GetTagLNAGain()
{
/*	INT8U lna = m_anaCtrl & 0x0030;

	switch(lna)
	{
	case 0:
		return 24;
		break;
	case 1:
		return 18;
		break;
	case 3:
		return 12;
		break;
	default:
		return 0;
	}*/
	return m_anaCtrl;
}


COleDateTime CTagInfo::GetTagReceiveTime()
{
	return m_oleRecvTime;
}

BOOL CTagInfo::SetTagMemory(const INT32U* tagMemory)
{
	memset(&m_hPCData, 0x00, sizeof(INT16U));
	memcpy(&m_hPCData, (INT16U*)((INT16U *)tagMemory), sizeof(INT16U));

#ifdef _DEBUG
	TRACE(_T("PC Area Data: %s\n"), ByteArrayToString((INT8U*)&m_hPCData, 2));
#endif

	// 기존 메모리 Clear
	if(m_hEPCData != NULL)
		free(m_hEPCData);

	// Memory Allocation
	m_hEPCData = (INT16U*) malloc(sizeof(INT16U) * GetTagLength());

	// EPC Memory Allocation
	memset(m_hEPCData, 0x00, sizeof(INT16U) * GetTagLength());
	memcpy(m_hEPCData, (INT16U*)(tagMemory) + 1, sizeof(INT16U) * GetTagLength());

#ifdef _DEBUG
	TRACE(_T("EPC Area Data: %s, size : \n"), ByteArrayToString((INT8U*)m_hEPCData, sizeof(INT16U) * GetTagLength()), sizeof(INT16U) * GetTagLength());
#endif

	return TRUE;
}

BOOL CTagInfo::IsValid()
{
	if(m_hPCData == NULL)
		return FALSE;

	if(m_hEPCData == NULL)
		return FALSE;

	if(((INT8U *)m_hPCData)[0] != 0x30 || ((INT8U *)m_hPCData)[0] != 0x40 || ((INT8U *)m_hPCData)[0] != 0x80)
		return FALSE;

	return TRUE;
}

void CTagInfo::SetTagPC(INT16U* pc)
{
	memcpy(&m_hPCData, pc, sizeof(INT16U));
}

void CTagInfo::SetTagEPC(INT16U* epc)
{
	// 기존 메모리 Clear
	if(m_hEPCData != NULL)
		free(m_hEPCData);

	// Memory Allocation
	m_hEPCData = (INT16U*) malloc(sizeof(INT16U) * GetTagLength());

	memset(m_hEPCData, 0x00, sizeof(INT16U) * GetTagLength());
	memcpy(m_hEPCData, (INT16U*)epc, sizeof(INT16U) * GetTagLength());

#ifdef _DEBUG
	TRACE(_T("Set EPC Area Data: %s\n"), ByteArrayToString((INT8U*)m_hEPCData, sizeof(INT16U) * GetTagLength()));
#endif
}

void CTagInfo::SetTagFilterFlag(BYTE flag)
{
	m_bFlag = flag;
}

void CTagInfo::SetTagReadCount(int count)
{
	m_ReadCount = count;
}

void CTagInfo::AddReadCount(int count)
{
	m_TotalCount += count;
}

void CTagInfo::SetTagTrialCount(INT16U tcount)
{
	m_TrialCount = tcount;
}

void CTagInfo::SetTagAntenna(int antenna)
{
	m_Antenna = antenna;
}

void CTagInfo::SetTagChannel(int channel)
{
	m_Channel = channel;
}

void CTagInfo::SetTagReveiveTime(COleDateTime time)
{
	m_oleRecvTime = time;
}

void CTagInfo::SetTagRSSI(INT16U rssi)
{
	m_rssi = rssi;
}

void CTagInfo::SetTagLNAGain(INT16U ana_ctrl)
{
	m_anaCtrl = ana_ctrl;
}


unsigned short pc_swap(unsigned short x)
{
	unsigned short temp = (x>>8) | (x<<8);

	return temp;
}

// EPC 영역의 Length 사이즈 리턴
INT16U CTagInfo::GetTagLength()
{
	unsigned __int16 pc = pc_swap(m_hPCData);

	unsigned __int16 word_count = pc & 0xf800;
	word_count = word_count >> 11;

	return word_count;
}

// UMI는 BANK 3 User Memory영역의 사용여부 표시
// 미사용의 경우 0을 리턴
// 사용의 경우 1을 리턴
BOOL CTagInfo::GetTagUMI()
{
	unsigned __int16 pc = pc_swap(m_hPCData);

	unsigned __int16 umi = pc  & 0x0400;
	umi = umi >> 10;

	return umi;
}

// XI는 추가적인 PC 영역 사용여부를 표시
// 미사용일 경우 0을 리턴
// 사용일 경우 1을 리턴
BOOL CTagInfo::GetTagXI()
{
	unsigned __int16 pc = pc_swap(m_hPCData);

	unsigned __int16 xi = pc  & 0x0200;
	xi = xi >> 9;

	return xi;
}

// Toggle는 Object에 기입되는 RFID 코드가 EPC 코드인지 아닌지(Non-EPC)를 표시
// EPC의 경우 0 리턴
// Non-EPC의 경우 1 리턴
BOOL CTagInfo::GetTagToggle()
{
	unsigned __int16 pc = pc_swap(m_hPCData);

	unsigned __int16 toggle = pc  & 0x0100;
	toggle = toggle >> 8;

	return toggle;
}

INT8U CTagInfo::GetTagAFI()
{
	unsigned __int16 pc = pc_swap(m_hPCData);

	unsigned __int16 temp = pc & 0x00ff;
	unsigned __int8 afi = (unsigned __int8)temp;

	return afi;
}

};