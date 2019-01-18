#pragma once

#ifndef _FILE_FUNC_H_
#define _FILE_FUNC_H_

#include <fileapi.h>
#include <KStringParser.h>
#include <vector>

#define PATH_SEPARATOR	_T("\\")

class KFileFunc {

public:

	/**
	* Create directory. This function call "CreateDirectory" many times
	*
	* Warning! Need to string check for file name. (ex : ?, :, etc)
	*/
	static BOOL CreateDirectoryRepeat(CString targetPath) {

		std::vector<CString> tokens;
		KStringParser::CStrTokenize(targetPath, tokens, PATH_SEPARATOR);

		CString pathAssembleBuffer;
		int tokenSize = (int)tokens.size() - 1;
		int i = 0;
		BOOL isPathValid = FALSE;

		for (; i < tokenSize; i++)
		{
			pathAssembleBuffer.Append(tokens[i]);
			CreateDirectory(pathAssembleBuffer, NULL);

			isPathValid = PathIsDirectory(pathAssembleBuffer);
			if (!isPathValid) {
				return FALSE;
			}
			else {//PathAddBackslash()
				pathAssembleBuffer.Append(PATH_SEPARATOR);
			}
		}

		if (isPathValid && (i == tokenSize)) {
			pathAssembleBuffer.Append(tokens[i]);
			CreateDirectory(pathAssembleBuffer, NULL);

			isPathValid = PathIsDirectory(pathAssembleBuffer);
		}

		return isPathValid;
	}

};

#endif // !_FILE_FUNC_H_
