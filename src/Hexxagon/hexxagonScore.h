// hexxagonScore.h: interface for the hexxagonScore class.
// This is only a small container class for both scores and (maybe some additional infos, like playtime, etc)
//////////////////////////////////////////////////////////////////////
#pragma once

#include "hexxagon_messages.h"
#include <string>
using std::string;

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
