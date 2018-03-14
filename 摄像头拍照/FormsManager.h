#pragma once

using namespace …„œÒÕ∑≈ƒ’’;

public ref class CFormsManager
{
public:
	CFormsManager();
	virtual ~CFormsManager();
	MyForm ^sf = nullptr;
	LoginForm^ lf = nullptr;
	MainForm^ mf = nullptr;
	OpenFileDialog^ dialog=nullptr;
	void ShowLogin();
	void ShowMain(CPersonInfo ^ p);
	void ShowMain(System::Object ^ p);
	void OnLoginFinish(CPersonInfo^ p);
	void OnMainClose();
private:
	int logintype = -1;
};

