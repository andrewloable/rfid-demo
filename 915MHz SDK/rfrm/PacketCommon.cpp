/ PacketCommon.cpp : implementation file
//

#include "stdafx.h"
#include "PacketCommon.h"


// CPacketCommon

CPacketCommon::CPacketCommon(RFID_PACKET_COMMON *packet)
: m_packet(packet)
, m_oleDataTimeRecv(COleDateTime::GetCurrentTime())
{
}

CPacketCommon::~CPacketCommon()
{
}

UINT8	CPacketCommon::GetPacketVersion(void)
{
	return m_packet->pkt_ver;
}

UINT8	CPacketCommon::GetFlags(void)
{
	return m_packet->flags;
}

UINT16	CPacketCommon::GetPacketType(void)
{
	return MacToHost16(m_packet->pkt_type);
}

UINT16	CPacketCommon::GetPacketLength(void)
{
	return MacToHost16(m_packet->pkt_len);
}

RFID_PACKET_COMMON*	CPacketCommon::GetPacketCommon()
{
	return m_packet;
}

COleDateTime CPacketCommon::GetReceiveTime()
{
	return m_oleDataTimeRecv;
}