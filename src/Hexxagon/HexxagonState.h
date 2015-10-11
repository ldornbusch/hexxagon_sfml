// HexxagonState.h: Schnittstelle für die Klasse HexxagonState.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include<vector>
#include<string>
#include "HexxagonStone.h"
typedef unsigned char BYTE;
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
