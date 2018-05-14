#pragma once
#include "osg/Node"
#include "osg/PagedLOD"
#include <osgDB/ReadFile>
#include <osgViewer/Renderer>
#include "osgUtil/RayIntersector"
#include "osgViewer/Viewer"
#include <algorithm>
#include <vector>
#include <string>
#include <libpq-fe.h>
#include "InterfaceOsgFinder.h"
using namespace std;

struct point3D
{
	point3D(double a = 0, double b = 0, double c = 0)
	{
		x = a; y = b; z = c;
	}
	point3D& operator=(point3D other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
	point3D operator-(point3D other)
	{
		point3D t;
		t.x = x - other.x;
		t.y = y - other.y;
		t.z = z - other.z;
		return t;
	}
	bool operator==(const point3D &p1)const {
		if (x == p1.x && y == p1.y && z == p1.z)
			return true;
		return false;
	}

	bool operator<(const point3D &p1) const {
		return (this->length() < p1.length());
	}

	inline double length() const
	{
		return sqrt(x*x + y*y + z*z);
	}

	double x;
	double y;
	double z;
};
struct CTri3D
{
	CTri3D(point3D v1,point3D v2,point3D v3)
	{
		p1 = v1;
		p2 = v2;
		p3 = v3;
	}
	CTri3D() {};
	CTri3D& operator=(CTri3D other)
	{
		p1 = other.p1;
		p2 = other.p2;
		p3 = other.p3;
		return *this;
	}
	bool operator<(const CTri3D &t1) const {
		return (p1 < t1.p1);
	}
	bool operator==(const CTri3D &t1)const {
		if (p1 == t1.p1 && p2 == t1.p2 && p3 == t1.p3)
			return true;
		return false;
	}

	point3D p1;
	point3D p2;
	point3D p3;
};

enum GEOMETRY_TYPE
{
	PG_POLYGON,
	PG_MULTIPOLYGON,
	PG_LINESTRING
};

enum EXTRACT_TYPE
{
	CONTOUR,
	HATCH
};

struct ID_TILE_PAIR
{
public:
	int id;
	std::string tilename;
};

class CPGController
{
public:

	CPGController()
	{
		char szapipath[MAX_PATH];
		memset(szapipath, 0, MAX_PATH);
		GetModuleFileNameA(NULL, szapipath, MAX_PATH);
		mEXEPath = string(szapipath);
		int pos = mEXEPath.rfind('\\');
		mEXEPath = mEXEPath.substr(0, pos);
	}
	//std::vector<std::string> m_vecTile;
	/***���ݿ����*******/

	//�������ݿ�
	PGconn* connectToDB(char *pghost = "127.0.0.1", char *pgport = "5432", char *dbname = "myDB3", char *user = "postgres", char *pwd = "");
	
	//�����ݿ�����������
	void DoSearchContourPostGis(PGconn* conn, CTri3D& tri, int& idSel, std::string m_tableName, std::vector<int>& ivecNeighbor, std::vector<point3D>& vecLineRes, double h, int clearTemp = 1);

	//�����ݿ�����������
	void DoSearchHatchPostGis(PGconn* conn, CTri3D& tri, int& idSel, std::string m_tableName, std::vector<int>& ivecNeighbor, std::vector<point3D>& vecLineRes, point3D p1,point3D p2, bool clearTemp = true);

	//�����ݿ�������һ��ƽ��
	void DoSearchPlanePostGis(PGconn* conn, CTri3D& tri, int& idSel, std::string m_tableName, std::vector<int>& ivecNeighbor, std::vector<point3D>& vecLineRes, point3D normal,float err,std::vector<CTri3D>& vectri, int clearTemp = 1);

	//�����ݿ���������״����
	void DoSearchSurfaceFeatures(PGconn* conn, CTri3D& tri, int& idSel, std::string m_tableName, std::vector<int>& ivecNeighbor, point3D normal, float err,  std::vector<CTri3D>& vecTriRes,  int time = 0);

	//�����Ƿ����
	//void checkPGTableTable(PGconn* conn, std::string table);

	//�����������
	int getContourStartTri(PGconn* conn,point3D worldPt, point3D nm, std::string bottomfile,CTri3D& tri,int& idSel,std::vector<int>& ivecNeibor);

	int getHatchStartTri(PGconn* conn, point3D ps,point3D pe, std::string bottomfile, CTri3D& tri, int& idSel, std::vector<int>& ivecNeibor,int doBatch = 0);

	//����geomtry��ʽ��polygon����
	void analysisGeometryDataString(std::string& sData, std::vector<point3D>& vecPt3D,std::vector<std::vector<point3D> >& vecVecPt3D, GEOMETRY_TYPE type);

	//�����ݿ�ɾ��ָ��������ͼ��
	int deleteGeomFromPG(PGconn* conn,double x,double y);

	//������������ȡ����
	void getObject(PGconn* conn, double x, double y,float dist, std::string& s,std::vector<CTri3D>& vecTri,  std::string& sContour,  double& mZ);

	void getObjectTest1(PGconn* conn, double x, double y, std::string& s, std::vector<CTri3D>& vecTri);

	//geometry���ݱ������ݿ�
	void insertGeometry(PGconn* conn, std::vector<point3D>& vecPt3D, EXTRACT_TYPE type,int id = 0);

	void insertBuilding(PGconn* conn,const std::vector<CLine>& vecBuildingDLG);

	//���geometry�ཻ��table
	void getIntersecTable(PGconn* conn, std::string& sGeometry,std::vector<std::string>& vectile);

protected:
	
	//�ѵ�������������Ƭ���浽���ݿ�
	void insertObject(PGconn* conn, std::vector<CTri3D>& vecTri3D,int id, std::string& s);

public:
	
	/***�㷨���*******/
	//�����������������
	void findContourByNeighbor(PGconn* conn,  string m_tableName, std::vector<int>& vecInt, CTri3D &tri, std::vector<point3D>& vecPt, double h, std::vector<int>& vecRec, bool start = false);

	//����������������
	void findHatchByNeighbor(PGconn* conn, int& idSel, string m_tableName, std::vector<int>& vecInt, CTri3D &tri, std::vector<point3D>& vecPt,point3D pStart,point3D pEnd);
	
	//�����������ƽ��
	void findPlaneByNeighbor(PGconn* conn, std::vector<CTri3D>& vecTri, string m_tableName, std::vector<int>& vecInt, CTri3D &tri, std::vector<point3D>& vecPt, std::vector<int>& vecID, point3D& normal,float err);

	//�����������ƽ��
	void findSurfaceByNeighbor(PGconn* conn, std::vector<CTri3D>& vecTriEdge, std::vector<int>& vecEdgeId, string m_tableName, std::vector<int>& vecInt, CTri3D &tri, std::vector<CTri3D>& vecTriRes,  point3D& normal, float err);

	//���������н�  flag = true �򽫽ǶȻ�Ϊ���
	double getAngle(point3D& p1,point3D& p2, bool flag = false);

	//����������Ƿ����
	bool vec3dEqWithEPS(point3D& p1, point3D& p2);

	//����ռ�ֱ�ߵĽ���
	point3D getCross(point3D& line11, point3D& line12, double pa, double pb);

	inline bool getCross(point3D& line11, point3D& line12, double pa, double pb,double pc, point3D& pCross);

protected:
	//���ַ�����ָ���ַ��ָ���浽vector
	void split(std::string sNeib, char * s, std::vector<int>& vecInt);

	void split(std::string sNeib, char * s, std::vector<double>& vecInt);

	//���ַ���s�е�t�滻Ϊw
	void replace_all(std::string& s, std::string const & t, std::string const & w);

	//�Ѵ�·�����ļ����޸�Ϊ���ݿ��еı���
	string getTableName(string fileName);

	//ɸѡ��ײ����
	void getBottomTile(PGconn* conn, std::vector<string>&vecName, std::vector<string>& vecNeed);

public:
	//��������tile����������
	int getNeighborTile(PGconn* conn, CTri3D& tri, point3D pt, std::string curTileName, std::string& sRes, std::vector<int>& vecint);

	//��������tile�������棩
	int getNeighborTile(PGconn* conn, CTri3D& tri, point3D ps, point3D pe, point3D pt, std::string curTileName, std::string& sRes, std::vector<int>& vecint);
	
	//��������tile����ƽ�棩
	int getNeighborTile(PGconn* conn, CTri3D& tri, point3D normal, float err, std::string curTileName, std::string& sRes, std::vector<int>& vecint);

	//��������tile����ƽ�棩
	int getSurfaceNeighbor(PGconn* conn, CTri3D& tri, point3D& normal, float err, std::string curTileName, std::string& sRes, std::vector<int>& vecint);

	//����������߳̽���
	void computeOutlinebyPoint(std::vector<point3D>& vecpt, double H,  std::vector<point3D>& vec);
	
	//�����������߶ν���
	void computeHatchbyPoint(CTri3D& tri, point3D p1,point3D p2, std::vector<point3D>& vec);

protected:
	//������������H�߶ȵĽ���
	void computePoints(point3D Pt1, point3D Pt2, point3D Pt3, double H, std::vector<point3D>& vec);

	void computePoints(point3D& Pt1, point3D& Pt2, point3D& Pt3, point3D& pStart,point3D& pEnd, std::vector<point3D>& vec);

	//�����߶���H�߶ȵĽ���
	inline point3D getInsection(point3D& p1, point3D& p2, double H)
	{
		return point3D((H - p1.z)*(p2.x - p1.x) / (p2.z - p1.z) + p1.x, (H - p1.z)*(p2.y - p1.y) / (p2.z - p1.z) + p1.y, H);
	}

	std::string mEXEPath;
};