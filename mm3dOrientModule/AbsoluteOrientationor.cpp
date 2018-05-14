#include "StdAfx.h"
#include "AbsoluteOrientationor.h"
#include "projection_matrix_transform.hpp"
#include "InterfaceOsgEditor.h"
#include "InterfaceOsgAlgorithm.h"
#include "InterfaceMFCExcute.h"
#include "qcomm.h"


CAbsoluteOrientationor::CAbsoluteOrientationor(void)
{
}


CAbsoluteOrientationor::~CAbsoluteOrientationor(void)
{
}

void CAbsoluteOrientationor::SetControlPtStatus(int ptNum, bool isCheckPt)
{
	for (int i = 0; i < vecRelaPt.size(); i++)
	{
		if (vecRelaPt[i].ptSerialNum == ptNum)
		{
			vecRelaPt[i].isCheckPoint = isCheckPt;
		}
	}
}

void CAbsoluteOrientationor::LoadControlPoint(std::string fileName)
{	
	FILE* fpCtrlPt = fopen(fileName.c_str(), "r");

	if (fpCtrlPt == NULL)
	{
		InterfaceMFCExcuteFactory IExcuteFactory;
		InterfaceMFCExcute* IExcute = IExcuteFactory.create();
		IExcute->PopUpMessage("ѡ��·������ȷ");
		return;
	}

	int cnt = 0;
	fscanf(fpCtrlPt, "%d\n", &cnt);

	for (int i = 0; i < cnt; i++)
	{
		int ptNum = 0;
		double ptX = 0;
		double ptY = 0;
		double ptZ = 0;
		char str[30];
		fscanf(fpCtrlPt, "%s %lf %lf %lf\n", &str, &ptX, &ptY, &ptZ);
		
		for (int i = 0;i<30;i++)
		{
			if (isalpha(str[i]))
			{
				InterfaceMFCExcuteFactory IExcuteFactory;
				InterfaceMFCExcute* IExcute = IExcuteFactory.create();
				IExcute->PopUpMessage("���Ƶ��Ž�֧�����֣����޸�");
				vecCtrlPt.clear();
				return;
			}
		}
		ptNum = atoi(str);
		vecCtrlPt.push_back(CControlPoint(ptNum, ptX, ptY, ptZ, FALSE));
	}

}

BOOL CAbsoluteOrientationor::AbsOrient(osg::ref_ptr<osg::Node> oriNode, std::string outputFilePath, osg::Matrix &absMatrix)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	std::vector<CoordDouble3D> vecAbsoluteCoord;
	std::vector<CoordDouble3D> vecRelaCoord;
	std::vector<CoordDouble3D> vecAllAbsCoord;

	if (vecCtrlPt.size() == 0)
	{
		return FALSE; 
		//AfxMessageBox(_T("û�м��ؿ��Ƶ�"));
	}

	for (int i = 0; i < vecRelaPt.size(); i++)
	{
		for (int j = 0; j < vecCtrlPt.size(); j++)
		{
			if (vecCtrlPt[j].ptSerialNum == vecRelaPt[i].ptSerialNum)
			{
				if (vecRelaPt[i].isCheckPoint == FALSE)
				{
					vecRelaCoord.push_back(CoordDouble3D(vecRelaPt[i].ptX, vecRelaPt[i].ptY, vecRelaPt[i].ptZ));
					vecAbsoluteCoord.push_back(CoordDouble3D(vecCtrlPt[j].ptX, vecCtrlPt[j].ptY, vecCtrlPt[j].ptZ));
				}
					
				vecAllAbsCoord.push_back(CoordDouble3D(vecCtrlPt[j].ptX, vecCtrlPt[j].ptY, vecCtrlPt[j].ptZ));
			}
		}

	}

	if (vecRelaCoord.size() < 3)
	{
		InterfaceMFCExcuteFactory IExcuteFactory;
		InterfaceMFCExcute* IExcute = IExcuteFactory.create();
		IExcute->PopUpMessage("���Ƶ�����С��3���޷����о��Զ������");
		return FALSE;
	}

	CSevenParameter sevenParamCalulator;
	sevenParamCalulator.LoadControlPoints(vecAbsoluteCoord, vecRelaCoord);
	sevenParamCalulator.CalculateSevenParameter();

	InterfaceMFCExcuteFactory IExcuteFactory;
	InterfaceMFCExcute* IExcute = IExcuteFactory.create();

	if (sevenParamCalulator.s_ < 0.5)
	{
		IExcute->PopUpMessage("ģ�ͳ߶�С��0.5�������ģ�Ϳ��ܹ�С���޷���ʾ��");
		return FALSE;
	}

	//���Զ���
	ModelOrientation(sevenParamCalulator, oriNode, absMatrix);

	std::string outFileReportFileName = outputFilePath + "report.txt";
	//������ȱ���
	OutputPrecisionReport(outFileReportFileName, sevenParamCalulator, vecAllAbsCoord);

	IExcute->PopUpMessage("���Զ�����ɣ����ȱ�������ڳ�������λ��");
	return TRUE;
}

void CAbsoluteOrientationor::ModelOrientation(CSevenParameter &sevenParamCalulator, osg::ref_ptr<osg::Node> oriNode, osg::Matrix &absMatrix)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	double matDB[16] = {0};
	int cnt = 0;
	//���ñ任����R��ת�����룬T����scale��scale��1/scale
	matDB[0] = sevenParamCalulator.R_[0]; matDB[1] = sevenParamCalulator.R_[3]; matDB[2] =	sevenParamCalulator.R_[6];
	matDB[4] = sevenParamCalulator.R_[1]; matDB[5] = sevenParamCalulator.R_[4]; matDB[6] =	sevenParamCalulator.R_[7];
	matDB[8] = sevenParamCalulator.R_[2]; matDB[9] = sevenParamCalulator.R_[5]; matDB[10] = sevenParamCalulator.R_[8];
	matDB[12] = sevenParamCalulator.t_[0] / sevenParamCalulator.s_; matDB[13] = sevenParamCalulator.t_[1] / sevenParamCalulator.s_; matDB[14] = sevenParamCalulator.t_[2] / sevenParamCalulator.s_; matDB[15] = 1 / sevenParamCalulator.s_;

	absMatrix.set(matDB);
	double* newDB = (double*) absMatrix.ptr();

	for (int i = 0; i < 16; i++)
	{
		newDB[i] *= sevenParamCalulator.s_;
	}

	InterfaceOsgEditorFactory  IEditorFactory;
	InterfaceOsgEditor* IEditor = IEditorFactory.create();
	IEditor->MultiplyTransMatrix(oriNode, absMatrix);
}

void CAbsoluteOrientationor::ReverseModelOrientation(osg::ref_ptr<osg::Node> oriNode, osg::Matrix &osgMatrix)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	osg::Matrix irOsgMatrix;
	irOsgMatrix = irOsgMatrix.inverse(osgMatrix);

	InterfaceOsgEditorFactory  IEditorFactory;
	InterfaceOsgEditor* IEditor = IEditorFactory.create();
	IEditor->MultiplyTransMatrix(oriNode, irOsgMatrix);

	osg::Matrix matrix;
	osgMatrix = matrix;
}

void CAbsoluteOrientationor::OutputPrecisionReport(std::string reportFileName, CSevenParameter& sevenParamCalulator, 
	std::vector<CoordDouble3D> vecAllAbsoluteCoord)
{
	FILE* fpReport = fopen(reportFileName.c_str(), "w");

	if (fpReport == NULL)
	{
		InterfaceMFCExcuteFactory IExcuteFactory;
		InterfaceMFCExcute* IExcute = IExcuteFactory.create();
		IExcute->PopUpMessage("����ѡ��·������");
		return;
	}

	InterfaceOsgAlgorithmFactory osgAlgorithm;
	InterfaceOsgAlgorithm* IOsgAlgorithm = osgAlgorithm.create();

	//��ȡ��ת��
	double fwk[3] ={0};

	IOsgAlgorithm->RtoAngle(sevenParamCalulator.R_, fwk[0], fwk[1], fwk[2]);
	fprintf(fpReport, "\t\t\t���ȱ���\n");
	fprintf(fpReport, "�����ǣ�%lf ����ǣ�%lf �����:%lf\n", fwk[0], fwk[1], fwk[2]);
	//��ȡλ��
	fprintf(fpReport, "λ��X: %lf λ��Y: %lf λ��Z: %lf\n", sevenParamCalulator.t_[0], sevenParamCalulator.t_[1], sevenParamCalulator.t_[2]);
	fprintf(fpReport, "�߶ȣ�%lf\n", sevenParamCalulator.s_);
	fprintf(fpReport, "���\t�Ƿ�Ϊ����\t�������X\t�������Y\t�������Z\t����X\t����Y\t����Z\t���X\t���Y\t���Z\n");

	for (int i = 0; i < vecRelaPt.size(); i++)
	{
		char strCheckPt[20]; 

		if (vecRelaPt[i].isCheckPoint == true)
		{
			sprintf_s(strCheckPt, "��");
		}
		else
		{
			sprintf_s(strCheckPt, "��");
		}

		CoordDouble3D absXYZ;
		sevenParamCalulator.CalculateRelativeToAbsolute(CoordDouble3D(vecRelaPt[i].ptX, vecRelaPt[i].ptY, vecRelaPt[i].ptZ), absXYZ);
		fprintf(fpReport, "%d\t%s\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", vecRelaPt[i].ptSerialNum, strCheckPt, absXYZ.x, absXYZ.y, absXYZ.z, 
			vecAllAbsoluteCoord[i].x, vecAllAbsoluteCoord[i].y, vecAllAbsoluteCoord[i].z, vecAllAbsoluteCoord[i].x - absXYZ.x, vecAllAbsoluteCoord[i].y - absXYZ.y, vecAllAbsoluteCoord[i].z - absXYZ.z);
	}

	fclose(fpReport);
}

void CAbsoluteOrientationor::ObtainModelRelativePoint(int ptNum, double xRelaPt, double yRelaPt, double zRelaPt, bool isCheckPt)
{
	vecRelaPt.push_back(CControlPoint(ptNum, xRelaPt, yRelaPt, zRelaPt, isCheckPt));
}

std::vector<CControlPoint> CAbsoluteOrientationor::GetVecCtrlPt()
{
	return vecCtrlPt;
}

std::vector<CControlPoint> CAbsoluteOrientationor::GetVecRelativePt()
{
	return vecRelaPt;
}

void CAbsoluteOrientationor::ClearVecRelativePt()
{
	vecRelaPt.clear();
}

void CAbsoluteOrientationor::ClearVecAbsolutePt()
{
	vecCtrlPt.clear();
}

void CAbsoluteOrientationor::EraseRelativePtIndex(int index)
{
	std::vector<CControlPoint>::iterator it = vecRelaPt.begin() + index;
	vecRelaPt.erase(it);
}