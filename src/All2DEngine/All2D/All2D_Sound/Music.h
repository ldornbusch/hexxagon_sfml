// Music.h: interface for the Music class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUSIC_H__C64C8FA6_1C52_4905_96E9_1BF56166566F__INCLUDED_)
#define AFX_MUSIC_H__C64C8FA6_1C52_4905_96E9_1BF56166566F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Sound.h"

class Music : public Sound  
{
public:
	Music(){};
	virtual ~Music(){};

};

#endif // !defined(AFX_MUSIC_H__C64C8FA6_1C52_4905_96E9_1BF56166566F__INCLUDED_)
