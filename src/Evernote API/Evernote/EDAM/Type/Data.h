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

class Data
{
public:

	struct Isset
	{
		bool bodyHash;
		bool size;
		bool body;
	};

	Thrift::Protocol::TBinary bodyHash;
	__int32 size;
	Thrift::Protocol::TBinary body;

	Isset __isset;

	Data();
	virtual ~Data() throw() {}

	void Read(Thrift::Protocol::TProtocol & iprot);
	void Write(Thrift::Protocol::TProtocol & oprot);
};
} // Type
} // EDAM
} // Evernote
