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

class Tag
{
public:

	struct Isset
	{
		bool guid;
		bool name;
		bool parentGuid;
		bool updateSequenceNum;
	};

	Guid guid;
	Thrift::Protocol::TString name;
	Guid parentGuid;
	__int32 updateSequenceNum;

	Isset __isset;

	Tag();
	virtual ~Tag() throw() {}

	void Read(Thrift::Protocol::TProtocol & iprot);
	void Write(Thrift::Protocol::TProtocol & oprot);
};
} // Type
} // EDAM
} // Evernote
