// HexxagonState.h: Schnittstelle für die Klasse HexxagonState.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXXAGONSTATE_H__92D02474_B3BE_4A4E_B6B1_D2049BC5F0C8__INCLUDED_)
#define AFX_HEXXAGONSTATE_H__92D02474_B3BE_4A4E_B6B1_D2049BC5F0C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<vector>
#include<string>
#include "HexxagonStone.h"

using namespace std;

class HexxagonState  
{
public:
	void setState(vector<HexxagonStone*>& vec, BYTE Player);	// speichert den State in diesem Object
	BYTE getState(vector<HexxagonStone*>& vec);	//rekonstruiert den State aus diesem Object..
	void load(string strFileName);
	void save(string strFileName);
	HexxagonState();
	virtual ~HexxagonState();
private:
	BYTE*	ptrBytes;
	BYTE bActivePlayer;
};

#endif // !defined(AFX_HEXXAGONSTATE_H__92D02474_B3BE_4A4E_B6B1_D2049BC5F0C8__INCLUDED_)
