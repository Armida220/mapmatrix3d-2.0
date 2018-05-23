// HeightSetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MapMatrix3D Editor.h"
#include "HeightSetDlg.h"
#include "afxdialogex.h"


// CHeightSetDlg �Ի���

IMPLEMENT_DYNAMIC(CHeightSetDlg, CDialogEx)

CHeightSetDlg::CHeightSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHeightSetDlg::IDD, pParent)
	, res1(_T(""))
{

}

CHeightSetDlg::~CHeightSetDlg()
{
}

void CHeightSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, res1);
}


BEGIN_MESSAGE_MAP(CHeightSetDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CHeightSetDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CHeightSetDlg ��Ϣ�������


void CHeightSetDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (res1.IsEmpty() )
	{
		return;
	}
	res = atof(res1);
	UpdateData(FALSE);
	CDialogEx::OnOK();
}
