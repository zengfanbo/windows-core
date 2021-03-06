#include "StdAfx.h"
#include "Reg.h"
#include <iostream>

using std::cout;
using std::endl;

BOOL Format_ErrorMessage(DWORD dword_ErrorCode) ;

BOOL SetKeyAndValue(LPCTSTR root_path,LPCTSTR sub_name,
	DWORD dword_length,BYTE * byte_value)
{
	HKEY hkey_Parent ;
	// open the register key
	// 1. perpare the param the root_path and write and read privilege
	// 2. call the function regopenkeyex
	// 3. release some memory we dynaimc alloc
	if (RegOpenKeyEx(HKEY_CURRENT_USER,NULL,0,KEY_ALL_ACCESS,&hkey_Parent) == ERROR_SUCCESS)
	{
		// create the sub_name key 
		HKEY hkey_Child ;
		DWORD dword_ErrorCode ;
		if (RegCreateKeyEx(hkey_Parent,root_path,0,REG_NONE,REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS,NULL,&hkey_Child,&dword_ErrorCode) ==  ERROR_SUCCESS)
		{
			if (RegSetValueEx(hkey_Child,sub_name,0,REG_SZ,byte_value,dword_length) == ERROR_SUCCESS)
			{
				wprintf(L"%s",sub_name) ;
				wprintf(L"%s",byte_value) ;
			}
		}


		//Format_ErrorMessage(dword_ErrorCode) ;
	}



	return true;
}

BOOL Format_ErrorMessage(DWORD dword_ErrorCode) 
{
	TCHAR * tchar_ErrorMessage ;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,dword_ErrorCode,0,(LPTSTR)&tchar_ErrorMessage,0,NULL) ;

	wprintf(L"%s",tchar_ErrorMessage) ;
	LocalFree(tchar_ErrorMessage) ;

	return true ;
}