#include "stdafx.h"
#include "MainForm.h"

using namespace System;

摄像头拍照::MainForm::MainForm(int id,int type):MainForm()
{
	AccountId = id;
	AccountType = type;
	this->Text += "欢迎您,";
	switch (type) {
	case ADMIN:
		this->Text += "管理员:";
		break;
	case HUZHU:
		this->Text += "户主:";
		tabControl1->Controls->RemoveAt(0);
		radioButton1->Enabled = 0;
		break;
	case CHANGZHU:
		this->Text += "常驻人员:";
		tabControl1->Controls->RemoveAt(0);
		radioButton1->Enabled = 0;
		radioButton2->Enabled = 0;
		break;
	}
	AccountName = LoginForm::getidname(AccountId);
	this->Text += AccountName;
}

摄像头拍照::MainForm::MainForm(CPersonInfo ^ p):MainForm()
{
	AccountId = p->Id;
	AccountType = p->Type;
	AccountName = p->Name;
	this->Text += "欢迎您,";
	switch (p->Type) {
	case ADMIN:
		this->Text += "管理员:";
		break;
	case HUZHU:
		this->Text += "户主:";
		tabControl1->Controls->RemoveAt(0);
		radioButton1->Enabled = 0;
		break;
	case CHANGZHU:
		this->Text += "常住人员:";
		tabControl1->Controls->RemoveAt(0);
		radioButton1->Enabled = 0;
		radioButton2->Enabled = 0;
		break;
	}
	this->Text += AccountName;
}

void 摄像头拍照::MainForm::OnShootFinish(String ^ picname)
{
	//MessageBox::Show(L"拍照完成" + picname);
	pictureBox1->Image = System::Drawing::Image::FromFile(picname);
	toolStripStatusLabel1->Text=L"拍照完成";
}

void 摄像头拍照::MainForm::showallinfo()
{
	dataGridView1->Rows->Clear();
	MySqlConnection ^mycon=nullptr;
	String^ constr = L"server=123.207.91.166;User Id=cha;password=123456;Database=2018rj";
	mycon = gcnew MySqlConnection(constr);
	int len = 0;
	try {
		mycon->Open();
		//MessageBox::Show(L"登陆成功");
		String^ sql = "select `id`,`name`,`contact` from view_allinfo";
		MySqlCommand ^mycmd = gcnew MySqlCommand(sql, mycon);
		String  ^name,^contact;
		int id = 0;
		auto reader = mycmd->ExecuteReader();
		while (reader->Read()) {
			id = reader->GetInt32("id");
			name= reader->GetString("name");
			contact= reader->GetString("contact");
			CPersonInfo^ pif = gcnew CPersonInfo(id, name, contact,0);
			addapersoninfo(dataGridView1, pif);
			++len;
		}
	}
	catch (MySqlException^ e) {
		MessageBox::Show(e->Message);
	}
	finally{
		mycon->Close();
	}
	toolStripStatusLabel1->Text = "查询成功，共有"+len+"条数据";
}

void 摄像头拍照::MainForm::addapersoninfo(Windows::Forms::DataGridView ^ dgv, CPersonInfo ^ pif)
{
	int index = this->dataGridView1->Rows->Add();
	dgv->Rows[index]->Cells[0]->Value = pif->Id;
	dgv->Rows[index]->Cells[1]->Value = pif->Name;
	dgv->Rows[index]->Cells[2]->Value = pif->Contact;
}

System::Void 摄像头拍照::MainForm::On_MainForm_Close(System::Object ^ sender, System::Windows::Forms::FormClosingEventArgs ^ e)
{
	if (!isneedask)return;
	auto r=MessageBox::Show(L"确定要退出吗",L"提示", MessageBoxButtons::OKCancel,MessageBoxIcon::Warning);
	if (r == Windows::Forms::DialogResult::OK) {
		//Environment::Exit(0);
		//e->Cancel = 0;
		MainClose();
	}
	else {
		e->Cancel = 1;
	}
	
}

System::Void 摄像头拍照::MainForm::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	MyForm mf;
	mf.ShootFinish += gcnew ShootFinishEventHandler(this, &MainForm::OnShootFinish);
	mf.ShowDialog();
}
System::Void 摄像头拍照::MainForm::button2_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	int type = -1;
	if (radioButton1->Checked) {
		type = HUZHU;
	}
	else if(radioButton2->Checked){
		type = CHANGZHU;
	}
	else if (radioButton3->Checked) {
		type = FANGKE;
	}
	if (type == -1) {
		MessageBox::Show(L"请选择人员类型");
		return;
	}
	CPersonInfo^ cpi = gcnew CPersonInfo(0, textBox1->Text, textBox2->Text,1);
	MyClient^ mc = gcnew MyClient();
	mc->RegisterPerson(cpi);
	//mc->Reply += gcnew ReplyHandler(test);
}

System::Void 摄像头拍照::MainForm::btn_search_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	toolStripStatusLabel1->Text = "正在查询，请稍候...";
	showallinfo();
}

System::Void 摄像头拍照::MainForm::btn_register_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	tabControl1->SelectedIndex = 1;
}

System::Void 摄像头拍照::MainForm::btn_chooselocal_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	OPENFILENAME ofn;
	WCHAR szFile[1024];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = (HWND)(int)this->Handle;
	ofn.lpstrTitle = L"请选择一张图片";
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"所有图片\0*.bmp;*.png;*.jpg;*.jpeg\0位图文件(*.bmp)\0*.bmp\0PNG图片(*.png)\0*.png\0JPG图片(*.jpg;*.jpeg)\0*.jpg;*.JPEG\0\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	String^ p=nullptr;
	if (GetOpenFileName(&ofn)) {
		p = gcnew String(ofn.lpstrFile);
		OnShootFinish(p);
	}
}

System::Void 摄像头拍照::MainForm::On_Pic_Drag(System::Object ^ sender, System::Windows::Forms::DragEventArgs ^ e)
{
	String^ f=safe_cast<array<String^>^>(e->Data->GetData(DataFormats::FileDrop))[0];
	MessageBox::Show(f);
}

System::Void 摄像头拍照::MainForm::立即保存配置ToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	CConfigManager::Submit();
}
