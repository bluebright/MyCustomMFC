#pragma once

#ifndef _MY_DATA_H_
#define _MY_DATA_H_

#include <SDKDDKVer.h>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

//If remove this header, complier occur LNK2019 error
#include <afxwin.h>
//#include <atlstr.h>


class MyData {

public:
	MyData(int number);

	int GetNumber();

	CString GetName();

	void SetName(CString name);

private:
	int number;

	CString name;

};

#endif // _MY_DATA_H_