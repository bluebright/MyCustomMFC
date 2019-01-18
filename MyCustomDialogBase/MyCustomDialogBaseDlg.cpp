
// MyCustomDialogBaseDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MyCustomDialogBase.h"
#include "MyCustomDialogBaseDlg.h"
#include "afxdialogex.h"

#include "KTypeCaster.h"
#include "KFileFunc.h"
#include "CSVIterator.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyCustomDialogBaseDlg 대화 상자



CMyCustomDialogBaseDlg::CMyCustomDialogBaseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYCUSTOMDIALOGBASE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyCustomDialogBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, k_tree_ctrl);
}

BEGIN_MESSAGE_MAP(CMyCustomDialogBaseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMyCustomDialogBaseDlg::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_BTN_INSERT, &CMyCustomDialogBaseDlg::OnBnClickedBtnInsert)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CMyCustomDialogBaseDlg::OnBnClickedBtnDelete)
	ON_BN_CLICKED(IDC_BTN_TEST, &CMyCustomDialogBaseDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_CREATE_FOLDER, &CMyCustomDialogBaseDlg::OnBnClickedBtnCreateFolder)
	ON_BN_CLICKED(IDC_BTN_TEST_CONVERT, &CMyCustomDialogBaseDlg::OnBnClickedBtnTestConvert)
	ON_BN_CLICKED(IDC_BTN_PARSE, &CMyCustomDialogBaseDlg::OnBnClickedBtnParse)
	ON_BN_CLICKED(IDC_BTN_CEDIT_DLG, &CMyCustomDialogBaseDlg::OnBnClickedBtnCeditDlg)
END_MESSAGE_MAP()


// CMyCustomDialogBaseDlg 메시지 처리기

BOOL CMyCustomDialogBaseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	h_root = k_tree_ctrl.InsertItem(_T("TREE ROOT!"), 0, TVI_ROOT);
	test_number = 0;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMyCustomDialogBaseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMyCustomDialogBaseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMyCustomDialogBaseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CMyCustomDialogBaseDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
		case VK_ESCAPE:
			return TRUE;
		default:
			break;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMyCustomDialogBaseDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_TREEVIEW *p_nm_tree_view = (NM_TREEVIEW *)pNMHDR;

	HTREEITEM tree_item = p_nm_tree_view->itemNew.hItem;


	if (tree_item == NULL)
	{
		//*pResult = -1;
		return;
	}
	else if (k_tree_ctrl.GetParentItem(tree_item) == NULL)
	{
		//*pResult = -1;
		return;
	}

	/*TVITEM tvItem;
	tvItem.mask = TVIF_PARAM;
	tvItem.hItem = tree_item;
	data_tree.GetItem(&tvItem);
	MyData *p_my_data = (MyData *)tvItem.lParam;*/

	MyData* p_my_data = (MyData *)k_tree_ctrl.GetItemData(tree_item);

	int item_idx = k_tree_ctrl.GetItemOrderFromParent(&tree_item);

	AfxMessageBox(KTypeCaster::CstFormat(_T("%s / item idx : %d"), p_my_data->GetName(), item_idx));

	p_my_data = NULL;

	*pResult = 0;
}


void CMyCustomDialogBaseDlg::OnBnClickedBtnInsert()
{
	test_number = ++test_number % 100;

	MyData *my_data = new MyData(test_number);

	CString name_cst = my_data->GetName();

	/*
	HTREEITEM inserted_item = data_tree.InsertItem(name_cst, h_root);
	data_tree.SetItemData(inserted_item, (DWORD_PTR) my_data);
	*/

	TV_INSERTSTRUCT insert_struct;
	insert_struct.hParent = h_root;
	insert_struct.hInsertAfter = TVI_LAST;
	insert_struct.item.mask = LVIF_TEXT | LVIF_PARAM;
	insert_struct.item.pszText = name_cst.GetBuffer(0);
	//insert_struct.item.iImage = 0;
	//insert_struct.item.iSelectedImage = 0;
	insert_struct.item.state = 0;
	insert_struct.item.stateMask = 0;
	insert_struct.item.lParam = (LPARAM)my_data;

	k_tree_ctrl.InsertItem(&insert_struct);


	k_tree_ctrl.Expand(h_root, TVE_EXPAND);
}


void CMyCustomDialogBaseDlg::OnBnClickedBtnDelete()
{
	HTREEITEM hNextItem;
	HTREEITEM hChildItem = k_tree_ctrl.GetChildItem(h_root);

	while (hChildItem != NULL)
	{
		hNextItem = k_tree_ctrl.GetNextItem(hChildItem, TVGN_NEXT);
		k_tree_ctrl.DeleteItem(hChildItem);
		hChildItem = hNextItem;
	}
}


void CMyCustomDialogBaseDlg::OnBnClickedBtnTest()
{
	CString msg;

	/*
	//Test block 1
	HTREEITEM child = NULL;
	BOOL result = k_tree_ctrl.GetChildItemFromParent(&h_root, &child, 4);

	if (result) {
		MyData* tree_item_data = (MyData *)k_tree_ctrl.GetItemData(child);
		msg = KTypeCaster::CstFormat(msg = _T("Find child !!\n%s"), tree_item_data->GetName());
	}
	else {
		msg = _T("Find error!!\nNot contain or index out of bound !!");
	}
	*/

	//Test block 2
	/*
	MyData tree_item_data = NULL;
	BOOL result = k_tree_ctrl.GetChildItemDataFromParent(&h_root, tree_item_data, 4);

	if (result) {
		msg = KTypeCaster::CstFormat(msg = _T("Find child !!\n%s"), tree_item_data.GetName());
	}
	else {
		msg = _T("Find error!!\nNot contain or index out of bound !!");
	}
	*/

	//Test block 3
	/**/
	MyData *tree_item_data = NULL;
	BOOL result = k_tree_ctrl.GetChildItemDataFromParent_P(&h_root, &tree_item_data, 4);

	if (result) {		
		msg = KTypeCaster::CstFormat((_T("Find child !!\n%s")), tree_item_data->GetName());
	}
	else {
		msg = _T("Find error!!\nNot contain or index out of bound !!");
	}

	AfxMessageBox(msg);
}


void CMyCustomDialogBaseDlg::OnBnClickedBtnCreateFolder()
{

}


void CMyCustomDialogBaseDlg::OnBnClickedBtnTestConvert()
{
	//문자 집합(유니코드, 멀티바이트)이 다를 경우
	//사용해야 하는 함수가 다를 수 있음
	//For test in Visual studio 2017 (Unicode)

	CString cstr(_T("나는 CString"));
	std::string str("나는 string");
	std::wstring wstr(_T("나는 wstring"));

	CString cst_int = _T("141432");
	CString cst_double = _T("141432.55");
	DWORD dword = 314159; //DWORD 사이즈는 4byte (LONG으로 변환)

	int number = 119;
	double    double_num = 3.14159265358979;


	///////////////////////////////////////////////////
	//To Cstring///////////////////////////////////////

	// CString <- std::string
	CString cstr2 = KTypeCaster::ConvertString_StdStr2Cstr(str);
	CString cstr3 = KTypeCaster::ConvertString_StdStr2Cstr_2(str);

	// CString <- std::wstring
	CString cstr4 = wstr.c_str();

	// CString <- int
	CString cstr5 = KTypeCaster::CstFormat(_T("Integer : %d"), number);

	// CString <- double
	CString cstr6 = KTypeCaster::CstFormat(_T("Double : %f"), double_num);

	/////////////////////////////////////////////////


	///////////////////////////////////////////////////
	//LPTSTR <- CString////////////////////////////////

	CString cstr7 = _T("This is a test");
	LPTSTR lpTstr;
	KTypeCaster::ConverString_Cstr2Lptstr(cstr7, &lpTstr);
	delete lpTstr;
	///////////////////////////////////////////////////


	//////////////////////////////////////////////////
	//To std::wstring/////////////////////////////////

	// std::wstring <- CString
	std::wstring wstr2 = KTypeCaster::ConvertString_Cstr2StdWstr(cstr);
	std::wstring wstr3 = cstr.GetBuffer(0);

	// std::wstring <- std::string
	std::wstring wstr4 = KTypeCaster::ConvertString_StdStr2StdWstr(str);
	std::wstring wstr5 = KTypeCaster::ConvertString_StdStr2StdWstr_2(str);    //std::string -> LPCTSTR

	/////////////////////////////////////////////////



	//////////////////////////////////////////////////
	//To std::string/////////////////////////////////

	// std::string <- CString
	std::string str2 = KTypeCaster::ConvertString_Cstr2StdStr(cstr);

	// std::string <- std::wstring
	std::string str3 = KTypeCaster::ConvertString_StdWstr2StdStr(wstr);

	/////////////////////////////////////////////////		



	//////////////////////////////////////////////////
	//To LPWSTR/////////////////////////////////

	// LPWSTR <- CString
	LPWSTR lpwstr = (LPWSTR)(LPCTSTR)cstr;

	/////////////////////////////////////////////////


	 //////////////////////////////////////////////////
	//To const char* /////////////////////////////////

	/*
	const char* <- std::string
	@see http://www.techiedelight.com/convert-std-string-const-char-cpp/
	*/

	// const char* <- std::string
	const char *c_char_1 = str.c_str();
	const char *c_char_2 = str.data();

	// const char* <- std::string (over C++11)
	const char *c_char_3 = &str[0];
	const char *c_char_4 = &*str.begin();

	// const char* <- CString
	const char *c_char_5 = (CStringA)cstr;

	/////////////////////////////////////////////////


	 //////////////////////////////////////////////////
	//To DWORD //////////////////////////////////////

	// DWORD <- CString
	DWORD dword2 = KTypeCaster::Convert_Cstr2Dword(cst_int);

	// CString <- DWORD
	CString cst_number2 = KTypeCaster::CstFormat(_T("%lu"), (ULONG)dword);

	/////////////////////////////////////////////////



	//////////////////////////////////////////////////
	//To integer/////////////////////////////////////

	// int <- CString
	int number_2 = KTypeCaster::Convert_Cstr2Int(cst_int);


	////////////////////////////////////////////////



	//////////////////////////////////////////////////
	//To double/////////////////////////////////////

	// double <- CString
	double double_num_2 = KTypeCaster::Convert_Cstr2Double(cst_double);


	////////////////////////////////////////////////

}


void CMyCustomDialogBaseDlg::OnBnClickedBtnParse()
{
	std::ifstream file("test.csv");

	int row_count = 0;
	for (CSVIterator loop(file); loop != CSVIterator(); ++loop) {

		CSVRow row = (*loop);
		int row_size = (int)row.size();

		for (int i = 0; i < row_size; i++) {
			CString rowText = KTypeCaster::ConvertString_StdStr2Cstr(row[i]);
			OutputDebugStringW(KTypeCaster::CstFormat(_T("%d : %s\n"), row_count, rowText));
		}

		row_count++;
	}
}


void CMyCustomDialogBaseDlg::OnBnClickedBtnCeditDlg()
{
	CEditExperimentDlg experimentDlg;
	experimentDlg.DoModal();
}