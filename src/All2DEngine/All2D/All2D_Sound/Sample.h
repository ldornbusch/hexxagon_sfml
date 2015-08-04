// Sample.h: interface for the Sample class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMPLE_H__C09AC4A7_D5FF_4FFB_9AF5_510C1F7EE153__INCLUDED_)
#define AFX_SAMPLE_H__C09AC4A7_D5FF_4FFB_9AF5_510C1F7EE153__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Sound.h"

class Sample : public Sound  
{
public:
	Sample(){};
	virtual ~Sample(){};

  /**
   * Sets the volume of the sound. Value of 0.0 means that the sound should be
   * inaudible and value of 1.0 means the sound is played at its normal volume.
   * Values above 1.0 are treated as 1.0 and values below 0.0 are treated as 0.0.
   *
   * NOTE: This feature is optional as it can't be supported on all platform implementations,
   * but all implementations offer at least a "do nothing" method.
   *
   *@param volume The sounds volume.
   */
  virtual void setVolume( float volume )=0;
  
  /**
   * Sets the pan of the sound. Value of -1.0 means that the sound will be
   * heard only from the left speaker and value of 1.0 means that the sound
   * will be heard only from the right speaker. Value of 0.0 means that
   * the sound is heard with equal volume from both speakers.
   * Values above 1.0 are treated as 1.0 and values below -1.0 are treated as -1.0.
   * 
   * NOTE: This feature is optional as it can't be supported on all platform implementations,
   * but all implementations offer at least a "do nothing" method.
   * 
   *@param pan The pan of the sound.
   */
  virtual void setPan( float pan )=0;

  /**
   * Returns the volume of the sound. Value of 0.0 means that the sound should be
   * inaudible and value of 1.0 means the sound is played at its normal volume.
   * 
   *@return The sounds volume.
   */
  virtual float getVolume()=0;
  
  /**
   * Returns the pan of the sound. Value of -1.0 means that the sound will be
   * heard only from the left speaker and value of 1.0 means that the sound
   * will be heard only from the right speaker. Value of 0.0 means that
   * the sound is heard with equal volume from both speakers.
   * 
   * NOTE: This feature is optional as it can't be supported on all platform implementations,
   * but all implementations offer at least a "do nothing" method.
   * 
   *@return The pan of the sound.
   */
  virtual float getPan()=0;
  
  /**
   * Returns a copy of this sound object that is independent from the
   * original sound object. This new sound object can be started/stopped
   * independently from the original sound object, but it most likely
   * uses the same sample data. Using this method to get multiple instances
   * of one sound will save memory on some implementations and is thus the
   * preferred way to duplicate sound objects.
   *
   *@return A independent copy of this sound or null if copy fails.
   */
  virtual Sample* getCopy()=0;

};

#endif // !defined(AFX_SAMPLE_H__C09AC4A7_D5FF_4FFB_9AF5_510C1F7EE153__INCLUDED_)
