// DomDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MapMatrix3D Editor.h"
#include "DomDoc.h"


// CDomDoc

IMPLEMENT_DYNCREATE(CDomDoc, CDocument)

CDomDoc::CDomDoc()
{
}

BOOL CDomDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CDomDoc::~CDomDoc()
{
}


BEGIN_MESSAGE_MAP(CDomDoc, CDocument)
END_MESSAGE_MAP()


// CDomDoc ���

#ifdef _DEBUG
void CDomDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CDomDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CDomDoc ���л�

void CDomDoc::Serialize(CArchive& ar)
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
#endif


// CDomDoc ����
