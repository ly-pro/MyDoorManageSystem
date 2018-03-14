#pragma once
#include "faceapi.h"

namespace ����ͷ���� {

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
	/// MyForm ժҪ
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
	private: System::Windows::Forms::ToolStripMenuItem^  �ļ�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ����Ƭ�ļ���ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ѡ��ToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  ��תToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ��ʱ��90ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ��ʱ��180ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ˳ʱ��90ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ˳ʱ��180ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ��תToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ���ҷ�תToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ���·�תToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ͼ��ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �˳�ToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  button2;
	public:
		property String ^ adminname;
		MyForm(void);

	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			//MessageBox::Show("����");
			cleanupfaceengine();
		}
	private: AForge::Controls::VideoSourcePlayer^  videoSourcePlayer1;
	protected:

	private:
		/// <summary>
		/// ����������������
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����֧������ķ��� - ��Ҫ�޸�
		/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
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
			this->�ļ�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->����Ƭ�ļ���ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ѡ��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->��תToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->��ʱ��90ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->��ʱ��180ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->˳ʱ��90ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->˳ʱ��180ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->��תToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->���ҷ�תToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->���·�תToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ͼ��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�˳�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			this->button1->Text = L"������ͷ";
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
			this->button2->Text = L"����";
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
			this->label1->Text = L"����ͷ";
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
				this->�ļ�ToolStripMenuItem,
					this->ѡ��ToolStripMenuItem, this->ͼ��ToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(507, 25);
			this->menuStrip1->TabIndex = 6;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// �ļ�ToolStripMenuItem
			// 
			this->�ļ�ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->����Ƭ�ļ���ToolStripMenuItem });
			this->�ļ�ToolStripMenuItem->Name = L"�ļ�ToolStripMenuItem";
			this->�ļ�ToolStripMenuItem->Size = System::Drawing::Size(44, 21);
			this->�ļ�ToolStripMenuItem->Text = L"�ļ�";
			// 
			// ����Ƭ�ļ���ToolStripMenuItem
			// 
			this->����Ƭ�ļ���ToolStripMenuItem->Name = L"����Ƭ�ļ���ToolStripMenuItem";
			this->����Ƭ�ļ���ToolStripMenuItem->Size = System::Drawing::Size(160, 22);
			this->����Ƭ�ļ���ToolStripMenuItem->Text = L"����Ƭ�ļ���";
			this->����Ƭ�ļ���ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::����Ƭ�ļ���ToolStripMenuItem_Click);
			// 
			// ѡ��ToolStripMenuItem
			// 
			this->ѡ��ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->��תToolStripMenuItem,
					this->��תToolStripMenuItem
			});
			this->ѡ��ToolStripMenuItem->Name = L"ѡ��ToolStripMenuItem";
			this->ѡ��ToolStripMenuItem->Size = System::Drawing::Size(44, 21);
			this->ѡ��ToolStripMenuItem->Text = L"ͼ��";
			// 
			// ��תToolStripMenuItem
			// 
			this->��תToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->��ʱ��90ToolStripMenuItem,
					this->��ʱ��180ToolStripMenuItem, this->˳ʱ��90ToolStripMenuItem, this->˳ʱ��180ToolStripMenuItem
			});
			this->��תToolStripMenuItem->Name = L"��תToolStripMenuItem";
			this->��תToolStripMenuItem->Size = System::Drawing::Size(100, 22);
			this->��תToolStripMenuItem->Text = L"��ת";
			// 
			// ��ʱ��90ToolStripMenuItem
			// 
			this->��ʱ��90ToolStripMenuItem->Name = L"��ʱ��90ToolStripMenuItem";
			this->��ʱ��90ToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->��ʱ��90ToolStripMenuItem->Text = L"��ʱ����ת90��";
			this->��ʱ��90ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::��ʱ��90ToolStripMenuItem_Click);
			// 
			// ��ʱ��180ToolStripMenuItem
			// 
			this->��ʱ��180ToolStripMenuItem->Name = L"��ʱ��180ToolStripMenuItem";
			this->��ʱ��180ToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->��ʱ��180ToolStripMenuItem->Text = L"��ʱ����ת180��";
			this->��ʱ��180ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::��ʱ��180ToolStripMenuItem_Click);
			// 
			// ˳ʱ��90ToolStripMenuItem
			// 
			this->˳ʱ��90ToolStripMenuItem->Name = L"˳ʱ��90ToolStripMenuItem";
			this->˳ʱ��90ToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->˳ʱ��90ToolStripMenuItem->Text = L"˳ʱ����ת90��";
			this->˳ʱ��90ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::˳ʱ��90ToolStripMenuItem_Click);
			// 
			// ˳ʱ��180ToolStripMenuItem
			// 
			this->˳ʱ��180ToolStripMenuItem->Name = L"˳ʱ��180ToolStripMenuItem";
			this->˳ʱ��180ToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->˳ʱ��180ToolStripMenuItem->Text = L"˳ʱ����ת180��";
			this->˳ʱ��180ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::˳ʱ��180ToolStripMenuItem_Click);
			// 
			// ��תToolStripMenuItem
			// 
			this->��תToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->���ҷ�תToolStripMenuItem,
					this->���·�תToolStripMenuItem
			});
			this->��תToolStripMenuItem->Name = L"��תToolStripMenuItem";
			this->��תToolStripMenuItem->Size = System::Drawing::Size(100, 22);
			this->��תToolStripMenuItem->Text = L"��ת";
			// 
			// ���ҷ�תToolStripMenuItem
			// 
			this->���ҷ�תToolStripMenuItem->Name = L"���ҷ�תToolStripMenuItem";
			this->���ҷ�תToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->���ҷ�תToolStripMenuItem->Text = L"���ҷ�ת";
			this->���ҷ�תToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::���ҷ�תToolStripMenuItem_Click);
			// 
			// ���·�תToolStripMenuItem
			// 
			this->���·�תToolStripMenuItem->Name = L"���·�תToolStripMenuItem";
			this->���·�תToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->���·�תToolStripMenuItem->Text = L"���·�ת";
			this->���·�תToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::���·�תToolStripMenuItem_Click);
			// 
			// ͼ��ToolStripMenuItem
			// 
			this->ͼ��ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->�˳�ToolStripMenuItem });
			this->ͼ��ToolStripMenuItem->Name = L"ͼ��ToolStripMenuItem";
			this->ͼ��ToolStripMenuItem->Size = System::Drawing::Size(44, 21);
			this->ͼ��ToolStripMenuItem->Text = L"ѡ��";
			// 
			// �˳�ToolStripMenuItem
			// 
			this->�˳�ToolStripMenuItem->Name = L"�˳�ToolStripMenuItem";
			this->�˳�ToolStripMenuItem->Size = System::Drawing::Size(100, 22);
			this->�˳�ToolStripMenuItem->Text = L"�˳�";
			this->�˳�ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::�˳�ToolStripMenuItem_Click_1);
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
			this->Text = L"���ս���";
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
		//��ת�Ƕ�
		static int dAngle = 0;
		//���·�ת
		static int shangxiafanzhuan = 0;
		//���ҷ�ת
		static int zuoyoufanzhuan = 0;
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void onmyform_close(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
	private: System::Void OnMyForm_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ����Ƭ�ļ���ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void �˳�ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
			 void markfaces(System::Drawing::Bitmap ^% image);
	public : System::Void videoSourcePlayer_NewFrame(System::Object^ sender, System::Drawing::Bitmap^% image);
	private: System::Void ��ʱ��90ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ��ʱ��180ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ˳ʱ��90ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ˳ʱ��180ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ���ҷ�תToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ���·�תToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void �˳�ToolStripMenuItem_Click_1(System::Object^  sender, System::EventArgs^  e);
};
}
