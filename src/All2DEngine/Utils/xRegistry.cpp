// xRegistry.cpp: implementation of the xRegistry class.
//
//////////////////////////////////////////////////////////////////////

#include "xRegistry.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

xRegistry::xRegistry(std::string key, HKEY root)
{
	// set defaults
	hRoot		= HKEY_LOCAL_MACHINE;
	strKey	= "Software";

	// set user params
	setRoot(root);
	setKey(key);
}

xRegistry::~xRegistry()
{

}

/*
 * get(name,defaultValue,create)
 * get string value with given name
 * ----------------------------------------------
 * retreives the registry value for the entry
 * with requested name using root and key
 * if no entry exists the default value is returned
 * if create is true (default) the key will be created
 */
std::string xRegistry::get(std::string name, std::string defaultValue, bool create)
{
	HKEY hKey;								// handle to found key

	// open registry key
	LONG lRet = RegOpenKeyEx(
		hRoot,									// handle to open key
		strKey.c_str(),					// address of name of subkey to open
		0,											// reserved options
		KEY_ALL_ACCESS,					// security access mask
		&hKey										// address of handle to open key
	);

	// return default if key couldn't be opened
	if ( lRet != ERROR_SUCCESS ) {
		if (hKey)		lRet = RegCloseKey(hKey);
		if (create)	set( name, defaultValue );
		return defaultValue;
	}

	// receiving vars vor registry value, size and type
	unsigned long	iKeyValSize = 1024;
	unsigned long	lpType = REG_SZ;

	// retreive size of value for given name
	lRet = RegQueryValueEx(
		hKey,										// handle to key to query
		name.c_str(),						// address of name of value to query
		0,											// reserved
		&lpType,								// address of buffer for value type
		NULL,										// NULL since we only want buffer size
		&iKeyValSize						// address of data buffer size
	);

	unsigned char* tmpVal = new unsigned char[iKeyValSize];

	// retreive value for given name
	lRet = RegQueryValueEx(
		hKey,										// handle to key to query
		name.c_str(),						// address of name of value to query
		0,											// reserved
		&lpType,								// address of buffer for value type
		tmpVal,									// address of data buffer
		&iKeyValSize						// address of data buffer size
	);

	// return default if value couldn't be retreived
	if ( lRet != ERROR_SUCCESS ) {
		lRet = RegCloseKey(hKey);
		delete tmpVal;
		if ( create ) set( name, defaultValue );
		return defaultValue;
	}

	std::string value = "";		// the value we want

	// get only if type is string
	if( lpType==REG_SZ || lpType==REG_EXPAND_SZ )
		value.assign((const char*)tmpVal);

	// free resources
	delete tmpVal;
	lRet = RegCloseKey(hKey);

	// return value
	return value;
}


/*
 * get(name,defaultValue,create)
 * get unsigned long value with given name
 * ----------------------------------------------
 * retreives the registry value for the entry
 * with requested name using root and key
 * if no entry exists the default value is returned
 * if create is true (default) the key will be created
 */
DWORD xRegistry::get(std::string name, DWORD defaultValue, bool create)
{
	HKEY hKey;								// handle to found key

	// open registry key
	LONG lRet = RegOpenKeyEx(
		hRoot,									// handle to open key
		strKey.c_str(),					// address of name of subkey to open
		0,											// reserved options
		KEY_ALL_ACCESS,					// security access mask
		&hKey										// address of handle to open key
	);

	// return default if key couldn't be opened
	if ( lRet != ERROR_SUCCESS ) {
		if (hKey)		lRet = RegCloseKey(hKey);
		if (create)	set( name, defaultValue );
		return defaultValue;
	}

	// receiving vars vor registry value, size and type
	unsigned long	lpType = REG_DWORD;
	DWORD	tmpVal;
	unsigned long	iKeyValSize = sizeof(tmpVal);

	// retreive value for given name
	lRet = RegQueryValueEx(
		hKey,										// handle to key to query
		name.c_str(),						// address of name of value to query
		0,											// reserved
		&lpType,								// address of buffer for value type
		(BYTE *) &tmpVal,				// address of data buffer
		&iKeyValSize						// address of data buffer size
	);

	// return default if value couldn't be retreived
	if ( lRet != ERROR_SUCCESS ) {
		lRet = RegCloseKey(hKey);
		//delete tmpVal;
		if ( create ) set( name, defaultValue );
		return defaultValue;
	}

	DWORD value = defaultValue;	// the value we want

	// only get if we have an unsigned long
	if (lpType==REG_DWORD)
			value = tmpVal;

	// free resources
	//delete tmpVal;
	lRet = RegCloseKey(hKey);

	// return value
	return value;
}


/*
 * set(name,value) : set name with given value
 * ----------------------------------------------
 * updates/creates the registry value for the entry
 * with requested name using root and key
 */
bool xRegistry::set(std::string name, std::string value)
{
	HKEY								hKey;	// handle to found key
	DWORD								hDepth;

	// create security attributes
	SECURITY_ATTRIBUTES sa;
	sa.nLength = 50;
	sa.lpSecurityDescriptor = 0;
	sa.bInheritHandle = true;

    char str_class[] = "REG_SZ";
	// open/create registry key
	LONG lRet = RegCreateKeyEx(
		hRoot,									// handle to an open key
		strKey.c_str(),         // address of subkey name
		0,											// reserved
		str_class,								// address of class string
		REG_OPTION_NON_VOLATILE,// special options flag
		KEY_ALL_ACCESS,					// desired security access
		&sa,										// address of key security structure
		&hKey,									// address of buffer for opened handle
		(LPDWORD)&hDepth				// address of disposition value buffer
	);

	// return empty string if key couldn't be opened
	if ( lRet != ERROR_SUCCESS ) {
		if (hKey) lRet = RegCloseKey(hKey);
		return false;
	}

	// avoid empty strings for RegSetValueEx()
	if (value.length()<1)
		value = " ";

	// set value for given name
	lRet = RegSetValueEx(
		hKey,										// handle to key to set value for
		name.c_str(),						// name of the value to set
		0,											// reserved
		REG_SZ,									// flag for value type
		(const unsigned char *)value.c_str(),
														// address of value data
		value.length()					// size of value data
	);

	// close key and return result
	lRet = RegCloseKey(hKey);
	return (lRet==ERROR_SUCCESS);
}


/*
 * set(name,value) : set name with given value
 * ----------------------------------------------
 * updates/creates the registry value for the entry
 * with requested name using root and key and DWORD value
 */
bool xRegistry::set(std::string name, DWORD value)
{
	HKEY								hKey;	// handle to found key
	DWORD								hDepth;

	// create security attributes
	SECURITY_ATTRIBUTES sa;
	sa.nLength = 50;
	sa.lpSecurityDescriptor = 0;
	sa.bInheritHandle = true;

    char str_class[] = "REG_DWORD";
	// open/create registry key
	LONG lRet = RegCreateKeyEx(
		hRoot,									// handle to an open key
		strKey.c_str(),         // address of subkey name
		0,											// reserved
		str_class,						// address of class string
		REG_OPTION_NON_VOLATILE,// special options flag
		KEY_ALL_ACCESS,					// desired security access
		&sa,										// address of key security structure
		&hKey,									// address of buffer for opened handle
		(LPDWORD)&hDepth				// address of disposition value buffer
	);

	// return empty string if key couldn't be opened
	if ( lRet != ERROR_SUCCESS ) {
		if (hKey)
			lRet = RegCloseKey(hKey);
		return false;
	}

	// set value for given name
	lRet = RegSetValueEx(
		hKey,										// handle to key to set value for
		name.c_str(),						// name of the value to set
		0,											// reserved
		REG_DWORD,							// flag for value type
		(unsigned char*)&value,
														// address of value data
		sizeof(value)						// size of value data
	);

	// close key and return result
	lRet = RegCloseKey(hKey);
	return (lRet==ERROR_SUCCESS);
}


/*
 * setRoot(root) ; sets the registry root
 * --------------------------------------------------
 * sets the default registry root to the given root
 * if the parameter is a valid root key
 */
void xRegistry::setRoot(HKEY root)
{
	// check if in range
	if (root>=HKEY_CLASSES_ROOT && root<=HKEY_PERFORMANCE_DATA)
		hRoot = root;
}


/*
 * setKey(key) ; sets the registry key
 * --------------------------------------------------
 * sets the default registry key to the given key
 * if the parameter is a non empty key string
 */
void xRegistry::setKey(std::string key)
{
	// check if string is passed
	// do not allow empty strings
	if (key.length() > 0)
		strKey = key;
}
