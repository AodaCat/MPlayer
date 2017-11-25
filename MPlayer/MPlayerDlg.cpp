
// MPlayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MPlayer.h"
#include "MPlayerDlg.h"
#include "afxdialogex.h"
#include "Mp3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMPlayerDlg �Ի���



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


// CMPlayerDlg ��Ϣ�������

BOOL CMPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMPlayerDlg::OnBnClickedExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	player.Stop();
	CDialog::OnCancel();//�˳�
}


void CMPlayerDlg::OnBnClickedOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char fliter[] = "�����ļ�(*.mp3;*.wma;*.wav)\0*.mp3;*.wma;*.wav\0"
		"�����ļ�(*.*)\0*.*\0\0";
	CFileDialog fdlg(TRUE);//TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
	fdlg.m_ofn.lpstrFilter = fliter;//�Ի����ļ���ʽ
	if (IDOK == fdlg.DoModal())
	{
		//�����ļ��Ի���
		CString strfilepath = fdlg.GetPathName();//�õ��������ļ���������Ŀ¼������չ���磺c:\ test\ test1.txt
		CString strfilename = fdlg.GetFileName();//�õ��������ļ�����������չ���磺test1.txt
		//SetDlgItemText(IDC_FILENAME, strfilename);
		//GetDlgItem(IDC_PAUSE)->EnableWindow(TRUE);//GetDlgItem(�ؼ�ID):���ظÿؼ���ָ��
		//GetDlgItem(IDC_STOP)->EnableWindow(TRUE);//EnableWindow(boolֵ):Trueʹ�ؼ�����,False����ÿؼ�
		list.InsertString(list.GetCount(), strfilepath);//GetCount():�����б�����б������Ŀ;InsertString():���б��������ַ���
		list.SetCurSel(list.GetCount() - 1);//ѡ��ָ�����б���
	}
}


void CMPlayerDlg::OnBnClickedPlay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strtemp;
	GetDlgItemText(IDC_PAUSE, strtemp);
	if (0 == strtemp.Compare("��������"))
	{
		SetDlgItemText(IDC_PAUSE, "��ͣ");
	}
	int index = list.GetCurSel();//���ص�ǰ��ѡ���������
	if (-1 == index)
	{
		MessageBox("�r(�s���t)�q\n��������֣�");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strtemp;
	int index = list.GetCurSel();
	if (-1 == index)
	{
		MessageBox("�r(�s���t)�q\n���Ȳ������֣�");
		return;
	}
	GetDlgItemText(IDC_PAUSE, strtemp);
	if (0 == strtemp.Compare("��ͣ"))
	{
		player.Pause();
		SetDlgItemText(IDC_PAUSE, "��������");
		KillTimer(0);
	}
	if (0 == strtemp.Compare("��������"))
	{
		player.resume();
		SetDlgItemText(IDC_PAUSE, "��ͣ");
		SetTimer(0, 1000, NULL);
	}
}


void CMPlayerDlg::OnBnClickedStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(0);
	int index = list.GetCurSel();
	if (-1 == index)
	{
		MessageBox("�r(�s���t)�q\n���Ȳ������֣�");
		return;
	}
	CString strtemp;
	GetDlgItemText(IDC_PAUSE, strtemp);
	if (0 == strtemp.Compare("��������"))
	{
		SetDlgItemText(IDC_PAUSE, "��ͣ");
	}
	player.Stop();
	//���ʱ���������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);//��ʼ���Ի������ݣ�FALSE�ǽ�����ӳ�䵽�ؼ���TRUE���Ǵӿؼ�������
	int index = list.GetCurSel();//GetCurSel��ȡ��ǰ����λ�ã����û��ѡ�����򷵻�CB_ERR
	//player.Stop();
	//SetDlgItemText(IDC_FILENAME, "");
	//KillTimer(0);
	if (index != LB_ERR)
	{
		list.DeleteString(index);//DeleteString()ɾ��ָ��������
	}
}


void CMPlayerDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	volume = vol.GetPos();//��ȡSlider��λ��
	player.SetVolume(volume*10);//��������
	CString Vtemp;
	Vtemp.Format("%d%%", volume);//������ʾ��ʽ
	SetDlgItemText(IDC_VOL, Vtemp);//����������ʾ
	*pResult = 0;
}


void CMPlayerDlg::OnDblclkList()//���б���ѡ�У�˫�������������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedPlay();
}


void CMPlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (0 == nIDEvent)
	{
		int index;
		totaltime = player.getinformation(MCI_STATUS_LENGTH);//��ȡ������ʱ��
		currenttime = player.getinformation(MCI_STATUS_POSITION);//��ȡ������ǰ����ʱ��
		if (currenttime >= totaltime)
		{
			player.SeekTo(0);
			OnBnClickedStop();

			return;
		}

		totaltime = totaltime / 1000;
		hour = totaltime / 3600;
		minute = (totaltime / 60) % 60;//����
		second = totaltime % 60;

		currenttime = currenttime / 1000;
		process.SetPos((currenttime * 100) / totaltime);//��������ǰ����ʱ��ת��Ϊ��������Ӧλ��
		ch = currenttime / 3600;
		cm = (currenttime / 60) % 60;
		cs = currenttime % 60;

		CString temp;
		temp.Format(" %.2d:%.2d:%.2d / %.2d:%.2d:%.2d", ch, cm, cs, hour, minute, second);//ʱ���ʽ
		SetDlgItemText(IDC_TIME, temp);//��ʾ��ظ���ʱ��
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMPlayerDlg::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CMPlayerDlg::OnNMReleasedcaptureSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetTimer(0, 1000, NULL);
	CString temp;
	GetDlgItemText(IDC_PAUSE, temp);
	DWORD time = player.getinformation(MCI_STATUS_LENGTH);
	DWORD currenttime;
	currenttime = time*(process.GetPos()) / 100;//��ȡ��������ǰλ�ò�ת��Ϊ������Ӧ����ʱ��
	player.SeekTo(currenttime);
	player.Play();
	if (temp.Compare("��������") == 0)
	{
		SetDlgItemText(IDC_PAUSE, "��ͣ");
	}
	*pResult = 0;
}
