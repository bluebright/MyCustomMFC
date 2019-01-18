
// MyCustomDialogBaseDlg.h: 헤더 파일
//

#pragma once
#include "CEditExperimentDlg.h"
#include "KTreeCtrl.h" 
#include "MyData.h"

// CMyCustomDialogBaseDlg 대화 상자
class CMyCustomDialogBaseDlg : public CDialogEx
{
// 생성입니다.
public:
	CMyCustomDialogBaseDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYCUSTOMDIALOGBASE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	int test_number;
	KTreeCtrl<MyData> k_tree_ctrl;
	HTREEITEM h_root;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedBtnInsert();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedBtnTest();
	afx_msg void OnBnClickedBtnCreateFolder();
	afx_msg void OnBnClickedBtnTestConvert();
	afx_msg void OnBnClickedBtnParse();
	DECLARE_MESSAGE_MAP()

public:


	afx_msg void OnBnClickedBtnCeditDlg();
};
