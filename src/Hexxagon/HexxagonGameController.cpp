// HexxagonGameController.cpp: Implementierung der Klasse HexxagonGameController.
// 021018 LDO: Some finetunings in All2D-Engine and start of HexxagonGame
// 021222 LDO: Implementing The Conroller Infrastructure for different PlayerControls
// MenuStructure 29.Nov.02:
//
/*

		(Continue)			|-Player----------------------------|Player A| PlayerB|
		Game				|-Controls-------KeysetA/KeysetB	-------------------------------------
                            |									|	NAME_PLAER________|				|
		Options-------------|									|	O Mouse     ___________			|
		Help				|-X Fullscreen						|   O Keyset A  |Configure|			|
		Credits				|O Red Begins   O Blue Begins		|   O Keyset B  -----------			|
		Exit													|   O Computer						|
				  |-UnDo Move									|		Difficulty: |---<>---| Easy |
				  |-Suggest Move								|   O Network						|
		Game------|-New Game									|       Configure TCP/IP   ----		|
				  |-Load Game									|                          |OK|		|
				  |-Save Game									-------------------------------------
*/
//////////////////////////////////////////////////////////////////////

#include "HexxagonGameController.h"
#include "../All2DEngine/All2D/All2D_System.h"
#include "../All2Dengine/All2D/All2D_Events/MessageManager.h"
#include "HexxagonConstants.h"

#include "MouseController.h"
#include "KeyController.h"
#include "AIController.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

HexxagonGameController::HexxagonGameController():myMenu("data/dialog.xml")
{
	isExit=false;
}

HexxagonGameController::~HexxagonGameController()
{
}

void HexxagonGameController::init()
{
	AppGameController::init();
	// load the total ressource image
	imgGFXElements.loadImage("data/elements.png");
	hexGame.getGFX(imgGFXElements);
	mouse.getGFX(imgGFXElements);
	myMenu.init(imgGFXElements);

	myFont.cloneImage(imgGFXElements,Rect(192,0,160,80));
	myFont.FontInit(16,16,10,"ABCDEFGHIJKLMNOPQRSTUVWXYZ ,.-0123456789");

    myMsgBox.setFont(myFont);
	myMsgBox.init();
	myMsgBox.setPriority(39);


	add(hexGame);
	add(myMenu);
	add(myMsgBox);
	add(mouse);	// wird als erstes in die EventQue gesteckt....+

// Alle Controller Adapter initialisieren:
	AIController* ctrlAI=new AIController();
	ctrlAI->setStones(hexGame.getBoard().getStones());
	ctrlAI->setPlayerID(1);
	AIController* ctrlAI2=new AIController();
	ctrlAI2->setStones(hexGame.getBoard().getStones());
	ctrlAI2->setPlayerID(-1);
	KeyController* ctrlKey1=new KeyController();
	KeyController* ctrlKey2=new KeyController();
	MouseController* ctrlMouse=new MouseController();
	vecCtrlAdapter.push_back(ctrlMouse);	//	index 0
	vecCtrlAdapter.push_back(ctrlKey1);		//	index 1= Keyset
	vecCtrlAdapter.push_back(ctrlKey2);		//	index 2= Keyset 2
	vecCtrlAdapter.push_back(ctrlAI);		//	index 3= Player A AI
	vecCtrlAdapter.push_back(ctrlAI2);		//	index 4= Player B AI
//	vecCtrlAdapter.push_back(ctrlTCP1);		//	index 5= Player A Network
//	vecCtrlAdapter.push_back(ctrlTCP2);		//	index 6= Player B Network

	setSettings();
	mouse.setDefault(ctrlMouse);
	hexGame.reset();
}

void HexxagonGameController::setSettings()
{
	// Setting the DialogValues...

// set/unSet Fullscreen...
	value val=myMenu.getValue("chkfullscreen");
	MessageManager::handleEvent(new Event(MM_SETFULLSCREEN,val.second,0));

// set/unSet Beginner...
	hexGame.setBeginner((myMenu.getValue("rdoblue").second==1)?HEX_BLUE_PLAYER:HEX_RED_PLAYER);

// set/unSet Names...
	hexGame.getScore().strBluePlayer=myMenu.getValue("txtplayer_b").first;
	hexGame.getScore().strRedPlayer=myMenu.getValue("txtplayer_a").first;

// set/unSet Controller...
	int iP1=0, iP2=0;	// default: beide Maus!
	if (myMenu.getValue("mouse_a").second==1)
		iP1=0;
	if (myMenu.getValue("keyset_1_a").second==1)
	{
		iP1=1;
		KeyController* ctrl1=(KeyController*) vecCtrlAdapter[iP1];
		int iU=myMenu.getValue("key_1_up").second;
		int iD=myMenu.getValue("key_1_down").second;
		int iL=myMenu.getValue("key_1_left").second;
		int iR=myMenu.getValue("key_1_right").second;
		int iF=myMenu.getValue("key_1_fire").second;
		ctrl1->setKeys(iU,iD,iL,iR,iF);
	}
	if (myMenu.getValue("keyset_2_a").second==1)
	{
		iP1=2;
		KeyController* ctrl2=(KeyController*) vecCtrlAdapter[iP1];
		int iU=myMenu.getValue("key_2_up").second;
		int iD=myMenu.getValue("key_2_down").second;
		int iL=myMenu.getValue("key_2_left").second;
		int iR=myMenu.getValue("key_2_right").second;
		int iF=myMenu.getValue("key_2_fire").second;
		ctrl2->setKeys(iU,iD,iL,iR,iF);
	}
	if (myMenu.getValue("computer_a").second==1)
		iP1=3;
	if (myMenu.getValue("network_a").second==1)
		iP1=5;

	if (myMenu.getValue("mouse_b").second==1)
		iP2=0;
	if (myMenu.getValue("keyset_1_b").second==1)
	{
		iP2=1;
		KeyController* ctrl1=(KeyController*) vecCtrlAdapter[iP2];
		int iU=myMenu.getValue("key_1_up").second;
		int iD=myMenu.getValue("key_1_down").second;
		int iL=myMenu.getValue("key_1_left").second;
		int iR=myMenu.getValue("key_1_right").second;
		int iF=myMenu.getValue("key_1_fire").second;
		ctrl1->setKeys(iU,iD,iL,iR,iF);
	}
	if (myMenu.getValue("keyset_2_b").second==1)
	{
		iP2=2;
		KeyController* ctrl2=(KeyController*) vecCtrlAdapter[iP2];
		int iU=myMenu.getValue("key_2_up").second;
		int iD=myMenu.getValue("key_2_down").second;
		int iL=myMenu.getValue("key_2_left").second;
		int iR=myMenu.getValue("key_2_right").second;
		int iF=myMenu.getValue("key_2_fire").second;
		ctrl2->setKeys(iU,iD,iL,iR,iF);
	}
	if (myMenu.getValue("computer_b").second==1)
		iP2=4;
	if (myMenu.getValue("network_b").second==1)
		iP2=6;

	mouse.setController(vecCtrlAdapter[iP1], vecCtrlAdapter[iP2]);

}


bool HexxagonGameController::paint(Image& backBuffer)
{
	backBuffer.clear(0x555555);
	xContainer::paint(backBuffer);

	return !isExit;
}

bool HexxagonGameController::handleEvent(Event *evt)
{
	if (evt->Type==A3D_XMLMENU_DISAPPEAR)
	{
		setSettings();
	}
	if (evt->Type==A3D_XMLMENU_APPEAR)
	{
		if (hexGame.getState()==HEX_RED_WIN ||
			hexGame.getState()==HEX_BLUE_WIN ||
			hexGame.getState()==HEX_NO_WIN )
		{
			UIElement* tmp= myMenu.getElement("continue");
			if (tmp)
				tmp->setEnabled(false);
		}else{
			UIElement* tmp= myMenu.getElement("continue");
			if (tmp)
				tmp->setEnabled(true);
		}
		myMenu.setValue("chkfullscreen",value("",All2D_System::fullScreen));
	}

	if (evt->Type==MM_CHANGE_FULLSCREEN)
	{
		myMenu.setValue("chkfullscreen",value("",All2D_System::fullScreen));
	}

	if (evt->Type==MM_BUTTON_CLICK && evt->wData==myMenu.getElement("btnnew")->getID())	// Restart Game!
	{
		if (hexGame.isRunning()){
			myMsgBox.setMessage("RESTART?");
			myMsgBox.setYesEvent(Event(HEX_RESET_GAME,0,0));
			myMsgBox.activate(true);
		} else {
			evt->Type=HEX_RESET_GAME;
		}
	}
	if (evt->Type==HEX_RESET_GAME)
	{
		myMenu.displayDialog("");
		setSettings();
		evt->Type=MM_NO_EVENT;	// Event is processed..
		hexGame.reset();
	}

	if (evt->Type==MM_KEYDOWN && evt->wData==VK_F7)
		hexGame.save("data\\save1.sav");
	if (evt->Type==MM_KEYDOWN && evt->wData==VK_F8)
		hexGame.load("data\\save1.sav");

	if (evt->Type==MM_BUTTON_CLICK && evt->wData==myMenu.getElement("chkfullscreen")->getID())
		MessageManager::handleEvent(new Event(MM_SETFULLSCREEN,myMenu.getValue("chkfullscreen").second,0));

	if (evt->Type==MM_BUTTON_CLICK && evt->wData==myMenu.getElement("btnundo")->getID())
	{
		myMenu.displayDialog("");
		hexGame.undoMove();
	}

	if (evt->Type==MM_BUTTON_CLICK && evt->wData==myMenu.getElement("btnsuggest")->getID())
	{
		myMenu.displayDialog("");
		hexGame.suggestMove();
	}

	if (evt->Type==MM_BUTTON_CLICK && evt->wData==myMenu.getElement("btnexit")->getID())
	{
		if (hexGame.isRunning())
		{
			myMsgBox.setMessage("QUIT?");
			myMsgBox.setYesEvent(Event(MM_QUIT,0,0));
			myMsgBox.activate(true);
		} else {
			evt->Type=MM_QUIT;
		}
	}
	if (evt->Type==MM_QUIT)
	{
		isExit=true;
	}

	xContainer::handleEvent(evt);
	return true;
}

