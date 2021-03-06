#pragma once

#include "EnInteropNote.h"
#include "Notebook.h"
#include "RecognitionEntry.h"
#include "Resource.h"
#include "SyncState.h"
#include "Tag.h"

class Guid;

class INoteStore
{
public:

	virtual void CreateNote
		( const Note         & note
		, const std::wstring & body
		, const ResourceList & resources
		, const Guid         & notebook
		, Note               & replacement
		, GuidList           & replacementTags
		) = 0;

	virtual void CreateNotebook
		( const Notebook & notebook
		, Notebook       & replacement
		) = 0;

	virtual void CreateTag
		( const Tag & tag
		, Tag       & replacement
		) = 0;

	virtual void DeleteNote(const Guid & guid) = 0;

	virtual void GetDefaultNotebook(Guid & notebook) = 0;

	virtual void GetNote
		( const Guid & guid
		, Note       & note
		, GuidList  & tags
		) = 0;

	virtual void GetNoteBody
		( const Note   & note
		, std::wstring & content
		) = 0;

	virtual void GetNoteResource
		( const Guid           & guid
		, Resource             & resource
		, RecognitionEntryList & recognitionEntries
		) = 0;

	virtual void GetNoteTagNames
		( const Note                & note
		, std::vector<std::wstring> & names
		) = 0;

	virtual void GetNotebook(const Guid & guid, Notebook & notebook) = 0;

	virtual void GetResource(const Guid & guid, Resource & resource) = 0;

	virtual void GetSyncState(SyncState & syncState) = 0;

	virtual void GetTag(const Guid & guid, Tag & tag) = 0;

	virtual void ListFullSyncEntries
		( EnInteropNoteList & notes
		, NotebookList      & notebooks
		, TagList           & tags
		, const Guid        & notebookFilter
		) = 0;

	virtual void ListIncrementalSyncEntries
		( int                 globalUpdateCount
		, int                 notebookUpdateCount
		, EnInteropNoteList & notes
		, NotebookList      & notebooks
		, TagList           & tags
		, std::vector<Guid> & expungedNotes
		, std::vector<Guid> & expungedNotebooks
		, std::vector<Guid> & expungedTags
		, std::vector<Guid> & resources
		, const Guid        & notebookFilter
		) = 0;

	virtual void UpdateNote
		( const Note         & note
		, const std::wstring & body
		, const GuidList     & tags
		, const ResourceList & resources
		, const Guid         & notebook
		, Note               & replacement
		, GuidList           & replacementTags
		) = 0;

	virtual void UpdateNotebook
		( const Notebook & notebook
		, Notebook       & replacement
		) = 0;

	virtual void UpdateTag
		( const Tag & tag
		, Tag       & replacement
		) = 0;
};
