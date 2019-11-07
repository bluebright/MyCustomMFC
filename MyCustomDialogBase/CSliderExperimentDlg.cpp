// CSliderExperimentDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MyCustomDialogBase.h"
#include "CSliderExperimentDlg.h"
#include "afxdialogex.h"
#include "KTypeCaster.h"


// CSliderExperimentDlg 대화 상자

IMPLEMENT_DYNAMIC(CSliderExperimentDlg, CDialogEx)

CSliderExperimentDlg::CSliderExperimentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TEST_CSLIDER, pParent)
{

}

CSliderExperimentDlg::~CSliderExperimentDlg()
{

}

void CSliderExperimentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEST_SLIDER_1, m_kSlider_1);
	DDX_Control(pDX, IDC_TEST_SLIDER_2, m_kSlider_2);
	DDX_Control(pDX, IDC_TEST_SLIDER_EDIT_1, m_sliderCEdit_1);
	DDX_Control(pDX, IDC_TEST_SLIDER_EDIT_2, m_sliderCEdit_2);
}


BEGIN_MESSAGE_MAP(CSliderExperimentDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_EN_KILLFOCUS(IDC_TEST_SLIDER_EDIT_1, &CSliderExperimentDlg::OnKillFocusSlider1Edit)
	ON_EN_KILLFOCUS(IDC_TEST_SLIDER_EDIT_2, &CSliderExperimentDlg::OnKillFocusSlider2Edit)
	
END_MESSAGE_MAP()


// CSliderExperimentDlg 메시지 처리기


BOOL CSliderExperimentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_kSlider_1.SetRange(0, 200);
	m_kSlider_1.SetPos(40);
	m_kSlider_1.SetTicFreq(10);
	m_kSlider_1.SetLineSize(5);
	m_kSlider_1.SetPageSize(10);

	m_sliderCEdit_1.SetWindowText(KTypeCaster::CstFormat(_T("%d"), m_kSlider_1.GetPos()));

	m_kSlider_2.SetRange(0, 200);
	m_kSlider_2.SetPos(40);
	m_kSlider_2.SetTicFreq(10);
	m_kSlider_2.SetLineSize(5);
	m_kSlider_2.SetPageSize(10);

	m_sliderCEdit_2.SetWindowText(KTypeCaster::CstFormat(_T("%d"), m_kSlider_2.GetPos()));


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSliderExperimentDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar) {
		if (pScrollBar->GetDlgCtrlID() == IDC_TEST_SLIDER_1) {
			CString str;
			CString buf;
			int npos;

			switch (nSBCode)
			{
			case SB_LEFT:      // Scroll to far left.
				OutputDebugString(_T("H : SB_LEFT\n"));
				break;
			case SB_RIGHT:      // Scroll to far right.
				OutputDebugString(_T("H : SB_RIGHT\n"));
				break;
			case SB_LINELEFT:      // Scroll left.
				OutputDebugString(_T("H : SB_LINE_LEFT\n"));
				break;
			case SB_LINERIGHT:   // Scroll right.
				OutputDebugString(_T("H : SB_LINE_RIGHT\n"));
				break;
			case SB_PAGELEFT:    // Scroll one page left.	
				OutputDebugString(_T("H : SB_PAGE_LEFT\n"));
				break;
			case SB_PAGERIGHT:      // Scroll one page right.
				OutputDebugString(_T("H : SB_PAGE_RIGHT\n"));
				break;
			case SB_THUMBTRACK:
				OutputDebugString(_T("H : SB_THUMBTRACK\n"));
				break;
			case SB_THUMBPOSITION:
				OutputDebugString(_T("H : SB_THUMBPOSITION\n"));
				break;
			default:
				OutputDebugString(_T("H : Slider Default\n"));
				break;
			case SB_ENDSCROLL:
				OutputDebugString(_T("H : SB_ENDSCROLL\n"));
								
				npos = m_kSlider_1.GetPos();
				str.Format(_T("%d"), npos);

				m_sliderCEdit_1.SetWindowText(str);
				UpdateData(false);
				break;
			}

		}
	}
	else {

	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSliderExperimentDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar) {
		if (pScrollBar->GetDlgCtrlID() == IDC_TEST_SLIDER_2) {
			CString str;
			CString buf;
			int npos;

			switch (nSBCode)
			{
			case SB_LEFT:      // Scroll to far left.
				OutputDebugString(_T("V : SB_LEFT\n"));
				break;
			case SB_RIGHT:      // Scroll to far right.
				OutputDebugString(_T("V : SB_RIGHT\n"));
				break;
			case SB_LINELEFT:      // Scroll left.
				OutputDebugString(_T("V : SB_LINE_LEFT\n"));
				break;
			case SB_LINERIGHT:   // Scroll right.
				OutputDebugString(_T("V : SB_LINE_RIGHT\n"));
				break;
			case SB_PAGELEFT:    // Scroll one page left.	
				OutputDebugString(_T("V : SB_PAGE_LEFT\n"));
				break;
			case SB_PAGERIGHT:      // Scroll one page right.
				OutputDebugString(_T("V : SB_PAGE_RIGHT\n"));
				break;
			case SB_THUMBTRACK:
				OutputDebugString(_T("V : SB_THUMBTRACK\n"));
				break;
			case SB_THUMBPOSITION:
				OutputDebugString(_T("V : SB_THUMBPOSITION\n"));
				break;
			default:
				OutputDebugString(_T("V : Slider Default\n"));
				break;
			case SB_ENDSCROLL:
				OutputDebugString(_T("V : SB_ENDSCROLL\n"));

				npos = m_kSlider_2.GetPos();
				str.Format(_T("%d"), npos);

				m_sliderCEdit_2.SetWindowText(str);
				UpdateData(false);
				break;
			}

		}
	}
	else {

	}

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CSliderExperimentDlg::OnKillFocusSlider1Edit()
{
	CString spos;
	m_sliderCEdit_1.GetWindowText(spos);
	int iPos = _ttoi(spos);


	int sliderRangeMin = m_kSlider_1.GetRangeMin();
	int sliderRangeMax = m_kSlider_1.GetRangeMax();

	if (iPos < sliderRangeMin) {
		iPos = sliderRangeMin;
	}
	else if (iPos > sliderRangeMax) {
		iPos = sliderRangeMax;
	}
	else
		;

	m_kSlider_1.SetPos(iPos);

	m_sliderCEdit_1.SetWindowText(KTypeCaster::CstFormat(_T("%d"),iPos));

	UpdateData(false);
}

void CSliderExperimentDlg::OnKillFocusSlider2Edit()
{
	CString spos;
	m_sliderCEdit_2.GetWindowText(spos);
	int iPos = _ttoi(spos);


	int sliderRangeMin = m_kSlider_2.GetRangeMin();
	int sliderRangeMax = m_kSlider_2.GetRangeMax();

	if (iPos < sliderRangeMin) {
		iPos = sliderRangeMin;
	}
	else if (iPos > sliderRangeMax) {
		iPos = sliderRangeMax;
	}
	else
		;

	m_kSlider_2.SetPos(iPos);

	m_sliderCEdit_2.SetWindowText(KTypeCaster::CstFormat(_T("%d"), iPos));

	UpdateData(false);
}

