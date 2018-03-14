#include "stdafx.h"
#include "CPersonInfo.h"


CPersonInfo::CPersonInfo()
{
	Id = 0;
}

CPersonInfo::CPersonInfo(int id, String ^ name, String ^ contact,int type)
{
	Name = name;
	Id = id;
	Contact = contact;
	Type = type;
}

CPersonInfo::CPersonInfo(int id)
{
	Id = id;
}

CPersonInfo ^ CPersonInfo::LoadFromJson(String ^ json)
{
	JObject^ o = JObject::Parse(json);
	int id = (int)o["id"];
	return gcnew CPersonInfo();
}

String ^ CPersonInfo::ToJson(CPersonInfo ^ cpi)
{
	JObject ^o = gcnew JObject();
	o["id"] = cpi->Id;
	String^ json = o->ToString();
	return json;
}

String ^ CPersonInfo::ToJson()
{
	JObject ^o = gcnew JObject();
	o["id"] = Id;
	o["name"] = Name;
	o["contact"] = Contact;
	o["type"] = Type;
	String^ json = o->ToString();
	return json;
}


CPersonInfo::~CPersonInfo()
{
}
