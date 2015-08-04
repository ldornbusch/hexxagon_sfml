// GameControler.h: Schnittstelle für die Klasse GameControler.
// Der GameController regelt den Ablauf eines Spiels mit verschiedenen Teilen:
// z.B:
// Selection-Screen, HighScore, Instruction, Configs usw.
// Jedes Teil ist ein xContainer , der jeweils wieder in 
// den GameController geAdded wird. 

//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMECONTROLER_H__419AD0FA_19E0_41CC_BB50_BEB575371117__INCLUDED_)
#define AFX_GAMECONTROLER_H__419AD0FA_19E0_41CC_BB50_BEB575371117__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "All2D_Base/xContainer.h"
#include "All2D_Events/MessageManager.h"
#include <string>
#include <vector>

using namespace std;

class AppGameController : public xContainer
{
public:
	// consruct / deconstruct
	AppGameController();
	virtual ~AppGameController();

  // container functions
	virtual void  requestLoad();
	virtual bool  handleEvent(Event* evt);
	virtual bool  paint(Image& backBuffer);
	virtual void          init();
private:
	bool  masterHandleEvent(Event* evt);
	bool  masterPaint(Image& backBuffer);
	Image imgFrameBuffer;

// eigentlich wollte ich nur die beiden Functionen paint und handleEvent des MessageManagers 
// zu friends machen gab aber immer einen No NameSpace Error.. deswegen die ganze class als friend :-(	
	friend class MessageManager;//::paint(Image& backBuffer);
protected:
	int iLoadReadyFlag;
	// manage game flow
	int		activeElement;
	int		newActiveElement;
	void	setActiveElement();

	virtual bool paintLoadScreen(Image& backBuffer);
	virtual bool paintRegularScreen(Image& backBuffer);
	bool blnLoadScreen;

	// load and save game data
	virtual void  loadGameData();
	virtual void  saveGameData();
};

#endif // !defined(AFX_GAMECONTROLER_H__419AD0FA_19E0_41CC_BB50_BEB575371117__INCLUDED_)
