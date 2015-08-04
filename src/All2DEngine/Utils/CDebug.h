//////////////////////////////////////////////////////////
// Program   : CDebug class header file
// Author    : Daniel Chirca
// Email     : D.Chirca@finsiel.ro
// Note      : You need to use Debug.exe to intercept the messages
//////////////////////////////////////////////////////////

#if !defined(CDEBUG)
#define CDEBUG

#include <string>
using namespace std;

class CDebug
{
private:
	//internal data variables
//	COPYDATASTRUCT	cpData;
	char	szBuffer[255];
//	HWND		hWnd;
	int		nLevel;

	//internal class members
	bool SendData();
	bool GetDebugWindowHandle();

public:
	//public class members
	CDebug();
	~CDebug();

	//show level 0 debug messages
	bool Printf0(string szFormat, ...);
	bool Printf0(LPTSTR szFormat, ...);
	bool Printf0(LPCTSTR szFormat, ...);

	//show level 1 debug messages
	bool Printf1(string szFormat, ...);
	bool Printf1(LPTSTR szFormat, ...);
	bool Printf1(LPCTSTR szFormat, ...);

	//show level 2 debug messages
	bool Printf2(string szFormat, ...);
	bool Printf2(LPTSTR szFormat, ...);
	bool Printf2(LPCTSTR szFormat, ...);

	//show level 3 debug messages
	bool Printf3(string szFormat, ...);
	bool Printf3(LPTSTR szFormat, ...);
	bool Printf3(LPCTSTR szFormat, ...);
};

#endif
