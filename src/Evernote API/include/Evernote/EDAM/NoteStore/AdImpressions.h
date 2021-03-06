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

class AdImpressions
{
public:

	__int32 adId;
	__int32 impressionCount;
	__int32 impressionTime;

	AdImpressions();
	virtual ~AdImpressions() throw() {}

	void Read(Thrift::Protocol::TProtocol & iprot);
	void Write(Thrift::Protocol::TProtocol & oprot);
};
} // NoteStore
} // EDAM
} // Evernote
