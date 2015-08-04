// NullMusic.h: interface for the NullMusic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NULLMUSIC_H__1C1DCC07_C53A_4EFB_9C43_DF30DFDC1161__INCLUDED_)
#define AFX_NULLMUSIC_H__1C1DCC07_C53A_4EFB_9C43_DF30DFDC1161__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../Music.h"

class NullMusic : public Music  
{
public:
	NullMusic(){}
	virtual ~NullMusic(){}
	// sound
	void play(){};
	void loop(){};
	void stop(){};
	bool isPlaying(){return false;};
	void free(){};
	int getID(){return -1;};
	char* getSource(){return "";};
};

#endif // !defined(AFX_NULLMUSIC_H__1C1DCC07_C53A_4EFB_9C43_DF30DFDC1161__INCLUDED_)
