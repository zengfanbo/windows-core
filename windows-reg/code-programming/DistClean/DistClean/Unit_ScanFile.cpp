#include "stdafx.h"
#include "Unit_ScanFile.h"
#include "Unit_GDef.h"
#include "Unit_Console.h"

#pragma  comment(lib,"Shlwapi")

void fun_EnumDirectory_listTempFile(wchar_t * pwchar_param_RootPath,
	wchar_t * pwchar_param_SaveFile,
	short short_param_ShowCmdInfo)
{
	wchar_t pwchar_var_FilePath[MAX_PATH] ;
	wchar_t pwchar_var_FileName [MAX_PATH] ;
	wchar_t pwchar_var_TempFilePath[MAX_PATH] ;
	WIN32_FIND_DATA struct_WinFinDat ;
	HANDLE handle_File ;
	size_t size_var_ParamSize ;

	wchar_t pwchar_var_PrintBuffer[MAX_PATH] ;
	// then we copy the rootpath to the pwchar_var_FilePath
	
	if (!pwchar_param_RootPath || !pwchar_param_SaveFile)
		return ;

	if (wcslen(pwchar_param_RootPath) == 0 ||
		wcslen(pwchar_param_SaveFile) == 0 )
		return ;

	StringCchLength(pwchar_param_RootPath,MAX_PATH,&size_var_ParamSize) ;

	if (size_var_ParamSize > MAX_PATH -3)
	{
		wprintf(L"目标路径太长\r\n") ;
		return ;
	}

	StringCchCopy(pwchar_var_FilePath,MAX_PATH,pwchar_param_RootPath) ;
	
	// add the \ to the pwchar_var_FilePath
	if (pwchar_param_RootPath[wcslen(pwchar_param_RootPath) - 1] != L'\\' )
	{
		StringCchCat(pwchar_var_FilePath,MAX_PATH,L"\\*.*") ;
	}
	else
	{
		StringCchCat(pwchar_var_FilePath,MAX_PATH,L"*.*") ;
	}


	//  search the find file
	handle_File = FindFirstFile(pwchar_var_FilePath,&struct_WinFinDat) ;

	if (handle_File == INVALID_HANDLE_VALUE)
	{
		wprintf(L"系统错误代码是:%u\r\n",GetLastError()) ;
		return ;
	}

	do 
	{
		if (struct_WinFinDat.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (!wcscmp(struct_WinFinDat.cFileName,L".") ||
				!wcscmp(struct_WinFinDat.cFileName,L".."))
			{
				if (pwchar_var_FilePath[wcslen(pwchar_var_FilePath) - 1] != L'\\')
					StringCchCat(pwchar_var_FilePath,MAX_PATH,L"\\");
				StringCchCat(pwchar_var_FilePath,MAX_PATH,struct_WinFinDat.cFileName) ;
				g_dword_DirectoryCount += 1;
				g_dword_CurseCount += 1;

				StringCchPrintf(pwchar_var_PrintBuffer,
								_countof(pwchar_var_PrintBuffer),
								ROW_SCANINFO_STATUS,
								g_dword_DirectoryCount,
								g_dword_FileCount,
								g_dword_TempFileCount) ;
				fun_Console_ClearRow(short_param_ShowCmdInfo,MAX_PATH) ;
				fun_Console_Printf_Pos(0,short_param_ShowCmdInfo,pwchar_var_PrintBuffer) ;
				fun_EnumDirectory_listTempFile(pwchar_var_FilePath,pwchar_param_SaveFile,
												short_param_ShowCmdInfo) ;
			}
		}
		else
		{
			if (fun_IsTempFiles(struct_WinFinDat.cFileName) == true)
			{
				g_dword_TempFileCount += 1 ;
				StringCchPrintf(pwchar_var_PrintBuffer,
								_countof(pwchar_var_PrintBuffer),
								ROW_SCANINFO_STATUS,
								g_dword_DirectoryCount,
								g_dword_FileCount,
								g_dword_CurseCount) ;
				fun_Console_ClearRow(short_param_ShowCmdInfo,MAX_PATH) ;
				fun_Console_Printf_Pos(0,short_param_ShowCmdInfo,pwchar_var_PrintBuffer) ;

				StringCchPrintf(pwchar_var_TempFilePath,_countof(pwchar_var_TempFilePath),L"%ls\\%ls\r\n",pwchar_var_FilePath,
							pwchar_var_FileName) ;


				
			}
		}
	} while (FindNextFile(handle_File,&struct_WinFinDat));
}

bool fun_IsTempFiles(const wchar_t * pwchar_param_FileName)
{
	wchar_t * pwchar_var_Ext = PathFindExtension(pwchar_param_FileName) ;
	if (wcscmp(pwchar_var_Ext,L".tmp") == 0)
		return true ; 
	return false ;
}


bool fun_SaveTempInfoFile(const wchar_t * pwchar_param_SaveFile, 
							const wchar_t * pwchar_param_Buffer, 
							DWORD dword_param_BufferSize)
{
	HANDLE handle_SaveFile ;
	DWORD dword_WordWritten ;

	handle_SaveFile = CreateFile(pwchar_param_SaveFile,
				FILE_ALL_ACCESS,
				FILE_SHARE_WRITE,
				NULL,OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,NULL) ;
	if (handle_SaveFile == INVALID_HANDLE_VALUE)
	{
		handle_SaveFile = CreateFile(pwchar_param_SaveFile,
				FILE_ALL_ACCESS,
				FILE_SHARE_WRITE,
				NULL,CREATE_NEW,
				FILE_ATTRIBUTE_NORMAL,NULL) ;

		if (handle_SaveFile == INVALID_HANDLE_VALUE)
		{
			wprintf_s(L"系统错误代码:%d\r\n",GetLastError()) ;
			return false ;
		}
		else
		{
			DWORD dword_WindowsPrefix = 0xfeff;
			//DWORD dword_Written ;
			WriteFile(handle_SaveFile,&dword_WindowsPrefix,
					sizeof(DWORD),&dword_WordWritten,NULL) ;
		}

		SetFilePointer(handle_SaveFile,0,NULL,FILE_END) ;
		WriteFile(handle_SaveFile,pwchar_param_Buffer,
				dword_param_BufferSize,&dword_WordWritten,NULL) ;

		CloseHandle(handle_SaveFile) ;
	}
}