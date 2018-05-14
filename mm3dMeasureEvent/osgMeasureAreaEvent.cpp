// osgMeasureAreaEvent.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "osgMeasrueAreaEvent.h"


bool COsgMeasureAreaEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
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

			//���㳤��
			double area = CalculateArea(vecWorldCoord);

			//������Ϣ
			char strMsg[99];
			sprintf_s(strMsg, " ����� %lfƽ����", area);
			iSigEventCallBack->EmitSigNotifyMeasureMsg(strMsg);

			iSigEventCallBack->EmitSigShowOpsHint("��Backspace������һ���㣬˫�������������Z������");
			
		}
		else if (IsMouseMove(ea) && GetKeyState(VK_CONTROL) < 0)
		{
			if (vecWorldCoord.empty())
			{
				return false;
			}
			CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pickResult.worldPt;

			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}

			//�������
			std::vector<osg::Vec3d> vecTempCoord = vecWorldCoord;
			vecTempCoord.push_back(worldPt);
			double area = CalculateArea(vecTempCoord);

			//������Ϣ
			char strMsg[99];
			sprintf_s(strMsg, " ����� %lfƽ����", area);
			iSigEventCallBack->EmitSigNotifyMeasureMsg(strMsg);
		}
		else if (IsDoubleClick(ea))
		{
			CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pickResult.worldPt;

			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}
			vecWorldCoord.push_back(worldPt);
			//���㳤��
			double area = CalculateArea(vecWorldCoord);

			//������Ϣ
			char strMsg[99];
			sprintf_s(strMsg, " ����� %lfƽ����", area);
			iSigEventCallBack->EmitSigNotifyMeasureMsg(strMsg);
			iSigEventCallBack->EmitSigShowOpsHint("��סctrl�������������ѡ�㣬Ȼ���ƶ������������Z����������ESC�˳��¼�");
			vecWorldCoord.clear();
		}
		else if(IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_BackSpace)
			{
				vecWorldCoord.pop_back();
				//��Ϣ�ÿ�
				char strMsg[99] = "";
				iSigEventCallBack->EmitSigNotifyMeasureMsg(strMsg);
				iSigEventCallBack->EmitSigShowOpsHint("��סctrl�������������ѡ�㣬Ȼ���ƶ������������Z����������ESC�˳��¼�");
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)					 //z
			{
				vecWorldCoord.clear();

				//��Ϣ�ÿ�
				char strMsg[99] = "";
				iSigEventCallBack->EmitSigNotifyMeasureMsg(strMsg);
				iSigEventCallBack->EmitSigShowOpsHint("��סctrl�������������ѡ�㣬Ȼ���ƶ������������Z����������ESC�˳��¼�");
			}
		}
	}

	return false;
}

void COsgMeasureAreaEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false; 

	if (isActivated == true)
	{
		flag = true;
	}

	isActivated = isActivate(vecOpState, OPS_MEASURE_AREA);

	if (isActivated == false && flag == true)
	{
		//��Ϣ�ÿ�
		char strMsg[99] = "";
		iSigEventCallBack->EmitSigNotifyMeasureMsg(strMsg);
		iSigEventCallBack->EmitSigCloseMeasureDlg();
		iSigEventCallBack->EmitSigShowOpsHint("");
	}

	if (isActivated && flag == false)																//�ռ���
	{
		iSigEventCallBack->EmitSigShowOpsHint("��סctrl�������������ѡ�㣬Ȼ���ƶ������������Z����������ESC�˳��¼�");
	}
}