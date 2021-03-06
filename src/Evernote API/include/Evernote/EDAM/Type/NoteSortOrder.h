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
enum NoteSortOrder
{
	CREATED = 1,
	UPDATED = 2,
	RELEVANCE = 3,
	UPDATE_SEQUENCE_NUMBER = 4,
	TITLE = 5,
}
;
} // Type
} // EDAM
} // Evernote
