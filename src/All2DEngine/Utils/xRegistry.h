// xRegistry.h: interface for the xRegistry class.
//
//////////////////////////////////////////////////////////////////////


#pragma once

// TODO: Remove win-shit
#include <windows.h>
#include <string>


class xRegistry
{
public:

	bool set(std::string name, std::string value);
	bool set(std::string name, DWORD value);

	std::string get(std::string name, std::string defaultValue="", bool create=true);
	DWORD get(std::string name, DWORD defaultValue, bool create=true);

	void setKey(std::string key);
	void setRoot(HKEY root);

	xRegistry(std::string key="",HKEY root=HKEY_LOCAL_MACHINE);
	virtual ~xRegistry();

private:
	std::string strKey;
	HKEY hRoot;
};
