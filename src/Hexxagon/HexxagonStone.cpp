// HexxagonStone.cpp: Implementierung der Klasse HexxagonStone.
//
//////////////////////////////////////////////////////////////////////

#include "HexxagonStone.h"
#define STONE_WIDTH 64
#define STONE_HEIGHT 32
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
UISprite** HexxagonStone::imgStoneImages=NULL;

HexxagonStone::HexxagonStone(int iID)
{
	ID=iID;
	if (imgStoneImages==NULL)
	{
		imgStoneImages = new UISprite*[15];
		for (int x=0;x<15;x++){
			imgStoneImages[x]=new UISprite();
		}
	}

	for (int x=0;x<(HEX_NUM_STONE_NEIGHBOURS+HEX_NUM_STONE_DISTANT_NEIGHBOURS);x++)
	{
		Neighbours[x]=-1;
		setNeighbour( HEX_SOUTHWEST	, -1);

	}
	reset();
}

HexxagonStone::~HexxagonStone()
{
	if (imgStoneImages!=NULL)
	{
		for (int x=0;x<15;x++){
			delete imgStoneImages[x];
		}
		imgStoneImages=NULL;
	}
}
unsigned int HexxagonStone::getID()
{
	return ID;
}

int HexxagonStone::getColor()	// wenn der Stein nicht sichtbar ist wird als Farbe nicht 0 zurueckgegeben, da sonst angenommen wird, das das Feld frei waere
{
	return isVisible() ? iColor : HEX_DISABLED;
}

void HexxagonStone::setColor(int iCol)
{
	iColor=iCol;
	iButtonState=HEX_STATE_NONE;
}

void HexxagonStone::reset()
{
	setColor(0);
	setState(HEX_STATE_NONE);
}

void HexxagonStone::getGFX(Image &imgGFX)
{
	GameImageCloner::getGFX(imgGFX);
	for (int x=0;x<3;x++)
	{
		for (int y=0;y<5;y++)
		{
			imgElements.setSrcRect(Rect(x*STONE_WIDTH,y*STONE_HEIGHT,STONE_WIDTH,STONE_HEIGHT));
			imgStoneImages[x*5+y]->cloneImage(imgElements);

		}
	}

	imgElements.setSrcRect(Rect(0,0,imgElements.getWidth(),imgElements.getHeight()));
	Hut.cloneImage(imgElements);
	Hut.setPosition(0,0,52,78);
	Hut.setOffset(26,47);
	Hut.setPriority(10);

	cloneImage(*imgStoneImages[0]);
	setPosition(Rect(0,0,STONE_WIDTH,STONE_HEIGHT-1));
	setOffset(STONE_WIDTH/2, STONE_HEIGHT/2);

	setSendFlag(HX_FIELD_CLICK,getID(),0);

	setBlitMode(IMAGE_BLTMODE_HALF);
	setHoverBlitMode(IMAGE_BLTMODE_ADD);
	setHoverImage(*imgStoneImages[1]);
}


bool HexxagonStone::isInside(int x, int y)	// HexxagonCheck fuer die Felder
{
	bool retVal=false;
	if (UIHoverButton::isInside(x,y)){	// ist der Punkt im umgebenden Rechteck?
		int dx=getPosition().x1-x;
		int dy=getPosition().y1-y;
		if (abs(dx)<STONE_WIDTH/4 && abs(dy)<(STONE_HEIGHT/2)-1)
		{
				retVal=true;
		}else{
			if (dx<0)
			{	// rechte Spitze
				dx+=STONE_WIDTH/4;
				if (dy<0)
				{// untere Kante
					retVal=(STONE_HEIGHT/2+dy>-dx && dy>(-STONE_HEIGHT/2)+1);
				}else {		// obere Kante
					retVal=(STONE_HEIGHT/2-dy>-dx);
				}
			}else{	// linke Spitze
				dx-=STONE_WIDTH/4;
				if (dy<0)
				{// untere Kante
					retVal=(STONE_HEIGHT/2+dy>dx && dy>(-STONE_HEIGHT/2)+1);
				}else {		// obere Kante
					retVal=(STONE_HEIGHT/2-dy>dx);
				}
			}

		}
	}
	return retVal;
}

bool HexxagonStone::paint(Image &backBuffer)
{
	setLook();
	setOffset(STONE_WIDTH/2, STONE_HEIGHT/2);

	Hut.setPosition(getPosition().x1,getPosition().y1);

	if (iColor==-1)
	{
		Hut.setSrcRect(Rect(0,240,52,78));
		Hut.show(backBuffer,(iButtonState==HEX_STATE_SELECT)?IMAGE_BLTMODE_ADD:IMAGE_BLTMODE_TRANS);
	}
	if (iColor==1)
	{
		Hut.setSrcRect(Rect(52,240,52,78));
		Hut.show(backBuffer,(iButtonState==HEX_STATE_SELECT)?IMAGE_BLTMODE_ADD:IMAGE_BLTMODE_TRANS);
	}
	return UIHoverButton::paint(backBuffer);
}

void HexxagonStone::setNeighbour(int iDirection, int iIndex)
{
	if (iIndex>=0 && iIndex<HEX_BOARD_STONES
		&& iDirection>=0 && iDirection<=(HEX_NUM_STONE_NEIGHBOURS+HEX_NUM_STONE_DISTANT_NEIGHBOURS)){
		Neighbours[iDirection]=iIndex;
	}

}

int HexxagonStone::getNeighbour(int iDirection)
{
	int retVal=-1;
	if (iDirection>=0 && iDirection<=(HEX_NUM_STONE_NEIGHBOURS+HEX_NUM_STONE_DISTANT_NEIGHBOURS)){
		retVal=Neighbours[iDirection];
	}
	return retVal;
}

int HexxagonStone::isNeighbour(int iIndex)
{
	int retVal=HEX_NO_NEIGHBOUR;
	for (int x=0;x<(HEX_NUM_STONE_NEIGHBOURS);x++)
	{
		if (iIndex==Neighbours[x])
			return HEX_NEAR_NEIGHBOUR;
	}
	for (int x=0;x<(HEX_NUM_STONE_DISTANT_NEIGHBOURS);x++)
	{
		if (iIndex==Neighbours[x+6])
			return HEX_FAR_NEIGHBOUR;
	}
	return retVal;
}

void HexxagonStone::setState(int iState)
{
	iButtonState=iState;
}

void HexxagonStone::setLook()
{
	int iIndex=0;
	switch(iColor)
	{
	case HEX_RED_PLAYER:
		iIndex=10;
		break;
	case HEX_BLUE_PLAYER:
		iIndex=5;
		break;
	default:
		break;
	}

	imgStoneImages[iIndex+1]->setOffset(STONE_WIDTH/2, STONE_HEIGHT/2);
	setHoverImage(*imgStoneImages[iIndex+1]);
	switch(iButtonState)
	{
	case HEX_STATE_NONE:
		iIndex+=0;
		break;
	case HEX_STATE_HOVER:
		iIndex+=1;
		break;
	case HEX_STATE_SELECT:
		iIndex+=2;
		break;
	case HEX_STATE_FAR_NEIGHBOUR:
		iIndex+=3;
		break;
	case HEX_STATE_NEIGHBOUR:
		iIndex+=4;
		break;
	default:
		break;
	}
	cloneImage(*imgStoneImages[iIndex]);
}

bool HexxagonStone::handleEvent(Event *evt)
{
	if (isVisible())
	{
		return UIHoverButton::handleEvent(evt);
	}else
		return true;
}
