// HexxagonScore.cpp: implementation of the HexxagonScore class.
//
//////////////////////////////////////////////////////////////////////

#include "hexxagonScore.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HexxagonScore::HexxagonScore()
{
	iPointBlue=0;
	iPointRed=0;
	strBluePlayer="DANIEL";
	strRedPlayer="LUTZ";
}

HexxagonScore::~HexxagonScore()
{

}

int HexxagonScore::getPoints(int iRequestedPlayer)
{
	int retVal=iPointRed;
	if (iRequestedPlayer==HEX_BLUE_PLAYER)
		retVal=iPointBlue;
	return retVal;
}

void HexxagonScore::setPoints(int iPoints,int iPlayer)
{
	if (iPlayer==HEX_BLUE_PLAYER)
		iPointBlue=iPoints;
	if (iPlayer==HEX_RED_PLAYER)
		iPointRed=iPoints;
}
