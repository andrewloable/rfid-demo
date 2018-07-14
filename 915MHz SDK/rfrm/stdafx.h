// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifdef WINCE
#pragma comment(linker, "/nodefaultlib:libc.lib")
#pragma comment(linker, "/nodefaultlib:libcd.lib")
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

// NOTE - this is value is not strongly correlated to the Windows CE OS version being targeted
#ifdef WINCE
	#define WINVER _WIN32_WCE

	#ifdef _CE_DCOM
	#define _ATL_APARTMENT_THREADED
	#endif

	#include <ceconfig.h>

#else
	#ifndef WINVER				// Allow use of features specific to Windows XP or later.
	#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
	#endif

	#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
	#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
	#endif						

	#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
	#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
	#endif

	#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
	#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
	#endif
#endif

// #if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
// #error "단일 스레드 COM 개체는 전체 DCOM 지원을 포함하지 않는 Windows Mobile 플랫폼과 같은 Windows CE 플랫폼에서 제대로 지원되지 않습니다. ATL이 단일 스레드 COM 개체의 생성을 지원하고 단일 스레드 COM 개체 구현을 사용할 수 있도록 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA를 정의하십시오. rgs 파일의 스레딩 모델은 DCOM Windows CE가 아닌 플랫폼에서 지원되는 유일한 스레딩 모델이므로 'Free'로 설정되어 있습니다."
// #endif


#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcview.h>		// MFC View classes
#include <afxdisp.h>        // MFC Automation classes

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#endif

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afx.h>

#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
	#define SHELL_AYGSHELL
	#ifndef _DEVICE_RESOLUTION_AWARE
		#define _DEVICE_RESOLUTION_AWARE
	#endif

	#ifdef _DEVICE_RESOLUTION_AWARE
	#include "DeviceResolutionAware.h"
	#endif

	#ifdef SHELL_AYGSHELL
	#include <aygshell.h>
	#pragma comment(lib, "aygshell.lib") 
	#endif // SHELL_AYGSHELL
#endif

#if (_WIN32_WCE < 0x500) && ( defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP) )
	#pragma comment(lib, "ccrtrtti.lib")
	#ifdef _X86_	
		#if defined(_DEBUG)
			#pragma comment(lib, "libcmtx86d.lib")
		#else
			#pragma comment(lib, "libcmtx86.lib")
		#endif
	#endif
#endif

#if defined(WINCE) && (_WIN32_WCE > 0x300)
	#ifndef SHELL_AYGSHELL
	#include <aygshell.h>
	#pragma comment(lib, "aygshell.lib")
	#endif // SHELL_AYGSHELL
#endif

#if defined(WINCE)
#include <altcecrt.h>
#endif

#if _MSC_VER >= 1300
	#include <..\src\mfc\afximpl.h>		// VC.NET
#else
	#include <..\src\afximpl.h>			// VC 5/6
#endif

//#include <afxrich.h>

#ifdef WIN32
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
#endif

#include "rfid_library.h"
#include "rfid_packets.h"
#include "rfid_types.h"
#include "rfid_library_eng_ext.h"

#ifdef RFID_LIBRARY_H_INCLUDED
#pragma comment(lib, "rfid.lib")
#endif

#ifdef COMPILE_BIG_ENDIAN

inline INT16U MacToHost16(INT16U x) {
	return (x << 8) | (x >> 8);
}
inline INT32U MacToHost32(INT32U x) {
	return MacToHost16(x >> 16) | (MacToHost16(x) << 16);
}

#else /* not COMPILE_BIG_ENDIAN */

inline INT16U MacToHost16(INT16U x) { return x; }
inline INT32U MacToHost32(INT32U x) { return x; }

#endif /* COMPILE_BIG_ENDIAN */


#define WM_PROCESS_TAG	WM_USER + 0x0001
#define WM_TAG_ACCESS	WM_USER + 0x0002
#define WM_STATUS_MSG	WM_USER + 0x0003
#define WM_FIRMWARE_MSG	WM_USER + 0x0004
#define WM_FIRMWARE_UPDATE_START	WM_USER + 0x0005
#define WM_FIRMWARE_UPDATE_END	WM_USER + 0x0006
#define WM_RADIO_RESET	WM_USER + 0x0007

enum {
	RFID_RADIO_FIRMWARE_UPDATE_ALL	= 0x0000,
	RFID_RADIO_FIRMWARE_TEST_ONLY	= 0x0001,
	RFID_RADIO_FIRMWARE_SKIP_TEST	= 0x0002
};
typedef INT32U  RFID_RADIO_FIRMWARE_MODE;

enum
{
	RFID_TAG_DISPLAY_MODE_EPC = 0x0000,
	RFID_TAG_DISPLAY_MODE_ASCII = 0x0001
};
typedef INT32U  RFID_TAG_DISPLAY_MODE;

typedef struct
{
	RFID_PACKET_COMMON* pPacket;
	int					indent;
} RFID_RADIO_PACKET;

#include <assert.h>

#include "AThread.h"
#include "PtrListEx.h"
#include "TagInfo.h"
#include "ToolBarEx.h"
#include "StatusBarEx.h"

// string message allocator for posting messages between windows...
static char* AllocBuffer(CString strMsg)
{
	long  nLen = strMsg.GetLength();
	char *pBuffer = new char[nLen+1]; 

	wcstombs (pBuffer,strMsg,nLen); 
	pBuffer[nLen] = '\0';
//	strcpy(pBuffer,(const char*)strMsg.);
//	pBuffer = strMsg.GetBuffer(0);

	ASSERT(pBuffer != NULL);
	return pBuffer;
}


using namespace techwin;

