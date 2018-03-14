#pragma once
#include "faceapi.h"

namespace 摄像头拍照 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;
	using namespace AForge;
	using namespace AForge::Controls;
	using namespace AForge::Imaging;
	using namespace AForge::Video;
	using namespace AForge::Video::DirectShow;

	public delegate void ShootFinishEventHandler(String^ picname);

	/// <summary>
	/// MyForm 摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		event ShootFinishEventHandler^ ShootFinish;
		FilterInfoCollection ^videoDevices;
		VideoCaptureDevice ^videoSource;
		int selectedDeviceIndex = 0;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  文件ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  打开照片文件夹ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  选项ToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  旋转ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  逆时针90ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  逆时针180ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  顺时针90ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  顺时针180ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  翻转ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  左右翻转ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  上下翻转ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  图像ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  退出ToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  button2;
	public:
		property String ^ adminname;
		MyForm(void);

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			//MessageBox::Show("析构");
			cleanupfaceengine();
		}
	private: AForge::Controls::VideoSourcePlayer^  videoSourcePlayer1;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->videoSourcePlayer1 = (gcnew AForge::Controls::VideoSourcePlayer());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->文件ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->打开照片文件夹ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->选项ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->旋转ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->逆时针90ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->逆时针180ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->顺时针90ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->顺时针180ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->翻转ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->左右翻转ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->上下翻转ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->图像ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->退出ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->statusStrip1->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// videoSourcePlayer1
			// 
			this->videoSourcePlayer1->Location = System::Drawing::Point(15, 32);
			this->videoSourcePlayer1->Name = L"videoSourcePlayer1";
			this->videoSourcePlayer1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->videoSourcePlayer1->Size = System::Drawing::Size(64, 48);
			this->videoSourcePlayer1->TabIndex = 0;
			this->videoSourcePlayer1->Text = L"videoSourcePlayer1";
			this->videoSourcePlayer1->VideoSource = nullptr;
			this->videoSourcePlayer1->Visible = false;
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(368, 135);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(109, 32);
			this->button1->TabIndex = 1;
			this->button1->Text = L"打开摄像头";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button2->Enabled = false;
			this->button2->Location = System::Drawing::Point(368, 200);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(109, 32);
			this->button2->TabIndex = 2;
			this->button2->Text = L"拍照";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(342, 68);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(153, 20);
			this->comboBox1->TabIndex = 3;
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(402, 43);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(41, 12);
			this->label1->TabIndex = 4;
			this->label1->Text = L"摄像头";
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->statusStrip1->Location = System::Drawing::Point(0, 281);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(507, 22);
			this->statusStrip1->TabIndex = 5;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(131, 17);
			this->toolStripStatusLabel1->Text = L"toolStripStatusLabel1";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->文件ToolStripMenuItem,
					this->选项ToolStripMenuItem, this->图像ToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(507, 25);
			this->menuStrip1->TabIndex = 6;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// 文件ToolStripMenuItem
			// 
			this->文件ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->打开照片文件夹ToolStripMenuItem });
			this->文件ToolStripMenuItem->Name = L"文件ToolStripMenuItem";
			this->文件ToolStripMenuItem->Size = System::Drawing::Size(44, 21);
			this->文件ToolStripMenuItem->Text = L"文件";
			// 
			// 打开照片文件夹ToolStripMenuItem
			// 
			this->打开照片文件夹ToolStripMenuItem->Name = L"打开照片文件夹ToolStripMenuItem";
			this->打开照片文件夹ToolStripMenuItem->Size = System::Drawing::Size(160, 22);
			this->打开照片文件夹ToolStripMenuItem->Text = L"打开照片文件夹";
			this->打开照片文件夹ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::打开照片文件夹ToolStripMenuItem_Click);
			// 
			// 选项ToolStripMenuItem
			// 
			this->选项ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->旋转ToolStripMenuItem,
					this->翻转ToolStripMenuItem
			});
			this->选项ToolStripMenuItem->Name = L"选项ToolStripMenuItem";
			this->选项ToolStripMenuItem->Size = System::Drawing::Size(44, 21);
			this->选项ToolStripMenuItem->Text = L"图像";
			// 
			// 旋转ToolStripMenuItem
			// 
			this->旋转ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->逆时针90ToolStripMenuItem,
					this->逆时针180ToolStripMenuItem, this->顺时针90ToolStripMenuItem, this->顺时针180ToolStripMenuItem
			});
			this->旋转ToolStripMenuItem->Name = L"旋转ToolStripMenuItem";
			this->旋转ToolStripMenuItem->Size = System::Drawing::Size(100, 22);
			this->旋转ToolStripMenuItem->Text = L"旋转";
			// 
			// 逆时针90ToolStripMenuItem
			// 
			this->逆时针90ToolStripMenuItem->Name = L"逆时针90ToolStripMenuItem";
			this->逆时针90ToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->逆时针90ToolStripMenuItem->Text = L"逆时针旋转90°";
			this->逆时针90ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::逆时针90ToolStripMenuItem_Click);
			// 
			// 逆时针180ToolStripMenuItem
			// 
			this->逆时针180ToolStripMenuItem->Name = L"逆时针180ToolStripMenuItem";
			this->逆时针180ToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->逆时针180ToolStripMenuItem->Text = L"逆时针旋转180°";
			this->逆时针180ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::逆时针180ToolStripMenuItem_Click);
			// 
			// 顺时针90ToolStripMenuItem
			// 
			this->顺时针90ToolStripMenuItem->Name = L"顺时针90ToolStripMenuItem";
			this->顺时针90ToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->顺时针90ToolStripMenuItem->Text = L"顺时针旋转90°";
			this->顺时针90ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::顺时针90ToolStripMenuItem_Click);
			// 
			// 顺时针180ToolStripMenuItem
			// 
			this->顺时针180ToolStripMenuItem->Name = L"顺时针180ToolStripMenuItem";
			this->顺时针180ToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->顺时针180ToolStripMenuItem->Text = L"顺时针旋转180°";
			this->顺时针180ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::顺时针180ToolStripMenuItem_Click);
			// 
			// 翻转ToolStripMenuItem
			// 
			this->翻转ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->左右翻转ToolStripMenuItem,
					this->上下翻转ToolStripMenuItem
			});
			this->翻转ToolStripMenuItem->Name = L"翻转ToolStripMenuItem";
			this->翻转ToolStripMenuItem->Size = System::Drawing::Size(100, 22);
			this->翻转ToolStripMenuItem->Text = L"翻转";
			// 
			// 左右翻转ToolStripMenuItem
			// 
			this->左右翻转ToolStripMenuItem->Name = L"左右翻转ToolStripMenuItem";
			this->左右翻转ToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->左右翻转ToolStripMenuItem->Text = L"左右翻转";
			this->左右翻转ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::左右翻转ToolStripMenuItem_Click);
			// 
			// 上下翻转ToolStripMenuItem
			// 
			this->上下翻转ToolStripMenuItem->Name = L"上下翻转ToolStripMenuItem";
			this->上下翻转ToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->上下翻转ToolStripMenuItem->Text = L"上下翻转";
			this->上下翻转ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::上下翻转ToolStripMenuItem_Click);
			// 
			// 图像ToolStripMenuItem
			// 
			this->图像ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->退出ToolStripMenuItem });
			this->图像ToolStripMenuItem->Name = L"图像ToolStripMenuItem";
			this->图像ToolStripMenuItem->Size = System::Drawing::Size(44, 21);
			this->图像ToolStripMenuItem->Text = L"选项";
			// 
			// 退出ToolStripMenuItem
			// 
			this->退出ToolStripMenuItem->Name = L"退出ToolStripMenuItem";
			this->退出ToolStripMenuItem->Size = System::Drawing::Size(100, 22);
			this->退出ToolStripMenuItem->Text = L"退出";
			this->退出ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::退出ToolStripMenuItem_Click_1);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(15, 32);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(320, 240);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 7;
			this->pictureBox1->TabStop = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(507, 303);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->videoSourcePlayer1);
			this->Controls->Add(this->pictureBox1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"拍照界面";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::onmyform_close);
			this->Load += gcnew System::EventHandler(this, &MyForm::OnMyForm_Load);
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public:
		void takephoto();
		void startcapture();
		void stopcapture();
		void getcamerainfo();
		//旋转角度
		static int dAngle = 0;
		//上下翻转
		static int shangxiafanzhuan = 0;
		//左右翻转
		static int zuoyoufanzhuan = 0;
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void onmyform_close(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
	private: System::Void OnMyForm_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void 打开照片文件夹ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void 退出ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
			 void markfaces(System::Drawing::Bitmap ^% image);
	public : System::Void videoSourcePlayer_NewFrame(System::Object^ sender, System::Drawing::Bitmap^% image);
	private: System::Void 逆时针90ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void 逆时针180ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void 顺时针90ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void 顺时针180ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void 左右翻转ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void 上下翻转ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void 退出ToolStripMenuItem_Click_1(System::Object^  sender, System::EventArgs^  e);
};
}
