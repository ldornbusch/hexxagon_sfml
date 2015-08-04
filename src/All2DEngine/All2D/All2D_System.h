// All2D_System.h: Schnittstelle für die Klasse All2D_System.
// Enthaelt alle Klassen auf die andere Programm elemente immer Zugriff
// haben sollen, wie SpriteManager, Sound, Registry usw
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEM_H__30A6EDFF_FA51_45E4_AD1D_F013D21CA958__INCLUDED_)
#define AFX_SYSTEM_H__30A6EDFF_FA51_45E4_AD1D_F013D21CA958__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "All2D_Sprites/SpriteManager.h"	// Hinzugefügt von der Klassenansicht
#include "All2D_Base/ImageText.h"
#include "All2D_Sound/SoundFactory.h"
#include "..\Utils\CDebug.h"	// Added by ClassView
#include "..\Utils\NativeTest.h"	// Added by ClassView
#include "..\Utils\xRegistry.h"

typedef enum tagRENDERMODES {
	ALL2D,
	OPENGL,
	DIRECTX
} RENDERMODES;

class All2D_System
{
public:
	static void setRenderMode(RENDERMODES iMode);
	static RENDERMODES getRenderMode();
	static int getTime();
	static Point getMouseCoords(Event* evt);

	static float skipFactor;		// Bestimmt wieviele Bilder einer Animation uebersprungen werden sollen
	static int fixedBits;			// Bittiefe(16 / 32 Bit)
	static int fixedX;				// Auflösung in X-Richtung
	static int fixedY;				// Auflösung in Y-Richtung
	static bool doubleBuffering;	// doubleBuffering
	static bool fullScreen;			// fullscreen oder windowed mode
	static CDebug Debug;			// DebugObject fuer DebugAusgaben

	static SpriteManager spriteManager;

	static SoundEngine *sound;

	static string WinTitle;

	static string dataPath(string szFile="");

	static xRegistry Registry;

	static Image UIElements;
	static ImageText SystemFont;

	static RENDERMODES iRendermode;

	static string appPath;
	static string loadPath;
	static string gamePath;
	static string tempPath;

private:
};

#endif // !defined(AFX_SYSTEM_H__30A6EDFF_FA51_45E4_AD1D_F013D21CA958__INCLUDED_)
