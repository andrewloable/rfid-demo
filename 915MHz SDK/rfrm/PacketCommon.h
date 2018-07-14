#pragma once

// CPacketCommon command target
#define BYTES_PER_LEN_UNIT	4

class CPacketCommon
{
public:
	CPacketCommon(RFID_PACKET_COMMON *packet);
	virtual ~CPacketCommon();
protected:
	RFID_PACKET_COMMON* m_packet;
	COleDateTime m_oleDataTimeRecv;

public:
// 	void	SetPacketVersion(UINT8 version);
// 	void	SetFlags(UINT8 flags);
// 	void	SetPacketType(UINT16 type);
// 	void	SetPacketLength(INT16U length);

	RFID_PACKET_COMMON*	GetPacketCommon();
	UINT8	GetPacketVersion(void);
	UINT8	GetFlags(void);
	UINT16	GetPacketType(void);
	virtual UINT16	GetPacketLength(void);
	COleDateTime	GetReceiveTime();
};


