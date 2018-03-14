#include "stdafx.h"
#include "LoginForm.h"

using namespace System;
using namespace System::Windows::Forms;

String ^ 摄像头拍照::LoginForm::getidname(int id)
{
	String^ name;
	try {
		mycon->Open();
		String^ sql = "SELECT * FROM `view_allinfo` WHERE `id` = " + id + " LIMIT 1";
		MySqlCommand ^mycmd = gcnew MySqlCommand(sql, mycon);
		auto reader = mycmd->ExecuteReader();
		while (reader->Read()) {
			name = reader->GetString("name");
		}
	}
	catch (MySqlException^ e) {
		MessageBox::Show(e->Message);
	}
	finally{
		mycon->Close();
	}
	
	return name;
}

//返回登陆成功之后的类型，-1密码错误,-2连接数据库失败
int 摄像头拍照::LoginForm::Login(String ^ name, String ^ pwd,int type)
{
	String^ tablename;
	switch (type) {
	case ADMIN:
		tablename = "login";
		break;
	case HUZHU:
		tablename = "login";
		break;
	case CHANGZHU:
		tablename = "login";
		break;
	}
	int r = -1;
	try {
		mycon->Open();
		String^ sql = "SELECT * FROM `"+tablename+"` WHERE `id` = '" + name + "' AND `pwd` = '" + pwd + "' LIMIT 1";
		MySqlCommand ^mycmd = gcnew MySqlCommand(sql, mycon);
		//String ^id, ^p;
		auto reader = mycmd->ExecuteReader();
		/*while (reader->Read()) {
			r = reader->GetInt32("type");
			AccountId = reader->GetString("id");
			AccountType = r;
		}*/
		r = 1;
		LoginFinish(gcnew CPersonInfo(1,"魔哥","地球",ADMIN));
	}
	catch (MySqlException^ e) {
		MessageBox::Show(e->Message);
		r = -2;
	}
	finally{
		mycon->Close();
	}
	/*if (mycmd->ExecuteNonQuery() > 0)
	{
		Console::WriteLine("数据插入成功！");
	}*/
	//Console::ReadLine();
	return r;
}

void 摄像头拍照::LoginForm::loginsuccsee()
{
	issu = 1;
	Close();
}

System::Void 摄像头拍照::LoginForm::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	String^ n = textBox1->Text;
	String^ p = textBox2->Text;
	if (rbtn_admin->Checked) {
		this->AccountType = ADMIN;
	}
	else if (rbtn_huzhu->Checked) {
		this->AccountType = HUZHU;
	}
	else if (rbtn_changzhu->Checked) {
		this->AccountType = CHANGZHU;
	}
	else {
		MessageBox::Show(L"请先选择账号类型");
		return;
	}
	int r=Login(n,p, this->AccountType);
	switch (r) {
	case -2:
		MessageBox::Show(L"连接数据库失败,请检查网络或联系管理员");
		break;
	case -1:
		MessageBox::Show(L"账号或密码错误");
		break;
	case 3:
		MessageBox::Show(L"访客无权登录本系统");
		break;
	default:
		loginsuccsee();
		break;
	}
}

System::Void 摄像头拍照::LoginForm::On_LoginForm_Close(System::Object ^ sender, System::Windows::Forms::FormClosingEventArgs ^ e)
{
	CConfigManager::SaveValueLater("LoginForm_id", textBox1->Text);
	CConfigManager::SaveValueLater("LoginForm_rem", checkBox1->Checked?"1":"0");
	if (checkBox1->Checked) {
		CConfigManager::SaveValueLater("LoginForm_pwd", textBox2->Text);
	}
	else {
		CConfigManager::DeleteValueLater("LoginForm_pwd");
	}
	CConfigManager::SaveValueLater("LoginForm_type",this->AccountType);
	CConfigManager::Submit();
	if(!issu)Environment::Exit(0);
}

System::Void 摄像头拍照::LoginForm::On_LoginForm_Load(System::Object ^ sender, System::EventArgs ^ e)
{
	textBox1->Text = CConfigManager::LoadValue("LoginForm_id");
	if (CConfigManager::LoadValue("LoginForm_rem") == "1") {
		checkBox1->Checked = 1;
		textBox2->Text = CConfigManager::LoadValue("LoginForm_pwd");
	}
	this->AccountType = CConfigManager::LoadInt("LoginForm_type");
	switch (this->AccountType) {
	case ADMIN:
		rbtn_admin->Checked = 1;
		break;
	case HUZHU:
		rbtn_huzhu->Checked = 1;
		break;
	case CHANGZHU:
		rbtn_changzhu->Checked = 1;
		break;
	}
}
