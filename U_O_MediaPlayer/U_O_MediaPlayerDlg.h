
// U_O_MediaPlayerDlg.h: 头文件
//

#pragma once
#include "CWMPPlayer4.h"
#include "CWMPControls3.h"
#include "CWMPMedia3.h"
#include "CWMPSettings2.h"
#include "CTextProgressCtrl.h"
#include "CGuiSliderCtrl.h"


// CUOMediaPlayerDlg 对话框
class CUOMediaPlayerDlg : public CDialogEx
{
// 构造
public:
	CUOMediaPlayerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_U_O_MEDIAPLAYER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	CString MakeMediaLength(int FileLength);
	int MakeFileLength(CString MediaLength);
	void Fast_Move(bool IsForward);
	void ReadinitFile(CString Path);
	void WriteinitFile(CString Path);
	void ListItemTop(int ItemToMove);
	void ListItemDown(int ItemToMove);
	void UpdatePlayList();
	DECLARE_MESSAGE_MAP()
public:
	CWMPPlayer4 Player;
	CWMPControls3 Control;
	CWMPMedia3 Media;
	CWMPSettings2 Settings;
	CTextProgressCtrl Voice;
	CGuiSliderCtrl PlayerBar;
	CListCtrl PL;
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedFastgo();
	afx_msg void OnBnClickedFastback();
	afx_msg void OnBnClickedPlayspeedminus();
	afx_msg void OnBnClickedVoiceadd();
	afx_msg void OnBnClickedPlayspeedadd();
	afx_msg void OnBnClickedVoiceminus();
	afx_msg void OnBnClickedMute();
	afx_msg void OnBnClickedFullscgreen();
	afx_msg void OnBnClickedSet();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedShutdown();
	afx_msg void OnBnClickedMinisize();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedCheck();
	afx_msg void OnThumbposchangingIdpPlay(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
