#include "RegOperation.h"


BOOL Format_ErrorMessage(DWORD dword_ErrorCode) ;

BOOL SetKeyAndValue(LPCTSTR lpstr_root_path, 
	LPCTSTR lpstr_sub_name, 
	BYTE * byte_value, 
	DWORD dword_size)
{
	if (lpstr_root_path == NULL)
		return false ;
	if (lpstr_sub_name == NULL) 
		return false ;

	// open the key HKEY_ROOT_CLASSIC 
	// 1. perpare the handle to key 
	HKEY hkey_Parent ;
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT,NULL,0,KEY_ALL_ACCESS,&hkey_Parent) 
		== ERROR_SUCCESS)
	{
		// create the key lpstr_root_path 
		HKEY hkey_Child ;
		DWORD dword_ErrorCode ;
		// set the lpstr_root_path value 
		if (RegCreateKeyEx(hkey_Parent,lpstr_root_path,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,
			NULL,&hkey_Child,&dword_ErrorCode) == ERROR_SUCCESS)
		{
			if (RegSetValueEx(hkey_Child,lpstr_sub_name,0,REG_SZ,byte_value,dword_size) == ERROR_SUCCESS)
			{
				wprintf(L"\r\n%s\r\n",lpstr_sub_name) ;
				wprintf(L"\r\n%s\r\n",byte_value) ;
			}
		}
		// get the error code
		Format_ErrorMessage(dword_ErrorCode) ;

		// delete the alloc resource
		if (hkey_Child != NULL)
			RegCloseKey(hkey_Child) ;
		hkey_Child = NULL ;
	}

	if (hkey_Parent != NULL)
		RegCloseKey(hkey_Parent) ;





}

BOOL Format_ErrorMessage(DWORD dword_ErrorCode)
{
	TCHAR * tchar_ErrorMessage ;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,dword_ErrorCode,0,(LPTSTR)&tchar_ErrorMessage,0,
		NULL) ;

	wprintf(L"%s",tchar_ErrorMessage) ;

	LocalFree(tchar_ErrorMessage) ;
	return true ;
}