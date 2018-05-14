// osgMeasureMultiLineEvent.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "osgMeasureMultiLineEvent.h"


bool COsgMeasureMultiLineEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
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

			//�������
			double length = CalLength(vecWorldCoord);
			//������Ϣ
			char strMsg[99];
			sprintf_s(strMsg, " ���ȣ� %lf��", length);
			iSigEventCallBack->EmitSigNotifyMeasureMsg(strMsg);

			iSigEventCallBack->EmitSigShowOpsHint("��Backspace������һ���㣬˫�������������Z������");
		}
		else if (IsMouseMove(ea) && GetKeyState(VK_CONTROL) < 0)
		{
			CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pickResult.worldPt;

			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}

			//�������
			int totalNum = vecWorldCoord.size();

			if (totalNum == 0)
			{
				return false;
			}

			double length = CalLength(vecWorldCoord);
			length += CalculateDist(worldPt, vecWorldCoord[totalNum - 1]);

			//������Ϣ
			char strMsg[99];
			sprintf_s(strMsg, " ���ȣ� %lf��", length);
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

			//�������
			int totalNum = vecWorldCoord.size();

			if (totalNum == 0)
			{
				return false;
			}

			double length = CalLength(vecWorldCoord);
			length += CalculateDist(worldPt, vecWorldCoord[totalNum - 1]);

			//������Ϣ
			char strMsg[99];
			sprintf_s(strMsg, " ���ȣ� %lf��", length);
			iSigEventCallBack->EmitSigNotifyMeasureMsg(strMsg);
			vecWorldCoord.clear();
			iSigEventCallBack->EmitSigShowOpsHint("��סctrl�������������ѡ�㣬Ȼ���ƶ������ߣ���ESC�˳��¼�");
		}
		else if(IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_BackSpace)
			{
				vecWorldCoord.pop_back();
				//��Ϣ�ÿ�
				char strMsg[99] = "";
				iSigEventCallBack->EmitSigNotifyMeasureMsg(strMsg);

				iSigEventCallBack->EmitSigShowOpsHint("��סctrl�������������ѡ�㣬Ȼ���ƶ������ߣ���ESC�˳��¼�");
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)					 //z
			{
				vecWorldCoord.clear();

				//��Ϣ�ÿ�
				char strMsg[99] = "";
				iSigEventCallBack->EmitSigNotifyMeasureMsg(strMsg);

				iSigEventCallBack->EmitSigShowOpsHint("��סctrl�������������ѡ�㣬Ȼ���ƶ������ߣ���ESC�˳��¼�");
			}
		}
	}

	return false;
}

void COsgMeasureMultiLineEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false; 

	if (isActivated == true)
	{
		flag = true;
	}

	isActivated = isActivate(vecOpState, OPS_MEASURE_MULTIlINE);

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
		iSigEventCallBack->EmitSigShowOpsHint("��סctrl�������������ѡ�㣬Ȼ���ƶ������ߣ���ESC�˳��¼�");
	}
}