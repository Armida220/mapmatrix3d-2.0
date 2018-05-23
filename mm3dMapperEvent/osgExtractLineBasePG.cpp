
#include "stdafx.h"
#include "resource.h"
#include <direct.h>
#include <iostream>
#include <string>  
#include <fstream>  
#include <streambuf>  
#include "osgExtractLineBasePG.h"
#include "InterfaceBaseDrawer.h"
#include "outline_3.h"
#include <osgDB/ReadFile>
#include <osgViewer/Renderer>
#include "osgUtil/RayIntersector"
#include <algorithm>
#include "PGControl.h"
#include "json/reader.h"
#include "json/value.h"
#include "json/writer.h"
#include "osg/KdTree"
using namespace std;

void COsgExtractLineBasePGEvent::RegisterJScripts()
{
	//���exe·��
	char szapipath[MAX_PATH];
	memset(szapipath, 0, MAX_PATH);
	GetModuleFileNameA(NULL, szapipath, MAX_PATH);
	mEXEPath = string(szapipath);
	int pos = mEXEPath.rfind('\\');
	mEXEPath = mEXEPath.substr(0, pos);

	//��ʼ��temp_found 
	std::ifstream in0(mEXEPath +"\\scripts\\initializeTempFound.sql");
	string s0((istreambuf_iterator<char>(in0)), istreambuf_iterator<char>());
	PQexec(conn, s0.c_str());

	//���temp_rec��  temprec���¼һ��tile�е�������¼
	std::ifstream in1(mEXEPath + "\\scripts\\checktempRecTable.sql");
	string s1((istreambuf_iterator<char>(in1)), istreambuf_iterator<char>());
	PQexec(conn, s1.c_str());
	
	//���temp_rec
	std::ifstream in2(mEXEPath + "\\scripts\\clearTempRec.sql");
	string s2((istreambuf_iterator<char>(in2)), istreambuf_iterator<char>());
	PQexec(conn, s2.c_str());//���ؽű�

	//��ȡ����tile��
	std::ifstream in3(mEXEPath + "\\scripts\\selectAllTileTable.sql");
	string s3((istreambuf_iterator<char>(in3)), istreambuf_iterator<char>());
	PQexec(conn, s3.c_str());//���ؽű�

	//���������Ƭ�Ƿ�������  δ��������ѡ���Ƿ����
	std::ifstream in4(mEXEPath + "\\scripts\\checkTheTriFound.sql");
	string s4((istreambuf_iterator<char>(in4)), istreambuf_iterator<char>());
	PQexec(conn, s4.c_str());//���ؽű�

	std::ifstream in5(mEXEPath + "\\scripts\\getRootTilebyPoint.sql");
	string s5((istreambuf_iterator<char>(in5)), istreambuf_iterator<char>());
	PQexec(conn, s5.c_str());//���ؽű�
	
	std::ifstream in6(mEXEPath + "\\scripts\\getSecondTilebyRoot.sql");
	string s6((istreambuf_iterator<char>(in6)), istreambuf_iterator<char>());
	PQexec(conn, s6.c_str());//���ؽű�
	
	std::ifstream in7(mEXEPath + "\\scripts\\getBottomTile.sql");
	string s7((istreambuf_iterator<char>(in7)), istreambuf_iterator<char>());
	PQexec(conn, s7.c_str());//���ؽű�
	
	std::ifstream in8(mEXEPath + "\\scripts\\checkBottomTile.sql");
	string s8((istreambuf_iterator<char>(in8)), istreambuf_iterator<char>());
	PQexec(conn, s8.c_str());//���ؽű�

	std::ifstream in9(mEXEPath + "\\scripts\\deleteLastNRecordFound.sql");
	string s9((istreambuf_iterator<char>(in9)), istreambuf_iterator<char>());
	PQexec(conn, s9.c_str());//���ؽű�
	
	std::ifstream in10(mEXEPath + "\\scripts\\getNumofTempFound.sql");
	string s10((istreambuf_iterator<char>(in10)), istreambuf_iterator<char>());
	PQexec(conn, s10.c_str());//���ؽű�

	std::ifstream in11(mEXEPath + "\\scripts\\deleteFromTempFound.sql");
	string s11((istreambuf_iterator<char>(in11)), istreambuf_iterator<char>());
	PQexec(conn, s11.c_str());//���ؽű�

	std::ifstream in12(mEXEPath + "\\scripts\\insertGeometry.sql");
	string s12((istreambuf_iterator<char>(in12)), istreambuf_iterator<char>());
	PQexec(conn, s12.c_str());//���ؽű�

	std::ifstream in13(mEXEPath + "\\scripts\\baseFunction.txt");
	string s13((istreambuf_iterator<char>(in13)), istreambuf_iterator<char>());
	PQexec(conn, s13.c_str());//���ؽű�
	
}

void COsgExtractLineBasePGEvent::UnRegisterJScripts()
{
	//ж����������ؽű�
	std::ifstream in0(mEXEPath + "\\scripts\\UninstallContourScripts.sql");
	string s0((istreambuf_iterator<char>(in0)), istreambuf_iterator<char>());
	PQexec(conn, s0.c_str());
	PQexec(conn, "begin;select UninstallContourScripts();drop function UninstallContourScripts();commit;");
}

void COsgExtractLineBasePGEvent::deleteOutofPolygon(std::vector<osg::Vec3d>& vCoord)
{
	std::ifstream in0(mEXEPath + "\\scripts\\getTriOutofContour.sql");
	string s0((istreambuf_iterator<char>(in0)), istreambuf_iterator<char>());
	PQexec(conn, s0.c_str());//���ؽű�
	char sql[1024];
	std::string sPoly("polygon((");
	for (auto pt : vCoord)
	{
		sPoly += (to_string(pt.x()) + " " + to_string(pt.y()) + ",");
	}
	sPoly += (to_string(vCoord[0].x()) + " " + to_string(vCoord[0].y()));
	sPoly += "))";
	
	string sSQL("select getTriOutofContour('");
	sSQL += (sPoly + "')");
	PQexec(conn, sSQL.c_str());
	//sprintf_s(sql, "select id,tilename,v3_z,tri from temp_object where st_contains(geometry(%s),tri) = 'f'",mContour.c_str());
	PGresult* res = PQexec(conn, "select id,tilename,z,tri from temp_trioutcontour order by z");
	for (int i = 0;i<PQntuples(res);++i)
	{
		int id = atoi(PQgetvalue(res, i, 0));
		string tile = PQgetvalue(res, i, 1);
		double z = atof(PQgetvalue(res,i,2));
		string geom = PQgetvalue(res, i, 3);
		/*PGresult* ress = PQexec(conn, "select line from tb_contour_simple where id = 274");
		geom = PQgetvalue(ress, 0, 0);*/
		if (z > mZ)
		{
			continue;
		}
		/*sprintf_s(sql, "select id,tilename from temp_object where st_intersects(geometry('%s'),tri) and v1_z > %f order by v1_z desc", geom.c_str(),z);
		PGresult* res1 = PQexec(conn, sql);*/
		sprintf_s(sql, "select id,tilename,z from temp_trioutcontour where st_intersects(geometry('%s'),tri) and st_touches(geometry('%s'),tri) = 'f'  and (id <> %d) order by z", geom.c_str(), geom.c_str(), id,tile.c_str(),z);
		PGresult* res2 = PQexec(conn, sql);
		if (PQntuples(res2) == 0)//����
		{
			/*int id1 = atoi(PQgetvalue(res1, 0, 0));
			string tile1 = PQgetvalue(res1, 0, 1);*/
			sprintf_s(sql, "delete from temp_object where id = %d and tilename = '%s'", id, tile.c_str());
			PQexec(conn, sql);
		}
		else if (PQntuples(res2) > 0)
		{
			double z2 = atof(PQgetvalue(res2, 0, 2));
			int id2 = atoi(PQgetvalue(res2, 0, 0));
			string tile2 = PQgetvalue(res2, 0, 1);
			if (z2 > z)
			{
				sprintf_s(sql, "delete from temp_object where id = %d and tilename = '%s'", id, tile.c_str());
				PQexec(conn, sql);
			}
			if (abs(z - z2) < 0.01)
			{
				sprintf_s(sql, "delete from temp_object where id = %d and tilename = '%s'", id, tile.c_str());
				PQexec(conn, sql);
				/*sprintf_s(sql, "delete from temp_object where id = %d and tilename = '%s'", id2, tile2.c_str());
				PQexec(conn, sql);*/
			}
		}
	}
}

void COsgExtractLineBasePGEvent::deleteTriInAngle(std::vector<int>& vNei, double nx, double ny, double nz, std::string tilename)
{
	char sql[2048];
	std::vector<int> vnei;
	mVec.clear();
	while (!vNei.empty())
	{
		vnei.clear();
		for (auto id : vNei)
		{
			sprintf_s(sql, "select * from temp_found where id = %d and tilename = '%s'", id, tilename.c_str());
			PGresult* r = PQexec(conn, sql);
			if (PQntuples(r)>0)
			{
				continue;
			}
			sprintf_s(sql, "insert into temp_found values(%d,'%s')", id, tilename.c_str());
			PQexec(conn, sql);
			sprintf_s(sql, "select * from temp_object where id = %d and tilename = '%s' and testvectorangleinerror(nx,ny,nz,0,0,1,70)", id, tilename.c_str());
			PGresult* res = PQexec(conn, sql);

			if (PQntuples(res) > 0)//�������ɾ������
			{
				sprintf_s(sql, "delete from temp_object where id = %d and tilename = '%s'", id, tilename.c_str());
				PQexec(conn, sql);
				if (atoi(PQgetvalue(res, 0, 14)) != 0)
				{
					vnei.push_back(atoi(PQgetvalue(res, 0, 14)));
				}
				if (atoi(PQgetvalue(res, 0, 15)) != 0)
				{
					vnei.push_back(atoi(PQgetvalue(res, 0, 15)));
				}
				if (atoi(PQgetvalue(res, 0, 16)) != 0)
				{
					vnei.push_back(atoi(PQgetvalue(res, 0, 16)));
				}
				sprintf_s(sql, "select edge from %s where id = %d", tilename.c_str(), id);
				PGresult* res1 = PQexec(conn, sql);
				if (atoi(PQgetvalue(res1, 0, 0)) != 0)
				{
					mVec.push_back(id);
				}
			}
		}
		vNei.assign(vnei.begin(), vnei.end());
	}
}

void COsgExtractLineBasePGEvent::editObject(osg::Vec3d worldPt, osg::Vec3d worldNm)
{
	char sql[1024];
	InterfaceBaseDrawerFactory IDrawerFactory;
	InterfaceBaseDrawer* IDrawer = IDrawerFactory.create();
	Json::Reader reader;
	Json::Value root;
	sprintf_s(sql, "select editobject('point(%f %f)',%f)", worldPt.x(), worldPt.y(), worldPt.z());
	PGresult* res = PQexec(conn, sql);
	
	/*if (PQntuples(res) > 0)
	{
		std::vector<osg::Vec3d> vPt;
		string sres = PQgetvalue(res, 0, 0);
		reader.parse(sres,root);
		std::string tile = root["tilename"].asString();
		int id = root["id"].asInt();
		int n1 = root["n1"].asInt();
		int n2 = root["n2"].asInt();
		int n3 = root["n3"].asInt();
		sprintf_s(sql, "delete from temp_object where id = %d and tilename = '%s'", id, tile.c_str());
		PQexec(conn, sql);

		std::vector<int> vNei;
		if (n1 != 0)
		{
			vNei.push_back(n1);
		}
		if (n2 != 0)
		{
			vNei.push_back(n2);
		}
		if (n3 != 0)
		{
			vNei.push_back(n3);
		}
		deleteTriInAngle(vNei,1,1,1,tile);
		CPGController pgControl;
		int nk = mVec.size();
		while (mVec.size()>0)
		{
			for (int i = 0;i<mVec.size();++i)
			{
				sprintf_s(sql, "select * from %s where id = %d", tile.c_str(), mVec[i]);
				res = PQexec(conn, sql);
				double x1 = atof(PQgetvalue(res, 0, 2));
				double y1 = atof(PQgetvalue(res, 0, 3));
				double z1 = atof(PQgetvalue(res, 0, 4));
				double x2 = atof(PQgetvalue(res, 0, 5));
				double y2 = atof(PQgetvalue(res, 0, 6));
				double z2 = atof(PQgetvalue(res, 0, 7));
				double x3 = atof(PQgetvalue(res, 0, 8));
				double y3 = atof(PQgetvalue(res, 0, 9));
				double z3 = atof(PQgetvalue(res, 0, 10));

				CTri3D tris(point3D(x1, y1, z1), point3D(x2, y2, z2), point3D(x3, y3, z3));
				point3D ppt(x1, y1, z1);
				string newTile;
				vNei.clear();
				int k = pgControl.getNeighborTile(conn, tris, ppt, tile, newTile, vNei);
				if (k == -1)
				{
					continue;
				}
				tile = newTile;
				deleteTriInAngle(vNei, 1, 1, 1, tile);
				break;
			}			
		}*/
		osg::ref_ptr<osg::Group> group = new osg::Group;
		ClearGroupResult(mapperGroup);
		res = PQexec(conn, "select v1_x,v1_y,v1_z,v2_x,v2_y,v2_z,v3_x,v3_y,v3_z from temp_object");
		int n = PQntuples(res);
		for (int i = 0;i<n;++i)
		{
			double x1 = atof(PQgetvalue(res, i, 0));
			double y1 = atof(PQgetvalue(res, i, 1));
			double z1 = atof(PQgetvalue(res, i, 2));
			double x2 = atof(PQgetvalue(res, i, 3));
			double y2 = atof(PQgetvalue(res, i, 4));
			double z2 = atof(PQgetvalue(res, i, 5));
			double x3 = atof(PQgetvalue(res, i, 6));
			double y3 = atof(PQgetvalue(res, i, 7));
			double z3 = atof(PQgetvalue(res, i, 8));
			std::vector<osg::Vec3d> vPt;
			vPt.push_back(osg::Vec3d(x1, y1, z1));
			vPt.push_back(osg::Vec3d(x2, y2, z2));
			vPt.push_back(osg::Vec3d(x3, y3, z3));
			IDrawer->BaseDrawPolygon(vPt, osg::Vec4(1, 1, 0, 0.4), group, worldMatrix);
		}
		mapperGroup->addChild(group.get());
	//}
}

bool COsgExtractLineBasePGEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (isActivated)
	{
		if (IsLeftClick(ea) && GetKeyState(VK_CONTROL) < 0)
		{
			CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
			worldPt = pickResult.localPt;
			worldMatrix = pickResult.matrix;
			normal = pickResult.worldNm;
			np = pickResult.nodePath;
			xx = ea.getX();
			yy = ea.getY();
			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}
			if (bEditObject)
			{
				editObject(worldPt,worldNm);
				return false;
			}

			bReplace = false;
			if (LeftClickSearchPostGis(ea.getX(), ea.getY(), worldPt, np, normal, worldMatrix))
			{
				iSigEventCallBack->EmitSigShowOpsHint("��� (A:ȫ������ȡ����)");
			}
			else
			{
				iSigEventCallBack->EmitSigShowOpsHint("ʧ��");
			}
		}
		else if (IsDoubleClick(ea) )
		{
			CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d pt = pickResult.localPt;
			int k = deleteResFromPG(conn, pt);
			if ( k == -1)
			{
				iSigEventCallBack->EmitSigShowOpsHint("δ�ҵ���ɾ������");
			}
			else
			{
				ClearGroupResult(mapperGroup);
				readContourFromPG(conn, "tb_contour");
				char msg[99];
				sprintf_s(msg, "��ִ��һ��ɾ������,ɾ������id = %d", k);
				iSigEventCallBack->EmitSigShowOpsHint(msg);
			}		
		}
		else if (IsRightClick(ea) /*&& GetKeyState(VK_CONTROL) < 0*/)
		{
			CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
			worldPt = pickResult.localPt;
			worldMatrix = pickResult.matrix;
			normal = pickResult.worldNm;
			np = pickResult.nodePath;
			xx = ea.getX();
			yy = ea.getY();
			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}
			if (bEditObject)
			{
				//mZ = worldPt.z();
				vecCoord.push_back(worldPt);
				return false;
			}
			bReplace = true;
			int k = LeftClickSearchPostGis(ea.getX(), ea.getY(), worldPt, np, normal, worldMatrix);
			if (k != 0)
			{
				if (k == -1)
				{
					iSigEventCallBack->EmitSigShowOpsHint("��� ,���滻����");
				}
				else
				{
					ClearGroupResult(mapperGroup);
					readContourFromPG(conn, "tb_contour");
					char msg[90];
					sprintf_s(msg, "��� ,�滻���ݿ���ID��Ϊ%d��������",k);
					iSigEventCallBack->EmitSigShowOpsHint(msg);
				}
			}
			else
			{
				iSigEventCallBack->EmitSigShowOpsHint("ʧ��");
			}
		}
		else if (IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_BackSpace)					 //BackSpace
			{
				int childNum = mapperGroup->getNumChildren();

				if (childNum > 0)
				{
					mapperGroup->removeChild(childNum - 1);
				}
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)
			{
				ClearGroupResult(mapperGroup);
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_A)
			{
				iSigEventCallBack->EmitSigShowOpsHint("����ȫ������ȡ����...");
				extentAll(conn);
				iSigEventCallBack->EmitSigShowOpsHint("���");
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_P)
			{
				
				
				iSigEventCallBack->EmitSigShowOpsHint("����ѡ����...");
				CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
				worldPt = pickResult.localPt;
				worldMatrix = pickResult.matrix;
				DoExtractObject(conn, worldPt.x(), worldPt.y());
				iSigEventCallBack->EmitSigShowOpsHint("���");
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_G)
			{
				iSigEventCallBack->EmitSigShowOpsHint("����������...");
				readContourFromPG(conn,"tb_contour_simple");
				iSigEventCallBack->EmitSigShowOpsHint("ԭʼ�����߼������");
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_F)
			{
				iSigEventCallBack->EmitSigShowOpsHint("����������...");
				readContourFromPG(conn,"tb_contour");
				iSigEventCallBack->EmitSigShowOpsHint("�������߼������");
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_E)
			{
				bEditObject = !bEditObject;

				if (bEditObject)
				{
					iSigEventCallBack->EmitSigShowOpsHint("�༭����");
				}
				else
				{

					iSigEventCallBack->EmitSigShowOpsHint("");
				}
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_K)
			{
				//if (vecCoord.size()>=3)
				{
					InterfaceBaseDrawerFactory IDrawerFactory;
					InterfaceBaseDrawer* IDrawer = IDrawerFactory.create();
					deleteOutofPolygon(vecCoord);
					osg::ref_ptr<osg::Group> group = new osg::Group;
					ClearGroupResult(mapperGroup);
					PGresult* res = PQexec(conn, "select v1_x,v1_y,v1_z,v2_x,v2_y,v2_z,v3_x,v3_y,v3_z from temp_object");
					int n = PQntuples(res);
					for (int i = 0; i < n; ++i)
					{
						double x1 = atof(PQgetvalue(res, i, 0));
						double y1 = atof(PQgetvalue(res, i, 1));
						double z1 = atof(PQgetvalue(res, i, 2));
						double x2 = atof(PQgetvalue(res, i, 3));
						double y2 = atof(PQgetvalue(res, i, 4));
						double z2 = atof(PQgetvalue(res, i, 5));
						double x3 = atof(PQgetvalue(res, i, 6));
						double y3 = atof(PQgetvalue(res, i, 7));
						double z3 = atof(PQgetvalue(res, i, 8));
						std::vector<osg::Vec3d> vPt;
						vPt.push_back(osg::Vec3d(x1, y1, z1));
						vPt.push_back(osg::Vec3d(x2, y2, z2));
						vPt.push_back(osg::Vec3d(x3, y3, z3));
						IDrawer->BaseDrawPolygon(vPt, osg::Vec4(1, 1, 0, 0.4), group, worldMatrix);
					}
					mapperGroup->addChild(group.get());
				}
				vecCoord.clear();
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_O)
			{
				char sql[512];
				InterfaceBaseDrawerFactory IDrawerFactory;
				InterfaceBaseDrawer* IDrawer = IDrawerFactory.create();
				osg::ref_ptr<osg::Group> group = new osg::Group;
				PGresult* res = PQexec(conn, "select * from temp_trioutcontour");
				for (int i = 0;i<PQntuples(res);++i)
				{
					sprintf_s(sql, "select * from %s where id = %d", PQgetvalue(res, i, 1), atoi(PQgetvalue(res, i, 0)));
					PGresult* res1 = PQexec(conn, sql);
					double x1 = atof(PQgetvalue(res1, 0, 2));
					double y1 = atof(PQgetvalue(res1, 0, 3));
					double z1 = atof(PQgetvalue(res1, 0, 4));
					double x2 = atof(PQgetvalue(res1, 0, 5));
					double y2 = atof(PQgetvalue(res1, 0, 6));
					double z2 = atof(PQgetvalue(res1, 0, 7));
					double x3 = atof(PQgetvalue(res1, 0, 8));
					double y3 = atof(PQgetvalue(res1, 0, 9));
					double z3 = atof(PQgetvalue(res1, 0, 10));
					std::vector<osg::Vec3d> vPt;
					vPt.push_back(osg::Vec3d(x1, y1, z1));
					vPt.push_back(osg::Vec3d(x2, y2, z2));
					vPt.push_back(osg::Vec3d(x3, y3, z3));
					IDrawer->BaseDrawPolygon(vPt, osg::Vec4(0, 0, 1, 0.6), group, worldMatrix);
				}
				mapperGroup->addChild(group.get());
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_R)//��ת
			{
				CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
				worldPt = pickResult.worldPt;

				osg::Vec3d eye;
				osg::Vec3d center;
				osg::Vec3d up;

				
				osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> spCameraManipulator = dynamic_cast<osgGA::KeySwitchMatrixManipulator*>(mViewer->getCameraManipulator());
				osg::ref_ptr<osgGA::StandardManipulator> manip = dynamic_cast<osgGA::StandardManipulator*>(spCameraManipulator->getCurrentMatrixManipulator());
				manip->getTransformation(eye, center, up);

				double radiu = (eye - center).length();
				double dx = sqrt(2)* radiu * sin(2.0 / 180);
				double dy = dx;

				if (eye.x()<=0 && eye.y()>=0)
				{
					eye.y() -= dy;
					eye.x() -= dx;
				}
				else if (eye.x()<=0 && eye.y()<=0)
				{
					eye.y() -= dy;
					eye.x() += dx;
				}
				else if (eye.x()>=0 && eye.y()<=0)
				{
					eye.y() += dy;
					eye.x() += dx;
				}
				else if (eye.x()>=0 && eye.y()>=0)
				{
					eye.y() += dy;
					eye.x() -= dx;
				}

				up = center - eye;
				
				manip->setTransformation(eye, center, up);
				mViewer->getCamera()->setViewMatrixAsLookAt(eye, center, up);
			}
		}
	}
	return false;
}

void COsgExtractLineBasePGEvent::readContourFromPG(PGconn* conn,std::string tb)
{
	InterfaceBaseDrawerFactory IDrawerFactory;
	InterfaceBaseDrawer* IDrawer = IDrawerFactory.create();
	std::string tbs = std::string("select st_astext(line) from ") + tb;
	PGresult* res = PQexec(conn, tbs.c_str());
	for (int i = 0;i<PQntuples(res);++i)
	{
		std::string polygon(PQgetvalue(res, i, 0));
		CPGController pgControl;
		std::vector<osg::Vec3d> vecPt;
		std::vector<point3D> vecPt3D;
		std::vector<std::vector<point3D> > vecVecPt3D;
		pgControl.analysisGeometryDataString(polygon, vecPt3D,vecVecPt3D,GEOMETRY_TYPE::PG_POLYGON);
		for (auto pt : vecPt3D)
		{
			vecPt.push_back(osg::Vec3d(pt.x,pt.y,pt.z));
		}
		if (tb == std::string("tb_contour"))
		{
			IDrawer->BaseDrawLineLoopOperate(vecPt, osg::Vec4(1, 1, 0, 1), 2.0, mapperGroup, worldMatrix);
		}
		else
			IDrawer->BaseDrawLineLoopOperate(vecPt, osg::Vec4(1, 0, 0, 1), 2.0, mapperGroup, worldMatrix);
	}
}

void COsgExtractLineBasePGEvent::DoExtractObject(PGconn* conn, double x, double y, double dist)
{
	InterfaceBaseDrawerFactory IDrawerFactory;
	InterfaceBaseDrawer* IDrawer = IDrawerFactory.create();
	osg::ref_ptr<osg::Group> group = new osg::Group;
	std::string sPoly;
	CPGController pgControl;
	std::vector<CTri3D> vecTri;
	
	pgControl.getObject(conn, x, y, dist, sPoly,vecTri, mContour,mZ);
	std::vector<point3D> vecPt3D;
	std::vector<std::vector<point3D> > vecVecPt3D;
	if (vecTri.size()>0)//�¹����Ķ��� ֱ�ӻ���
	{
		for (auto tri:vecTri)
		{
			std::vector<osg::Vec3d> vPt;
			vPt.push_back(osg::Vec3d(tri.p1.x,tri.p1.y, tri.p1.z));
			vPt.push_back(osg::Vec3d(tri.p2.x, tri.p2.y, tri.p2.z));
			vPt.push_back(osg::Vec3d(tri.p3.x, tri.p3.y, tri.p3.z));
			IDrawer->BaseDrawPolygon(vPt, osg::Vec4(1, 1, 0, 0.4), group, worldMatrix);
		}
	}
	else//������ݿ��д��ڸö��� ���ȡ���������� Ȼ�����
	{
		pgControl.analysisGeometryDataString(sPoly, vecPt3D, vecVecPt3D, GEOMETRY_TYPE::PG_MULTIPOLYGON);
		if (vecVecPt3D.size() > 0)
		{
			for (int i = 0; i < vecVecPt3D.size(); ++i)
			{
				std::vector<osg::Vec3d> vPt;
				for (int j = 0; j < vecVecPt3D[i].size(); ++j)
				{
					vPt.push_back(osg::Vec3d(vecVecPt3D[i][j].x, vecVecPt3D[i][j].y, vecVecPt3D[i][j].z));
				}
				IDrawer->BaseDrawPolygon(vPt, osg::Vec4(1, 1, 0, 0.4), group, worldMatrix);
			}
		}
	}
	if(group->getNumChildren()>0)
		mapperGroup->addChild(group.get());
}

void COsgExtractLineBasePGEvent::extentAll(PGconn* conn)
{
	InterfaceBaseDrawerFactory IDrawerFactory;
	InterfaceBaseDrawer* IDrawer = IDrawerFactory.create();
	int nFound = 0;
	std::vector<std::string> vecTable;
	std::vector<ID_TILE_PAIR> vecITP;
	char sql[1024];
	sprintf_s(sql, "select selectAllTileTable()");
	PGresult* res = PQexec(conn, sql);
	if (PQntuples(res) == 0)
		return;

	std::ifstream in0(mEXEPath + "\\scripts\\SelectExtentTribyAngle.sql");
	string sJS((istreambuf_iterator<char>(in0)), istreambuf_iterator<char>());
	
	for (int i = 0;i<PQntuples(res);++i)
	{
		std::string sData = sJS;
		replace_all(sData, "para_tablename", PQgetvalue(res, i, 0));
		PQexec(conn, sData.c_str());
		sprintf_s(sql, "select SelectExtentTribyAngle(%f,5)", worldPt.z());
		PGresult* res1 = PQexec(conn, sql);
		for (int j = 0; j <  PQntuples(res1); ++j)
		{
			ID_TILE_PAIR itp;
			itp.id = atoi(PQgetvalue(res1, j, 0));
			itp.tilename = PQgetvalue(res, i, 0);
			vecITP.push_back(itp);
		}
	}
	
	std::ifstream in1("E:\\svn_code2.0\\MM3D_0519\\mm3dMapperEvent\\scripts\\getExtentStartTri.sql");
	sJS = string((istreambuf_iterator<char>(in1)), istreambuf_iterator<char>());
	Json::Reader reader;
	Json::Value root;
	
	for (int i = 0;i<vecITP.size();++i)
	{
		string sData = sJS;
		replace_all(sData, "para_tablename", vecITP[i].tilename);
		PQexec(conn, sData.c_str());
		sprintf_s(sql, "select getExtentStartTri(%d)", vecITP[i].id);
		res = PQexec(conn, sql);
		string sRes = PQgetvalue(res, 0, 0);
		reader.parse(sRes, root);
		if (root["found"].asInt() == 0)
			continue;
		CTri3D tri;
		std::vector<int> vecInt;
		double x1 = root["x1"].asDouble();
		double y1 = root["y1"].asDouble();
		double z1 = root["z1"].asDouble();
		double x2 = root["x2"].asDouble();
		double y2 = root["y2"].asDouble();
		double z2 = root["z2"].asDouble();
		double x3 = root["x3"].asDouble();
		double y3 = root["y3"].asDouble();
		double z3 = root["z3"].asDouble();

		if (root["n1"].asInt() != 0)
			vecInt.push_back(root["n1"].asInt());
		if (root["n2"].asInt() != 0)
			vecInt.push_back(root["n2"].asInt());
		if (root["n3"].asInt() != 0)
			vecInt.push_back(root["n3"].asInt());
		
		tri.p1 = point3D(x1, y1, z1);
		tri.p2 = point3D(x2, y2, z2);
		tri.p3 = point3D(x3, y3, z3);
		
		//��¼����֮ǰtemp_found��¼��
		sprintf_s(sql, "select getNumofTempFound()");
		res = PQexec(conn, sql);
		int numRecord = atoi(PQgetvalue(res, 0, 0));
		std::vector<point3D> vecResLine;
		CPGController pgControl;
		pgControl.DoSearchContourPostGis(conn,tri, vecITP[i].id, vecITP[i].tilename, vecInt, vecResLine,worldPt.z(), 0);
		if (vecResLine.size() == 0)
			continue;
		
		if (pgControl.vec3dEqWithEPS(vecResLine.back(),vecResLine.front()))
		{
			//���ƽ��
			std::vector<osg::Vec3d> vecLineResOSG;//������ʾ���
			for (auto pt : vecResLine)
			{
				vecLineResOSG.push_back(osg::Vec3d(pt.x, pt.y, pt.z));
			}
			IDrawer->BaseDrawCurLineOperate(vecLineResOSG, osg::Vec4(1, 1, 0, 1), 2.5, mapperGroup, worldMatrix);
			//�������polygon���浽postGis
			pgControl.insertGeometry(conn, vecResLine,EXTRACT_TYPE::CONTOUR);
		}
		else
		{
			//��������·��
			sprintf_s(sql, "select deleteLastNRecordFound(%d)", numRecord);
			PQexec(conn, sql);
		}
	}
}

int COsgExtractLineBasePGEvent::deleteResFromPG(PGconn* conn, osg::Vec3d pt)
{
	CPGController pgControl;
	return pgControl.deleteGeomFromPG(conn, pt.x(), pt.y());
}

int COsgExtractLineBasePGEvent::LeftClickSearchPostGis(float x, float y, osg::Vec3d worldPt, osg::NodePath& np, osg::Vec3d nm,osg::Matrix worldMatrix)
{
	InterfaceBaseDrawerFactory IDrawerFactory;
	InterfaceBaseDrawer* IDrawer = IDrawerFactory.create();

	char msg[255];
	char sql[1024];

	CPGController pgControl;
	std::string m_tableName("");
	
	if (!getLodBottomLevelFile(x, y, np, mViewer, m_tableName))//��������ײ��ļ�ʧ��
	{
		iSigEventCallBack->EmitSigShowOpsHint("������ײ��ļ�ʧ��!");
		return 0;
	}

	//����������Ƭ
	CTri3D tri;
	int idSel;
	std::vector<int> ivecNeighbor;
	
	int numTri = pgControl.getContourStartTri(conn, point3D(worldPt.x(), worldPt.y(), worldPt.z()), point3D(nm.x(), nm.y(), nm.z()),
		m_tableName, tri, idSel, ivecNeighbor);

	if (numTri < 1)
	{
		iSigEventCallBack->EmitSigShowOpsHint("��ȡ������Ƭʧ��!");
		return 0;
	}
	else
	{
		sprintf_s(msg, "������%d��������Ƭ", numTri);
		iSigEventCallBack->EmitSigShowOpsHint(msg);
	}
	std::vector<point3D> vecLineRes;
	pgControl.DoSearchContourPostGis(conn,tri,idSel,m_tableName,ivecNeighbor,vecLineRes,worldPt.z());
	//����ɹ�
	if (vecLineRes.empty())
	{
		iSigEventCallBack->EmitSigShowOpsHint("�����쳣��");
		return 0;
	}
	std::vector<osg::Vec3d> vecLineResOSG;//������ʾ���
	for (auto pt : vecLineRes)
	{
		vecLineResOSG.push_back(osg::Vec3d(pt.x,pt.y,pt.z));
	}
	if (vecLineRes.back() == vecLineRes.front())
	{	
		std::string sSql;
		//���ƽ��
		IDrawer->BaseDrawCurLineOperate(vecLineResOSG, osg::Vec4(1, 1, 0, 1), 2.5, mapperGroup, worldMatrix);

		
		//������滻��ֱ�ӱ���
		if (!bReplace)
		{
			pgControl.insertGeometry(conn, vecLineRes, EXTRACT_TYPE::CONTOUR);//�������polygon���浽postGis
		}
		else//�����滻���ݿ��¼
		{
			//����polygon�ַ���
			std::string sPolygon = "polygon((";
			for (int i = 0; i < vecLineRes.size(); ++i)
			{
				sPolygon += (std::to_string(vecLineRes[i].x) + std::string(" ") + std::to_string(vecLineRes[i].y)
					+ std::string(" ") + std::to_string(vecLineRes[i].z) + std::string(","));
			}
			sPolygon += (std::to_string(vecLineRes[0].x) + std::string(" ") + std::to_string(vecLineRes[0].y)
				+ std::string(" ") + std::to_string(vecLineRes[0].z) + "))");
			
			sSql = "select id from tb_contour where st_intersects(line,'";
			sSql = sSql + sPolygon + "') = 't'";
			PGresult* res = PQexec(conn, sSql.c_str());
			if (PQntuples(res)>0)
			{
				int n = atoi(PQgetvalue(res, 0, 0));
				sprintf_s(sql,"delete from tb_contour where id = %d",n);
				PQexec(conn, sql);
				sprintf_s(sql, "delete from tb_contour_simple where id = %d", n);
				PQexec(conn, sql);
				pgControl.insertGeometry(conn, vecLineRes, EXTRACT_TYPE::CONTOUR, n);//�������polygon���浽postGis
				return n;
			}
			else
			{
				return -1;
			}
		}
	}
	else
	{
		//���ƽ��
		IDrawer->BaseDrawCurLineOperate(vecLineResOSG, osg::Vec4(1, 0, 0, 1), 2.5, mapperGroup, worldMatrix);
		return -1;
	}
	return true;
}

void COsgExtractLineBasePGEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	InterfaceBaseDrawerFactory IDrawerFactory;
	InterfaceBaseDrawer* IDrawer = IDrawerFactory.create();
	bool flag = false;

	if (isActivated == true)
	{
		flag = true;
	}

	isActivated = isActivate(vecOpState, OPS_EXTRACT_OUTLINE_BY_POSTGIS);

	if (isActivated == false && flag == true)
	{
		if (conn)
		{
			UnRegisterJScripts();
			PQfinish(conn);
		}
		iSigEventCallBack->EmitSigShowOpsHint("");
	}

	if (isActivated && flag == false)																//�ռ���
	{
		CPGController pgControl;
		conn = pgControl.connectToDB();
		RegisterJScripts();//ע��ű�
		iSigEventCallBack->EmitSigShowOpsHint("postgis ����");
	}
}

bool COsgExtractLineBasePGEvent::getLodBottomLevelFile(float x, float y, osg::NodePath& np, osgViewer::Viewer *mViewer, std::string& m_tableName)
{
	InterfaceOsgFinderFactory IFinderFactory;
	InterfaceOsgFinder* IFinder = IFinderFactory.create();

	//���ҵײ�����
	std::vector<std::string> vecChildFileName;

	for (int i = np.size() - 1; i >= 0; i--)
	{
		osg::ref_ptr<osg::PagedLOD> lod = dynamic_cast<osg::PagedLOD*> (np[i]);

		if (lod)
		{
			IFinder->FindLodBottomLevelFile(lod, vecChildFileName);
			break;
		}
	}
	if (vecChildFileName.size() == 0)
		return false;
	if (vecChildFileName.size() > 1)
	{
		osg::ref_ptr<osg::Camera> camera = mViewer->getCamera();
		osgViewer::Renderer *render = dynamic_cast<osgViewer::Renderer *>(camera->getRenderer());
		osgUtil::SceneView *sceneView = render->getSceneView(0);
		osg::Vec3 vScreen1(x, y, 0);
		osg::Vec3 vScreen2(x, y, 1);
		osg::Vec3 window1, window2;
		sceneView->projectWindowIntoObject(vScreen1, window1);
		sceneView->projectWindowIntoObject(vScreen2, window2);

		for (int j = 0; j < vecChildFileName.size(); ++j)
		{
			osg::Node* node = osgDB::readNodeFile(vecChildFileName[j]);
			if (node)
			{
				osg::ref_ptr<osgUtil::RayIntersector> ri = new osgUtil::RayIntersector(window1, window2 - window1);
				osgUtil::IntersectionVisitor iv1(ri);
				node->accept(iv1);
				if (ri.valid() && ri->containsIntersections())
				{
					m_tableName = vecChildFileName[j];
					break;
				}
			}
		}
	}
	else
	{
		m_tableName = vecChildFileName[0];
	}
	if (m_tableName.empty())
	{
		return false;
	}
	m_tableName = getTableName(m_tableName);
	replace_all(m_tableName, "+", "");
	std::transform(m_tableName.begin(), m_tableName.end(), m_tableName.begin(), ::tolower);
	return true;
}

string COsgExtractLineBasePGEvent::getTableName(string fileName)
{
	int pos = fileName.rfind("\\");
	int pos1 = fileName.rfind("\/");
	int pos2 = fileName.rfind(".osgb");

	int posT = (pos > pos1) ? pos : pos1;
	return fileName.substr(posT + 1, pos2 - posT - 1);
}

void COsgExtractLineBasePGEvent::replace_all(std::string& s, std::string const & t, std::string const & w)
{
	string::size_type pos = s.find(t), t_size = t.size(), r_size = w.size();
	while (pos != string::npos) { // found   
		s.replace(pos, t_size, w);
		pos = s.find(t, pos + r_size);
	}
}
