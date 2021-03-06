#pragma once


#include "KEditCtrl.h" //#include "..\..\Source\KEditCtrl.h"


// CEditExperimentDlg 대화 상자

class CEditExperimentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditExperimentDlg)

public:
	CEditExperimentDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CEditExperimentDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEST_CEDIT };
#endif

protected:
	KEditCtrl *edit_multiline;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnBnClickedBtnAppendText();
	afx_msg void OnBnClickedBtnMoveCursor1();
	afx_msg void OnBnClickedBtnClear();
};


