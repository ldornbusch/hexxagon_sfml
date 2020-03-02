// Hexxagon3DPlayer.h: Schnittstelle für die Klasse Hexxagon3DPlayer.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "../All2DEngine/All2D/All2D_Sprites/UIElement.h"
#include "HexxagonBoard.h"

//#include <gl\gl.h>
//#include <gl\glu.h>

class Hexxagon3DPlayer : public UIElement
{

public:

//	GLdouble rotateX;
//	GLdouble rotateY;

	Hexxagon3DPlayer();
	virtual ~Hexxagon3DPlayer();

	bool paint(Image& backBuffer);
	void setBoard(HexxagonBoard* board);

private:
	void init3D();

//	GLUquadricObj* quadObj;
	HexxagonBoard* hexBoard;
	bool bInitialized;

};
