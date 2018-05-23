#pragma once
#include "OSG_Plus.h"
#include <string>

class COsgPageLodSetter : public osg::NodeVisitor
{
public:
	COsgPageLodSetter(std::string FileName);
	~COsgPageLodSetter(void);

	//�ӿ�
	void SetLodFileName(osg::ref_ptr<osg::Node> node, std::string fileName);		//����lod�ļ���

protected:
	virtual void apply(osg::PagedLOD& pagedLod);
private:
	std::string fileName;
};

