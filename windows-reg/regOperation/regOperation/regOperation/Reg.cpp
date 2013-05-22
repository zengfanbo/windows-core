#include "StdAfx.h"
#include "Reg.h"
#include <iostream>

using std::cout;
using std::endl;

BOOL SetKeyAndValue(LPCTSTR root_path,LPCTSTR sub_path,LPCTSTR sub_name,
					short short_length,BYTE * byte_value)
{

	// to finish the idea about how to set the name and value
	// we refer the could divide three steps.
	// 1. we open the root_path reflect the root_key
	// 1.1 we need use the regcreatekeyex function
	HKEY hkey_Parent ;
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT,root_path,0,KEY_ALL_ACCESS,&hkey_Parent) != ERROR_SUCCESS)
		hkey_Parent = NULL ;
	// 1.2 the param about the hkey and KEY_ALL_ACCESS and the root_path and the HKEY_
	// 1.3 if we use some dynamic storage ,we could release in below.
	// 2. we create the sub_path key
	// 2.1 we need the function : regcreatekeyex
	// 2.2 we need the param hkey KEY_ALL_ACCESS sub_path 
	// 2.3 release we dynamic memory 
	HKEY hkey_Child ;
	DWORD dword_ErrorCode ;
	if ((hkey_Parent != NULL) && 
		(RegCreateKeyEx(hkey_Parent,sub_path,0,NULL,REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,NULL,&hkey_Child,&dword_ErrorCode) != ERROR_SUCCESS))
	{
		wprintf(L"%d",dword_ErrorCode) ;
		hkey_Child = NULL;
	}
	// 3  we set the sub_path value
	// 3.1 we need the function : regsetvalueex
	// 3.2 we need the param the hkey type REG_SZ,byte_value
	// 3.3 we release we dynamic memory
	
	if ( (hkey_Child != NULL) &&
		(RegSetValueEx(hkey_Child,sub_name,0,REG_SZ,byte_value,short_length) != ERROR_SUCCESS))
	{
		wprintf(L"\r\n%s\r\n",sub_name) ;
		wprintf(L"\r\n%s\r\n",byte_value) ;
	}

	if (hkey_Child != NULL)
	{
		RegCloseKey(hkey_Child) ;
	}

	if (hkey_Parent != NULL)
	{
		RegCloseKey(hkey_Parent) ;
	}
	return true;
}