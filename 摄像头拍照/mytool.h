#pragma once

#include<sstream>

using namespace System::Drawing;
using namespace System::IO;

void inttocharx(int x,char* c);
int charxtoint(char* c);
void dump(byte *d, size_t len, const char* file);
String^ readfile(String^ filename);

#ifndef WM_COPYGLOBALDATA
#define WM_COPYGLOBALDATA 0x0049
#endif
typedef WINUSERAPI BOOL WINAPI CHANGEWINDOWMESSAGEFILTER(UINT message, DWORD dwFlag);

//修复OnDropFile在win7管理员权限下接收不到的问题
void DropFileFix();