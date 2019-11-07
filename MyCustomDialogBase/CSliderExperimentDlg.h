#pragma once


#include "KSliderCtrl.h"


// CSliderExperimentDlg 대화 상자

class CSliderExperimentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSliderExperimentDlg)

public:
	CSliderExperimentDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSliderExperimentDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEST_CSLIDER };
#endif

protected:

	//Horizontal silder bar
	KSliderCtrl m_kSlider_1;	
	CEdit m_sliderCEdit_1;

	//Vertical slider bar
	KSliderCtrl m_kSlider_2;
	CEdit m_sliderCEdit_2;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKillFocusSlider1Edit();
	afx_msg void OnKillFocusSlider2Edit();

};
