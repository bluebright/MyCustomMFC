#pragma once

#ifndef _CUSTOM_STRING_PARSER_H_
#define _CUSTOM_STRING_PARSER_H_

#include <string>
#include <vector>
#include <atlstr.h>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

/*
@see http://www.cplusplus.com/reference/cctype/isspace/
*/
#define TRIM_SPACE " \t\n\v\f\r"

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
	* TODO!! Warning!! This method has error when delimiter contain space.
	*
	* Tokenize CString
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

	
	/*
	
	*/
	static inline std::string trimDelimiter(std::string& s, const std::string& drop = TRIM_SPACE)
	{
		std::string r = s.erase(s.find_last_not_of(drop) + 1);
		return r.erase(0, r.find_first_not_of(drop));
	}
	
	/*
	
	*/
	static inline std::string rtrimDelimiter(std::string s, const std::string& drop = TRIM_SPACE)
	{
		return s.erase(s.find_last_not_of(drop) + 1);
	}
	
	/*
	
	*/
	static inline std::string ltrimDelimiter(std::string s, const std::string& drop = TRIM_SPACE)
	{
		return s.erase(0, s.find_first_not_of(drop));
	}

	/**
	* Split string with string delimiter.
	* Delimiters can contain spaces. like " : "

	@see https://ospace.tistory.com/114
	@see https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
	@see http://www.martinbroadhurst.com/how-to-trim-a-stdstring.html
	* 
	*/
	static void StdStrTokenize(const std::string& str, std::vector<std::string>& tokens, bool enableTrim, const std::string& delimiters)
	{

		try
		{						
			size_t delimitersLength = delimiters.length();

			if (delimitersLength <= 0) 
			{
				//TODO Need to throw exception
				return;
			}

			size_t start = 0U;
			size_t end = str.find(delimiters);

			//Ignore if the first sentence is a delimiter
			if (end == start)
			{
				start = end + delimitersLength;
				end = str.find(delimiters, start);
			}

			while (end != std::string::npos)
			{
				std::string token = str.substr(start, end - start);
				tokens.push_back(token);

				start = end + delimitersLength;
				end = str.find(delimiters, start);
			}

			std::string lastToken = str.substr(start, end);	

			if (enableTrim) 
			{
				lastToken = trimDelimiter(lastToken);
			}
						
			if (lastToken.length() > 0)
			{				
				tokens.push_back(lastToken);
			}
						
			//Process trim
			if (enableTrim)
			{
				//Exclude last token
				int tokensLength = tokens.size() - 1;

				for (int i = 0; i < tokensLength; i++) {
					tokens.at(i) = trimDelimiter(tokens.at(i));
				}
			
			}
			
		}
		catch (const std::exception ex)
		{
			
		}
	}		
		

			
};
#endif // !_CUSTOM_STRING_PARSER_H_

