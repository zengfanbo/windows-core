// regOperation.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Reg.h"

using std::cout;
using std::endl;

int _tmain(int argc, _TCHAR* argv[])
{

	// how to test the function named SetKeyAndValue
	// 1. we prepare the param 
	// 1.1 we the	root_path type:LPCTSTR
	// 1.2			sub_path type: LPCTSTR
	// 1.3			sub_name type: LPCTSTR
	// 1.4			byte_value type : byte array
	// 2. we call the function
	// 3. we release the memory

	LPCTSTR lpctstr_root_path = TEXT("Software") ;
	LPCTSTR lpctstr_sub_path = TEXT("Winapp") ;
	LPCTSTR lpctstr_sub_name = TEXT("Name") ;
	char * char_value = "C:\\system32" ;

	SetKeyAndValue(lpctstr_root_path,lpctstr_sub_path,lpctstr_sub_name,
					strlen(char_value),(BYTE *)char_value) ;

	return 0;
}

