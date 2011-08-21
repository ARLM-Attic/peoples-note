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

class NoteAttributes
{
public:

	struct Isset
	{
		bool subjectDate;
		bool latitude;
		bool longitude;
		bool altitude;
		bool author;
		bool source;
		bool sourceURL;
		bool sourceApplication;
		bool shareDate;
	};

	Timestamp subjectDate;
	double latitude;
	double longitude;
	double altitude;
	Thrift::Protocol::TString author;
	Thrift::Protocol::TString source;
	Thrift::Protocol::TString sourceURL;
	Thrift::Protocol::TString sourceApplication;
	Timestamp shareDate;

	Isset __isset;

	NoteAttributes();
	virtual ~NoteAttributes() throw() {}

	void Read(Thrift::Protocol::TProtocol & iprot);
	void Write(Thrift::Protocol::TProtocol & oprot);
};
} // Type
} // EDAM
} // Evernote