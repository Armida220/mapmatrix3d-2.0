// MessageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCDepends.h"
#include "MessageDlg.h"
#include "afxdialogex.h"

const UINT_PTR BLAND_IN = 1;  
const UINT_PTR DLG_DELAY = 2;  
const UINT_PTR BLAND_OUT = 3;  

const UINT IN_ELAPSE = 40;  
const UINT DELAY_ELAPSE = 800;  
const UINT OUT_ELAPSE = 40;  

//���뵭�����  
const BYTE BLAND_SPAN = 15;  
//���뵭����Сֵ  
const BYTE BLAND_MIN = 0;  
//���뵭�����ֵ  
const BYTE BLAND_MAX = 255*0.8;  
//���뵭����ɫֵ����  
const COLORREF BLAND_COLOR = 0;
// CMessageDlg �Ի���

IMPLEMENT_DYNAMIC(CMessageDlg, CDialogEx)

CMessageDlg::CMessageDlg(std::string str,CWnd* pParent /*=NULL*/)
	: CDialogEx(CMessageDlg::IDD, pParent)
	, m_strTipInfo(str)  
	, m_bAlpha(0) 
{
	
}

CMessageDlg::~CMessageDlg()
{
}

void CMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMessageDlg, CDialogEx)
	ON_WM_TIMER()  
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMessageDlg ��Ϣ�������
BOOL CMessageDlg::OnInitDialog()  
{  
	CDialog::OnInitDialog();  
	
	// TODO:  Add extra initialization here 
	if (m_strTipInfo.length()<=36)
	{
		m_strTipInfo = "\n"+m_strTipInfo;
	}
	CString cstr(m_strTipInfo.c_str());
	SetDlgItemText(IDC_STATIC_MESSAGE, cstr);  


	CenterScreen();
	//InitDlgPosition();  

	//���ô��ڿɵ��뵭��  
	ModifyStyleEx(NULL, WS_EX_LAYERED);  

	//��Ϣ���뽥��Ч��  
	SetTimer(BLAND_IN, IN_ELAPSE, NULL);  

	static CFont m_font;

	m_font.CreateFont(
		20,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
		_T("΢���ź�"));                 // lpszFacename
	GetDlgItem(IDC_STATIC_MESSAGE)->SetFont(&m_font);

	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE)|WS_EX_LAYERED);
	SetLayeredWindowAttributes(0,0,LWA_ALPHA);
	return TRUE;  
}  


void CMessageDlg::OnTimer(UINT_PTR nIDEvent)  
{  
	RECT rect;  
	SystemParametersInfo(SPI_GETWORKAREA,0,&rect,0);  
	int cy = rect.bottom-rect.top;  
	int cx = rect.right-rect.left;  

	CRect rectTip;  
	GetWindowRect(&rectTip);  

	switch (nIDEvent)  
	{  
	case BLAND_IN:  
		{  
			if (m_bAlpha > (BLAND_MAX - BLAND_SPAN))  
			{  
				m_bAlpha = BLAND_MAX;  
			}  
			else  
			{  
				m_bAlpha += BLAND_SPAN;  
			}  

			SetLayeredWindowAttributes(BLAND_COLOR, m_bAlpha, LWA_ALPHA);  

			if (BLAND_MAX == m_bAlpha)  
			{  
				KillTimer(BLAND_IN);  

				SetTimer(DLG_DELAY, DELAY_ELAPSE, NULL);  
			}  

			break;  
		}  
	case DLG_DELAY:  
		{  
			KillTimer(DLG_DELAY);  
			SetTimer(BLAND_OUT, OUT_ELAPSE, NULL);  

			break;  
		}  
	case BLAND_OUT:  
		{  
			if (m_bAlpha < BLAND_SPAN)  
			{  
				m_bAlpha = BLAND_MIN;  
			}  
			else  
			{  
				m_bAlpha -= BLAND_SPAN;  
			}  

			SetLayeredWindowAttributes(BLAND_COLOR, m_bAlpha, LWA_ALPHA);  

			if (BLAND_MIN == m_bAlpha)  
			{  
				KillTimer(BLAND_OUT);  
				PostMessage(WM_CLOSE);  
			}  

			break;  
		}  
	}  

	CDialog::OnTimer(nIDEvent);  
}

BOOL CMessageDlg::PreTranslateMessage(MSG* pMsg)  
{  
	//�Ի�������Enter��ESC��  
	if (WM_KEYDOWN == pMsg->message)  
	{  
		if (    (VK_RETURN == pMsg->wParam)  
			|| (VK_ESCAPE == pMsg->wParam))  
		{  
			return TRUE;  
		}  
	}  

	return CDialog::PreTranslateMessage(pMsg);  
}  

void CMessageDlg::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CPaintDC   dc(this);   
	CRect   rect;   
	GetClientRect(&rect);   
	CDC   dcMem;   
	dcMem.CreateCompatibleDC(&dc);   
	CBitmap   bmpBackground;   
	bmpBackground.LoadBitmap(IDB_BITMAP1);   //IDB_BITMAP�����Լ���ͼ��Ӧ��ID   �������Ҹոռ����λͼ��Դ 
	//������������IDB_Bg�������������bmpBackground.LoadBitmap(IDB_Bg);  

	BITMAP   bitmap;   
	bmpBackground.GetBitmap(&bitmap);   
	CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,   
		bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);   
}


HBRUSH CMessageDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if(nCtlColor == CTLCOLOR_STATIC ) 
	{ 
		pDC->SetBkMode(TRANSPARENT);//���ñ���͸�� 
		pDC->SetTextColor(RGB(255,255,255));//��������Ϊ��ɫ 

		return (HBRUSH)::GetStockObject(NULL_BRUSH); 
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CMessageDlg::CenterScreen()
{
	//ShowWindow(SW_NORMAL);  
	CRect rtDesk;  
	CRect rtDlg;  
	::GetWindowRect(::GetDesktopWindow(), &rtDesk);  
	GetWindowRect(&rtDlg);  
	int iXpos = rtDesk.Width() / 2 - rtDlg.Width() / 2;  
	int iYpos = rtDesk.Height() / 2 - rtDlg.Height() / 2;  
	SetWindowPos(NULL, iXpos, iYpos, 0, 0, SWP_NOOWNERZORDER|SWP_NOSIZE|SWP_NOZORDER);  
}