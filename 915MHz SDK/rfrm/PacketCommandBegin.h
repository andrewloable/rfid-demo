#pragma once

// CPacketCommon command target
#include "PacketCommon.h"

class CPacketCommandBegin : public CPacketCommon
{
public:
	CPacketCommandBegin(RFID_PACKET_COMMON *packet);
	virtual ~CPacketCommandBegin();

public:
	INT32U	GetCommand();
};


