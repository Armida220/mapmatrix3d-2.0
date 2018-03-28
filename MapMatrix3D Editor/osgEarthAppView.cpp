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

// osgEarthAppView.cpp : CosgEarthAppView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MapMatrix3D Editor.h"
#endif

//#include "osgEarthAppDoc.h"
#include "osgEarthAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CosgEarthAppView

IMPLEMENT_DYNCREATE(CosgEarthAppView, CView)

BEGIN_MESSAGE_MAP(CosgEarthAppView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	//ON_COMMAND(ID_BUTTON2, &CosgEarthAppView::OnButton2)
END_MESSAGE_MAP()

// CosgEarthAppView ����/����

CosgEarthAppView::CosgEarthAppView()
{
	// TODO: �ڴ˴���ӹ������
	openFileFlag = FALSE;
}

CosgEarthAppView::~CosgEarthAppView()
{
}

BOOL CosgEarthAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CosgEarthAppView ����

void CosgEarthAppView::OnDraw(CDC* /*pDC*/)
{
	CDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//��ȡ�ļ�
	if (openFileFlag == FALSE)
	{
		openFileFlag = TRUE;

	/*	theApp.IOsgEarth->InitOSGearth("");*/
		/*mThreadHandle = theApp.IOsgEarth->StartRendering();
		std::vector<OperatingState> vecOps;
		vecOps.push_back(OPS_INTERNET_ORIENTATION);
		theApp.IOsgEarth->AddViewerOPS(vecOps);*/
	}

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CosgEarthAppView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CosgEarthAppView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CosgEarthAppView ���

#ifdef _DEBUG
void CosgEarthAppView::AssertValid() const
{
	CView::AssertValid();
}

void CosgEarthAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CosgEarthAppDoc* CosgEarthAppView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CosgEarthAppDoc)));
	return (CosgEarthAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CosgEarthAppView ��Ϣ�������


void CosgEarthAppView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	//InterfaceOsgEarthFactory IOsgEarthFactory;
	//theApp.IOsgEarth = IOsgEarthFactory.Create(m_hWnd);

	////��������
	//CRect rect;
	//AfxGetMainWnd()->GetClientRect(rect);

	//myBtn1.Create(_T("��λ"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,CRect(rect.right/2-100,rect.bottom/2,rect.right/2-50, rect.bottom/2+50),
	//	this,1);
	//myBtn1.ShowWindow(SW_SHOW);
}


//void CosgEarthAppView::OnButton2()
//{
//	// TODO: �ڴ���������������
//	openFileFlag = FALSE;
//
//	this->Invalidate(TRUE);
//}
