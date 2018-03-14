#pragma once
#include "stdafx.h"

using namespace System::Collections::Generic;
using namespace System::Net;
using namespace System::Text;
using namespace System::Threading;

public delegate void ReplyHandler(String^ reply);
public ref class MyRequest {
public:
	MyRequest(String^ url, String^ data)
		:_url(url),_data(data) {};
	MyRequest(String^ url) 
		:_url(url){};
	MyRequest(String^ url, String^ data, Dictionary<String^, String^>^ dict) 
		:_url(url), _data(data),_dict(dict) {};
	MyRequest(String^ url, Dictionary<String^, String^>^ dict) 
		:_url(url), _dict(dict){};
	~MyRequest() {};
	String^ _url;
	String^ _data;
	Dictionary<String^, String^>^ _dict;
};
public ref class MyClient
{
public:
	MyClient();
	virtual ~MyClient();
	static event ReplyHandler^ Reply;
	static String^ Host = "http://127.0.0.1";
	static int port = 8765;
	static String^ RegisterPath = "";
	static void RegisterPerson(CPersonInfo^ cpi);
	static void RegisterPerson(String^ personjson);
	static void HttpPost(String ^ Url, String ^ postDataStr);
	static void HttpPost(String ^ Url, Dictionary<String^, String^>^ postDataDic);
	static void HttpPostDict(String ^ Url, Dictionary<String^, String^>^ postDataDic);
	static void HttpGet(String ^ url);
private:
	static String ^ HttpPostThread(String ^ Url, String ^ postDataStr);
	static String ^ HttpPostThread(String ^ Url, Dictionary<String^, String^>^ postDataDic);
	static String ^ HttpPostDictThread(String ^ Url, Dictionary<String^, String^>^ postDataDic);
	static String ^ HttpGetThread(String ^ url);
	//url+data
	static void HttpPost(Object^ o);
	//url+dict
	static void HttpPostDict(Object^ o);
	//url
	static void HttpGet(Object^ o);
};

