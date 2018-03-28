#pragma once
#include "OSG_Plus.h"

#ifdef EDITORLIBDLL  
#define EDITORAPI _declspec(dllexport)  
#else  
#define EDITORAPI  _declspec(dllimport)  
#endif  


class EDITORAPI InterfaceOsgEditor
{
public:
	virtual void RemoveEmtyLod(osg::ref_ptr<osg::Node> node) = 0;												//�Ƴ���lod

	virtual void MoveLodCenter(osg::ref_ptr<osg::Node> node, double XMove, double YMove, double ZMove) = 0;		//�ƶ�lod����

	virtual void CombineScene(osg::ref_ptr<osg::Node> node, std::string groupFileFolder) = 0;					//�ϲ�����

	virtual void SplitSceneLod(osg::ref_ptr<osg::Node> node, std::string inFileName) = 0;						//��������

	virtual void SetLodFileName(osg::ref_ptr<osg::Node> node, std::string fileName) = 0;						//����lod�ļ���

	virtual void ChangeTransMatrix(osg::ref_ptr<osg::Node> node, double XMove, double YMove, double ZMove) = 0;	//�ı�ڵ���Ԫ�ؾ���

	virtual void MultiplyTransMatrix(osg::ref_ptr<osg::Node> node,osg::Matrix PosMulMatrix) = 0;				//�ڵ������Ԫ�ؾ���

	virtual void ComputeVertex(osg::ref_ptr<osg::Node> node, double *Rr, double *FWK, double s) = 0;			//��������߲���

	virtual void SetImageDataVariance(osg::ref_ptr<osg::Node> node) = 0;										//����Ӱ������variance

	virtual std::vector<osg::ref_ptr<osg::Geometry>> SetObjectHighLight(osg::ref_ptr<osg::Node> node, osg::Vec4d highLightColor) = 0;				//��������

	virtual void CancelObjectHighLight(osg::ref_ptr<osg::Node> node) = 0;										//ȡ����������

	virtual void ReCalPagedLodCenter(osg::ref_ptr<osg::Node> node) = 0;											//���¼���pagedLod����

	virtual void setGeometryDepthTest(osg::ref_ptr<osg::Node> node) = 0;										//������ȼ��
};

class EDITORAPI InterfaceOsgEditorFactory
{
public:		
	InterfaceOsgEditor* create();

};