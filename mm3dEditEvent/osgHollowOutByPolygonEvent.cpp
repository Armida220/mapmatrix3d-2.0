// osgHollowOutByPolygon.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "InterfaceMFCExcute.h"
#include "InterfaceOsgClip.h"
#include "InterfaceOsgFinder.h"
#include "InterfaceOsgEditor.h"
#include "osgHollowOutByPolygonEvent.h"
#include "qcomm.h"
#include "ThreadSafeUpdateCallback.h"
#include "InterfaceCOsgClipByScope.h"
#include "InterfaceMFCExcute.h"

bool COsgHollowOutByPolygonEvent::StartHollowOutByPolygon(osg::ref_ptr<osg::Node> sceneNode, std::string inFilePath, std::vector<CScope> vecClipScope, bool isInside, InterfaceSigEventCallBack* iSigEventCallBack)
{
	//����Χ�ڿ�
	InterfaceCOsgClipByScopeFactory iOsgClipByScopeFactory;
	InterfaceCOsgClipByScope* iOsgClipByScope = iOsgClipByScopeFactory.create(ACCURATE_HOLLOW_OUT_BY_POLYGON_1);
	bool isSuccess = iOsgClipByScope->hollowOutByScope(sceneNode, inFilePath, vecClipScope, false, iSigEventCallBack, false);

	if (isSuccess)
	{
		vecWorldCoord.clear();
		vecScope.clear();
	}

	return isSuccess;
}

void COsgHollowOutByPolygonEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false;

	if (isActivated == true)
	{
		flag = true;
	}

	isActivated = isActivate(vecOpState, OPS_HOLLOW_OUT);

	if (isActivated == false && flag == true)
	{
		//��Ϣ�ÿ�
		iSigEventCallBack->EmitSigShowOpsHint("");
		vecWorldCoord.clear();
		vecScope.clear();
	}

	if (isActivated && flag == false)																//�ռ���
	{
		iSigEventCallBack->EmitSigShowOpsHint("��Ctrl + �������Χ����ɻ���Χ��˫���������Χ��Ȼ������ڿգ���ESC�˳��¼�");
	}
}

bool COsgHollowOutByPolygonEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
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

			vecWorldCoord.push_back(worldPt);
			iSigEventCallBack->EmitSigShowOpsHint("��BackSpace������һ���㣬��Zȫ����������ESC�˳��¼�");
		}
		else if (IsMouseMove(ea) && GetKeyState(VK_CONTROL) < 0)
		{

		}
		else if (IsDoubleClick(ea))
		{
			//��������
			CScope scope;
			scope.vecCoord = vecWorldCoord;
			vecScope.push_back(scope);

			//��ʼ�µĻ��պ���
			vecWorldCoord.clear();
		}
		else if (IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_BackSpace)					 //BackSpace
			{
				if (vecWorldCoord.size() > 0)
				{
					//�����ϸ���
					vecWorldCoord.pop_back();
					iSigEventCallBack->EmitSigShowOpsHint("��Ctrl + �������Χ����ɻ���Χ��˫���������Χ��Ȼ������ڿգ���ESC�˳��¼�");
				}
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)
			{
				vecWorldCoord.clear();
				vecScope.clear();
				iSigEventCallBack->EmitSigShowOpsHint("��Ctrl + �������Χ����ɻ���Χ��˫���������Χ��Ȼ������ڿգ���ESC�˳��¼�");
			}
		}
	}
	else
	{

	}

	return false;
}

bool COsgHollowOutByPolygonEvent::GetClipScope(std::vector<CScope> &vecClipScope, std::vector<CScope> vecScope, std::vector<osg::Vec3d> vecWorldCoord)
{
	if (vecScope.size() == 0)
	{
		if (vecWorldCoord.size() < 3)
		{
			InterfaceMFCExcuteFactory IExcuteFactory;
			InterfaceMFCExcute* IExcute = IExcuteFactory.create();
			IExcute->PopUpMessage("����ѡ����з�Χ");
			return false;
		}
		else
		{
			CScope scope;
			scope.vecCoord = vecWorldCoord;
			vecClipScope.push_back(scope);
		}
	}
	else
	{
		if (vecWorldCoord.size() >= 3)
		{
			vecClipScope = vecScope;
			CScope scope;
			scope.vecCoord = vecWorldCoord;
			vecClipScope.push_back(scope);
		}
		else
		{
			vecClipScope = vecScope;
		}
	}

	return true;
}