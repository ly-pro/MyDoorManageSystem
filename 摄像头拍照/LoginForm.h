#pragma once

namespace 摄像头拍照 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace MySql::Data::MySqlClient;

	/// <summary>
	/// LoginForm 摘要
	/// </summary>
	public delegate void LoginFinishEventhandler(CPersonInfo^ p);
	public ref class LoginForm : public System::Windows::Forms::Form
	{
	public:
		event LoginFinishEventhandler^ LoginFinish;
		property int AccountType;
		property int AccountId;
		LoginForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//
			constr = L"server=123.207.91.166;User Id=cha;password=123456;Database=2018rj";
			mycon = gcnew MySqlConnection(constr);
		}
		static String^ getidname(int id);
	private:
		static String ^ constr;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::RadioButton^  rbtn_changzhu;
	private: System::Windows::Forms::RadioButton^  rbtn_huzhu;
	private: System::Windows::Forms::RadioButton^  rbtn_admin;
			 static MySqlConnection ^mycon;
		int Login(String^ name, String^ pwd,int type);
	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~LoginForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label2;
	protected:

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(LoginForm::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->rbtn_changzhu = (gcnew System::Windows::Forms::RadioButton());
			this->rbtn_huzhu = (gcnew System::Windows::Forms::RadioButton());
			this->rbtn_admin = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(114, 110);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(146, 32);
			this->button1->TabIndex = 0;
			this->button1->Text = L"登陆";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &LoginForm::button1_Click);
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(29, 27);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 12);
			this->label1->TabIndex = 1;
			this->label1->Text = L"账号:";
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->Location = System::Drawing::Point(101, 26);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(159, 21);
			this->textBox1->TabIndex = 2;
			// 
			// textBox2
			// 
			this->textBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox2->Location = System::Drawing::Point(101, 67);
			this->textBox2->Name = L"textBox2";
			this->textBox2->PasswordChar = '*';
			this->textBox2->Size = System::Drawing::Size(159, 21);
			this->textBox2->TabIndex = 4;
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(29, 70);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 12);
			this->label2->TabIndex = 3;
			this->label2->Text = L"密码:";
			// 
			// checkBox1
			// 
			this->checkBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(20, 118);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(72, 16);
			this->checkBox1->TabIndex = 5;
			this->checkBox1->Text = L"记住密码";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->rbtn_changzhu);
			this->groupBox1->Controls->Add(this->rbtn_huzhu);
			this->groupBox1->Controls->Add(this->rbtn_admin);
			this->groupBox1->Location = System::Drawing::Point(279, 27);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(82, 114);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"账号类型";
			// 
			// rbtn_changzhu
			// 
			this->rbtn_changzhu->AutoSize = true;
			this->rbtn_changzhu->Location = System::Drawing::Point(6, 83);
			this->rbtn_changzhu->Name = L"rbtn_changzhu";
			this->rbtn_changzhu->Size = System::Drawing::Size(71, 16);
			this->rbtn_changzhu->TabIndex = 2;
			this->rbtn_changzhu->TabStop = true;
			this->rbtn_changzhu->Text = L"常住人员";
			this->rbtn_changzhu->UseVisualStyleBackColor = true;
			// 
			// rbtn_huzhu
			// 
			this->rbtn_huzhu->AutoSize = true;
			this->rbtn_huzhu->Location = System::Drawing::Point(6, 56);
			this->rbtn_huzhu->Name = L"rbtn_huzhu";
			this->rbtn_huzhu->Size = System::Drawing::Size(47, 16);
			this->rbtn_huzhu->TabIndex = 1;
			this->rbtn_huzhu->TabStop = true;
			this->rbtn_huzhu->Text = L"户主";
			this->rbtn_huzhu->UseVisualStyleBackColor = true;
			// 
			// rbtn_admin
			// 
			this->rbtn_admin->AutoSize = true;
			this->rbtn_admin->Location = System::Drawing::Point(6, 29);
			this->rbtn_admin->Name = L"rbtn_admin";
			this->rbtn_admin->Size = System::Drawing::Size(59, 16);
			this->rbtn_admin->TabIndex = 0;
			this->rbtn_admin->TabStop = true;
			this->rbtn_admin->Text = L"管理员";
			this->rbtn_admin->UseVisualStyleBackColor = true;
			// 
			// LoginForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(374, 168);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"LoginForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"登录";
			this->TopMost = true;
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &LoginForm::On_LoginForm_Close);
			this->Load += gcnew System::EventHandler(this, &LoginForm::On_LoginForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public:
		bool issu = 0;
	private: 
		void loginsuccsee();
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void On_LoginForm_Close(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
	private: System::Void On_LoginForm_Load(System::Object^  sender, System::EventArgs^  e);
};
}
