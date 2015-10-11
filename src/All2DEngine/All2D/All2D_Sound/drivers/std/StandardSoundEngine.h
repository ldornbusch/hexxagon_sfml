// StandardSoundEngine.h: interface for the StandardSoundEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_StandardSOUNDENGINE_H__82A43FE8_7953_455B_A1EB_E88440443ABB__INCLUDED_)
#define AFX_StandardSOUNDENGINE_H__82A43FE8_7953_455B_A1EB_E88440443ABB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\SoundEngine.h"
#include <Vector>

using namespace std;

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

#endif // !defined(AFX_StandardSOUNDENGINE_H__82A43FE8_7953_455B_A1EB_E88440443ABB__INCLUDED_)
