// StandardSoundEngine.cpp: implementation of the SoundEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "StandardSoundEngine.h"
#include "StandardSample.h"
#include "../null/NullMusic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

StandardSoundEngine::StandardSoundEngine() {}
StandardSoundEngine::~StandardSoundEngine() {	free(); }

void StandardSoundEngine::setDataSource(char* szPath)
{
}

Sample* StandardSoundEngine::loadSample(char* filename)
{
	StandardSample* smp = new StandardSample(samples.size(),filename);
	samples.insert(samples.end(),smp);
	return smp;
}

Music* StandardSoundEngine::loadMusic(char* filename)
{
	return new NullMusic();
}

void StandardSoundEngine::playSample(unsigned int id)
{
	if (id<samples.size()) samples[id]->play();
}

void StandardSoundEngine::playMusic(unsigned int id)
{
}

int StandardSoundEngine::loadedSamples()
{
	return samples.size();
}

int StandardSoundEngine::loadedMusic()
{
	return tracks.size();
}

/*int StandardSoundEngine::addSample(Sample &smp, int insertAt=0) {
	if (insertAt>0&&insertAt<samples.size()) {
		Sample** ilt=samples.begin()+insertAt;
		samples.insert(ilt,&smp);
	} else {
		if (insertAt<0)	samples.insert(samples.begin(), &smp);
		else						samples.insert(samples.end(), &smp);
	}
	return smp.getID();
}

	/**
	 * Frees all the resources that are used by the sound representation.
	 * This method is quite slow to execute and should preferrably be called upon
	 * exiting the game or between level changes etc.
	 */
void StandardSoundEngine::free()
{
  sndPlaySound( NULL, 0 );

	for (unsigned int i=0; i<samples.size(); i++) {
		samples[i]->stop();
		samples[i]->free();
	}
	samples.clear();

	for (unsigned int i=0; i<tracks.size(); i++) {
		tracks[i]->stop();
		tracks[i]->free();
	}
	tracks.clear();
}

const char* StandardSoundEngine::getDriverInfo() {
  return "StandardSoundEngine";
}

