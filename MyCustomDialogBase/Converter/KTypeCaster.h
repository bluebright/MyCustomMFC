#pragma once

#ifndef _TYPE_CASTER_H_
#define _TYPE_CASTER_H_

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <atlstr.h>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS


class KTypeCaster {

public:

	/*
	CString formating

	This code block
	{@code
		int num = 32
		CString strTemp;
		strTemp.Format(_T("I am the %d years old"), nYear);
		AfxMessageBox(strTemp);
	}

	can change to
	{@code
		int nYear = 32
		AfxMessageBox(CstFormat(_T("I am the %d years old"), nYear));
	}

	@see http://blog.daum.net/kwonjunsung/34
	*/

	static CString CstFormat(const CString strMsg, ...)
	{
		CString strRet;
		va_list valist;

		va_start(valist, strMsg);
		strRet.FormatV(strMsg, valist);
		va_end(valist);

		return strRet;
	}

	// CString <- std::string
	static CString ConvertString_StdStr2Cstr(const std::string src) {
		CString result = CA2CT(src.c_str());
		return result;
	}

	// CString <- std::string
	static CString ConvertString_StdStr2Cstr_2(const std::string src) {
		return CString(src.c_str());
	}

	/*
	// LPTSTR <- CString
	 @see https://docs.microsoft.com/ko-kr/cpp/atl-mfc-shared/cstring-operations-relating-to-c-style-strings
	!!Need to delete when program exit!!
	*/
	static void ConverString_Cstr2Lptstr(const CString src, LPTSTR *result) {
		int sizeOfString = src.GetLength() + 1;
		*result = new TCHAR[sizeOfString];
		_tcscpy_s(*result, sizeOfString, src);
	}


	/*
	std:wstring <- std::string
	*/
	static std::wstring ConvertString_StdStr2StdWstr(const std::string src) {
		std::wstring result = CA2CT(src.c_str());
		return result;
	}


	/**
	 std:wstring <- std::string

	{@code
		string = "COM3";
		wstring stemp;
		LPCWSTR result_port;
		stemp = s2ws(port_nr);
		result_port = stemp.c_str(); // now passing result_port to my function i am getting success
	}
	@see https://stackoverflow.com/a/22713047/7017299 (std::string -> LPCTSTR)

	*/
	static std::wstring ConvertString_StdStr2StdWstr_2(const std::string &source)
	{
		int soureLength = (int)source.length() + 1;
		int len = MultiByteToWideChar(CP_ACP, 0, source.c_str(), soureLength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, source.c_str(), soureLength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		return r;
	}


	/*
	 std:wstring <- CString
	*/
	static std::wstring ConvertString_Cstr2StdWstr(const CString src) {
		std::wstring result = src.operator LPCWSTR();
		return result;
	}

	//std::string <- std::wstring
	static std::string ConvertString_StdWstr2StdStr(const std::wstring src) {
		std::string result = CT2CA(src.c_str());
		return result;
	}

	//std::string <- CString
	static std::string ConvertString_Cstr2StdStr(const CString src) {
		std::string result = CT2CA(src.operator LPCWSTR());
		return result;
	}

	//std::string <- TCHAR *
	static std::string ConvertString_Tchar2StdStr(const TCHAR* ptsz)
	{
		CString result_cst(ptsz);
		return ConvertString_Cstr2StdStr(result_cst);
	}


#ifdef UNICODE
	static DWORD Convert_Cstr2Dword(CString src) {
		DWORD result = _ttol(src);
		return result;
	}

	static int Convert_Cstr2Int(CString src) {
		int result = _ttoi(src);
		return result;
	}

	static double Convert_Cstr2Double(CString src) {
		double result = _wtof(src);
		return result;
	}
#else
	static DWORD Convert_Cstr2Dword(CString src) {
		DWORD result = atol(src);
		return result;
	}

	static int Convert_Cstr2Int(CString src) {
		int result = atoi(src);
		return result;
	}

	static double Convert_Cstr2Double(CString src) {
		double result = atof(src);
		return result;
	}

#endif // !UNICODE





	/*
	typedef struct _CART2SCREEN {
		int cartX;
		int cartY;
		int screenX;
		int screenY;


		_CART2SCREEN(int cartX, int cartY, int screenX, int screenY)
			: cartX(cartX), cartY(cartY), screenX(screenX), screenY(screenY) {
		}

		_CART2SCREEN(int cart_X, int cart_Y, int zoom_Factor, int screen_Width, int screen_Height)
			: cartX(cartX), cartY(cartY) {
			screenX = cartesian2screenX(cart_X, zoom_Factor, screen_Width);
			screenY = cartesian2screenY(cart_Y, zoom_Factor, screen_Height);
		}

		int cartesian2screenX(int cart_X, int zoom_Factor, int screen_Width) {
			return (zoom_Factor * cart_X) + (screen_Width / 2);
		}

		int cartesian2screenY(int cart_Y, int zoom_Factor, int screen_Height) {
			return (screen_Height / 2) - (zoom_Factor * cart_Y);
		}

		int screen2CartesianX(int screen_X, int zoom_Factor, int screen_Width) {
			return (screen_X - screen_Width / 2)/ zoom_Factor;
		}

		int screen2CartesianY(int screen_Y, int zoom_Factor, int screen_Height) {
			return (-screen_Y + screen_Height / 2) / zoom_Factor;
		}
	}CART2SCREEN;


	typedef struct _CART2SCREEN_LA {
		int cartX;
		int cartY;
		int screenX;
		int screenY;

		_CART2SCREEN_LA()
			: cartX(0), cartY(0), screenX(0), screenY(0)
		{}

		_CART2SCREEN_LA(int cartX, int cartY, int screenX, int screenY)
			: cartX(cartX), cartY(cartY), screenX(screenX), screenY(screenY) {
		}

		_CART2SCREEN_LA(int cart_X, int cart_Y, int zoom_Factor, int screen_Width, int screen_Height)
			: cartX(cartX), cartY(cartY) {

			screenX = cartesian2screenX(cart_X, zoom_Factor, screen_Width);
			screenY = cartesian2screenY(cart_Y, zoom_Factor, screen_Height);
		}

		int cartesian2screenX(int cart_X, int zoom_Factor, int screen_Width) {
			return (zoom_Factor * cart_X);
		}

		int cartesian2screenY(int cart_Y, int zoom_Factor, int screen_Height) {
			return (screen_Height / 2) - (zoom_Factor * cart_Y);
		}

		int screen2CartesianX(int screen_X,int zoom_Factor, int screen_Width)	{
			return screen_X / zoom_Factor;
		}

		int screen2CartesianY(int screen_Y, int zoom_Factor, int screen_Height)	{
			return (-screen_Y + screen_Height / 2) / zoom_Factor;
		}

	}CART2SCREEN_LA;
	*/

	};
#endif // !_TYPE_CASTER_H_