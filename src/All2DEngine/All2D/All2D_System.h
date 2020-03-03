// All2D_System.h: Schnittstelle f�r die Klasse All2D_System.
// Enthaelt alle Klassen auf die andere Programm elemente immer Zugriff
// haben sollen, wie SpriteManager, Sound, Registry usw
//////////////////////////////////////////////////////////////////////

#pragma once

#include "All2D_Sprites/SpriteManager.h"	// Hinzugef�gt von der Klassenansicht
#include "All2D_Base/ImageText.h"
#include "All2D_Sound/SoundFactory.h"
#include <SFML/System/Clock.hpp>
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
	static int fixedX;				// Aufl�sung in X-Richtung
	static int fixedY;				// Aufl�sung in Y-Richtung
	static bool fullScreen;			// fullscreen oder windowed mode

	static SpriteManager spriteManager;

	static SoundEngine *sound;

	static string WinTitle;

	static string dataPath(string szFile="");

	static Image UIElements;
	static ImageText SystemFont;

	static string loadPath;
    static sf::Clock Timer;
private:
};
