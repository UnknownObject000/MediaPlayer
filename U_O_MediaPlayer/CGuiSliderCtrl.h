#pragma once
#include <afxcmn.h>

#define SlIDER_BK_COLOR RGB(255,255,255)
#define SLIDER_LEFT_COLOR RGB(148, 40, 255)
#define SLIDER_THUMB_COLOR RGB(65,105,225)
#define DIALOG_BKCOLOR RGB(240,240,240)
class CGuiSliderCtrl : public CSliderCtrl
{
public:
	CGuiSliderCtrl();
	~CGuiSliderCtrl();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void CustDraw(CDC *pDc);
};

