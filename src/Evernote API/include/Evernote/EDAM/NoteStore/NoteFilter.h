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
#include <Evernote/EDAM/Types.h>
#include <Evernote/EDAM/Error.h>
#include <Evernote/EDAM/Limits.h>


namespace Evernote
{
namespace EDAM
{
namespace NoteStore
{

class NoteFilter
{
public:

	struct Isset
	{
		bool order;
		bool ascending;
		bool words;
		bool notebookGuid;
		bool tagGuids;
		bool timeZone;
		bool inactive;
	};

	__int32 order;
	bool ascending;
	Thrift::Protocol::TString words;
	Evernote::EDAM::Types::Guid notebookGuid;
	std::vector<Evernote::EDAM::Types::Guid > tagGuids;
	Thrift::Protocol::TString timeZone;
	bool inactive;

	Isset __isset;

	NoteFilter();
	virtual ~NoteFilter() throw() {}

	void Read(Thrift::Protocol::TProtocol & iprot);
	void Write(Thrift::Protocol::TProtocol & oprot);
};
} // NoteStore
} // EDAM
} // Evernote
