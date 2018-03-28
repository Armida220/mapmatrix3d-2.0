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

// MapMatrix3D EditorView.h : CMapMatrix3DEditorView ��Ľӿ�
//

#pragma once
#include "publicDefined.h"
#include "coord.hpp"
#include <vector>
//#include "MFC_OSG.h"
#include "InterfaceOsgMfcViewer.h"


class CMapMatrix3DEditorView : public CView
{
protected: // �������л�����
	CMapMatrix3DEditorView();
	DECLARE_DYNCREATE(CMapMatrix3DEditorView)

// ����
public:
	CMapMatrix3DEditorDoc* GetDocument() const;

// ����
public:
	//������ʾosg
	/*cOSG* mOSG;*/
	//���ڷ�װview��

	//��CString�������ļ���·��  
	std::vector<CString> ary_filename;  
	//�ж��Ƿ��Ѿ��򿪹��ļ�
	BOOL openFileFlag;
	HANDLE mThreadHandle;
	////����·��
	//CString sceneFileName;
private:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();

public:

protected:

// ʵ��
public:
	virtual ~CMapMatrix3DEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnOpen3dmodel();
	afx_msg void OnRemoveScene();
	afx_msg int OnCreate(LPCREATESTRUCT LPCREATESTRUCT);
	afx_msg void OnDestroy();

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

};

#ifndef _DEBUG  // MapMatrix3D EditorView.cpp �еĵ��԰汾
inline CMapMatrix3DEditorDoc* CMapMatrix3DEditorView::GetDocument() const
   { return reinterpret_cast<CMapMatrix3DEditorDoc*>(m_pDocument); }
#endif

