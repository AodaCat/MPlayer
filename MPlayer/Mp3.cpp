#include "stdafx.h"
#include "Mp3.h"


Mp3::Mp3()
{
}


Mp3::~Mp3()
{
}

void Mp3::Open(HWND hwnd, CString Strfilepath)
{
	m_hWnd = hwnd;
	mciSendCommand(DeviceID, MCI_CLOSE, NULL, NULL);//�ر��豸�������ļ�ǰ������ϴ����á�mciSendCommand():MCI��������Ϣ�ӿڣ�����MCI������Ϣ����ͨ��mciSendCommand��������
	mciopenparms.lpstrElementName = Strfilepath;//�������ļ�·�������豸
	DWORD dwReturn;
	if (dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT|MCI_WAIT, (DWORD)(LPVOID)&mciopenparms))//MC_OPEN_ELEMENT:MCI_OPEN_PARMS �ṹ��lpstrElementName ����ָ�����豸Ԫ��
	{
		//���ɹ��򷵻�0�����򷵻ش�����
		//�����ʧ�ܣ���������Ϣ����buffer����ʾ������
		char buffer[256];
		mciGetErrorString(dwReturn, buffer, 256);//��ȡ��ǰMCI ������ַ�������
		MessageBox(hwnd, buffer,"ERROR",MB_ICONHAND|MB_ICONERROR|MB_ICONSTOP);//��ʾ���󴰿�
	}
	DeviceID = mciopenparms.wDeviceID;//������Ϣ���豸ID
}

DWORD Mp3::getinformation(DWORD item)
{
	MCI_STATUS_PARMS mcistatusparms;//��ѯ��ǰ��Ϣ
	mcistatusparms.dwItem = item;
	mcistatusparms.dwReturn = 0;
	mciSendCommand(DeviceID,MCI_STATUS, MCI_WAIT|MCI_STATUS_ITEM, (DWORD)(LPVOID)&mcistatusparms);//��һ��MCI �豸�����йص�״̬��Ϣ
	return mcistatusparms.dwReturn;//������Ϣ�����StatusParms.dwReturn��
}

void Mp3::Play()
{
	MCI_PLAY_PARMS mciplayparms;
	mciplayparms.dwCallback = (DWORD)m_hWnd;
	mciplayparms.dwFrom = 0;// ָ����ʲô�ط���ʱ�䣩����
	mciSendCommand(DeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciplayparms);//��ʼ��������
}

void Mp3::Pause()
{
	mciSendCommand(DeviceID, MCI_PAUSE, NULL, NULL);//��ͣ���Ż��¼
}

void Mp3::resume()
{
	mciSendCommand(DeviceID, MCI_RESUME, NULL, NULL);//��ʼ���Ż��¼
}

void Mp3::Stop()
{
	mciSendCommand(DeviceID, MCI_STOP, NULL, NULL);//ֹͣ
	mciSendCommand(DeviceID, MCI_CLOSE, NULL, NULL);//�ر�һ��MCI�豸
}

void Mp3::SetVolume(DWORD d_vol)
{
	MCI_DGV_SETAUDIO_PARMS mcidgvsetvolumn;
	mcidgvsetvolumn.dwCallback = NULL;
	mcidgvsetvolumn.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mcidgvsetvolumn.dwValue = d_vol;
	mciSendCommand(DeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE|MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&mcidgvsetvolumn);
}

void Mp3::SeekTo(DWORD to)
{
	MCI_SEEK_PARMS mciseek;
	mciseek.dwTo = to;
	mciSendCommand(DeviceID, MCI_SEEK, MCI_TO, (DWORD)(LPVOID)&mciseek);
}
