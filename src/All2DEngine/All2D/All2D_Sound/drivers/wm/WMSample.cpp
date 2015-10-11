// WMSample.cpp: implementation of the WMSample class.
//
//////////////////////////////////////////////////////////////////////

#include "WMSample.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


WMSample::WMSample()
{
  iID         = -1;
  szFilename  = NULL;
	fVolume			= 1.0f;
	fPan				= 0.0f;
}

WMSample::WMSample( int id, char *filename )
{
  iID         = id;
  szFilename  = filename;
	fVolume			= 1.0f;
	fPan				= 0.0f;
}

WMSample::~WMSample()
{

}

// sound
void WMSample::play(){}
void WMSample::loop(){}
void WMSample::stop(){}
bool WMSample::isPlaying(){return false;}
void WMSample::free(){}
int WMSample::getID(){return -1;}
const char* WMSample::getSource(){return "";};

// sample
void WMSample::setVolume(float volume){fVolume=volume;}
void WMSample::setPan(float pan){fPan=pan;}
float WMSample::getVolume(){return fVolume;}
float WMSample::getPan(){return fPan;}
Sample* WMSample::getCopy(){return new WMSample();}
