#pragma once
#include "BaseUserEvent.h"
#include "operationState.h"
#include "InterfaceUserEventCallBack.h"
#include "PGControl.h"

class COsgExtractHatchingEvent : public CBaseUserEvent
{
public:
	COsgExtractHatchingEvent(osgViewer::Viewer *viewer, osg::Group *root, osg::ref_ptr<osg::Group> MapperGroup, osg::ref_ptr<osg::Group> TempGroup, InterfaceSigEventCallBack* iSigEventCallBack) : CBaseUserEvent(viewer)
	{
		mViewer = viewer;
		mRoot = root;
		isActivated = false;
		isBatch = false;
		this->iSigEventCallBack = iSigEventCallBack;
		mapperGroup = MapperGroup;
		tempGroup = TempGroup;
		mStep = 10;
		bLocal = false;
		bConnect = false;
	}

protected:

	void UpdateActivatedStatus(std::vector<OperatingState> vecOpState);

	//��ʼ��ȡ������
	bool startComputeHatching(float x, float y, osg::Vec3d p1, osg::Vec3d p2,  osg::NodePath& np1, bool repeat = false);

	//��ʼ������ȡ������
	bool startComputeBatchHatching(std::vector<osg::Vec3d>& vecIn);

	//������ѡ�еĵײ��ļ�
	bool getLodBottomLevelFile(float x, float y, osg::NodePath& np, osgViewer::Viewer *mViewer, std::string& m_tableName);

	//�ļ���ת��Ϊpostgis����
	std::string getTableName(string fileName);

	//�滻�ַ�����ָ���Ӵ�
	void replace_all(std::string& s, std::string const & t, std::string const & w);

	virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);

	//ͨ������·�����������������˵㼯
	void getHatchPathMultiline(std::vector<osg::Vec3d>& vecPtIn,double HatchLenth,double step,std::vector<osg::Vec3d>& vecPtOut);

	//ͨ�����������������ڵײ��ļ���
	bool findStartFile(osg::Vec3d& ps,osg::Vec3d& pe,std::string & tableName);

	//��ps���pe�ƶ�len�ľ���
	void stretchPointToPoint(osg::Vec3d& ps,osg::Vec3d& pe,double len);

	void RegisterJScripts();

	void UnRegisterJScripts();
protected:
	std::vector<osg::Vec3d> vecWorldCoord;
	osgViewer::Viewer *mViewer;
	osg::Group *mRoot;
	osg::Group *mapperGroup;
	osg::Group *tempGroup;
	InterfaceSigEventCallBack* iSigEventCallBack;

	//���Զ�����ת����
	osg::Matrix absMatrix;
	bool isActivated;
	bool isBatch;
	
	osg::NodePath np;
	osg::Matrix worldMatrix;
	
	PGconn* conn;

	std::string mEXEPath;
	osg::Vec3d PS, PE;//��¼��һ�������ߵ������˵�

public:
	double mStep;//������ȡ����

	//������������
	float FX1, FY1;
	osg::NodePath NP1;
	bool bLocal;
	bool bConnect;
};