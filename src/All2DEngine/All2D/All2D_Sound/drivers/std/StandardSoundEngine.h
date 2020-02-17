// StandardSoundEngine.h: interface for the StandardSoundEngine class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "..\..\SoundEngine.h"
#include <Vector>

using std::vector;

class StandardSoundEngine : public SoundEngine
{
public:
  StandardSoundEngine();
  virtual ~StandardSoundEngine();
	void setDataSource(char* szPath);
	Sample* loadSample(char* filename);
	Music* loadMusic(char* filename);
	void playSample(unsigned int id);
	void playMusic(unsigned int id);
	int loadedSamples();
	int loadedMusic();
	void updateStatus(){}
	void init(){}
	void free();
	const char* getDriverInfo();

	vector<Sample*> samples;
	vector<Music*> tracks;

private:
	char * szDefPath;

};
