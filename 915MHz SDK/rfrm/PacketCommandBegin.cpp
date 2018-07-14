/ PacketCommandBegin.cpp : implementation file
//

#include "stdafx.h"
#include "PacketCommandBegin.h"


// CPacketCommon

CPacketCommandBegin::CPacketCommandBegin(RFID_PACKET_COMMON *packet)
: CPacketCommon(packet)
{
}

CPacketCommandBegin::~CPacketCommandBegin()
{
}

INT32U	CPacketCommandBegin::GetCommand()
{
	RFID_PACKET_COMMAND_BEGIN *cmdbegin = (RFID_PACKET_COMMAND_BEGIN *)m_packet;
	return MacToHost32(cmdbegin->command);
}