// osgExtractOutlineEvent.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "InterfaceBaseDrawer.h"
#include "osgExtractOutlineEvent.h"
#include "outline_1.h"
#include "InterfaceMFCExcute.h"
#include "toShpAndDxf.h"

void COsgExtractOutLineEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false; 

	if (isActivated == true)
	{
		flag = true;
	}

	isActivated = isActivate(vecOpState, OPS_EXTRACT_OUTLINE);

	if (isActivated == false && flag == true)
	{
		ClearGroupResult(mapperGroup);
		vecWorldCoord.clear();
		vecVec.clear();
		iSigEventCallBack->EmitSigShowOpsHint("");
	}

	if (isActivated && flag == false)																//�ռ���
	{
		iSigEventCallBack->EmitSigShowOpsHint("��Ctrl + ���ѡ�㣬�Զ���ȡ�����ߣ���ESC�˳��¼�");
	}
}


bool COsgExtractOutLineEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (isActivated)
	{
		if (IsLeftClick(ea) && GetKeyState(VK_CONTROL) < 0)
		{
			CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pickResult.worldPt;
			osg::Vec3d normal = pickResult.worldNm;
			osg::Matrix worldMatrix = pickResult.matrix;

			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}

			vecWorldCoord.push_back(worldPt);

			//��ȡ������
			std::vector<osg::Vec3d> vecLine;
			outline::ComputeOutline(worldPt, normal, mRoot, vecLine);
			vecVec.push_back(vecLine);
			vecVec1 = vecVec;
			//��������
			if (vecLine.size() > 0)
			{
				InterfaceBaseDrawerFactory IDrawerFactory;
				InterfaceBaseDrawer* IDrawer = IDrawerFactory.create();
				osg::Vec4d color(1.0, 0, 1, 1.0);
				double size = 3.5f;
				IDrawer->BaseDrawLineLoopOperate(vecLine, color, size, mapperGroup, worldMatrix);

				iSigEventCallBack->EmitSigShowOpsHint("��BackSpaceɾ����һ�������ߣ���Z����ȫ������ESC�˳��¼�");
			}
		}
		else if (IsMouseMove(ea) && GetKeyState(VK_CONTROL) < 0)
		{

		}
		else if(IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_BackSpace)					 //BackSpace
			{
				if (vecWorldCoord.size() > 0)
				{
					//�����ϸ���
					vecWorldCoord.pop_back();
				}
				int childNum = mapperGroup->getNumChildren();
				if(childNum>0)
				{
					mapperGroup->removeChild(childNum - 1);
					if (!vecVec.empty())
					{
						vecVec.pop_back();
					}

					iSigEventCallBack->EmitSigShowOpsHint("��Ctrl + ���ѡ�㣬�Զ���ȡ�����ߣ���ESC�˳��¼�");
				}
				
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)
			{
				vecWorldCoord.clear();
				vecVec.clear();
				ClearGroupResult(mapperGroup);

				iSigEventCallBack->EmitSigShowOpsHint("��Ctrl + ���ѡ�㣬�Զ���ȡ�����ߣ���ESC�˳��¼�");
			}
		}
	}
	else
	{
		vecWorldCoord.clear();
	}

	return false;
}

std::vector<std::vector<osg::Vec3d> >& COsgExtractOutLineEvent::getVec()
{
	return vecVec;
}

void COsgExtractOutLineEvent::clearVec()
{
	vecVec.clear();
}

void COsgExtractOutLineEvent::pushBack(std::vector<std::vector<osg::Vec3d> >& vec)
{
	//vecVec1.assign(vecVec.begin(),vecVec.end()) ;
	vecVec.insert(vecVec.end(),vec.begin(),vec.end());
}

bool COsgExtractOutLineEvent::exportOutline()
{
	if(!vecVec.empty())
	{
		//�����ļ��в��������·��
		std::string extSelect = "DXF�ļ� (*.dxf)|*.dxf|SHP�ļ� (*.shp)|*.shp||";
		std::string outputFileName;
		InterfaceMFCExcuteFactory IExcuteFactory;
		InterfaceMFCExcute* IExcute = IExcuteFactory.create();
		bool isSuccess = IExcute->OpenDialogEx(outputFileName, extSelect, false,".dxf",".shp");
		if (!isSuccess)
		{
			return TRUE;
		}

		if (int(outputFileName.find(".shp")) != -1)//������shp
		{
			toShpAndDxf::convertToShp(vecVec1,outputFileName,"outline");
			IExcute->PopUpMessage("SHP�ļ������ɣ�");
			return TRUE;
		}
		else
		{
			//toShpAndDxf::convertToDxf(vecVec,outputFileName,"outline");
			IExcute->PopUpMessage("DXF�ļ������ɣ�");
			return TRUE;
		}
	}
	else
	{
		InterfaceMFCExcuteFactory IExcuteFactory;
		InterfaceMFCExcute* IExcute = IExcuteFactory.create();
		IExcute->PopUpMessage("δ����������!");
		return false;
	}
}

