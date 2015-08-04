// ColumnsImageCloner.cpp: Implementierung der Klasse ColumnsImageCloner.
//
//////////////////////////////////////////////////////////////////////

#include "GameImageCloner.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

GameImageCloner::GameImageCloner()
{

}

GameImageCloner::~GameImageCloner()
{
	// nothing to do, because the Image is cloned..
}

void GameImageCloner::getGFX(Image& imgGFX)
{
	imgElements.cloneImage(imgGFX);
}
