#include "stdafx.h"
#include "UserUpdater.h"

#include "Guid.h"
#include "INoteStore.h"
#include "IUserModel.h"

UserUpdater::UserUpdater
	( INoteStore & noteStore
	, IUserModel & userModel
	)
	: noteStore (noteStore)
	, userModel (userModel)
{
}

void UserUpdater::UpdateNote(const Guid & guid)
{
	Note     note;
	GuidList tags;
	noteStore.GetNote(guid, note, tags);

	userModel.UpdateNote(guid, note);
	userModel.DeleteNoteTags(guid);

	foreach (const Guid & tag, tags)
		userModel.AddTagToNote(tag, note);
}

void UserUpdater::UpdateNotebook(const Guid & guid)
{
	Notebook notebook;
	noteStore.GetNotebook(guid, notebook);
	userModel.UpdateNotebook(guid, notebook);
}

void UserUpdater::UpdateResource(const Guid & guid)
{
	Resource resource;
	noteStore.GetResource(guid, resource);
	userModel.UpdateResource(guid, resource);
}

void UserUpdater::UpdateTag(const Guid & guid)
{
	Tag tag;
	noteStore.GetTag(guid, tag);
	userModel.UpdateTag(guid, tag);
}
