#include "stdafx.h"
#include "OsgClipBySupendScope.h"
#include "InterfaceOsgClip.h"
#include "qcomm.h"


void COsgClipBySupendScope::startClipModelByScope(std::vector<osg::MatrixTransform*> vecTrans, std::string headOutputFilePath, std::string inFilePath,
	std::vector<CScope> vecClipScope, CStProgressSetter stProgressSetter, bool isInside)
{
	InterfaceOsgClipFactory iOsgClipFactory;
	InterfaceOsgClip* IClip = iOsgClipFactory.create(BY_SUSPEND_SCOPE);
	//����
	for (int i = 0; i < vecTrans.size(); i++)
	{
		osg::ref_ptr<osg::MatrixTransform> mTrans = vecTrans[i];

		std::vector<std::string> vecHalfInPolygonFileName, vecTotalInPolygonFileName;
		IClip->clipSceneByScope(mTrans, inFilePath, headOutputFilePath, vecClipScope, stProgressSetter, isInside);
	}
}


void COsgClipBySupendScope::showHintClipping(InterfaceSigEventCallBack* iSigEventCallBack)
{
	iSigEventCallBack->EmitSigShowOpsHint("���ڽ������������");
}

void COsgClipBySupendScope::showHintFinishClipping(InterfaceSigEventCallBack* iSigEventCallBack)
{
	iSigEventCallBack->EmitSigShowOpsHint("������������");
}