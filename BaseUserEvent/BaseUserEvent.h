#pragma once
#include "OSG_Plus.h"
#include "publicDefined.h"
#include "operationState.h"



#ifdef USEREVENTLIBDLL  
#define USEREVENTAPI _declspec(dllexport)  
#else  
#define USEREVENTAPI  _declspec(dllimport)  
#endif  

class USEREVENTAPI CBaseUserEvent : public osgGA::GUIEventHandler 
{
public:
	CBaseUserEvent(osgViewer::Viewer* viewer)
	{
		//���òü�Сϸ��
		osg::CullStack::CullingMode cullingMode = viewer->getCamera()->getCullingMode();  
		cullingMode &= ~(osg::CullStack::SMALL_FEATURE_CULLING);  
		viewer->getCamera()->setCullingMode(cullingMode);  
	}

	virtual bool IsKeyPress(const osgGA::GUIEventAdapter &ea);														//�Ƿ񰴼�
																													
	virtual bool IsKeyUp(const osgGA::GUIEventAdapter &ea);															//�Ƿ��ɿ�����
																													
	virtual bool IsLeftClick(const osgGA::GUIEventAdapter &ea);														//�Ƿ����
																													
	virtual bool IsDoubleClick(const osgGA::GUIEventAdapter &ea);													//�Ƿ�˫��
																													
	virtual bool IsRightClick(const osgGA::GUIEventAdapter &ea);													//�Ƿ��һ�
																													
	virtual bool IsMouseMove(const osgGA::GUIEventAdapter &ea);														//�Ƿ�����ƶ�

	virtual CPickResult PickResult(float x, float y, osgViewer::Viewer *mViewer);									//��ײ���

	virtual void ClearGroupResult(osg::ref_ptr<osg::Group> group);													//�������

	virtual double CalLength(std::vector<osg::Vec3d> coord);														//���㳤��

	virtual double CalculateDist(osg::Vec3d pt1, osg::Vec3d pt2);													//�������

	virtual double CalculateArea(std::vector<osg::Vec3d> coord);													//�������

	virtual bool isActivate(std::vector<OperatingState> vecOpState, OperatingState ops);							//�ж��¼��Ƿ񼤻�

	virtual void UpdateActivatedStatus(std::vector<OperatingState> vecOpState) = 0;									//�����¼�����״̬

};