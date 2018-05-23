// osgFlat.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "osgFlat.h"
#include "MultiScopeHeadGeodeflatter.h"
#include "MultiScopeHeadGeodeNormalizeFlatter.h"
#include "MultiScopePagedLodNormalizeFlatter.h"
#include "MultiScopeHeadGeodeFlatRecoverer.h"
#include "MultiScopePagedLodFlatRecoverer.h"
#include "InterfaceOsgAlgorithm.h"

//�ӿ�
bool COsgFlatter::flatSceneByScope(osg::ref_ptr<osg::MatrixTransform> mTrans, std::string inFilePath, std::string outputFilePath, std::vector<CScope> vecScope,
	CStProgressSetter stProgress)
{
	osg::ref_ptr<osg::Group> mGroup = mTrans->getChild(0)->asGroup();

	if (!mGroup)
	{
		return false;
	}

	osg::Matrix worldMatrix = mTrans->getMatrix();

	CObtainSelTileFileName tileFileNameGetter(vecScope);
	tileFileNameGetter.obtainFlatFileName(mTrans);
	std::vector<std::string> vecFlatPolygonFileName = tileFileNameGetter.getFlatPolygonFileName();

	CLogShower lodShower;
	lodShower.ShowLogFinishSelectScope();

	//�ϲ���
	COsgPagedLodReader reader(inFilePath);
	osg::ref_ptr<osg::Group> combineTotalInPolygonGroup = reader.combinePagedLod(vecFlatPolygonFileName);						//�����е�tile�ϲ�																													

	lodShower.ShowLogStartOutputTotalInScopeOsgb();

	//�����ڷ�Χ�ڽ���ѹƽ
	FlatTotalInPolygonTile(combineTotalInPolygonGroup, worldMatrix);

	COsgPagedLodOutputer outputer(outputFilePath);
	outputer.replacePagedLodClipFilePath(mTrans, inFilePath, vecFlatPolygonFileName);

	lodShower.ShowLogFinishOutputTotalInScopeOsgb();
}


//�ӿ�
bool COsgFlatter::NormalizeflatSceneByScope(osg::ref_ptr<osg::MatrixTransform> mTrans, const std::string InFilePath, const std::string OutputFilePath, 
	const std::vector<CScope> VecScope, CStProgressSetter stProgress)
{
	InitOsgFlatter(InFilePath, OutputFilePath, VecScope, stProgress);

	CObtainSelTileFileName tileFileNameGetter(vecScope);
	tileFileNameGetter.obtainFlatFileName(mTrans);
	std::vector<std::string> vecFlatPolygonFileName = tileFileNameGetter.getFlatPolygonFileName();

	CLogShower lodShower;
	lodShower.ShowLogFinishSelectScope();

	//�ϲ���
	COsgPagedLodReader reader(InFilePath);
	osg::ref_ptr<osg::Group> combineTotalInPolygonGroup = reader.combinePagedLod(vecFlatPolygonFileName);						//�����е�tile�ϲ�																													

	lodShower.ShowLogStartOutputTotalInScopeOsgb();

	osg::Matrix worldMatrix = mTrans->getMatrix();

	//�����ڷ�Χ�ڽ���ѹƽ
	NormalizeFlatTotalInPolygonTile(combineTotalInPolygonGroup, worldMatrix);

	COsgPagedLodOutputer outputer(outputFilePath);
	outputer.replacePagedLodClipFilePath(mTrans, inFilePath, vecFlatPolygonFileName);

	lodShower.ShowLogFinishOutputTotalInScopeOsgb();
}

bool COsgFlatter::RecoverFlatSceneByArea(osg::ref_ptr<osg::MatrixTransform> mTrans, std::string InFilePath, std::string OutputFilePath, std::vector<CScope> VecScope,
	std::vector<CScope> VecPreFlatScope, CStProgressSetter stProgress)
{
	InitOsgFlatter(InFilePath, OutputFilePath, VecScope, stProgress);

	osg::ref_ptr<osg::Group> mGroup = mTrans->getChild(0)->asGroup();
	CObtainSelTileFileName tileFileNameGetter(VecScope);
	tileFileNameGetter.obtainFlatFileName(mTrans);
	std::vector<std::string> vecFlatPolygonFileName = tileFileNameGetter.getFlatPolygonFileName();

	CLogShower lodShower;
	lodShower.ShowLogFinishSelectScope();

	//�ϲ���
	COsgPagedLodReader reader(InFilePath);
	osg::ref_ptr<osg::Group> combineTotalInPolygonGroup = reader.combinePagedLod(vecFlatPolygonFileName);

	_logop("��ʼ���ѹƽ�ڷ�Χ�ڷ�Χ");

	osg::Matrix worldMatrix = mTrans->getMatrix();

	//�����ڷ�Χ�ڽ���ѹƽ
	RecoverPreFlatTotalInPolygonTile(mTrans, VecPreFlatScope, worldMatrix);

	//�滻·��
	COsgPagedLodOutputer outputer(outputFilePath);
	outputer.replacePagedLodClipFilePath(mTrans, inFilePath, vecFlatPolygonFileName);
	lodShower.ShowLogFinishOutputTotalInScopeOsgb();
}

void COsgFlatter::FlatTotalInPolygonTile(osg::ref_ptr<osg::Node> node, osg::Matrix Matrix)
{
	//�����ڷ�Χ�ڽ���ѹƽ
	double flattenHeight = 0;
	obtainFlattenHeight(node, vecScope[0].vecCoord, Matrix, flattenHeight);

	//�������
	sqliteSaveer.saveFlattenHeight(flattenHeight);

	CMultiScopePagedLodFlatter iveFlatter(vecScope, inFilePath, outputFilePath, Matrix, flattenHeight, stPrgress);
	node->accept(iveFlatter);
}

void COsgFlatter::NormalizeFlatTotalInPolygonTile(osg::ref_ptr<osg::Node> node, osg::Matrix matrix)
{
	double sceneMaxHeight = 0;
	ObtainSceneMaxHeight(node, vecScope[0].vecCoord, matrix, sceneMaxHeight);

	double flattenHeight = 0;
	obtainFlattenHeight(node, vecScope[0].vecCoord, matrix, flattenHeight);

	//�������
	sqliteSaveer.savePreFlattenHeight(flattenHeight, sceneMaxHeight);

	//�����ڷ�Χ�ڽ���ѹƽ
	CMultiScopePagedLodNormalizeFlatter iveFlatter(vecScope, inFilePath, outputFilePath, matrix, flattenHeight, sceneMaxHeight, stPrgress);
	node->accept(iveFlatter);
}

void COsgFlatter::RecoverPreFlatTotalInPolygonTile(osg::ref_ptr<osg::Node> node, std::vector<CScope> vecPreScope, osg::Matrix matrix)
{
	sqliteSaveer.readPreFlattenHeight();
	double flattenHeight = sqliteSaveer.getPreFlattenHeight();
	double sceneMaxHeight = sqliteSaveer.getPreSceneMaxHeight();

	CMultiScopePagedLodFlatRecoverer iveFlatter(vecScope, vecPreScope, inFilePath, outputFilePath, matrix, flattenHeight, sceneMaxHeight, stPrgress);
	node->accept(iveFlatter);
}

//�ӿ�

bool COsgFlatter::flatOsgHeader(osg::ref_ptr<osg::Node> sceneNode, std::vector<CScope> vecScope)
{
	InterfaceOsgFinderFactory IOsgFinderFactory;
	InterfaceOsgFinder* IOsgFinder = IOsgFinderFactory.create();

	std::vector<osg::MatrixTransform*> vecMatTrans;
	IOsgFinder->FindTransNode(sceneNode, vecMatTrans);


	if (vecMatTrans.size() > 0)
	{
		osg::Matrix matrix = vecMatTrans[0]->getMatrix();
		double flattenHeight = 0;
		obtainFlattenHeight(sceneNode, vecScope[0].vecCoord, matrix, flattenHeight);

		//database·����Ϊ���,��ͷ������
		CMultiScopeHeadGeodeflatter ive(vecScope, matrix, flattenHeight);
		sceneNode->accept(ive);
	}

	return true;
}


bool COsgFlatter::normalizeflatOsgHeader(osg::ref_ptr<osg::Node> sceneNode, std::vector<CScope> vecScope)
{
	InterfaceOsgFinderFactory IOsgFinderFactory;
	InterfaceOsgFinder* IOsgFinder = IOsgFinderFactory.create();

	std::vector<osg::MatrixTransform*> vecMatTrans;
	IOsgFinder->FindTransNode(sceneNode, vecMatTrans);

	if (vecMatTrans.size() > 0)
	{
		osg::Matrix matrix = vecMatTrans[0]->getMatrix();
		
		double flattenHeight = 0; double sceneMaxHeight = 0;
		ObtainSceneMaxHeight(sceneNode, vecScope[0].vecCoord, matrix, sceneMaxHeight);
		obtainFlattenHeight(sceneNode, vecScope[0].vecCoord, matrix, flattenHeight);

		//database·����Ϊ���,��ͷ������
		CMultiScopeHeadGeodeNormalizeFlatter ive(vecScope, matrix, sceneMaxHeight, flattenHeight);
		sceneNode->accept(ive);
	}

	return true;
}

bool COsgFlatter::recoverFlatOsgHeader(osg::ref_ptr<osg::Node> sceneNode, std::vector<CScope> vecScope, std::vector<CScope> preVecScope, double preSceneMaxHeight, double preFlattenHeight)
{
	InterfaceOsgFinderFactory IOsgFinderFactory;
	InterfaceOsgFinder* IOsgFinder = IOsgFinderFactory.create();

	std::vector<osg::MatrixTransform*> vecMatTrans;
	IOsgFinder->FindTransNode(sceneNode, vecMatTrans);

	if (vecMatTrans.size() > 0)
	{
		osg::Matrix matrix = vecMatTrans[0]->getMatrix();
		CMultiScopeHeadGeodeFlatRecoverer ive(vecScope, preVecScope, matrix, preSceneMaxHeight, preFlattenHeight);
		sceneNode->accept(ive);
	}

	return true;
}

void COsgFlatter::ObtainSceneMaxHeight(osg::ref_ptr<osg::Node> sceneNode, std::vector<osg::Vec3d> vecWorldPt, osg::Matrix matrix, double &sceneMaxHeight)
{
	//��ȡѹƽ�߶Ⱥͳ������߶�
	double sceneMinHeight = 0;
	InterfaceOsgFinderFactory IOsgFinderFactory;
	InterfaceOsgFinder* IOsgFinder = IOsgFinderFactory.create();
	IOsgFinder->FindNodeMinMaxHeight(sceneNode, matrix, sceneMinHeight, sceneMaxHeight);
}

void COsgFlatter::obtainFlattenHeight(osg::ref_ptr<osg::Node> sceneNode, std::vector<osg::Vec3d> vecWorldPt, osg::Matrix matrix, double &flattenHeight)
{
	double minHeight = 0; double maxHeight = 0;
	InterfaceOsgAlgorithmFactory iOsgAlgorithmFactory;
	InterfaceOsgAlgorithm* iOsgAlgorithm = iOsgAlgorithmFactory.create();
	iOsgAlgorithm->FindMinMaxHeight(vecWorldPt, minHeight, maxHeight);
	flattenHeight = minHeight;
}

void COsgFlatter::InitOsgFlatter(const std::string inFilePath, const std::string outputFilePath, const std::vector<CScope> vecScope, 
	CStProgressSetter stPrgress)
{
	this->inFilePath = inFilePath;
	this->outputFilePath = outputFilePath;
	this->vecScope = vecScope;
	this->stPrgress = stPrgress;
}
