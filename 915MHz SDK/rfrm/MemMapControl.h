#pragma once

class CMemMapControl 
{
public:
	CMemMapControl(void);
	virtual ~CMemMapControl(void);
	// File Handle
	HANDLE m_fileHandle;
	HANDLE m_mappingHandle;
	LPVOID m_startAddress;
	UINT32 m_size;
};
