// osgMoveWholeSceneXY.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "osgMoveWholeSceneXY.h"
#include "InterfaceOsgStitcher.h"

bool COsgMoveWholeSceneXYEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (isActivated)
	{
		int selCnt = iSigEventCallBack->EmitSigSelModelIndex();										 //���ѡ��ģ��

		if (selCnt < 0)
		{
			return false;
		}
		
		osg::ref_ptr<osg::Group> sceneGroup = mRoot->getChild(0)->asGroup();
		osg::ref_ptr<osg::Node> sceneNode = sceneGroup->getChild(selCnt);

		if(IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Up)
			{
				//������ǰ�ƶ�
				double decimal = 0.1;
				KeyPressAdjustWholeScene(0, decimal, 0, sceneNode);
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Down)
			{
				//��������ƶ�
				double decimal = -0.1;
				KeyPressAdjustWholeScene(0, decimal, 0, sceneNode);
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Left)
			{
				//���������ƶ�
				double decimal = -0.1;
				KeyPressAdjustWholeScene(decimal, 0, 0, sceneNode);
			}
			else if(ea.getKey() == osgGA::GUIEventAdapter::KEY_Right)
			{
				//���������ƶ�
				double decimal = 0.1;
				KeyPressAdjustWholeScene(decimal, 0, 0, sceneNode);
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)					 //z
			{
				//�����ƶ�

			}
		}
	}
	else
	{
		vecWorldCoord.clear();
	}

	return false;
}

void COsgMoveWholeSceneXYEvent::KeyPressAdjustWholeScene(double xDecimal, double yDecimal, double zDecimal, osg::ref_ptr<osg::Node> sceneNode)
{
	//��ȡѡ��ĳ���
	InterfaceOsgStitcherFactory IStitchFactory;
	InterfaceOsgStitcher* IStitch = IStitchFactory.create();

	if (zDecimal == 0)
	{
		IStitch->MoveWholeSceneXY(sceneNode, xDecimal, yDecimal);
	}
	else if (xDecimal == 0 && yDecimal == 0)
	{
		IStitch->MoveWholeSceneZ(sceneNode, zDecimal);
	}

}

void COsgMoveWholeSceneXYEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	isActivated = isActivate(vecOpState, OPS_EDIT_WHOLE_SCENE_XY);
}

