// WMSoundEngine.h: interface for the WMSoundEngine class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "..\..\SoundEngine.h"
#include <Vector>

using std::vector;

class WMSoundEngine : public SoundEngine
{
public:
	WMSoundEngine();
	virtual ~WMSoundEngine();
	void setDataSource(const char* szPath);
	Sample* loadSample(const char* filename);
	Music* loadMusic(const char* filename);
	void playSample(unsigned int id);
	void playMusic(unsigned int id);
	int loadedSamples();
	int loadedMusic();
	void init(){}
	void free();
	void updateStatus(){}
	const char* getDriverInfo();

private:
	vector<Sample*> samples;
	vector<Music*> tracks;
};
