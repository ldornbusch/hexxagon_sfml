// NullSample.h: interface for the NullSample class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NULLSAMPLE_H__558B7A19_2082_4A24_8B98_2E3DE6DF5EA4__INCLUDED_)
#define AFX_NULLSAMPLE_H__558B7A19_2082_4A24_8B98_2E3DE6DF5EA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
	char* getSource(){return "";};
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

#endif // !defined(AFX_NULLSAMPLE_H__558B7A19_2082_4A24_8B98_2E3DE6DF5EA4__INCLUDED_)
