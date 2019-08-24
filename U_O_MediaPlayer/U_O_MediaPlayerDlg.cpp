
// U_O_MediaPlayerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "U_O_MediaPlayer.h"
#include "U_O_MediaPlayerDlg.h"
#include "afxdialogex.h"
#include "LisFile.h"
#include "InitFile.h"
#include <iostream>
#include <fstream>
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef Gets
#define Get_AppPoint CUOMediaPlayerApp *app = (CUOMediaPlayerApp *)AfxGetApp();
#define Get_PlayState long ps = Player.get_playState();
#endif

#define PLAYSTATE_PLAY 3
#define PLAYSTATE_PAUSE 2
#define PLAYSTATE_STOP 1
#define PLAYSTATE_LOADING 6
#define PLAYSTATE_LINKING 9
#define PLAYSTATE_READY 10
#define string std::string
#define fstream std::fstream
#define _CRT_SECURE_NO_WARNINGS

const CString EmptyString = _T("");
bool IsOpenFile = false;
CString MediaLength = _T("00:00");
int line = 0;
int ChoosenLine;
LisFile lis;

bool IsFileExist(string FilePath);
string GetProgramDir();


// CUOMediaPlayerDlg 对话框



CUOMediaPlayerDlg::CUOMediaPlayerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_U_O_MEDIAPLAYER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUOMediaPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDA_PLAYER, Player);
	DDX_Control(pDX, IDP_VOICE, Voice);
	DDX_Control(pDX, IDP_PLAY, PlayerBar);
	DDX_Control(pDX, IDC_LIST1, PL);
}

BEGIN_MESSAGE_MAP(CUOMediaPlayerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDB_PLAY, &CUOMediaPlayerDlg::OnBnClickedPlay)
	ON_BN_CLICKED(IDB_PAUSE, &CUOMediaPlayerDlg::OnBnClickedPause)
	ON_BN_CLICKED(IDB_STOP, &CUOMediaPlayerDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDB_FASTGO, &CUOMediaPlayerDlg::OnBnClickedFastgo)
	ON_BN_CLICKED(IDB_FASTBACK, &CUOMediaPlayerDlg::OnBnClickedFastback)
	ON_BN_CLICKED(IDB_PLAYSPEEDMINUS, &CUOMediaPlayerDlg::OnBnClickedPlayspeedminus)
	ON_BN_CLICKED(IDB_VOICEADD, &CUOMediaPlayerDlg::OnBnClickedVoiceadd)
	ON_BN_CLICKED(IDB_PLAYSPEEDADD, &CUOMediaPlayerDlg::OnBnClickedPlayspeedadd)
	ON_BN_CLICKED(IDB_VOICEMINUS, &CUOMediaPlayerDlg::OnBnClickedVoiceminus)
	ON_BN_CLICKED(IDB_MUTE, &CUOMediaPlayerDlg::OnBnClickedMute)
	ON_BN_CLICKED(IDB_FULLSCGREEN, &CUOMediaPlayerDlg::OnBnClickedFullscgreen)
	ON_BN_CLICKED(IDB_SET, &CUOMediaPlayerDlg::OnBnClickedSet)
	ON_BN_CLICKED(IDB_OPEN, &CUOMediaPlayerDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDB_SHUTDOWN, &CUOMediaPlayerDlg::OnBnClickedShutdown)
	ON_BN_CLICKED(IDB_MINISIZE, &CUOMediaPlayerDlg::OnBnClickedMinisize)
	ON_BN_CLICKED(IDB_DELETE, &CUOMediaPlayerDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDB_ADD, &CUOMediaPlayerDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDB_CHECK, &CUOMediaPlayerDlg::OnBnClickedCheck)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDP_PLAY, &CUOMediaPlayerDlg::OnThumbposchangingIdpPlay)
	ON_WM_TIMER()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CUOMediaPlayerDlg::OnClickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CUOMediaPlayerDlg::OnDblclkList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CUOMediaPlayerDlg::OnRclickList1)
END_MESSAGE_MAP()


// CUOMediaPlayerDlg 消息处理程序

BOOL CUOMediaPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	Player.put_enableContextMenu(false);	//关闭右键菜单
	Player.put_fullScreen(false);			//设置非全屏
	Player.put_stretchToFit(true);			//开启缩放
	Player.put_uiMode(_T("none"));			//关闭播放器自带GUI
	Control = static_cast<CWMPControls3>(Player.get_controls());
	Settings = Player.get_settings();
	Settings.put_autoStart(false);			//关闭自动播放
	Settings.put_volume(50);				//设置音量:50
	Settings.put_rate(1.00);				//设置播放速度:1(正常)
	CString tmp;
	//tmp.Format(L"音量：%d", Settings.get_volume());
	//((CProgressCtrl*)GetDlgItem(IDP_VOICE))->SetRange(0,100);
	//((CProgressCtrl*)GetDlgItem(IDP_VOICE))->SetPos(50);
	//SetDlgItemText(IDS_VOICENUM, tmp);
	Voice.SetRange(0, 100);			//设置音量条范围
	Voice.SetPos(50);				//设置初始音量位置
	//配置文件初始化
	string path = GetProgramDir();
	path = path + "\\" + "Settings.init";
	if (IsFileExist(path))
	{
		CString tmp(path.c_str());
		ReadinitFile(tmp);
	}
	else
	{
		MessageBox(_T("配置文件丢失，程序将使用默认配置"), _T("警告"), MB_OK | MB_ICONWARNING);
		Get_AppPoint;
		app->Develop = false;
		app->AutoPlay = false;
		app->AutoFullScreen = false;
		app->AutoAddPlayList = true;
		app->AutoCheckPlayList = true;
		app->BackGroundColor = "";
		app->Volume = 50;
		app->PlaySpeed = 1;
		app->VolumeStep = 1;
		app->AutoKeepPlay = app->AKP_Hint;
		app->PlaySpeedStep = 0.5;
		app->FastGo_BackStep = 10;
		app->PlayListErrorOpt = app->PLEO_Hint;
		CString tmp(path.c_str());
		WriteinitFile(tmp);
	}
	//配置文件初始化完毕
	//初始化播放列表
	LONG lStyle;
	lStyle = GetWindowLong(PL.m_hWnd, GWL_STYLE);//获取当前窗口style 
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位 
	lStyle |= LVS_REPORT; //设置style 
	SetWindowLong(PL.m_hWnd, GWL_STYLE, lStyle);//设置style
	PL.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	PL.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 50);//插入列
	PL.InsertColumn(1, _T("文件名"), LVCFMT_LEFT, 170);//插入列
	PL.InsertColumn(2, _T("长度"), LVCFMT_LEFT, 150);//插入列
	path = GetProgramDir();
	path = path + "\\" + "PlayList.lis";
	if (IsFileExist(path))
	{
		CString tmp(path.c_str());
		CString cache;
		List list;
		lis.ReadlisFile(tmp);
		if (lis.GetFirstItem(&list))
		{
			cache.Format(_T("%d"), list.ListNumber);
			line = PL.InsertItem(0, cache);
			PL.SetItemText(line, 1, list.FileName);
			PL.SetItemText(line, 2, MakeMediaLength(list.Length));
			while (lis.GetNextItem(&list))
			{
				cache.Format(_T("%d"), list.ListNumber);
				line = PL.InsertItem(0, cache);
				PL.SetItemText(line, 1, list.FileName);
				PL.SetItemText(line, 2, MakeMediaLength(list.Length));
			}
			for (int i = 0; i < list.ListNumber; i++)
			{
				ListItemTop(i);
			}
		}
		else
		{
			MessageBox(_T("播放列表文件损坏，程序无法加载"), _T("错误"), MB_OK | MB_ICONERROR);
			line = PL.InsertItem(0, _T(""));
			PL.SetItemText(line, 1, _T("播放列表为空！"));
			PL.SetItemText(line, 2, _T(""));
		}
	}
	else
	{
		line = PL.InsertItem(0, _T(""));
		PL.SetItemText(line, 1, _T("播放列表为空！"));
		PL.SetItemText(line, 2, _T(""));
	}
	//播放列表初始化完毕
	tmp.Format(L"播放速度：%.1lfx", Settings.get_rate());	//准备播放速度字符串
	SetDlgItemText(IDS_PLAYSPEED, tmp);						//初始化播放速度显示
	SetTimer(2, 100, NULL);		//设置播放速度实时更新定时器
	SetTimer(3, 100, NULL);		//设置播放进度实时更新定时器
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUOMediaPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUOMediaPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

string GetProgramDir()
{
	wchar_t exeFullPath[MAX_PATH]; // Full path   
	string strPath = "";
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	char CharString[MAX_PATH];
	size_t convertedChars = 0;
	wcstombs_s(&convertedChars, CharString, MAX_PATH, exeFullPath, _TRUNCATE);
	strPath = (string)CharString;    // Get full path of the file   
	int pos = strPath.find_last_of('\\', strPath.length());
	return strPath.substr(0, pos);  // Return the directory without the file name   
}

void CUOMediaPlayerDlg::Fast_Move(bool IsForward)
{
	Get_AppPoint;
	if (IsForward)
	{
		if ((Control.get_currentPosition() + app->FastGo_BackStep) >= Media.get_duration())
		{
			Control.put_currentPosition(Media.get_duration());
		}
		else
		{
			Control.put_currentPosition(Control.get_currentPosition() + app->FastGo_BackStep);
		}
	}
	else
	{
		if ((Control.get_currentPosition() - app->FastGo_BackStep) <= 0.0)
		{
			Control.put_currentPosition(0.0);
		}
		else
		{
			Control.put_currentPosition(Control.get_currentPosition() - app->FastGo_BackStep);
		}
	}
}

void CUOMediaPlayerDlg::ReadinitFile(CString Path)
{
	CString tmp;
	Get_AppPoint;
	CStdioFile file;
	if (!file.Open(Path, 0x04000 | 0x01000 | 0x02000 | 0x00002 | 0x00010))
	{
		return;
	}
	file.ReadString(tmp);
	app->Develop = SolveBool(tmp);
	file.ReadString(tmp);
	app->AutoPlay = SolveBool(tmp);
	file.ReadString(tmp);
	app->AutoFullScreen = SolveBool(tmp);
	file.ReadString(tmp);
	app->AutoAddPlayList = SolveBool(tmp);
	file.ReadString(tmp);
	app->AutoCheckPlayList = SolveBool(tmp);
	file.ReadString(tmp);
	app->BackGroundColor = tmp;
	file.ReadString(tmp);
	app->Volume = SolveInt(tmp);
	file.ReadString(tmp);
	app->PlaySpeed = SolveDouble(tmp, 100.00);
	file.ReadString(tmp);
	app->VolumeStep = SolveInt(tmp);
	file.ReadString(tmp);
	app->AutoKeepPlay = SolveInt(tmp);
	file.ReadString(tmp);
	app->PlaySpeedStep = SolveDouble(tmp, 100.00);
	file.ReadString(tmp);
	app->FastGo_BackStep = SolveInt(tmp);
	file.ReadString(tmp);
	app->PlayListErrorOpt = SolveInt(tmp);
	file.Close();
	return;
}

void CUOMediaPlayerDlg::WriteinitFile(CString Path)
{
	CString tmp;
	Get_AppPoint;
	CStdioFile file;
	if (!file.Open(Path, 0x04000 | 0x01000 | 0x02000 | 0x00002 | 0x00010))
	{
		return;
	}
	file.WriteString(anti_SolveBool(app->Develop));
	file.WriteString(_T("\n"));
	file.WriteString(anti_SolveBool(app->AutoPlay));
	file.WriteString(_T("\n"));
	file.WriteString(anti_SolveBool(app->AutoFullScreen));
	file.WriteString(_T("\n"));
	file.WriteString(anti_SolveBool(app->AutoAddPlayList));
	file.WriteString(_T("\n"));
	file.WriteString(anti_SolveBool(app->AutoCheckPlayList));
	file.WriteString(_T("\n"));
	file.WriteString(app->BackGroundColor);
	file.WriteString(_T("\n"));
	file.WriteString(anti_SolveInt(app->Volume));
	file.WriteString(_T("\n"));
	file.WriteString(anti_SolveDouble(app->PlaySpeed, 100));
	file.WriteString(_T("\n"));
	file.WriteString(anti_SolveInt(app->VolumeStep));
	file.WriteString(_T("\n"));
	file.WriteString(anti_SolveInt(app->AutoKeepPlay));
	file.WriteString(_T("\n"));
	file.WriteString(anti_SolveDouble(app->PlaySpeedStep, 100));
	file.WriteString(_T("\n"));
	file.WriteString(anti_SolveInt(app->FastGo_BackStep));
	file.WriteString(_T("\n"));
	file.WriteString(anti_SolveInt(app->PlayListErrorOpt));
	file.Close();
	return;
}

void CUOMediaPlayerDlg::ListItemTop(int ItemToMove)
{
	CString i1, i2, i3;
	i1 = PL.GetItemText(ItemToMove, 0);
	i2 = PL.GetItemText(ItemToMove, 1);
	i3 = PL.GetItemText(ItemToMove, 2);
	PL.DeleteItem(ItemToMove);
	int line = PL.InsertItem(0, i1);
	PL.SetItemText(line, 1, i2);
	PL.SetItemText(line, 2, i3);
	return;
}

void CUOMediaPlayerDlg::ListItemDown(int ItemToMove)
{

}

void CUOMediaPlayerDlg::UpdatePlayList()
{
	List list;
	CString cache;
	PL.DeleteAllItems();
	if (lis.GetFirstItem(&list))
	{
		cache.Format(_T("%d"), list.ListNumber);
		line = PL.InsertItem(0, cache);
		PL.SetItemText(line, 1, list.FileName);
		PL.SetItemText(line, 2, MakeMediaLength(list.Length));
		while (lis.GetNextItem(&list))
		{
			cache.Format(_T("%d"), list.ListNumber);
			line = PL.InsertItem(0, cache);
			PL.SetItemText(line, 1, list.FileName);
			PL.SetItemText(line, 2, MakeMediaLength(list.Length));
		}
		for (int i = 0; i < list.ListNumber; i++)
		{
			ListItemTop(i);
		}
	}
	return;
}

bool IsFileExist(string FilePath)
{
	fstream _file;
	_file.open(FilePath, std::ios::in);
	if (!_file)
	{
		return false;
	}
	else
	{
		_file.close();
		return true;
	}
}

CString CUOMediaPlayerDlg::MakeMediaLength(int FileLength)
{
	CString ret;
	if (FileLength < 60)
	{
		ret.Format(_T("%d秒"), FileLength);
	}
	else if ((FileLength >= 60) && (FileLength < 3600))
	{
		int min = FileLength / 60;
		int sec = FileLength % 60;
		ret.Format(_T("%d分钟%d秒"), min, sec);
	}
	else
	{
		int hou = FileLength / 3600;
		int min = (FileLength % 3600) / 60;
		int sec = (FileLength % 3600) % 60;
		ret.Format(_T("%d小时%d分钟%d秒"), hou, min, sec);
	}
	return ret;
}

int CUOMediaPlayerDlg::MakeFileLength(CString MediaLength)
{
	CString tmp;
	int ret;
	if (MediaLength.Find(_T("小时"), 0) != -1)
	{
		tmp = MediaLength;
		tmp.Delete(tmp.Find(_T("小时"), 0) - 1, tmp.GetLength());
		ret = _wtoi(tmp);
		MediaLength.Delete(0, MediaLength.Find(_T("分钟"), 0) - 1);
		tmp = MediaLength;
		tmp.Delete(tmp.Find(_T("分钟"), 0) - 1, tmp.GetLength());
		ret = ret + _wtoi(tmp);
		MediaLength.Delete(0, MediaLength.Find(_T("秒"), 0));
		tmp = MediaLength;
		tmp.Delete(tmp.Find(_T("秒"), 0), tmp.GetLength());
		ret = ret + _wtoi(tmp);
	}
	else if (MediaLength.Find(_T("分钟"), 0) != -1)
	{
		tmp = MediaLength;
		tmp.Delete(tmp.Find(_T("分钟"), 0) - 1, tmp.GetLength());
		ret = _wtoi(tmp);
		MediaLength.Delete(0, MediaLength.Find(_T("秒"), 0));
		tmp = MediaLength;
		tmp.Delete(tmp.Find(_T("秒"), 0), tmp.GetLength());
		ret = ret + _wtoi(tmp);
	}
	else
	{
		tmp = MediaLength;
		tmp.Delete(tmp.Find(_T("秒"), 0), tmp.GetLength());
		ret = _wtoi(tmp);
	}
	return ret;
}

void CUOMediaPlayerDlg::OnBnClickedPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	Get_PlayState;
	Get_AppPoint;
	if (!IsOpenFile)
	{
		MessageBox(_T("无媒体，无法播放"), _T("无效操作"), MB_OK | MB_ICONERROR);
	}
	else if ((ps == PLAYSTATE_STOP) || (ps == PLAYSTATE_READY))
	{
		Control.play();
		//Media = static_cast<CWMPMedia3>(Player.get_currentMedia());
		SetTimer(1, 100, NULL);
		if (app->AutoFullScreen)
		{
			Player.put_fullScreen(true);
		}
	}
	else if (ps == PLAYSTATE_PAUSE)
	{
		Control.play();
	}
	else if (ps == PLAYSTATE_PLAY)
	{
		MessageBox(_T("正在播放!"), _T("重复操作"), MB_OK | MB_ICONINFORMATION);
	}
	else if (ps == PLAYSTATE_LOADING)
	{
		MessageBox(_T("正在加载，无法播放"), _T("无效操作"), MB_OK | MB_ICONERROR);
	}
	else if (ps == PLAYSTATE_LINKING)
	{
		MessageBox(_T("正在连接媒体，无法播放"), _T("无效操作"), MB_OK | MB_ICONERROR);
	}
	else
	{
		MessageBox(_T("播放器出现问题，无法播放。请重试或点击\"发现BUG\"按钮反馈BUG"), _T("程序错误"), MB_OK | MB_ICONERROR);
	}
}


void CUOMediaPlayerDlg::OnBnClickedPause()
{
	// TODO: 在此添加控件通知处理程序代码
	Get_PlayState;
	if (ps == PLAYSTATE_PLAY)
	{
		Control.pause();
	}
	else
	{
		MessageBox(_T("未播放，无法暂停"), _T("无效操作"), MB_OK | MB_ICONERROR);
	}
}


void CUOMediaPlayerDlg::OnBnClickedStop()
{
	// TODO: 在此添加控件通知处理程序代码
	Get_PlayState;
	if ((ps == PLAYSTATE_PLAY) || (ps == PLAYSTATE_PAUSE))
	{
		KillTimer(1);
		((CSliderCtrl*)GetDlgItem(IDP_PLAY))->SetPos(0);
		Control.stop();
	}
	else
	{
		MessageBox(_T("未播放，无法停止"), _T("无效操作"), MB_OK | MB_ICONERROR);
	}
}


void CUOMediaPlayerDlg::OnBnClickedFastgo()
{
	// TODO: 在此添加控件通知处理程序代码
	Fast_Move(true);
}


void CUOMediaPlayerDlg::OnBnClickedFastback()
{
	// TODO: 在此添加控件通知处理程序代码
	Fast_Move(false);
}


void CUOMediaPlayerDlg::OnBnClickedPlayspeedminus()
{
	// TODO: 在此添加控件通知处理程序代码
	Get_AppPoint;
	if ((Settings.get_rate() - (app->PlaySpeedStep)) <= 0)
	{
		MessageBox(_T("当前已是最低速率！"), _T("无效操作"), MB_OK | MB_ICONERROR);
	}
	else
	{
		CString tmp;
		tmp.Format(L"播放速度：%.1lfx", Settings.get_rate() - (app->PlaySpeedStep));
		SetDlgItemText(IDS_PLAYSPEED, tmp);
		Settings.put_rate(Settings.get_rate() - (app->PlaySpeedStep));
	}
}


void CUOMediaPlayerDlg::OnBnClickedVoiceadd()
{
	// TODO: 在此添加控件通知处理程序代码
	Get_AppPoint;
	if ((Settings.get_volume() + app->VolumeStep) > 100)
	{
		MessageBox(_T("音量最大值为100！"), _T("无效操作"), MB_OK | MB_ICONERROR);
	}
	else
	{
		Settings.put_volume(Settings.get_volume() + app->VolumeStep);
		//CString tmp;
		//tmp.Format(L"音量：%d", Settings.get_volume());
		Voice.SetPos(Settings.get_volume());
		//SetDlgItemText(IDS_VOICENUM, tmp);

	}
}


void CUOMediaPlayerDlg::OnBnClickedPlayspeedadd()
{
	// TODO: 在此添加控件通知处理程序代码
	Get_AppPoint;
	CString tmp;
	tmp.Format(L"播放速度：%.1lfx", Settings.get_rate() + (app->PlaySpeedStep));
	SetDlgItemText(IDS_PLAYSPEED, tmp);
	Settings.put_rate(Settings.get_rate() + (app->PlaySpeedStep));
}


void CUOMediaPlayerDlg::OnBnClickedVoiceminus()
{
	// TODO: 在此添加控件通知处理程序代码
	Get_AppPoint;
	if ((Settings.get_volume() - app->VolumeStep) < 0)
	{
		MessageBox(_T("音量最小值为0！"), _T("无效操作"), MB_OK | MB_ICONERROR);
	}
	else
	{
		Settings.put_volume(Settings.get_volume() - app->VolumeStep);
		//CString tmp;
		//tmp.Format(L"音量：%d", Settings.get_volume());
		Voice.SetPos(Settings.get_volume());
		//SetDlgItemText(IDS_VOICENUM, tmp);
	}
}


void CUOMediaPlayerDlg::OnBnClickedMute()
{
	// TODO: 在此添加控件通知处理程序代码
	if (Settings.get_mute())
	{
		SetDlgItemText(IDB_MUTE, _T("静音"));
		Settings.put_mute(false);
		Voice.SetPos(Settings.get_volume());
	}
	else
	{
		SetDlgItemText(IDB_MUTE, _T("关闭静音"));
		Settings.put_mute(true);
		Voice.SetPos(0);
	}
}


void CUOMediaPlayerDlg::OnBnClickedFullscgreen()
{
	// TODO: 在此添加控件通知处理程序代码
	Player.put_fullScreen(true);
}


void CUOMediaPlayerDlg::OnBnClickedSet()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("资源管理器未连接，设置菜单无法运行"),_T("错误"),MB_OK | MB_ICONERROR);
}


void CUOMediaPlayerDlg::OnBnClickedOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog FileDialog(true, NULL, NULL, OFN_HIDEREADONLY, _T(
		"所有支持的媒体文件(*.mp3;*.mp4;*.wma;*.dat;*.wav;*.avi;*.mov;*.mmm;*.mid;*.rmi;*.mpeg)|*.mp3;*.mp4;*.wma;*.dat;*.wav;*.avi;*.mov;*.mmm;*.mid;*.rmi;*.mpeg|"
		"Wma文件(*.wma)|*.wma|"
		"Video文件(*.dat)|*.dat|"
		"Wave文件e(*.wav)|*.wav|"
		"AVI文件(*.avi)|*.avi|"
		"Movie文件(*.mov)|*.mov|"
		"Media文件(*.mmm)|*.mmm|"
		"Mid文件(*.mid;*.rmi)|*.mid;*.rmi|"
		"MPEG文件(*.mpeg)|*.mpeg|"
		"MP4文件(*.mp4)|*.mp4|"
		"Mp3文件(*.mp3)|*.mp3|"), this);
	if (FileDialog.DoModal() == IDOK)
	{
		Player.put_URL(FileDialog.GetPathName());
		Media = static_cast<CWMPMedia3>(Player.newMedia(FileDialog.GetPathName()));
		((CSliderCtrl*)GetDlgItem(IDP_PLAY))->SetRange(0, Media.get_duration());
		MediaLength = Media.get_durationString();
		((CSliderCtrl*)GetDlgItem(IDP_PLAY))->SetPos(0);
		IsOpenFile = true;
	}
	else return;
}


void CUOMediaPlayerDlg::OnBnClickedShutdown()
{
	// TODO: 在此添加控件通知处理程序代码
	if (MessageBox(_T("确定要关闭此播放器吗？"), _T("提示"), MB_YESNO) == IDYES)
	{
		KillTimer(1);
		exit(0);
	}
}


void CUOMediaPlayerDlg::OnBnClickedMinisize()
{
	// TODO: 在此添加控件通知处理程序代码
	WINDOWPLACEMENT lwndpl;
	WINDOWPLACEMENT * lpwndpl;
	lpwndpl = &lwndpl;
	GetWindowPlacement(lpwndpl);
	lpwndpl->showCmd = SW_SHOWMINIMIZED;
	SetWindowPlacement(lpwndpl);
}


void CUOMediaPlayerDlg::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	PL.DeleteItem(ChoosenLine);
	lis.DeleteItem(ChoosenLine);
	UpdatePlayList();
}


void CUOMediaPlayerDlg::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog FileDialog(true, NULL, NULL, OFN_HIDEREADONLY, _T(
		"所有支持的媒体文件(*.mp3;*.mp4;*.wma;*.dat;*.wav;*.avi;*.mov;*.mmm;*.mid;*.rmi;*.mpeg)|*.mp3;*.mp4;*.wma;*.dat;*.wav;*.avi;*.mov;*.mmm;*.mid;*.rmi;*.mpeg|"
		"Wma文件(*.wma)|*.wma|"
		"Video文件(*.dat)|*.dat|"
		"Wave文件e(*.wav)|*.wav|"
		"AVI文件(*.avi)|*.avi|"
		"Movie文件(*.mov)|*.mov|"
		"Media文件(*.mmm)|*.mmm|"
		"Mid文件(*.mid;*.rmi)|*.mid;*.rmi|"
		"MPEG文件(*.mpeg)|*.mpeg|"
		"MP4文件(*.mp4)|*.mp4|"
		"Mp3文件(*.mp3)|*.mp3|"), this);
	if (FileDialog.DoModal() == IDOK)
	{
		CString f1, f2;
		int f3;
		f1 = FileDialog.GetFileName();
		CWMPMedia3 tmp;
		tmp = static_cast<CWMPMedia3>(Player.newMedia(FileDialog.GetPathName()));
		f3 = tmp.get_duration();
		f2.Format(_T("%d"), PL.GetItemCount() + 1);
		//int line = PL.InsertItem(PL.GetItemCount() + 1, f2);
		//PL.SetItemText(line, 1, f1);
		//PL.SetItemText(line, 2, MakeMediaLength(f3));
		List list;
		list.FileName = f1;
		list.FilePath = FileDialog.GetPathName();
		list.Length = f3;
		lis.AddItem(list);
		UpdatePlayList();
	}
}


void CUOMediaPlayerDlg::OnBnClickedCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	int success = 0;
	CStringA tmp;
	CString cache;
	for (int i = 1; i <= lis.GetListCount(); i++)
	{
		tmp = lis.GetFilePath(i);
		if (!IsFileExist(tmp.GetBuffer()))
		{
			success++;
			cache.Format(_T("文件“%s”不存在，详细信息：\n文件名：%s\n原地址：%s\n操作：\n按“是”删除该文件并继续检查\n按“否”跳过该文件并继续检查\n按“取消”停止检查"), lis.GetFileName(i), lis.GetFileName(i), lis.GetFilePath(i));
			int ret = MessageBox(cache, _T("播放列表检查报告"), MB_YESNOCANCEL | MB_ICONINFORMATION);
			if (ret == IDYES)
			{
				lis.DeleteItem(i);
				UpdatePlayList();
				continue;
			}
			else if (ret == IDCANCEL)
			{
				break;
			}
			else
			{
				continue;
			}
		}
	}
	if (success == 0)
	{
		MessageBox(_T("播放列表检查完毕，未发现失效项"), _T("播放列表检查报告"), MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		cache.Format(_T("播放列表检查完毕，共发现%d个失效项"), success);
		MessageBox(cache, _T("播放列表检查报告"), MB_OK | MB_ICONINFORMATION);
	}
}


void CUOMediaPlayerDlg::OnThumbposchangingIdpPlay(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
	int p = PlayerBar.GetPos();
	Control.put_currentPosition((double)p);
	SetTimer(1, 100, NULL);
	*pResult = 0;
}


void CUOMediaPlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Get_AppPoint;
	switch (nIDEvent)
	{
	case 1:
	{
		double tmp = Control.get_currentPosition();
		PlayerBar.SetPos((int)tmp);
		break;
	}
	case 2:
	{
		CString tmp;
		tmp.Format(L"播放速度：%.1lfx", Settings.get_rate());
		SetDlgItemText(IDS_PLAYSPEED, tmp);
		break;
	}
	case 3:
	{
		CString tmp;
		tmp.Format(L"播放进度： %s/%s", Control.get_currentPositionString(), MediaLength);
		SetDlgItemText(IDS_PLAYTIME, tmp);
	}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CUOMediaPlayerDlg::OnClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	POSITION ps;
	int nIndex;
	ps = PL.GetFirstSelectedItemPosition();
	nIndex = PL.GetNextSelectedItem(ps);//nIndex为选中的列表项Item值
	ChoosenLine = nIndex;
	*pResult = 0;
}


void CUOMediaPlayerDlg::OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	POSITION ps;
	int nIndex;
	ps = PL.GetFirstSelectedItemPosition();
	nIndex = PL.GetNextSelectedItem(ps);//nIndex为选中的列表项Item值
	Player.put_URL(lis.GetFilePath(nIndex));
	Media = static_cast<CWMPMedia3>(Player.newMedia(lis.GetFilePath(nIndex)));
	((CSliderCtrl*)GetDlgItem(IDP_PLAY))->SetRange(0, Media.get_duration());
	MediaLength = Media.get_durationString();
	((CSliderCtrl*)GetDlgItem(IDP_PLAY))->SetPos(0);
	IsOpenFile = true;
	Control.play();
	SetTimer(1, 100, NULL);
	*pResult = 0;
}


void CUOMediaPlayerDlg::OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	POSITION ps;
	int nIndex;
	ps = PL.GetFirstSelectedItemPosition();
	nIndex = PL.GetNextSelectedItem(ps);//nIndex为选中的列表项Item值
	Player.put_URL(lis.GetFilePath(nIndex));
	Media = static_cast<CWMPMedia3>(Player.newMedia(lis.GetFilePath(nIndex)));
	((CSliderCtrl*)GetDlgItem(IDP_PLAY))->SetRange(0, Media.get_duration());
	MediaLength = Media.get_durationString();
	((CSliderCtrl*)GetDlgItem(IDP_PLAY))->SetPos(0);
	IsOpenFile = true;
	Control.play();
	SetTimer(1, 100, NULL);
	*pResult = 0;
}
