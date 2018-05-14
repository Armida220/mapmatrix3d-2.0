#pragma once
#include "InterfaceBaseDrawer.h"
#include <osgManipulator/Command>
#include <osgManipulator/CommandManager>  
#include <osgManipulator/Translate2DDragger>
class DRAWERAPI CSceneDrawer : public InterfaceBaseDrawer
{
public:
	void BaseDrawPtOperate(osg::Vec3d worldPt, osg::Vec4d color, double size, osg::ref_ptr<osg::Group> drawGroup, osg::Matrix worldMatrix);											 //����
																																													 
	void BaseDrawLineOperate(osg::Vec3d worldPt1, osg::Vec3d worldPt2, osg::Vec4d color, double size, osg::ref_ptr<osg::Group> drawGroup, osg::Matrix worldMatrix);					 //����
																																													 
	void BaseDrawSolidOperate(std::vector<osg::Vec3d> worldCoord, double height, osg::Vec4d color, double size, osg::ref_ptr<osg::Group> drawGroup, osg::Matrix worldMatrix);		 //����
																																													 
	void BaseDrawFlatPlaneOperate(osg::Vec3d newCenter, double radius, osg::Vec4d color, osg::ref_ptr<osg::Group> drawGroup, osg::Matrix worldMatrix);								 //��ƽ��
																																													 
	void BaseDrawLineLoopOperate(std::vector<osg::Vec3d> vecWorldCoord, osg::Vec4d color, double size, osg::ref_ptr<osg::Group> drawGroup, osg::Matrix worldMatrix);				 //����Ȧ
																																													 
	void BaseDrawCurLineOperate(std::vector<osg::Vec3d> vecWorldCoord, osg::Vec4d color, double size, osg::ref_ptr<osg::Group> drawGroup, osg::Matrix worldMatrix);					 //������

	void BaseDrawCircleLoopOperate(osg::Vec3d newCenter, double radius, osg::Vec4d color, double size, osg::ref_ptr<osg::Group> drawGroup, osg::Matrix worldMatrix);				 //��ԲȦ

	void DeleteVecChild(int childIndex, std::vector<osg::Vec3d> &vecGroup);																											 //ɾ��vector�ӽڵ�

	void ClearGroupChild(osg::ref_ptr<osg::Group> group);																															 //�����

	void AddDraggerToScene(osg::ref_ptr<osg::Group> mRoot,osg::ref_ptr<osg::Group> tempGroup,osg::ref_ptr<osg::Group> scopeGroup);

	void BaseDrawPolygon(std::vector<osg::Vec3d> vecWorldCoord, osg::Vec4d color, osg::ref_ptr<osg::Group> drawGroup, osg::Matrix worldMatrix);
protected:
	osg::ref_ptr<osg::Geode> DrawPoint(osg::Vec3d pt, osg::Vec4d color, double size);

	osg::ref_ptr<osg::Geode> DrawLine(osg::Vec3d pt1, osg::Vec3d pt2, osg::Vec4d color, double size);

	osg::ref_ptr<osg::Geode> DrawLineLoop(std::vector<osg::Vec3d> coord, osg::Vec4d color, double size);

	osg::ref_ptr<osg::Geode> DrawCurLine(std::vector<osg::Vec3d> coord, osg::Vec4d color, double size);

	osg::ref_ptr<osg::Geode> DrawPolygon(std::vector<osg::Vec3d> coord, osg::Vec4d color);

	osg::ref_ptr<osg::Geode> DrawPolygonNT(std::vector<osg::Vec3d> coord, osg::Vec4d color);

	osg::ref_ptr<osg::Group> DrawSolid(std::vector<osg::Vec3d> coord, double height, osg::Vec4d color, double size);

	osg::ref_ptr<osg::Geode> DrawFlatPlane(osg::Vec3d center, double radius, osg::Vec4d color);

	osg::ref_ptr<osg::Geode> DrawCircleLoop(osg::Vec3d center, double radius, osg::Vec4d color, double size);

	void AddNodeChildToGroup(osg::ref_ptr<osg::Node> nodeChild, osg::ref_ptr<osg::Group> parent, osg::Matrix matrix);

	osg::ref_ptr<osg::StateSet> MakePtState(int size);

	osg::ref_ptr<osg::StateSet> MakeLineState();
	
	osg::ref_ptr<osg::StateSet> MakeLineStateNT();
	osgManipulator::Dragger* createDragger(osg::Group* group);
};