
// MFCApplication5Dlg.h: 头文件
//

#pragma once


// CMFCApplication5Dlg 对话框
class CMFCApplication5Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication5Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION5_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_bflb; // 播放列表
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	BOOL m_zzbf; // 是否正在播放
	BOOL StopPlay();
	TCHAR m_gqqm[MAX_PATH]; // 歌曲全名
	TCHAR m_gqdm[MAX_PATH]; // 歌曲短名
	void ErrBox(DWORD dwErr);
	afx_msg void OnBnClickedButton6();
	CSliderCtrl m_slider;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	UINT m_zsj;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnDblclkList1();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();

};
