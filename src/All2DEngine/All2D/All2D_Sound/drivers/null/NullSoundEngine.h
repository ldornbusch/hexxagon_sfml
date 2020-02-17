// NullSoundEngine.h: interface for the NullSoundEngine class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "../../SoundEngine.h"
#include "NullSample.h"
#include "NullMusic.h"

class NullSoundEngine : public SoundEngine
{
public:
	NullSoundEngine(){}
	virtual ~NullSoundEngine(){}

	void setDataSource(const char* szPath){}
	Sample* loadSample(const char* filename){ return new NullSample(); }
	Music* loadMusic(const char* filename){ return new NullMusic(); }
	void playSample(unsigned int id){};
	void playMusic(unsigned int id){};
	int loadedSamples(){return 0;};
	int loadedMusic(){return 0;};
	void init(){}
	void free(){}
	void updateStatus(){}
	const char* getDriverInfo(){return "NullSoundEngine 0 NULL";}

};
