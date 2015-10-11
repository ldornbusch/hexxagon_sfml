// Sound.h: interface for the Sound class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <mmsystem.h>
//#include <stdio.h>
//#include <conio.h>


/**
 * defines the base interface for all representations of a sound.
 * offers methods for controlling the playback of a sound.
 *
 * @author dbug 20020130
 * @version SETest 0.1
 * @since SETest 0.1
 */
class Sound
{
public:

	Sound(){};
	virtual ~Sound(){};

	/**
	 * Plays the sound once and then stops. If the sound is
	 * already playing then it is stopped and restarted.
	 */
	virtual void play()=0;

	/**
	 * Plays the sound over and over again (looping).
	 * If the sound is already playing then it is stopped and
	 * restarted.
	 */
	virtual void loop()=0;

	/**
	 * Stops playing the sound.
	 */
	virtual void stop()=0;

	/**
	 * Returns true if play() or loop() has been invoked on the sound and
	 * the stop() hasn't been called after that. This method doesn't reflect
	 * the fact if the sound can be heard or not at the moment.
	 */
	virtual bool isPlaying()=0;

	/**
	 * Frees all the resources that are used by the sound representation.
	 * This method is quite slow to execute and should preferrably be called upon
	 * exiting the game or between level changes etc.
	 */
	virtual void free()=0;

	/**
	 * Returns the id associated with this sound
	 */
	virtual int getID()=0;

	/**
	 * Returns the source (filename) of this sound
	 */
	virtual const char* getSource()=0;
};
