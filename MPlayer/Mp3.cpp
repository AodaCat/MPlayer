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
	mciSendCommand(DeviceID, MCI_CLOSE, NULL, NULL);//关闭设备，加载文件前先清除上次设置。mciSendCommand():MCI的命令消息接口，所有MCI命令消息都是通过mciSendCommand函数发送
	mciopenparms.lpstrElementName = Strfilepath;//将音乐文件路径传给设备
	DWORD dwReturn;
	if (dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT|MCI_WAIT, (DWORD)(LPVOID)&mciopenparms))//MC_OPEN_ELEMENT:MCI_OPEN_PARMS 结构的lpstrElementName 域中指定了设备元素
	{
		//若成功则返回0，否则返回错误码
		//如果打开失败，将出错信息存在buffer并显示出错警告
		char buffer[256];
		mciGetErrorString(dwReturn, buffer, 256);//获取当前MCI 错误的字符串描述
		MessageBox(hwnd, buffer,"ERROR",MB_ICONHAND|MB_ICONERROR|MB_ICONSTOP);//显示错误窗口
	}
	DeviceID = mciopenparms.wDeviceID;//接受消息的设备ID
}

DWORD Mp3::getinformation(DWORD item)
{
	MCI_STATUS_PARMS mcistatusparms;//查询当前信息
	mcistatusparms.dwItem = item;
	mcistatusparms.dwReturn = 0;
	mciSendCommand(DeviceID,MCI_STATUS, MCI_WAIT|MCI_STATUS_ITEM, (DWORD)(LPVOID)&mcistatusparms);//从一个MCI 设备返回有关的状态信息
	return mcistatusparms.dwReturn;//返回信息存放于StatusParms.dwReturn中
}

void Mp3::Play()
{
	MCI_PLAY_PARMS mciplayparms;
	mciplayparms.dwCallback = (DWORD)m_hWnd;
	mciplayparms.dwFrom = 0;// 指定从什么地方（时间）播放
	mciSendCommand(DeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciplayparms);//开始播放数据
}

void Mp3::Pause()
{
	mciSendCommand(DeviceID, MCI_PAUSE, NULL, NULL);//暂停播放或记录
}

void Mp3::resume()
{
	mciSendCommand(DeviceID, MCI_RESUME, NULL, NULL);//开始播放或记录
}

void Mp3::Stop()
{
	mciSendCommand(DeviceID, MCI_STOP, NULL, NULL);//停止
	mciSendCommand(DeviceID, MCI_CLOSE, NULL, NULL);//关闭一个MCI设备
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
