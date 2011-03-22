#include "stdafx.h"
#include "VoiceEditorPresenter.h"

#include "MockAudio.h"
#include "MockNoteListView.h"
#include "MockVoiceEditorModel.h"
#include "MockVoiceEditorView.h"
#include "MockUserModel.h"

using namespace boost;
using namespace std;

//-----------------------
// auxilliary definitions
//-----------------------

struct VoiceEditorPresenterFixture
{
	MockAudio            audio;
	MockNoteListView     noteListView;
	MockVoiceEditorModel voiceEditorModel;
	MockVoiceEditorView  voiceEditorView;
	MockUserModel        userModel;

	VoiceEditorPresenter presenter;

	VoiceEditorPresenterFixture()
		: presenter
			( audio
			, noteListView
			, voiceEditorModel
			, voiceEditorView
			, userModel
			)
	{
	}
};

//-----------
// test cases
//-----------

BOOST_FIXTURE_TEST_CASE
	( VoiceEditorPresenter_Cancel
	, VoiceEditorPresenterFixture
	)
{
	voiceEditorView.isShown = true;

	voiceEditorView.SignalCancel();
	
	BOOST_CHECK(!voiceEditorView.isShown);
}

BOOST_FIXTURE_TEST_CASE
	( VoiceEditorPresenter_NewPhoto
	, VoiceEditorPresenterFixture
	)
{
	voiceEditorView.isShown = false;

	noteListView.SignalNewVoiceNote();
	
	BOOST_CHECK(voiceEditorView.isShown);
}
