// PacketCommandBegin.cpp : implementation file
//

#include "stdafx.h"
#include "PacketCommandEnd.h"


// CPacketCommandBegin

CPacketCommandEnd::CPacketCommandEnd(RFID_PACKET_COMMON *packet)
: CPacketCommon(packet)
{
}

CPacketCommandEnd::~CPacketCommandEnd()
{
}

INT32U	CPacketCommandEnd::GetStatus()
{
	RFID_PACKET_COMMAND_END *cmdend = (RFID_PACKET_COMMAND_END *)m_packet;
	return MacToHost32(cmdend->status);
}
