#include "StdAfx.h"
#include "ViewerSlot.h"
#include "InterfaceOsgDomGenerator.h"
#include "InterfaceOsgDsmGene.h"

void CMapperSlot::outForDxfAndShp()
{
	osg::ref_ptr<osg::Group> mapperGroup = root->getChild(3)->asGroup();

	vector<vector<osg::Vec3d> > vecVec;
	vector<osg::Vec3d> vecLine;
	vecLine.clear();
	vecVec.clear();
	InterfaceMFCExcuteFactory IExcuteFactory;
	InterfaceMFCExcute* IExcute = IExcuteFactory.create();
	std::vector<osg::MatrixTransform*> vecTrans;
	InterfaceOsgFinderFactory IFinderFactory;
	InterfaceOsgFinder* IFinder = IFinderFactory.create();

	osg::ref_ptr<osg::Vec3Array> extracted_verts;
	IFinder->FindTransNode(mapperGroup, vecTrans);

	if (vecTrans.size() == 0)
	{
		IExcute->PopUpMessage("�Ҳ�������");
		return ;
	}

	//�����ļ��в��������·��
	std::string extSelect = "DXF FILE (*.dxf)|*.dxf|SHP FILE (*.shp)|*.shp||";
	std::string outputFileName;
	bool isSuccess = IExcute->OpenDialogEx(outputFileName, extSelect, false,".dxf",".shp");
	//IExcute->PopUpMessage(outputFileName);
	if (!isSuccess)
	{
		//IExcute->PopUpMessage("�ļ�����·������");
		return ;
	}

	for (int i=0;i<vecTrans.size();++i)
	{
		osg::Geode* geode = vecTrans[i]->getChild(0)->asGeode();
		osg::Matrix matrix = vecTrans[i]->getMatrix();
		IFinder->ExtractVerts(geode,extracted_verts);
		for (int j = 0;j<extracted_verts->size();++j)
		{
			osg::Vec3d pt(extracted_verts->at(j).x(), extracted_verts->at(j).y(), extracted_verts->at(j).z());
			pt = pt*matrix;
			vecLine.push_back(pt);
		}
		vecVec.push_back(vecLine);
		vecLine.clear();
	}

	if (int(outputFileName.find(".shp")) != -1)//������shp
	{
		toShpAndDxf::convertToShp(vecVec,outputFileName,"hatching");
		IExcute->PopUpMessage("SHP�ļ������ɣ�");
		return ;
	}
	else
	{
		toShpAndDxf::convertToDxf(vecVec,outputFileName,"hatching");
		IExcute->PopUpMessage("DXF�ļ������ɣ�");
		return ;
	}
}

void CMapperSlot::ProduceDom(std::string strSceneFileName, double res)
{
	
}

void CMapperSlot::ProduceDsm(std::string strSceneFileName, double res)
{
	
}


bool CMapperSlot::ExtractContour(double high)
{
	return osgExtractTriangleBaseOutLineEvent->extractContour(high);
}


void CMapperSlot::setPtCloudParameter(double angle, double alpha, double color)
{
	osgExtractPtCloudEvent->ANGLE = angle;
	osgExtractPtCloudEdgeEvent->alpha = alpha;
	osgExtractPtCloudEvent->similarity = color;
}

void CMapperSlot::getPtCloudParameter(double& angle, double& alpha, double& color)
{
	angle = osgExtractPtCloudEvent->ANGLE;
	alpha = osgExtractPtCloudEdgeEvent->alpha;
	color = osgExtractPtCloudEvent->similarity;
}
