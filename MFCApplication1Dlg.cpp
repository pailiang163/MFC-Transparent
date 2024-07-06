
// MFCApplication1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "CTransparentStatic.h"
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


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1,str);
	DDX_Control(pDX, IDC_STATIC_1, m_TransparentStatic);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序
void CMFCApplication1Dlg::MoveImageToTopRight()
{
	// 获取窗口的矩形
	CRect windowRect;
	GetClientRect(&windowRect);

	// 获取图片控件的矩形
	CRect imageRect;
	CStatic* pImageCtrl = (CStatic*)GetDlgItem(IDC_STATIC_P);
	pImageCtrl->GetWindowRect(&imageRect);

	// 计算目标位置
	int targetX = windowRect.right - imageRect.Width();
	int targetY = windowRect.top;

	// 将图片控件的坐标从屏幕坐标转换为客户区坐标
	ScreenToClient(&imageRect);

	// 移动图片
	pImageCtrl->SetWindowPos(NULL, targetX, targetY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

BOOL CMFCApplication1Dlg::OnInitDialog()
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
	MoveImageToTopRight();

	// 设置文本
	
	//CWnd* pWnd = GetDlgItem(IDC_STATIC_1);
	// 获取文本控件指针

	m_TransparentStatic.SetWindowText(_T("设置了透明背景的文本"));
	// 设置文本颜色为白色
	

	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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
		//CDialogEx::OnPaint();
		CPaintDC dc(this); // 设备上下文
		m_bgBitmap.LoadBitmap(IDB_BITMAP1); // IDB_BACKGROUND 是资源中的位图ID
		// 获取对话框的客户区矩形
		CRect rect;
		GetClientRect(&rect);

		// 创建内存DC并选择背景图片
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);
		CBitmap* pOldBitmap = memDC.SelectObject(&m_bgBitmap);

		// 获取背景图片的尺寸
		BITMAP bitmap;
		m_bgBitmap.GetBitmap(&bitmap);

		// 绘制背景图片
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

		// 恢复内存DC
		memDC.SelectObject(pOldBitmap);

	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	str = str + _T("abc");
	UpdateData(FALSE);
}


HBRUSH CMFCApplication1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	int controlId = pWnd->GetDlgCtrlID();

	// 根据控件ID判断是否应用特定设置
	if (controlId == IDC_STATIC_2) {
		CFont font;
		font.CreateFont(
			16,                         // 字体高度
			0,                          // 字体宽度
			0,                          // 文字倾斜度
			0,                          // 角度
			FW_BOLD,                    // 字体粗细
			FALSE,                      // 斜体
			FALSE,                      // 下划线
			0,                          // 删除线
			ANSI_CHARSET,               // 字符集
			OUT_DEFAULT_PRECIS,         // 输出精度
			CLIP_DEFAULT_PRECIS,        // 裁剪精度
			DEFAULT_QUALITY,            // 字体质量
			DEFAULT_PITCH | FF_SWISS,   // 字体族
			_T("宋体")                  // 字体名称
		);

		pDC->SelectObject(&font);  // 选择字体到设备上下文

		pDC->SetTextColor(RGB(255, 255, 255));  // 设置文本颜色为白色
		pDC->SetBkMode(TRANSPARENT);  // 设置背景透明
		return (HBRUSH)::GetStockObject(NULL_BRUSH);  // 返回透明画刷
	}

	// 默认情况下，调用基类的处理方式
	return CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	
}
