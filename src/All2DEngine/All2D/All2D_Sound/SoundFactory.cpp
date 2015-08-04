// SoundFactory.cpp: implementation of the SoundFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "SoundFactory.h"

#include "drivers/null/NullSoundEngine.h"
#include "drivers/std/StandardSoundEngine.h"
#include "drivers/wm/WMSoundEngine.h"
//#include "drivers/ds/DSSoundEngine.h"


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
//		case 3:
//			singletonInstance = new DSSoundEngine();
			break;
		case 2:
			singletonInstance = new WMSoundEngine();
			break;
		case 1:
			singletonInstance = new StandardSoundEngine();
			break;
		default:
			singletonInstance = new NullSoundEngine();
			break;
		}
	}
  return singletonInstance;
}
