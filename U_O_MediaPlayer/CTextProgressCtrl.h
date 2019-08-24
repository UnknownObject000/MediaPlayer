#pragma once
#include <afxcmn.h>
class CTextProgressCtrl : public CProgressCtrl
{
private:
	COLORREF m_prgsColor;
	COLORREF m_freeColor;
	COLORREF m_prgsTextColor;
	COLORREF m_freeTextColor;
	int m_iMin;
	int m_iMax;
	int m_iPos;
	int m_nBarWidth;
public:
	CTextProgressCtrl();
	~CTextProgressCtrl();
	int SetPos(int nPos);
	void SetRange(int nLower, int nUpper);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};