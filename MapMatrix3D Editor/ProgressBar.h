#pragma once
#include "resource.h"
#include "afxcmn.h"
// CProgressBar �Ի���


class CProgressBar : public CDialogEx
{
	DECLARE_DYNAMIC(CProgressBar)
public:
	CProgressBar(CWnd* pParent = NULL);   // ��׼���캯��
	void ChangeStaticText(CString posStr);
	virtual ~CProgressBar();

// �Ի�������
	enum { IDD = IDD_DIALOG_PROGRESS_BAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	int pos;
	CProgressCtrl m_ProgressBar;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
