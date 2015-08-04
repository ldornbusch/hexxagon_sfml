// Hexxagon3DPlayer.h: Schnittstelle für die Klasse Hexxagon3DPlayer.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXXAGON3DPLAYER_H__E4E9A7EF_0461_4774_9F16_0B1DE44D1A1B__INCLUDED_)
#define AFX_HEXXAGON3DPLAYER_H__E4E9A7EF_0461_4774_9F16_0B1DE44D1A1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\ALL2DENGINE\ALL2D\ALL2D_SPRITES\UIElement.h"
#include "HexxagonBoard.h"

#include <gl\gl.h>
#include <gl\glu.h>

class Hexxagon3DPlayer : public UIElement  
{

public:
	
	GLdouble rotateX;
	GLdouble rotateY;
	
	Hexxagon3DPlayer();
	virtual ~Hexxagon3DPlayer();

	bool paint(Image& backBuffer);
	void setBoard(HexxagonBoard* board);

private:
	void init3D();

	GLUquadricObj* quadObj;
	HexxagonBoard* hexBoard;
	bool bInitialized;

};

#endif // !defined(AFX_HEXXAGON3DPLAYER_H__E4E9A7EF_0461_4774_9F16_0B1DE44D1A1B__INCLUDED_)
