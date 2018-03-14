#include "stdafx.h"
#include "MyClient.h"

MyClient::MyClient()
{
}


MyClient::~MyClient()
{
}

void MyClient::RegisterPerson(CPersonInfo ^ cpi)
{
	RegisterPerson(cpi->ToJson());
}
void MyClient::HttpPost(String ^ Url, Dictionary<String^, String^>^ postDataDic) {
	Thread ^thread = gcnew Thread(gcnew ParameterizedThreadStart(MyClient::HttpPostDict));
	MyRequest^ mq = (gcnew MyRequest(Url, postDataDic));
	thread->Start((Object^)mq);
}
void MyClient::HttpPostDict(String ^ Url, Dictionary<String^, String^>^ postDataDic)
{
	Thread ^thread = gcnew Thread(gcnew ParameterizedThreadStart(MyClient::HttpPostDict));
	thread->Start((Object^)(gcnew MyRequest(Url,postDataDic)));
}
void MyClient::HttpGet(String ^ url)
{
	Thread ^thread = gcnew Thread(gcnew ParameterizedThreadStart(MyClient::HttpGet));
	thread->Start((Object^)(gcnew MyRequest(url)));
}
void MyClient::RegisterPerson(String ^ personjson)
{
	String^ Url = Host+":"+port +"/"+ RegisterPath;
	Dictionary<String^, String^>^ data = gcnew Dictionary<String^, String^>();
	data->Add("json", personjson);
	HttpPost(Url, data);
}

void MyClient::HttpPost(String ^ Url, String ^ postDataStr)
{
	Thread ^thread = gcnew Thread(gcnew ParameterizedThreadStart(MyClient::HttpPost));
	thread->Start((Object^)(gcnew MyRequest(Url,postDataStr)));
}

String ^ MyClient::HttpPostThread(String ^ Url, String ^ postDataStr)
{
	HttpWebRequest^ request = (HttpWebRequest^)WebRequest::Create(Url);
	request->Method = "POST";
	request->ContentType = "application/x-www-form-urlencoded";
	//WCHAR* ch2 = (WCHAR*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalUni(postDataStr);
	//request->ContentLength = wcslen(ch2)*sizeof(WCHAR);
	Stream ^myRequestStream = request->GetRequestStream();
	StreamWriter ^myStreamWriter = gcnew StreamWriter(myRequestStream, Encoding::GetEncoding("utf-8"));
	myStreamWriter->Write(postDataStr);
	myStreamWriter->Close();
	HttpWebResponse^ response = (HttpWebResponse^)request->GetResponse();
	Stream ^myResponseStream = response->GetResponseStream();
	StreamReader ^myStreamReader = gcnew StreamReader(myResponseStream, Encoding::GetEncoding("utf-8"));
	String ^retString = myStreamReader->ReadToEnd();
	myStreamReader->Close();
	myResponseStream->Close();
	return retString;
}

String ^ MyClient::HttpPostThread(String ^ Url, Dictionary<String^, String^>^ postDataDic)
{
	String ^param = L"";
	int f = -1;
	for each (auto var in postDataDic)
	{
		param += (++f ? L"&" : L"") + var.Key + L"=" + var.Value;
	}
	return HttpPostThread(Url, param);
}

String ^ MyClient::HttpPostDictThread(String ^ Url, Dictionary<String^, String^>^ postDataDic)
{
	return HttpPostThread(Url,postDataDic);
}

String ^ MyClient::HttpGetThread(String ^ url)
{
	HttpWebRequest ^request = (HttpWebRequest^)WebRequest::Create(url);
	request->Method = L"GET";
	request->ContentType = L"text/html;charset=UTF-8";
	request->UserAgent = R"_TWT_(Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.140 Safari/537.36)_TWT_";
	//request->Timeout = 5000;

	HttpWebResponse ^response = (HttpWebResponse^)request->GetResponse();
	Stream ^myResponseStream = response->GetResponseStream();
	StreamReader ^myStreamReader = gcnew StreamReader(myResponseStream, Encoding::GetEncoding(L"utf-8"));
	String ^retString = myStreamReader->ReadToEnd();
	myStreamReader->Close();
	myResponseStream->Close();

	return retString;
}

void MyClient::HttpPost(Object ^ o)
{
	MyRequest^ mq = safe_cast<MyRequest^>(o);
	String^ r = MyClient::HttpPostThread(mq->_url,mq->_data);
	Reply(r);
}

void MyClient::HttpPostDict(Object ^ o)
{
	MyRequest^ mq = safe_cast<MyRequest^>(o);
	String^ r = MyClient::HttpPostDictThread(mq->_url,mq->_dict);
	Reply(r);
}

void MyClient::HttpGet(Object ^ o)
{
	MyRequest^ mq = safe_cast<MyRequest^>(o);
	String^ r = MyClient::HttpGetThread(mq->_url);
	Reply(r);
}
