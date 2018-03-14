#include "stdafx.h"
#include "LoginForm.h"

using namespace System;
using namespace System::Windows::Forms;

String ^ ����ͷ����::LoginForm::getidname(int id)
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

//���ص�½�ɹ�֮������ͣ�-1�������,-2�������ݿ�ʧ��
int ����ͷ����::LoginForm::Login(String ^ name, String ^ pwd,int type)
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
		LoginFinish(gcnew CPersonInfo(1,"ħ��","����",ADMIN));
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
		Console::WriteLine("���ݲ���ɹ���");
	}*/
	//Console::ReadLine();
	return r;
}

void ����ͷ����::LoginForm::loginsuccsee()
{
	issu = 1;
	Close();
}

System::Void ����ͷ����::LoginForm::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
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
		MessageBox::Show(L"����ѡ���˺�����");
		return;
	}
	int r=Login(n,p, this->AccountType);
	switch (r) {
	case -2:
		MessageBox::Show(L"�������ݿ�ʧ��,�����������ϵ����Ա");
		break;
	case -1:
		MessageBox::Show(L"�˺Ż��������");
		break;
	case 3:
		MessageBox::Show(L"�ÿ���Ȩ��¼��ϵͳ");
		break;
	default:
		loginsuccsee();
		break;
	}
}

System::Void ����ͷ����::LoginForm::On_LoginForm_Close(System::Object ^ sender, System::Windows::Forms::FormClosingEventArgs ^ e)
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

System::Void ����ͷ����::LoginForm::On_LoginForm_Load(System::Object ^ sender, System::EventArgs ^ e)
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
