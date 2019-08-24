#include "stdafx.h"
#include "CTextProgressCtrl.h"


CTextProgressCtrl::CTextProgressCtrl()
{
}


CTextProgressCtrl::~CTextProgressCtrl()
{
}

int CTextProgressCtrl::SetPos(int nPos)
{
	if (!::IsWindow(m_hWnd))
	{
		return -1;
	}
	int nOldPos = m_iPos;
	m_iPos = nPos;
	CRect rect;
	GetClientRect(rect);
	//�����ȼ���Ҫ��ʾ�Ľ�������ȣ������ͬһ���ȶ�λ��ƴ���
	double Fraction = (double)(m_iPos - m_iMin) / ((double)(m_iMax - m_iMin));
	int nBarWidth = (int)(Fraction * rect.Width());
	if (nBarWidth != m_nBarWidth)
	{
		m_nBarWidth = nBarWidth;
		RedrawWindow();
	}
	return nOldPos;
}

void CTextProgressCtrl::SetRange(int nLower, int nUpper)
{
	m_iMax = nUpper;
	m_iMin = nLower;
	m_iPos = m_iMin;
	m_nBarWidth = 0;
}

void CTextProgressCtrl::OnPaint()
{
	//�����ж������Ƿ���Ч
	if (m_iMin >= m_iMax)
	{
		return;
	}
	m_freeColor = RGB(248, 248, 255);
	m_prgsColor = RGB(148, 0, 211);
	m_prgsTextColor = RGB(248, 248, 255);
	m_freeTextColor = RGB(148, 0, 211);
	CPaintDC dc(this); // device context for painting
	// ��Ϊ��ͼ��Ϣ���� CProgressCtrl::OnPaint()
	//��ȡ��Ч�Ľ�������λ�úʹ�С
	CRect LeftRect, RightRect, ClientRect;
	GetClientRect(ClientRect);
	LeftRect = RightRect = ClientRect;
	//������ʾ���ȵı���
	double Fraction = (double)(m_iPos - m_iMin) / ((double)(m_iMax - m_iMin));
	//���������������е���Ч����
	LeftRect.right = LeftRect.left + (int)((LeftRect.right - LeftRect.left) * Fraction);
	dc.FillSolidRect(LeftRect, m_prgsColor);
	//����ʣ�����
	RightRect.left = LeftRect.right;
	dc.FillSolidRect(RightRect, m_freeColor);
	CString str;
	str.Format(_T("������%d"), m_iPos);
	//�������ֱ�����ɫΪ͸��
	dc.SetBkMode(TRANSPARENT);
	//Ϊ���ܹ��ڽ��Ⱥ�ʣ���������ʾ��ͬ��ɫ�����壬��Ҫ�ֱ��������ߵ�������ɫ����ͼ
	CRgn rgn;
	rgn.CreateRectRgn(LeftRect.left, LeftRect.top, LeftRect.right, LeftRect.bottom);
	dc.SelectClipRgn(&rgn);
	dc.SetTextColor(m_prgsTextColor);
	dc.DrawText(str, ClientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rgn.DeleteObject();
	rgn.CreateRectRgn(RightRect.left, RightRect.top, RightRect.right, RightRect.bottom);
	dc.SelectClipRgn(&rgn);
	dc.SetTextColor(m_freeTextColor);
	dc.DrawText(str, ClientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//�����������������ֻ��ʾһ��������ɫ����ô����ֱ�ӵ���
	//dc.SetTextColor(m_freeTextColor);
	//dc.DrawText(str, ClientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}

BEGIN_MESSAGE_MAP(CTextProgressCtrl, CProgressCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()
