// CEditExperimentDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MyCustomDialogBase.h"
#include "CEditExperimentDlg.h"
#include "afxdialogex.h"


// CEditExperimentDlg 대화 상자

IMPLEMENT_DYNAMIC(CEditExperimentDlg, CDialogEx)

CEditExperimentDlg::CEditExperimentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TEST_CEDIT, pParent)
{

}

CEditExperimentDlg::~CEditExperimentDlg()
{
}

void CEditExperimentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEditExperimentDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_APPEND_TEXT, &CEditExperimentDlg::OnBnClickedBtnAppendText)
	ON_BN_CLICKED(IDC_BTN_MOVE_CURSOR_1, &CEditExperimentDlg::OnBnClickedBtnMoveCursor1)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CEditExperimentDlg::OnBnClickedBtnClear)
END_MESSAGE_MAP()


// CEditExperimentDlg 메시지 처리기

BOOL CEditExperimentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	edit_multiline = (KEditCtrl *)GetDlgItem(IDC_EDIT1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CEditExperimentDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
		{
			CWnd *focusCwnd = GetFocus();

			if(focusCwnd == edit_multiline)
				edit_multiline->BreakLineFromCursor();							
		}
		return TRUE;
		case VK_ESCAPE:
			return TRUE;
		default:
			break;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CEditExperimentDlg::OnBnClickedBtnAppendText()
{
	UpdateData(TRUE);
	edit_multiline->AppendText(_T("What"));
	edit_multiline->AppendText(_T(" A 띠리띠리\n가"));
}


void CEditExperimentDlg::OnBnClickedBtnMoveCursor1()
{
	UpdateData(TRUE);

}


void CEditExperimentDlg::OnBnClickedBtnClear()
{
	edit_multiline->ClearAll();
}
