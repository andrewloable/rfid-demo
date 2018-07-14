#include "StdAfx.h"
#include "TagData.h"

CTagData::CTagData(void)
: m_nSumofReadCount(0)
, m_oleDateTimeRecv(COleDateTime::GetCurrentTime())
, m_epc(new UINT32)
, m_nReadCount(1)
, m_nTrialCount(0)
, m_nAntennaNumber(1)
{
//	m_epc = new UINT32;
//	memset(m_epc, 0, sizeof(UINT32) * 3);
}

CTagData::~CTagData(void)
{
	if(m_epc != NULL)
		delete m_epc;
}

long CTagData::GetTagSumofReadCount()
{
	return m_nSumofReadCount;
}

COleDateTime CTagData::GetTagReceiveTime()
{
	return m_oleDateTimeRecv;
}

UINT32*	CTagData::GetTagEPC()
{
	return m_epc;
}

CString CTagData::GetTagEPCString()
{
	return ByteArrayToCString((UINT8*)m_epc, 12);;
}

UINT CTagData::GetTagReadCount()
{
	return m_nReadCount;
}

UINT CTagData::GetTagTrialCount()
{
	return m_nTrialCount;
}

void CTagData::SetTagReadCount(UINT count)
{
	m_nReadCount = count;
	m_nSumofReadCount += count;
}

void CTagData::SetTagTrialCount(UINT count)
{
	m_nTrialCount = count;
}

void CTagData::SetTagEPC(UINT32* epc)
{
	assert(epc);
//	m_epc = new UINT32;

#ifdef _DEBUG
	TRACE(_T("CTagData EPC : "));
	ByteArrayToCString((UINT8*)m_epc, 12);
	ByteArrayToCString((UINT8*)epc, 12);
#endif

	memcpy(m_epc, epc, sizeof(UINT32) * 3);

#ifdef _DEBUG
	TRACE(_T("CTagData EPC : "));
	ByteArrayToCString((UINT8*)m_epc, 12);
	ByteArrayToCString((UINT8*)epc, 12);
#endif
}

void CTagData::SetTagReceiveTime(COleDateTime time)
{
	m_oleDateTimeRecv = time;
}

CString CTagData::ByteArrayToCString(
									  const INT8U *bytes,
									  int length
									  )
{
	int index;
	CString stemp, str; 
	str = "";

	for (index = 0; index < length; ++index)
	{
		stemp.Format(_T("%.2x"), bytes[index]);
		str += stemp;
	}

	str.MakeUpper();
#ifdef _DEBUG
	CString temp = str + _T("\n");
	TRACE(temp);
#endif

	return str;
}
