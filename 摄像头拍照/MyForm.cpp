#include "stdafx.h"
#include "MyForm.h"

#define ISRUN 1
#define ISSTOP 0

int camerastate = ISSTOP;

摄像头拍照::MyForm::MyForm(void)
{
	InitializeComponent();
	//
	//TODO:  在此处添加构造函数代码
	//
	this->videoSourcePlayer1->NewFrame -= gcnew VideoSourcePlayer::NewFrameHandler(this,&MyForm::videoSourcePlayer_NewFrame);
	this->videoSourcePlayer1->NewFrame += gcnew VideoSourcePlayer::NewFrameHandler(this,&MyForm::videoSourcePlayer_NewFrame);
	initfaceengine();
}

void 摄像头拍照::MyForm::takephoto()
{
	this->toolStripStatusLabel1->Text = L"正在拍照...";
	if (videoSource == nullptr)return;
	Bitmap ^bitmap = videoSourcePlayer1->GetCurrentVideoFrame();
	String^ fileName = DateTime::Now.ToString("yyyy-MM-dd-HH-mm-ss-ff") + ".bmp";
	bitmap->Save(fileName, ImageFormat::Bmp);
	this->toolStripStatusLabel1->Text = L"拍照成功，照片已保存";
	ShootFinish(fileName);
}

void 摄像头拍照::MyForm::startcapture()
{
	selectedDeviceIndex = this->comboBox1->SelectedIndex;
	if (selectedDeviceIndex == -1)throw gcnew Exception(L"未检测到摄像头");
	videoSource = gcnew VideoCaptureDevice(videoDevices[selectedDeviceIndex]->MonikerString);//连接摄像头。
	videoSource->VideoResolution = videoSource->VideoCapabilities[selectedDeviceIndex];
	videoSourcePlayer1->VideoSource = videoSource;
	// set NewFrame event handler
	
	videoSourcePlayer1->Start();
}

void 摄像头拍照::MyForm::stopcapture()
{
	if (camerastate == ISSTOP)return;
	videoSourcePlayer1->Stop();
	camerastate = ISSTOP;
}

void 摄像头拍照::MyForm::getcamerainfo()
{
	videoDevices = gcnew FilterInfoCollection(FilterCategory::VideoInputDevice);
	int dvs = videoDevices->Count;
	if (dvs > 0) {
		for each(FilterInfo^ device in videoDevices)
		{
			//this.comboBox_camera.Items.Add(device.Name);
			this->comboBox1->Items->Add(device->Name);
		}
		this->comboBox1->SelectedIndex = 0;
	}
}

System::Void 摄像头拍照::MyForm::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (camerastate == ISSTOP) {
		try {
			startcapture();
			this->button1->Text = L"关闭摄像头";
			camerastate = ISRUN;
			this->button2->Enabled = 1;
			this->comboBox1->Enabled = 0;
			toolStripStatusLabel1->Text = L"正在拍照..";
		}
		catch (Exception^ e) {
			MessageBox::Show(e->Message);
		}
		
	}
	else {
		stopcapture();
		this->button1->Text = L"打开摄像头";
		camerastate = ISSTOP;
		this->button2->Enabled = 0;
		this->comboBox1->Enabled = 1;
		toolStripStatusLabel1->Text = L"准备拍照..";
	}
}

System::Void 摄像头拍照::MyForm::button2_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (camerastate == ISSTOP)return;
	takephoto();
}
using namespace System::Windows;
System::Void 摄像头拍照::MyForm::onmyform_close(System::Object ^ sender, Forms::FormClosingEventArgs ^ e)
{
	CConfigManager::SaveValueLater("ShootForm_dAngle", dAngle);
	CConfigManager::SaveValueLater("ShootForm_zuoyoufanzhuan", zuoyoufanzhuan);
	CConfigManager::SaveValueLater("ShootForm_shangxiafanzhuan", shangxiafanzhuan);
	if (camerastate == ISSTOP) {
		//e->Cancel = 0;
	}
	else {
		Forms::DialogResult dr = MessageBox::Show("请是否关闭摄像头?", "提示:", MessageBoxButtons::OKCancel, MessageBoxIcon::Information);
		if (dr == Forms::DialogResult::OK) {
			stopcapture();
			camerastate = ISSTOP;
		}
		else if (dr == Forms::DialogResult::Cancel) {
			e->Cancel = 1;
		}
	}
}

System::Void 摄像头拍照::MyForm::OnMyForm_Load(System::Object ^ sender, System::EventArgs ^ e)
{
	this->toolStripStatusLabel1->Text = L"正在获取摄像头信息";
	getcamerainfo();
	this->toolStripStatusLabel1->Text = L"摄像头信息获取成功,请选择摄像头";
	dAngle = CConfigManager::LoadInt("ShootForm_dAngle");
	zuoyoufanzhuan = CConfigManager::LoadInt("ShootForm_zuoyoufanzhuan");
	shangxiafanzhuan = CConfigManager::LoadInt("ShootForm_shangxiafanzhuan");
}

System::Void 摄像头拍照::MyForm::打开照片文件夹ToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	String ^path=Environment::CurrentDirectory;
	//MessageBox::Show(path);
	Diagnostics::Process::Start("explorer.exe", path);
}

System::Void 摄像头拍照::MyForm::退出ToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	this->Close();
}
void drawgacesrecs(LPAFD_FSDK_FACERES facesrecs,byte* picstart, int bitcount, int linebytes, System::Drawing::Color c, int bordersize) {
	for (int i = 0;i < facesrecs->nFace;++i) {
		MRECT mrec = (facesrecs->rcFace)[i];
		System::Drawing::Rectangle rec;
		rec.X = mrec.left;
		rec.Y= mrec.top;
		rec.Width = mrec.right - mrec.left;
		rec.Height= mrec.bottom - mrec.top;
		drawrect(picstart, bitcount, linebytes, rec, c, bordersize);
	}
}
void 摄像头拍照::MyForm::markfaces(System::Drawing::Bitmap ^% yimage) {
	System::Drawing::Bitmap ^image = safe_cast<Bitmap^>(yimage->Clone());
	int h = image->Height,w= image->Width;
	System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, w, h);
	System::Drawing::Imaging::BitmapData^ bmpData =
		image->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, image->PixelFormat);
	IntPtr ptr = bmpData->Scan0;
	byte* p = (byte*)ptr.ToPointer();
	int bitcount = 3;
	int linebytes = (w + 3) / 4 * 4* bitcount;
	//dump(p, (image->Width* image->Height)*3, "1.bmp");
	//drawrect(p, bitcount, linebytes, System::Drawing::Rectangle(w/6,h/6,w*2/3,h*2/3), System::Drawing::Color::Red,4);
	LPAFD_FSDK_FACERES facesrecs=getfacesrecsbybmp24data(p, w, h);
	drawgacesrecs(facesrecs, p, bitcount, linebytes, System::Drawing::Color::Red, 4);
	image->UnlockBits(bmpData);
	pictureBox1->Image = image;
}
System::Void 摄像头拍照::MyForm::videoSourcePlayer_NewFrame(System::Object^ sender, System::Drawing::Bitmap ^% image)
{
	if (image != nullptr)
	{
		RotateFlipType pType = RotateFlipType::RotateNoneFlipNone;
		switch (dAngle) {
		case 0:
			pType = RotateFlipType::RotateNoneFlipNone;
			break;
		case 90:
			pType = RotateFlipType::Rotate90FlipNone;
			break;
		case 180:
			pType = RotateFlipType::Rotate180FlipNone;
			break;
		case 270:
			pType = RotateFlipType::Rotate270FlipNone;
			break;
		}
		if (zuoyoufanzhuan == 1) {
			pType = RotateFlipType::RotateNoneFlipX;
		}
		if (shangxiafanzhuan == 1) {
			pType = RotateFlipType::RotateNoneFlipY;
		}
		// 实时按角度绘制
		image->RotateFlip(pType);

		markfaces(image);
	}
}

System::Void 摄像头拍照::MyForm::逆时针90ToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	dAngle = dAngle - 90+360;
	dAngle = dAngle % 360;
}

System::Void 摄像头拍照::MyForm::逆时针180ToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	dAngle = dAngle - 180 + 360;
	dAngle = dAngle % 360;
}

System::Void 摄像头拍照::MyForm::顺时针90ToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	dAngle = dAngle +90;
	dAngle = dAngle % 360;
}

System::Void 摄像头拍照::MyForm::顺时针180ToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	dAngle = dAngle +180;
	dAngle = dAngle % 360;
}

System::Void 摄像头拍照::MyForm::左右翻转ToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	zuoyoufanzhuan = 1 - zuoyoufanzhuan;
}

System::Void 摄像头拍照::MyForm::上下翻转ToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	shangxiafanzhuan = 1 - shangxiafanzhuan;
}

System::Void 摄像头拍照::MyForm::退出ToolStripMenuItem_Click_1(System::Object ^ sender, System::EventArgs ^ e)
{
	this->Close();
}
