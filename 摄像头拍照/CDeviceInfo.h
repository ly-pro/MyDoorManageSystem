#pragma once

using namespace Newtonsoft::Json::Linq;

public ref class CDeviceInfo
{
public:
	CDeviceInfo();
	CDeviceInfo(int id,int houseid);
	property int Id;
	property int HouseId;
	static CDeviceInfo^ LoadFromJson(String^ json);
	static String^ ToJson(CDeviceInfo^ cdi );
	String^ ToJson();
	virtual ~CDeviceInfo();
};

