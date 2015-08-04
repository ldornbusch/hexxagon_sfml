// KeyboardNavigator.h: interface for the KeyboardNavigator class.
// LUTZ(2002-06-05):This class manages the up and Downkeystroke to navigate through an 
// index.. You can set max and minimum indexes and if the user pushes 
// outside these  limits it will be wrapped around.. you can retrieve
// then the Index to check which menu item was highlighted..
// FOr pressing the SelectButton, the Class is not responsible..
// It manages only the up&Down Navigation..
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEYBOARDNAVIGATOR_H__4AE3A7BA_FD02_4FAE_AF14_367647A7E607__INCLUDED_)
#define AFX_KEYBOARDNAVIGATOR_H__4AE3A7BA_FD02_4FAE_AF14_367647A7E607__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../All2DEngine/All2D/All2D_Base/xElement.h"

class KeyboardNavigator  : public xElement
{
public:
	void setMenuDirection(bool isUpdown);
	virtual bool handleEvent(Event* evt);
	void setActualEntry(int i);
	int	 getActualEntry();
	void setMinEntry(int i);
	int	 getMinEntry();
	void setMaxEntry(int i);
	int	 getMaxEntry();
	int getLastEntry();
	
	KeyboardNavigator();
	virtual ~KeyboardNavigator();
private:
	bool blnUpDown;
	int iActualMenuEntry;
	int iLastMenuEntry;
	int iMinMenuEntry;
	int iMaxMenuEntry;
	void menuUp();
	void menuDown();
};

#endif // !defined(AFX_KEYBOARDNAVIGATOR_H__4AE3A7BA_FD02_4FAE_AF14_367647A7E607__INCLUDED_)
