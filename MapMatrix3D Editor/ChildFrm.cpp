// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "MapMatrix3D Editor.h"
#include "qcomm.h"
#include "ChildFrm.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame
CChildFrame* g_mfcChildFrame = NULL;

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
END_MESSAGE_MAP()

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	g_mfcChildFrame = this;
	WindowMove = (double) GetSystemMetrics(SM_CYCAPTION);
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;
	
	
	double widthFileView = 0;
	
	/*cs.x = rect.left - 3 * GetSystemMetrics(SM_CXDLGFRAME);
	cs.y = rect.top - GetSystemMetrics(SM_CYCAPTION) - 3 * GetSystemMetrics(SM_CXDLGFRAME);
	cs.cx = rect.Width() + 3 * GetSystemMetrics(SM_CXDLGFRAME) + 200;
	cs.cy = rect.Height() - 2 * GetSystemMetrics(SM_CYCAPTION);*/


	/*cs.x = rect.left -  3*GetSystemMetrics(SM_CXDLGFRAME);
	cs.y = rect.top - GetSystemMetrics(SM_CYCAPTION) - 3*GetSystemMetrics(SM_CXDLGFRAME);
	cs.cx = rect.Width()+6*GetSystemMetrics(SM_CXDLGFRAME);
	cs.cy = rect.Height() - GetSystemMetrics(SM_CYCAPTION) - 3*GetSystemMetrics(SM_CXDLGFRAME);*/

	/*cs.x = 0;
	cs.y=0;
	cs.cx= rect.Width();
	cs.cy= rect.Height();*/
	cs.style =WS_MAXIMIZE ;
	return TRUE;
}

// CChildFrame ���

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame ��Ϣ�������