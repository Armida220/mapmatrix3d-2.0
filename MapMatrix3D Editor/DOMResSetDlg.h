#pragma once
#include "resource.h"

// CDOMResSetDlg �Ի���

class CDOMResSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDOMResSetDlg)

public:
	CDOMResSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDOMResSetDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SET_DOM_RES };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString res1;
	double res;
};
