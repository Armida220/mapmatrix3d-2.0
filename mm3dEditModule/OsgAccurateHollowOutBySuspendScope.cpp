#include "stdafx.h"
#include "OsgAccurateHollowOutBySuspendScope.h"
#include "InterfaceOsgClip.h"
#include "qcomm.h"

void COsgAccurateHollowOutBySuspendScope::startClipModelByScope(std::vector<osg::MatrixTransform*> vecTrans, std::string headOutputFilePath, std::string inFilePath,
	std::vector<CScope> vecClipScope, CStProgressSetter stProgressSetter, bool isInside)
{
	for (int i = 0; i < vecTrans.size(); i++)
	{
		osg::ref_ptr<osg::MatrixTransform> mTrans = vecTrans[i];

		fileSelector.createClipOutputFolder(mTrans, headOutputFilePath);
		std::string outputFilePath = fileSelector.getClipOutputFilePath();

		InterfaceOsgClipFactory iOsgClipFactory;
		InterfaceOsgClip* iOsgClip = iOsgClipFactory.create(BY_ACCURATE_SUSPEND_SCOPE);
		bool isSuccess = iOsgClip->clipSceneByScope(mTrans, inFilePath, outputFilePath, vecClipScope, stProgressSetter, isInside);
	}
}

void COsgAccurateHollowOutBySuspendScope::showHintClipping(InterfaceSigEventCallBack* iSigEventCallBack)
{
	_logop("��ʼ���о�ȷ���������");
}

void COsgAccurateHollowOutBySuspendScope::showHintFinishClipping(InterfaceSigEventCallBack* iSigEventCallBack)
{
	iSigEventCallBack->EmitSigShowOpsHint("��ȷ������������");
}