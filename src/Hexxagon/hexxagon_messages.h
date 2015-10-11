// HexxagonStone.h: Schnittstelle für die Klasse HexxagonStone.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#define HEX_RED_PLAYER 1
#define HEX_EMPTY_STONE 0
#define HEX_BLUE_PLAYER -HEX_RED_PLAYER
#define HEX_DISABLED  -100

#define HEX_BOARD_STONES 77

#define HEX_NUM_STONE_NEIGHBOURS 6
#define HEX_NORTH		 0  //  NW N NE
#define HEX_NORTHEAST	 1  //    \|/
#define HEX_SOUTHEAST	 2  // 	   O
#define HEX_SOUTH		 3  //    /|\   //
#define HEX_SOUTHWEST	 4  //  SW S SE
#define HEX_NORTHWEST	 5

#define HEX_NUM_STONE_DISTANT_NEIGHBOURS 12
#define HEX_NN			 6  // NNW NN NNE
#define HEX_NNE			 7  //NWW \|/  NEE
#define HEX_NEE			 8  //WW---O----EE
#define HEX_EE			 9  //SWW /|\  SEE
#define HEX_SEE			10  // SSW SS SSE
#define HEX_SSE			11
#define HEX_SS			12
#define HEX_SSW			13
#define HEX_SWW			14
#define HEX_WW			15
#define HEX_NWW			16
#define HEX_NNW			17

#define HEX_WAIT_FOR_CLICK_1	0x0001
#define HEX_WAIT_FOR_CLICK_2	0x0002
#define HEX_WAIT_FOR_UPDATE		0x0003
#define HEX_BETWEEN_MOVE		0x0004
#define HEX_SUGGEST_MOVE		0x0005
#define HEX_FILL_UP				0x0006
#define HEX_RED_WIN				0x0007
#define HEX_BLUE_WIN			0x0008
#define HEX_NO_WIN				0x0009

//GameMessages sent via MessageManager
#define HEX_MOUSE_CHANGE		0xA801
#define HEX_RESET_GAME			0xA802

#define HEX_AI_MOUSE_MOVE		0xA803	// Both Messages will be converted to MOUSE_MOVE-Messages
#define HEX_AI_MOUSE_CLICK		0xA804


#define HEX_NO_NEIGHBOUR	0
#define HEX_NEAR_NEIGHBOUR	1
#define HEX_FAR_NEIGHBOUR	2

// Stati der Buttons
#define HEX_STATE_NONE				0x00	// keine besondere Eigenschaft
#define HEX_STATE_HOVER				0x01	// Maus ist darueber
#define HEX_STATE_SELECT			0x02	// 1. Stein der ausgewaehlt wurde
#define HEX_STATE_NEIGHBOUR			0x03	// Nachbarn des Ausgewaehlten Steins
#define HEX_STATE_FAR_NEIGHBOUR		0x04	// Entfernte Nachbarn des ausgewaehlten Steins

#define HX_FIELD_CLICK 0x9001

// Move Types
#define HEX_MOVE_DOUBLE				0x01	// Der Stein verdoppelt sich in ein Nachbarfeld
#define HEX_MOVE_JUMP				0x02	// Der Stein Springt in ein entferntes Nachbarfeld
