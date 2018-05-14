#pragma once
#include "InterfaceOsgOrient.h"
#include <vector>
#include "resource.h"
#include "DynamicListCtrl.h"
#include "afxwin.h"


// CAbsoluteOrientationDlg �Ի���

class CAbsoluteOrientationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAbsoluteOrientationDlg)

public:
	CAbsoluteOrientationDlg(CWnd* pParent, std::vector<CString> VecSceneFileName);   // ��׼���캯��
	virtual ~CAbsoluteOrientationDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_ABSOLUTE_ORIENTATION };

public:
	int getNumColumn();																								//��ȡ�б�����				
	void setRelativePoint(int ptNum, double xCtrlPt, double yCtrlPt, double zCtrlPt, bool isCheckPt);				//������������
	void insertNewColumn(int ptNum, double xClickPt, double yClickPt, double zClickPt);								//��������
	int  ObtainSelectedRow();																						//��ȡѡ����
	//void ObtainImageControlPoint(double xImageCtrlPt, double yImageCtrlPt, double zImageCtrlPt, bool isCheckPt);  //��ȡӰ����Ƶ�
	void ObtainModelRelaPoint(int ptNum, double xRelaPt, double yRelaPt, double zRelaPt, bool isCheckPt);			//��ȡģ�Ϳ��Ƶ�
	CString ObtainSelectedPtNum();																					//��ȡѡ����
	bool InsertControlListCompleteStatus();																			//����ѡ�������״̬	
	bool isAlreadyClicked();																							//�Ƿ��Ѿ��̹�

	void InsertControlListRecord(int ptNum, double ptX, double ptY, double ptZ);									//�б�����¼
	void closeDlg();  //�رնԻ���
public:
	//QyManipulatorMode qMode; 
	CDynamicComboBox m_ComboBox1;
	CDynamicListCtrl m_list_control_point;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	//int ObtainControlListRowText(std::vector<CoordDouble3D> &vecAbsoluteCoord, std::vector<CoordDouble3D> &vecRelaCoord);
	
	bool ChangeCompleteStatusByRow(int row);
	void ChangeCompleteStatusByPtNum(int ptNum);
	void ClearCompleteStatusInList();
private:
	afx_msg void OnBnClickedLoadControlPoint();
	afx_msg void OnBnClickedAbsoluteOrientaton();
	afx_msg void OnClose();
	afx_msg void OnSetAsCheckPoint();
	afx_msg void OnRclickListControlPoint(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnInsertRecord();
	afx_msg void OnReclickControlPoint();
	afx_msg void OnClickListControlPoint(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSaveClickPtResult();
	afx_msg void OnBnClickedLoadClickPtResult();



public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
