// ChildDomFrm.cpp : ʵ���ļ�
//


#include "stdafx.h"
#include "MapMatrix3D Editor.h"
#include "ChildDomFrm.h"


// CChildDomFrm

IMPLEMENT_DYNAMIC(CChildDomFrm, CMDIChildWndEx)

CChildDomFrm::CChildDomFrm()
{

}

CChildDomFrm::~CChildDomFrm()
{
}


BEGIN_MESSAGE_MAP(CChildDomFrm, CMDIChildWndEx)
END_MESSAGE_MAP()



// CChildDomFrm ��Ϣ�������




BOOL CChildDomFrm::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (!CMDIChildWndEx::PreCreateWindow(cs))
	{
		return FALSE;
	}
	
	CRect rect;
	AfxGetMainWnd()->GetClientRect(rect);
	cs.x = 0;
	cs.y = 0;
	cs.cx = rect.Width();
	cs.cy = rect.Height();
	return TRUE;
}
