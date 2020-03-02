// SFMLSoundEngine.h: interface for the SFMLSoundEngine class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "../../SoundEngine.h"
#include<vector>

class SFMLSoundEngine : public SoundEngine
{
public:
	SFMLSoundEngine();
	virtual ~SFMLSoundEngine();

	void setDataSource(const char* szPath);

	Sample* loadSample(const char* filename);
	Music* loadMusic(const char* filename);

	void playSample(unsigned int id);
	void playMusic(unsigned int id);

	int loadedSamples();
	int loadedMusic();

	void init();
	void free();
	void updateStatus();

	virtual const char* getDriverInfo();

	std::vector<Sample*> samples;
	std::vector<Music*> tracks;

private:
	bool	bInitialized;
	char*	szDefPath;
};
