#include "stdafx.h"

using namespace System;
using namespace 摄像头拍照;
using namespace MySql::Data::MySqlClient;

inline void sqlitetest();
bool debugmod = 0;
void init() {
	DropFileFix();
	CConfigManager::init(0);
	Application::EnableVisualStyles();
}
void cleanup() {
	CConfigManager::Submit();
	CConfigManager::cleanup();
}
void runmod1() {
	if (debugmod) {
		MainForm^ mf = gcnew MainForm;
		mf->Show();
	}
	else {
		LoginForm ^lf = gcnew LoginForm;
		lf->ShowDialog();
		if (lf->issu) {
			MainForm^ mf = nullptr;
			mf = gcnew MainForm(lf->AccountId, lf->AccountType);
			mf->Show();
		}
		delete lf;
	}
	Application::Run();
}
void runmod2() {
	CFormsManager fm;
	if (!debugmod) {
		fm.ShowLogin();
	}
	else {
		fm.ShowMain(gcnew CPersonInfo(1, "魔哥", "地球", ADMIN));
	}
	Application::Run();
}
int main(array<System::String ^> ^args)
{
	init();
	//sqlitetest();
	//runmod1();
	runmod2();
	cleanup();
    return 0;
}
void sqlitetest() {
	CConfigManager::Submit();
	int a = CConfigManager::LoadInt("action");
	/*CConfigManager::SaveValue("action", "睡觉");
	String^ a = CConfigManager::LoadValue("action");
	CConfigManager::DeleteValue("action");*/
}