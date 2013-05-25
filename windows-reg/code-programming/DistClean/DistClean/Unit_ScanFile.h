#include "stdafx.h"

#pragma  once


extern DWORD g_dword_FileCount ;
extern DWORD g_dword_DirectoryCount ;
extern DWORD g_dword_TempFileCount ;
extern DWORD g_dword_CurseCount ;


void fun_EnumDirectory_listTempFile(wchar_t * pwchar_param_RootPath,
									wchar_t * pwchar_param_SaveFile,
									short short_param_ShowCmdInfo) ;

bool fun_IsTempFiles(const wchar_t * pwchar_param_FileName) ;

bool fun_SaveTempInfoFile(const wchar_t * pwchar_param_SaveFile,
							const wchar_t * pwchar_param_Buffer,
							DWORD dword_param_BufferSize) ;