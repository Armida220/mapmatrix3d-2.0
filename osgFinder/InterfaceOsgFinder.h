#pragma once
#include "OSG_Plus.h"
#include "publicDefined.h"

#ifdef FINDERLIBDLL  
#define FINDERAPI _declspec(dllexport)  
#else  
#define FINDERAPI  _declspec(dllimport)  
#endif  


class FINDERAPI InterfaceOsgFinder
{
public:
	virtual void FindClipNode(osg::ref_ptr<osg::Node> node, std::vector<osg::ClipNode*> &vecTrans) = 0;		   //����ClipNode

	virtual bool FindGeode(osg::ref_ptr<osg::Node> node) = 0;  												   //�����Ƿ����Geode

	virtual std::vector<osg::Geode*>  FindAndGetGeode(osg::ref_ptr<osg::Node> node) = 0;			     	   //���Ҳ����Geode

	virtual void FindLodBlockName(osg::ref_ptr<osg::Node> node, std::string& blockName) = 0;				   //����Ŀ¼��

	virtual void FindLodBottomLevelFile(osg::ref_ptr<osg::Node> node, std::vector<std::string> &VecBottomLevelPagedLodFileName) = 0; 	//���ҵײ��ļ���

	virtual void FindPagedLod(osg::ref_ptr<osg::Node> node, std::vector<osg::PagedLOD*> &vecPagedLod) = 0;	   //����pagedLod

	virtual void FindRepairTransNode(osg::ref_ptr<osg::Node> node, std::vector<osg::MatrixTransform*> &vecMatTrans) = 0;	//�����޸��ڵ��trans�ڵ�

	virtual void FindTransFolderName(osg::ref_ptr<osg::Node> node, std::string &folderFileName) = 0;		   //����TransĿ¼��

	virtual void FindTransMatrix(osg::ref_ptr<osg::Node> node, std::vector<osg::Matrix> &vecMatrix, std::vector<osg::MatrixTransform*> &vecTrans) = 0;	 //����trans�ڵ�

	virtual void FindTransNode(osg::ref_ptr<osg::Node> node, std::vector<osg::MatrixTransform*> &vecTrans) = 0; //����trans�ڵ�

	virtual void FindTriangleNum(osg::ref_ptr<osg::Node> node, int &triCnt) = 0; 							    //��������������

	virtual void ExtractVerts(osg::ref_ptr<osg::Node> node, osg::ref_ptr<osg::Vec3Array> &extracted_verts) = 0;  //����verts

	virtual void FindEmptyLod(osg::ref_ptr<osg::Node> node, std::vector<osg::PagedLOD*> &vecPagedLod) = 0;		//���ҿյ�LOD

	virtual osg::ref_ptr<osg::Node> FindObjectNodeFromNodePath(osg::NodePath np) = 0;										//���Ҷ���ڵ�

	virtual osg::ref_ptr<osg::Node> FindObjectPagedLodFromNodePath(osg::NodePath np) = 0;									//���Ҷ���ڵ�

	virtual osg::ref_ptr<osg::Node> FindObjectPropertyNodeFromNodePath(osg::NodePath np) = 0;								//�������Խڵ�

	virtual osg::ref_ptr<osg::Node> FindObjectPropertyNodeByName(osg::ref_ptr<osg::Node> node, std::string ObjectPropertyName, std::string ObjectPropertyValue) = 0;	//�����������Խڵ�

	virtual bool FindTriangleByPolygon(osg::ref_ptr<osg::Node> node, std::vector<CScope> vecScope, std::map<double, osg::Vec3d> &mapVerts, bool isInside) = 0;

	virtual bool FindNodeMinMaxHeight(osg::ref_ptr<osg::Node> node, osg::Matrix matrix, double &minHeight, double &maxHeight) = 0;

	virtual void replacePointFound(osg::ref_ptr<osgViewer::Viewer> viewer, osg::ref_ptr<osg::Node> scenceNode, osg::ref_ptr<osg::Node> vertexNode, osg::Matrix matrix, float x, float y, float pixSize, float disErr) = 0;
};



class FINDERAPI InterfaceOsgFinderFactory
{
public:		
	InterfaceOsgFinder* create();

};
