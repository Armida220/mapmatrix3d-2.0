// osgClipByScope.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "osgClipByScope.h"
#include "publicDefined.h"
#include "qcomm.h"
#include "InterfaceMFCExcute.h"
#include "InterfaceOsgFinder.h"
#include "InterfaceOsgClip.h"
#include "InterfaceOsgEditor.h"

bool COsgClipByScope::hollowOutByScope(osg::ref_ptr<osg::Node> sceneNode, std::string inFilePath, std::vector<CScope> vecClipScope, bool isInside, InterfaceSigEventCallBack* iSigEventCallBack)
{
	//ѡ��·��
	bool isSuccess = fileSelector.selectDir();

	if (!isSuccess)
	{
		return false;
	}

	std::string headOutputFileName = fileSelector.getSelFileName();

	int pos = headOutputFileName.rfind('\\');
	std::string headOutputFilePath = headOutputFileName.substr(0, pos);

	if (fileSelector.isSameAsOutputFileName(inFilePath, headOutputFileName) == true)
	{
		return false;
	}

	//����trans�ڵ�
	isSuccess = transFinder.findTrans(sceneNode);

	if (!isSuccess)
	{
		InterfaceMFCExcuteFactory iMFCExcuteFactory;
		InterfaceMFCExcute* IExcute = iMFCExcuteFactory.create();
		IExcute->PopUpMessage("����δ��ƽ��������ƽ");
		return false;
	}

	std::vector<osg::MatrixTransform*> vecTrans = transFinder.getTrans();
	showHintClipping(iSigEventCallBack);

	int posStart = 0;
	int posInterval = 800;
	int tempInterval = posInterval / vecTrans.size();
	CStProgressSetter stProgressSetter(iSigEventCallBack, posStart, tempInterval);

	//����ģ��
	startClipModelByScope(vecTrans, headOutputFilePath, inFilePath, vecClipScope, stProgressSetter, isInside);

	//����ͷ�ļ�
	HollowOutOsgbHeader(vecClipScope, sceneNode, headOutputFileName, isInside);

	iSigEventCallBack->EmitSigEndProgressFun();

	//���¼���
	fileSelector.reloadScene(iSigEventCallBack, headOutputFileName);

	showHintFinishClipping(iSigEventCallBack);
}


void COsgClipByScope::startClipModelByScope(std::vector<osg::MatrixTransform*> vecTrans, std::string headOutputFilePath, std::string inFilePath, 
	std::vector<CScope> vecClipScope, CStProgressSetter stProgressSetter, bool isInside)
{
	for (int i = 0; i < vecTrans.size(); i++)
	{
		osg::ref_ptr<osg::MatrixTransform> mTrans = vecTrans[i];

		std::string blockName;
		InterfaceOsgFinderFactory iFinderFactory;
		InterfaceOsgFinder* IFinder = iFinderFactory.create();
		IFinder->FindLodBlockName(mTrans, blockName);

		//����Ŀ¼
		std::string outputFilePath = headOutputFilePath + blockName + ".\\Clip";

		InterfaceMFCExcuteFactory iMFCExtueFactory;
		InterfaceMFCExcute* IExcute = iMFCExtueFactory.create();
		IExcute->createFolder(outputFilePath);
	}
}


void COsgClipByScope::HollowOutOsgbHeader(std::vector<CScope> vecClipScope, osg::ref_ptr<osg::Node> sceneNode, std::string headOutputFileName, bool isInside)
{
	/*_logop("��ʼ�������tile");*/
	InterfaceOsgEditorFactory IEditorFactory;
	InterfaceOsgEditor* IEditor = IEditorFactory.create();

	osg::ref_ptr<osg::Node> copyNode = dynamic_cast<osg::Node*> (sceneNode->clone(osg::CopyOp::DEEP_COPY_ALL));
	InterfaceOsgClipFactory IClipFactory;
	InterfaceOsgClip* IClip = IClipFactory.create(BY_POLYGON);
	IClip->clipOsgHeader(copyNode, vecClipScope, isInside);
	IEditor->SetLodFileName(copyNode, "");

	osgDB::writeNodeFile(*copyNode, headOutputFileName);
}
