#pragma once
#include "osgClip.h"
#include "StProgressSetter.h"

class COsgClipperBySuspendScope : public COsgClipper
{
public:
	//�ӿ�
protected:
	virtual void clipHalfInPolygonTile(osg::ref_ptr<osg::Node> node, std::vector<CScope> VecScope, std::string InFilePath, std::string OutFilePath, 
		osg::Matrix Matrix, CStProgressSetter StProgressSetter, bool IsInside);
};

