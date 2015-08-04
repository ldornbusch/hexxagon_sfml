// xRegistry.h: interface for the xRegistry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XREGISTRY_H__0AC473F7_FD16_4283_B53A_E7E2EAD388A3__INCLUDED_)
#define AFX_XREGISTRY_H__0AC473F7_FD16_4283_B53A_E7E2EAD388A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_XREGISTRY_H__0AC473F7_FD16_4283_B53A_E7E2EAD388A3__INCLUDED_)
