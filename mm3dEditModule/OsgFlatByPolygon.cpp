#include "stdafx.h"
#include "OsgFlatByPolygon.h"
#include "InterfaceMFCExcute.h"
#include "InterfaceOsgEditor.h"
#include "InterfaceOsgFlat.h"
#include "InterfaceOsgFinder.h"
#include "InterfaceOsgAlgorithm.h"

bool COsgFlatByPolygon::flatSceneByScope(osg::ref_ptr<osg::Node> sceneNode, std::string InFilePath, std::vector<CScope> VecClipScope,
	InterfaceSigEventCallBack* iSigEventCallBack)
{
	InitFlatPara(InFilePath, VecClipScope, iSigEventCallBack);
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
	showHintFlating(iSigEventCallBack);

	//����ģ��
	startFlatModelByScope(vecTrans, headOutputFilePath);

	//����ͷ�ļ�
	flatOsgbHeader(vecClipScope, sceneNode, headOutputFileName);

	iSigEventCallBack->EmitSigEndProgressFun();

	fileSelector.reloadScene(iSigEventCallBack, headOutputFileName);
	showHintFinishFlat(iSigEventCallBack);
}

bool COsgFlatByPolygon::flatSingleObjectByScope(osg::ref_ptr<osg::Node> sceneNode, std::vector<CScope> vecClipScope)
{
	InterfaceOsgFlatFactory IOsgFlatFactory;
	InterfaceOsgFlat* IFlat = IOsgFlatFactory.create();
	IFlat->flatOsgHeader(sceneNode, vecClipScope);
	return true;
}

void COsgFlatByPolygon::showHintFlating(InterfaceSigEventCallBack* iSigEventCallBack)
{
	iSigEventCallBack->EmitSigShowOpsHint("����ѹƽ");
}

void COsgFlatByPolygon::showHintFinishFlat(InterfaceSigEventCallBack* iSigEventCallBack)
{
	iSigEventCallBack->EmitSigShowOpsHint("����ѹƽ");
}

void COsgFlatByPolygon::startFlatModelByScope(std::vector<osg::MatrixTransform*> vecTrans, std::string headOutputFilePath)
{
	int posStart = 0;
	int posInterval = 800;
	int tempInterval = posInterval / vecTrans.size();

	InterfaceOsgFlatFactory iOsgFlatFactory;
	InterfaceOsgFlat* iOsgFlat = iOsgFlatFactory.create();

	double flattenHeight = 0;
	obtainFlattenHeight(flattenHeight, vecClipScope);

	
	
	//ѹƽ
	for (int i = 0; i < vecTrans.size(); i++)
	{
		osg::ref_ptr<osg::MatrixTransform> mTrans = vecTrans[i];

		fileSelector.createClipOutputFolder(mTrans, headOutputFilePath);
		std::string outputFilePath = fileSelector.getClipOutputFilePath();
		
		CStProgressSetter stProgress(iSigEventCallBack, posStart + tempInterval * i, tempInterval);
		iOsgFlat->flatSceneByScope(mTrans, inFilePath, headOutputFilePath, vecClipScope, stProgress);

	}
}


void COsgFlatByPolygon::flatOsgbHeader(std::vector<CScope> vecClipScope, osg::ref_ptr<osg::Node> sceneNode, std::string headOutputFileName)
{
	//�Ի�ȡѹƽ�߶�
	double flattenHeight = 0;
	obtainFlattenHeight(flattenHeight, vecClipScope);

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

void COsgFlatByPolygon::obtainFlattenHeight(double &flattenHeight, std::vector<CScope> vecClipScope)
{
	std::vector<osg::Vec3d> vecWorldPt = vecClipScope[0].vecCoord;
	InterfaceOsgAlgorithmFactory iOsgAlgorithmFactory;
	InterfaceOsgAlgorithm* iOsgAlgorithm = iOsgAlgorithmFactory.create();
	double minHeight = 0; double maxHeight = 0;
	iOsgAlgorithm->FindMinMaxHeight(vecWorldPt, minHeight, maxHeight);
	flattenHeight = minHeight;
}

void COsgFlatByPolygon::InitFlatPara(std::string InFilePath, std::vector<CScope> VecClipScope, InterfaceSigEventCallBack* iSigEventCallBack)
{
	inFilePath = InFilePath;
	vecClipScope = VecClipScope;
	iSigEventCallBack = iSigEventCallBack;
}

