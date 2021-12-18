
// MFCApplication5Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication5.h"
#include "MFCApplication5Dlg.h"
#include "afxdialogex.h"
#include <mmsystem.h> // 播放声音必须加
#include <locale> // 中文支持
#include "CMMDlg.h"


#pragma comment(lib, "winmm.lib")// 播放声音必须加

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCApplication5Dlg 对话框



CMFCApplication5Dlg::CMFCApplication5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION5_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_bflb);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
}

BEGIN_MESSAGE_MAP(CMFCApplication5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication5Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication5Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication5Dlg::OnBnClickedButton6)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication5Dlg::OnBnClickedButton3)
	ON_LBN_DBLCLK(IDC_LIST1, &CMFCApplication5Dlg::OnDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication5Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication5Dlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMFCApplication5Dlg 消息处理程序

BOOL CMFCApplication5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_zzbf = FALSE; //默认不在播放
	m_zsj = 0;
	*m_gqqm = _T('\0');
	*m_gqdm = _T('\0');
	SetTimer(1, 50, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CMFCApplication5Dlg::OnBnClickedButton2()
{
	// 添加文件对话框
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, _T("音乐文件(*.mp3;*.wma;*.wav) |*.mp3;*.wma;*.wav|所有文件(*.*)|*.*||"), this);
	TCHAR* pBuf = new TCHAR[MAX_PATH * 255];	//创建数组来储存多个文件
	*pBuf = 0;
	dlg.m_ofn.lpstrFile = pBuf;
	dlg.m_ofn.nMaxFile = MAX_PATH * 255;

	// 获取选中文件的位置和名称并显示在播放列表中
	if (dlg.DoModal() == IDOK) {
		POSITION pos = dlg.GetStartPosition();
		CString strFile;
		while (pos != NULL) {
			strFile = dlg.GetNextPathName(pos);

			// 播放列表只显示文件名
			//CString filename = strFile.Right(strFile.GetLength() - strFile.ReverseFind('\\') - 1); 
			//filename = filename.Left(filename.ReverseFind('.'));
			//m_bflb.AddString(filename);

			m_bflb.AddString(strFile);
		}
	}
	delete[] pBuf; //有new就有delete
}


void CMFCApplication5Dlg::OnBnClickedButton1()
{
	// 判断是否在播放
	if (m_zzbf) {
		StopPlay();
	}
	else {

		CString strCmd;
		DWORD dwErr;
		int nIndex = m_bflb.GetCurSel();

		// 判断有没有可以播放的歌曲
		if (nIndex < 0) {
			return;
		}
		else {
			m_bflb.GetText(nIndex, m_gqqm);
			GetShortPathName(m_gqqm, m_gqdm, MAX_PATH);

			// 调用mci打开音乐
			strCmd.Format(_T("open %s"), m_gqdm);
			dwErr = mciSendString(strCmd, NULL, 0, NULL);
			// mci可能报错，显示报错原因
			if (dwErr != 0) {
				ErrBox(dwErr);
				return;
			}

			// 调用mci播放音乐
			strCmd.Format(_T("play %s"), m_gqdm);
			dwErr = mciSendString(strCmd, NULL, 0, NULL);
			if (dwErr != 0) {
				ErrBox(dwErr);
				return;
			}
			// 能成功播放，设置进度条相关参数
			else {
				TCHAR szReturn[MAX_PATH] = { 0 };
				// 调用mci获取歌曲总时间
				strCmd.Format(_T("status %s length"), m_gqdm);
				dwErr = mciSendString(strCmd, szReturn, MAX_PATH, NULL);
				if (dwErr != 0) {
					ErrBox(dwErr);
					return;
				}
				else {
					m_zsj = _ttoi(szReturn);
					m_slider.SetRange(0, m_zsj, TRUE);
				}
			}

			m_zzbf = TRUE;	//正在播放
			SetDlgItemText(IDC_BUTTON1, _T("停止"));
		}
	}
}


BOOL CMFCApplication5Dlg::StopPlay() 
{
	if (!m_zzbf) {
		return TRUE;
	}
	else {
		DWORD dwErr;

		// 调用mci停止音乐
		dwErr = mciSendString(_T("stop all"), NULL, 0, NULL);
		if (dwErr != 0) {
			ErrBox(dwErr);
			return TRUE;
		}

		// 调用mci关闭音乐
		dwErr = mciSendString(_T("close all"), NULL, 0, NULL);
		if (dwErr != 0) {
			ErrBox(dwErr);
			return TRUE;
		}
		else {
			m_zzbf = FALSE;	//停止播放
			SetDlgItemText(IDC_BUTTON1, _T("播放"));
			m_slider.SetPos(0);
			return TRUE;
		}

	}
}


void CMFCApplication5Dlg::ErrBox(DWORD dwErr) 
{
	TCHAR szBuf[MAX_PATH] = { 0 };
	mciGetErrorString(dwErr, szBuf, MAX_PATH);
	AfxMessageBox(szBuf);
}


void CMFCApplication5Dlg::OnBnClickedButton6()
{
	int nIndex = m_bflb.GetCurSel();

	// 判断有没有要删除的条目
	if (nIndex < 0) {
		return;
	}
	else {
		m_bflb.DeleteString(nIndex);
	}
}


void CMFCApplication5Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// 如果在播放，让进度条动起来
	if (m_zzbf) {
		CString strCmd;
		DWORD dwErr;
		TCHAR szReturn[MAX_PATH] = { 0 };
		// 调用mci获取歌曲当前进度
		strCmd.Format(_T("status %s position"), m_gqdm);
		dwErr = mciSendString(strCmd, szReturn, MAX_PATH, NULL);
		if (dwErr != 0) {
			ErrBox(dwErr);
			return;
		}
		else {
			UINT nPosition = _ttoi(szReturn);
			m_slider.SetPos(nPosition);

			// 如果当前歌曲播放完成，自动播放下一首歌曲
			if (nPosition == m_zsj) {
				StopPlay();
				int nIndex = m_bflb.FindString(-1, m_gqdm);
				// 判断播放列表是否为空
				if (nIndex < 0) {
					nIndex = 0;
				}
				else {
					nIndex++;
					// 如果播放完最后一首，回到第一首
					if (nIndex > m_bflb.GetCount() - 1) {
						nIndex = 0;
					}
				m_bflb.SetCurSel(nIndex);
				OnBnClickedButton1();
				}
			}		
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CMFCApplication5Dlg::OnBnClickedButton3()
{
	// 判断是否在播放
	if (m_zzbf) {
		StopPlay();
	}
	// 设置从第一首开始顺序播放列表
	m_bflb.SetCurSel(0);
	OnBnClickedButton1();
}


void CMFCApplication5Dlg::OnDblclkList1()
{
	int nIndex = m_bflb.GetCurSel();

	if (nIndex < 0) {
		return;
	}
	else {
		// 判断是否在播放
		if (m_zzbf) {
			StopPlay();
		}
		// 从双击的歌曲开始播放
		m_bflb.SetCurSel(nIndex);
		OnBnClickedButton1();
	}
}


void CMFCApplication5Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_bflb.GetCurSel();
	CString str;

	// 判断有没有要重命名的条目
	if (nIndex < 0) {
		return;
	}
	else {
		m_bflb.GetText(nIndex, str);
		CMMDlg dlg;
		dlg.m_csm = str;
		if (dlg.DoModal() == IDOK) {
			str = dlg.m_xgm;
		}
		else {
			return;
		}
		// 先删除，再重新插入，实现重命名
		m_bflb.DeleteString(nIndex);	
		m_bflb.InsertString(nIndex, str);	
	}
}


void CMFCApplication5Dlg::OnBnClickedButton4()
{
	CStdioFile sFile;
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK) {
		if (!sFile.Open(dlg.GetPathName(), CStdioFile::modeCreate| CStdioFile::modeWrite)) {
			MessageBox(_T("打开文件失败！"));
			return;
		}
		else {
			setlocale(LC_CTYPE, "chs"); // 加了这个才能写入中文
			sFile.SeekToEnd();	// 将写入指针移至末尾
			CString str;
			int nIndex = 0;
			int nCount = m_bflb.GetCount() - 1;	// count 比 index 多 1
			// 遍历写入
			while (nCount > -1 && nIndex <= nCount) {
				m_bflb.GetText(nIndex, str);
				str += "\n";
				sFile.WriteString(str);
				nIndex++;
			}
			sFile.Close();	// 有open就有close
			MessageBox(_T("保存成功！"));
		}
	}
}
