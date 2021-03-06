#pragma once
#include "ISyncModel.h"

#include "EnInteropNote.h"
#include "Note.h"
#include "Notebook.h"
#include "SyncMessageQueue.h"
#include "Tag.h"

class EnNoteTranslator;
class Guid;
class IEnService;
class IMessagePump;
class INoteStore;
class ILogger;
class IUserModel;
class UserUpdater;

class SyncModel : public ISyncModel
{
// events

	MacroEvent(StatusUpdated)
	MacroEvent(SyncComplete)

// types

private:

	class LoggerRAII
	{
	private:

		ILogger & logger;

	public:

		LoggerRAII(ILogger & logger);

		~LoggerRAII();
	};

// data

private:

	EnNoteTranslator & enNoteTranslator;
	IEnService       & enService;
	IMessagePump     & messagePump;
	ILogger          & logger;
	IUserModel       & userModel;

	std::wstring username;
	std::wstring token;
	std::wstring shard;
	Guid         notebook;

	HANDLE syncThread;

	CRITICAL_SECTION lock;

	SyncMessageQueue messages;

	bool stopRequested;

	std::wstring statusText;
	double       syncProgress;

// interface

public:

	SyncModel
		( EnNoteTranslator & enNoteTranslator
		, IEnService       & enService
		, IMessagePump     & messagePump
		, IUserModel       & userModel
		, ILogger      & logger
		);

	~SyncModel();

	void ProcessMessages();

	void StopSync();

// ISyncModel implementation

public:

	virtual void BeginSync
		( const std::wstring & username
		, const std::wstring & token
		, const std::wstring & shard
		, const Guid         & notebook
		);

	virtual const wchar_t * GetStatusText();

	virtual double GetSyncProgress();

// utility functions

private:

	void CloseThread();

	void GetLocalNotes(EnInteropNoteList & notes);

	void FinishSync
		( const wchar_t * logMessage
		, const wchar_t * friendlyMessage
		);

	void PostProgressMessage     (double          progress);
	void PostTextMessage         (const wchar_t * text);
	void PostSyncCompleteMessage ();

	void ProcessNotes
		( const EnInteropNoteList & remoteNotes
		, INoteStore              & noteStore
		, bool                      fullSync
		);

	void ProcessNotebooks
		( const NotebookList & remoteNotebooks
		, INoteStore         & noteStore
		, bool                 fullSync
		);

	void ProcessTags
		( const TagList & remoteTags
		, INoteStore    & noteStore
		, bool            fullSync
		);

	void Sync();

	static DWORD WINAPI Sync(LPVOID param);

	void UpdateDefaultNotebook(INoteStore & noteStore);

	void UpdateModel             (INoteStore  & noteStore);
	void UpdateNotebooksAndNotes (UserUpdater & updater);
	void UpdateResources         (UserUpdater & updater);
	void UpdateTags              (UserUpdater & updater);
};
