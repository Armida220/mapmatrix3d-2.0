// osgQuickDeleteSingleTriangleByLineEvent.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "osgQuickDeleteSingleTriangleByLineEvent.h"
#include "InterfaceOsgFinder.h"
#include "Geometry.h"
#include "qcomm.h"

void COsgQuickDeleteSingleTriangleByLineEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false;

	if (isActivated == true)
	{
		flag = true;
	}

	isActivated = isActivate(vecOpState, OPS_QUICK_DELETE_SINGLE_TRIANGLE_BY_LINE);

	if (isActivated == false && flag == true)
	{
		vecWorldCoord.clear();
	}

	if (isActivated && flag == false)																//�ռ���
	{

	}
}


bool COsgQuickDeleteSingleTriangleByLineEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (isActivated)
	{
		if (IsLeftClick(ea) && GetKeyState(VK_CONTROL) < 0)
		{
			CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pickResult.worldPt;
			osg::Matrix worldMatrix = pickResult.matrix;
			osg::NodePath np = pickResult.nodePath;

			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}

			vecWorldCoord.push_back(worldPt);

			if (vecWorldCoord.size() == 1)
			{
				return false;
			}

			//����ɾ��
			osg::ref_ptr<osg::Node> sceneNode = mRoot->getChild(0)->asGroup()->getChild(0);
			StartQuickDeleteByLine(sceneNode, worldMatrix, vecWorldCoord[0], vecWorldCoord[1]);
			vecWorldCoord.clear();
		}
		else if (IsDoubleClick(ea) && GetKeyState(VK_CONTROL) >= 0)
		{

		}
		else if (IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_BackSpace)					 //BackSpace
			{

			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)
			{

			}
		}
	}

	return false;
}


void COsgQuickDeleteSingleTriangleByLineEvent::StartQuickDeleteByLine(osg::ref_ptr<osg::Node> node, osg::Matrix worldMatrix, osg::Vec3d lineSegPt1, osg::Vec3d lineSegPt2)
{
	InterfaceOsgFinderFactory IOsgFinderFactory;
	InterfaceOsgFinder* IOsgFinder = IOsgFinderFactory.create();
	std::vector<osg::Geode*> vecGeode = IOsgFinder->FindAndGetGeode(node);

	for (size_t i = 0; i < vecGeode.size(); ++i)
	{
		if (!vecGeode[i])
		{
			continue;
		}

		int num = vecGeode[i]->getNumDrawables();

		for (int j = num - 1; j >= 0; --j)
		{
			osg::Geometry* geom = dynamic_cast<osg::Geometry*>(vecGeode[i]->getDrawable(j));

			if (!geom)
				continue; //�õ��ɻ��ƽ��Ķ������� 

			osg::Vec3Array* verts = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());

			for (size_t k = 0; k < geom->getNumPrimitiveSets(); k++)
			{
				osg::PrimitiveSet* priSet = geom->getPrimitiveSet(k);
				osg::ref_ptr<osg::DrawElements> drawElementTriangle = priSet->getDrawElements();
				osg::ref_ptr<osg::DrawElementsUInt> newDrawElementsTriangle = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES);
				int cnt = drawElementTriangle->getNumIndices();
				int triCnt = cnt / 3;

				for (int w = 0; w < triCnt; w++)
				{
					int index1 = drawElementTriangle->index(w * 3);
					int index2 = drawElementTriangle->index(w * 3 + 1);
					int index3 = drawElementTriangle->index(w * 3 + 2);

					double x1 = verts->at(index1).x();
					double y1 = verts->at(index1).y();
					double z1 = verts->at(index1).z();
					osg::Vec3d pt1(x1, y1, z1);
					pt1 = pt1 * worldMatrix;

					double x2 = verts->at(index2).x();
					double y2 = verts->at(index2).y();
					double z2 = verts->at(index2).z();
					osg::Vec3d pt2(x2, y2, z2);
					pt2 = pt2 * worldMatrix;

					double x3 = verts->at(index3).x();
					double y3 = verts->at(index3).y();
					double z3 = verts->at(index3).z();
					osg::Vec3d pt3(x3, y3, z3);
					pt3 = pt3 * worldMatrix;

					if (LineInTriangle(lineSegPt1, lineSegPt2, pt1, pt2, pt3) == false)//�ҵ����������Ƭ
					{
						newDrawElementsTriangle->push_back(index1);
						newDrawElementsTriangle->push_back(index2);
						newDrawElementsTriangle->push_back(index3);
					}
				}

				geom->setPrimitiveSet(k, newDrawElementsTriangle);
			}
		}
	}
}

//�жϵ���������Ƭ��
bool COsgQuickDeleteSingleTriangleByLineEvent::LineInTriangle(osg::Vec3d pt1, osg::Vec3d pt2, osg::Vec3d& t1, osg::Vec3d& t2, osg::Vec3d& t3)
{
	bool isInterSect = false;

	if (CL::IsIntersect(pt1.x(), pt1.y(), pt2.x(), pt2.y(), t1.x(), t1.y(), t2.x(), t2.y()))
	{
		isInterSect = true;
	}
	else if (CL::IsIntersect(pt1.x(), pt1.y(), pt2.x(), pt2.y(), t2.x(), t2.y(), t3.x(), t3.y()))
	{
		isInterSect = true;
	}
	else if (CL::IsIntersect(pt1.x(), pt1.y(), pt2.x(), pt2.y(), t3.x(), t3.y(), t1.x(), t1.y()))
	{
		isInterSect = true;
	}

	if (isInterSect)
	{
		if (pt1.z() > pt2.z())
		{
			if ((t1.z() > pt2.z() && t1.z() < pt1.z()) || (t2.z() > pt2.z() && t2.z() < pt1.z()) || (t3.z() > pt2.z() && t3.z() < pt1.z()))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (pt1.z() < pt2.z())
		{
			if ((t1.z() > pt1.z() && t1.z() < pt2.z()) || (t2.z() > pt1.z() && t2.z() < pt2.z()) || (t3.z() > pt1.z() && t3.z() < pt2.z()))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
}

