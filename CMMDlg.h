#pragma once


// CMMDlg 对话框

class CMMDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMMDlg)

public:
	CMMDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMMDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_csm;
	CString m_xgm;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
