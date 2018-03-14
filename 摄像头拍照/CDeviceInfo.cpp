#include "stdafx.h"
#include "CDeviceInfo.h"


CDeviceInfo::CDeviceInfo()
{
}

CDeviceInfo::CDeviceInfo(int id, int houseid)
{
	Id = id;
	HouseId = houseid;
}


CDeviceInfo^ CDeviceInfo::LoadFromJson(String ^ json)
{
	JObject^ o = JObject::Parse(json);
	int id = (int)o["id"];
	int p=(int)o["houseid"];
	return gcnew CDeviceInfo(id,p);
}

String ^ CDeviceInfo::ToJson(CDeviceInfo ^ cdi)
{
	JObject ^o = gcnew JObject();
	o["id"] = cdi->Id;
	o["place"] = cdi->HouseId;
	String^ json = o->ToString();
	return json;
}

String ^ CDeviceInfo::ToJson()
{
	JObject ^o = gcnew JObject();
	o["id"] = Id;
	o["place"] = HouseId;
	String^ json = o->ToString();
	return json;
}

CDeviceInfo::~CDeviceInfo()
{
}
