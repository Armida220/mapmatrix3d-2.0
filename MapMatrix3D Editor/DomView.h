#pragma once
#include "publicDefined.h"
#include <string>
#include "coord.hpp"
#include <vector>

// CDomView ��ͼ

class CDomView : public CView
{
	DECLARE_DYNCREATE(CDomView)
public:
		
protected:
	CDomView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDomView();
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	DECLARE_MESSAGE_MAP()
	
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:	
	BOOL isPaint;													//�Ƿ����
	double scale;													//���ű���
	int zoomImageHeight;											//���ź��Ӱ���
	int zommImageWidth;												//���ź��Ӱ���
	long moveX;														//X����Ӱ���ƶ�
	long moveY;														//Y����Ӱ���ƶ�
	CImage m_Image;													//Ӱ���ͼ
	OperatingState ops;												//������ʶ
	long lastMouseX;												//�ϴε�x����Ӱ���ƶ�
	long lastMouseY;												//�ϴε�y����Ӱ���ƶ�
	CString strFileName;											//��ȡӰ��·���ļ���
	std::vector<CoordDouble2D> vecImgPoint;							//�̵�Ӱ������
	double xResolution;												//x����ֱ���
	double yResolution;												//y����ֱ���
	double xStart;													//x����ʼ����
	double yStart;													//y����ʼ����
	bool isMoveWindow;												//�Ƿ��ƶ�����
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnOpenImage();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};


