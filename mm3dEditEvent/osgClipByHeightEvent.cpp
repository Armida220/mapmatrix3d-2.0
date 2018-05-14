// osgClipByHeightEvent.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "osgClipByHeightEvent.h"
#include "InterfaceOsgFinder.h"
#include "InterfaceMFCExcute.h"
#include "InterfaceOsgClipByHeight.h"

void COsgClipByHeightEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false; 
	reFactor = 1;
	if (isActivated == true)
	{
		flag = true;
	}

	isActivated = isActivate(vecOpState, OPS_CLIP_BY_HEIGHT);

	if (isActivated == false && flag == true)																	
	{
		//��Ϣ�ÿ�
		iSigEventCallBack->EmitSigShowOpsHint("");
	}

	if (isActivated && flag == false)																//�ռ���
	{
		iSigEventCallBack->EmitSigShowOpsHint("�����¼��������и߶ȣ���ESC�˳��¼�");
	}
}

bool COsgClipByHeightEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (isActivated)
	{
		if (IsKeyPress(ea))
		{
			osg::ref_ptr<osg::Group> sceneGroup = mRoot->getChild(0)->asGroup();

			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Up)
			{
				//���������ƶ� ������
				double increaseH = 0.5;
				KeyDownMoveClipByHeight(increaseH, reFactor, sceneGroup);
				iSigEventCallBack->EmitSigShowOpsHint("��Z������");
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Down)
			{
				//���������ƶ� ������
				double increaseH = -0.5;
				KeyDownMoveClipByHeight(increaseH, reFactor, sceneGroup);
				iSigEventCallBack->EmitSigShowOpsHint("��Z������");
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)					 //z ����
			{
				osg::ref_ptr<osg::Group> sceneGroup = mRoot->getChild(0)->asGroup();
				KeyCtrlZReverseClipByHeight(sceneGroup);
				iSigEventCallBack->EmitSigShowOpsHint("");
				isActivated = false;
			}
		}
	}

	return false;
}

void COsgClipByHeightEvent::ClipHeight()
{
	//���ݼ��������߶Ȼ�׼��
	osg::BoundingSphere bound = mRoot->getChild(0)->getBound();
	osg::Vec3f newCenter = bound.center();
	osg::Vec4f color(0.f, 1.f, 1.f, 0.8f);
	double radius = bound.radius();
	osg::ref_ptr<osg::Group> sceneGroup = mRoot->getChild(0)->asGroup();

	clipHeight = newCenter.z();

	InterfaceOsgClipByHeightFactory iOsgClipByHeightFactory;
	InterfaceOsgClipByHeight* iOsgClipByHeight = iOsgClipByHeightFactory.create();
	iOsgClipByHeight->StartClipSceneByHeight(newCenter.z(), reFactor, sceneGroup);										//��ʼ���߶Ȳ��г���
}

void COsgClipByHeightEvent::InvertClipByHeight()
{
	if (!isActivated)
	{
		InterfaceMFCExcuteFactory IExcuteFactory;
		InterfaceMFCExcute* IExcute = IExcuteFactory.create();
		IExcute->PopUpMessage("δ���ø߶Ȳ�����");
		return;
	}

	reFactor = reFactor * -1;

	osg::ref_ptr<osg::Group> sceneGroup = mRoot->getChild(0)->asGroup();
	osg::ref_ptr<osg::ClipNode> clipNode = dynamic_cast<osg::ClipNode*>(sceneGroup->getChild(0));
	InterfaceOsgClipByHeightFactory iOsgClipByHeightFactory;
	InterfaceOsgClipByHeight* iOsgClipByHeight = iOsgClipByHeightFactory.create();
	iOsgClipByHeight->ResetClipHeightAndRefactor(clipHeight, reFactor, clipNode);
}

void COsgClipByHeightEvent::KeyCtrlZReverseClipByHeight(osg::ref_ptr<osg::Group> mSceneGroup)
{
	osg::ref_ptr<osg::ClipNode> clipNode = dynamic_cast<osg::ClipNode*>(mSceneGroup->getChild(0));

	if (clipNode)
	{
		int numClipPlane = clipNode->getNumClipPlanes();

		if (numClipPlane > 1)
		{
			for (int i = numClipPlane;i>1;i--)
			{
				clipNode->removeClipPlane(i - 1);
			}

			osg::ref_ptr<osg::Node> oriNode = clipNode->getChild(0);
			mSceneGroup->replaceChild(clipNode, oriNode);
		}
		else if (numClipPlane == 1)
		{
			osg::ref_ptr<osg::Node> oriNode = clipNode->getChild(0);
			mSceneGroup->replaceChild(clipNode, oriNode);
		}
	}
}

void COsgClipByHeightEvent::KeyDownMoveClipByHeight(double moveY, double reFactor, osg::ref_ptr<osg::Group> mSceneGroup)
{
	//�ƶ����̽��в���
	osg::ref_ptr<osg::ClipNode> clipNode = dynamic_cast<osg::ClipNode*>(mSceneGroup->getChild(0));
	InterfaceOsgClipByHeightFactory iOsgClipByHeightFactory;
	InterfaceOsgClipByHeight* iOsgClipByHeight = iOsgClipByHeightFactory.create();

	if (clipNode)
	{
		iOsgClipByHeight->ResetClipHeightAndRefactor(clipHeight, reFactor, clipNode);
		clipHeight += moveY;
	}
}
