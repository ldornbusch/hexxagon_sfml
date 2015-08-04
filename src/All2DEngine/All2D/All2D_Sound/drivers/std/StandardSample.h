// StandardSample.h: interface for the StandardSample class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_StandardSample_H__A2030E53_9181_4F82_9864_C534AB327C76__INCLUDED_)
#define AFX_StandardSample_H__A2030E53_9181_4F82_9864_C534AB327C76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_StandardSample_H__A2030E53_9181_4F82_9864_C534AB327C76__INCLUDED_)
