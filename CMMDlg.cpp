// CMMDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication5.h"
#include "CMMDlg.h"
#include "afxdialogex.h"
#include "MFCApplication5Dlg.h"

// CMMDlg 对话框

IMPLEMENT_DYNAMIC(CMMDlg, CDialogEx)

CMMDlg::CMMDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_csm(_T(""))
{

}

CMMDlg::~CMMDlg()
{
}

void CMMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_csm);
	DDX_Text(pDX, IDC_EDIT2, m_xgm);
}


BEGIN_MESSAGE_MAP(CMMDlg, CDialogEx)


	ON_BN_CLICKED(IDOK, &CMMDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMMDlg 消息处理程序



void CMMDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}


BOOL CMMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
