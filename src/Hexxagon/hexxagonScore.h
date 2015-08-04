// hexxagonScore.h: interface for the hexxagonScore class.
// This is only a small container class for both scores and (maybe some additional infos, like playtime, etc)
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXXAGONSCORE_H__22106CFD_6508_43BC_865C_805A1DB65959__INCLUDED_)
#define AFX_HEXXAGONSCORE_H__22106CFD_6508_43BC_865C_805A1DB65959__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Hexxagon_messages.h"
#include <string>
using namespace std;
class HexxagonScore  
{
public:
	string strBluePlayer;
	string strRedPlayer;
	void setPoints(int iPoints,int iPlayer=HEX_RED_PLAYER);
	int getPoints(int iRequestedPlayer=HEX_RED_PLAYER);
	HexxagonScore();
	virtual ~HexxagonScore();

private:
	int iPointRed;
	int iPointBlue;
};

#endif // !defined(AFX_HEXXAGONSCORE_H__22106CFD_6508_43BC_865C_805A1DB65959__INCLUDED_)
