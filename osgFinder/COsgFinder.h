#pragma once
#include "OSG_Plus.h"
#include "InterfaceOsgFinder.h"

class FINDERAPI COsgFinder : public InterfaceOsgFinder
{
public:
	void FindClipNode(osg::ref_ptr<osg::Node> node, std::vector<osg::ClipNode*> &vecTrans);		  //����ClipNode

	bool FindGeode(osg::ref_ptr<osg::Node> node);												  //�����Ƿ����Geode

	std::vector<osg::Geode*>  FindAndGetGeode(osg::ref_ptr<osg::Node> node);					  //���Ҳ����Geode

	void FindLodBlockName(osg::ref_ptr<osg::Node> node, std::string& blockName);				  //����Ŀ¼��

	void FindLodBottomLevelFile(osg::ref_ptr<osg::Node> node, std::vector<std::string> &VecBottomLevelPagedLodFileName); 	//���ҵײ��ļ���

	void FindPagedLod(osg::ref_ptr<osg::Node> node, std::vector<osg::PagedLOD*> &vecPagedLod);	  //����pagedLod

	void FindRepairTransNode(osg::ref_ptr<osg::Node> node, std::vector<osg::MatrixTransform*> &vecMatTrans);	//�����޸��ڵ��trans�ڵ�

	void FindTransFolderName(osg::ref_ptr<osg::Node> node, std::string &folderFileName);			   //����TransĿ¼��

	void FindTransMatrix(osg::ref_ptr<osg::Node> node, std::vector<osg::Matrix> &vecMatrix, std::vector<osg::MatrixTransform*> &vecTrans);	 //����trans�ڵ�

	void FindTransNode(osg::ref_ptr<osg::Node> node, std::vector<osg::MatrixTransform*> &vecTrans); //����trans�ڵ�

	void FindTriangleNum(osg::ref_ptr<osg::Node> node, int &triCnt); 							   //��������������

	void ExtractVerts(osg::ref_ptr<osg::Node> node, osg::ref_ptr<osg::Vec3Array> &extracted_verts);  //����verts

	void FindEmptyLod(osg::ref_ptr<osg::Node> node, std::vector<osg::PagedLOD*> &vecPagedLod);		//���ҿյ�LOD

	void FindTextureCoord(osg::ref_ptr<osg::Array> nodeArray, osg::ref_ptr<osg::Vec2Array> mTexCoorArray);				//������������

	osg::ref_ptr<osg::Node> FindObjectNodeFromNodePath(osg::NodePath np);										//���Ҷ���ڵ�

	osg::ref_ptr<osg::Node> FindObjectPagedLodFromNodePath(osg::NodePath np);									//���Ҷ���ڵ�

	osg::ref_ptr<osg::Node> FindObjectPropertyNodeFromNodePath(osg::NodePath np);								//�������Խڵ�

	osg::ref_ptr<osg::Node> FindObjectPropertyNodeByName(osg::ref_ptr<osg::Node> node, std::string ObjectPropertyName, std::string ObjectPropertyValue);	//�����������Խڵ�

	bool FindTriangleByPolygon(osg::ref_ptr<osg::Node> node, std::vector<CScope> vecScope, std::map<double, osg::Vec3d> &mapVerts, bool isInside);

	bool FindNodeMinMaxHeight(osg::ref_ptr<osg::Node> node, osg::Matrix matrix, double &minHeight, double &maxHeight);

	void replacePointFound(osg::ref_ptr<osgViewer::Viewer> viewer,osg::ref_ptr<osg::Node> scenceNode,osg::ref_ptr<osg::Node> vertexNode,osg::Matrix matrix,float x,float y,float pixSize,float disErr);
};
