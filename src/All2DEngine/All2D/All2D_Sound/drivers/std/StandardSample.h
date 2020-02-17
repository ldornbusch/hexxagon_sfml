// StandardSample.h: interface for the StandardSample class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "..\..\Sample.h"

class StandardSample : public Sample
{
public:
  StandardSample();
  StandardSample( int id, const char  *filename );
  virtual ~StandardSample();

	// sound
	void play();
	void loop();
	void stop();
	bool isPlaying();
	void free();
	int getID();
	virtual const char* getSource();

	// sample
  void setVolume(float volume);
  void setPan(float pan);
  float getVolume();
  float getPan();
  Sample* getCopy();

private:
	int		iID;
	char const *szFilename;
	float fVolume;
	float fPan;

};
