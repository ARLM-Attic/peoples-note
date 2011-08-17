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

class NoteMetadata
{
public:

	struct Isset
	{
		bool title;
		bool contentLength;
		bool created;
		bool updated;
		bool updateSequenceNum;
		bool notebookGuid;
		bool tagGuids;
		bool attributes;
		bool largestResourceMime;
		bool largestResourceSize;
	};

	Evernote::EDAM::Type::Guid guid;
	Thrift::Protocol::TString title;
	__int32 contentLength;
	Evernote::EDAM::Type::Timestamp created;
	Evernote::EDAM::Type::Timestamp updated;
	__int32 updateSequenceNum;
	Thrift::Protocol::TString notebookGuid;
	std::vector<Evernote::EDAM::Type::Guid > tagGuids;
	Evernote::EDAM::Type::NoteAttributes attributes;
	Thrift::Protocol::TString largestResourceMime;
	__int32 largestResourceSize;

	Isset __isset;

	NoteMetadata();
	virtual ~NoteMetadata() throw() {}

	void Read(Thrift::Protocol::TProtocol & iprot);
	void Write(Thrift::Protocol::TProtocol & oprot);
};
} // NoteStore
} // EDAM
} // Evernote
