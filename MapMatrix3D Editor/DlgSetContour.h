#pragma once


// DlgSetContour �Ի���

class DlgSetContour : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSetContour)

public:
	DlgSetContour(double zmax = 0,double zmin = 0, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgSetContour();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SET_CONTOUR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_zmax;
	double m_zmin;
	double m_zstart;
	double m_zend;
	double m_zspan;
};
