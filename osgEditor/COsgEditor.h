#pragma once
#include "OSG_Plus.h"
#include "InterfaceOsgEditor.h"

class OsgEditor : public InterfaceOsgEditor
{
public:
	virtual void RemoveEmtyLod(osg::ref_ptr<osg::Node> node);	//�Ƴ���lod

	virtual void MoveLodCenter(osg::ref_ptr<osg::Node> node, double XMove, double YMove, double ZMove);		//�ƶ�lod����

	virtual void CombineScene(osg::ref_ptr<osg::Node> node, std::string groupFileFolder);					//�ϲ�����

	virtual void SplitSceneLod(osg::ref_ptr<osg::Node> node, std::string inFileName);						//��������

	virtual void SetLodFileName(osg::ref_ptr<osg::Node> node, std::string fileName);						//����lod�ļ���

	virtual void ChangeTransMatrix(osg::ref_ptr<osg::Node> node, double XMove, double YMove, double ZMove);	//�ı�ڵ���Ԫ�ؾ���

	virtual void MultiplyTransMatrix(osg::ref_ptr<osg::Node> node,osg::Matrix PosMulMatrix);				//�ڵ������Ԫ�ؾ���

	virtual void ComputeVertex(osg::ref_ptr<osg::Node> node, double *Rr, double *FWK, double s);			//��������߲���

	virtual void SetImageDataVariance(osg::ref_ptr<osg::Node> node);										//����Ӱ��variance

	virtual std::vector<osg::ref_ptr<osg::Geometry>> SetObjectHighLight(osg::ref_ptr<osg::Node> node, osg::Vec4d highLightColor);				//��������

	virtual void CancelObjectHighLight(osg::ref_ptr<osg::Node> node);										//ȡ����������
	
	virtual void ReCalPagedLodCenter(osg::ref_ptr<osg::Node> node);											//���¼���pagedLod����

	virtual void setGeometryDepthTest(osg::ref_ptr<osg::Node> node);
};
