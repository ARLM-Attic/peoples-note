#pragma once
#include "IEditorView.h"

#include "HTMLayoutWindow.h"
#include "Note.h"

class EditorView : public HTMLayoutWindow, public IEditorView
{
// events

	MacroEvent(Accept)
	MacroEvent(Cancel)
	MacroEvent(DeleteNote)

// data

private:

	HWND           parent;
	HWND           menuBar;
	HINSTANCE      instance;
	SHACTIVATEINFO activateInfo;

	bool isMaximized;

	Note note;

// interface

public:

	EditorView
		( HINSTANCE         instance
		, bool              highRes
		, IHtmlDataLoader & htmlDataLoader
		);

	void Create(HWND parent);

	virtual void RegisterEventHandlers();

// IEditorView implementation

public:

	virtual void GetBody(std::wstring & html);

	virtual void GetNote(Note & note);

	virtual void GetTitle(std::wstring & text);

	virtual void Hide();

	virtual void SetNote
		( const Note         & note
		, const std::wstring & bodyHtml
		);

	virtual void Show();

// window message handlers

private:

	void OnActivate      (Msg<WM_ACTIVATE>      & msg);
	void OnCommand       (Msg<WM_COMMAND>       & msg);
	void OnSettingChange (Msg<WM_SETTINGCHANGE> & msg);

	virtual void ProcessMessage(WndMsg &msg);

// HTMLayout message handlers

private:

	void OnCheck     (BEHAVIOR_EVENT_PARAMS * params);
	void OnHidePanel (BEHAVIOR_EVENT_PARAMS * params);
	void OnInput     (BEHAVIOR_EVENT_PARAMS * params);
	void OnShowPanel (BEHAVIOR_EVENT_PARAMS * params);

// utility functions

private:

	ATOM RegisterClass(const std::wstring & wndClass);

	void ResizeWindow();
};
