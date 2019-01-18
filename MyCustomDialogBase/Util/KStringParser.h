#pragma once

#ifndef _CUSTOM_STRING_PARSER_H_
#define _CUSTOM_STRING_PARSER_H_

#include <string>
#include <vector>
#include <atlstr.h>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

class KStringParser {

public:
	/**
	Using "AfxExtractSubString" function

	BOOL AFXAPI AfxExtractSubString(
		CString& rString,
		LPCTSTR lpszFullString,
		int iSubString,
		TCHAR chSep = '\n'
	);

	*@see https://msdn.microsoft.com/ko-kr/library/aa991543.aspx
	*/
	

	/**
	*@see https://gist.github.com/Legor/1231475
	*/
	static void StdStrTokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters)
	{
		//tokens.clear();

		// 맨 첫 글자가 구분자인 경우 무시
		std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
		// 구분자가 아닌 첫 글자를 찾는다
		std::string::size_type pos = str.find_first_of(delimiters, lastPos);

		while (std::string::npos != pos || std::string::npos != lastPos)
		{
			// token을 찾았으니 vector에 추가한다
			tokens.push_back(str.substr(lastPos, pos - lastPos));
			// 구분자를 뛰어넘는다.  "not_of"에 주의하라
			lastPos = str.find_first_not_of(delimiters, pos);
			// 다음 구분자가 아닌 글자를 찾는다
			pos = str.find_first_of(delimiters, lastPos);
		}
	}

	/**
	*Tokenize CString
	*/
	static void CStrTokenize(const CString& srcCst, std::vector<CString>& tokens, const CString& delimiters)
	{
		int cursorPosition = 0;
		CString outToken = srcCst.Tokenize(delimiters, cursorPosition);
		
		while (!outToken.IsEmpty()) {		
			tokens.push_back(outToken);
			outToken = srcCst.Tokenize(delimiters, cursorPosition);
		}	
	}

};
#endif // !_CUSTOM_STRING_PARSER_H_

