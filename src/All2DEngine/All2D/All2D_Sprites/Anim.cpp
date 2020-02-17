// Anim.cpp: Implementierung der Klasse Anim.
//
//////////////////////////////////////////////////////////////////////

#include "Anim.h"
#include "../All2D_System.h"
#include <math.h>
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Anim::Anim() :maxDimension()
{
	xEParent=NULL;
	speed=1;
	actualIndex=0;
	numOfRepeats=0;
	animDuration=-1;
	isplaying=false;
	frameBased=false;
	bClone=false;
	startTime=0;
	maxDimension.x=0; maxDimension.y=0;
	actualPlayMode=0;
	setPlayMode(ANIM_FORW | ANIM_LOOP);
}

Anim::~Anim()
{

}

// Speed ist die anzahl von frames, die von einem paint() zum naechsten uebersprungen werden
void Anim::setSpeed(int sp)
{	speed=sp;}

// Die Direction der Animation wird im lowNibble (0x000f) gespeichert, der RepeatMode in highNibble(0x00f0)
void Anim::setPlayMode(int md, bool	immediate)
{
	if (immediate)
		requestedPlayMode=md;
	else
		requestedPlayMode=md;
}

// interne Routine, die den Neuen Playmode setzt
void Anim::setActualPlayMode(int md)
{
	if ((md & ANIM_FORW) || (md & ANIM_BACK))
		actualPlayMode= (actualPlayMode & 0xfff0) | (md & 0x000f);
	if ((md & ANIM_LOOP) || (md & ANIM_ONCE) || (md & ANIM_FLIP))
		actualPlayMode= (actualPlayMode & 0xff0f) | (md & 0x00f0);
}

// Restarts the Animation , if wished, is triggered by end of animation
void Anim::restartAnim()
{
	if (actualPlayMode & ANIM_ONCE){
		actualIndex--;	// einen wieder zurueckgehen..
		stop();
		if (xEParent)		// evl Parent ueber stop()-Command unterrichten
			xEParent->notify(Event(MN_ANIM_STOP,0,0));
	}
	if (actualPlayMode & ANIM_LOOP)
	{
		if (actualPlayMode & ANIM_BACK)
			actualIndex=vecIndexes.size() /2-1;

		if (actualPlayMode & ANIM_FORW)
			actualIndex=0;

		if (actualPlayMode & ANIM_FLIP)
			actualIndex=0;

		if (xEParent)		// evl Parent ueber restart()-Command unterrichten
			xEParent->notify(Event(MN_ANIM_RESTART,0,0));
	}
}

// starts the Animation
// falls anim schon abgespielt wird, passiert nichts
void Anim::play(int pMode)
{
	if (!isplaying)
	{
		if (xEParent)		// evl Parent ueber play()-Command unterrichten
			xEParent->notify(Event(MN_ANIM_START,0,0));

		if (pMode!=0)
			setActualPlayMode(pMode);
		else
			setActualPlayMode(requestedPlayMode);

		if (actualPlayMode & ANIM_FORW)
		{
			iEnd= (actualPlayMode & ANIM_FLIP) ? vecIndexes.size()-1 : vecIndexes.size()/2-1;
			actualIndex=0;
		}
		if (actualPlayMode & ANIM_BACK)
		{
			iEnd=  vecIndexes.size()-1 ;
			actualIndex=vecIndexes.size()/2-1;
		}
		if (actualPlayMode & ANIM_FLIP)
		{
			iEnd=  vecIndexes.size()-1 ;
			actualIndex=0;
		}
		startTime=All2D_System::getTime();
		numOfRepeats=0;
	}
	isplaying=true;
}

// stoppt die aktuelle Animation
void Anim::stop(int stopMode)
{
	if (isplaying)
	{
		if (stopMode & ANIM_STOP_IMMEDIATELY)
		{
			// einzige ausnahme: wenn vorwaerts gespielt wird ohne Loop, muss am Ende gehalten werden, sonst _IMMER_ am anfang
			if (actualPlayMode & ANIM_FORW && !(actualPlayMode & ANIM_LOOP) && !(actualPlayMode & ANIM_FLIP))
				actualIndex=vecIndexes.size()/2-1;
			else
				actualIndex=0;

			isplaying=false;
			numOfRepeats=0;
		}
		else
		{
			if (actualPlayMode & ANIM_FLIP)
				setActualPlayMode(ANIM_ONCE | ANIM_FLIP);
			else
				setActualPlayMode(ANIM_ONCE);
		}
	}
}

// gibt Index im Vector zurück, den das Frame einnimmt..not implemented
int Anim::addFrame(AnimFrame& frm, bool blnClone)
{

	bClone=blnClone;	// keine Anim geladen, da geclont...
	bool sizeChanged=false;
	if (frm.getWidth()>maxDimension.x)
	{
		maxDimension.x=frm.getWidth();
		sizeChanged=true;
	}
	if (frm.getHeight()>maxDimension.y)
	{
		maxDimension.y=frm.getHeight();
		sizeChanged=true;
	}
	if (sizeChanged && Buffering)
	{
			Buffer1->resize(maxDimension.x, maxDimension.y);
			Buffer2->resize(maxDimension.x, maxDimension.y);
	}

	vecFrames.insert(vecFrames.end(), &frm);
	animDuration=-1;
	generateIndexList();
	return -1;
}

// gibt das Image an der aktuellen Stelle zurueck
AnimFrame* Anim::getFrame()
{
	AnimFrame* retVal=NULL;
	if (frameBased)
	{
		if (vecFrames.size()>0)
			retVal=vecFrames[vecIndexes[actualIndex]];

		if (isplaying)
		{
			actualIndex+=speed;
			if (actualIndex>iEnd)
				restartAnim();
		}

	} else {					// TimeBased Animation .. nach x ms wird das zugehoerige Frame gespielt..

		if (isplaying && vecFrames.size()>0)
		{
			bool atEnd=false;
			int actTime=All2D_System::getTime() - startTime;
			int actAnimDuration=animDuration;			// Zeit in ms fuer einen ganzen Durchlauf
			int frameDuration = vecFrames[0]->duration;	//single Duration of a frame
			if (actualPlayMode & ANIM_FLIP)
				actAnimDuration*=2;									// Bei FlipFlop doppelte Zeit ( hin und zurueck)

			actualIndex = actTime % actAnimDuration;		// ANZahl der ms leit letzter wdh..
			actualIndex /= frameDuration;									// geteilt durch ms pro Frame ->Index des Frames

			unsigned int actNumOfRepeats=actTime / actAnimDuration;	// wurde das Ende erreicht/ueberschritten?
			atEnd=(actNumOfRepeats!=numOfRepeats);

			if (atEnd && actualPlayMode & ANIM_ONCE)
			{
				stop();
				if (xEParent)		// evl Parent ueber stop()-Command unterrichten
					xEParent->notify(Event(MN_ANIM_STOP,0,0));
			}
			else {
				if (!(actualPlayMode & ANIM_FLIP))
				{
					if (actualPlayMode & ANIM_BACK)
						actualIndex+=vecIndexes.size()/2-1;
				}
				numOfRepeats=actNumOfRepeats;
			}
		}
	}
	if (vecFrames.size()>0)
		retVal=vecFrames[vecIndexes[actualIndex]];

	return retVal;
}

void Anim::blit(Image& Dest, int bltMode)
{
//  Hier wird gebuffert...Wir muessen die Source clippen!!(ALL3D clippt nur die Destination!!)
	AnimFrame* actPic=displayFrame;
	if (actPic)
	{
		if (isBuffered())
		{
			// Werte aus Dest Retten....
			Rect tmpRect=Dest.getSrcRect();
			Point tmpPoint=Dest.getOffset();
			Dest.setOffset(0,0);

			if (active1)
			{
				BufferPos1=Position;				// richtig bewegen
				BufferPos1.x1-=(getOffset().x + actPic->getOffset().x);
				BufferPos1.y1-=(getOffset().y + actPic->getOffset().y);

				tmpRect.clip(BufferPos1);		// BufferPos and den Rändern clippen
				Dest.setSrcRect(BufferPos1);
				Dest.show(*Buffer1,0,0, IMAGE_BLTMODE_FAST);
			}else{
				BufferPos2=Position;				// richtig bewegen
				BufferPos2.x1-=(getOffset().x + actPic->getOffset().x);
				BufferPos2.y1-=(getOffset().y + actPic->getOffset().y);

				tmpRect.clip(BufferPos2);		// BufferPos and den Rändern clippen
				Dest.setSrcRect(BufferPos2);
				Dest.show(*Buffer2,0,0, IMAGE_BLTMODE_FAST);
			}
			// Werte restaurieren...
			Dest.setSrcRect(tmpRect);
			Dest.setOffset(tmpPoint.x, tmpPoint.y);
		}

		actPic->show(Dest,Position.x1,Position.y1,Position.x2,Position.y2, bltMode);
	}
}

void Anim::show(Image& BackBuffer, int x1, int y1, int w, int h, int bltMode)
{
	UISprite::setPosition(x1,y1,w,h);
	show(BackBuffer, bltMode);
}

void Anim::show(Image& backBuffer, int bltMode)
{
	displayFrame=getFrame();
	UISprite::show(backBuffer, bltMode);
}


int Anim::getWidth()
{
	return maxDimension.x;
}

int Anim::getHeight()
{
	return maxDimension.y;
}

bool Anim::loadAnimation(string n, int start, int end, float step, float secAnimationTime)
{
	char* fileName= new char[80];
	bool retVal=true;
	if (step<0)
		step=All2D_System::skipFactor;
	float index=(float)start;
	int duration=(int)(1000 * secAnimationTime / (ceil((end - start) / step)));
	for (int x=start;x<end;x++)
	{
		if (index<end)
		{
			AnimFrame* tmp=new AnimFrame();
			tmp->duration=duration;
			sprintf(fileName,n.c_str(),(int)index);
			if (!tmp->loadImage(fileName))
				retVal=false;
			addFrame(*tmp, false);
			index+=step;
		}	else
			break;
	}
	delete fileName;
	return retVal;
}

bool Anim::isPlaying()
{	return isplaying;}

int Anim::getActualFrame()
{	return vecIndexes[actualIndex];}

float Anim::getActualTime()
{
	if (vecFrames.size()!=0)
	{
		int framesPerAnim;
		if (actualPlayMode & ANIM_FLIP)	//wenn  flip angeschaltet, ist die Animation doppelt so lang(hin und zurück)
			framesPerAnim=vecIndexes.size();
		else
			framesPerAnim=vecIndexes.size()/2;

		int tmpIndex=actualIndex;
		if (actualPlayMode & ANIM_BACK)//&& tmpIndex>=vecIndexes.size()/2)  // wenn die Animation rueckwaerts abgespielt wird, muss vecIndexes.size()/2 von actualIndex abgezogen werden..
			tmpIndex-=vecIndexes.size()/2;

		float duration=animDuration/framesPerAnim;
		double myD=(duration*tmpIndex);
		return myD/animDuration;
	} else
	return -1.0;
}
void Anim::setActualFrame(unsigned int i)
{
	if (i>vecIndexes.size())
		i=vecIndexes.size();
	if (i<0)
		i=0;
	actualIndex=i;
}

void Anim::finish()
{
	speed=1;
	actualIndex=0;
	isplaying=false;
	maxDimension.x=0; maxDimension.y=0;
	actualPlayMode=0;
	setPlayMode(ANIM_FORW | ANIM_LOOP);

	if (!bClone)		// Wenn nur diese Klasse eine Instanz besitzt, KILL IT!	// TODO: more sophisticated...
	{
		for(vector<AnimFrame*>::iterator x=vecFrames.begin(); x!=vecFrames.end(); x++)
		{
			(*x)->finish();
			delete (*x);
		}
	}
	vecFrames.clear();
	vecIndexes.clear();
//	delete Root;
}

// Solange diese Funktion nicht eingebaut ist, koennen die AnimFrames
// nur alle die gleiche duration haben
// Muss nach dem letzten Frame aufgerufen werden...Baut den Binärbaum auf
// WIRD ABER IM MOMENT NUR  GENUTZT, UM DIE GESAMTSPIELZEIT ZU ERMITTELN
//...WEIL : Iam a LOSER Baby, so why dont you kill me
void Anim::BuildSortTree()
{
/*
	BTree** sortBaum=new BTree*[vecFrames.size()];
	int i=0, actDuration=0;
	for (AnimFrame** x=vecFrames.begin();x!=vecFrames.end();x++)
	{
		sortBaum[i]=new BTree();
		sortBaum[i]->Content=i; //(der Index in den vector vecFrames
		sortBaum[i]->setCharakteristic(actDuration);	//danach wird sortiert

		actDuration+=(*x)->duration;
		i++;
	}

	animDuration=actDuration;	// Dauer der Animation in ms

	// Normalerweise muss der BinaerBaum hier sortiert werden, aber unser
	// Array ist schon sortiert, deswegen entfaellt die Sortierung..

	// Baue Baum aus Array von folgenden Indizes..
	Root=BTree::buildSubTree(sortBaum, 0, vecFrames.size());

	delete[] sortBaum;
*/
}


void Anim::setFrameBasedModus(bool mode)
{	frameBased=mode;}

void Anim::generateIndexList()
{
	vecIndexes.clear();
	for (int x=vecFrames.size()-1;x>=0;x--)
	{
		vecIndexes.insert(vecIndexes.begin(),x);
		vecIndexes.insert(vecIndexes.end(),x);
	}
	if (vecFrames.size()>0)
		animDuration=vecFrames[0]->duration * vecFrames.size();		// alle Frames gleichlang
	else
		animDuration=-1;
	// buildSortTree()
}

void Anim::setOffset(int x, int y)
{
	for (unsigned int a=0; a<vecFrames.size();a++)
	{
		vecFrames[a]->setOffset(x,y);
	}
}

void Anim::setParent(xElement &Parent)
{
	xEParent=&Parent;
}

AnimFrame* Anim::getFrame(unsigned int index)
{
	if (index>=0 && index <vecFrames.size())
	{
		return vecFrames[index];
	}
	return NULL;
}

int Anim::getFrameCount()
{
	return vecFrames.size();
}
