// All2D_System.h: Schnittstelle für die Klasse All2D_System.
// Enthaelt alle Klassen auf die andere Programm elemente immer Zugriff
// haben sollen, wie SpriteManager, Sound, Registry usw
//////////////////////////////////////////////////////////////////////

#pragma once

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
	static unsigned int getTime();
	static Point extractMouseCoords(Event* evt);

	static float skipFactor;		// Bestimmt wieviele Bilder einer Animation uebersprungen werden sollen
	static int fixedBits;			// Bittiefe(16 / 32 Bit)
	static int fixedX;				// Auflösung in X-Richtung
	static int fixedY;				// Auflösung in Y-Richtung
	static bool fullScreen;			// fullscreen oder windowed mode
	static CDebug Debug;			// DebugObject fuer DebugAusgaben

	static SpriteManager spriteManager;

	static SoundEngine *sound;

	static string WinTitle;

	static string dataPath(string szFile="");

	static xRegistry Registry;

	static Image UIElements;
	static ImageText SystemFont;

	static string loadPath;

private:
};
