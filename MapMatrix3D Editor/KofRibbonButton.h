#pragma once

// CKofRibbonButton ����Ŀ��

class CKofRibbonButton : public CMFCRibbonButton
{
public:
	friend class CKofRibbonPanel;
	friend class CKofRibbonTab;

protected:
	CSize DrawBottomText(CDC* pDC, BOOL bCalcOnly);
	void OverrideOnDraw(CDC* pDC);
};


