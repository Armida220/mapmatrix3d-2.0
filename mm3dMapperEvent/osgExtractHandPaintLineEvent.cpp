// osgExtractHandPaintLineEvent.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "InterfaceBaseDrawer.h"
#include "osgExtractHandPaintLineEvent.h"


void COsgExtractHandPaintLineEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false; 

	if (isActivated == true)
	{
		flag = true;
	}

	isActivated = isActivate(vecOpState, OPS_EXTRACT_HAND_PAINT_LINE);

	if (isActivated == false && flag == true)
	{
		vecWorldCoord.clear();
		iSigEventCallBack->EmitSigShowOpsHint("");

		ClearGroupResult(tempGroup);
	}

	if (isActivated && flag == false)																//�ռ���
	{
		isCatch = false;   //�رղ�׽
		iSigEventCallBack->EmitSigShowOpsHint("��Ctrl + ������ߣ�˫�����ڶ����ߣ���BackSpace���ˣ���ESC�˳��¼�     ��׽[X]���ر�");
	}
}

bool COsgExtractHandPaintLineEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (isActivated)
	{
		if (IsLeftClick(ea) && GetKeyState(VK_CONTROL) < 0)
		{
			CPickResult pResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pResult.worldPt;
			osg::Matrix worldMatrix = pResult.matrix;

			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}
			if (isCatch)
			{
				CatchPointOperate(worldPt,mapperGroup);

				if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
				{
					return false;
				}
			}
			//������
			osg::Vec4d color(1.0, 0, 0.0, 1.0);
			double size = 5.5f;
			LeftClickExtractHandPaintLineOperate(vecWorldCoord, worldPt, color, size, mapperGroup, worldMatrix);					   //���û�����
		}
		else if (IsMouseMove(ea) && GetKeyState(VK_CONTROL) < 0)
		{
			CPickResult pResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pResult.worldPt;
			osg::Matrix worldMatrix = pResult.matrix;

			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}

			//������
			osg::Vec4d color(1.0, 0, 0.0, 1.0);
			double size = 5.5f;
			MouseMoveExtractHandPaintLineOperate(vecWorldCoord, worldPt, color, size, tempGroup, worldMatrix);		//��������ƶ�����

		}
		else if (IsDoubleClick(ea) && GetKeyState(VK_CONTROL) < 0)
		{
			CPickResult pResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pResult.worldPt;

			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}

			DoubleClickDrawExtractHandPaintOperate(vecWorldCoord, tempGroup);
		}
		else if(IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_BackSpace)
			{
				int childNum = mapperGroup->getNumChildren();
				
				if (childNum > 0)
				{
					mapperGroup->removeChild(childNum - 1);
				}

				vecWorldCoord.pop_back();
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)					 //z
			{
				ClearGroupResult(mapperGroup);
				vecWorldCoord.clear();
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_X)					 //x
			{
				if (isCatch == true)
				{
					isCatch = false;
					iSigEventCallBack->EmitSigShowOpsHint("��Ctrl + ������ߣ�˫�����ڶ����ߣ���BackSpace���ˣ���ESC�˳��¼�     ��׽[X]���ر�");
				}
				else
				{
					isCatch = true;
					iSigEventCallBack->EmitSigShowOpsHint("��Ctrl + ������ߣ�˫�����ڶ����ߣ���BackSpace���ˣ���ESC�˳��¼�     ��׽[X]������");
				}
			}
		}
	}
	else
	{
		vecWorldCoord.clear();
	}

	return false;
}

void COsgExtractHandPaintLineEvent::LeftClickExtractHandPaintLineOperate(std::vector<osg::Vec3d> &vecWorldCoord, osg::Vec3d worldPt, osg::Vec4d color, double size, osg::ref_ptr<osg::Group> drawGroup, osg::Matrix worldMatrix)
{
	//������
	if(vecWorldCoord.size() == 0)
	{
		
	}
	else
	{
		//������
		int totalNum = vecWorldCoord.size();
		//�����˵���ֵ
		//std::vector<osg::Vec3d> vecPoints;
		//vecPoints.clear();
		//InsertPoints(vecWorldCoord[totalNum-1],worldPt,vecPoints);
		//IBaseDrawer->BaseDrawCurLineOperate(vecPoints, color, size - 2, drawGroup, worldMatrix);
		IBaseDrawer->BaseDrawLineOperate(vecWorldCoord[totalNum - 1], worldPt, color, size - 2, drawGroup, worldMatrix);
	}

	//����		
	vecWorldCoord.push_back(worldPt);
}

bool COsgExtractHandPaintLineEvent::MouseMoveExtractHandPaintLineOperate(std::vector<osg::Vec3d> &vecWorldCoord, osg::Vec3d worldPt, osg::Vec4d color, double size, osg::ref_ptr<osg::Group> drawGroup, osg::Matrix worldMatrix)
{
	if (vecWorldCoord.size() == 0)
	{
		return false;
	}

	int childNum = drawGroup->getNumChildren();

	if (childNum > 0)
	{
		drawGroup->removeChild(childNum - 1, 1U);
	}
	
	//����
	int totalNum = vecWorldCoord.size();

	if (totalNum > 0)
	{
		osg::Vec3d pt1 = vecWorldCoord[totalNum - 1];
		IBaseDrawer->BaseDrawLineOperate(pt1, worldPt, color, size - 2, drawGroup, worldMatrix);
	}
	
	return true;
}

void COsgExtractHandPaintLineEvent::DoubleClickDrawExtractHandPaintOperate(std::vector<osg::Vec3d> &vecWorldCoord, osg::Group* TempGroup)
{
	vecWorldCoord.clear();
	ClearGroupResult(TempGroup);
}

bool COsgExtractHandPaintLineEvent::CatchPointOperate(osg::Vec3d &worldPt,osg::Group* mapperGroup)
{
	if (!mapperGroup)
	{
		return false;
	}
	InterfaceOsgFinderFactory IFinderFactory;
	InterfaceOsgFinder* IFinder = IFinderFactory.create();
	std::vector<osg::MatrixTransform*> vecTrans;
	IFinder->FindTransNode(mapperGroup, vecTrans);

	osg::Vec3d pt(0,0,0);//����� 
	double dis = 9999,d1,d2;//��С����

	for (int i = 0; i < vecTrans.size(); i++)
	{
		osg::ref_ptr<osg::MatrixTransform> mTrans =  vecTrans[i];
		if (!mTrans)
		{
			return false;
		}
		osg::ref_ptr<osg::Vec3Array> extracted_verts = new osg::Vec3Array;
		IFinder->ExtractVerts(mTrans, extracted_verts);
		osg::Matrix matrix = mTrans->getMatrix();
		if (extracted_verts->size() < 2)
		{
			return false;
		}
		d1 = distancep2p(extracted_verts->front()*matrix,worldPt);
		d2 = distancep2p(extracted_verts->back()*matrix,worldPt);
		if (d1 < dis)
		{
			dis = d1;
			pt = extracted_verts->front();
			pt= pt*matrix;	
		}

		if (d2 < dis)
		{
			dis = d2;
			pt = extracted_verts->back();
			pt= pt*matrix;	
		}
		
	}
	
	worldPt = pt;
	return true;
}

void COsgExtractHandPaintLineEvent::InsertPoints(osg::Vec3d p_start,osg::Vec3d p_end,std::vector<osg::Vec3d> &vecPoints)
{
	vecPoints.push_back(p_start);
	double len = distancep2p(p_start,p_end);
	
	double step = 0.1/len;
	double dx = step * (p_end.x() - p_start.x());
	double dy = step * (p_end.y() - p_start.y());
	double dz = step * (p_end.z() - p_start.z());

	osg::Vec3d pt = p_start;

	while (distancep2p(pt,p_end)>0.1)
	{
		pt = p_start + osg::Vec3d(dx,dy,dz);

		vecPoints.push_back(pt);
		p_start = pt;
	}
	vecPoints.push_back(p_end);
}