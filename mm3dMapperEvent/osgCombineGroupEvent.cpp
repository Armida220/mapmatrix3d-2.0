// osgCombineGroupEvent.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "osgCombineGroupEvent.h"
#include "InterfaceMFCExcute.h"
#include "InterfaceBaseDrawer.h"
#include "InterfaceOsgExtractWall.h"
#include "Geometry.h"

#define LINECOLOR osg::Vec4d(1,0,0,1)        //����ɫ
#define COMBINECOLOR osg::Vec4d(1,0,1,1)      //�����ɫ
void COsgCombineGroupEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false;

	if (isActivated == true)
	{
		flag = true;
	}
	isActivated = isActivate(vecOpState, OPS_COMBINE);

	if (isActivated == false && flag == true)
	{
		iSigEventCallBack->EmitSigShowOpsHint("");
	}

	if (isActivated && flag == false)																//�ռ���
	{
		vecCoord.clear();
		iSigEventCallBack->EmitSigShowOpsHint("��ϣ���ctrl + ���ѡ����Ϸ�Χ��˫���������(ע�⣺���ǰ�Ƚ����߶ν���)");
	}

}

bool COsgCombineGroupEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (isActivated)
	{
		InterfaceBaseDrawerFactory IDrawerFactory;
		InterfaceBaseDrawer* IDrawer = IDrawerFactory.create();
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
			vecCoord.push_back(worldPt);
		}
		else if (IsDoubleClick(ea) && GetKeyState(VK_CONTROL) < 0)
		{
			IWall->combineGroup(numChild,vecCoord,vecLFC,mapperGroup,COMBINECOLOR,worldMatrix,iSigEventCallBack);//����num��¼���Ƶ�ǽ����
			vecCoord.clear();
			return false;
		}
		else if (IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_BackSpace)
			{
				if (vecCoord.size()>0)
				{
					vecCoord.pop_back();
				}
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)//������Ͻ��
			{
				if (numChild > 0)
				{
					for (int i = 0; i < numChild; i++)
					{
						mapperGroup->removeChild(mapperGroup->getNumChildren() - 1);
					}

					numChild = 0;
					for (size_t i = 0; i < vecLFC.size(); ++i)
					{
						osg::ref_ptr<osg::Group> group = new osg::Group;
						IDrawer->BaseDrawLineOperate(vecLFC[i].p1, vecLFC[i].p2, LINECOLOR, 3.5, group, worldMatrix);
						group->setName(vecLFC[i].name.c_str());
						mapperGroup->addChild(group);
					}
					vecLFC.clear();
				}
			}
		}
	}
	return false;
}

