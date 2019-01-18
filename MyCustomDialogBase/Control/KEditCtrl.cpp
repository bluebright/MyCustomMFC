#include "KEditCtrl.h"


BEGIN_MESSAGE_MAP(KEditCtrl, CEdit)
END_MESSAGE_MAP()


void KEditCtrl::BreakLineFromCursor()
{
	SetFocus();
	CPoint caretPoint = GetCaretPos();
	int caretPos = CharFromPos(caretPoint);

	SetSel(caretPos, caretPos);
	ReplaceSel(_T("\r\n"));
	SetFocus();
}

void KEditCtrl::AppendText(LPCTSTR pText) {
	int textLength = GetWindowTextLength();

	SetFocus();
	SetSel(textLength, textLength);
	ReplaceSel(pText);
	SetFocus();
}

void KEditCtrl::MoveCursorToEnd() {
	
}

void KEditCtrl::ClearAll() {
	SetSel(0, -1, TRUE);
	Clear();
}

