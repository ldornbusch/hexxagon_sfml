// DSSoundEngine.cpp: implementation of the DSSoundEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "DSSoundEngine.h"
#include "DSSample.h"
#include "../null/NullMusic.h"
#include "../null/NullSample.h"
#include "../../../All2D_System.h"
#include <mmreg.h>
#include <msacm.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DSSoundEngine::DSSoundEngine() { bInitialized=false; }
DSSoundEngine::~DSSoundEngine(){ free(); }

void DSSoundEngine::setDataSource(char* szPath)
{
}

Sample* DSSoundEngine::loadSample(char* filename)
{
	if (!bInitialized) return new NullSample();

	DSSample* smp = new DSSample();
	smp->load(samples.size(),filename,lpDirectSound);
	samples.insert(samples.end(),smp);
	return smp;
}

Music* DSSoundEngine::loadMusic(char* filename)
{
	return new NullMusic();
}

void DSSoundEngine::playSample(int id)
{
	if (!bInitialized) return;
	if (id<samples.size()) samples[id]->play();
}

void DSSoundEngine::playMusic(int id)
{
	if (!bInitialized) return;
}

int DSSoundEngine::loadedSamples()
{
	return samples.size();
}

int DSSoundEngine::loadedMusic()
{
	return tracks.size();
}

/*int DSSoundEngine::addSample(Sample &smp, int insertAt=0) {
	if (insertAt>0&&insertAt<samples.size()) {
		Sample** ilt=samples.begin()+insertAt;
		samples.insert(ilt,&smp);
	} else {
		if (insertAt<0)	samples.insert(samples.begin(), &smp);
		else						samples.insert(samples.end(), &smp);
	}
	return smp.getID();
}

	/**
	 * Frees all the resources that are used by the sound representation.
	 * This method is quite slow to execute and should preferrably be called upon
	 * exiting the game or between level changes etc.
	 */
void DSSoundEngine::free()
{
	for (int i=0; i<samples.size(); i++) {
		samples[i]->stop();
		samples[i]->free();
	}
	samples.clear();

	for (i=0; i<tracks.size(); i++) {
		tracks[i]->stop();
		tracks[i]->free();
	}
	tracks.clear();

	SafeRelease(pDSBPrimary);
	SafeRelease(lpDirectSound);

	if (pwfx!=NULL) {
		GlobalFree(pwfx);
		pwfx=NULL;
	}

}

char* DSSoundEngine::getDriverInfo() {
  return "DSSoundEngine DirectX3 Sound Implementation Version 0.2";
}

void DSSoundEngine::DuplicateSoundBuffer(LPDIRECTSOUNDBUFFER src,LPDIRECTSOUNDBUFFER* dest) {
	if (!bInitialized) return;
	lpDirectSound->DuplicateSoundBuffer(src,dest);
}

void DSSoundEngine::init()
{
  DSBUFFERDESC    dsbd;
	DWORD						dw;

  // Get the largest waveformatex structure.
  if (MMSYSERR_NOERROR != acmMetrics(NULL, ACM_METRIC_MAX_SIZE_FORMAT, &dw)) {
    MessageBox(All2D_System::hWnd, "ACM Metrics failed, aborting", "Colmns Sound Driver", MB_OK|MB_ICONSTOP);
		return;
  }

  // Setup the format, frequency, volume, etc.
  if ((pwfx = (WAVEFORMATEX*)GlobalAlloc(GPTR, dw)) == NULL) {
		MessageBox(All2D_System::hWnd, "Out of Memory", "Colmns Sound Driver", MB_OK|MB_ICONSTOP);
		return;
  }

  pwfx->wFormatTag			= WAVE_FORMAT_PCM;
  pwfx->nChannels				= 2;
  pwfx->nSamplesPerSec	= 22050;
  pwfx->wBitsPerSample	= 16;
  pwfx->nBlockAlign			= 4;
  pwfx->nAvgBytesPerSec	= 88200;
  pwfx->cbSize					= 0;

	// initialize DirectSound and set cooperative level
	if (SUCCEEDED(DirectSoundCreate(NULL, &lpDirectSound, NULL))) {
 		if (SUCCEEDED(lpDirectSound->SetCooperativeLevel(All2D_System::hWnd, DSSCL_EXCLUSIVE))) {

			// Set up the primary direct sound buffer.
      ZeroMemory(&dsbd, sizeof(dsbd));
      dsbd.dwSize					= sizeof(dsbd);
      dsbd.dwFlags				= DSBCAPS_PRIMARYBUFFER;
			dsbd.dwBufferBytes	= 0;
			dsbd.lpwfxFormat		= NULL;

      if (SUCCEEDED(lpDirectSound->CreateSoundBuffer(&dsbd,&pDSBPrimary,NULL))) {

        if (SUCCEEDED(pDSBPrimary->SetFormat(pwfx))) {

					//if (SUCCEEDED(pDSB->Play(0,0,DSBPLAY_LOOPING))) {
						
						// is initialized
						bInitialized=true;

					//} else {

					//	MessageBox(All2D_System::hWnd, "Cannot play primary buffer", "Columns Sound Driver", MB_OK|MB_ICONSTOP);
					//}

				} else {
					MessageBox(All2D_System::hWnd, "Cannot set format for primary buffer", "Columns Sound Driver", MB_OK|MB_ICONSTOP);
				}

      } else {
				MessageBox(All2D_System::hWnd, "Cannot create primary buffer", "Columns Sound Driver", MB_OK|MB_ICONSTOP);
      }

    } else {
			MessageBox(All2D_System::hWnd, "DirectSound SetCooperativeLevel failed", "Columns Sound Driver", MB_OK|MB_ICONSTOP);
    }

  } else {
    MessageBox(All2D_System::hWnd, "Failed to Initialize DirectSound object", "Columns Sound Driver", MB_OK | MB_ICONSTOP);
  }

	SafeRelease(pDSBPrimary);
	/* replaced by SafeRelease
	if (pDSB) {
		pDSB->Release();
		pDSB = NULL;
	}*/

}


void DSSoundEngine::updateStatus()
{
	if (!bInitialized) return;
	for (int i=0; i<samples.size(); i++) {
		((DSSample*)samples[i])->updateStatus();
	}

}
