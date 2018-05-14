#pragma once
#include "boost/signals2/signal.hpp"

#ifdef USEREVENTLIBDLL  
#define USEREVENTAPI _declspec(dllexport)  
#else  
#define USEREVENTAPI  _declspec(dllimport)  
#endif  



template<typename T>
struct result_handler
{
	typedef T result_type;

	template<typename InputIterator>
	T operator() (InputIterator first,InputIterator last) const
	{
		return T(first,last);
	}
};


class USEREVENTAPI InterfaceSigEventCallBack
{
public:
	virtual boost::signals2::signal<void ()>* ObtainSigStartProgress() = 0;														//��ÿ�ʼ�������ź�

	virtual void EmitSigStartProgressFun() = 0;																					//���Ϳ�ʼ�������ź�

	virtual boost::signals2::signal<void ()>* ObtainSigEndProgress() = 0;														//��ý����������ź�

	virtual void EmitSigEndProgressFun() = 0;																					//���ͽ����������ź�

	virtual	boost::signals2::signal<int (), result_handler<std::vector<int>>>* ObtainSigSelModelIndex() = 0;					//��ȡѡ��ģ���ź�

	virtual int EmitSigSelModelIndex() = 0;																						//����ѡ��ģ���ź�

	virtual boost::signals2::signal<void (int)>* ObtainSigSetProgress() = 0;													//������ý��ȵ��ź�

	virtual void EmitSigSetProgressFun(int) = 0;																				//�������ý����ź�

	virtual boost::signals2::signal<void (int, double, double, double, bool)>* ObtainSigRelativePt() = 0;						//�����Դ̵��ź�

	virtual void EmitSigObtainRelativePoint(int ptNum, double xRelaPt, double yRelaPt, double zRelaPt, bool isCheckPt) = 0;		//������Ե��ź�
																												
	virtual boost::signals2::signal<int (), result_handler<std::vector<int>>>* ObtainSigGetSelPtNumFromAbsDlg() = 0;			//��þ��Զ���Ի����ѡ����

	virtual int EmitSigGetSelPtNumFromAbsDlg() = 0;																				//���ͻ�þ��Զ���Ի����ѡ����

	virtual boost::signals2::signal<int (), result_handler<std::vector<int>>>* ObtainSigGetSelRowFromAbsDlg() = 0;				//��ȡ���Զ���Ի����ѡ����

	virtual int EmitSigGetSelRowFromAbsDlg() = 0;																				//���ͻ�þ��Զ���Ի����ѡ����

	virtual boost::signals2::signal<void  (char*)>* ObtainSigNotifyMeasureMsg() = 0;											//���֪ͨ�������ź�

	virtual void EmitSigNotifyMeasureMsg(char* strMsg) = 0;																		//����֪ͨ�������ź�

	virtual boost::signals2::signal<void  (void)>* ObtainSigCloseMeasureDlg() = 0;												//��ùرղ������ź�

	virtual void EmitSigCloseMeasureDlg() = 0;																					//���͹رղ������ź�

	virtual boost::signals2::signal<void  (void)>* ObtainSigCloseAbsDlg() = 0;													//��ùرն�����ź�

	virtual void EmitSigCloseAbsDlg() = 0;																						//���͹رն�����ź�

	virtual boost::signals2::signal<bool (), result_handler<std::vector<bool>>>* ObtainSigChangeCtrlList() = 0;					//��øı�����б��ź�

	virtual bool EmitSigChangeCtrlList() = 0;																					//���͸ı�����б��ź�

	virtual boost::signals2::signal<void ()>* ObtainSigRemoveAllScene() = 0;													//���������г����ź�

	virtual void EmitSigRemoveAllScene() = 0;																					//����������г����ź�

	virtual boost::signals2::signal<void (char*)>* ObtainSigAddScene() = 0;														//������ӳ����ź�

	virtual void EmitSigAddScene(char* strName) = 0;																			//�������ӳ����ź�

	virtual boost::signals2::signal<void (int, double, double, double)>* ObtainSigInsertCtrlListRecord() = 0;					//��ȡ��������б��¼�ź�

	virtual void EmitSigInsertControlListRecord(int ptNum, double ptX, double ptY, double ptZ) = 0;								//���Ͳ�������б��¼

	virtual boost::signals2::signal<void (char*)>* ObtainSigShowOpsHint() = 0;													//�����ʾ״̬������ʾ���ź�

	virtual void EmitSigShowOpsHint(char* strHint) = 0;																			//������ʾ״̬������ʾ���ź�

	virtual boost::signals2::signal<void (char*)>* ObtainSigLinkPropertyListDlg() = 0;											//��õ��廯�������ԶԻ���

	virtual void EmitSigLinkPropertyListDlg(char* sigPropertyListName) = 0;														//���͹������Բ˵��Ի���

	virtual boost::signals2::signal<void(int, int)>* obtainSigObjectMenuDlg() = 0;												//��ȡ�������廯�˵��ĶԻ���

	virtual void EmitSigObjectMenuDlg(int mouseX, int mouseY) = 0;																//���͵��廯�˵����ź�
};

class USEREVENTAPI InterfaceSigEventCallBackFactory
{
public:
	InterfaceSigEventCallBack* create();
};