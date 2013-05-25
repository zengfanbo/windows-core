// DistClean.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Unit_GDef.h"
#include "Unit_ScanFile.h"
#include "Unit_Console.h"
bool fun_AskUserScan(void) ;

DWORD g_dword_FileCount ;
DWORD g_dword_TempFileCount ;
DWORD g_dword_DirectoryCount ;
DWORD g_dword_CurseCount = 0;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL,"chs") ;
	fun_Console_ClearAll() ;
	fun_Console_HideCursor() ;

	g_dword_FileCount = 0 ;
	g_dword_TempFileCount = 0 ;
	g_dword_DirectoryCount = 0 ;

	if (fun_AskUserScan() == false)
		return 0;
	wprintf_s(L"正在对C盘扫描，请耐心等待..\r\n") ;
	fun_EnumDirectory_listTempFile(L"C:\\Users\\",STR_SAVETEMPFILEINFO_FILENAME,
									ROW_JUNKINFO) ;

	return 0;
}



bool  fun_AskUserScan()
{
	wchar_t wchar_key ;

	do 
	{
		wprintf_s(L"\r\n是否扫描windows系统(按下y键继续或者按下q键退出\r\n") ;
		wscanf_s(L" %lc",&wchar_key) ;
		getwchar() ;
	} while ((wchar_key != L'y') && 
				(wchar_key != L'n'));

	if (wchar_key == L'y')
		return true ;
	else
		return false ;
}