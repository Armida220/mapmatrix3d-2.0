#pragma once
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "OSG_Plus.h"

using namespace std;

struct Line
{
	Line(float x, float y)
	{
		k = x;
		b = y;
	}
	float k;
	float b;
};

struct Coord 
{
	Coord(int a,int b,int c,int d)
	{
		x = a;
		y = b;
		width = c;
		height = d;
	}
	int x;
	int y;

	int width;
	int height;
};

class CImageTool
{
public:
	IplImage* combineImage(IplImage* image1, IplImage*image2);  //�ϲ���ֵͼ��

	int ReadImageToBuff(const char* inputFileName, double *&pImageBuf, int&width, int& height) throw();  //GDAL��ȡtiffͼ��

	bool getCoordInfo(const char* inputFileName, double& leftX,double& leftY,double& resX,double& resY);

	void calcIntersectPointOfLine(Line& l1, Line& l2, osg::Vec3d& pt);

	bool checkColor(osg::Vec3d& c1, osg::Vec3d& c2, double err);

	IplImage* EqualizeHistColorImage(IplImage *pImage);    //��ǿͼ��Աȶ�

	inline double getHeightInDSM(double* dsmImage,int x,int y,int widStep);   //��ȡָ������ĸ߳�

	void searchByHeight(IplImage* contourImage,double* dsmData,Coord& coord,double seedH,double heiErr,std::vector<osg::Vec2i>& vecPoints);//ͨ���߳�ɸѡ��

	void searchByColor(IplImage* contourImage, IplImage* image, double* dsmData, Coord& coord, osg::Vec3d color,  double heiErr, std::vector<osg::Vec2i>& vecPoints);//ͨ����ɫѡ��

	void pointsToContour3D(osg::Group* mRoot, std::vector<osg::Vec3d>& vecPt3D, int N, std::vector<osg::Vec3d>& vecResult);  //���ص㼯��3ά������

private:

	inline double distance2(osg::Vec3d& pt1, osg::Vec3d& pt2)
	{
		return sqrt((pt1.x() - pt2.x())*(pt1.x() - pt2.x()) + (pt1.y() - pt2.y())*(pt1.y() - pt2.y()) + (pt1.z() - pt2.z())*(pt1.z() - pt2.z()));
	}
};
