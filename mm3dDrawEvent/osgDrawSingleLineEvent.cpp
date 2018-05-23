// osgDrawSingleLineEvent.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "osgDrawSingleLineEvent.h"


bool COsgDrawSingleLineEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (isActivated)
	{
		if(IsLeftClick(ea) && GetKeyState(VK_CONTROL) < 0)				//������
		{
			CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pickResult.worldPt;
			osg::Matrix worldMatrix = pickResult.matrix;

			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}

			osg::Vec4d color(1.0, 0, 1, 1.0);
			double size = 3.5f;
			LeftClickDrawSingleLineOperate(vecWorldCoord, pickResult.worldPt, color, size, mEditSceneGroup, worldMatrix, true);
		}
		else if (IsMouseMove(ea) && GetKeyState(VK_CONTROL) < 0)		//����ƶ�
		{
			CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pickResult.worldPt;
			osg::Matrix worldMatrix = pickResult.matrix;

			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}

			//������
			osg::Vec4d color(1.0, 0, 1, 1.0);
			double size = 3.5f;
			MouseMoveDrawSingleLineOperate(vecWorldCoord, worldPt, color, size, mEditSceneGroup, worldMatrix);			//���û�����ģʽ
		}
		else if(IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_BackSpace)
			{
				BackSpaceReverseDrawSingleLineOperate(vecWorldCoord, mEditSceneGroup);
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)					 //z
			{
				ClearGroupResult(mEditSceneGroup);
				vecWorldCoord.clear();
			}
		}
	}
	else
	{
		vecWorldCoord.clear();
	}
	
	return false;
}

void COsgDrawSingleLineEvent::LeftClickDrawSingleLineOperate(std::vector<osg::Vec3d> &vecWorldCoord, osg::Vec3d worldPt, osg::Vec4d color, double size, osg::ref_ptr<osg::Group> drawGroup, osg::Matrix worldMatrix, bool isOnlyOneLine)
{
	//������
	bool isInitPt = true;
	int totalNum = vecWorldCoord.size();

	if (totalNum % 2 == 0)
	{
		isInitPt = true;
	}
	else
	{
		isInitPt = false;
	}

	if (isInitPt)
	{
		if (isOnlyOneLine)
		{
			ClearGroupResult(drawGroup);
		}

		IBaseDrawer->BaseDrawPtOperate(worldPt, color, size, drawGroup, worldMatrix);				//�տ�ʼ�໭һ��
		IBaseDrawer->BaseDrawPtOperate(worldPt, color, size, drawGroup, worldMatrix);
	}
	else 
	{
		int childNum = drawGroup->getNumChildren();
		drawGroup->removeChild(childNum - 1, 1U);
		//����
		int totalNum = vecWorldCoord.size();
		osg::Vec3d pt1 = vecWorldCoord[totalNum - 1];
		IBaseDrawer->BaseDrawLineOperate(pt1, worldPt, color, size - 2, drawGroup, worldMatrix);
		//����
		IBaseDrawer->BaseDrawPtOperate(worldPt, color, size, drawGroup, worldMatrix);
	}

	//����
	vecWorldCoord.push_back(worldPt);
}

bool COsgDrawSingleLineEvent::MouseMoveDrawSingleLineOperate(std::vector<osg::Vec3d> &vecWorldCoord, osg::Vec3d worldPt, osg::Vec4d color, double size, osg::ref_ptr<osg::Group> drawGroup, osg::Matrix worldMatrix)												
{
	//������
	bool isLineMove = true;
	int totalNum = vecWorldCoord.size();

	if (totalNum % 2 == 1)
	{
		isLineMove = true;
	}
	else
	{
		isLineMove = false;
	}

	if (isLineMove)
	{
		int childNum = drawGroup->getNumChildren();
		drawGroup->removeChild(childNum - 1, 1U);

		//����
		int totalNum = vecWorldCoord.size();
		osg::Vec3d pt1 = vecWorldCoord[totalNum - 1];
		IBaseDrawer->BaseDrawLineOperate(pt1, worldPt, color, size - 2, drawGroup, worldMatrix);

		return true;
	}
	else
	{
		return false;
	}
}

void COsgDrawSingleLineEvent::BackSpaceReverseDrawSingleLineOperate(std::vector<osg::Vec3d> &vecWorldCoord, osg::ref_ptr<osg::Group> drawGroup)
{
	int childNum = drawGroup->getNumChildren();

	if (childNum >= 3)
	{
		drawGroup->removeChild(childNum - 1, 1U);
		drawGroup->removeChild(childNum - 2, 1U);
		//drawGroup->removeChild(childNum - 3, 1U);
		int totalNum = vecWorldCoord.size();
		IBaseDrawer->DeleteVecChild(totalNum - 1, vecWorldCoord);
	}
	else if (childNum >= 2)
	{
		drawGroup->removeChild(childNum - 1, 1U);
		drawGroup->removeChild(childNum - 2, 1U);
		int totalNum = vecWorldCoord.size();
		IBaseDrawer->DeleteVecChild(totalNum - 1, vecWorldCoord);
	}
	else if (childNum == 1)
	{
		drawGroup->removeChild(childNum - 1, 1U);
		int totalNum = vecWorldCoord.size();
		IBaseDrawer->DeleteVecChild(totalNum - 1, vecWorldCoord);
	}
}

void COsgDrawSingleLineEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false; 

	if (isActivated == true)
	{
		flag = true;
	}

	isActivated = isActivate(vecOpState, OPS_DRAW_SINGLE_LINE);

	if (isActivated == false && flag == true)
	{
		ClearGroupResult(mEditSceneGroup);
		vecWorldCoord.clear();
	}
}
