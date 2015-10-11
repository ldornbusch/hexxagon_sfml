// WMSoundEngine.h: interface for the WMSoundEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WMSOUNDENGINE_H__82A43FE8_7953_455B_A1EB_E88440443ABB__INCLUDED_)
#define AFX_WMSOUNDENGINE_H__82A43FE8_7953_455B_A1EB_E88440443ABB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\SoundEngine.h"
#include <Vector>

using namespace std;

class WMSoundEngine : public SoundEngine
{
public:
	WMSoundEngine();
	virtual ~WMSoundEngine();
	void setDataSource(char* szPath);
	Sample* loadSample(char* filename);
	Music* loadMusic(char* filename);
	void playSample(unsigned int id);
	void playMusic(unsigned int id);
	int loadedSamples();
	int loadedMusic();
	void init(){}
	void free();
	void updateStatus(){}
	const char* getDriverInfo();

private:
	vector<Sample*> samples;
	vector<Music*> tracks;

};

#endif // !defined(AFX_WMSOUNDENGINE_H__82A43FE8_7953_455B_A1EB_E88440443ABB__INCLUDED_)
