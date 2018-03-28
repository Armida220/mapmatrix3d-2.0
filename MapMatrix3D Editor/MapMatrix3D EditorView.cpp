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

// MapMatrix3D EditorView.cpp : CMapMatrix3DEditorView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MapMatrix3D Editor.h"
#endif

#include "MapMatrix3D EditorDoc.h"
#include "MapMatrix3D EditorView.h"
#include "MainFrm.h"
#include "MapMatrix3D Editor.h"
#include "FileView.h"
#include "ProgressBar.h"
#include "publicDefined.h"
#include "cv_plus.hpp"
#include "DOMResSetDlg.h"
#include <gl\GL.h>
#include "OPStatusBar.h"
#include "boost/signals2/signal.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif   

//extern void CallBackStartProgress();


IMPLEMENT_DYNCREATE(CMapMatrix3DEditorView, CView)

BEGIN_MESSAGE_MAP(CMapMatrix3DEditorView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_OPEN_3DMODEL, &CMapMatrix3DEditorView::OnOpen3dmodel)
	ON_COMMAND(ID_REMOVE_SCENE, &CMapMatrix3DEditorView::OnRemoveScene)
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

#ifdef _DEBUG
void CMapMatrix3DEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CMapMatrix3DEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapMatrix3DEditorDoc* CMapMatrix3DEditorView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapMatrix3DEditorDoc)));
	return (CMapMatrix3DEditorDoc*)m_pDocument;
}
#endif //_DEBUG
// CMapMatrix3DEditorView ����/����

CMapMatrix3DEditorView::CMapMatrix3DEditorView()
{
	// TODO: �ڴ˴���ӹ������

}

CMapMatrix3DEditorView::~CMapMatrix3DEditorView()
{
}

BOOL CMapMatrix3DEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	CRect rect;
	return CView::PreCreateWindow(cs);
}

void CMapMatrix3DEditorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	InterfaceOsgMfcViewerFactory IViewerFactory;
	theApp.IOsgMfcViewer = IViewerFactory.create(m_hWnd);
	openFileFlag = FALSE;

	theApp.InitCallBack();
}

// CMapMatrix3DEditorView ��Ϣ�������

void CMapMatrix3DEditorView::OnOpen3dmodel()
{
	// TODO: �ڴ���������������
	CFileDialog dialog(TRUE, NULL, NULL, OFN_HIDEREADONLY, (LPCTSTR)_TEXT("3D model Files (*.osgb, *.osg, *.obj)|*.osgb;*.osg;*.obj;*.osgt|All Files (*.*)|*.*||"),NULL);

	if (dialog.DoModal() == IDOK)
	{
		CString fileName = dialog.GetPathName();
		ary_filename.push_back(fileName);
	}

	if (ary_filename.size() > 0)
	{
		this->Invalidate(TRUE);
	}

}

void CMapMatrix3DEditorView::OnDraw(CDC* /*pDC*/)
{	
	if (!ary_filename.empty())
	{
		std::string strModel = ary_filename[0]; 

		if (openFileFlag == TRUE)
		{
			ary_filename.clear();
			theApp.IOsgMfcViewer->ObtainISig()->EmitSigShowOpsHint("���ڴ򿪳���...");
			theApp.IOsgMfcViewer->ObtainISig()->EmitSigSetProgressFun(500);
			theApp.IOsgMfcViewer->ObtainISig()->EmitSigSetProgressFun(502);
		
			
			theApp.AddScene(strModel);
			Sleep(1000);
			theApp.IOsgMfcViewer->getViewer()->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KEY_Space);
			//theApp.IOsgMfcViewer->ObtainISig()->EmitSigSetProgressFun(900);
			theApp.IOsgMfcViewer->ObtainISig()->EmitSigSetProgressFun(999);
			theApp.IOsgMfcViewer->ObtainISig()->EmitSigEndProgressFun();
			theApp.IOsgMfcViewer->ObtainISig()->EmitSigShowOpsHint("");
		}
		else if (openFileFlag == FALSE)
		{
			openFileFlag = TRUE;
			ary_filename.clear();
			theApp.IOsgMfcViewer->ObtainISig()->EmitSigShowOpsHint("���ڴ򿪳���...");
			theApp.IOsgMfcViewer->ObtainISig()->EmitSigSetProgressFun(500);
			
			theApp.IOsgMfcViewer->ObtainISig()->EmitSigSetProgressFun(502);
			theApp.IOsgMfcViewer->InitOSG(strModel);

			//��ȡ·��
			CString sceneFileName = strModel.c_str();
			int pos = sceneFileName.ReverseFind('\\');
			CString sceneFilePath = sceneFileName.Left(pos);
			theApp.vecSceneFileName.push_back(sceneFileName);
			CString fileTitle = sceneFileName.Right(sceneFileName.GetLength() - 1 - pos);

			//���÷�Χ
			theApp.IOsgMfcViewer->SetSceneExtent();

			//���·������ͼ��
			CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
			pMain->insertItem(sceneFilePath, fileTitle);

			mThreadHandle = theApp.IOsgMfcViewer->StartRendering();

			
			theApp.IOsgMfcViewer->getViewer()->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KEY_L);
			Sleep(100);
			theApp.IOsgMfcViewer->getViewer()->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KEY_Space);
			theApp.IOsgMfcViewer->ObtainISig()->EmitSigSetProgressFun(999);
			theApp.IOsgMfcViewer->ObtainISig()->EmitSigEndProgressFun();
			theApp.IOsgMfcViewer->ObtainISig()->EmitSigShowOpsHint("");
		}
		
		//if (ary_filename.size() > 1)
		//{
		//	for (int i = 1; i < ary_filename.size(); i++)
		//	{
		//		std::string strTemp = ary_filename[i];
		//		osg::ref_ptr<osg::Node> tempNode1 = osgDB::readNodeFile(strTemp);
		//		osg::ref_ptr<osg::Group> group = mOSG->mRoot->getChild(0)->asGroup();
		//		group->addChild(tempNode1);

		//		//��ȡ·��
		//		sceneFileName = strTemp.c_str();
		//		int pos = sceneFileName.ReverseFind('\\');
		//		CString sceneFilePath = sceneFileName.Left(pos);
		//		vecSceneFileName.push_back(sceneFileName);
		//		CString fileTitle = sceneFileName.Right(sceneFileName.GetLength() - 1 - pos);

		//		//���·������ͼ��
		//		CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
		//		pMain->insertItem(sceneFilePath, fileTitle);
		//	}

		//}

	}

	CMapMatrix3DEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CMapMatrix3DEditorView::OnRemoveScene()
{
	// TODO: �ڴ���������������
	if(theApp.isLoadModel() == false)
	{
		return;
	}
	
	theApp.RemoveAllScene();
}


int CMapMatrix3DEditorView::OnCreate(LPCREATESTRUCT LPCREATESTRUCT)
{
	if (CView::OnCreate(LPCREATESTRUCT) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	return 0;
}

void CMapMatrix3DEditorView::OnDestroy()
{
	CView::OnDestroy();
	// TODO: �ڴ˴������Ϣ����������
}

BOOL CMapMatrix3DEditorView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE)
		{
			if (!theApp.isLoadModel())
			{
				return FALSE;
			}
			std::vector<OperatingState> vecOPS;
			vecOPS.push_back(OPS_None);
			theApp.IOsgMfcViewer->AddViewerOPS(vecOPS);
		}
	}

	return CView::PreTranslateMessage(pMsg);
}


BOOL CMapMatrix3DEditorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect   m_rt;
	GetClientRect(&m_rt);
	CBrush   brush;
	brush.CreateSolidBrush(RGB(60, 60, 60));
	pDC->FillRect(&m_rt, &brush);
	DeleteObject(brush);

	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}
