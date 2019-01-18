#pragma once

#ifndef _K_EDIT_CTRL_H_
#define _K_EDIT_CTRL_H_

#include <afxwin.h>

class KEditCtrl : public CEdit {

public:
	/**
	Code from http://mainia.tistory.com/599
	Change line (Carrage return ?) from current cursor in CEdit
	*/
	void BreakLineFromCursor();
	
	void AppendText(LPCTSTR pText);

	void MoveCursorToEnd();

	void ClearAll();

protected:

	DECLARE_MESSAGE_MAP()
};
#endif // !_K_EDIT_CTRL_H_
