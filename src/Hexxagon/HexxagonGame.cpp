// HexxagonGame.cpp: implementation of the HexxagonGame class.
//
//////////////////////////////////////////////////////////////////////

#include "HexxagonGame.h"
#include "../All2DEngine/All2D/All2D_Events/MessageManager.h"
#include "../All2DEngine/All2D/All2D_System.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define SUGGEST_TIME 4000

HexxagonGame::HexxagonGame():xContainer("Game")
{
	iPlayer=HEX_RED_PLAYER;
	iGameStatus=HEX_WAIT_FOR_CLICK_1;
	setBeginner();
}

HexxagonGame::~HexxagonGame()
{

}
void HexxagonGame::getGFX(Image &imgGFX)
{
	GameImageCloner::getGFX(imgGFX);
	hexBoard.getGFX(imgElements);
	myFont.cloneImage(imgGFX,Rect(192,0,160,80));
	myFont.FontInit(16,16,10,"ABCDEFGHIJKLMNOPQRSTUVWXYZ ,.-0123456789");

	sprtWinner.cloneImage(imgElements);
	sprtWinner.setPosition(0,0,640,480);
	sprtWinner.setPriority(15);
	hex3DPlayer.setBoard(&hexBoard);

	add(hexBoard);
	add(hex3DPlayer);
	hexBoard.reset();
}


bool HexxagonGame::handleEvent(Event *evt)
{
	switch(evt->Type)
	{
	case HX_FIELD_CLICK:
		switch(iGameStatus){
		case HEX_WAIT_FOR_CLICK_1:
			if (hexBoard.getColor(evt->wData)==iPlayer)
			{
				if (hexBoard.hiLight(evt->wData))
				{
					actualMove.from=evt->wData;
					iGameStatus=HEX_WAIT_FOR_CLICK_2;
				}
			}
			break;
		case HEX_WAIT_FOR_CLICK_2:
			if ((int)evt->wData==-1){
				hexBoard.hiLight(actualMove.from,false);
				actualMove.from=-1;
				iGameStatus=HEX_WAIT_FOR_CLICK_1;
			} else {
				actualMove.to=evt->wData;
				actualMove.Color=iPlayer;
				vec2Flip=hexBoard.processMove(actualMove);
				hexBoard.hiLight(actualMove.from,false);
				if (actualMove.moveType==HEX_NO_NEIGHBOUR)
				{
					// Ungueltiger Zug, nochmal clicken
					iGameStatus=HEX_WAIT_FOR_CLICK_1;
				} else {
					// Wenn Zug gueltig, Player wechseln
					iGameStatus=HEX_WAIT_FOR_UPDATE;
					MessageManager::handleEvent(new Event(HEX_MOUSE_CHANGE,2,0));
				}
			}

			break;
		case HEX_SUGGEST_MOVE:
			if (hexBoard.getColor(evt->wData)==iPlayer)
			{
				unSuggest();
				if (hexBoard.hiLight(evt->wData))
				{
					actualMove.from=evt->wData;
					iGameStatus=HEX_WAIT_FOR_CLICK_2;
				}
			}
			break;
		default:
			break;
		}
		break;
	}
	if (isRunning())
		return xContainer::handleEvent(evt);
	else
		return false;
}

void HexxagonGame::setBeginner(int beginner)
{
	if (beginner!=HEX_RED_PLAYER)
		iBeginner=HEX_BLUE_PLAYER;
	else
		iBeginner=HEX_RED_PLAYER;
}
void HexxagonGame::reset()
{
	for (unsigned int x=0;x<vecMoves.size();x++)
	{
		delete vecMoves[x];
	}
	vecMoves.clear();

	hexBoard.reset();
	iPlayer=iBeginner;
	iGameStatus=HEX_WAIT_FOR_CLICK_1;
	MessageManager::handleEvent(new Event(HEX_MOUSE_CHANGE,iPlayer,0));

	hexBoard.setVisible(33,false);
	hexBoard.setVisible(34,false);
	hexBoard.setVisible(47,false);
	hexBoard.setColor(2,1);
	hexBoard.setColor(54,1);
	hexBoard.setColor(58,1);
	hexBoard.setColor(18,-1);
	hexBoard.setColor(22,-1);
	hexBoard.setColor(74,-1);

	HexxagonState*	tmp=new HexxagonState();
	tmp->setState(getBoard().getStones(), (BYTE)iPlayer);
	vecMoves.push_back(tmp);
}

bool HexxagonGame::paint(Image& backBuffer)
{
	iGameStatus = update();
	hexBoard.updateScore(scScore);
	printScore(backBuffer);
	xContainer::paint(backBuffer);
	if (iGameStatus==HEX_RED_WIN)
	{
		sprtWinner.setSrcRect(Rect(0,1440,640,480));
		sprtWinner.show(backBuffer,IMAGE_BLTMODE_HALF);
	}
	if (iGameStatus==HEX_BLUE_WIN)
	{
		sprtWinner.setSrcRect(Rect(0,960,640,480));
		sprtWinner.show(backBuffer,IMAGE_BLTMODE_HALF);
	}
	if (iGameStatus==HEX_NO_WIN)
	{
		sprtWinner.setSrcRect(Rect(0,1920,640,480));
		sprtWinner.show(backBuffer,IMAGE_BLTMODE_HALF);
	}
	return true;
}

int HexxagonGame::update()
{
	if (vec2Flip.size()>0)	// Hier werden die einzelnen Spielfelder geflipt, einer nach dem anderen
	{
		// Check if a specific Amount of time has passed, before excuting next Flip
		static int timeNow=0;
		if (All2D_System::getTime()-timeNow > (actualMove.moveType==HEX_FAR_NEIGHBOUR?20:50))
		{
			int iIndex=vec2Flip[0];
			hexBoard.setColor(iIndex,iPlayer);
			vec2Flip.erase(vec2Flip.begin());
			timeNow=All2D_System::getTime();

			// Check if this was the last flip and set/restore normal gamestate
			if (vec2Flip.size()==0)
			{
				if (iGameStatus!=HEX_FILL_UP)
				{
					if (hexBoard.getPossibleMoves(iPlayer).size()==0)	// GAme Over fuer actuellen Player?
					{
						iGameStatus=HEX_FILL_UP;	// letzten Felder auffuellen..
						iPlayer*=-1;
					} else {
						iPlayer*=-1;
						if (hexBoard.getPossibleMoves(iPlayer).size()==0)	// GAme Over fuer naechsten Player?
						{
							iGameStatus=HEX_FILL_UP;	// letzten Felder auffuellen..
							iPlayer*=-1;
						} else {						// Spieler Wechseln........
							MessageManager::handleEvent(new Event(HEX_MOUSE_CHANGE,iPlayer,0));
							HexxagonState*	tmp=new HexxagonState();
							tmp->setState(getBoard().getStones(), (BYTE)iPlayer);
							vecMoves.push_back(tmp);
							iGameStatus=HEX_WAIT_FOR_CLICK_1;
						}
					}
				}
			}
		}
	}else {
		if (iGameStatus==HEX_FILL_UP)
		{
			actualMove=hexAI.getBestMove(iPlayer, hexBoard.getStones());
			if (actualMove.from==-1 || actualMove.to==-1){
				if (scScore.getPoints(HEX_RED_PLAYER) > scScore.getPoints(HEX_BLUE_PLAYER))
					iGameStatus=HEX_RED_WIN;
				if (scScore.getPoints(HEX_RED_PLAYER) < scScore.getPoints(HEX_BLUE_PLAYER))
					iGameStatus=HEX_BLUE_WIN;
				if (scScore.getPoints(HEX_RED_PLAYER) == scScore.getPoints(HEX_BLUE_PLAYER))
					iGameStatus=HEX_NO_WIN;
				MessageManager::handleEvent(new Event(HEX_MOUSE_CHANGE,2,0));
			}else
				vec2Flip=hexBoard.processMove(actualMove);
		}
	}
	if (iGameStatus==HEX_SUGGEST_MOVE)	// Blinken!
	{
		int iSuggestTime=All2D_System::getTime() - iSuggestTimeStart;
		if ( iSuggestTime > SUGGEST_TIME)
			unSuggest();
		else {
			if ((iSuggestTime/500)%2==0)
			{
				getBoard().getStones()[suggestedMove.from]->setState(HEX_STATE_SELECT);
				getBoard().getStones()[suggestedMove.to]->setState(HEX_STATE_HOVER);
			}else{
				getBoard().getStones()[suggestedMove.from]->setState(HEX_STATE_NONE);
				getBoard().getStones()[suggestedMove.to]->setState(HEX_STATE_NONE);
			}
		}
	}
	return iGameStatus;
}

void HexxagonGame::printScore(Image& backBuffer)
{
	char buffer[40];
	Image tmp;
	tmp.cloneImage(backBuffer,Rect(20,20,280,40));
	tmp.clear(0xcccc00);
	myFont.PrintCenter(tmp,4,scScore.strRedPlayer.c_str(),IMAGE_BLTMODE_SUB);
	sprintf(buffer,"%d",scScore.getPoints(HEX_RED_PLAYER));
	myFont.PrintCenter(tmp,22,buffer,IMAGE_BLTMODE_SUB);

	tmp.cloneImage(backBuffer,Rect(340,20,280,40));
	tmp.clear(0x000033);
	myFont.PrintCenter(tmp,4,scScore.strBluePlayer. c_str());
	sprintf(buffer,"%d",scScore.getPoints(HEX_BLUE_PLAYER));
	myFont.PrintCenter(tmp,22,buffer);

}

HexxagonBoard& HexxagonGame::getBoard()
{
	return hexBoard;
}

HexxagonScore& HexxagonGame::getScore()
{
	return scScore;
}

void HexxagonGame::load(string strFileName)
{
	HexxagonState state;
	state.load(strFileName);
	iPlayer=state.getState(hexBoard.getStones());
	iGameStatus=HEX_WAIT_FOR_CLICK_1;
	MessageManager::handleEvent(new Event(HEX_MOUSE_CHANGE,iPlayer,0));
}

void HexxagonGame::save(string strFileName)
{
	HexxagonState state;
	state.setState(hexBoard.getStones(), iPlayer);
	state.save(strFileName);
}

int HexxagonGame::getState()
{
	return iGameStatus;
}

void HexxagonGame::undoMove()
{
	if (vecMoves.size()>1)
	{
		HexxagonState* tmp=vecMoves[vecMoves.size()-1];
		delete tmp;
		vecMoves.pop_back();
		HexxagonState*	state=vecMoves[vecMoves.size()-1];	// last Move in Vector
		iPlayer=state->getState(hexBoard.getStones());
		if (iPlayer>1)
			iPlayer=-1;
		iGameStatus=HEX_WAIT_FOR_CLICK_1;
		MessageManager::handleEvent(new Event(HEX_MOUSE_CHANGE,iPlayer,0));
	}
}

void HexxagonGame::suggestMove()
{
	iGameStatus=HEX_SUGGEST_MOVE;
	suggestedMove=hexAI.getBestMove(iPlayer,getBoard().getStones());
	iSuggestTimeStart=All2D_System::getTime();
	getBoard().getStones()[suggestedMove.from]->setState(HEX_STATE_SELECT);
	getBoard().getStones()[suggestedMove.to]->setState(HEX_STATE_HOVER);
}

void HexxagonGame::unSuggest()
{
	getBoard().getStones()[suggestedMove.from]->setState(HEX_STATE_NONE);
	getBoard().getStones()[suggestedMove.to]->setState(HEX_STATE_NONE);
	iGameStatus=HEX_WAIT_FOR_CLICK_1;
}

bool HexxagonGame::isRunning()
{
	bool retVal=true;
	if (getState()==HEX_RED_WIN ||
		getState()==HEX_BLUE_WIN||
		getState()==HEX_NO_WIN)
		retVal=false;
	return retVal;
}
