#pragma once
#include "operationState.h"
#include "OSG_Plus.h"
#include "publicDefined.h"
#include "InterfaceOsgMfcViewer.h"
#include "InterfaceUserEventCallBack.h"
#include "InterfaceOsgEditEvent.h"
#include "InterfaceOsgMeasureEvent.h"
#include "InterfaceOsgOrientEvent.h"
#include "InterfaceOsgMonomerEvent.h"
#include "InterfaceOsgMapperEvent.h"
#include "InterfaceOsgDrawEvent.h"

#include <string>

class MFCVIEWERAPI cOSG : public InterfaceOsgMfcViewer
{
public:
    cOSG(HWND hWnd);
    ~cOSG();

    void InitOSG(std::string modelname);

	HANDLE StartRendering();																						//��ʼ��Ⱦ				

	void AddChild(osg::ref_ptr<osg::Node> parent, osg::ref_ptr<osg::Node> node);									//�ӽڵ�

	void RemoveChild(osg::ref_ptr<osg::Node> parent, osg::ref_ptr<osg::Node> node);									//����ڵ�

	void SetSceneExtent();																							//���ó�����Χ

	osgViewer::Viewer* getViewer();																					//��ȡ�����ָ��

	void RemoveAllChild();																							//������нڵ�

	void AddViewerOPS(std::vector<OperatingState> vecOps);															//�����������������

	void ChangeView(int num);																						//�ı��ӽ�

	InterfaceSigEventCallBack* ObtainISig();																		//��ȡ�źŵĽӿ�

	InterfaceOsgOrientEvent* ObtainOrientEventSlot();																//��ȡ�����¼��۵Ľӿ�

	InterfaceOsgEditEvent* ObtainEditEventSlot();																	//��ȡ�༭�¼��۵Ľӿ�

	InterfaceOsgMapperEvent* ObtainMapperEventSlot();																//��ȡ��ͼ�¼��۵Ľӿ�

	InterfaceOsgMonomerEvent* ObtainMonomerEventSlot();																//��ȡ���廯�¼��۵Ľӿ�

	osg::ref_ptr<osg::Group> ObtainRoot();																			//��ȡ���ڵ�

	void simulateMouseButtonEvent();																				//ģ��������¼�
	

public:
	void PreFrameUpdate(void);
	
	void PostFrameUpdate(void);
	
protected:
    void InitManipulators(void);
    void InitSceneGraph(void);
    void InitCameraConfig(void);

    void Done(bool value) { mDone = value; }
    bool Done(void) { return mDone; }
    static void Render(void* ptr);

	void LookDown();																								//����

	void LookUp();																									//����

	void LeftView();																								//����

	void RightView();																								//����

	void FrontView();																								//ǰ��

	void RearView();																								//����	

	void ShowFillTriangle();																						//��ʾ�������������

	bool LinePickUpPoint(osg::Vec3d start, osg::Vec3d end, osg::Vec3d &worldPt, osg::ref_ptr<osg::Node> pickUpNode);//��ֱ��ײ���


protected:
	InterfaceSigEventCallBack* iSigEventCallBack;

	InterfaceOsgEditEvent* iOsgEditEvent;

	InterfaceOsgOrientEvent* iOsgOrientEvent;
	
	InterfaceOsgMeasureEvent* iOsgMeasureEvent;

	InterfaceOsgMonomerEvent* iOsgMonomerEvent;

	InterfaceOsgDrawEvent* iOsgDrawEvent;

	InterfaceOsgMapperEvent* iOsgMapperEvent;

    bool mDone;
    std::string m_ModelName;
    HWND m_hWnd;
	osg::ref_ptr<osgViewer::Viewer> mViewer;
    osg::ref_ptr<osg::Group> mRoot;
    osg::ref_ptr<osg::Node> mModel;
    osg::ref_ptr<osgGA::TerrainManipulator> trackball;
	osg::ref_ptr<osgGA::TerrainManipulator> terrain;
    osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator;

	//���泡�����ݽڵ���
	osg::ref_ptr<osg::Group> mSceneGroup;
	//���泡���༭��
	osg::ref_ptr<osg::Group> mEditSceneGroup;
	//�����������
	osg::ref_ptr<osg::Group> mViewerGroup;
	//�����ͼ���
	osg::ref_ptr<osg::Group> mMapperGroup;
	//������պнڵ�
	osg::ref_ptr<osg::Group> mSkyBoxGroup;
	//��ʱ��
	osg::ref_ptr<osg::Group> mTempGroup, mTempGroup1, mScopeGroup;

	BOOL isShowFillWireTriangle;

protected:
	void InitialViewerGroup(osg::ref_ptr<osg::Group> mViewerGroup);
	void InitialSkyBox(osg::ref_ptr<osg::Group> mSkyBoxGroup);
	void InitViewerEvent();
};

class CRenderingThread : public OpenThreads::Thread
{
public:
    CRenderingThread( cOSG* ptr );
    virtual ~CRenderingThread();

    virtual void run();

protected:
    cOSG* _ptr;
    bool _done;
};

