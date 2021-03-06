#include "stdafx.h"
#include "EnImportPresenter.h"

#include "EnNoteTranslator.h"
#include "MockEnImporter.h"
#include "Note.h"
#include "MockNoteListModel.h"
#include "MockNoteListView.h"
#include "MockUserModel.h"

#include <algorithm>

using namespace boost;
using namespace std;

template<typename T, int N>
void PushArray(vector<T> & v, const T (&a)[N])
{
	for (int i(0); i != N; ++i)
		v.push_back(a[i]);
}

Note MakeNote(wchar_t * name, int creationDate)
{
	Note note;
	note.name = name;
	note.creationDate = creationDate;
	return note;
}

Note MakeNote(const Guid & guid, wchar_t * name, int creationDate)
{
	Note note;
	note.guid = guid;
	note.name = name;
	note.creationDate = creationDate;
	return note;
}

BOOST_AUTO_TEST_CASE(EnImportPresenter_Import_Test0)
{
	EnNoteTranslator enNoteTranslator;
	MockEnImporter    enImporter;
	MockNoteListModel noteListModel;
	MockNoteListView  noteListView;
	MockUserModel     userModel;

	EnImportPresenter enImportPresenter
		( enNoteTranslator
		, enImporter
		, noteListModel
		, noteListView
		, userModel
		);

	noteListModel.notes.push_back(MakeNote(L"note-0", 0));

	enImporter.notes.push_back(MakeNote(L"note-1", 1));
	enImporter.notes.push_back(MakeNote(L"note-2", 2));
	enImporter.bodies.push_back(L"<en-note>body-1</en-note>");
	enImporter.bodies.push_back(L"<en-note>body-2</en-note>");

	noteListView.hasEnexPath = true;
	noteListView.enexPath    = L"data\\Mixed.enex";

	noteListView.SignalImport();

	typedef vector<MockUserModel::NoteRecord> NoteRecordList;
	const NoteRecordList & addedNotes = userModel.addedNotes;
	BOOST_REQUIRE_EQUAL(addedNotes.size(), 2);
	BOOST_CHECK_EQUAL(addedNotes.at(0).note.name, L"note-1");
	BOOST_CHECK_EQUAL(addedNotes.at(1).note.name, L"note-2");
	BOOST_CHECK_EQUAL(addedNotes.at(0).body, L"<en-note>body-1</en-note>");
	BOOST_CHECK_EQUAL(addedNotes.at(1).body, L"<en-note>body-2</en-note>");
	BOOST_CHECK_EQUAL(addedNotes.at(0).notebook, userModel.lastUsedNotebook);
	BOOST_CHECK_EQUAL(addedNotes.at(1).notebook, userModel.lastUsedNotebook);

	BOOST_CHECK(noteListModel.isReloaded);
}

BOOST_AUTO_TEST_CASE(EnImportPresenter_Import_Test1)
{
	EnNoteTranslator enNoteTranslator;
	MockEnImporter    enImporter;
	MockNoteListModel noteListModel;
	MockNoteListView  noteListView;
	MockUserModel     userModel;

	EnImportPresenter enImportPresenter
		( enNoteTranslator
		, enImporter
		, noteListModel
		, noteListView
		, userModel
		);

	enImporter.notes.push_back(MakeNote(L"note-0", 0));

	noteListView.hasEnexPath = false;
	noteListView.enexPath    = L"test-path";

	noteListView.SignalImport();

	BOOST_REQUIRE_EQUAL(userModel.addedNotes.size(), 0);
}
#include <stdarg.h>

BOOST_AUTO_TEST_CASE(EnImportPresenter_Resourceimport_Test)
{
	EnNoteTranslator  enNoteTranslator;
	MockEnImporter    enImporter;
	MockNoteListModel noteListModel;
	MockNoteListView	  noteListView;
	MockUserModel     userModel;

	EnImportPresenter enImportPresenter
		( enNoteTranslator
		, enImporter
		, noteListModel
		, noteListView
		, userModel
		);

	Guid guid;
	enImporter.notes.push_back(MakeNote(guid, L"note-0", 0));
	enImporter.bodies.push_back(L"");

	enImporter.resources.push_back(Resource());
	BYTE data[] = { 2, 3, 5, 7 };
	PushArray(enImporter.resources.back().Data, data);
	enImporter.resources.back().Note = guid;
	enImporter.resources.back().Mime = L"mime/type";

	noteListView.hasEnexPath = true;
	noteListView.enexPath    = L"data\\Mixed.enex";

	noteListView.SignalImport();

	BOOST_REQUIRE_EQUAL(userModel.resources.size(), 1);
	BOOST_CHECK_EQUAL(userModel.resources.at(0).Data.size(), 4);
	BOOST_CHECK_EQUAL(userModel.resources.at(0).Note, guid);
	BOOST_CHECK_EQUAL(userModel.resources.at(0).Mime, L"mime/type");
}
