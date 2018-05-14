#pragma once

#ifndef DLL_API
#define DLL_API __declspec(dllexport)
#endif

DLL_API typedef void (*pNotifyMsgFunc) (char *num);

DLL_API pNotifyMsgFunc DllNotifyFun(pNotifyMsgFunc pFun); //���嵼�����������������е��ã��ѻص�������ַ���ݵ�DLL 

DLL_API typedef int (*pGetSelIndexFunc) ();

DLL_API pGetSelIndexFunc DllGetSelModelIndexFun(pGetSelIndexFunc pFun); //���嵼�����������������е��ã��ѻص�������ַ���ݵ�DLL 

DLL_API pGetSelIndexFunc DllGetSelAbsDlgRowFun(pGetSelIndexFunc pFun);	//���嵼�����������������е��ã��ѻص�������ַ���ݵ�DLL 

DLL_API typedef bool (*pChangeStatus) ();

DLL_API pChangeStatus DllChangeStatusFun(pChangeStatus pFun);			//���嵼�����������������е��ã��ѻص�������ַ���ݵ�DLL 		

DLL_API typedef void (*pObtainRelativePoint) (int, double, double, double, bool);

DLL_API pObtainRelativePoint DllOtainRelativePt(pObtainRelativePoint pFun);//���嵼�����������������е��ã��ѻص�������ַ���ݵ�DLL 