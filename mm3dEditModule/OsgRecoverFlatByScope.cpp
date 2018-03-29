#include "stdafx.h"
#include "OsgRecoverFlatByScope.h"
#include "InterfaceMFCExcute.h"
#include "InterfaceOsgFlat.h"
#include "InterfaceOsgEditor.h"

bool COsgRecoverFlatByScope::recoverFlatSceneByScope(osg::ref_ptr<osg::Node> sceneNode, std::string inFilePath, std::vector<CScope> vecClipScope, std::vector<CScope> vecPreClipScope,
	InterfaceSigEventCallBack* iSigEventCallBack)
{
	initRecoverFlatPara(inFilePath, vecClipScope, vecPreClipScope, iSigEventCallBack, preSceneMaxHeight, preFlattenHeight);
	//ѡ��·��
	bool isSuccess = fileSelector.selectDir();

	if (!isSuccess)
	{
		return false;
	}

	std::string headOutputFileName = fileSelector.getSelFileName();
	int pos = headOutputFileName.rfind('\\');
	std::string headOutputFilePath = headOutputFileName.substr(0, pos);

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
	showHintRecovering(iSigEventCallBack);

	//����ģ��
	startRecoverFlatModelByScope(vecTrans, headOutputFilePath);

	//����ͷ�ļ�
	recoverFlatOsgbHeader(vecClipScope, sceneNode, headOutputFileName);

	iSigEventCallBack->EmitSigEndProgressFun();

	fileSelector.reloadScene(iSigEventCallBack, headOutputFileName);
	showHintFinishRecover(iSigEventCallBack);
}

bool COsgRecoverFlatByScope::recoverFlatSingleObjectByScope(osg::ref_ptr<osg::Node> sceneNode, std::vector<CScope> vecClipScope, std::vector<CScope> preVecClipScope, double preSceneMaxHeight, 
	double preFlattenHeight)
{
	InterfaceOsgFlatFactory IOsgFlatFactory;
	InterfaceOsgFlat* IFlat = IOsgFlatFactory.create();
	IFlat->recoverFlatOsgHeader(sceneNode, vecClipScope, preVecClipScope, preSceneMaxHeight, preFlattenHeight);

	return true;
}

bool COsgRecoverFlatByScope::startRecoverFlatModelByScope(std::vector<osg::MatrixTransform*> vecTrans, std::string headOutputFilePath)
{
	int posStart = 0;
	int posInterval = 800;
	int tempInterval = posInterval / vecTrans.size();

	InterfaceOsgFlatFactory iOsgFlatFactory;
	InterfaceOsgFlat* iOsgFlat = iOsgFlatFactory.create();
	//����
	for (int i = 0; i < vecTrans.size(); i++)
	{
		osg::ref_ptr<osg::MatrixTransform> mTrans = vecTrans[i];

		fileSelector.createClipOutputFolder(mTrans, headOutputFilePath);
		std::string outputFilePath = fileSelector.getClipOutputFilePath();

		CStProgressSetter stProgress(iSigEventCallBack, posStart + tempInterval * i, tempInterval);

		//����һ���ķ������в���
		iOsgFlat->RecoverFlatSceneByArea(mTrans, inFilePath, outputFilePath, vecClipScope, vecPreClipScope, stProgress);
	}
}

void COsgRecoverFlatByScope::recoverFlatOsgbHeader(std::vector<CScope> vecClipScope, osg::ref_ptr<osg::Node> sceneNode, std::string headOutputFileName)
{
	//�Ի�ȡѹƽ�߶�

	//ͷ���ѹƽ
	osg::ref_ptr<osg::Node> copyNode = dynamic_cast<osg::Node*> (sceneNode->clone(osg::CopyOp::DEEP_COPY_ALL));
	InterfaceOsgFlatFactory IOsgFlatFactory;
	InterfaceOsgFlat* IFlat = IOsgFlatFactory.create();
	IFlat->flatOsgHeader(copyNode, vecClipScope);

	//ͷ������
	InterfaceOsgEditorFactory IEditorFactory;
	InterfaceOsgEditor* IEditor = IEditorFactory.create();
	IEditor->SetLodFileName(copyNode, "");

	osg::ref_ptr<osgDB::Options> spOptions = new osgDB::Options;
	spOptions->setPluginStringData("WriteImageHint", "IncludeFile");
	osgDB::writeNodeFile(*copyNode, headOutputFileName, spOptions.get());
}


void COsgRecoverFlatByScope::initRecoverFlatPara(std::string inFilePath, std::vector<CScope> vecClipScope, std::vector<CScope> vecPreClipScope, InterfaceSigEventCallBack* iSigEventCallBack, 
	double preSceneMaxHeight, double preFlattenHeight)
{
	this->inFilePath = inFilePath;
	this->vecClipScope = vecClipScope;
	this->iSigEventCallBack = iSigEventCallBack;
	this->vecPreClipScope = vecPreClipScope;
	this->iSigEventCallBack = iSigEventCallBack;
	this->preSceneMaxHeight = preSceneMaxHeight;
	this->preFlattenHeight = preFlattenHeight;
}


void COsgRecoverFlatByScope::showHintRecovering(InterfaceSigEventCallBack* iSigEventCallBack)
{
	iSigEventCallBack->EmitSigShowOpsHint("���ڻָ�ѹƽ");
}

void COsgRecoverFlatByScope::showHintFinishRecover(InterfaceSigEventCallBack* iSigEventCallBack)
{
	iSigEventCallBack->EmitSigShowOpsHint("�ָ�ѹƽ");
}
