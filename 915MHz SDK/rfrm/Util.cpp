#include "StdAfx.h"
#include "Util.h"

#include <stdio.h>

namespace techwin
{
	CUtil::CUtil(void)
	{
	}

	CUtil::~CUtil(void)
	{
	}

	__int32 CUtil::StrToWord(CString Param)//CString-> Bin숫자로 change
	{
		CString sBuffer;
		wchar_t	*cBuffer, *cStrStopString;
		_int32	Total=0, Int32Upper=0, Int32Lower=0;
		int		nStrLength;

		if (Param.GetLength() <= 8)
		{
			//get lower 32bit
			sBuffer = _T("0X") + Param;
			nStrLength = sBuffer.GetLength();
			cBuffer = sBuffer.GetBuffer(nStrLength);
			Int32Lower	= wcstoul(cBuffer, &cStrStopString, 16);
		}

		Total = Int32Lower;

		return Total;
	}

	__int64 CUtil::StrToDWord(CString Param)//CString-> Bin숫자로 change
	{
		CString sBuffer;
		wchar_t	*cBuffer, *cStrStopString;
		_int64	Total=0, Int64Upper=0, Int64Lower=0;
		int		nStrLength;

		if (Param.GetLength() > 8)
		{
			//get upper 32bit
			sBuffer = _T("0X") + Param;
			nStrLength = Param.GetLength() - 8;
			sBuffer = sBuffer.Left(nStrLength+2);
			cBuffer = sBuffer.GetBuffer(nStrLength+2);
			Int64Upper	= wcstoul(cBuffer, &cStrStopString, 16);
			//get lower 32bit
			sBuffer = Param.Mid(nStrLength);
			sBuffer = _T("0X") + sBuffer;
			cBuffer = sBuffer.GetBuffer(10);
			Int64Lower	= wcstoul(cBuffer, &cStrStopString, 16);
		}

		Total = (Int64Upper * 0x100000000) + Int64Lower;
		
		return Total;
	}

	CString	CUtil::WordToStr(WORD in)
	{
		char buff[8];
#ifndef WINCE
		sprintf_s(buff, "%u", in);
#else if
		sprintf(buff, "%u", in);
#endif
		return (CString)buff;
	}

	CString	CUtil::WordToHexStr(WORD in)
	{
		char buff[8];
#ifndef WINCE
		sprintf_s(buff, "%.8x", in);
#else if
		sprintf(buff, "%.8x", in);
#endif
		return (CString)buff;
	}


	CString	CUtil::DWordToStr(DWORD in)
	{
		char buff[16];

#ifndef WINCE
		sprintf_s(buff, "%u", in);
#else if
		sprintf(buff, "%u", in);
#endif

		return (CString)buff;
	}

	void CUtil::endian_swap(unsigned short& x)
	{
		x = (x>>8) | 
			(x<<8);
	}

	void CUtil::endian_swap(unsigned __int32& x)
	{
		x = (x>>24) | 
			((x<<8) & 0x00FF0000) |
			((x>>8) & 0x0000FF00) |
			(x<<24);
	}

	// __int64 for MSVC, "long long" for gcc
	void CUtil::endian_swap(unsigned __int64& x)
	{
		x = (x>>56) | 
			((x<<40) & 0x00FF000000000000) |
			((x<<24) & 0x0000FF0000000000) |
			((x<<8)  & 0x000000FF00000000) |
			((x>>8)  & 0x00000000FF000000) |
			((x>>24) & 0x0000000000FF0000) |
			((x>>40) & 0x000000000000FF00) |
			(x<<56);
	}

	/////////////////////////////////////////////////////////////////////
	//  char -> wchar

	wchar_t* CUtil::CharToWChar(const char* pstrSrc)
	{
		ASSERT(pstrSrc);
		int nLen = strlen(pstrSrc)+1;

		wchar_t* pwstr      = (LPWSTR) malloc ( sizeof( wchar_t )* nLen);
		mbstowcs(pwstr, pstrSrc, nLen);

		return pwstr;
	}

	/////////////////////////////////////////////////////////////////////
	// wchar -> char
	char* CUtil::WCharToChar(const wchar_t* pwstrSrc)
	{
		ASSERT(pwstrSrc);

#if !defined _DEBUG
		int len = 0;
		len = (wcslen(pwstrSrc) + 1)*2;
		char* pstr      = (char*) malloc ( sizeof( char) * len);

		WideCharToMultiByte( 949, 0, pwstrSrc, -1, pstr, len, NULL, NULL);
#else

		int nLen = wcslen(pwstrSrc);

		char* pstr      = (char*) malloc ( sizeof( char) * nLen + 1);
		wcstombs(pstr, pwstrSrc, nLen+1);
#endif

		return pstr;
	}

	DWORD CUtil::Str2Hex( CString const & s )
	{
		DWORD result = 0;

		for ( int i = 0; i < s.GetLength(); i++ )
		{
			if ( isdigit( s[ i ] ) )
			{
				result = result * 16 + ( s[ i ] - '0' );
			}
			else // if ( isxdigit( s[ i ] ) )
			{
				result = result * 16 + ( s[ i ] - 'a' + 10 ); 
			}
		}

		return result;
	}

	CString CUtil::Hex2Str( const INT8U *bytes, int length)
	{
		int index;
		CString stemp, str; 
		str = "";

		for (index = 0; index < length; ++index)
		{
			//		stemp.Format(_T("%s%.2x"), (index && !(index % 4)) ? _T(" ") : _T(""), bytes[index]);
			stemp.Format(_T("%.2x"), bytes[index]);
			str += stemp;
		}

		str.MakeUpper();

		return str;
	}


};