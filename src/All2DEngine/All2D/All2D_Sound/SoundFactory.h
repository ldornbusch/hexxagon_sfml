// SoundFactory.h: interface for the SoundFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUNDFACTORY_H__9A639C38_C15B_4074_BF9F_57C891E62315__INCLUDED_)
#define AFX_SOUNDFACTORY_H__9A639C38_C15B_4074_BF9F_57C891E62315__INCLUDED_

#include "SoundEngine.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SoundFactory  
{

public:

	SoundFactory();
	virtual ~SoundFactory();

	/**
	 * Returns the single instance of Null Sample Engine class.
	 */
	static SoundEngine* getInstance(int driver=1);


private:

	/**
	 * The singleton instance of the SoundEngine class.
	 */
	static SoundEngine* singletonInstance;

};

#endif // !defined(AFX_SOUNDFACTORY_H__9A639C38_C15B_4074_BF9F_57C891E62315__INCLUDED_)
