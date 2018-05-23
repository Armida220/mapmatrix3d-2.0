#include "stdafx.h"
#include "OsgClipByPolygon.h"
#include "InterfaceMFCExcute.h"
#include "InterfaceOsgClip.h"
#include "qcomm.h"
#include "InterfaceUserEventCallBack.h"

void COsgClipByPolygon::startClipModelByScope(std::vector<osg::MatrixTransform*> vecTrans, std::string headOutputFilePath, std::string inFilePath, 
	std::vector<CScope> vecClipScope, CStProgressSetter stProgressSetter, bool isInside)
{
	InterfaceOsgClipFactory iOsgClipFactory;
	InterfaceOsgClip* IClip = iOsgClipFactory.create(BY_POLYGON);
	//����
	for (int i = 0; i < vecTrans.size(); i++)
	{
		osg::ref_ptr<osg::MatrixTransform> mTrans = vecTrans[i];

		std::vector<std::string> vecHalfInPolygonFileName, vecTotalInPolygonFileName;
		IClip->clipSceneByScope(mTrans, inFilePath, headOutputFilePath, vecClipScope, stProgressSetter, isInside);
	}
}

void COsgClipByPolygon::showHintClipping(InterfaceSigEventCallBack* iSigEventCallBack)
{
	_logop("��ʼ���з�Χ����");
	iSigEventCallBack->EmitSigShowOpsHint("���ڽ��з�Χ����...");
}



void COsgClipByPolygon::showHintFinishClipping(InterfaceSigEventCallBack* iSigEventCallBack)
{
	iSigEventCallBack->EmitSigShowOpsHint("��Χ�������");
}