#include "stdafx.h"

using namespace std;
void inttocharx(int x, char* c)
{
	stringstream ss(x);
	ss >> c;
}

int charxtoint(char * c)
{
	int x = 0;
	stringstream ss(c);
	ss >> x;
	return x;
}

void dump(byte * d, size_t len, const char * file) {
	FILE *fp = nullptr;
	fopen_s(&fp, file, "w+b");
	fwrite(d, sizeof(byte), len, fp);
	fclose(fp);
}

String ^ readfile(String^ filename)
{
	FileStream^ aFile = gcnew FileStream(filename, FileMode::Open);
	StreamReader^ sr = gcnew StreamReader(aFile);
	return sr->ReadToEnd();
}

void DropFileFix()
{
	HINSTANCE hDllInst = LoadLibrary(L"user32.dll");
	if (hDllInst)
	{
		CHANGEWINDOWMESSAGEFILTER *pAddMessageFilterFunc = (CHANGEWINDOWMESSAGEFILTER *)GetProcAddress(hDllInst, "ChangeWindowMessageFilter");
		if (pAddMessageFilterFunc)
		{
			pAddMessageFilterFunc(WM_DROPFILES, MSGFLT_ADD);
			pAddMessageFilterFunc(WM_COPYDATA, MSGFLT_ADD);
			pAddMessageFilterFunc(0x0049, MSGFLT_ADD);
		}
		FreeLibrary(hDllInst);
	}
}
