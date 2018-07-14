#pragma once

#include "PacketCommon.h"

class CPacket18K6CInventory : public CPacketCommon
{
public:
	CPacket18K6CInventory(RFID_PACKET_COMMON* packet = NULL);
	virtual ~CPacket18K6CInventory(void);

// Attributes
protected:
// Operations
protected:
	CString BytetoArrayString(const INT8U* bytes, int start = 0, int length = 24);

public:
	INT32U	GetReadCount(void);
	INT32U	GetTrialCount(void);
	CString GetStrEPC(void);
	CString GetStrPC(void);
	void	GetEPC(UINT32* epc);
	virtual INT16U	GetPacketLength(void);
};
