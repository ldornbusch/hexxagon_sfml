// StandardSample.cpp: implementation of the StandardSample class.
//
//////////////////////////////////////////////////////////////////////

#include "StandardSample.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

StandardSample::StandardSample()
{
  iID         = -1;
  szFilename  = "";
  fVolume     = 1.0f;
  fPan        = 0.0f;
}

StandardSample::StandardSample( int id, char const *filename )
{
  iID         = id;
  szFilename  = filename;
  fVolume     = 1.0f;
  fPan        = 0.0f;
}

StandardSample::~StandardSample()
{
}

// sound
void StandardSample::play()
{
  if (szFilename!=NULL)
    sndPlaySound( szFilename, SND_ASYNC | SND_NODEFAULT );
}

void StandardSample::loop()
{
  if (szFilename!=NULL)
    sndPlaySound( szFilename, SND_ASYNC | SND_NODEFAULT | SND_LOOP );
}

void StandardSample::stop()
{
  sndPlaySound( NULL, 0 );
}

// sample
Sample* StandardSample::getCopy()
{
  return new StandardSample(iID, szFilename);
}

bool StandardSample::isPlaying(){ return false; }

int StandardSample::getID(){ return iID; }
char const * StandardSample::getSource(){ return szFilename; }
void StandardSample::setVolume(float volume){ fVolume=volume; }
void StandardSample::setPan(float pan){ fPan=pan; }
float StandardSample::getVolume(){ return fVolume; }
float StandardSample::getPan(){ return fPan; }

void StandardSample::free(){}
