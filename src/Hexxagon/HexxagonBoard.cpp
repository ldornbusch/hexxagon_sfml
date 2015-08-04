// HexxagonBoard.cpp: Implementierung der Klasse HexxagonBoard.
//
//////////////////////////////////////////////////////////////////////

#include "HexxagonBoard.h"
#include "..\ALL2DENGINE\ALL2D\ALL2D_System.h"
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
HexxagonBoard::HexxagonBoard():xContainer("HexxagonBoard")
{
	for (int x=0;x<HEX_BOARD_STONES;x++)
	{
		HexxagonStone* tmp=new HexxagonStone(x);
		vecStones.insert(vecStones.end(),tmp);
		add(*tmp);

	}
}

HexxagonBoard::~HexxagonBoard()
{
	for (int x=0;x<HEX_BOARD_STONES;x++)
	{
		HexxagonStone* tmp= vecStones[x];
		delete tmp;
	}

}
void HexxagonBoard::getGFX(Image &imgGFX)
{
	GameImageCloner::getGFX(imgGFX);

	for (int x=0;x<HEX_BOARD_STONES;x++)
	{
		vecStones[x]->getGFX(imgGFX);
	}
	positioner.PositionStones(vecStones);
}
// sets a color of a stone and according to this returns
// a vector of neighbours which have to switch their color too
vector<int> HexxagonBoard::setColor(int iIndex, int iColor)
{
	vector<int> retVal;
	if (vecStones[iIndex]){
		vecStones[iIndex]->setColor(iColor);
		retVal.insert(retVal.end(),iIndex);
		if (iColor!=0)
		{
			for (int x=0;x<HEX_NUM_STONE_NEIGHBOURS;x++)
			{
				int n=vecStones[iIndex]->getNeighbour(x);
				if (n!=-1){
					int tmpCol=vecStones[n]->getColor();
					if (tmpCol==-iColor){
						retVal.insert(retVal.end(),n);
					}
				}
			}
		}
	}
	return retVal;
}
void HexxagonBoard::setVisible(int iIndex, bool blnVisible)
{
	if (vecStones[iIndex])
		vecStones[iIndex]->setVisible(blnVisible);
}

// returns a vector with all indexes which have to be changed
// and the mov.moveType will be set appropriate
// HEX_NEAR_NEIGHBOUR	// for morphing into a new Field
// HEX_FAR_NEIGHBOUR	// for jumping into far Field
// HEX_NO_NEIGHBOUR		// illegal move
vector<int> HexxagonBoard::processMove(HexxagonMove& mov)
{
	vector<int> retVal;

	if (mov.from>=0 && mov.from<HEX_BOARD_STONES
		&& mov.to>=0 && mov.to<HEX_BOARD_STONES)
	{
		if (vecStones[mov.to]->getColor()==HEX_EMPTY_STONE)	// Feld unbesetzt?
		{
			mov.moveType=vecStones[mov.from]->isNeighbour(mov.to);
			switch (mov.moveType)
			{
			case HEX_NEAR_NEIGHBOUR:	// morph into Field
				retVal=setColor(mov.to,mov.Color);
				break;
			case HEX_FAR_NEIGHBOUR:		// jump into distant Field
				setColor(mov.from,0);
				retVal=setColor(mov.to,mov.Color);
				break;
			case HEX_NO_NEIGHBOUR:
			default:
				break;
			}
		}else{
			mov.moveType=HEX_NO_NEIGHBOUR;
		}
	}
	return retVal;
}

int HexxagonBoard::getColor(int iIndex)
{
	int retVal=-1;
	if (vecStones[iIndex]){
		retVal=vecStones[iIndex]->getColor();
	}
	return retVal;
}

void HexxagonBoard::reset()
{
	for (int x=0;x<HEX_BOARD_STONES;x++)
		vecStones[x]->setColor(0);
}

bool HexxagonBoard::hiLight(int iIndex, bool hilite)
{
	bool retVal=false;	// Falls die Figur keinen gueltigen Zug machen kann, wird false zurueckgegeben
	if (vecStones[iIndex])
	{
		if (hilite)	// Hilites setzen?
		{
			for (int x=0;x<HEX_NUM_STONE_NEIGHBOURS+HEX_NUM_STONE_DISTANT_NEIGHBOURS;x++)
			{
				int iNeighbour=vecStones[iIndex]->getNeighbour(x);
				if (iNeighbour!=-1)
				{
					if (vecStones[iNeighbour]->getColor()==HEX_EMPTY_STONE)
					{
						vecStones[iNeighbour]->setState((x<HEX_NUM_STONE_NEIGHBOURS)?HEX_STATE_NEIGHBOUR:HEX_STATE_FAR_NEIGHBOUR);
						retVal=true;
					}
				}
			}
			if (retVal)	// nur falls ein Zug moeglich ist, wird der State gesetzt, ansonsten wird false zurueckgegeben, was dem Aufrufer anzeigt das hier kein legaler Zug moeglich ist...
				vecStones[iIndex]->setState(HEX_STATE_SELECT);
		}else{	// , oder hilites loeschen
			vecStones[iIndex]->setState(HEX_STATE_NONE);
			for (int x=0;x<HEX_NUM_STONE_NEIGHBOURS+HEX_NUM_STONE_DISTANT_NEIGHBOURS;x++)
			{
				int iNeighbour=vecStones[iIndex]->getNeighbour(x);
				if (iNeighbour!=-1)
				{
					vecStones[iNeighbour]->setState(HEX_STATE_NONE);
				}
			}
		}
	}
	return retVal;
}

void HexxagonBoard::updateScore(HexxagonScore& scScore)
{
	int blue=0;//scScore.getPoints(HEX_BLUE_PLAYER);
	int red=0;//scScore.getPoints(HEX_RED_PLAYER);

	for (int x=0; x<HEX_BOARD_STONES;x++)
	{
		HexxagonStone* tmp = vecStones[x];
		if (tmp->getColor()==HEX_BLUE_PLAYER)
			blue++;
		if (tmp->getColor()==HEX_RED_PLAYER)
			red++;
	}

	scScore.setPoints(blue,HEX_BLUE_PLAYER);
	scScore.setPoints(red,HEX_RED_PLAYER);
}

vector<HexxagonMove> HexxagonBoard::getPossibleMoves(int iColor)
{
	vector<HexxagonMove> retVal;
	for (int x=0;x<HEX_BOARD_STONES;x++)
	{
		HexxagonStone* tmp = vecStones[x];
		if (tmp->getColor()==iColor)	// Wenn der zu untersuchende Stein die gleiche Farbe hat, wie die zu untersuchende Partei, merke alle moeglichen Zuege
		{
			for (int y=0;y<HEX_NUM_STONE_NEIGHBOURS;y++)	// check erstmal die Nahen Nachbarn
			{
				int iIndex=tmp->getNeighbour(y);
				if (iIndex>-1 && iIndex<HEX_BOARD_STONES)
				{
					if (vecStones[iIndex]->getColor()==HEX_EMPTY_STONE)	// Yooh.. der muss rein in den Vector
					{
						HexxagonMove	actMove;
						actMove.from=x;
						actMove.to=iIndex;
						actMove.Color=iColor;
						actMove.moveType=HEX_MOVE_DOUBLE;
// check if the move exist already:
						bool blnMoveExist=false;
						for (int a=0;a<retVal.size();a++)
						{
							HexxagonMove tmp=retVal[a];
							if (tmp.to==iIndex && tmp.moveType==HEX_MOVE_DOUBLE)
								blnMoveExist=true;
							break;
						}
	// if move doesn't exist, put it into vector
						if (!blnMoveExist)
							retVal.insert(retVal.begin(),actMove);
						retVal.insert(retVal.begin(),actMove);
					}
				}
			}
			for (int z=HEX_NUM_STONE_NEIGHBOURS;z<HEX_NUM_STONE_DISTANT_NEIGHBOURS;z++)	// nun die entfernten Nachbarn
			{
				int iIndex=tmp->getNeighbour(z);
				if (iIndex>-1 && iIndex<HEX_BOARD_STONES)
				{
					if (vecStones[iIndex]->getColor()==HEX_EMPTY_STONE)	// Yooh.. der muss rein in den Vector
					{
						HexxagonMove	actMove;
						actMove.from=x;
						actMove.to=iIndex;
						actMove.Color=iColor;
						actMove.moveType=HEX_MOVE_JUMP;

// check if the move exist already:
						bool blnMoveExist=false;
						for (int a=0;a<retVal.size();a++)
						{
							HexxagonMove tmp=retVal[a];
							if (tmp.to==iIndex && tmp.moveType==HEX_MOVE_DOUBLE)
								blnMoveExist=true;
							break;
						}
	// if move doesn't exist, put it into vector
						if (!blnMoveExist)
							retVal.insert(retVal.begin(),actMove);
					}
				}
			}
		}
	}
	return retVal;
}

vector<HexxagonStone*>& HexxagonBoard::getStones()
{
	return vecStones;
}
