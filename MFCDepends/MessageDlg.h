#pragma once
#include <string>
#include "resource.h"
// CMessageDlg �Ի���

class CMessageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMessageDlg)

public:
	CMessageDlg(std::string strTipInfo,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMessageDlg();

	// �Ի�������
	enum { IDD = IDD_DIALOG_MESSAGE };
	void ShowMsgWindow(); 
	void CenterScreen();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();  
	virtual BOOL PreTranslateMessage(MSG* pMsg);  

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

private:  
	std::string m_strTipInfo;    
	BYTE m_bAlpha;//���뵭��͸��Ч�� 
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
