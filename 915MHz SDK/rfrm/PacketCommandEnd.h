#pragma once

// CPacketCommandEnd command target
#include "PacketCommon.h"

class CPacketCommandEnd : public CPacketCommon
{
public:
	CPacketCommandEnd(RFID_PACKET_COMMON *packet);
	virtual ~CPacketCommandEnd();

public:
	INT32U	GetStatus();
};


