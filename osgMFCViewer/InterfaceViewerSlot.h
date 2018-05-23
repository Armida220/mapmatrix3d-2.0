#pragma once
#include <string>
#include "OSG_Plus.h"

#ifdef ORISLOTLIBDLL  
#define ORISLOTAPI _declspec(dllexport)  
#else  
#define ORISLOTAPI  _declspec(dllimport)  
#endif  

class ORISLOTAPI InterfaceOrientSlot
{
public:
	virtual BOOL AbsOrient(std::string inFilePath) = 0;															//���Զ���

	virtual void ReClickCtrlPt(int ptNum) = 0;																	//���Զ������´̵�

	virtual void LoadCtrlPt() = 0;																				//���ؿ��Ƶ�

	virtual void MatchSingleModel() = 0;																		//ƥ�䵥��ģ��

	virtual void InternetAbsOrient() = 0;																		//���������Զ���

	virtual void ManualHorizon() = 0;																			//�ֶ���ƽ

	virtual void ResetControlPtStatus(int ptNum, bool isCheckPt) = 0;											//�������ÿ��Ƶ�״̬

	virtual void MatchWholeModel() = 0;
};


class ORISLOTAPI InterfaceEditSlot
{
public:
	virtual void ClipByPolyon(std::string inFilePath) = 0;														//��Χ����

	virtual void HollowOut(std::string inFilePath) = 0;															//�ڿ�

	virtual void HollowOutSuspend(std::string inFilePath) = 0;													//�������ڿ�

	virtual void RepairHole() = 0;																				//�޲��ն�

	virtual void ClipByHeight() = 0;																			//�߶Ȳ���

	virtual void InvertClipHeight() = 0;																		//�߶Ȳ��з�ת

	virtual void AbsoluteHollowOutByPolygon(std::string inFilePath) = 0;										//����Χ�ڽ��в���

	virtual void FlatByPolygon(std::string inFilePath) = 0;														//����Χѹƽ
};

class ORISLOTAPI InterfaceMapperSlot
{
public:
	virtual void outForDxfAndShp() = 0;																			 //DXF���

	virtual void ProduceDom(std::string strSceneFileName, double res) = 0;										 //���DOM

	virtual void ProduceDsm(std::string strSceneFileName, double res) = 0;										 //���DSM

	virtual bool ExtractContour(double high) = 0;																//��ȡ�ȸ���			

	virtual void setPtCloudParameter(double angle, double alpha,double color) = 0;                               //���õ�����ȡ��ز���

	virtual void getPtCloudParameter(double& angle, double& alpha,double& color) = 0;							//��õ�����ȡ��ز���
};

class ORISLOTAPI InterfaceMonomerSlot
{
public:
	virtual void StartExtractTexture(double res, double deltaZ) = 0;											//��ȡ����

	virtual void ExtractObjectByPolygon(std::string inFilePathName) = 0;

	virtual void QuickClipByPolygon() = 0;	

	virtual void QuickClipBySolid() = 0;

	virtual void SetObjectProperty(std::string strObjectProperty) = 0;

	virtual void LookUpOjbectProperty(std::string objectPropertyName, std::string objectPropertyValue) = 0;

	virtual void OutputObjectModelWithoutTexture(std::string outModelWithoutFileName) = 0;

	virtual void SelectHousePt() = 0;
};