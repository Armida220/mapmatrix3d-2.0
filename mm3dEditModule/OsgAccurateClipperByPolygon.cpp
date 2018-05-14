#include "stdafx.h"
#include "OsgAccurateClipperByPolygon.h"
#include "MultiScopeAccuratePagedLodClipper.h"

void COsgAccurateClipperByPolygon::clipHalfInPolygonTile(osg::ref_ptr<osg::Node> node, std::vector<CScope> VecScope, std::string InFilePath, std::string OutFilePath, 
	osg::Matrix Matrix, CStProgressSetter StProgressSetter, bool IsInside)
{
	//���ڲ���ȫ�ڷ�Χ�ڽ��в���
	CMultiScopeAccuratePagedLodClipper iveClipper(VecScope, InFilePath, OutFilePath, Matrix, StProgressSetter, IsInside);
	node->accept(iveClipper);

}
