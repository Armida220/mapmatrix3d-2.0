#include "stdafx.h"
#include "OsgAccurateHollowOutByPolygon.h"
#include "InterfaceOsgClip.h"
#include "InterfaceMFCExcute.h"
#include "InterfaceUserEventCallBack.h"
#include "qcomm.h"

void COsgAccurateHollowOutByPolygon::startClipModelByScope(std::vector<osg::MatrixTransform*> vecTrans, std::string headOutputFilePath, std::string inFilePath,
	std::vector<CScope> vecClipScope, CStProgressSetter stProgressSetter, bool isInside)
{
	for (int i = 0; i < vecTrans.size(); i++)
	{
		osg::ref_ptr<osg::MatrixTransform> mTrans = vecTrans[i];

		fileSelector.createClipOutputFolder(mTrans, headOutputFilePath);
		std::string outputFilePath = fileSelector.getClipOutputFilePath();

		InterfaceOsgClipFactory iOsgClipFactory;
		InterfaceOsgClip* iOsgClip = iOsgClipFactory.create(BY_ACCURATE_POLYGON);
		bool isSuccess = iOsgClip->clipSceneByScope(mTrans, inFilePath, outputFilePath, vecClipScope, stProgressSetter, isInside);
	}
}

void COsgAccurateHollowOutByPolygon::showHintClipping(InterfaceSigEventCallBack* iSigEventCallBack)
{
	_logop("��ʼ���о�ȷ��Χ�ڿ�");
	iSigEventCallBack->EmitSigShowOpsHint("���ڽ��о�ȷ��Χ�ڿ�...");
}

void COsgAccurateHollowOutByPolygon::showHintFinishClipping(InterfaceSigEventCallBack* iSigEventCallBack)
{
	iSigEventCallBack->EmitSigShowOpsHint("��ȷ��Χ�ڿ����");
}