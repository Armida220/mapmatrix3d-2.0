#pragma once
#include <string>
#include <vector>

#include "coord.hpp"
#include "SevenParameter.h"
#include "OSG_Plus.h"
#include "InterfaceOsgOrient.h"

class CAbsoluteOrientationor : public InterfaceOsgOrient
{
public:
	CAbsoluteOrientationor(void);
	~CAbsoluteOrientationor(void);

	//�ӿ�
	void LoadControlPoint(std::string fileName);																								//���ؿ��Ƶ�

	//�ӿ�
	BOOL AbsOrient(osg::ref_ptr<osg::Node> oriNode, std::string outputFilePath, osg::Matrix &absMatrix);										//���Զ���

	//�ӿ�
	void ObtainModelRelativePoint(int ptNum, double xRelaPt, double yRelaPt, double zRelaPt, bool isCheckPt);									//��ȡģ������Ե�

	//�ӿ�
	void ModelOrientation(CSevenParameter &sevenParamCalulator, osg::ref_ptr<osg::Node> oriNode, osg::Matrix &absMatrix);						//ģ�Ͷ���

	//�ӿ�
	void ReverseModelOrientation(osg::ref_ptr<osg::Node> oriNode, osg::Matrix &osgMatrix);														//ģ�ͷ�����

	std::vector<CControlPoint> GetVecCtrlPt();																									//���ģ���ϵĿ��Ƶ�

	std::vector<CControlPoint> GetVecRelativePt();																								//���ģ���ϵ���Ե�

	void SetControlPtStatus(int ptNum, bool isCheckPt);																							//���ÿ��Ƶ�״̬

	void EraseRelativePtIndex(int index);	
																																				//�����Ե����
	void ClearVecRelativePt();

	void ClearVecAbsolutePt();																													//������Զ�����

private:
	std::vector<CControlPoint> vecCtrlPt;																										//���Ƶ�
	std::vector<CControlPoint> vecRelaPt;																										//��Ե�

	osg::Matrix osgMatrix;

private:
	void OutputPrecisionReport(std::string reportFileName, CSevenParameter &sevenParamCalulator, std::vector<CoordDouble3D> vecAbsoluteCoord);  //�������

};

