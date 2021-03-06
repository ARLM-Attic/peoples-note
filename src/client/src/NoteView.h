#pragma once
#include "INoteView.h"

#include "HTMLayoutWindow.h"
#include "Note.h"
#include "NoteViewGestureProcessor.h"
#include "WindowRenderer.h"

class IAnimator;

class NoteView : public HTMLayoutWindow, public INoteView
{
	MacroEvent(Attachment)
	MacroEvent(Close)
	MacroEvent(Delete)
	MacroEvent(Edit)
	MacroEvent(EditTags)
	MacroEvent(PlayAttachment)
	MacroEvent(ToggleMaximize)

private:

	typedef htmlayout::dom::element element;

private:

	HINSTANCE instance;
	HWND      menuBar;
	HWND      parent;

	NoteViewGestureProcessor gestureProcessor;

	Note note;

	AttachmentViewInfoList attachments;

	POINT startScrollPos;

	bool isMaximized;

	std::set<int> dirtyCheckboxIds;

	element body;
	element vScroll;
	element hScroll;

// interface

public:

	NoteView
		( HINSTANCE         instance
		, bool              highRes
		, IAnimator       & animator
		, IHtmlDataLoader & htmlDataLoader
		);

	void Create(HWND parent);

	virtual void RegisterEventHandlers();

// INoteView implementation

public:

	virtual void GetBody(std::wstring & html);

	virtual void GetDirtyCheckboxIds(std::set<int> & dirtyCheckboxIds);

	virtual void GetNote(Note & note);

	virtual std::wstring GetSavePath
		( const std::wstring & title
		, const std::wstring & fileName
		, const std::wstring & directory
		);

	virtual Guid GetSelectedAttachmentGuid();

	virtual std::wstring GetSelectedAttachmentName();

	virtual void GetTitle(std::wstring & text);

	virtual void Hide();

	virtual bool IsDirty();

	virtual bool IsMaximized();

	virtual void MaximizeWindow();

	virtual void Render(Thumbnail & thumbnail);

	virtual void RestoreWindow();

	virtual void SetNote
		( const Note                   & note
		, const std::wstring           & titleText
		, const std::wstring           & subtitleText
		, const std::wstring           & bodyHtml
		, const AttachmentViewInfoList & attachments
		, const bool                     enableChrome
		);

	virtual void SetSubtitle(const std::wstring & subtitleText);

	virtual void SetWindowTitle(const std::wstring & text);

	virtual void Show();

// utility functions

private:

	POINT GetScrollPos();

	virtual int GetSelectedAttachmentIndex();

	ATOM RegisterClass(const std::wstring & wndClass);

	void Reset();

	void SetChrome(bool enable);

	void SetScrollPos(POINT pos);

	void UpdateAttachments();

	void UpdateScrollbar();

	void UpdateWindowState();

	bool TrySetHtml(const unsigned char * text, size_t textLength);

// gesture message handlers

private:

	void OnDelayedMouseDown();
	void OnGestureStart();
	void OnGestureStep();

// window message handlers

private:

	void OnActivate      (Msg<WM_ACTIVATE>      & msg);
	void OnClose         (Msg<WM_CLOSE>         & msg);
	void OnCommand       (Msg<WM_COMMAND>       & msg);
	void OnMouseDown     (Msg<WM_LBUTTONDOWN>   & msg);
	void OnMouseUp       (Msg<WM_LBUTTONUP>     & msg);
	void OnMouseMove     (Msg<WM_MOUSEMOVE>     & msg);
	void OnKeyUp         (Msg<WM_KEYUP>         & msg);
	void OnSettingChange (Msg<WM_SETTINGCHANGE> & msg);

	virtual void ProcessMessage(WndMsg &msg);

// HTMLayout message handlers

private:

	void OnAttachment     (BEHAVIOR_EVENT_PARAMS * params);
	void OnInput          (BEHAVIOR_EVENT_PARAMS * params);
	void OnPlayAttachment (BEHAVIOR_EVENT_PARAMS * params);
};
