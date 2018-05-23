// osgMeasurePtEvent.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "qcomm.h"
#include "osgMeasurePtEvent.h"

bool COsgMeasurePtEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (isActivated)
	{
		if(IsLeftClick(ea) && GetKeyState(VK_CONTROL) < 0)											//���
		{
			CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pickResult.worldPt;

			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}

			//������Ϣ
			char strMsg[99];
			sprintf_s(strMsg, " XYZ = %lf  %lf %lf", worldPt.x(), worldPt.y(), worldPt.z());
			iSigEventCallBack->EmitSigNotifyMeasureMsg(strMsg);

			//iSigEventCallBack->EmitSigShowOpsHint("��Backspace������һ���㣬��Z������");
		}
		else if(IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_BackSpace || ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)
			{
				//��Ϣ�ÿ�
				char strMsg[99] = "";
				iSigEventCallBack->EmitSigNotifyMeasureMsg(strMsg);
				//iSigEventCallBack->EmitSigShowOpsHint("��סctrl���������������㣬��ESC�˳��¼�");
			}
		}
	}
	else
	{
		vecWorldCoord.clear();
	}

	return false;
}

void COsgMeasurePtEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false; 

	if (isActivated == true)
	{
		flag = true;
	}

	isActivated = isActivate(vecOpState, OPS_MEASURE_POINT);

	if (isActivated == false && flag == true)														//�ղ�����
	{
		
		//��Ϣ�ÿ�
		char strMsg[99] = "";
		iSigEventCallBack->EmitSigNotifyMeasureMsg(strMsg);
		iSigEventCallBack->EmitSigCloseMeasureDlg();
		iSigEventCallBack->EmitSigShowOpsHint("");
	}

	if (isActivated && flag == false)																//�ռ���
	{
		vecWorldCoord.clear();
		iSigEventCallBack->EmitSigShowOpsHint("��סctrl���������������㣬��ESC�˳��¼�");
	}
}