// SoundFactory.h: interface for the SoundFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "SoundEngine.h"	// Added by ClassView
#pragma once

class SoundFactory
{

public:

	SoundFactory();
	virtual ~SoundFactory();

	/**
	 * Returns the single instance of Null Sample Engine class.
	 */
	static SoundEngine* getInstance(int driver=1);


private:

	/**
	 * The singleton instance of the SoundEngine class.
	 */
	static SoundEngine* singletonInstance;

};
