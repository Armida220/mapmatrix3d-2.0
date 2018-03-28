#pragma once
#include "SevenParameter.h"
#include "OSG_Plus.h"
#include "ControlPoint.h"

#ifdef OSGORIENTLIBDLL  
#define OSGORIENTAPI _declspec(dllexport)  
#else  
#define OSGORIENTAPI  _declspec(dllimport)  
#endif  


class OSGORIENTAPI InterfaceOsgOrient
{
public:
	//�ӿ�
	virtual void LoadControlPoint(std::string fileName) = 0;																								//���ؿ��Ƶ�

	//�ӿ�
	virtual BOOL AbsOrient(osg::ref_ptr<osg::Node> oriNode, std::string outputFilePath, osg::Matrix &absMatrix) = 0;										//���Զ���

	//�ӿ�
	virtual void ObtainModelRelativePoint(int ptNum, double xRelaPt, double yRelaPt, double zRelaPt, bool isCheckPt) = 0;									//��ȡģ������Ե�

	//�ӿ�
	virtual void ModelOrientation(CSevenParameter &sevenParamCalulator, osg::ref_ptr<osg::Node> oriNode, osg::Matrix &absMatrix) = 0;						//ģ�Ͷ���

	//�ӿ�
	virtual void ReverseModelOrientation(osg::ref_ptr<osg::Node> oriNode, osg::Matrix &osgMatrix) = 0;														//ģ�ͷ�����

	virtual std::vector<CControlPoint> GetVecCtrlPt() = 0;																									//���ģ���ϵĿ��Ƶ�

	virtual std::vector<CControlPoint> GetVecRelativePt() = 0;																								//���ģ���ϵ���Ե�

	virtual void SetControlPtStatus(int ptNum, bool isCheckPt) = 0;																							//���ÿ��Ƶ�״̬

	virtual void EraseRelativePtIndex(int index) = 0;																										//�����Ե����	

	virtual void ClearVecRelativePt() = 0;																													//�����Ե���

	virtual void ClearVecAbsolutePt() = 0;																													//������Ե���
};

class OSGORIENTAPI InterfaceOsgOrientFactory
{
public:
	InterfaceOsgOrient* create();
};