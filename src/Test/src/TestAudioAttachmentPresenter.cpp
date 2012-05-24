#include "stdafx.h"
#include "AudioAttachmentPresenter.h"

#include "MockAudioPlayer.h"
#include "MockAudioPlayerView.h"
#include "MockCredentialsModel.h"
#include "MockNoteView.h"
#include "MockUserModel.h"

using namespace boost;
using namespace std;

//-----------------------
// auxilliary definitions
//-----------------------

struct AudioAttachmentPresenterFixture
{
	MockAudioPlayer      audioPlayer;
	MockAudioPlayerView  audioPlayerView;
	MockCredentialsModel credentialsModel;
	MockNoteView         noteView;
	MockUserModel        userModel;

	AudioAttachmentPresenter presenter;

	AudioAttachmentPresenterFixture()
		: presenter
			( audioPlayer
			, audioPlayerView
			, credentialsModel
			, noteView
			, userModel
			)
	{
	}
};

//-----------
// test cases
//-----------

BOOST_FIXTURE_TEST_CASE
	( AudioAttachmentPresenter_Cancel
	, AudioAttachmentPresenterFixture
	)
{
	audioPlayerView.isShown = true;
	audioPlayerView.SignalCancel();
	BOOST_CHECK(!audioPlayerView.isShown);
}

BOOST_FIXTURE_TEST_CASE
	( AudioAttachmentPresenter_Hide
	, AudioAttachmentPresenterFixture
	)
{
	audioPlayer.isPlaying = true;
	userModel.loadMethod = MockUserModel::LoadMethodLoad;
	audioPlayerView.SignalHide();
	BOOST_CHECK(!audioPlayer.isPlaying);
	BOOST_CHECK_EQUAL(userModel.loadMethod, MockUserModel::LoadMethodNone);
}

BOOST_FIXTURE_TEST_CASE
	( AudioAttachmentPresenter_Play
	, AudioAttachmentPresenterFixture
	)
{
}

BOOST_FIXTURE_TEST_CASE
	( AudioAttachmentPresenter_PlayAttachment
	, AudioAttachmentPresenterFixture
	)
{
}

BOOST_FIXTURE_TEST_CASE
	( AudioAttachmentPresenter_Show
	, AudioAttachmentPresenterFixture
	)
{
}

BOOST_FIXTURE_TEST_CASE
	( AudioAttachmentPresenter_Stop
	, AudioAttachmentPresenterFixture
	)
{
}
