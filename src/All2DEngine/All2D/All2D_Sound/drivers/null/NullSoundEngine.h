// NullSoundEngine.h: interface for the NullSoundEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NULLSOUNDENGINE_H__6606D7E0_3C0D_47D6_969B_4D8D20A58835__INCLUDED_)
#define AFX_NULLSOUNDENGINE_H__6606D7E0_3C0D_47D6_969B_4D8D20A58835__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../SoundEngine.h"
#include "NullSample.h"
#include "NullMusic.h"

class NullSoundEngine : public SoundEngine  
{
public:
	NullSoundEngine(){}
	virtual ~NullSoundEngine(){}

	void setDataSource(char* szPath){}
	Sample* loadSample(char* filename){ return new NullSample(); }
	Music* loadMusic(char* filename){ return new NullMusic(); }
	void playSample(int id){};
	void playMusic(int id){};
	int loadedSamples(){return 0;};
	int loadedMusic(){return 0;};
	void init(){}
	void free(){}
	void updateStatus(){}
	char* getDriverInfo(){return "NullSoundEngine 0 NULL";}

};

#endif // !defined(AFX_NULLSOUNDENGINE_H__6606D7E0_3C0D_47D6_969B_4D8D20A58835__INCLUDED_)
