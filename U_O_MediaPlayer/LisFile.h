#ifndef __AFXWIN_H__
#include "stdafx.h"
#endif

struct List
{
	int ListNumber;
	int Length;
	CString FileName;
	CString FilePath;
};

class LisFile : public CStdioFile
{
	private:
	int Poi;
	int ListNumber;
	int Length[256];
	CString FileName[256];
	CString FilePath[256];

	public:
	void Init()
	{
		ListNumber=0;
		for(int i=0;i<256;i++)
		{
			Length[i]=0;
			FileName[i]="";
			FilePath[i]="";
		}
		return;
	}

	private:
	List Solve(CStringA String)
	{
		List list;
		CStringA tmp;
		String.Delete(0,String.Find("r",0)+1);
		tmp=String;
		tmp.Delete(tmp.Find("@",0)-1,tmp.GetLength());
		list.ListNumber=atoi(tmp);
		String.Delete(0,String.Find(":",0)+2);
		tmp=String;
		tmp.Delete(tmp.Find("$",0)-1,tmp.GetLength());
		list.FileName=tmp;
		String.Delete(0,String.Find("h:",0)+3);
		tmp=String;
		tmp.Delete(tmp.Find("&",0)-1,tmp.GetLength());
		list.Length=atoi(tmp);
		String.Delete(0,String.Find("h:",0)+3);
		tmp=String;
		tmp.Delete(tmp.Find(";",0)-1,tmp.GetLength());
		list.FilePath=tmp;
		return list;
	}

	public:
	int ReadlisFile(CString Path)
	{
		CStdioFile file;
		CString cache;
		List list;
		Init();
		if(!file.Open(Path,typeText|modeCreate|modeNoTruncate|modeReadWrite|shareExclusive))
		{
			return -1;
		}
		else
		{
			file.ReadString(cache);
			file.ReadString(cache);
			cache.Delete(0,cache.Find(L":",0)+1);
			cache.Delete(cache.Find(L"]",0)-1,cache.GetLength());
			ListNumber=_wtoi(cache);
			for(int i=1;i<=ListNumber;i++)
			{
				file.ReadString(cache);
				CStringA tmp;
				tmp = cache;
				list=Solve(tmp);
				if(list.ListNumber==i)
				{
					Length[i]=list.Length;
					FileName[i]=list.FileName;
					FilePath[i]=list.FilePath;
				}
				else
				{
					file.Close();
					return -2;
				}
			}
		}
		file.Close();
		return 0;
	}

	void WritelisFile(CString Path)
	{
		CString tmp;
		CStdioFile file;
		if(!file.Open(Path,typeText|modeCreate|modeNoTruncate|modeReadWrite|shareExclusive))
		{
			return;
		}
		file.WriteString(_T("# This file is a playlist file of U.O.Media Player, and you have no right to change it unless you are Mr. Unknown Object yourself. #"));
		tmp.Format(L"[ List Number : %d ]",ListNumber);
		for(int i=0;i<ListNumber;i++)
		{
			tmp.Format(L"List Number %d @ Name: %s $ Length: %d & Path: %s ;",i,FileName[i],Length[i],FilePath[i]);
		}
		file.Close();
		return;
	}

	bool GetFirstItem(List *list)
	{
		const CString EmptyString = _T("");
		if ((FileName[1] == EmptyString) || (FilePath[1] == EmptyString) || (Length[1] == 0))
		{
			return false;
		}
		Poi = 1;
		List tmp;
		tmp.FileName = FileName[1];
		tmp.FilePath = FilePath[1];
		tmp.Length = Length[1];
		tmp.ListNumber = 1;
		*list = tmp;
		return true;
	}

	bool GetNextItem(List *list)
	{
		const CString EmptyString = _T("");
		Poi++;
		if ((FileName[Poi] == EmptyString) || (FilePath[Poi] == EmptyString) || (Length[Poi] == 0))
		{
			return false;
		}
		List tmp;
		tmp.FileName = FileName[Poi];
		tmp.FilePath = FilePath[Poi];
		tmp.Length = Length[Poi];
		tmp.ListNumber = Poi;
		*list = tmp;
		return true;
	}

	void AddItem(List item)
	{
		ListNumber++;
		FileName[ListNumber] = item.FileName;
		FilePath[ListNumber] = item.FilePath;
		Length[ListNumber] = item.Length;
	}

	void DeleteItem(int ObjIndex)
	{
		const CString EmptyString = _T("");
		ListNumber--;
		int i = 1;
		while (FileName[ObjIndex + i] != EmptyString)
		{
			FileName[ObjIndex + (i - 1)] = FileName[ObjIndex + i];
			FileName[ObjIndex + i] = EmptyString;
			i++;
		}
		i = 1;
		while (FilePath[ObjIndex + i] != EmptyString)
		{
			FilePath[ObjIndex + (i - 1)] = FilePath[ObjIndex + i];
			FilePath[ObjIndex + i] = EmptyString;
			i++;
		}
		i = 1;
		while (Length[ObjIndex + i] != 0)
		{
			Length[ObjIndex + (i - 1)] = Length[ObjIndex + i];
			Length[ObjIndex + i] = 0;
			i++;
		}
	}

	int GetListCount()
	{
		return ListNumber;
	}

	CString GetFilePath(int Index)
	{
		return FilePath[Index];
	}

	CString GetFileName(int Index)
	{
		return FileName[Index];
	}
};
