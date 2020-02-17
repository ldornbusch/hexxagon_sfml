// Anim.h: Schnittstelle für die Klasse Anim.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include <String>
#include <Vector>
#include "UISprite.h"
#include "AnimFrame.h"
#include "../../UTILS/POINT.H"	// Hinzugefügt von der Klassenansicht
// For Standard TemplateLibrary Support...
using std::string;
using std::vector;

#define	ANIM_FORW				0x0001	//Forwaerts
#define	ANIM_BACK				0x0002	//rueckwaerts
#define	ANIM_LOOP				0x0010	//Immer wiederholen
#define	ANIM_ONCE				0x0020	//Einmal abspielen
#define	ANIM_FLIP				0x0040	//Vor und Zurueck
#define ANIM_STOP_IMMEDIATELY	0x0100	// Stoppt sofort
#define ANIM_STOP_AT_END		0x0200	// Stoppt am Ende der Animation

#if defined(DEMO)
//#define ANIM_FPS				20
#define ANIM_FPS				60
#else
#define ANIM_FPS				60
#endif

class Anim : public UISprite
{
public:
	float getActualTime();
	void virtual setOffset(int x, int y);
	int getFrameCount();
	AnimFrame* getFrame(unsigned int index);
	void setActualFrame(unsigned int i);
	void setParent(xElement& Parent);
	void setFrameBasedModus(bool mode=true);
	void BuildSortTree();
	virtual void finish();
	virtual void blit(Image& Dest, int bltMode);
	int getActualFrame();
	bool isPlaying();
	bool loadAnimation(string n, int start, int end, float step=-1.0f, float secAnimationTime=1.0f);
	virtual int getHeight();
	virtual int getWidth();
	void show(Image& BackBuffer, int x1, int y1, int w, int h, int bltMode=IMAGE_BLTMODE_TRANS);
	void show(Image& BackBuffer, int bltMode=IMAGE_BLTMODE_TRANS);
	int addFrame(AnimFrame& frm,bool blnClone=true);
	void play(int pMode=0);
	void stop(int stopMode=ANIM_STOP_IMMEDIATELY);
	void setPlayMode(int md, bool immediate=false);
	void setSpeed(int sp);
	Anim();
	virtual ~Anim();

private:
	AnimFrame*	displayFrame;
	xElement* xEParent;
	bool bClone;
	AnimFrame* getFrame();

	void setActualPlayMode(int md);
	Point maxDimension;
	void restartAnim();
	bool isplaying;

	bool frameBased;			// Wenn true, dann wird jedes Frame gespielt(langsamer auf langsamen Rechner), wenn false, wird nach Zeit gespielt..
	int startTime;				// Start der Animation
	unsigned int animDuration;			// Dauer der Animation in ms
	unsigned int actualIndex;			// Zeigt den aktiven Index aus vecIndexes an..
	int requestedPlayMode;
	int actualPlayMode;			// Here is either Forward or Backward and Loop, Flip or Once
	int speed;
	unsigned int numOfRepeats;				// hier werden die anzahl der Wiederholungen gespeichert, so dass  man beim TimebaseAnimation sehen kann, ob eine Phase zuende ist..
	unsigned int	iEnd;			// This value îs the  endpoint of the indexList, which will be played..and shows when it should be repeated
protected:
	void generateIndexList();
//	BTree* Root;
	vector<AnimFrame*> vecFrames;
	vector<int> vecIndexes;					// this one holds the Indexes in vecFrames, so that it play a flip-flop loop.. so we just go 1 step in this array forward, without doing anything like counters, or directions
};
