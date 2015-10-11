// KeyboardNavigator.cpp: implementation of the KeyboardNavigator class.
//
//////////////////////////////////////////////////////////////////////

#include "KeyboardNavigator.h"
//#include "../Columns/ColumnsConstants.h"// 2DO: Abhaengigkeit auch hier raus.. wie bei MessageBox!

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

KeyboardNavigator::KeyboardNavigator()
{
	iMinMenuEntry=1;
	iMaxMenuEntry=1;
	iActualMenuEntry=1;
	iLastMenuEntry=1;
	blnUpDown=true;
}

KeyboardNavigator::~KeyboardNavigator()
{

}

void KeyboardNavigator::menuUp()
{
	iLastMenuEntry=iActualMenuEntry;
	iActualMenuEntry--;
	if (iActualMenuEntry<iMinMenuEntry)
		iActualMenuEntry=iMaxMenuEntry;
}
void KeyboardNavigator::menuDown()
{
	iLastMenuEntry=iActualMenuEntry;
	iActualMenuEntry++;
	if (iActualMenuEntry>iMaxMenuEntry)
		iActualMenuEntry=iMinMenuEntry;
}
void KeyboardNavigator::setActualEntry(int i)
{
	iLastMenuEntry=iActualMenuEntry;
	iActualMenuEntry=i;
}
int KeyboardNavigator::getActualEntry()
{
	return iActualMenuEntry;
}

void KeyboardNavigator::setMinEntry(int i)
{
	iMinMenuEntry=i;
}
int KeyboardNavigator::getMinEntry()
{
	return iMinMenuEntry;
}

void KeyboardNavigator::setMaxEntry(int i)
{
	iMaxMenuEntry=i;
}
int KeyboardNavigator::getMaxEntry()
{
	return iMaxMenuEntry;
}

int KeyboardNavigator::getLastEntry()
{
	return iLastMenuEntry;
}

bool KeyboardNavigator::handleEvent(Event *evt)
{
	bool retVal=false;	// wenn nix geändert wird, false zurueckgeben..kein Update notwendig
	switch(evt->Type)
	{
		case MM_KEYDOWN:
		{
			char a=(char)evt->wData;
			if (blnUpDown){
				switch (a) {
 					case sf::Keyboard::Up:
						menuUp();
						retVal=true;
						break;
					case sf::Keyboard::Down:
						menuDown();
						retVal=true;
							break;
					default:
						break;
					}
			} else {
				switch (a) {
					case sf::Keyboard::Left:
						menuUp();
						retVal=true;
						break;
					case sf::Keyboard::Right:
						menuDown();
						retVal=true;
							break;
					default:
						break;
					}
			}
		}
	}
	if (blnUpDown){
		if (evt->Type==MM_UP)
		{
			retVal=true;
			menuUp();
		}

		if (evt->Type==MM_DOWN)
		{
			retVal=true;
			menuDown();
		}
	}else {
		if (evt->Type==MM_LEFT)
		{
			retVal=true;
			menuUp();
		}

		if (evt->Type==MM_RIGHT)
		{
			retVal=true;
			menuDown();
		}
	}
	return retVal;
}

void KeyboardNavigator::setMenuDirection(bool isUpdown)
{
	blnUpDown=isUpdown;
}
