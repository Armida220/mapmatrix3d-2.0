#pragma once


// CHeightSetDlg �Ի���

class CHeightSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHeightSetDlg)

public:
	CHeightSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHeightSetDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SET_HEIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString res1;
	double res;
	afx_msg void OnBnClickedOk();
};
