#pragma once
#include "OSG_Plus.h"

#ifdef TRIANGLERELATIONLIBDLL  
#define TRIANGLERELATIONAPI _declspec(dllexport)  
#else  
#define TRIANGLERELATIONAPI  _declspec(dllimport)  
#endif  

class TRIANGLERELATIONAPI CTriangle
{
public:
	osg::Vec3d pt1;
	osg::Vec3d pt2;
	osg::Vec3d pt3;

	osg::Vec4 color;//��Ƭ��ɫ
	osg::Vec3d normal; //�����淨���� 
public:
	bool neighborWith(CTriangle& other);//�Ƿ�����
	bool operator == (const CTriangle& other);//���� ==  
	CTriangle & operator = (const CTriangle &triangle); //��ֵ�����������  
	
private:
	bool pointInTriangle(osg::Vec3d pt, const CTriangle& triangle);
};

class TRIANGLERELATIONAPI CTriangleRelation
{
public:
	CTriangleRelation()
	{
		neighbor.clear();
	}

	CTriangle self;                             //������Ƭ
	std::vector<CTriangle> neighbor;            //����������Ƭ
};

//�Զ��������ڷ��Ͳ����㷨ν��
class findTriangle
{
public:

	findTriangle(const CTriangle& triangle) { tri = triangle; }
	bool operator()(CTriangleRelation& dValue)
	{
		if (dValue.self == tri)
			return true;
		else
			return false;
	}
	CTriangle tri;
};

