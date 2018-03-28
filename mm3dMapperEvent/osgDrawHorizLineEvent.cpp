// osgDrawHorizLineEvent.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "osgDrawHorizLineEvent.h"
#include "InterfaceBaseDrawer.h"
#include "InterfaceOsgExtractWall.h"

#define LINECOLOR osg::Vec4d(1,0,0,1)        //����ɫ
#define PTCOLOR osg::Vec4d(0,0,1,1)          //����ɫ
void COsgDrawHorizLineEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false;

	if (isActivated == true)
	{
		flag = true;
	}
	isActivated = isActivate(vecOpState, OPS_DRAW_HORIZ_LINE);

	if (isActivated == false && flag == true)
	{
		ClearGroupResult(tempGroup);
		iSigEventCallBack->EmitSigShowOpsHint("");
	}

	if (isActivated && flag == false)																//�ռ���
	{
		islineStart = true;
		iSigEventCallBack->EmitSigShowOpsHint("����ˮƽ�ߣ���ѡ��ˮƽ�߻������");
	}

}

bool COsgDrawHorizLineEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (isActivated)
	{
		InterfaceOsgExtractWallFactory IWallFactory;
		InterfaceOsgExtractWall* IWall = IWallFactory.create();
		if (IsLeftClick(ea) && GetKeyState(VK_CONTROL) < 0)//�����¼�
		{
			CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pickResult.worldPt;
			worldMatrix = pickResult.matrix;
			osg::Vec3d normal = pickResult.worldNm;
			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}
			IWall->drawHorizLineOprate(islineStart, horiz_high, worldPt, vecLine, vecName, worldMatrix, vecCoord, tempGroup, mapperGroup, iSigEventCallBack);
		}
		else if (IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_BackSpace)//������һ��ˮƽ��
			{
				IWall->deleteHorizLine(vecName,mapperGroup,tempGroup,vecLine,vecCoord,islineStart,worldMatrix,iSigEventCallBack);
				return false;
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)//ɾ������ͼ�νڵ�
			{
				ClearGroupResult(mapperGroup);
				ClearGroupResult(tempGroup);
			}
		}
	}
	return false;
}

