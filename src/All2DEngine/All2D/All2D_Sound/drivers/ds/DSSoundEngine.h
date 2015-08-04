// DSSoundEngine.h: interface for the DSSoundEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSSOUNDENGINE_H__3C16E479_BA19_44BA_BF6E_9AD3789D6188__INCLUDED_)
#define AFX_DSSOUNDENGINE_H__3C16E479_BA19_44BA_BF6E_9AD3789D6188__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\SoundEngine.h"
//#include "dsound.h"
#include <Vector>

using namespace std;

template <class T>
inline void SafeRelease(T& iface)
{
	if( iface ) {
		iface->Release();
		iface=NULL;
	}
}

class DSSoundEngine : public SoundEngine
{
public:
	DSSoundEngine();
	virtual ~DSSoundEngine();

	void setDataSource(char* szPath);

	Sample* loadSample(char* filename);
	Music* loadMusic(char* filename);

	void playSample(int id);
	void playMusic(int id);

	int loadedSamples();
	int loadedMusic();

	void init();
	void free();
	void updateStatus();

	char* getDriverInfo();

	void DuplicateSoundBuffer(LPDIRECTSOUNDBUFFER src,LPDIRECTSOUNDBUFFER* dest);

	vector<Sample*> samples;
	vector<Music*> tracks;

private:
	bool								bInitialized;
	char*								szDefPath;
	LPDIRECTSOUND				lpDirectSound;
	LPDIRECTSOUNDBUFFER pDSBPrimary;
	WAVEFORMATEX*				pwfx;
};

#endif // !defined(AFX_DSSOUNDENGINE_H__3C16E479_BA19_44BA_BF6E_9AD3789D6188__INCLUDED_)
