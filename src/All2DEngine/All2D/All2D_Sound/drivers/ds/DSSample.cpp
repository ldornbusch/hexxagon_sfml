#define INITGUID
// DSSample.cpp: implementation of the DSSample class.
//
//////////////////////////////////////////////////////////////////////

#include "DSSoundEngine.h"
#include "DSSample.h"
#include "../../../All2D_System.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DSSample::DSSample()
{
  iID         = -1;
  szFilename  = "";
	init();
}

DSSample::DSSample( int id, char *filename )
{
  iID         = id;
	szFilename	= filename;
	init();
}

DSSample::~DSSample() {}


// sound
int DSSample::load( int id, char *filename, LPDIRECTSOUND lpDirectSound )
{
	szFilename	= filename;

 	// lokale Variablen deklarieren
 	MMCKINFO mmcktemp;
 	MMCKINFO mmckinfo;
 	PCMWAVEFORMAT pcmWaveFormat;
 	WORD cbExtraAlloc;
 	WAVEFORMATEX *waveFormatEx;
 	PCMWAVEFORMAT pcmwf;
 	DSBUFFERDESC dsbdesc;
 	HMMIO hMMIO;

 	// Datei öffnen
 	if ((hMMIO=mmioOpen(filename, NULL, MMIO_ALLOCBUF|MMIO_READ)) == NULL) {
 		return -1;
 	}

 	// In ersten Chunk einsteigen
 	if (((int)mmioDescend(hMMIO, &mmckinfo, NULL, 0)) != 0)	{
 		return -2;
 	}

 	// Ist dieses eine gültige WAV-Datei?
 	if ((mmckinfo.ckid!=FOURCC_RIFF)||(mmckinfo.fccType!=mmioFOURCC('W','A','V','E'))) {
 		return -3;
 	}

 	// nach FMT-Chunk suchen
 	mmcktemp.ckid = mmioFOURCC('f','m','t',' ');
 	if (((int)mmioDescend(hMMIO, &mmcktemp, &mmckinfo, MMIO_FINDCHUNK)) != 0) {
 		return -4;
 	}

 	// Ist dies ein gültiger Chunk?
 	if (mmcktemp.cksize < (long)sizeof(PCMWAVEFORMAT)) {
 		return -5;
 	}

 	// Daten übertragen
 	if (mmioRead(hMMIO, (HPSTR)&pcmWaveFormat, (long)sizeof(pcmWaveFormat))!=(long)sizeof(pcmWaveFormat)) {
 		return -6;
 	}

 	// Anzahl von Extrabytes bestimmen
 	if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM) {
 		cbExtraAlloc = 0;
 	}	else {
 		// Extrabytes einlesen
 		if (mmioRead(hMMIO, (LPTSTR)&cbExtraAlloc, (long)sizeof(cbExtraAlloc))!=(long)sizeof(cbExtraAlloc)) {
 			return -7;
 		}
 	}

 	// Speicher allokieren
 	if ((waveFormatEx = (tWAVEFORMATEX *)GlobalAlloc(GMEM_FIXED, sizeof(WAVEFORMATEX)+cbExtraAlloc)) == NULL) {
 		return -8;
 	}

 	// Daten kopieren
 	memcpy(waveFormatEx, &pcmWaveFormat, sizeof(pcmWaveFormat));
 	waveFormatEx->cbSize = cbExtraAlloc;

 	// Auf Extra Bytes prüfen
 	if (cbExtraAlloc != 0) {
 		// Extra Bytes einlesen
 		if (mmioRead(hMMIO, (LPTSTR) (((BYTE*)&(waveFormatEx->cbSize))
			+ sizeof(cbExtraAlloc)),(long) (cbExtraAlloc)) != (long)(cbExtraAlloc))	{
 			return -9;
 		}
 	}

 	// Aus FMT Chunk aussteigen
 	if ((mmioAscend(hMMIO, &mmcktemp, 0)) != 0)	{
 		return -10;
 	}

 	// Daten-Chunk suchen
 	if ((mmioSeek(hMMIO, mmckinfo.dwDataOffset + sizeof(FOURCC), SEEK_SET)) == -1) {
 		return -11;
 	}

 	// in Daten-Chunk einsteigen
 	mmcktemp.ckid = mmioFOURCC('d','a','t','a');
 	if ((mmioDescend(hMMIO, &mmcktemp, &mmckinfo, MMIO_FINDCHUNK)) != 0) {
 		return -12;
 	}

 	// Informationen kopieren
 	memset(&pcmwf,0,sizeof(PCMWAVEFORMAT));
 	pcmwf.wf.wFormatTag = waveFormatEx->wFormatTag;
 	pcmwf.wf.nChannels = waveFormatEx->nChannels;
 	pcmwf.wf.nSamplesPerSec = waveFormatEx->nSamplesPerSec;
 	pcmwf.wf.nBlockAlign = waveFormatEx->nBlockAlign;
 	pcmwf.wf.nAvgBytesPerSec = pcmwf.wf.nSamplesPerSec * pcmwf.wf.nBlockAlign;
 	pcmwf.wBitsPerSample = waveFormatEx->wBitsPerSample;

  // Bufferbeschreibung vorbereiten
 	memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));
 	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
 	dsbdesc.dwBufferBytes = mmcktemp.cksize;
 	dsbdesc.dwFlags = 0|DSBCAPS_STATIC|/*DSBCAPS_CTRLDEFAULT|*/DSBCAPS_CTRLPOSITIONNOTIFY;
 	dsbdesc.lpwfxFormat = (LPWAVEFORMATEX)&pcmwf;

  // create buffer
 	//LPDIRECTSOUNDBUFFER pTempBuffer;
 	if (FAILED(lpDirectSound->CreateSoundBuffer(&dsbdesc, &(aBuffer[0].pBuffer),NULL))) {
 		return -13;
 	}

	// copy to first buffer
	aBuffer[0].bIsPlaying = false;
	//aBuffer[0].pBuffer = pTempBuffer;
	aBuffer[0].nBufferSize = dsbdesc.dwBufferBytes;


  // fill buffers with data
 	readNext(hMMIO, &mmckinfo);

 	// return success
	return 0;
}

void DSSample::updateStatus()
{
	int nObject;

	// Wurde eins der Sound-Events signalisiert?
 	if ((nObject = WaitForMultipleObjects(NUM_DSSOUNDBUFFERS, ahEvent, false, 0)) != WAIT_TIMEOUT) {
 		// Zugehörigen SoundBuffer als nicht mehr spielend markieren
 		aBuffer[nObject].bIsPlaying = false;
 	}
}

void DSSample::play()
{
	if (!aBuffer[0].bIsPlaying) {

		// Regionsvariable vorbereiten
 		aDSBpos[0].dwOffset = DSBPN_OFFSETSTOP;
 		aDSBpos[0].hEventNotify = ahEvent[0];

 		// Notifikation vorbereiten
 		LPDIRECTSOUNDNOTIFY lpdsNotify;

 		// Schnittstelle anfordern
 		if FAILED(aBuffer[0].pBuffer
  				->QueryInterface(IID_IDirectSoundNotify,
 				(LPVOID *)&lpdsNotify))
 		{
 			// Fehler melden
 			return; // (1);
 		}

 		// Notifikation setzen
 		if FAILED(lpdsNotify->SetNotificationPositions(1,aDSBpos))
 		{
 			// Fehler! Freigabe
 			IDirectSoundNotify_Release(lpdsNotify);

 			// Fehler melden
 			return; // (2);
 		}

 		// Soundbuffer abspielen
 		aBuffer[0].pBuffer->Play(0,0,0);

 		// Merken, dass Buffer abgespielt wird.
 		aBuffer[0].bIsPlaying = true;

	} else {

 		// lokale Variablen vorbereiten
 		bool bFound = false;
 		int i=1;

 		// Alle Buffer absuchen
 		while ((!bFound) && (i<NUM_DSSOUNDBUFFERS))
 		{
 			// Wird der aktuelle Buffer bereits abgespielt?
 			if (!aBuffer[i].bIsPlaying)
 			{
 				// Nein, der Buffer ist noch frei.
 				bFound = true;

 				// Buffer mit Sounddaten duplizieren
				((DSSoundEngine*)All2D_System::sound)->DuplicateSoundBuffer(aBuffer[0].pBuffer,&aBuffer[i].pBuffer);

 				// Regionsvariable vorbereiten
 				aDSBpos[i].dwOffset = DSBPN_OFFSETSTOP;
 				aDSBpos[i].hEventNotify = ahEvent[i];

 				// Notifikation vorbereiten
 				LPDIRECTSOUNDNOTIFY         lpdsNotify;

 				// Schnittstelle anfordern
 				if FAILED(aBuffer[i].pBuffer
  				->QueryInterface(IID_IDirectSoundNotify,
 				(LPVOID *)&lpdsNotify))
 				{
 					// Fehler melden
 					return; // (3);
 				}

 				// Notifikation setzen
 				if FAILED(lpdsNotify->SetNotificationPositions(1, &aDSBpos[i]))
 				{
 			// Fehler! Freigabe der
  			//Schnittstelle.
 			IDirectSoundNotify_Release(lpdsNotify);

 					// Fehler melden
 					return; // (4);
 				}

 				// Buffer abspielen
 				aBuffer[i].pBuffer->Play(0,0,0);

 				// Merken, dass dieser Buffer abgespielt
  				// wird.
 				aBuffer[i].bIsPlaying = true;
 			}

 			// Iterator inkrementieren
 			i++;
 		}
	}
}

void DSSample::loop()
{
}

void DSSample::stop()
{
 	// Soundbuffer durchsuchen
 	for (int i=0; i<NUM_DSSOUNDBUFFERS; i++)
 		if (aBuffer[i].bIsPlaying) aBuffer[i].pBuffer->Stop();
}

// sample
Sample* DSSample::getCopy() {
  return new DSSample(iID,szFilename);
}

bool DSSample::isPlaying(){

 	// Soundbuffer durchsuchen
 	for (int i=0; i<NUM_DSSOUNDBUFFERS; i++)
 		if (aBuffer[i].bIsPlaying) return true;

	return false;
}

int DSSample::getID(){ return iID; }
char* DSSample::getSource(){ return szFilename; }
void DSSample::setVolume(float volume){ fVolume=volume; }
void DSSample::setPan(float pan){ fPan=pan; }
float DSSample::getVolume(){ return fVolume; }
float DSSample::getPan(){ return fPan; }

void DSSample::free(){}

int DSSample::readNext(HMMIO _hMMIO, MMCKINFO *_pmmckInfo)
{
	// lokale Variablen vorbereiten
 	UCHAR *pAudioBytes1=NULL;
 	UCHAR *pAudioBytes2=NULL;
 	DWORD audioBytes1, audioBytes2;
 	LPDWORD nAudioBytes1=&audioBytes1;
 	LPDWORD nAudioBytes2=&audioBytes2;
 	UINT nBytesRead;

 	// Buffer sperren
 	if ((FAILED(aBuffer[0].pBuffer->Lock(0, aBuffer[0].nBufferSize,
 			(void **)&pAudioBytes1, nAudioBytes1,
 			(void **)&pAudioBytes2, nAudioBytes2,
 			0))))
 	{
 		// report error
 		return (1);
 	}

 	// Daten auslesen
 	readWave(_hMMIO, aBuffer[0].nBufferSize, pAudioBytes1, _pmmckInfo, &nBytesRead);

 	// War alles OK?
 	if (!(nBytesRead==aBuffer[0].nBufferSize))
 	{
 		// an error occurred, report it
 		return (3);
 	}

 	// unlock the buffer again
 	if (FAILED(aBuffer[0].pBuffer->Unlock(pAudioBytes1, *nAudioBytes1,
 					pAudioBytes2, *nAudioBytes2)))
 	{
 		return (4);
 	}

 	// return success
 	return 0;
}

int DSSample::readWave(HMMIO _hMMIO,UINT _nBytes,BYTE *_pAddress,MMCKINFO *_pmmckinfo,UINT *_pActuallyRead)
{
 	// data
 	MMIOINFO info;

 	// get file info
 	if (mmioGetInfo(_hMMIO, &info, 0) != 0)	return -1;

 	// adapt params when trying to read more bytes than available
 	if (_nBytes > _pmmckinfo->cksize) _nBytes = _pmmckinfo->cksize;

 	// decrease remaining bytes
 	_pmmckinfo->cksize -= _nBytes;

 	// handle each byte
 	for (UINT i=0; i < _nBytes; i++) {

		// can we read more
 		if (info.pchNext == info.pchEndRead) {
 			// update file position
 			if ((mmioAdvance(_hMMIO, &info, MMIO_READ)) != 0) return -2;
 			// check if filepos is valid
 			if (info.pchNext == info.pchEndRead) return -3;
 		}

 		// copy byets
 		*((BYTE*)_pAddress+i) = *((BYTE*)info.pchNext);
 		info.pchNext++;
 	}

 	// update file info
 	if ((mmioSetInfo(_hMMIO, &info, 0)) != 0) {
 		return  -4;
 	}

 	// acutally read bytes in memory
 	*_pActuallyRead = _nBytes;

 	// everything fine
 	return 0;

}

int DSSample::init()
{
  fVolume     = 1.0f;
  fPan        = 0.0f;

 	// Soundbuffer initialisieren
 	for (int i=0; i<NUM_DSSOUNDBUFFERS; i++) {
 		aBuffer[i].bIsPlaying = false;
 		aBuffer[i].nBufferSize = 0;
 		aBuffer[i].nHandle = 0;
 		aBuffer[i].pBuffer = NULL;
 	}

 	// Events für Soundbuffer anlegen
 	for (i = 0; i < NUM_DSSOUNDBUFFERS; i++) {
		ahEvent[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (NULL == ahEvent[i]) return -1;
	}

	return 0;

}
