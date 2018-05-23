#include "stdafx.h"
#include "OsgClipperBySuspendScope.h"
#include "MultiScopePagedLodClipper.h"
#include "qcomm.h"

void COsgClipperBySuspendScope::clipHalfInPolygonTile(osg::ref_ptr<osg::Node> node, std::vector<CScope> VecScope, std::string InFilePath, std::string OutFilePath, 
	osg::Matrix Matrix, CStProgressSetter StProgressSetter, bool IsInside)
{
	//���ڲ���ȫ�ڷ�Χ�ڽ��в���
	CMultiScopePagedLodClipper iveClipper(VecScope, InFilePath, OutFilePath, Matrix, StProgressSetter, IsInside);
	node->accept(iveClipper);
}

