// DSSample.h: interface for the DSSample class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include<SFML/Audio.hpp>
#include "..\..\Sample.h"




class SFMLSample : public Sample
{
public:
	SFMLSample();
    SFMLSample(int id, char *filename);
	virtual ~SFMLSample();

    int load(int id, char *filename);

	// sound
	void play();
	void loop();
	void stop();

	bool isPlaying();

	void free();
	void updateStatus();

	int getID();
	char* getSource();

    // sample
    void setVolume(float volume);
    void setPan(float pan);
    float getVolume();
    float getPan();

	Sample* getCopy();

private:
	int init();

	int		iID;
	char *szFilename;
	float fVolume;
	float fPan;
    sf::SoundBuffer buffer;
    sf::Sound sample;
};
