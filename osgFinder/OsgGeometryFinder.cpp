#include "StdAfx.h"
#include "OsgGeometryFinder.h"
#include "InterfaceMFCExcute.h"

void COsgGeodeFinder::apply(osg::Geode& geode)
{
	isFindGeometry = true;                                            /////�޸ĳɱ���
	traverse(geode);

	InterfaceMFCExcuteFactory IMfcExcuteFactory;
	InterfaceMFCExcute* IMFCExecute = IMfcExcuteFactory.create();
	IMFCExecute->MFCPeekMessage();			//ˢ�½�����
}