#include "stdafx.h"
#include "FormsManager.h"


CFormsManager::CFormsManager()
{
}


CFormsManager::~CFormsManager()
{
}

void CFormsManager::ShowLogin()
{
	if (lf == nullptr) {
		lf = gcnew LoginForm;
		lf->LoginFinish += gcnew LoginFinishEventhandler(this,&CFormsManager::OnLoginFinish);		
	}
	lf->Show();
}

void CFormsManager::ShowMain(CPersonInfo ^ p)
{
	if (mf == nullptr) {
		mf = gcnew MainForm(p);
		mf->MainClose += gcnew MainCloseHandler(this,&CFormsManager::OnMainClose);
	}
	mf->Show();
}
void CFormsManager::ShowMain(System::Object ^ p)
{
	if (mf == nullptr) {
		mf = gcnew MainForm(safe_cast<CPersonInfo^>(p));
		mf->MainClose += gcnew MainCloseHandler(this,&CFormsManager::OnMainClose);
	}
	mf->Show();
}

void CFormsManager::OnLoginFinish(CPersonInfo ^ p)
{
	//MessageBox::Show("µÇÂ¼´°¿ÚÍê³É");
	if (p->Id!=0) {
		ShowMain(p);
		/*Threading::Thread^ app = gcnew Threading::Thread(gcnew Threading::ParameterizedThreadStart(this,&CFormsManager::ShowMain));
		app->SetApartmentState(Threading::ApartmentState::STA);
		app->Start(p);*/
	}
}

void CFormsManager::OnMainClose()
{
	mf->isneedask = 0;
	//Application::Exit();
	CConfigManager::Submit();
	Environment::Exit(0);
}
