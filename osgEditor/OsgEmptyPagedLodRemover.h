#pragma once
#include "OSG_Plus.h"

class COsgEmptyPagedLodRemover : public osg::NodeVisitor
{
public:
	COsgEmptyPagedLodRemover();
	~COsgEmptyPagedLodRemover();
	//�ӿ�
	void RemoveEmtyLod(osg::ref_ptr<osg::Node> node);				//�Ƴ���lod

	void StartRemovePagedLod();										//��ʼ�Ƴ�

protected: 
	virtual void apply(osg::PagedLOD& pagedLod);

	std::vector<osg::PagedLOD*> vecPagedLod;
};

