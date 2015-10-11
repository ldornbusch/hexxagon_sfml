// NullSample.h: interface for the NullSample class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "../../Sample.h"

class NullSample : public Sample
{
public:
	NullSample() {fVolume=1.0f;fPan=0.0f;}
	virtual ~NullSample() {}
	// sound
	void play(){};
	void loop(){};
	void stop(){};
	bool isPlaying(){return false;};
	void free(){};
	int getID(){return -1;};
	const char* getSource(){return "";};
	// sample
  void setVolume(float volume){fVolume=volume;};
  void setPan(float pan){fPan=pan;};
  float getVolume(){return fVolume;};
  float getPan(){return fPan;};
  Sample* getCopy(){return new NullSample();};
private:
	float fVolume;
	float fPan;
};

