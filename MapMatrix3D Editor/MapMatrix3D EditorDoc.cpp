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

// MapMatrix3D EditorDoc.cpp : CMapMatrix3DEditorDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MapMatrix3D Editor.h"
#endif

#include "MapMatrix3D EditorDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMapMatrix3DEditorDoc

IMPLEMENT_DYNCREATE(CMapMatrix3DEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMapMatrix3DEditorDoc, CDocument)
END_MESSAGE_MAP()


// CMapMatrix3DEditorDoc ����/����

CMapMatrix3DEditorDoc::CMapMatrix3DEditorDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CMapMatrix3DEditorDoc::~CMapMatrix3DEditorDoc()
{
}

BOOL CMapMatrix3DEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	//CMapMatrix3DEditorApp* p_app = (CMapMatrix3DEditorApp*) AfxGetApp();
	//createNewWindow(p_app->pDocTemplateSecond, this); 

	return TRUE;
}


CFrameWnd* CMapMatrix3DEditorDoc::createNewWindow(CDocTemplate *pTemplate, CDocument *pDocument)
{
	ASSERT_VALID(pTemplate);   
	ASSERT_VALID(pDocument);   
	CFrameWnd* pFrame = pTemplate->CreateNewFrame(pDocument, NULL);
	
	if( pFrame == NULL )   
	{
       TRACE0( "Warning: failed to Create new frame.\n" );   
       return NULL;   
    }   
	
	CRect rect;
	GetClientRect(pFrame->m_hWnd, &rect);
	pFrame->MoveWindow(0, 0, rect.Width() / 2, rect.Height());
	ASSERT_KINDOF(CFrameWnd, pFrame);   
	pTemplate->InitialUpdateFrame(pFrame, pDocument);   
	
	return pFrame;  
}

// CMapMatrix3DEditorDoc ���л�

void CMapMatrix3DEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CMapMatrix3DEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.createFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CMapMatrix3DEditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CMapMatrix3DEditorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMapMatrix3DEditorDoc ���

#ifdef _DEBUG
void CMapMatrix3DEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMapMatrix3DEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMapMatrix3DEditorDoc ����
