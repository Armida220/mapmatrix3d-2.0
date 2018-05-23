// MeasureResultDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainFrm.h"
#include "MeasureResultDlg.h"
#include "afxdialogex.h"
#include "MapMatrix3D Editor.h"
#include "InterfaceMFCExcute.h"
CMeasureResultDlg* g_mfcMeasureResultDlg = NULL;
// CMeasureResultDlg �Ի���

IMPLEMENT_DYNAMIC(CMeasureResultDlg, CDialog)

CMeasureResultDlg::CMeasureResultDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMeasureResultDlg::IDD, pParent)
{
	g_mfcMeasureResultDlg = this;
	isSaved = FALSE;
}

CMeasureResultDlg::~CMeasureResultDlg()
{

}

void CMeasureResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_CATCH, m_check_curve);
	DDX_Control(pDX, IDC_STATIC_Measure_Result, m_Static_Measure_Result);
}


BEGIN_MESSAGE_MAP(CMeasureResultDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CMeasureResultDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_CATCH, &CMeasureResultDlg::OnBnClickedCheckCatch)
	ON_WM_DESTROY()
	ON_WM_CLOSE()

	ON_BN_CLICKED(IDC_BUTTON_OUT_MEASURE_RESULT, &CMeasureResultDlg::OnBnClickedButtonOutMeasureResult)
	ON_BN_CLICKED(IDC_BUTTON_SAVEDATA, &CMeasureResultDlg::OnBnClickedButtonSavedata)
END_MESSAGE_MAP()

// CMeasureResultDlg ��Ϣ�������
BOOL CMeasureResultDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	GetWindowRect(rect);
	ClientToScreen(rect); 
	MoveWindow(100, 200, rect.Width(), rect.Height());

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CMeasureResultDlg::notifyMeasureResult(char* strMsg)
{
	GetDlgItem(IDC_STATIC_Measure_Result)->SetWindowText((LPCTSTR)strMsg);

	resultMsg = strMsg;
	isSaved = FALSE;
	
}




void CMeasureResultDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�������
	GetDlgItem(IDC_STATIC_Measure_Result)->SetWindowText("");
	vecMeasureResult.clear();
	/*std::vector<OperatingState> vecOps;
	vecOps.push_back(OPS_None);
	theApp.IOsgMfcViewer->AddViewerOPS(vecOps);*/
}

void CMeasureResultDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	//theApp.IOsgMfcViewer->SetViewerOPS(OPS_None);
}

void CMeasureResultDlg::closeDlg()
{
	theApp.isPtMeasure = FALSE;
	theApp.isLineMeasure = FALSE;
	theApp.isMultiLineMeasure = FALSE;
	theApp.isAreaMeasure = FALSE;
	
	SendMessage(WM_CLOSE);
}

void CMeasureResultDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	vecMeasureResult.clear();
	CDialog::OnClose();
	std::vector<OperatingState> vecOps;
	vecOps.push_back(OPS_None);
	theApp.IOsgMfcViewer->AddViewerOPS(vecOps);
}

void CMeasureResultDlg::OnBnClickedCheckCatch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//if (m_check_curve.GetCheck() == 1)
	//{
	//	if (g_mfcOSG->mOpState->opState == OPS_MEASURE_LINE)
	//	{
	//		g_mfcOSG->mOpState->opState = OPS_MEASURE_CURLINE;
	//	}
	//	else if (g_mfcOSG->mOpState->opState == OPS_MEASURE_MULTIlINE)
	//	{
	//		g_mfcOSG->mOpState->opState = OPS_MEASURE_MULTICURLINE;
	//	}
	//}
	//else
	//{
	//	if (g_mfcOSG->mOpState->opState == OPS_MEASURE_CURLINE)
	//	{
	//		g_mfcOSG->mOpState->opState = OPS_MEASURE_LINE;
	//	}
	//	else if (g_mfcOSG->mOpState->opState == OPS_MEASURE_MULTICURLINE)
	//	{
	//		g_mfcOSG->mOpState->opState = OPS_MEASURE_MULTIlINE;
	//	}
	//}

}

void CMeasureResultDlg::OnBnClickedButtonOutMeasureResult()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	InterfaceMFCExcuteFactory IExcuteFactory;
	InterfaceMFCExcute* IExcute = IExcuteFactory.create();
	if (vecMeasureResult.empty())
	{
		IExcute->PopUpMessage("�����ݿɵ���");
		return;
	}
	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY, (LPCTSTR)_TEXT("TXT File (*.txt)|*.txt|All Files (*.*)|*.*||"), NULL);

	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();
		CString fileExt = dlg.GetFileExt();

		if (fileExt != _T("txt"))
		{
			filePath += _T(".txt");
		}

		std::string strFilePath = filePath;
		FILE* fpMeasureResult = fopen(strFilePath.c_str(), "w");

		for (int i = 0; i < vecMeasureResult.size(); i++)
		{
			fprintf(fpMeasureResult, "%s\n", vecMeasureResult[i].c_str());
		}

		fclose(fpMeasureResult);
		IExcute->PopUpMessage("���ݵ������");
	}
}


BOOL CMeasureResultDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	static bool m_ctrl_down = false;//�˺�����һ�ε��õ�ʱ���ʼ��
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE ) 
	{
		vecMeasureResult.clear();
		std::vector<OperatingState> vecOps;
		vecOps.push_back(OPS_None);
		theApp.IOsgMfcViewer->AddViewerOPS(vecOps);
		return TRUE;
	}
	

	else if (pMsg->message == WM_KEYDOWN)
	{

		switch (pMsg->wParam)
		{
			//VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A) �����ִ�Сд

		case 'S'://Ctrl + A
			if (m_ctrl_down)
			{
				OnBnClickedButtonSavedata();return TRUE;
			}
			break;
		case VK_CONTROL:
			m_ctrl_down = true;return TRUE;
		default:
			return TRUE;
		}
	}
	if (pMsg->message == WM_KEYUP)
	{
		switch (pMsg->wParam)
		{
		case VK_CONTROL:
			m_ctrl_down = false; return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CMeasureResultDlg::OnBnClickedButtonSavedata()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!resultMsg.empty()&&!isSaved)
	{
		vecMeasureResult.push_back(resultMsg);
		isSaved = TRUE;
		DWORD id = GetThreadLocale();
		std::string strState;
		if (id != 1033)
		{
			strState =  "\n�ѱ���";
		}
		else
			strState =  "\nSaved";
		GetDlgItem(IDC_STATIC_Measure_Result)->SetWindowText((LPCTSTR)(resultMsg+strState).c_str());
	}
}
