#include "stdafx.h"
#include "OsgFlatByScope.h"
#include "StProgressSetter.h"

bool COsgFlatByScope::flatSceneByScope(osg::ref_ptr<osg::Node> sceneNode, std::string inFilePath, std::vector<CScope> vecClipScope, InterfaceSigEventCallBack* ISigEventCallBack)
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
	showHintFlating(ISigEventCallBack);

	int posStart = 0;
	int posInterval = 800;
	int tempInterval = posInterval / vecTrans.size();
	CStProgressSetter stProgressSetter(ISigEventCallBack, posStart, tempInterval);

	//����ģ��
	startFlatModelByScope(vecTrans, headOutputFilePath);

	//����ͷ�ļ�
	flatOsgbHeader(vecClipScope, sceneNode, headOutputFileName);

	ISigEventCallBack->EmitSigEndProgressFun();

	//���¼���
	fileSelector.reloadScene(ISigEventCallBack, headOutputFileName);

	showHintFinishFlat(ISigEventCallBack);
}
