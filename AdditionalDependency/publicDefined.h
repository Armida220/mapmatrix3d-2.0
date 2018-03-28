#ifndef _ENUM_STRUCT_DEFINED_

#define _ENUM_STRUCT_DEFINED_

#define		STR_HIGHLIGHT		"OutlineHighLight"

#include <vector>
#include "coord.hpp"
#include "OSG_Plus.h"
#include <map>

#ifdef OPSLIBDLL  
#define OPSAPI _declspec(dllexport)  
#else  
#define OPSAPI  _declspec(dllimport)  
#endif  

class CTransNodeandMatrix
{
public:
	osg::Matrix matrix;
	osg::ref_ptr<osg::MatrixTransform> mTrans;
};

class CPropertyListText
{
public:
	std::string strFirstWord;
	std::string strSecondWord;
};

class OPSAPI CPickResult
{
public:
	osg::Vec3d localPt;					//ԭʼ��
	osg::Vec3d worldPt;					//���������
	osg::Vec3d worldNm;
	int modelIndex;						//�ڼ���ģ��
	osg::NodePath nodePath;				//��ײ��Ľṹ
	osg::ref_ptr<osg::Node> parent;		//��Ͳ��ĸ��ӽڵ�
	osg::Matrix matrix;					//����
};

class OPSAPI CScope
{
public:
	CScope()
	{
		minH = 0;
		maxH = 0;
	}

public:
	std::vector<osg::Vec3d> vecCoord;
	osg::Matrix matrix;
	double minH;
	double maxH;
};

struct SCOPEINFO
{
	CScope scope;
	osg::Vec3d pt;//�Խǵ�
	int pointIndex;//��ţ�0����3��
	bool point_up;//ѡ�еĵ��Ƿ����Ϸ�
};

class PLane//ƽ��
{
public:
	double A;
	double B;
	double C;
	double D;
	PLane()
	{
		A = 0;
		B = 0;
		C = 0;
		D = 0;
	}
	PLane(double a,double b,double c,double d)
	{
		A = a;
		B = b;
		C = c;
		D = d;
	}
};
//��¼ǽ����Ϣ
struct WallInfo
{
	PLane* pl;
	std::vector<osg::Vec3d> coord;//���ƶ���
	float angle;//��б�Ƕ�
	double err;//������
	std::string normal;//������

	double minH;
	double maxH;
	double minx;
	double maxx;
	double miny;
	double maxy;
};

struct CPointWall
{
	osg::Vec3d pt;
	std::vector<int> vecWallIndex;
};

struct CLine
{
	CLine(osg::Vec3d P1, osg::Vec3d P2)
	{
		p1 = P1;
		p2 = P2;
	}
	CLine()
	{
	}
	bool operator == (const CLine& d)//���� ==  
	{
		return (this->p1 == d.p1 && this->p2 == d.p2) || (this->p1 == d.p2 && this->p2 == d.p1);
	}
	//ֱ�������˵�
	osg::Vec3d p1;
	osg::Vec3d p2;
};

struct LineInfo
{
	LineInfo(osg::Vec3d P1,osg::Vec3d P2)
	{
		p1 = P1;
		p2 = P2;
		pl1 = NULL;
		pl2 = NULL;
	}
	LineInfo()
	{
		pl1 = NULL;
		pl2 = NULL;
	}
	//ֱ�������˵�
	osg::Vec3d p1;
	osg::Vec3d p2;
	//ֱ�����ڵ�������
	PLane* pl1;
	PLane* pl2;
};

struct LineForCombine
{
	string name;
	osg::Vec3d p1;
	osg::Vec3d p2;
};

class CPickNodePath
{
public:
	osg::Vec3d pt;
	osg::NodePath nodePath;
};

inline double distance2(osg::Vec3d p1, osg::Vec3d p2)
{
	return sqrt((p1.x() - p2.x())*(p1.x() - p2.x()) + (p1.y() - p2.y())*(p1.y() - p2.y()) + (p1.z() - p2.z())*(p1.z() - p2.z()));
}

//���嵱ǰ�����Ĳ���״̬
enum OperatingState{
	OPS_None=0,							//��ʼ״̬,0
	OPS_MEASURE_POINT,					//���״̬ 1
	OPS_MEASURE_LINE,					//����״̬ 2
	OPS_MEASURE_AREA,					//����״̬ 3
	OPS_MEASURE_ANGLE,					//�����Ƕ� 4
	OPS_MEASURE_VOLUME,					//����״̬ 5
	OPS_MEASURE_HEIGHT,					//�����߶� 6
	OPS_MEASURE_MULTIlINE,				//�����ܳ� 26
	OPS_MEASURE_CURLINE,				//�������� 33
	OPS_MEASURE_MULTICURLINE,			//������������ 34
	OPS_SCENE_STITCH,					//����ƴ��		   49
	OPS_SELECT_CONTROL_POINT,			//ѡ����Ƶ�	   50
	OPS_ABSOLUTE_ORIENTATION,			//���Զ���		   51
	OPS_MANUAL_ORIENTATION,				//�ֶ�����
	OPS_INTERNET_ORIENTATION,			//���������Զ���
	OPS_MODEL_MATCHING,					//ģ��ƥ��		   52
	OPS_NONE2,
	OPS_ABS_NONE,						//���Զ����ÿ�
	OPS_EDIT_WHOLE_SCENE_Z,				//�޸�����������Ϣ 47
	OPS_EDIT_WHOLE_SCENE_XY,			//�޸�����������Ϣ 48
	OPS_CLIP_BY_POLYGON,				//����Χ�ü� 35
	OPS_CLIP_BY_HEIGHT,					//���߶Ȳü� 36
	OPS_SEL_TILE_REMOVE,				//�Ƴ�ѡ���tile   37
	OPS_EDIT_NONE,						//�༭����	
	OPS_HOLLOW_OUT,						//�����ڿ�		   56
	OPS_REPAIR_STOP,					//��ͣ�޸�		   57
	OPS_HOLLOW_OUT_STOP,				//��ͣ�ڿ�		   58
	OPS_HOLLOW_OUT_SUSPENDED,			//�ڿ�����		   59
	OPS_HOLLOW_OUT_SUSPENDED_STOP,		//�ڿ�������ͣ	   60
	OPS_FINE_CUTTING,					//��ϸ����		   61
	OPS_ENTITY_create_DRAG_MOVE_UP,		//���ϴ�������ģ�� 62
	OPS_ENTITY_DRAG_MOVE_UP,			//�������������ƶ� 63
	OPS_FLAT_PLANES_MOVE,				//ƽ�������ƶ�	   64
	OPS_FLAT_PLANES_START,				//ƽ�濪ʼ�ƶ�	   65
	OPS_FLAT_PLANE_STOP,				//��ͣƽ���ƶ�	   66 
	OPS_REPAIR_HOLE,					//�޲��ն�		   67
	OPS_EXTRACT_HATCH,					//��ȡ������		
	OPS_EXTRACT_OUTLINE,				//��ȡ������
	OPS_DRAW_SINGLE_PT,					//������
	OPS_DRAW_MULTI_PT,					//�����
	OPS_DRAW_SINGLE_LINE,				//������
	OPS_DRAW_MULTI_SINGLE_LINE,			//����������
	OPS_DRAW_MULTI_LINE,				//������
	OPS_DRAW_CLOSED_LINE,				//���պ���
	OPS_DRAW_FLAT_PLANE,				//���պϻ�
	OPS_DRAW_SUSPEND_OBJ_SCOPE,			//�������ﷶΧ
	OPS_EXTRACT_ACCURA_OUTLINE,         //��ȷ��ȡ����
	OPS_EXTRACT_HAND_PAINT,             //�ֹ���ͼ
	OPS_DRAW_CLOSED_LINE_HAND,          //�ֹ���ͼ���պ���
	OPS_EXTRACT_HAND_PAINT_RING,        //��ȡ�ֹ����Ƶıպ���
	OPS_EXTRACT_HAND_PAINT_LINE,        //��ȡ�ֹ����Ƶ��߶�
	OPS_DRAW_MULTI_LINE_HAND,           //�ֹ������߶�
	OPS_DRAW_MULTI_CLOSED_LINE,			//������պ���
	OPS_EXTRACT_TRIANGLE_OUTLINE,		//��ȷ��ȡ������
	OPS_DRAW_RECTANGLE,					//����
	OPS_SELECT_LINE_BY_RECTANGLE,		//��ѡ�߶�
	OPS_SELECT_LINE_BY_Area,			//����Χѡ�߶�
	OPS_DRAW_MULTI_CLOSED_LINE_DBCLICK,	//������պ���
	OPS_SELECT_LINE_BY_CLICK,           //��ѡ��
	OPS_EXTRACT_TRIANGLE_OUTLINE_CHANGE_HEIGHT, //���¸߶���ȡ������
	OPS_HOLLOW_OUT_SUSPENDED_UP,                //����ѡ��Χ
	OPS_DRAW_MULTI_CLOSED_LINE_FOR_AREA,        //������������Ļ���պ����¼�
	OPS_DRAW_MULTI_LINE_FOR_MULTI_LINE,         //���ڶ��߲����Ļ������¼�
	OPS_EXTRACT_WALLSPACE,                      //��ȡǽ��
	OPS_SELECT_WALLSPACE_AUTO,                  //�Զ�ѡ��ǽ��
	OPS_SELECT_WALLSPACE_HAND,                  //�ֶ�ѡ��ǽ��
	OPS_DRAW_HORIZ_LINE,                         //��ˮƽֱ��
	OPS_COMBINE,                                  //��Ͻڵ�
	OPS_LINE_INSECT,                               //ֱ����
	OPS_MANUAL_EXTRACT_TEXTURE,					 //���廯��ȡ����
	OPS_WHOLE_MATCH_SCENE,				//ȫ����ƥ��
	OPS_FITTING_WALLSPACE,                //���ǽ��
	OPS_WALLSPACE_INSECT,                 //ǽ����
	OPS_EXTRACT_OBJECT_BY_POLYGON,				//����������ȡ
	OPS_QUICK_CLIP_MODEL_BY_TRIANGLE,			//����ɾ��������
	OPS_QUICK_DELETE_SINGLE_TRIANGLE,			//����ɾ������������
	OPS_QUICK_DELETE_SINGLE_TRIANGLE_BY_LINE,	//ͨ�����߿���ɾ������������
	OPS_QUICK_DELETE_SINGLE_TRIANGLE_BY_SOLID,	//ͨ�������ɾ������������
	OPS_ABS_HOLLOW_OUT_BY_POLYGON,				//��Ե�ڲ��ڿ�
	OPS_FLAT_SCENE_BY_POLYGON,					//��Χ��ѹƽ
	OPS_DRAG_POINT,                              //��ק�ƶ���
	OPS_EXTRACT_TRIANGLE_OUTLINE_DRAW_AREA,
	OPS_EXTRACT_TRIANGLE_OUTLINE_IN_AREA,
	OPS_EXTRACT_TRIANGLE_OUTLINE_IN_AREA_CHANGE_HEIGHT,
	OPS_HIGHLIGHT_OBJECT_BY_CLICK,				//�������廯����
	OPS_LINK_PROPERTY_WITH_OBJECT,				//��������
	OPS_EXTRCT_PT_CLOUD_EDGE,                   //��ȡ���Ʊ�Ե
	OPS_SELECT_PTCLOUD_BY_Area,                 //��Χѡȡ����
	OPS_EXTRCT_PT_CLOUD,						//��ȡ����
	OPS_SIMPLIFY_OBJECT,						//ģ�ͼ�
	OPS_DRAW_CLOSED_LINE_WITH_POINT,				//���պ��ߺ͵����¼�
	OPS_EXTRACT_ROAD,                              //��ȡ��·
	OPS_DRAW_ROAD_PATH,                             //��·��
	OPS_DRAW_EDGE_BY_HAND,                           //�ֶ����Ʊ�Ե
	OPS_DRAW_EDGE_BY_HAND_1,
	OPS_EXTRACT_ROAD_BY_DOM,
	OPS_BREAKOUT_LINE,
	OPS_HORIZON_ACCURATE ,                        //��ȷ��ƽ
	OPS_EXTRACT_CONTOUR,                           //��ȡ�ȸ���
	OPS_EXTRACT_OUTLINE_BY_POSTGIS                 //���ݿ���ȡ����
};

enum QyManipulatorMode
{
	ManipulatorMode_Normal,		//�������
	ManipulatorMode_Path,		//·������
	ManipulatorMode_Panorama,	//ȫ������
	ManipulatorMode_MAP_REGISTRATION  //��ͼ��׼
};

typedef struct tagGridDem
{
	double x0, y0;    // ������DEM���½�����
	double x1, y1;    // ������DEM���Ͻ�����
	double dx, dy;    // ������DEM�������
	double kappa;     // ������DEM����ת��
	int cols, rows;   // ������DEM����������������
	float* z;         // ������DEM������ĸ߳�����
	float avgz;       // ������DEM��ƽ���߳�
	float minz, maxz; // ������DEM����С�����߳�
	float denum;
	float* nx;        // ������DEM�ķ�����X����
	float* ny;        // ������DEM�ķ�����Y����
	float* nz;        // ������DEM�ķ�����Z����
	float valid;
	// ��ʼ��������DEM���ݽṹ
	tagGridDem(){
		x0 = y0 = 0;
		x1 = y1 = 0;
		dx = dy = 0;
		kappa = 0;
		cols = rows = 0;
		z = NULL;
		avgz = minz = maxz = 0.0;
		denum = 0.0f;
		nx = NULL;
		ny = NULL;
		nz = NULL;
		valid=0;
	};
}GridDem;

class PropertyDataType : public osg::Referenced
{
public:
	std::map<std::string, std::string> mapProperty;
};

#endif 