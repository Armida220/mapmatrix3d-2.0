#pragma once
#include "OSG_Plus.h"
#include <vector>

class COsgTransNodeFinder : public osg::NodeVisitor
{
public:
	std::vector<osg::MatrixTransform*> vecTrans;
public:
	COsgTransNodeFinder() : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) 
	{

	}

	//�ӿ�
	void FindTransNode(osg::ref_ptr<osg::Node> node, std::vector<osg::MatrixTransform*> &vecTrans);		//����trans�ڵ�

protected:
	virtual void apply(osg::MatrixTransform& node);

private:

};