#include "stdafx.h"
#include "Unit_Console.h"
/*
*   功能： 隐藏光标
*   参数： 无
* 	返回结果：无
*/
void fun_Console_HideCursor()
{
	CONSOLE_CURSOR_INFO struct_ConsInfo ;
	HANDLE handle_StdOut = GetStdHandle(STD_OUTPUT_HANDLE) ;
	if (handle_StdOut != INVALID_HANDLE_VALUE)
	{
		GetConsoleCursorInfo(handle_StdOut,&struct_ConsInfo) ;
		struct_ConsInfo.bVisible = false ;
		SetConsoleCursorInfo(handle_StdOut,&struct_ConsInfo) ;
	}

	CloseHandle(handle_StdOut) ;
	return ;
} // fun_Console_HideCursor

void fun_Console_ClearRow(short short_param_Row,short short_param_Len)
{
	COORD struct_coord = { 0,short_param_Row } ;
	DWORD dword_written ;
	HANDLE handle_StdOut ;
	CONSOLE_SCREEN_BUFFER_INFO struct_ConScrBufInf ;
	handle_StdOut = GetStdHandle(STD_OUTPUT_HANDLE) ;

	GetConsoleScreenBufferInfo(handle_StdOut,&struct_ConScrBufInf) ;
	FillConsoleOutputCharacter(handle_StdOut,(TCHAR)32,short_param_Len,struct_coord,&dword_written) ;
	//SetConsoleTextAttribute(handle_StdOut,struct_ConScrBufInf.wAttributes) ;
	FillConsoleOutputAttribute(handle_StdOut,struct_ConScrBufInf.wAttributes,short_param_Len,
								struct_coord,&dword_written) ;
	

} // fun_Console_ClearRow


void fun_Console_ClearAll()
{
	COORD struct_coord = { 0, 0 } ;
	HANDLE handle_StdOut ;
	CONSOLE_SCREEN_BUFFER_INFO ConScrBufInf ;
	DWORD dword_Write ;

	handle_StdOut = GetStdHandle(STD_OUTPUT_HANDLE) ;
	if (handle_StdOut != INVALID_HANDLE_VALUE)
	{
		DWORD dword_ConsoleSize ;
		GetConsoleScreenBufferInfo(handle_StdOut,&ConScrBufInf) ;
		dword_ConsoleSize = ConScrBufInf.dwSize.X * ConScrBufInf.dwSize.Y ;
		FillConsoleOutputCharacter(handle_StdOut,(TCHAR)32,dword_ConsoleSize,struct_coord,&dword_Write) ;
		FillConsoleOutputAttribute(handle_StdOut,ConScrBufInf.wAttributes,
		dword_ConsoleSize,struct_coord,&dword_Write) ;
	}

} //fun_Console_ClearAll

void fun_Console_Printf_Pos(short sint_param_Column,
							short sint_param_Row,
							wchar_t * wchar_param_PrintBuffer)
{

	HANDLE handle_StdOut ;
	COORD struct_coord = {sint_param_Column,sint_param_Row };
	DWORD dword_Written ;
	
		handle_StdOut = GetStdHandle(STD_OUTPUT_HANDLE) ;
		if (handle_StdOut != INVALID_HANDLE_VALUE)
		{
			SetConsoleCursorPosition(handle_StdOut,struct_coord) ;
			WriteConsole(handle_StdOut,(void*)wchar_param_PrintBuffer,wcslen(wchar_param_PrintBuffer),
					&dword_Written,NULL) ;
		}

		return ;
}