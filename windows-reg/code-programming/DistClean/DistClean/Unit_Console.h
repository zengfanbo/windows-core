

#pragma once


void fun_Console_HideCursor(void);
void fun_Console_Printf_Pos(short sint_param_Column,
							short sint_param_Row,
							wchar_t * wchar_param_PrintBuffer);

void fun_Console_ClearAll(void);

void fun_Console_ClearRow(short short_param_Row,short short_param_Len);