#include "stdafx.h"
#include "AboutPresenter.h"

#include "MockAboutView.h"
#include "MockNoteListView.h"

struct AboutPresenterFixture
{
	MockAboutView    aboutView;
	MockNoteListView noteListView;

	AboutPresenter aboutPresenter;

	AboutPresenterFixture()
		: aboutPresenter
			( aboutView
			, noteListView
			)
	{
	}
};

BOOST_FIXTURE_TEST_CASE
	( AboutPresenter_Test
	, AboutPresenterFixture
	)
{
	noteListView.SignalAbout();

	BOOST_CHECK(aboutView.isShown);

	aboutView.SignalClose();

	BOOST_CHECK(!aboutView.isShown);
}
