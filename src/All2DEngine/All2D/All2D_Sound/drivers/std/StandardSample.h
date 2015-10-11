// StandardSample.h: interface for the StandardSample class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "..\..\Sample.h"

class StandardSample : public Sample
{
public:
  StandardSample();
  StandardSample( int id, char *filename );
  virtual ~StandardSample();

	// sound
	void play();
	void loop();
	void stop();
	bool isPlaying();
	void free();
	int getID();
	char* getSource();

	// sample
  void setVolume(float volume);
  void setPan(float pan);
  float getVolume();
  float getPan();
  Sample* getCopy();

private:
	int		iID;
	char *szFilename;
	float fVolume;
	float fPan;

};
