// MFCDepends.h : MFCDepends DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCDependsApp
// �йش���ʵ�ֵ���Ϣ������� MFCDepends.cpp
//

class CMFCDependsApp : public CWinApp
{
public:
	CMFCDependsApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
