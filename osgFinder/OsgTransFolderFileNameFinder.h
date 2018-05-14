#pragma once
#include "OSG_Plus.h"
#include "InterfaceOsgFinder.h"

class COsgTransFolderNameFinder : public osg::NodeVisitor
{
public:
	COsgTransFolderNameFinder() : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
	{

	};

	// �ӿ�
	void FindTransFolderName(osg::ref_ptr<osg::Node> node, std::string &folderFileName);	//����TransĿ¼��

protected:
	virtual void apply(osg::PagedLOD& pagedLod);

public:
	std::string FolderFileName;
};