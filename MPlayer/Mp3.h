#pragma once

class Mp3
{
public:
	Mp3();
	~Mp3();
	HWND m_hWnd;//窗口句柄
	DWORD DeviceID;//保存设备ID，由 4 字节长（32 位整数）的数字表示的数据。设备驱动程序和服务的许多参数都是此类型
	MCI_OPEN_PARMS mciopenparms;//MCI媒体控制接口,打开设备
	DWORD getinformation(DWORD item);//获取相关歌曲信息
	void Open(HWND hwnd, CString Strfilepath);//打开
	void Play();//播放
	void Pause();//暂停
	void resume();//开始
	void Stop();//停止
	void SetVolume(DWORD d_vol);//音量设置
	void SeekTo(DWORD to);//进度设置
};