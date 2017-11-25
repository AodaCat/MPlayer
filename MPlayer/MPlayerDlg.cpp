
// MPlayerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MPlayer.h"
#include "MPlayerDlg.h"
#include "afxdialogex.h"
#include "Mp3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMPlayerDlg 对话框



CMPlayerDlg::CMPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MPLAYER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	hour = 0;
	minute = 0;
	second = 0;
	ch = 0;
	cm = 0;
	cs = 0;
	totaltime = 0;
	currenttime = 0;
}

void CMPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, list);
	DDX_Control(pDX, IDC_SLIDER1, vol);
	DDX_Control(pDX, IDC_SLIDER2, process);
}

BEGIN_MESSAGE_MAP(CMPlayerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT, &CMPlayerDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_OPEN, &CMPlayerDlg::OnBnClickedOpen)
//	ON_LBN_SELCHANGE(IDC_LIST, &CMPlayerDlg::OnLbnSelchangeList)
//ON_LBN_SELCHANGE(IDC_LIST, &CMPlayerDlg::OnLbnSelchangeList)
//ON_LBN_DBLCLK(IDC_LIST, &CMPlayerDlg::OnLbnDblclkList)
ON_BN_CLICKED(IDC_PLAY, &CMPlayerDlg::OnBnClickedPlay)
ON_BN_CLICKED(IDC_PAUSE, &CMPlayerDlg::OnBnClickedPause)
ON_BN_CLICKED(IDC_STOP, &CMPlayerDlg::OnBnClickedStop)
ON_BN_CLICKED(IDC_DEL, &CMPlayerDlg::OnBnClickedDel)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CMPlayerDlg::OnNMCustomdrawSlider1)
ON_LBN_DBLCLK(IDC_LIST, &CMPlayerDlg::OnDblclkList)
//ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &CMPlayerDlg::OnNMReleasedcaptureSlider1)
ON_WM_TIMER()
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CMPlayerDlg::OnNMCustomdrawSlider2)
ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER2, &CMPlayerDlg::OnNMReleasedcaptureSlider2)
END_MESSAGE_MAP()


// CMPlayerDlg 消息处理程序

BOOL CMPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMPlayerDlg::OnPaint()
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
HCURSOR CMPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMPlayerDlg::OnBnClickedExit()
{
	// TODO: 在此添加控件通知处理程序代码
	player.Stop();
	CDialog::OnCancel();//退出
}


void CMPlayerDlg::OnBnClickedOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	char fliter[] = "音乐文件(*.mp3;*.wma;*.wav)\0*.mp3;*.wma;*.wav\0"
		"所有文件(*.*)\0*.*\0\0";
	CFileDialog fdlg(TRUE);//TRUE为OPEN对话框，FALSE为SAVE AS对话框
	fdlg.m_ofn.lpstrFilter = fliter;//对话框文件格式
	if (IDOK == fdlg.DoModal())
	{
		//创建文件对话框
		CString strfilepath = fdlg.GetPathName();//得到完整的文件名，包括目录名和扩展名如：c:\ test\ test1.txt
		CString strfilename = fdlg.GetFileName();//得到完整的文件名，包括扩展名如：test1.txt
		//SetDlgItemText(IDC_FILENAME, strfilename);
		//GetDlgItem(IDC_PAUSE)->EnableWindow(TRUE);//GetDlgItem(控件ID):返回该控件的指针
		//GetDlgItem(IDC_STOP)->EnableWindow(TRUE);//EnableWindow(bool值):True使控件可用,False则禁用控件
		list.InsertString(list.GetCount(), strfilepath);//GetCount():返回列表框中列表项的数目;InsertString():向列表框中添加字符串
		list.SetCurSel(list.GetCount() - 1);//选择指定的列表项
	}
}


void CMPlayerDlg::OnBnClickedPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strtemp;
	GetDlgItemText(IDC_PAUSE, strtemp);
	if (0 == strtemp.Compare("继续播放"))
	{
		SetDlgItemText(IDC_PAUSE, "暂停");
	}
	int index = list.GetCurSel();//返回当前被选择项的索引
	if (-1 == index)
	{
		MessageBox("╮(╯▽╰)╭\n请添加音乐！");
		return;
	}
	CString strfilename;
	list.GetText(index, strfilename);
	SetDlgItemText(IDC_FILENAME, strfilename);
	player.Stop();
	player.Open(m_hWnd, strfilename);
	player.Play();
	//GetDlgItem(IDC_PAUSE)->EnableWindow(TRUE);
	//GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
	KillTimer(0);
	SetTimer(0, 1000, NULL);
	hour = minute = second = ch = cm = cs = 0;
	strtemp.Format("%.2d:%.2d:%.2d / %.2d:%.2d:%.2d", ch, cm, cs, hour, minute, second);
	SetDlgItemText(IDC_TIME, strtemp);
	process.SetPos(0);
}


void CMPlayerDlg::OnBnClickedPause()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strtemp;
	int index = list.GetCurSel();
	if (-1 == index)
	{
		MessageBox("╮(╯▽╰)╭\n请先播放音乐！");
		return;
	}
	GetDlgItemText(IDC_PAUSE, strtemp);
	if (0 == strtemp.Compare("暂停"))
	{
		player.Pause();
		SetDlgItemText(IDC_PAUSE, "继续播放");
		KillTimer(0);
	}
	if (0 == strtemp.Compare("继续播放"))
	{
		player.resume();
		SetDlgItemText(IDC_PAUSE, "暂停");
		SetTimer(0, 1000, NULL);
	}
}


void CMPlayerDlg::OnBnClickedStop()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(0);
	int index = list.GetCurSel();
	if (-1 == index)
	{
		MessageBox("╮(╯▽╰)╭\n请先播放音乐！");
		return;
	}
	CString strtemp;
	GetDlgItemText(IDC_PAUSE, strtemp);
	if (0 == strtemp.Compare("继续播放"))
	{
		SetDlgItemText(IDC_PAUSE, "暂停");
	}
	player.Stop();
	//相关时间进度设置
	hour = 0;
	minute = 0;
	second = 0;
	ch = 0;
	cm = 0;
	cs = 0;
	strtemp.Format("%.2d:%.2d:%.2d / %.2d:%.2d:%.2d", ch, cm, cs, hour, minute, second);
	SetDlgItemText(IDC_TIME, strtemp);
	process.SetPos(0);
	//GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
	//GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
}


void CMPlayerDlg::OnBnClickedDel()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//初始化对话框数据，FALSE是将变量映射到控件，TRUE则是从控件到变量
	int index = list.GetCurSel();//GetCurSel获取当前光标的位置，如果没有选中项则返回CB_ERR
	//player.Stop();
	//SetDlgItemText(IDC_FILENAME, "");
	//KillTimer(0);
	if (index != LB_ERR)
	{
		list.DeleteString(index);//DeleteString()删除指定行内容
	}
}


void CMPlayerDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	volume = vol.GetPos();//获取Slider的位置
	player.SetVolume(volume*10);//设置音量
	CString Vtemp;
	Vtemp.Format("%d%%", volume);//音量显示格式
	SetDlgItemText(IDC_VOL, Vtemp);//更改音量显示
	*pResult = 0;
}


void CMPlayerDlg::OnDblclkList()//在列表中选中，双击左键播放音乐
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedPlay();
}


void CMPlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (0 == nIDEvent)
	{
		int index;
		totaltime = player.getinformation(MCI_STATUS_LENGTH);//获取歌曲总时长
		currenttime = player.getinformation(MCI_STATUS_POSITION);//获取歌曲当前播放时刻
		if (currenttime >= totaltime)
		{
			player.SeekTo(0);
			OnBnClickedStop();

			return;
		}

		totaltime = totaltime / 1000;
		hour = totaltime / 3600;
		minute = (totaltime / 60) % 60;//机智
		second = totaltime % 60;

		currenttime = currenttime / 1000;
		process.SetPos((currenttime * 100) / totaltime);//将歌曲当前播放时刻转换为进度条相应位置
		ch = currenttime / 3600;
		cm = (currenttime / 60) % 60;
		cs = currenttime % 60;

		CString temp;
		temp.Format(" %.2d:%.2d:%.2d / %.2d:%.2d:%.2d", ch, cm, cs, hour, minute, second);//时间格式
		SetDlgItemText(IDC_TIME, temp);//显示相关歌曲时间
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMPlayerDlg::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CMPlayerDlg::OnNMReleasedcaptureSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	SetTimer(0, 1000, NULL);
	CString temp;
	GetDlgItemText(IDC_PAUSE, temp);
	DWORD time = player.getinformation(MCI_STATUS_LENGTH);
	DWORD currenttime;
	currenttime = time*(process.GetPos()) / 100;//获取进度条当前位置并转换为歌曲相应播放时刻
	player.SeekTo(currenttime);
	player.Play();
	if (temp.Compare("继续播放") == 0)
	{
		SetDlgItemText(IDC_PAUSE, "暂停");
	}
	*pResult = 0;
}
