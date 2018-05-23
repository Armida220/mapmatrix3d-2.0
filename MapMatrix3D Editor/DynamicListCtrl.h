// ������
// 2005 05 20
// ���� List Ctrl ,CHeaderCtrl, Edit Box
// �ṩ��̬�༭�༭���ܣ�EditBoxʧȥ����ʱ�ύ�༭���������Esc��ȡ���༭
// �ṩ��ɫ�����༭
// �ṩ����
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_DYNAMICLISTCTRL_H__83596DF1_D30C_43C5_99DC_8F97BC941951__INCLUDED_)
#define AFX_DYNAMICLISTCTRL_H__83596DF1_D30C_43C5_99DC_8F97BC941951__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DynamicListCtrl.h : header file
//
#include <afxdlgs.h>
//#include "Extend.h"

/////////////////////////////////////////////////////////////////////////////
// CDynamicEdit window

#ifndef _DYNAMIC_EDIT_
#define _DYNAMIC_EDIT_
class /*_EXTEND_DLL_DEF_*/ CDynamicEdit : public CEdit
{
public:
/*	
	CDynamicEdit();
	~CDynamicEdit();*/
	CString	m_strBack;

	// �����Ϊ�գ�ֻ���ַ����ڳ��ֵ��ַ���������
	// ÿ�ιرպ���Զ����
	CString m_strMask;
protected:
	//{{AFX_MSG(CDynamicEdit)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDynamicComboBox window
// ��̬ѡ���
class /*_EXTEND_DLL_DEF_*/ CDynamicComboBox : public CComboBox
{
// Construction
public:
	CDynamicComboBox();
	//virtual ~CDynamicComboBox();
//
	int	m_iSelected;
protected:
	//{{AFX_MSG(CDynamicComboBox)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnCbnSelchange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//void DrawItem(LPDRAWITEMSTRUCT lpdis);
	//BOOL SubclassWindow(HWND hWnd);
	
public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	
};
#endif //_DYNAMIC_EDIT_

/////////////////////////////////////////////////////////////////////////////
// CSortHeaderCtrl window
// ������ʾ����ķ���
#ifndef _SORT_HEADER_CTRL_
#define _SORT_HEADER_CTRL_
class /*_EXTEND_DLL_DEF_*/ CSortHeaderCtrl : public CHeaderCtrl
{
// Construction
public:
	CSortHeaderCtrl();
	virtual ~CSortHeaderCtrl();

// Implementation
public:
	void SetSortArrow( const int iColumn, const BOOL bAscending );

	// Generated message map functions
protected:
	void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );

	int m_iSortColumn;
	BOOL m_bSortAscending;

	//{{AFX_MSG(CSortHeaderCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
#endif //_SORT_HEADER_CTRL_

/////////////////////////////////////////////////////////////////////////////
// CDynamicListCtrl window
// �ṩ��̬�༭�Ĺ���
// �����޸��ı���ɫ�ͱ���
// ���� ItemData Ϊ�յ���

// �༭�Ŀ�ʼ�ͽ���
// wParam : DynamicInfo�ṹָ��
// lParam : û��ʹ��

// ��̬���ڹر�֮ǰ���������ⲿ���޸ĵ�����������
//_EXTEND_DLL_DEF_ extern UINT WM_DYNAMIC_END;
// ��̬������ʾ֮ǰ���������ⲿ����ʼ���Ĳ���
// ������˳�ʼ����������DynamicInfo.iFlag��Ϊ0
//_EXTEND_DLL_DEF_ extern UINT WM_DYNAMIC_START;

#define DYNAMIC_MAX_COL 32

typedef enum {
	modeReadOnly=0,
	modeEdit=1,
	modeCombo=2,
	modeColor=3,
} DynamicMode;
typedef struct tagDynamicDDV
{
	DynamicMode mode;
	short		iMax;
	bool		bNumber;
	bool		bFloat;
	tagDynamicDDV()
	{
		mode = modeReadOnly;
		iMax = 0;
		bNumber = 0;
		bFloat = 0;
	}
}DynamicDDV;
typedef struct tagDynamicInfo
{
	DWORD	dwId;		// listctrl id
	CWnd	*pWnd;		// dynamic window
	int		iRow;		// item
	int		iColumn;	// subitem
	short	sMode;		// ItemMode
	int		iModify;	// �Ƿ����ı�
	int		iFlag;		// �����ǣ�����������Ϣ���˴����޸�Ϊ0,-1��ʾδ������1��ʾ�ܾ�
}DynamicInfo,*PDynamicInfo;


class /*_EXTEND_DLL_DEF_*/ CDynamicListCtrl : public CListCtrl
{
// Construction
public:
	CDynamicListCtrl();
	virtual ~CDynamicListCtrl();
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

// Attributes
public:
	int		m_iItem;
	int		m_iSubItem;
private:
	CDynamicEdit	m_edit;
	CDynamicComboBox	m_combo;
	CColorDialog	m_color;

	BOOL	m_bEdit;
	DynamicDDV	m_dmMode[DYNAMIC_MAX_COL];
	BOOL	m_bCheckData;

	COLORREF	m_crNormal[2];
	COLORREF	m_crSelected[2];
	COLORREF	m_crDisabled[2];

// Operations
public:
	void Refresh();
	int GetNextEnabledItem( int index );
	int GetSelectedEnabledCount();

	// ʵʱ�༭
	void EnableEdit(int nColumn,DynamicDDV mode);
	inline BOOL	IsEditing(){ return m_bEdit; };
	BOOL	EditLabel(int iItem,int iSubItem);
	BOOL	EditRowColor(int iItem);
	int inline GetCurItem(){ return m_iItem; };
	int inline GetCurSubItem(){ return m_iSubItem; };
	void inline CheckData(BOOL bCheckData=FALSE){ m_bCheckData = bCheckData;}

	// ������ɫ����
	// ��ͨ��ѡ�С���Ч
	void SetNormalColor(COLORREF crText,COLORREF crBack);
	void SetSelectedColor(COLORREF crText,COLORREF crBack);
	void SetDisalbedColor(COLORREF crText,COLORREF crBack);
	void inline GetNormalColor(COLORREF &crText,COLORREF &crBack)	{crText = m_crNormal[0];crBack = m_crNormal[1];}
	void inline GetSelectedColor(COLORREF &crText,COLORREF &crBack)	{crText = m_crSelected[0];crBack = m_crSelected[1];}
	void inline GetDisabledColor(COLORREF &crText,COLORREF &crBack)	{crText = m_crDisabled[0];crBack = m_crDisabled[1];}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDynamicListCtrl)
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CDynamicListCtrl)
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnDynamicEnd(WPARAM wParam, LPARAM lParam);
	afx_msg void OnColumnClick( NMHDR* pNMHDR, LRESULT* pResult );
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdraw ( NMHDR* pNMHDR, LRESULT* pResult );
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	// ����
	BOOL m_bSortAscending;
	int m_iSortColumn;
	int m_iNumColumns;
	CSortHeaderCtrl m_ctlHeader;

private:
//	virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );
	static int CALLBACK CompareFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData );
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DYNAMICLISTCTRL_H__83596DF1_D30C_43C5_99DC_8F97BC941951__INCLUDED_)
