// DSSample.h: interface for the DSSample class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSSAMPLE_H__F76D26FC_5801_4A2F_B15E_4617362A4DFC__INCLUDED_)
#define AFX_DSSAMPLE_H__F76D26FC_5801_4A2F_B15E_4617362A4DFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Sample.h"
//#include "dsound.h"

#define NUM_DSSOUNDBUFFERS		4

struct SSoundBuffer
{
	LPDIRECTSOUNDBUFFER pBuffer;
	bool bIsPlaying;
	UINT nBufferSize;
	UINT nHandle;
};

class DSSample : public Sample
{
public:
	DSSample();
  DSSample(int id, char *filename);
	virtual ~DSSample();

  int load(int id, char *filename, LPDIRECTSOUND lpDirectSound);

	// sound
	void play();
	void loop();
	void stop();

	bool isPlaying();

	void free();
	void updateStatus();

	int getID();
	char* getSource();

	// sample
  void setVolume(float volume);
  void setPan(float pan);
  float getVolume();
  float getPan();

	Sample* getCopy();

private:
	int init();
	int		readWave(HMMIO _hMMIO,UINT _nBytes,BYTE *_pAddress,MMCKINFO *_pmmckinfo,UINT *_pActuallyRead);
	int		readNext(HMMIO _hMMIO, MMCKINFO *_pmmckInfo);

	int		iID;
	char *szFilename;
	float fVolume;
	float fPan;
	//bool	bPlaying;

	//UINT	uiBufferSize;
	//UINT	uiHandle;

 	//LPDIRECTSOUNDBUFFER lpBuffer;
	//DSBPOSITIONNOTIFY	dsNotify;

	SSoundBuffer				aBuffer[NUM_DSSOUNDBUFFERS];
	DSBPOSITIONNOTIFY		aDSBpos[NUM_DSSOUNDBUFFERS];
	HANDLE							ahEvent[NUM_DSSOUNDBUFFERS];


};

#endif // !defined(AFX_DSSAMPLE_H__F76D26FC_5801_4A2F_B15E_4617362A4DFC__INCLUDED_)
