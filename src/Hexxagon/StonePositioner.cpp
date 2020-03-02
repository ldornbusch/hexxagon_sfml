// StonePositioner.cpp: Implementierung der Klasse StonePositioner.
// Diese Klasse Uebernimmt die Positionierung der Steine und verkettet
// die Steine untereinander zu sog. Nachbarn.
// Es gibt zwei Arten von Nachbarn: 6 normale und 12 entfernte
// Diese sind den 4 Himmelsrichtungen nach benannt N E S W.
// die beiden Routinen
// Point Index2Coord(int iIndex)
// int   Coord2Index(Point ptPoint)
// wandeln den Index in Coordinaten und umgekehrt um s. ggf Dokumentation in Bildern
//////////////////////////////////////////////////////////////////////

#include "StonePositioner.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
#include "../All2DEngine/All2D/All2D_System.h"
#include "hexxagon_messages.h"

#define STONE_DISTANCE_X 48//72-->Fullscreen
#define STONE_DISTANCE_Y 16//28-->Fullscreen


StonePositioner::StonePositioner()
{

}

StonePositioner::~StonePositioner()
{

}

void StonePositioner::PositionStones(vector<HexxagonStone*> vecStones)
{
	const int scrX=All2D_System::fixedX;
	const int scrY=All2D_System::fixedY;

	int startX=scrX/2;
	int startY=(scrY-(16*STONE_DISTANCE_Y))/2;
	int iStoneIndex=0;
	int iY=startY;
	int iX;
	for (int row=0;row<17;row++)
	{
		int iCount=(row%2==0)?5:4;
		iX= startX-(iCount-1)*STONE_DISTANCE_X;
		for (int stone=0;stone<iCount;stone++)
		{
			if (isBlackOut(iStoneIndex))
			{
				vecStones[iStoneIndex]->setVisible(false);
			} else {
				vecStones[iStoneIndex]->setPosition(Rect(iX,iY));
				initializeNeighbours(vecStones[iStoneIndex],iStoneIndex,row);
			}
			iX+=2*STONE_DISTANCE_X;
			iStoneIndex++;
		}
		iY+=STONE_DISTANCE_Y;
	}
}

// checkt ob der Index zu einem DummyStone(unsichtbar) gehoert
bool StonePositioner::isBlackOut(int iIndex)
{
	bool retVal=false;
	int blackList[]={0,1,3,4,5,8,9,13,63,67,68,71,72,73,75,76}; //Indizes aller Dummy Felder, um das Feld rechteckig zu bekommen
	for (int x=0;x<16;x++){
		if (blackList[x]==iIndex){
			retVal=true;
			break;
		}
	}
	return retVal;
}

// Checkt, ob der index in der angegebenen Reihe zu finden ist(das array wrapped ja am Zeilenende, d.h der Letzte Stein einer Zeile stoesst zwar im Array an den ersten Stein der naechsten Zeile, deswegen sind sie aber keine Nachbarn
bool StonePositioner::isInLine(int iIndex, int iRow)
{
	bool retVal=false;
	int RowLen[]	={1,2, 3, 4, 5, 4, 5, 4, 5, 4, 5, 4, 5, 4, 3, 2, 1};	// Die Laenge der einzelnen Reihen des HexxagonSpielfeldes
	int startIndex[]={2,6,10,14,18,23,27,32,36,41,45,50,54,59,64,69,74}; // StartIndizes der SpielfeldSteine
	if (iRow>=0 && iRow<17 && !isBlackOut(iIndex))
		if (iIndex>=startIndex[iRow] && iIndex<startIndex[iRow]+RowLen[iRow])
			retVal=true;
	return retVal;
}

void StonePositioner::initializeNeighbours(HexxagonStone *objStone, int iIndex, int iRow)
{
// 6 direkte Nachbarn
	if(!isBlackOut(iIndex-9))
		objStone->setNeighbour( HEX_NORTH			, iIndex - 9);
	if (isInLine(iIndex-4,iRow-1))
		objStone->setNeighbour( HEX_NORTHEAST	, iIndex - 4);
	if (isInLine(iIndex+5,iRow+1))
		objStone->setNeighbour( HEX_SOUTHEAST	, iIndex + 5);
	if(!isBlackOut(iIndex+9))
		objStone->setNeighbour( HEX_SOUTH			, iIndex + 9);
	if (isInLine(iIndex+4,iRow+1))
		objStone->setNeighbour( HEX_SOUTHWEST	, iIndex + 4);
	if (isInLine(iIndex-5,iRow-1))
		objStone->setNeighbour( HEX_NORTHWEST	, iIndex - 5);

// 12 Entfernte Nachbarn
	if(!isBlackOut(iIndex-18))
		objStone->setNeighbour( HEX_NN				, iIndex -18);

	if (isInLine(iIndex-13,iRow-3))
		objStone->setNeighbour( HEX_NNE			, iIndex -13);
	if (isInLine(iIndex-8,iRow-2))
		objStone->setNeighbour( HEX_NEE			, iIndex - 8);
	if (isInLine(iIndex+1,iRow+0))
		objStone->setNeighbour( HEX_EE			, iIndex + 1);
	if (isInLine(iIndex+10,iRow+2))
		objStone->setNeighbour( HEX_SEE			, iIndex +10);
	if (isInLine(iIndex+14,iRow+3))
		objStone->setNeighbour( HEX_SSE			, iIndex +14);

	if(!isBlackOut(iIndex+18))
		objStone->setNeighbour( HEX_SS				, iIndex +18);

	if (isInLine(iIndex+13,iRow+3))
		objStone->setNeighbour( HEX_SSW			, iIndex +13);
	if (isInLine(iIndex+8,iRow+2))
		objStone->setNeighbour( HEX_SWW			, iIndex + 8);
	if (isInLine(iIndex-1,iRow+0))
		objStone->setNeighbour( HEX_WW			, iIndex - 1);
	if (isInLine(iIndex-10,iRow-2))
		objStone->setNeighbour( HEX_NWW			, iIndex -10);
	if (isInLine(iIndex-14,iRow-3))
		objStone->setNeighbour( HEX_NNW			, iIndex -14);

}
