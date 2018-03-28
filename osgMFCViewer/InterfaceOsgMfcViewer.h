#pragma once
#include <string>
#include "OSG_Plus.h"
#include "publicDefined.h"
#include "InterfaceOsgMfcViewer.h"
#include "InterfaceUserEventCallBack.h"
#include "InterfaceOsgEditEvent.h"
#include "InterfaceOsgOrientEvent.h"
#include "InterfaceOsgMonomerEvent.h"
#include "InterfaceOsgMapperEvent.h"

#ifdef MFCVIEWERIBDLL  
#define MFCVIEWERAPI _declspec(dllexport)  
#else  
#define MFCVIEWERAPI  _declspec(dllimport)  
#endif  


class MFCVIEWERAPI InterfaceOsgMfcViewer
{
public:
	virtual void InitOSG(std::string modelname) = 0;																	//����ģ��

	virtual HANDLE StartRendering() = 0;																				//��ʼ��Ⱦ

	virtual void AddChild(osg::ref_ptr<osg::Node> parent, osg::ref_ptr<osg::Node> node) = 0;							//�ӽڵ�

	virtual void RemoveChild(osg::ref_ptr<osg::Node> parent, osg::ref_ptr<osg::Node> node) = 0;							//����ڵ�

	virtual void RemoveAllChild() = 0;																					//�Ƴ����нڵ�

	virtual void SetSceneExtent() = 0;																					//���÷�Χ

	virtual void AddViewerOPS(std::vector<OperatingState> vecOps) = 0;													//��������������¼�

	virtual void ChangeView(int num) = 0;																				//�ı��ӽ� 0ǰ 1��	2�� 3�� 4�� 5��

	virtual void ShowFillTriangle() = 0;																				//��ʾ�������������Ƭ

	virtual osgViewer::Viewer* getViewer() = 0;																			//��ȡ�����

	virtual osg::ref_ptr<osg::Group> ObtainRoot() = 0;																	//��ȡroot�ڵ�	

	virtual InterfaceSigEventCallBack* ObtainISig() = 0;																//��ȡ�źŵĽӿ�

	virtual InterfaceOsgOrientEvent* ObtainOrientEventSlot() = 0;														//��ȡ�����¼��۽ӿ�

	virtual InterfaceOsgEditEvent* ObtainEditEventSlot() = 0;															//��ȡ�༭�¼��۵Ľӿ�

	virtual InterfaceOsgMapperEvent* ObtainMapperEventSlot() = 0;														//��ȡ�༭�¼��۵Ľӿ�

	virtual InterfaceOsgMonomerEvent* ObtainMonomerEventSlot() = 0;														//��ȡ���廯�¼��۵Ľӿ�

	virtual void simulateMouseButtonEvent() = 0;																		//ģ��������¼�
};


class MFCVIEWERAPI InterfaceOsgMfcViewerFactory
{
public:
	InterfaceOsgMfcViewer* create(HWND hWnd);
};

