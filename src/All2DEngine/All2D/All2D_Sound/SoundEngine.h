// SoundEngine.h: interface for the SoundEngine class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "Sample.h"
#include "Music.h"

class SoundEngine
{
public:
	SoundEngine(){};
	virtual ~SoundEngine(){};

  /**
   * Sets the data directory wherefrom the sounds are loaded.
   * The source directory defaults to the current directory.
   *
   * Note: Do not add the last path separator, it will be added automatically.
   * Note: Remember to use the unix-style separator '/' as the separator of directories.
   *
   *@see loadSample(char*)
   *@see loadMusic(char*)
   *@param szPath The full path to the directory that contains the audio data
   */
  virtual void setDataSource( char* szPath )=0;

  /**
   * Loads a sample and returns the control object for the sample.
	 * Samples are loaded by default from the current directory,
   * the directory that is used to load the samples can be set with the
   * setDataSource() method.
   *
   *@see setDataSource(char*)
   *@param fileName The name of the file to be loaded (without the file extension)
   *@return An unique Sample object that represents the loaded sample
   */
  virtual Sample* loadSample( char* fileName )=0;

  /**
   * Plays a sample by id that was previously loaded.
   *
   *@see #loadSample(char*)
   *@param id The id of the sample to be played
   */
  virtual void playSample(unsigned int id )=0;

	virtual int loadedSamples()=0;

  /**
   * Tries to load a music file from the current data directory.
	 * When suitable file is found returns a control object for the music
	 * file if no suitable file is found returns NullSound object.
	 * Music files are loaded by default from the current directory,
	 * the directory that is used to load the samples can be set with
	 * the setDataSource() method.
   *
   *@see setDataSource(char*)
   *@param fileName The name of the file to be loaded (without the file extension)
   *@return An unique Sample object that represents the loaded sample
   */
  virtual Music* loadMusic( char* fileName )=0;

  /**
   * Plays a track by id that was previously loaded.
   *
   *@see #loadMusic(char*)
   *@param id The id of the track to be played
   */
  virtual void playMusic( unsigned int id )=0;

	virtual int loadedMusic()=0;

	/**
	 * Routine called for initialisation purpose
	 * set vars to defaults and reset buffers
	 */
	virtual void init()=0;

	/**
	 * Frees all the resources that are used by the sound representation.
	 * This method is quite slow to execute and should preferrably be called upon
	 * exiting the game or between level changes etc.
	 */
	virtual void free()=0;

	/**
	 * Update status information about playing buffers etc.
	 * calls updateStatus for all loaded samples
	 */
	virtual void updateStatus()=0;

	/**
	 * Returns an information String representing unique representation
	 * of the current driver loaded
	 */
	virtual const char* getDriverInfo()=0;

};

