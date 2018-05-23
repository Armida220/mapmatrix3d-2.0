#include "stdafx.h"
#include "FileSelector.h"
#include "InterfaceMFCExcute.h"
#include "InterfaceOsgFinder.h"

std::string CFileSelector::getSelFileName() const
{
	return selFileName;
}


std::string CFileSelector::getClipOutputFilePath() const
{
	return clipOutputFilePath;
}

bool CFileSelector::selectDir()
{
	std::string extSelect = "osgbģ�� (*.osgb)|*.osgb|osg (*.osg)|*.osg|All Files (*.*)|*.*||";

	InterfaceMFCExcuteFactory IExcuteFactory;
	InterfaceMFCExcute* IExcute = IExcuteFactory.create();

	bool isSuccess = IExcute->OpenDialog(selFileName, extSelect, false);

	if (!isSuccess)
	{
		return false;
	}

	return true;
}

void CFileSelector::createClipOutputFolder(osg::ref_ptr<osg::MatrixTransform> mTrans, std::string headOutputFilePath)
{
	std::string blockName;
	InterfaceOsgFinderFactory iFinderFactory;
	InterfaceOsgFinder* IFinder = iFinderFactory.create();
	IFinder->FindLodBlockName(mTrans, blockName);

	//����Ŀ¼
	clipOutputFilePath = headOutputFilePath + blockName + ".\\Clip";

	InterfaceMFCExcuteFactory iMFCExtueFactory;
	InterfaceMFCExcute* IExcute = iMFCExtueFactory.create();
	IExcute->createFolder(clipOutputFilePath);
}


bool CFileSelector::isSameAsOutputFileName(std::string inFilePath, std::string headOutputFileName)
{
	int pos = headOutputFileName.rfind("\\");
	std::string headOutputFilePath = headOutputFileName.substr(0, pos + 1);

	if (inFilePath == headOutputFilePath)
	{
		InterfaceMFCExcuteFactory iMfcExcuteFactory;
		InterfaceMFCExcute* IExcute = iMfcExcuteFactory.create();
		IExcute->PopUpMessage("���·�����ܺ�ģ������λ��һ��");
		return true;
	}

	return false;
}

void CFileSelector::reloadScene(InterfaceSigEventCallBack* iSigEventCallBack, std::string headOutputFileName)
{
	//���û�ѡ���Ƿ����¼���
	InterfaceMFCExcuteFactory iMFCExcuteFactory;
	InterfaceMFCExcute* IExcute = iMFCExcuteFactory.create();
	bool isReload = IExcute->MessageBoxIsReload();

	if (isReload)
	{
		iSigEventCallBack->EmitSigRemoveAllScene();
		char* reloadFileName = (char*)headOutputFileName.c_str();
		iSigEventCallBack->EmitSigAddScene(reloadFileName);
	}
}