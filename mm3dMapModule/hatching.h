#include <osgViewer/Viewer>
#include <osg/Group>
#include <windows.h>
#include <math.h>

#ifdef DLL_HATCH_APILIBDLL  
#define DLL_HATCH_API _declspec(dllexport)  
#else  
#define DLL_HATCH_API  _declspec(dllimport)  
#endif 

int restart ;//��¼ѭ����մ���

bool isDown;
double deltaX,deltaY;
osg::Matrix worldMatrix;

void MoveBack(osg::Vec3d &p1,osg::Vec3d &p2,osg::Group *mRoot,osg::Matrix transMatrix);
void MoveUp(osg::Vec3d &p,std::vector<osg::Vec3d>& vecLine,osg::Group *root);//����
void MoveDown(osg::Vec3d &p,std::vector<osg::Vec3d>& vecLine,osg::Group *root,osg::Matrix transMatrix);//����
void MoveForward(osg::Vec3d &p,double &dx,double &dy,std::vector<osg::Vec3d>& vecLine,osg::Group *root,osg::Matrix transMatrix);//ǰ��
osg::Geode* drawLine(osg::Vec3d p1,osg::Vec3d p2, double r, double g, double b, double a, double size);
osg::Geode* drawPoint(osg::Vec3d p, double r, double g, double b, double a, double size);
osg::StateSet* makePtState(int size);


DLL_HATCH_API  void computeHatching(osg::Vec3d Pt1,osg::Vec3d Pt2,osg::Group *root,std::vector<osg::Vec3d>& vecLine, osg::Matrix transMatrix);//���������ߣ�����㼯