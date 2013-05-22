#pragma once

/*
 *	the file description of the Reg set value.
 * the main idea about how to set the key and vlaue
 * we could recieve the root_path and the sub_path and the value
 * 1. we open the root_path 
 * 2. we create the sub_path -- the sub_path just the name
 * 3. we set the sub_path's value
 */
#include <windows.h>

BOOL SetKeyAndValue(LPCTSTR root_path,LPCTSTR sub_path,LPCTSTR sub_value,
					short short_length,BYTE * byte_value);
