// osgMoveWholeSceneZ.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "InterfaceOsgStitcher.h"
#include "osgMoveWholeSceneZ.h"


bool COsgMoveWholeSceneZEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (isActivated)
	{
		osg::ref_ptr<osg::Group> sceneGroup = mRoot->getChild(0)->asGroup();

		int selCnt = iSigEventCallBack->EmitSigSelModelIndex();													//���ѡ��ģ��

		if (selCnt < 0)
		{
			return false;
		}

		osg::ref_ptr<osg::Node> sceneNode = sceneGroup->getChild(selCnt);

		if(IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Up)
			{
				//������ǰ�ƶ�
				double decimal = 0.1;
				KeyPressAdjustWholeScene(0, 0, decimal, sceneNode);
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Down)
			{
				//��������ƶ�
				double decimal = -0.1;
				KeyPressAdjustWholeScene(0, 0, decimal, sceneNode);
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)					 //z
			{
				
			}
		}
	}

	return false;
}

void COsgMoveWholeSceneZEvent::KeyPressAdjustWholeScene(double xDecimal, double yDecimal, double zDecimal, osg::ref_ptr<osg::Node> sceneNode)
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

void COsgMoveWholeSceneZEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	isActivated = isActivate(vecOpState, OPS_EDIT_WHOLE_SCENE_Z);
}
