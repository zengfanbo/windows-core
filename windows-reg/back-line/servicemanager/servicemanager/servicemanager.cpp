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

	// enum the service 
	// 1. prepare the param we need in the EnumServiceStatus
	// 2. call the function 
	// 3. display the result of the function we get
	// 4. release the dynamic memory

	LPENUM_SERVICE_STATUS service_status_Result ;
	DWORD dword_BytesNeed = 0;
	DWORD dword_SerivceReturned = 0;
	DWORD dword_ResumeHandle = 0;

	service_status_Result = (LPENUM_SERVICE_STATUS)LocalAlloc(LPTR,64 * 1024) ;
	EnumServicesStatus(handle_opened_Manager,SERVICE_WIN32,SERVICE_STATE_ALL,service_status_Result,
						64 * 1024,&dword_BytesNeed,&dword_SerivceReturned,&dword_ResumeHandle) ;

	for (DWORD  i = 0 ; i < dword_SerivceReturned; ++i)
	{
		wprintf(L"服务名称:%s\t\t",service_status_Result[i].lpServiceName) ;
		wprintf(L"显示名称:%s\r\n",service_status_Result[i].lpDisplayName) ;
	}
	if (dword_SerivceReturned == 0)
	{
		GetLastError();
	}

	LocalFree(service_status_Result) ;
	CloseServiceHandle(handle_opened_service) ;
	CloseServiceHandle(handle_opened_Manager) ;
	
	getwchar() ;

	return 0;
}

