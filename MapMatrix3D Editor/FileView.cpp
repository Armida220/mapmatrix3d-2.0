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

#include "stdafx.h"
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "MapMatrix3D Editor.h"
#include "qcomm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CFileView* g_mfcFileView = NULL;


/////////////////////////////////////////////////////////////////////////////
// CFileView

CFileView::CFileView()
{
	g_mfcFileView = this;
}

CFileView::~CFileView()
{
}

BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar ��Ϣ�������

int CFileView::OnCreate(LPCREATESTRUCT LPCREATESTRUCT)
{
	if (CDockablePane::OnCreate(LPCREATESTRUCT) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// ������ͼ:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_CHECKBOXES;

	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("δ�ܴ����ļ���ͼ\n");
		return -1;      // δ�ܴ���
	}

	// ������ͼͼ��:
	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 3, RGB(255, 255, 255));
	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_STATE);
	m_wndFileView.ModifyStyle( TVS_CHECKBOXES, 0 );
	m_wndFileView.ModifyStyle( 0, TVS_CHECKBOXES );


	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* ������*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// �������ͨ���˿ؼ�·�ɣ�������ͨ�������·��:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	//// ����һЩ��̬����ͼ����(�˴�ֻ������������룬�����Ǹ��ӵ�����)
	//FillFileView();
	AdjustLayout();

	return 0;
}

void CFileView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

std::vector<CString> CFileView::obtainVecFileTitle()
{
	HTREEITEM hItem = m_wndFileView.GetRootItem();
	std::vector<CString> vecCString;
	
	do 
	{
		HTREEITEM hChildItem = m_wndFileView.GetChildItem(hItem);
		CString str = m_wndFileView.GetItemText(hChildItem);
		vecCString.push_back(str);

	} while (hItem = m_wndFileView.GetNextSiblingItem(hItem));

	return vecCString;
}

std::vector<CString> CFileView::obtainVecFilePath()
{
	HTREEITEM hItem = m_wndFileView.GetRootItem();
	std::vector<CString> vecCString;

	do 
	{
		CString str = m_wndFileView.GetItemText(hItem);
		vecCString.push_back(str);

	} while (hItem = m_wndFileView.GetNextSiblingItem(hItem));

	return vecCString;
}

void CFileView::insertItem(CString filePath, CString fileTitle)
{
	HTREEITEM hRoot = m_wndFileView.InsertItem(filePath, 0, 0);
	m_wndFileView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
	
	HTREEITEM hSrc = m_wndFileView.InsertItem(fileTitle, 0, 0, hRoot);
	m_wndFileView.Expand(hRoot, TVE_EXPAND);				//�Զ�չ��
	m_wndFileView.Expand(hSrc, TVE_EXPAND);
	m_wndFileView.SetCheck(hRoot, TRUE);
	m_wndFileView.SetCheck(hSrc, TRUE);
}

void CFileView::deleteAllItem()
{
	HTREEITEM hItem = m_wndFileView.GetRootItem();		//��ȡ�����,���ܻ��ж�������
	
	while(hItem != NULL)
	{
		do
		{
			m_wndFileView.DeleteItem(hItem);
	
		} while(hItem = m_wndFileView.GetNextSiblingItem(hItem));

		hItem = m_wndFileView.GetRootItem();
	}
}

void CFileView::deleteItem(int num)
{
	HTREEITEM hItem = m_wndFileView.GetRootItem();	
	
	for (int i = 0; i < num; i++)
	{
		hItem = m_wndFileView.GetNextSiblingItem(hItem);
	}
	
	m_wndFileView.DeleteItem(hItem);
}

void CFileView::FillFileView()
{
	//HTREEITEM hRoot = m_wndFileView.InsertItem(_T("FakeApp �ļ�"), 0, 0);
	//m_wndFileView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	//HTREEITEM hSrc = m_wndFileView.InsertItem(_T("FakeApp Դ�ļ�"), 0, 0, hRoot);

	//m_wndFileView.InsertItem(_T("FakeApp.cpp"), 1, 1, hSrc);
	//m_wndFileView.InsertItem(_T("FakeApp.rc"), 1, 1, hSrc);
	//m_wndFileView.InsertItem(_T("FakeAppDoc.cpp"), 1, 1, hSrc);
	//m_wndFileView.InsertItem(_T("FakeAppView.cpp"), 1, 1, hSrc);
	//m_wndFileView.InsertItem(_T("MainFrm.cpp"), 1, 1, hSrc);
	//m_wndFileView.InsertItem(_T("StdAfx.cpp"), 1, 1, hSrc);

	//HTREEITEM hInc = m_wndFileView.InsertItem(_T("FakeApp ͷ�ļ�"), 0, 0, hRoot);

	//m_wndFileView.InsertItem(_T("FakeApp.h"), 2, 2, hInc);
	//m_wndFileView.InsertItem(_T("FakeAppDoc.h"), 2, 2, hInc);
	//m_wndFileView.InsertItem(_T("FakeAppView.h"), 2, 2, hInc);
	//m_wndFileView.InsertItem(_T("Resource.h"), 2, 2, hInc);
	//m_wndFileView.InsertItem(_T("MainFrm.h"), 2, 2, hInc);
	//m_wndFileView.InsertItem(_T("StdAfx.h"), 2, 2, hInc);

	//HTREEITEM hRes = m_wndFileView.InsertItem(_T("FakeApp ��Դ�ļ�"), 0, 0, hRoot);

	//m_wndFileView.InsertItem(_T("FakeApp.ico"), 2, 2, hRes);
	//m_wndFileView.InsertItem(_T("FakeApp.rc2"), 2, 2, hRes);
	//m_wndFileView.InsertItem(_T("FakeAppDoc.ico"), 2, 2, hRes);
	//m_wndFileView.InsertItem(_T("FakeToolbar.bmp"), 2, 2, hRes);

	//m_wndFileView.Expand(hRoot, TVE_EXPAND);
	//m_wndFileView.Expand(hSrc, TVE_EXPAND);
	//m_wndFileView.Expand(hInc, TVE_EXPAND);
}

void CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// ѡ���ѵ�������:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	/*theApp.GetContextMenuManager()->ShowPopupMenu(IDR_MENU2, point.x, point.y, this, TRUE);*/

	CMenu menu;
	menu.LoadMenuA(IDR_MENU3);				//���ز˵���Դ
	CMenu *pPopup=menu.GetSubMenu(0);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, point.x, point.y, this);
}

int CFileView::getSelectedItemCount()
{
	HTREEITEM selectedItem = m_wndFileView.GetSelectedItem(); 
	HTREEITEM hItem = m_wndFileView.GetRootItem();		
	int selectedCount = 0;

	do
	{
		if (selectedItem == hItem)
		{
			return selectedCount;
		}
		else
		{
			HTREEITEM hItemChild = m_wndFileView.GetChildItem(hItem);

			if (hItemChild == selectedItem)
			{
				return selectedCount;
			}
		}

		selectedCount++;

	}while(hItem = m_wndFileView.GetNextSiblingItem(hItem));

	return -99;
}

void CFileView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CFileView::OnProperties()
{
	AfxMessageBox(_T("����...."));

}

void CFileView::OnFileOpen()
{
	// TODO: �ڴ˴���������������
}

void CFileView::OnFileOpenWith()
{
	// TODO: �ڴ˴���������������
}

void CFileView::OnDummyCompile()
{
	// TODO: �ڴ˴���������������
}

void CFileView::OnEditCut()
{
	// TODO: �ڴ˴���������������
}

void CFileView::OnEditCopy()
{
	// TODO: �ڴ˴���������������
}

void CFileView::OnEditClear()
{
	// TODO: �ڴ˴���������������
}

void CFileView::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������

	CRect rectTree;
	m_wndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CFileView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFileView.SetFocus();
}

void CFileView::OnChangeVisualStyle()
{
	//m_wndToolBar.CleanUpLockedImages();
	//m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* ����*/);

	//m_FileViewImages.DeleteImageList();

	//UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	//CBitmap bmp;
	//if (!bmp.LoadBitmap(uiBmpId))
	//{
	//	TRACE(_T("�޷�����λͼ: %x\n"), uiBmpId);
	//	ASSERT(FALSE);
	//	return;
	//}

	//BITMAP bmpObj;
	//bmp.GetBitmap(&bmpObj);

	//UINT nFlags = ILC_MASK;

	//nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	//m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	//m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	//m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}


