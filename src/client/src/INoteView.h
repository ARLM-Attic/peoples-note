#pragma once

#include "AttachmentViewInfo.h"
#include "Blob.h"
#include "ISignalProvider.h"
#include "Thumbnail.h"

#include <set>

class Note;

class INoteView : public ISignalProvider
{
	MacroIEvent(Attachment)
	MacroIEvent(Close)
	MacroIEvent(Delete)
	MacroIEvent(Edit)
	MacroIEvent(EditTags)
	MacroIEvent(PlayAttachment)
	MacroIEvent(ToggleMaximize)

public:

	virtual void GetDirtyCheckboxIds(std::set<int> & dirtyCheckboxIds) = 0;

	virtual void GetNote(Note & note) = 0;

	virtual std::wstring GetSavePath
		( const std::wstring & title
		, const std::wstring & fileName
		, const std::wstring & directory
		) = 0;

	virtual Guid GetSelectedAttachmentGuid() = 0;

	virtual std::wstring GetSelectedAttachmentName() = 0;

	virtual void GetTitle(std::wstring & text) = 0;

	virtual void Hide() = 0;

	virtual bool IsDirty() = 0;

	virtual bool IsMaximized() = 0;

	virtual void MaximizeWindow() = 0;

	virtual void Render(Thumbnail & thumbnail) = 0;

	virtual void RestoreWindow() = 0;

	virtual void SetNote
		( const Note                   & note
		, const std::wstring           & titleText
		, const std::wstring           & subtitleText
		, const std::wstring           & bodyHtml
		, const AttachmentViewInfoList & attachments
		, const bool                     enableChrome
		) = 0;

	virtual void SetSubtitle(const std::wstring & subtitleText) = 0;

	virtual void SetWindowTitle(const std::wstring & text) = 0;

	virtual void Show() = 0;
};
