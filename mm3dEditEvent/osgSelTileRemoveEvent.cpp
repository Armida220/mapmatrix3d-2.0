// osgSelTileRemove.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "osgSelTileRemoveEvent.h"
#include "InterfaceOsgFinder.h"
#include "qcomm.h"

bool COsgSelTileRemoveEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (isActivated)
	{
		if (IsLeftClick(ea) && GetKeyState(VK_CONTROL) < 0)
		{
			CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pickResult.worldPt;

			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}

			osg::ref_ptr<osg::Node> sceneNode = mRoot->getChild(0)->asGroup()->getChild(0);
			StartSelTileRemove(sceneNode, pickResult);

			iSigEventCallBack->EmitSigShowOpsHint("��Z������һ���������ESC�˳��¼�");

		}
		else if(IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)
			{
				if (vecchildNode.empty())
				{
					return false;
				}

				parentNode = vecparentNode.back();
				childNode = vecchildNode.back();

				if (parentNode && childNode)
				{
					if (childNode->getName() == "repairMatrix")
					{
						parentNode->insertChild(0, childNode);
					}
					else
					{
						parentNode->addChild(childNode);
					}

					//�ÿ�
					parentNode = NULL;
					childNode = NULL;
					vecchildNode.pop_back();
					vecparentNode.pop_back();
					iSigEventCallBack->EmitSigShowOpsHint("��Ctrl + ���ѡ��tile���Ƴ�����ESC�˳��¼�");
				}
			}
		}
	}

	return false;

}

void COsgSelTileRemoveEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false; 

	if (isActivated == true)
	{
		flag = true;
	}

	isActivated = isActivate(vecOpState, OPS_SEL_TILE_REMOVE);

	if (isActivated == false && flag == true)
	{
		//��Ϣ�ÿ�
		iSigEventCallBack->EmitSigShowOpsHint("");
	}

	if (isActivated && flag == false)																//�ռ���
	{
		vecchildNode.clear();
		vecparentNode.clear();
		iSigEventCallBack->EmitSigShowOpsHint("��Ctrl + ���ѡ��tile���Ƴ�����ESC�˳��¼�");
	}
}

bool COsgSelTileRemoveEvent::StartSelTileRemove(osg::ref_ptr<osg::Node> sceneNode, CPickResult pResult)
{
	//��ѡ��tileɾ��
	bool isSuccess = RemoveSelTile(pResult.nodePath, sceneNode);
	return isSuccess;
}


bool COsgSelTileRemoveEvent::RemoveSelTile(osg::NodePath np, osg::ref_ptr<osg::Node> sceneNode)
{
	int row = 0;
	int col = 0;
	std::string selFileName;

	for (int i = 0; i < np.size(); i++)
	{
		osg::ref_ptr<osg::PagedLOD> pagedLOD = dynamic_cast<osg::PagedLOD*> (np[i]);
		if (pagedLOD)
		{
			for (int j = 0; j < pagedLOD->getNumFileNames(); j++)
			{
				std::string fileName = pagedLOD->getFileName(j);

				if (fileName.size() > 0 && selFileName.size() == 0)
				{
					selFileName = fileName;
					break;
				}
			}
		}
	}

	if (selFileName.size() != 0)
	{
		std::vector<osg::MatrixTransform*> vecTrans;
		InterfaceOsgFinderFactory IFinderFactory;
		InterfaceOsgFinder* IFinder = IFinderFactory.create();
		IFinder->FindTransNode(sceneNode, vecTrans);

		if (vecTrans.size() == 0)
		{
			return false;
		}

		//��ѡ��tile����
		for (int i = 0; i < vecTrans.size(); i++)
		{
			osg::ref_ptr<osg::MatrixTransform> mTrans = vecTrans[i];
			int childNum = mTrans->getNumChildren();

			std::vector<osg::PagedLOD*> vecPagedLod;
			IFinder->FindPagedLod(sceneNode, vecPagedLod);

			for(int j = 0; j < vecPagedLod.size(); j++)
			{
				for (int k = 0; k < vecPagedLod[j]->getNumFileNames(); k++)
				{
					std::string fileName = vecPagedLod[j]->getFileName(k);

					if (fileName.size() > 0 && selFileName == fileName)
					{
						osg::ref_ptr<osg::Group> group = vecPagedLod[j]->getParent(0);
						//����
						vecparentNode.push_back(group) ;
						vecchildNode.push_back(vecPagedLod[j]) ;

						//osg::ref_ptr<osg::PagedLOD> pagedLod = dynamic_cast<osg::PagedLOD*> (vecPagedLod[j]->clone(osg::CopyOp::DEEP_COPY_ALL));
						group->removeChild(vecPagedLod[j]);
						return true;
					}
				}
			}
		}
	}

	//���û�ҵ����������repair�ڵ�
	for (int i = 0; i < np.size(); i++)
	{
		osg::ref_ptr<osg::MatrixTransform> mTrans = dynamic_cast<osg::MatrixTransform*> (np[i]);

		if (mTrans)
		{
			std::string repairName = mTrans->getName();

			if (repairName == "repairMatrix")
			{
				int numParent = mTrans->getNumParents();

				if (numParent > 0)
				{
					osg::ref_ptr<osg::Group> group = mTrans->getParent(0);

					if (group)
					{
						group->removeChild(mTrans);
						vecparentNode.push_back(group) ;
						vecchildNode.push_back(mTrans) ;
						break;
					}
				}

			}
			
		}
	}

	return true;
}

void COsgSelTileRemoveEvent::ObtainSelRolCowFromNodePath(osg::NodePath np, int &row, int &col)
{
	for (int i = 0; i < np.size(); i++)
	{
		osg::ref_ptr<osg::PagedLOD> pagedLOD = dynamic_cast<osg::PagedLOD*> (np[i]);
		if (pagedLOD)
		{
			for (int j = 0; j < pagedLOD->getNumFileNames(); j++)
			{
				std::string fileName = pagedLOD->getFileName(j);

				if (fileName.size() > 0)
				{
					ObtainRowAndColFromFileName(fileName, row, col);

					if (row > 0 && col > 0)
					{
						break;
					}
				}

			}

		}
	}
}


void COsgSelTileRemoveEvent::ObtainRowAndColFromFileName(std::string fileName, int &row, int &col)
{
	if (fileName.size() > 0)
	{
		int rPos = fileName.rfind('_+');
		int pos = fileName.find('_+');
		int length = fileName.length() - 1;
		std::string rowStr = fileName.substr(pos + 2, rPos);
		std::string colStr = fileName.substr(rPos + 2, length);
		row = atof(rowStr.c_str());
		col = atof(colStr.c_str());
	}
}
