
// MPlayer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMPlayerApp: 
// �йش����ʵ�֣������ MPlayer.cpp
//

class CMPlayerApp : public CWinApp
{
public:
	CMPlayerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
//	afx_msg void OnList();
};

extern CMPlayerApp theApp;