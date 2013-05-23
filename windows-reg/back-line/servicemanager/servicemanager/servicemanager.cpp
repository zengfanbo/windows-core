// servicemanager.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{

	// open the SC manager 
	// 1. set the handle to the SC manager
	// 2. open the  service 
	// 3. error report 
	// 4. release the alloc memeory

	_wsetlocale(LC_ALL,L"chs") ;

	 SC_HANDLE handle_opened_Manager ;
	 SC_HANDLE handle_opened_service ;

	handle_opened_Manager = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS) ;
	if (handle_opened_Manager == NULL)
	{
		wprintf(L"%d",GetLastError()) ;

		return -1 ;
	}


	handle_opened_service = OpenService(handle_opened_Manager,L"AxInstSV",SERVICE_ALL_ACCESS) ;

	if (handle_opened_service == NULL)
	{
		wprintf(L"%d",GetLastError()) ;

		return -1 ;
	}

	CloseServiceHandle(handle_opened_service) ;
	CloseServiceHandle(handle_opened_Manager) ;
	
	return 0;
}

