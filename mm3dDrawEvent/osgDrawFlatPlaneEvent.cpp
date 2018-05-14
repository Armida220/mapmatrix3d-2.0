// osgDrawFlatPlaneEvent.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "InterfaceOsgStitcher.h"
#include "InterfaceOsgFinder.h"
#include "osgDrawFlatPlaneEvent.h"

bool COsgDrawFlatPlaneEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (isActivated)
	{
		if(IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Up)
			{
				//������ǰ�ƶ�
				double decimal = 0.5;
				KeyPressAdjustDrawHeight(decimal, mEditSceneGroup);
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Down)
			{
				//��������ƶ�
				double decimal = -0.5;
				KeyPressAdjustDrawHeight(decimal, mEditSceneGroup);
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)
			{
				ClearGroupResult(mEditSceneGroup);
			}
		}
	}
	else
	{
		vecWorldCoord.clear();
	}

	return false;
}


void COsgDrawFlatPlaneEvent::KeyPressAdjustDrawHeight(double zDecimal, osg::ref_ptr<osg::Node> node)
{
	//��ȡѡ��ĳ���
	InterfaceOsgStitcherFactory IStitchFactory;
	InterfaceOsgStitcher* IStitch = IStitchFactory.create();
	IStitch->MoveWholeSceneZ(node, zDecimal);
}

void COsgDrawFlatPlaneEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false; 

	if (isActivated == true)
	{
		flag = true;
	}

	isActivated = isActivate(vecOpState, OPS_DRAW_FLAT_PLANE);

	if (isActivated == true && flag == false)
	{
		ClearGroupResult(mEditSceneGroup);
		DrawFlatPlaneByHeight();
	}
	if (isActivated == false && flag == true)
	{
		ClearGroupResult(mEditSceneGroup);
		vecWorldCoord.clear();
	}
}

void COsgDrawFlatPlaneEvent::DrawFlatPlaneByHeight()
{
	//���ݼ��������߶Ȼ�׼��
	osg::BoundingSphere bound = mRoot->getChild(0)->getBound();
	osg::Vec3f newCenter = bound.center();
	osg::Vec4f color(0.f, 1.f, 1.f, 0.8f);
	double radius = bound.radius();
	double size = 4.0;
	
	InterfaceOsgFinderFactory IFinderFactory;
	InterfaceOsgFinder* IFinder = IFinderFactory.create();

	osg::ref_ptr<osg::Node> sceneNode = mRoot->getChild(0)->asGroup()->getChild(0);
	std::vector<osg::MatrixTransform*> vecTrans;
	IFinder->FindTransNode(sceneNode, vecTrans);

	if (vecTrans.size() == 0)
	{
		return;
	}

	osg::Matrix worldMatrix = vecTrans[0]->getMatrix();
	IBaseDrawer->BaseDrawCircleLoopOperate(newCenter, radius, color, size, mEditSceneGroup, worldMatrix);
}
