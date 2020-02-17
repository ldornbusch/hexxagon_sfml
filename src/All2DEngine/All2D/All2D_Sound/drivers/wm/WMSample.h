// WMSample.h: interface for the WMSample class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "..\..\Sample.h"

class WMSample : public Sample
{
public:
	WMSample();
	WMSample( int id, const char *filename );
	virtual ~WMSample();

	// sound
	void play();
	void loop();
	void stop();
	bool isPlaying();
	void free();
	int getID();
	const char* getSource();

	// sample
  void setVolume(float volume);
  void setPan(float pan);
  float getVolume();
  float getPan();
  Sample* getCopy();

private:
	int		iID;
	const char *szFilename;
	float fVolume;
	float fPan;

};
