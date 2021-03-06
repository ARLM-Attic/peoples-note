#pragma once

/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 */

#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <windows.h>
#include <Thrift/Thrift.h>
#include <Thrift/Protocol.h>
#include <Thrift/Transport.h>
#include <Evernote/EDAM/UserStore.h>
#include <Evernote/EDAM/Type.h>
#include <Evernote/EDAM/Error.h>
#include <Evernote/EDAM/Limits.h>


namespace Evernote
{
namespace EDAM
{
namespace NoteStore
{

class NoteCollectionCounts
{
public:

	struct Isset
	{
		bool notebookCounts;
		bool tagCounts;
		bool trashCount;
	};

	std::map<Evernote::EDAM::Type::Guid, __int32 > notebookCounts;
	std::map<Evernote::EDAM::Type::Guid, __int32 > tagCounts;
	__int32 trashCount;

	Isset __isset;

	NoteCollectionCounts();
	virtual ~NoteCollectionCounts() throw() {}

	void Read(Thrift::Protocol::TProtocol & iprot);
	void Write(Thrift::Protocol::TProtocol & oprot);
};
} // NoteStore
} // EDAM
} // Evernote
