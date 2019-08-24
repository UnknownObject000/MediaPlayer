
// U_O_MediaPlayer.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CUOMediaPlayerApp:
// 有关此类的实现，请参阅 U_O_MediaPlayer.cpp
//

class CUOMediaPlayerApp : public CWinApp
{
public:
	CUOMediaPlayerApp();

// 重写
public:
	virtual BOOL InitInstance();
public:
	//全局常量放置处
	const int AKP_Hint = 255;
	const int AKP_Auto = 256;
	const int PLEO_Hint = 32767;
	const int PLEO_Wait = 32768;
	const int PLEO_Delete = 32769;
	//截止
	//全局变量放置处
	bool Develop;
	bool AutoPlay;
	bool AutoFullScreen;
	bool AutoAddPlayList;
	bool AutoCheckPlayList;
	CString BackGroundColor;
	int Volume;
	double PlaySpeed;
	int VolumeStep;
	int AutoKeepPlay;
	double PlaySpeedStep;
	int FastGo_BackStep;
	int PlayListErrorOpt;

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CUOMediaPlayerApp theApp;
