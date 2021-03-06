#pragma once
#include "ISignalProvider.h"

#include "Blob.h"
#include "Guid.h"
#include "Notebook.h"
#include "NotebookViewStyle.h"

class INoteListView : public ISignalProvider
{
	MacroIEvent(About)
	MacroIEvent(ClearSearch)
	MacroIEvent(DeleteNote)
	MacroIEvent(Import)
	MacroIEvent(NewInkNote)
	MacroIEvent(NewNote)
	MacroIEvent(NewPhotoNote)
	MacroIEvent(NewVoiceNote)
	MacroIEvent(NotebookSelected)
	MacroIEvent(NotebookTitleStateChanged)
	MacroIEvent(OpenNote)
	MacroIEvent(PageDown)
	MacroIEvent(PageUp)
	MacroIEvent(Profile)
	MacroIEvent(Search)
	MacroIEvent(SearchChanged)
	MacroIEvent(SignIn)
	MacroIEvent(Sync)
	MacroIEvent(ViewStyleChanged)

public:

public:

	virtual ~INoteListView() {}

	virtual void AddNote
		( const std::wstring & html
		, const std::wstring & value
		,       bool           isDirty
		) = 0;

	virtual void ClearNotes() = 0;

	virtual void DisableSync() = 0;

	virtual void EnableSync() = 0;

	virtual bool GetEnexPath(std::wstring & path) = 0;

	virtual bool GetRequestedNotebookTitleState() = 0;

	virtual NotebookViewStyle GetRequestedViewStyle() = 0;

	virtual std::wstring GetSearchText() = 0;

	virtual Guid GetSelectedNotebookGuid() = 0;

	virtual Guid GetSelectedNoteGuid() = 0;

	virtual void GetThumbSize(SIZE & size) = 0;

	virtual void HideNotebookTitle() = 0;

	virtual void HidePageDown() = 0;

	virtual void HidePageUp() = 0;

	virtual void HideSyncButton() = 0;

	virtual void SelectNotebook(const Guid & notebook) = 0;

	virtual void SetNotebookMenu(const NotebookList & notebooks) = 0;

	virtual void SetProfileText(const std::wstring & text) = 0;

	virtual void SetProgress(double fraction) = 0;

	virtual void SetSearchButtonToClear() = 0;

	virtual void SetSearchButtonToSearch() = 0;

	virtual void SetSearchText(const std::wstring & text) = 0;

	virtual void SetSigninText(const std::wstring & text) = 0;

	virtual void SetStatusText(const std::wstring & text) = 0;

	virtual void SetSyncText(const std::wstring & text) = 0;

	virtual void SetViewStyle(NotebookViewStyle style) = 0;

	virtual void SetWindowTitle(const std::wstring & text) = 0;

	virtual void ShowNotebookTitle() = 0;

	virtual void ShowPageDown() = 0;

	virtual void ShowPageUp() = 0;

	virtual void ShowSyncButton() = 0;

	virtual void UpdateNotes() = 0;

	virtual void UpdateThumbnail(const Guid & note) = 0;
};
