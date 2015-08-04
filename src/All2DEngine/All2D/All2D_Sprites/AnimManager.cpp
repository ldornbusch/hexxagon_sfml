// AnimManager.cpp: Implementierung der Klasse AnimManager.
//
//////////////////////////////////////////////////////////////////////

#include "AnimManager.h"
#include "../All2D_System.h"
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

AnimManager::AnimManager()
{
	xEParent=NULL;
	actualAnim=NULL;
	blnSmoothTransitions=false;
	strNextAnimation="";
	actualAnimationName="";
}

AnimManager::~AnimManager()
{

}

void AnimManager::addAnim(Anim &a, string name)
{
	a.setParent(*this);
	mapAnims[name]= &a;
}
void AnimManager::play(string n)
{
	if (actualAnim!=NULL){
		if (blnSmoothTransitions)
		{
			if (isPlaying())		// spielt die Anim noch?
			{										// ja: Neue Anim merken und abhauen..
				strNextAnimation=n;
				return;
			}
//									nein: neue Anim auswaehlen und starten
		}	else {
			actualAnim->stop();
		}
	}

	actualAnim = mapAnims[n];

		if (actualAnim!=NULL)
		{
			actualAnimationName=n;
			actualAnim->play();
		}
}


void AnimManager::show(Image& BackBuffer, int bltMode)
{
	if (actualAnim!=NULL)
		actualAnim->show(BackBuffer, bltMode);

}

void AnimManager::setPosition(int x1, int y1, int w, int h)
{
	if (actualAnim)
		actualAnim->setPosition(x1,y1,w,h);
}

int AnimManager::getActualFrame()
{
	if (actualAnim)
		return actualAnim->getActualFrame();
	else
		return -1;
}
float AnimManager::getActualTime()
{
	if (actualAnim)
		return actualAnim->getActualTime();
	else
		return -1.0;
}

void AnimManager::setActualFrame(int i)
{
	if (actualAnim)
		actualAnim->setActualFrame(i);
}

string AnimManager::getAnimationName()
{
	return actualAnimationName;
}

void AnimManager::setPlayMode(string n, int pMode)
{
	Anim* tmp=mapAnims[n];
	if (tmp)
		tmp->setPlayMode(pMode);
}

void AnimManager::stop(string n)
{
	Anim* tmp=mapAnims[n];
	if (tmp)
	{
		tmp->stop();
	}
}

void AnimManager::finish()
{
// TODO:. Aus AnimManager aller Anims entfernen..

	typedef map<string, Anim*>::const_iterator CI;
	for ( CI x= mapAnims.begin();x!=mapAnims.end(); x++)
	{
		Anim* myAni=(x->second);
		if (myAni)
			myAni->finish();
	}

}

// TODO:gibt die maximale Ausdehnung aller Animationen wieder..
Rect AnimManager::getPosition()
{
	if (actualAnim)
		return actualAnim->getPosition();
	else
		return Rect(RECT_INVALID,RECT_INVALID, RECT_INVALID, RECT_INVALID);
}

// gibt zurück, ob die angegebene Animation gerade abgespielt wird..
// Wenn der Name nicht existiert, wird die aktuelle Animation genommen
bool AnimManager::isPlaying(string name)
{
		Anim* tmp=mapAnims[name];
		if (!tmp)
			tmp=actualAnim;
		return tmp->isPlaying();
}

void AnimManager::setSmoothTransition(bool flag)
{
	blnSmoothTransitions=flag;
}

void AnimManager::notify(Event evt)
{
	if (evt.Type==MN_ANIM_STOP)		// Liegt beim Stop der Anim schon die naeachste auf Lager?
	{
		if (blnSmoothTransitions && strNextAnimation!="")
		{
			play(strNextAnimation);
		}
		strNextAnimation="";
	}
	if (xEParent)
		xEParent->notify(evt);
}

void AnimManager::setParent(xElement &Parent)
{
	xEParent=&Parent;
}

int AnimManager::getWidth()
{
	int retVal=RECT_INVALID;
	if (actualAnim)
		retVal= actualAnim->getWidth();
	else
		{
			if(mapAnims[0])
				retVal= mapAnims[0]->getWidth();
		}
	return retVal;
}

int AnimManager::getHeight()
{
	int retVal=RECT_INVALID;
	if (actualAnim)
		retVal= actualAnim->getHeight();
	else
		{
			if(mapAnims[0])
				retVal= mapAnims[0]->getHeight();
		}
	return retVal;
}

