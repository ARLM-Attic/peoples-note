#pragma once

#include "ISignalProvider.h"

class Note;

class IEditorView : public ISignalProvider
{
	MacroIEvent(Accept)
	MacroIEvent(Cancel)
	MacroIEvent(DeleteNote)

public:

	virtual void GetBody(std::wstring & html) = 0;

	virtual void GetNote(Note & note) = 0;

	virtual void GetTitle(std::wstring & text) = 0;

	virtual void Hide() = 0;

	virtual void SetNote
		( const Note         & note
		, const std::wstring & bodyHtml
		) = 0;

	virtual void Show() = 0;
};
