#pragma once

using namespace System;

public ref class CPersonInfo
{
public:
	property String^ Name;
	property int Id;
	property String^ Contact;
	property int Type;
	CPersonInfo();
	CPersonInfo(int id,String^ name,String^ contact,int type);
	CPersonInfo(int id);
	static CPersonInfo^ LoadFromJson(String^ json);
	static String^ ToJson(CPersonInfo^ cdi);
	String^ ToJson();
	virtual ~CPersonInfo();
};

