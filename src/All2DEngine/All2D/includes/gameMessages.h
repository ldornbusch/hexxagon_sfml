// GameMessages.h
// Here are all Messages which are sent and/or received
// by Buttons or other game elements defined

#ifndef ALL2D_MSG_CONSTANT
#define ALL2D_MSG_CONSTANT


#define		MM_NO_EVENT				0000			// Damit kann der Event-Type auf einen Standartwert gesetzt werden
#define		MM_MOUSEACTIVE			8001			// wData ist entweder true, oder false
#define 	MM_MOUSEMOVE			8002
#define 	MM_LBUTTONDOWN			8003
#define 	MM_LBUTTONUP			8004
#define 	MM_RBUTTONDOWN			8005
#define 	MM_RBUTTONUP			8006
#define		MM_CHAR					8007
#define		MM_KEYDOWN				8008
#define		MM_KEYUP				8009
// BUTTON STANDARD SUPPORT
#define		MM_BUTTON_CLICK			8010			// wdata ist ButtonID
// ScrollBar Support..
#define		MM_SCROLL_UP			8011			// wdata ist ScrollBarID
#define		MM_SCROLL_DOWN			8012			// wdata ist ScrollBarID
#define		MM_SCROLL_PAGE_UP		8013			// wdata ist ScrollBarID
#define		MM_SCROLL_PAGE_DOWN		8014			// wdata ist ScrollBarID

// Keyrecorder (legacy) Support..
#define		MM_KEYRECORDERACTIVE	8015			// Keyrecorder wurde de/aktiviert, in wData steht ob aktiviert(true), oder deaktiviert(false) in ldata die ID
#define		MM_KEYRECORDERSET		8016			// Keyrecorder hat Taste aufgenommen, in wData steht der neue TastaturCode, in lData die ID

#define		MM_SETFULLSCREEN		8017			// SWITCHES TO FULLSCREEN OR BACK (wData is true(Fullscreen) or false(Window))
#define		MM_CHANGE_FULLSCREEN	8018			// Notification FullscreenStatus is changed (wData contains blnIsFullscreen)

#define		MM_SETSMOOTH	    	8019			// CONTROLS Filtering of texture "FullScreen Antialasing

#define		MN_ANIM_START			8020			// NOTIFY MESSAGES...ANIM HAS STARTED
#define		MN_ANIM_RESTART			8021			// NOTIFY MESSAGES...ANIM HAS RESTARTED
#define		MN_ANIM_STOP			8022			// NOTIFY MESSAGES...ANIM HAS STOPPED

// Dies sind die Messages, um die Applikation zu steuern(Auswahl,Spiele,Ende)
#define		MM_APP_QUIT				8223

// default dialog
#define		MM_NAVIGATION_HOVER		8203
#define		MM_RADIO_SET_VALUE		8204

// focus messages
#define		MM_GOT_FOCUS			8600		// wird von item gesendet wenn es den focus bekommt
#define		MM_LOST_FOCUS			8601		// wird von item gesendet wenn es den focus verliert
#define		MM_NEXT_FOCUS			8602		// wird von item gesendet wenn es den focus abgeben will

// IN-GAME Standard-KEYS
#define MM_LEFT								0x8701
#define MM_RIGHT							0x8702
#define MM_UP								0x8703
#define MM_DOWN								0x8704
#define MM_FIRE								0x8705
#define MM_BOSS								0x8706
#define MM_PAUSE							0x8707

#define A3D_XMLMENU_NAVIGATION				0x8800
#define A3D_XMLMENU_APPEAR					0x8801
#define A3D_XMLMENU_DISAPPEAR				0x8802

#define A3D_CUSTOM							0x9000	// use area from 0x9000 - 0xFFFF for own messageIDs
#endif
