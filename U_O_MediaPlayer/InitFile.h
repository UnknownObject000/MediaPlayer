#ifndef __AFXWIN_H__
#include "stdafx.h"
#endif

bool SolveBool(CString string)
{
	if(string=="true")
	{
		return true;
	}
	else
	{
		return false;
	}
}

CString anti_SolveBool(bool vari)
{
	CString tmp;
	if(vari)
	{
		tmp="true";
		return tmp;
	}
	else
	{
		tmp="false";
		return tmp;
	}
}

int SolveInt(CString string)
{
	return _wtoi(string);
}

CString anti_SolveInt(int vari)
{
	CString tmp;
	tmp.Format(L"%d",vari);
	return tmp;
}

double SolveDouble(CString string,double SaveTimes)
{
	int i= _wtoi(string);
	double d=i;
	d=d/SaveTimes;
	return d;
}

CString anti_SolveDouble(double vari,double times)
{
	int i;
	double d;
	CString s;
	d=vari*times;
	i=d;
	s.Format(L"%d",i);
	return s;
}