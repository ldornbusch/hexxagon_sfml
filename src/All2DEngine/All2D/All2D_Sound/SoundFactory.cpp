// SoundFactory.cpp: implementation of the SoundFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "SoundFactory.h"

#include "drivers/null/NullSoundEngine.h"
#include "drivers/sfml/SFMLSoundEngine.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SoundEngine* SoundFactory::singletonInstance=NULL;

SoundFactory::SoundFactory()
{
}

SoundFactory::~SoundFactory()
{

}

/**
 * Returns the single instance of Null Sample Engine class.
 */
SoundEngine* SoundFactory::getInstance(int driverID)
{
	// check if we have an instance
	if (singletonInstance==NULL) {
		// create new instance depending on capabilities
		switch (driverID) {
		case 3:
			singletonInstance = new SFMLSoundEngine();
			break;
		default:
			singletonInstance = new NullSoundEngine();
			break;
		}
	}
	singletonInstance->init();
  return singletonInstance;
}
