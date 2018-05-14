// osgMeasureSingleLineEvent.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "osgMeasureSingleLineEvent.h"

bool COsgMeasureLineEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
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

			vecWorldCoord.push_back(worldPt);

			if (vecWorldCoord.size() % 2 == 1)														//����ʱ��			
			{
				return false;
			}

			//�������
			int totalNum = vecWorldCoord.size();

			if (totalNum <= 1)
			{
				return false;
			}

			osg::Vec3d pt1 = vecWorldCoord[totalNum - 1];
			osg::Vec3d pt2 = vecWorldCoord[totalNum - 2];
			double dist = CalculateDist(pt1, pt2);
			double height = abs(pt1.z() - pt2.z());
			//������Ϣ
			char strMsg[99];
			sprintf_s(strMsg, " ���룺 %lf��  �߶�: %lf��", dist, height);
			iSigEventCallBack->EmitSigNotifyMeasureMsg(strMsg);

			iSigEventCallBack->EmitSigShowOpsHint("��Backspace������һ���㣬��Z������");
		}
		else if (IsMouseMove(ea))
		{
			CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pickResult.worldPt;

			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}

			if (vecWorldCoord.size() % 2 == 0)														//ż��ʱ��			
			{
				return false;
			}

			//�������
			int totalNum = vecWorldCoord.size();
			osg::Vec3d pt1 = vecWorldCoord[totalNum - 1];
			double dist = CalculateDist(pt1, worldPt);
			double height = abs(pt1.z() - worldPt.z());

			//������Ϣ
			char strMsg[99];
			sprintf_s(strMsg, " ���룺 %lf��  �߶�: %lf��", dist, height);
			iSigEventCallBack->EmitSigNotifyMeasureMsg(strMsg);
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
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)
			{
				vecWorldCoord.clear();

				//��Ϣ�ÿ�
				char strMsg[99] = "";
				iSigEventCallBack->EmitSigNotifyMeasureMsg(strMsg);

				iSigEventCallBack->EmitSigShowOpsHint("��סctrl�������������ѡ�㣬Ȼ���ƶ������ߣ���ESC�˳��¼�");
			}
		}
	}
	else 
	{
		vecWorldCoord.clear();
	}

	return false;
}

void COsgMeasureLineEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false; 

	if (isActivated == true)
	{
		flag = true;
	}

	isActivated = isActivate(vecOpState, OPS_MEASURE_LINE);

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