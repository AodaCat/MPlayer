#pragma once

class Mp3
{
public:
	Mp3();
	~Mp3();
	HWND m_hWnd;//���ھ��
	DWORD DeviceID;//�����豸ID���� 4 �ֽڳ���32 λ�����������ֱ�ʾ�����ݡ��豸��������ͷ�������������Ǵ�����
	MCI_OPEN_PARMS mciopenparms;//MCIý����ƽӿ�,���豸
	DWORD getinformation(DWORD item);//��ȡ��ظ�����Ϣ
	void Open(HWND hwnd, CString Strfilepath);//��
	void Play();//����
	void Pause();//��ͣ
	void resume();//��ʼ
	void Stop();//ֹͣ
	void SetVolume(DWORD d_vol);//��������
	void SeekTo(DWORD to);//��������
};