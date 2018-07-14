#pragma once

namespace techwin
{
	class CUtil
	{
	public:
		CUtil(void);
		virtual ~CUtil(void);

		static __int32	StrToWord(CString Param);
		static __int64	StrToDWord(CString Param);
		static CString	WordToStr(WORD in);
		static CString	WordToHexStr(WORD in);
		static CString	DWordToStr(DWORD in);
		static void		endian_swap(unsigned short& x);
		static void		endian_swap(unsigned __int32& x);
		// __int64 for MSVC, "long long" for gcc
		static void		endian_swap(unsigned __int64& x);
		static wchar_t* CharToWChar(const char* pstrSrc);
		static char* WCharToChar(const wchar_t* pwstrSrc);
		static DWORD Str2Hex( CString const & s );
		static CString Hex2Str( const INT8U *bytes, int length);
	};

};
