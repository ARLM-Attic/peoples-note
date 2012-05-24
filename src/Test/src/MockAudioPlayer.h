#pragma once
#include "IAudioPlayer.h"

class MockAudioPlayer : public IAudioPlayer
{
public:

	bool isPlaying;
	boost::shared_ptr<ISqlBlob> blob;

public:

	virtual void Play(boost::shared_ptr<ISqlBlob> & blob);

	virtual void Stop();
};
