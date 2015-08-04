// AnimManager.h: Schnittstelle für die Klasse AnimManager.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANIMMANAGER_H__ED431EA1_2D20_11D5_B046_00E098802DF2__INCLUDED_)
#define AFX_ANIMMANAGER_H__ED431EA1_2D20_11D5_B046_00E098802DF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Anim.h"

#include <string>
#include <map>

#include "../../utils/RECT.h"
using namespace std;

class AnimManager :public xElement
{
public:
	int getWidth();
	int getHeight();
	float getActualTime();
	void setActualFrame(int i);
	void setParent(xElement& Parent);
	void setSmoothTransition(bool flag=true);
	void setPlayMode(string, int pMode);
	void setPosition(int x1=RECT_INVALID, int y1=RECT_INVALID, int w=RECT_INVALID, int h=RECT_INVALID);
	virtual void notify(Event evt);
	bool isPlaying(string name="");
	virtual Rect getPosition();
	int getActualFrame();
	string	getAnimationName();
	virtual void finish();
	void stop(string n);
	void show(Image& BackBuffer, int bltMode=IMAGE_BLTMODE_TRANS);
	void addAnim(Anim& a, string name);
	void play(string n);

	AnimManager();
	virtual ~AnimManager();
private:
	xElement* xEParent;
	string actualAnimationName, strNextAnimation;
	bool blnSmoothTransitions;
		Anim*	actualAnim;
protected:
	map<string, Anim*> mapAnims;
};

#endif // !defined(AFX_ANIMMANAGER_H__ED431EA1_2D20_11D5_B046_00E098802DF2__INCLUDED_)
