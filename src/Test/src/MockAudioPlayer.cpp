#include "stdafx.h"
#include "MockAUdioPlayer.h"

using namespace boost;

void MockAudioPlayer::Play(shared_ptr<ISqlBlob> & blob)
{
	isPlaying = true;
	this->blob = blob;
}

void MockAudioPlayer::Stop()
{
	isPlaying = false;
}