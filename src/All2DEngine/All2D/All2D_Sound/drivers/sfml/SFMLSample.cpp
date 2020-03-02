#define INITGUID
// DSSample.cpp: implementation of the DSSample class.
//
//////////////////////////////////////////////////////////////////////

#include "SFMLSoundEngine.h"
#include "SFMLSample.h"
#include "../../../All2D_System.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SFMLSample::SFMLSample()
{
    iID         = -1;
    szFilename  = "";
    init();
}

SFMLSample::SFMLSample( int id, const char *filename )
{
    iID         = id;
    szFilename	= filename;
    init();
}

SFMLSample::~SFMLSample() {}


// sound
int SFMLSample::load( int id, const char *filename)
{
	szFilename	= filename;
    if (!buffer.loadFromFile(szFilename)){
        return -1;
    }
 	// Datei öffnen
    init();
 	// return success
	return 0;
}

void SFMLSample::updateStatus()
{
}

void SFMLSample::play()
{
    sample.setLoop(false);
    sample.play();
}

void SFMLSample::loop()
{
    sample.setLoop(true);
    sample.play();
}

void SFMLSample::stop()
{
    sample.stop();
}

// sample
Sample* SFMLSample::getCopy() {
  return new SFMLSample(iID,szFilename);
}

bool SFMLSample::isPlaying(){
    return (sample.getStatus()==sf::SoundSource::Status::Playing);
}

int SFMLSample::getID(){ return iID; }
char const * SFMLSample::getSource(){ return szFilename; }
void SFMLSample::setVolume(float volume){ fVolume=volume; }
void SFMLSample::setPan(float pan){ fPan=pan; }
float SFMLSample::getVolume(){ return fVolume; }
float SFMLSample::getPan(){ return fPan; }

void SFMLSample::free(){
    stop();
}


int SFMLSample::init()
{
    fVolume     = 1.0f;
    fPan        = 0.0f;

    sample.setBuffer(buffer);
    return 0;
}
