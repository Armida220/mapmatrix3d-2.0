// osgSceneMatchEvent.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "InterfaceOsgOrient.h"
#include "osgSceneMatchEvent.h"
#include "InterfaceMFCExcute.h"
#include "qcomm.h"

COsgSceneMatchEvent::COsgSceneMatchEvent(osgViewer::Viewer *viewer, osg::Group *root, osg::Group* editGroup, InterfaceSigEventCallBack* iSigEventCallBack) : CBaseUserEvent(viewer)
{
	mViewer = viewer;
	mRoot = root;
	mEditGroup = editGroup;
	this->iSigEventCallBack = iSigEventCallBack;
	isActivated = false;
}


bool COsgSceneMatchEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (isActivated)
	{
		if (IsLeftClick(ea) && GetKeyState(VK_CONTROL) < 0)
		{
			CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pickResult.worldPt;

			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}

			int totalNum = vecWorldCoord.size();
			vecWorldCoord.push_back(worldPt);

			if (totalNum % 2 == 1)
			{
				vecRelaCoord.push_back(worldPt);
			}
			else
			{
				vecAbsCoord.push_back(worldPt);
			}

			iSigEventCallBack->EmitSigShowOpsHint("��Backspace������һ���㣬�һ��ļ��б��ģ�ͽ���ƥ��");
		}
		else if (IsMouseMove(ea) && GetKeyState(VK_CONTROL) < 0)
		{
			
		}
		else if(IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_BackSpace)					 //BackSpace
			{
				//�س�һ����
				int totalNum = vecWorldCoord.size();

				if (totalNum % 2 == 0)
				{
					vecRelaCoord.pop_back();
				}
				else
				{
					vecAbsCoord.pop_back();
				}

				vecWorldCoord.pop_back();
				iSigEventCallBack->EmitSigShowOpsHint("�������Ҫ����ģ�͵�ͬ���㣬Ȼ������ο�ģ�͵�ͬ���㣬��ESC�˳��¼�");
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)
			{
				osg::ref_ptr<osg::Group> sceneGroup = mRoot->getChild(0)->asGroup();

				int selCnt = iSigEventCallBack->EmitSigSelModelIndex();													//���ѡ��ģ��

				if (selCnt < 0)
				{
					return false;
				}

				osg::ref_ptr<osg::Node> sceneNode = sceneGroup->getChild(selCnt);

				InterfaceOsgOrientFactory IOrientFactory;
				InterfaceOsgOrient* IOrient = IOrientFactory.create();
				IOrient->ReverseModelOrientation(sceneNode, absMatrix);

				osg::Matrix matrix;
				absMatrix = matrix;
				iSigEventCallBack->EmitSigShowOpsHint("�������Ҫ����ģ�͵�ͬ���㣬Ȼ������ο�ģ�͵�ͬ���㣬��ESC�˳��¼�");
			}
		}
	}
	else
	{
		vecAbsCoord.clear();
		vecRelaCoord.clear();
		vecWorldCoord.clear();
	}

	return false;
}

void COsgSceneMatchEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false; 

	if (isActivated == true)
	{
		flag = true;
	}

	isActivated = isActivate(vecOpState, OPS_MODEL_MATCHING);

	if (isActivated == false && flag == true)																	
	{
		//��Ϣ�ÿ�
		iSigEventCallBack->EmitSigShowOpsHint("");
	}

	if (isActivated && flag == false)																//�ռ���
	{
		iSigEventCallBack->EmitSigShowOpsHint("�������Ҫ����ģ�͵�ͬ���㣬Ȼ������ο�ģ�͵�ͬ���㣬��ESC�˳��¼�");
	}
}

void COsgSceneMatchEvent::MatchSingleModel()
{
	// TODO: �ڴ���������������
	if (vecRelaCoord.size() < 3 && vecAbsCoord.size() < 3)
	{
		InterfaceMFCExcuteFactory IMFCExecuteFactory;
		InterfaceMFCExcute* IMFCExecute = IMFCExecuteFactory.create();
		IMFCExecute->PopUpMessage("ͬ�����������С��3");
		return;
	}

	int selModel = iSigEventCallBack->EmitSigSelModelIndex(); //��ȡѡ��ĳ���

	if (selModel < 0)
	{
		return;
	}

	std::vector<CoordDouble3D> vecAbsPt, vecRelaPt;

	for (int i = 0; i < vecAbsCoord.size(); i++)
	{
		vecAbsPt.push_back(CoordDouble3D(vecAbsCoord[i].x(), vecAbsCoord[i].y(), vecAbsCoord[i].z()));
	}

	for (int i = 0; i < vecAbsCoord.size(); i++)
	{
		vecRelaPt.push_back(CoordDouble3D(vecRelaCoord[i].x(), vecRelaCoord[i].y(), vecRelaCoord[i].z()));
	}

	CSevenParameter sevenParamCalulator;
	sevenParamCalulator.LoadControlPoints(vecRelaPt, vecAbsPt);

	sevenParamCalulator.CalculateSevenParameter();

	osg::ref_ptr<osg::Node> oriNode = mRoot->getChild(0)->asGroup()->getChild(selModel);

	InterfaceOsgOrientFactory IOrientFactory;
	InterfaceOsgOrient* IOrient = IOrientFactory.create();
	IOrient->ModelOrientation(sevenParamCalulator, oriNode, absMatrix);

	mViewer->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KEY_Space);

	ClearGroupResult(mEditGroup);
	vecAbsCoord.clear();
	vecRelaCoord.clear();
	iSigEventCallBack->EmitSigShowOpsHint("��z������ƥ��������ESC�˳��¼�");
}


