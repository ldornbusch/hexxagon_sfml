// WMSoundEngine.cpp: implementation of the WMSoundEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "WMSoundEngine.h"
#include "WMSample.h"
#include "../null/NullMusic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WMSoundEngine::WMSoundEngine()
{

}

WMSoundEngine::~WMSoundEngine()
{

}

void WMSoundEngine::setDataSource(char* szPath)
{
}

Sample* WMSoundEngine::loadSample(char* filename)
{
	WMSample* smp = new WMSample(samples.size(),filename);
	samples.insert(samples.end(),smp);
	return smp;
}

void WMSoundEngine::playSample(int id)
{
	if (id<samples.size()) samples[id]->play();
}

Music* WMSoundEngine::loadMusic(char* filename)
{
	return new NullMusic();
}

void WMSoundEngine::playMusic(int id)
{
}

int WMSoundEngine::loadedSamples()
{
	return samples.size();
}

int WMSoundEngine::loadedMusic()
{
	return tracks.size();
}


/*int WMSoundEngine::addSample(Sample &smp, int insertAt=0) {
	if (insertAt>0&&insertAt<samples.size()) {
		Sample** ilt=samples.begin()+insertAt;
		samples.insert(ilt,&smp);
	} else {
		if (insertAt<0)	samples.insert(samples.end(), &smp);
		else						samples.insert(samples.begin(), &smp);
	}
	return smp.getID();
}

	/**
	 * Frees all the resources that are used by the sound representation.
	 * This method is quite slow to execute and should preferrably be called upon
	 * exiting the game or between level changes etc.
	 */
void WMSoundEngine::free(){
	for (int i=0; i<samples.size(); i++) {
		samples[i]->stop();
		samples[i]->free();
	}
	samples.clear();

	for (int i=0; i<tracks.size(); i++) {
		tracks[i]->stop();
		tracks[i]->free();
	}
	tracks.clear();
}

char* WMSoundEngine::getDriverInfo() {
	return "WMSoundEngine 0.1 WaveMix32.dll";
}

