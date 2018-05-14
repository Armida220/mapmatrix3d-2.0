// osgMultiFileLinkCreator.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "osgMultiFileLinkCreator.h"
#include "InterfaceMFCExcute.h"
#include "qcomm.h"
#include <process.h>

void COsgMultiFileLinkCreator::createLinkForMultiFile(InterfaceSigEventCallBack* iSigEventCallBack)
{
	this->iSigEventCallBack = iSigEventCallBack;
	StartcreateLinkForMultiFile();
}

void COsgMultiFileLinkCreator::createMultiFileLink(void* ptr)
{
	COsgMultiFileLinkCreator* Creator = (COsgMultiFileLinkCreator*)ptr;
	InterfaceSigEventCallBack* ISigCallBack = Creator->iSigEventCallBack;

	Creator->createLink(ISigCallBack);

}

void COsgMultiFileLinkCreator::StartcreateLinkForMultiFile()
{
	_beginthread(&createMultiFileLink, 0, this);
}


void COsgMultiFileLinkCreator::createLink(InterfaceSigEventCallBack* iSigEventCallBack)
{
	std::string filePath;
	InterfaceMFCExcuteFactory IMFCExcuteFactory;
	InterfaceMFCExcute* IMFCExcute = IMFCExcuteFactory.create();
	IMFCExcute->SelectDir(filePath);

	if (filePath.empty())
	{
		return;
	}

	iSigEventCallBack->EmitSigShowOpsHint("���ڲ�������...");

	std::string outputLodFile = filePath +"\\MultiFoderReader.osgb";
	int length = filePath.length() - 1;

	if(filePath.substr(length - 1, 1) != "\\") 
	{
		filePath += "\\";
		filePath += "*.*" ;
	}

	int percent = 0;
	//iSigEventCallBack->EmitSigSetProgressFun(percent);
	iSigEventCallBack->EmitSigStartProgressFun();
	InterfaceMFCExcuteFactory IMFCExecuteFactory;
	InterfaceMFCExcute* IMFCExecute = IMFCExecuteFactory.create();

	char* temp = "��ʼ��������";
	_logop(temp);
	std::vector<std::string> vecStrFileName;
	IMFCExecute->SearchFile(filePath, &vecStrFileName);											//�ļ�����

	if (vecStrFileName.empty())
	{
		IMFCExecute->PopUpMessage("�Ҳ���Tile�ļ�");
		//iSigEventCallBack->EmitSigEndProgressFun();
		iSigEventCallBack->EmitSigShowOpsHint("");
		return;
	}

	percent = 100;
	iSigEventCallBack->EmitSigSetProgressFun(percent);

	_logop("finish find link");

	//��Ŀ¼����
	std::string str = filePath.substr(0,filePath.length()-3);
	char strMsg[99];
	sprintf(strMsg,"����ΪĿ¼%s��������...",str.c_str());
	iSigEventCallBack->EmitSigShowOpsHint(strMsg);
	osg::ref_ptr<osg::Group> group = new osg::Group();

	for (int i = 0; i < vecStrFileName.size(); i++)
	{
		char strMsg[99];
		sprintf(strMsg,"%s",vecStrFileName[i].c_str());
		_logop(strMsg);

		if (i % 10 == 0 || i < 10)
		{
			percent = (int)((double) (i + 1) / (double) vecStrFileName.size() * 800) + 100;
			iSigEventCallBack->EmitSigSetProgressFun(percent);
		}

		osg::ref_ptr<osg::PagedLOD> lod = dynamic_cast<osg::PagedLOD*>(osgDB::readNodeFile(vecStrFileName[i]));

		if (!lod)
		{
			continue;
		}

		int pos = vecStrFileName[i].rfind('\\');
		std::string subSTR = vecStrFileName[i].substr(0, pos);
		int posL = subSTR.rfind('\\');
		std::string relativeFilePath = ".\\" + vecStrFileName[i].substr(posL + 1, vecStrFileName[i].length() - posL);;  //���·��
		lod->setFileName(1, relativeFilePath); 

		lod->setRange(0, 0, 1.0);																							//��һ�㲻�ɼ�
		lod->setRange(1, 1.0, 1e+030);

		lod->setDatabasePath("");
		group->addChild(lod);
	}

	temp = "��ʼ�������";
	_logop(temp);
	osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
	trans->addChild(group);
	osg::Matrix mat;
	trans->setMatrix(mat);
	osgDB::writeNodeFile(*trans, outputLodFile);

	//����������
	iSigEventCallBack->EmitSigEndProgressFun();
	iSigEventCallBack->EmitSigShowOpsHint("");
	IMFCExecute->PopUpMessage("�����ɹ������ָ��·��");
}