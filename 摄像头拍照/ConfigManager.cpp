#include "stdafx.h"
#include "ConfigManager.h"


CConfigManager::CConfigManager()
{
	m_dbConnection = gcnew SQLiteConnection("Data Source=config.db;Version=3;");
	m_dbConnection->Open();
	String ^sql = "create table if not exists appconfig (name varchar(255), value varchar(255))";
	SQLiteCommand^ command = gcnew SQLiteCommand(sql, m_dbConnection);
	command->ExecuteNonQuery();
}


CConfigManager::~CConfigManager()
{
	m_dbConnection->Close();
}

void CConfigManager::init(bool safe)
{
	m_dbConnection = gcnew SQLiteConnection("Data Source=config.db;Version=3;");
	m_dbConnection->Open();
	String ^sql = "";
	if(!safe)sql += "PRAGMA synchronous = OFF; ";
	sql+="create table if not exists appconfig (name varchar(255), value varchar(255));";
	SQLiteCommand^ command = gcnew SQLiteCommand(sql, m_dbConnection);
	command->ExecuteNonQuery();
}

void CConfigManager::cleanup()
{
	m_dbConnection->Close();
}

String ^ CConfigManager::LoadValue(String ^ cfgname)
{
	//CConfigManager();
	String^ sql = "select value from appconfig where `name`='"+cfgname+"' limit 1";
	SQLiteCommand^ command = gcnew SQLiteCommand(sql, m_dbConnection);
	SQLiteDataReader ^reader = command->ExecuteReader();
	String ^v;
	while (reader->Read()) {
		v = reader->GetString(0);
	}
	return v;
}

int CConfigManager::LoadInt(String ^ cfgname)
{
	String^ sql = "select value from appconfig where `name`='" + cfgname + "' limit 1";
	SQLiteCommand^ command = gcnew SQLiteCommand(sql, m_dbConnection);
	SQLiteDataReader ^reader = command->ExecuteReader();
	String ^v;
	while (reader->Read()) {
		v = reader->GetString(0);
	}
	int i = 0;
	Int32::TryParse(v, i);
	return i;
}

void CConfigManager::SaveValue(String ^ cfgname, String ^ value)
{
	//CConfigManager();
	String^ sql = "replace into appconfig( name ,value ) VALUES ( '"+cfgname+"','"+value+"')";
	SQLiteCommand^ command = gcnew SQLiteCommand(sql, m_dbConnection);
	command->ExecuteNonQuery();
}

void CConfigManager::SaveValue(String ^ cfgname, int value)
{
	SaveInt(cfgname, value);
}

void CConfigManager::SaveInt(String ^ cfgname, int value)
{
	String^ sql = "replace into appconfig( name ,value ) VALUES ( '" + cfgname + "'," + value + ");";
	SQLiteCommand^ command = gcnew SQLiteCommand(sql, m_dbConnection);
	command->ExecuteNonQuery();
}

void CConfigManager::DeleteValue(String ^ cfgname)
{
	String^ sql = "DELETE FROM appconfig WHERE name='" + cfgname + "';";
	SQLiteCommand^ command = gcnew SQLiteCommand(sql, m_dbConnection);
	command->ExecuteNonQuery();
}

void CConfigManager::DeleteValueLater(String ^ cfgname)
{
	SubmitSql += "DELETE FROM appconfig WHERE name='" + cfgname + "';";
}

void CConfigManager::SaveValueLater(String ^ cfgname, String ^ value)
{
	SubmitSql+= "replace into appconfig( name ,value ) VALUES ( '" + cfgname + "','" + value + "');";
}

void CConfigManager::SaveValueLater(String ^ cfgname, int value)
{
	SaveIntLater(cfgname,value);
}

void CConfigManager::SaveIntLater(String ^ cfgname, int value)
{
	SubmitSql+= "replace into appconfig( name ,value ) VALUES ( '" + cfgname + "'," + value + ");";
}

void CConfigManager::Submit()
{
	SubmitSql += "commit;";
	SQLiteCommand^ command = gcnew SQLiteCommand(SubmitSql, m_dbConnection);
	command->ExecuteNonQuery();
	SubmitSql = "begin;";
}

