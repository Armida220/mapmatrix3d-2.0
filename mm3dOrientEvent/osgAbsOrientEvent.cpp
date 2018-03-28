// osgAbsOrientEvent.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "InterfaceMFCExcute.h"
#include "osgAbsOrientEvent.h"
#include "InterfaceBaseDrawer.h"

bool COsgAbsOrientEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (isActivated)
	{
		if (IsLeftClick(ea) && GetKeyState(VK_CONTROL) < 0)
		{
			CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pickResult.worldPt;
			osg::Matrix worldMatrix = pickResult.matrix;
			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}

			//���ѡ����
			int selRow = iSigEventCallBack->EmitSigGetSelRowFromAbsDlg();																//���ѡ����

			if (selRow < 0)
			{
				InterfaceMFCExcuteFactory IExcuteFactory;
				InterfaceMFCExcute* IExcute = IExcuteFactory.create();
				IExcute->PopUpMessage("δѡ����Ƶ㣬�������Ƶ��б����ѡ��");
				return false; 
			}

			if (iSigEventCallBack->EmitSigChangeCtrlList() == false)			//�ж��Ƿ���ɴ̵�
			{
				InterfaceMFCExcuteFactory IMfcExcuteFactory;
				InterfaceMFCExcute* IExcute = IMfcExcuteFactory.create();
				IExcute->PopUpMessage("�õ��Ѿ��̹�����ѡ���������");
				return false;
			}

			//ģ���ϻ���
			InterfaceBaseDrawerFactory IDrawerFactory;
			InterfaceBaseDrawer* IDrawer = IDrawerFactory.create();
			osg::Vec4d color(1.0, 0, 0, 1.0);
			double size = 3.5f;
			IDrawer->BaseDrawPtOperate(worldPt,color,size,mEditGroup,worldMatrix);
			//��ȡģ���ϵ�
			bool isCheckPt = false;

			int ptNum = iSigEventCallBack->EmitSigGetSelPtNumFromAbsDlg();
			IAbsOrient->ObtainModelRelativePoint(ptNum, worldPt.x(), worldPt.y(), worldPt.z(), isCheckPt);
		}
		else if (IsMouseMove(ea) && GetKeyState(VK_CONTROL) < 0)
		{

		}
		else if(IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_BackSpace)					 //BackSpace
			{
				//�س�һ����
				
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)
			{
				osg::ref_ptr<osg::Node> sceneNode = mRoot->getChild(0)->asGroup()->getChild(0);
				IAbsOrient->ReverseModelOrientation(sceneNode, absMatrix);
				iSigEventCallBack->EmitSigShowOpsHint("��������б�ѡ��̵��У�Ȼ��סctrl�������ѡ�㣬��ESC�˳��¼�");
				mViewer->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KEY_Space);
			}
		}
	}
	else
	{
		vecWorldCoord.clear();
		osg::Matrix matrix;
		absMatrix = matrix;
	}

	return false;
}

void COsgAbsOrientEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false; 

	if (isActivated == true)
	{
		flag = true;
	}

	isActivated = isActivate(vecOpState, OPS_ABSOLUTE_ORIENTATION);

	if (isActivated == false && flag == true)																	
	{
		ClearGroupResult(mEditGroup);
		IAbsOrient->ClearVecRelativePt();
		IAbsOrient->ClearVecAbsolutePt();
		//��Ϣ�ÿ�
		iSigEventCallBack->EmitSigShowOpsHint("");
		iSigEventCallBack->EmitSigCloseAbsDlg();
	}

	if (isActivated && flag == false)																//�ռ���
	{
		iSigEventCallBack->EmitSigShowOpsHint("��������б�ѡ��̵��У�Ȼ��סctrl�������ѡ�㣬��ESC�˳��¼�");
	}
}

BOOL COsgAbsOrientEvent::AbsOrient(std::string inFilePath)
{
	//�����ļ��в��������·��
	osg::ref_ptr<osg::Node> sceneNode = mRoot->getChild(0)->asGroup()->getChild(0);

	//�Ѿ��ȱ�������·������Ϊ����λ��
	if(!IAbsOrient->AbsOrient(sceneNode, inFilePath, absMatrix))
	{
		return FALSE;
	};

	mViewer->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KEY_Space);

	iSigEventCallBack->EmitSigShowOpsHint("��z������������ ��ESC�˳��¼�");

	osg::ref_ptr<osg::Group> editGroup = mRoot->getChild(1)->asGroup();
	ClearGroupResult(editGroup);
	return TRUE;
}

void COsgAbsOrientEvent::LoadControlPt()
{
	InterfaceMFCExcuteFactory IExcuteFactory;
	InterfaceMFCExcute* IExcute = IExcuteFactory.create();

	if (IAbsOrient->GetVecCtrlPt().size() > 0)
	{
		IExcute->PopUpMessage("�Ѿ����ع����Ƶ��ˣ��������μ���,��رպ������¼���");
		return;
	}

	std::string ctrlPtFileName;
	std::string extName = "Control Point Files (*.txt)|*.txt|All Files (*.*)|*.*||";
	bool isSuccess = IExcute->OpenDialog(ctrlPtFileName, extName, true);

	if (isSuccess)
	{
		FILE* fpCtrlPt = fopen(ctrlPtFileName.c_str(), "r");

		if (fpCtrlPt == NULL)
		{
			IExcute->PopUpMessage("ѡ��·������ȷ");
			return;
		}

		//���ؿ��Ƶ�
		IAbsOrient->LoadControlPoint(ctrlPtFileName);				

		std::vector<CControlPoint> vecCtrlPt = IAbsOrient->GetVecCtrlPt();
		//�����б���
		for (int i = 0; i < vecCtrlPt.size(); i++)
		{
			iSigEventCallBack->EmitSigInsertControlListRecord(vecCtrlPt[i].ptSerialNum, vecCtrlPt[i].ptX, vecCtrlPt[i].ptY, vecCtrlPt[i].ptZ);
		}
	}
}

void COsgAbsOrientEvent::ReclickCtrlPt(int ptNum)
{
	std::vector<CControlPoint> vecRelaPt = IAbsOrient->GetVecRelativePt();

	for (int i = 0; i < vecRelaPt.size(); i++)
	{
		if (ptNum == vecRelaPt[i].ptSerialNum)
		{
			IAbsOrient->EraseRelativePtIndex(i);							//�����Ӧ��index

			int childNum = mEditGroup->getNumChildren();
			osg::ref_ptr<osg::Node> node = mEditGroup->getChild(i);
			mEditGroup->removeChild(node);
		}
	}
}

void COsgAbsOrientEvent::ReSetCtrlPtCheckStatus(int ptNum, bool isCheckPt)
{
	IAbsOrient->SetControlPtStatus(ptNum, isCheckPt);							//�����Ӧ��index
}

