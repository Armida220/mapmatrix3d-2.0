#pragma once


// DLGHatchSetting �Ի���

class DLGHatchSetting : public CDialogEx
{
	DECLARE_DYNAMIC(DLGHatchSetting)

public:
	DLGHatchSetting(double step = 10, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DLGHatchSetting();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SET_HATCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double mStep;
};
