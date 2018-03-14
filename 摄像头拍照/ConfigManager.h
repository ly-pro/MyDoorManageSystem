#pragma once

using namespace System;
using namespace System::Data::SQLite;

public ref class CConfigManager
{
public:
	CConfigManager();
	virtual ~CConfigManager();
	//初始化数据库，是否使用安全模式，关闭可以大幅提升速度，但是意外情况容易丢失数据
	static void init(bool safe);
	static void cleanup();
	static String^ ConfigDB=L"config.db";
	static String^ LoadValue(String^ cfgname);
	static int LoadInt(String^ cfgname);
	static void SaveValue(String^ cfgname, String^ value);
	static void SaveValue(String^ cfgname, int value);
	static void SaveInt(String^ cfgname, int value);
	static SQLiteConnection ^m_dbConnection = nullptr;
	static void DeleteValue(String^ cfgname);
	static void DeleteValueLater(String^ cfgname);
	static void SaveValueLater(String^ cfgname, String^ value);
	static void SaveValueLater(String^ cfgname, int value);
	static void SaveIntLater(String^ cfgname, int value);
	static void Submit();
private:
	static String^ SubmitSql="begin;";
};

