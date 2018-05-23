#include "stdafx.h"
#include "OsgAccurateClipByPolygon.h"
#include "InterfaceMFCExcute.h"
#include "InterfaceOsgClip.h"
#include "qcomm.h"

void COsgAccurateClipByPolygon::startClipModelByScope(std::vector<osg::MatrixTransform*> vecTrans, std::string headOutputFilePath, std::string inFilePath, 
	std::vector<CScope> vecClipScope, CStProgressSetter stProgressSetter, bool isInside)
{
	InterfaceOsgClipFactory iOsgClipFactory;
	InterfaceOsgClip* IClip = iOsgClipFactory.create(BY_ACCURATE_POLYGON);
	//����
	for (int i = 0; i < vecTrans.size(); i++)
	{
		osg::ref_ptr<osg::MatrixTransform> mTrans = vecTrans[i];
		stProgressSetter.percentStart += stProgressSetter.percentInterval * i;

		std::vector<std::string> vecHalfInPolygonFileName, vecTotalInPolygonFileName;
		IClip->clipSceneByScope(mTrans, inFilePath, headOutputFilePath, vecClipScope, stProgressSetter, isInside);
	}
}

void COsgAccurateClipByPolygon::showHintClipping(InterfaceSigEventCallBack* iSigEventCallBack)
{
	_logop("��ʼ���о�ȷ��Χ����");
	iSigEventCallBack->EmitSigShowOpsHint("���ڽ��о�ȷ��Χ����...");
}

void COsgAccurateClipByPolygon::showHintFinishClipping(InterfaceSigEventCallBack* iSigEventCallBack)
{
	iSigEventCallBack->EmitSigShowOpsHint("��ȷ��Χ�������");
}