#include "stdafx.h"
#include "CGuiSliderCtrl.h"


CGuiSliderCtrl::CGuiSliderCtrl()
{
}


CGuiSliderCtrl::~CGuiSliderCtrl()
{
}
BEGIN_MESSAGE_MAP(CGuiSliderCtrl, CSliderCtrl)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void CGuiSliderCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CSliderCtrl::OnPaint()
	CSliderCtrl::OnPaint();
	CDC *pDc = GetDC();
	CustDraw(pDc);
	ReleaseDC(pDc);
}


void CGuiSliderCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CSliderCtrl::OnLButtonDown(nFlags, point);
	CRect   rectClient, rectChannel;
	GetClientRect(rectClient);
	GetChannelRect(rectChannel);
	int nMax = 0;
	int nMin = 0;
	GetRange(nMin, nMax);
	int nPos = (nMax - nMin)*(point.x - rectClient.left - rectChannel.left) / (rectChannel.right - rectChannel.left);
	SetPos(nPos);
}

void CGuiSliderCtrl::CustDraw(CDC * pDc)
{
	COLORREF colorLeft(SLIDER_LEFT_COLOR);
	COLORREF colorChannel(SlIDER_BK_COLOR);
	CPen penChannel(PS_DASHDOTDOT, 2, colorChannel);
	CBrush brushChannel;
	brushChannel.CreateSolidBrush(colorChannel);
	COLORREF colorThumb(SLIDER_THUMB_COLOR);
	CPen penThumb(PS_DASHDOTDOT, 2, colorThumb);
	CBrush brushThumb;
	brushThumb.CreateSolidBrush(colorThumb);
	CRect clientRect;
	GetClientRect(clientRect);
	CRect channelRect;
	GetChannelRect(&channelRect);
	//clientRect.bottom /= 2;
	pDc->SetBkMode(TRANSPARENT);
	pDc->FillSolidRect(clientRect, DIALOG_BKCOLOR);
	clientRect.left = channelRect.left;
	clientRect.right = channelRect.right;
	pDc->FillSolidRect(clientRect, colorChannel);
	pDc->Draw3dRect(clientRect, colorChannel, colorChannel);
	CRect thumbRect;
	GetThumbRect(thumbRect);
	thumbRect.bottom *= 2;
	CRect leftRect;
	leftRect.left = clientRect.left;
	leftRect.top = clientRect.top;
	leftRect.bottom = clientRect.bottom;
	leftRect.right = thumbRect.left;
	pDc->SelectObject(&brushThumb);
	pDc->SelectObject(&penThumb);
	pDc->FillSolidRect(leftRect, colorLeft);
	pDc->Draw3dRect(leftRect, colorLeft, colorLeft);
	pDc->Ellipse(thumbRect);
}
