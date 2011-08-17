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
#include <Evernote/EDAM/Limits.h>


namespace Evernote
{
namespace EDAM
{
namespace Type
{

class Notebook
{
public:

	struct Isset
	{
		bool guid;
		bool name;
		bool updateSequenceNum;
		bool defaultNotebook;
		bool serviceCreated;
		bool serviceUpdated;
		bool publishing;
		bool published;
		bool stack;
		bool sharedNotebookIds;
	};

	Guid guid;
	Thrift::Protocol::TString name;
	__int32 updateSequenceNum;
	bool defaultNotebook;
	Timestamp serviceCreated;
	Timestamp serviceUpdated;
	Publishing publishing;
	bool published;
	Thrift::Protocol::TString stack;
	std::vector<__int64 > sharedNotebookIds;

	Isset __isset;

	Notebook();
	virtual ~Notebook() throw() {}

	void Read(Thrift::Protocol::TProtocol & iprot);
	void Write(Thrift::Protocol::TProtocol & oprot);
};
} // Type
} // EDAM
} // Evernote
