#pragma once

#include "Attachment.h"
#include "Blob.h"
#include "DbLocation.h"
#include "ISignalProvider.h"
#include "Guid.h"
#include "Note.h"
#include "Notebook.h"
#include "RecognitionEntry.h"
#include "Resource.h"
#include "Tag.h"
#include "Thumbnail.h"

class ISqlBlob;

class IUserModel : public ISignalProvider
{
	MacroIEvent(Loaded)

public:

	typedef boost::shared_ptr<ISqlBlob> SqlBlob;

public:

	virtual void AddNote
		( const Note          & note
		, const std::wstring  & body
		, const std::wstring  & bodyText
		, const Guid          & notebook
		) = 0;

	virtual void AddNotebook(const Notebook & notebook) = 0;

	virtual void AddRecognitionEntry(const RecognitionEntry & entry) = 0;

	virtual void AddResource(const Resource & resource) = 0;

	virtual void AddTag(const Tag & tag) = 0;

	virtual void AddTagToNote
		( const Guid & tag
		, const Note & note
		) = 0;

	virtual void BeginTransaction() = 0;

	virtual void Compact() = 0;

	virtual void DeleteNote(const Guid & note) = 0;

	virtual void DeleteNoteTags(const Guid & note) = 0;

	virtual void DeleteNoteThumbnail(const Guid & note) = 0;

	virtual void EndTransaction() = 0;

	virtual bool Exists(const std::wstring & username) = 0;

	virtual void ExpungeNote(const Guid & note) = 0;

	virtual void ExpungeNotebook(const Guid & notebook) = 0;

	virtual void ExpungeTag(const Guid & tag) = 0;

	virtual std::wstring GetPasswordHash() = 0;

	virtual std::wstring GetUsername() = 0;

	virtual void GetDefaultNotebook(Guid & notebook) = 0;

	virtual void GetDeletedNotes(GuidList & notes) = 0;

	virtual int GetDirtyNoteCount(const Guid & notebook) = 0;

	virtual __int64 GetLastSyncEnTime() = 0;

	virtual void GetLastUsedNotebook(Guid & notebook) = 0;

	virtual void GetLastUsedNotebookOrDefault(Guid & notebook) = 0;

	virtual DbLocation GetLocation() = 0;

	virtual void GetNote(const Guid & guid, Note & note) = 0;

	virtual void GetNoteAttachments
		( const Guid     & note
		, AttachmentList & attachments
		) = 0;

	virtual void GetNotebook
		( const Guid & guid
		, Notebook   & notebook
		) = 0;

	virtual void GetNoteBody
		( const Guid   & guid
		, std::wstring & body
		) = 0;

	virtual void GetNoteResources
		( const Guid        & note
		, std::vector<Guid> & resources
		) = 0;

	virtual void GetNoteTags
		( const Note & note
		, TagList    & tags
		) = 0;

	virtual void GetNoteThumbnail
		( const Guid & guid
		, Thumbnail  & thumbnail
		) = 0;

	virtual void GetNotebooks(NotebookList & notebooks) = 0;

	virtual int GetNotebookUpdateCount(const Guid & notebook) = 0;

	virtual void GetNotes
		( Guid           notebook // leave empty, if not used
		, std::wstring   search   // leave empty, if not used
		, int            start    // set count to 0, if not used
		, int            count    // set to 0, if not used
		, NoteList     & notes
		) = 0;

	virtual std::wstring GetPath() = 0;

	virtual void GetResource
		( const std::string & hash
		, Blob              & blob
		) = 0;

	virtual void GetResource
		( const Guid & guid
		, Resource   & resource
		) = 0;

	virtual SqlBlob GetResourceData(const Guid & guid) = 0;

	virtual void GetResources(GuidList & resources) = 0;

	virtual __int64 GetSize() = 0;

	virtual int GetSyncVersion() = 0;

	virtual void GetTags(TagList & tags) = 0;

	virtual int GetUpdateCount() = 0;

	virtual int GetVersion() = 0;

	virtual void Load(const std::wstring & username) = 0;

	virtual void LoadAs
		( const std::wstring & oldUsername
		, const std::wstring & newUsername
		) = 0;

	virtual void LoadOrCreate(const std::wstring & username) = 0;

	virtual void MakeNotebookDefault(const Guid & notebook) = 0;

	virtual void MakeNotebookLastUsed(const Guid & notebook) = 0;

	virtual void MoveToCard() = 0;

	virtual void MoveToDevice() = 0;

	virtual void ReplaceNote
		( const Note          & note
		, const std::wstring  & body
		, const std::wstring  & bodyText
		, const Guid          & notebook
		) = 0;

	virtual void SetCredentials
		( const std::wstring & username
		, const std::wstring & passwordHash
		) = 0;

	virtual void SetLastSyncEnTime(__int64 enTime) = 0;
	
	virtual void SetNoteThumbnail
		( const Guid      & guid
		, const Thumbnail & thumbnail
		) = 0;

	virtual void SetNotebookUpdateCount
		( const Guid & notebook
		, int          updateCount
		) = 0;

	virtual void SetSyncVersion(int version) = 0;

	virtual void SetUpdateCount(int updateCount) = 0;

	virtual void Unload() = 0;

	virtual void UpdateNote
		( const Guid & note
		, const Note & replacement
		) = 0;

	virtual void UpdateNotebook
		( const Guid     & notebook
		, const Notebook & replacement
		) = 0;

	virtual void UpdateResource
		( const Guid     & resource
		, const Resource & replacement
		) = 0;

	virtual void UpdateTag
		( const Guid & tag
		, const Tag  & replacement
		) = 0;
};
