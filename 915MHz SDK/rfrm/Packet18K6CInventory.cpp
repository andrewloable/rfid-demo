#include "StdAfx.h"
#include "Packet18K6CInventory.h"

CPacket18K6CInventory::CPacket18K6CInventory(RFID_PACKET_COMMON* packet)
: CPacketCommon(packet)
{
}

CPacket18K6CInventory::~CPacket18K6CInventory(void)
{
}

CString CPacket18K6CInventory::BytetoArrayString(const INT8U* bytes, int start, int length)
{
	int index;
	CString stemp, str; 
	str = "";

	for (index = start; index < length; ++index)
	{
		//		stemp.Format(_T("%s%.2x"), (index && !(index % 4)) ? _T(" ") : _T(""), bytes[index]);
		stemp.Format(_T("%.2x"), bytes[index]);
		str += stemp;
	}

//	str.MakeUpper();
// #ifdef _DEBUG
// 	CString temp = str + _T("\n");
// 	TRACE(temp);
// #endif

	return str;
}

INT16U	CPacket18K6CInventory::GetPacketLength(void)
{
	return (MacToHost16(m_packet->pkt_len)-1) * BYTES_PER_LEN_UNIT - (m_packet->flags >> 6);
}

INT32U	CPacket18K6CInventory::GetReadCount(void)
{
	RFID_PACKET_18K6C_INVENTORY* packet = (RFID_PACKET_18K6C_INVENTORY *)m_packet;

	return MacToHost32(packet->count);
}

INT32U	CPacket18K6CInventory::GetTrialCount(void)
{
	RFID_PACKET_18K6C_INVENTORY* packet = (RFID_PACKET_18K6C_INVENTORY *)m_packet;

	return MacToHost32(packet->trial_count);
}

CString CPacket18K6CInventory::GetStrEPC(void)
{
	return BytetoArrayString((UINT8*)((RFID_PACKET_18K6C_INVENTORY *)m_packet)->inv_data, 2, 14);
}

CString CPacket18K6CInventory::GetStrPC(void)
{
	return BytetoArrayString((UINT8*)((RFID_PACKET_18K6C_INVENTORY *)m_packet)->inv_data, 0, 2);
}

void CPacket18K6CInventory::GetEPC(UINT32* epc)
{
//	INT32U epc[3];// = new INT32U;

//	memset(epc, 0, sizeof(INT32U) * 3);
	memcpy(((INT8U *)epc), ((INT8U *)((RFID_PACKET_18K6C_INVENTORY *)m_packet)->inv_data) + 2, sizeof(INT8U) * 12);

//	return epc;
}