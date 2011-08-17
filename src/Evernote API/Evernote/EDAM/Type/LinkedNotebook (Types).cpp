/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 */

#include "../Type.h"
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

using namespace Evernote::EDAM::Type;

LinkedNotebook::LinkedNotebook()
{
	::ZeroMemory(&__isset, sizeof(Isset));
}

void LinkedNotebook::Read(Thrift::Protocol::TProtocol & iprot)
{
	Thrift::Protocol::TStruct struc;
	iprot.ReadStructBegin(struc);
	for (;;)
	{
		Thrift::Protocol::TField field;
		iprot.ReadFieldBegin(field);
		if (field.GetType() == Thrift::Protocol::TypeStop)
			break;
		switch (field.GetID())
		{
		case 2:
			if (field.GetType() == Thrift::Protocol::TypeString)
			{
				iprot.ReadString(this->shareName);
				this->__isset.shareName = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 3:
			if (field.GetType() == Thrift::Protocol::TypeString)
			{
				iprot.ReadString(this->username);
				this->__isset.username = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 4:
			if (field.GetType() == Thrift::Protocol::TypeString)
			{
				iprot.ReadString(this->shardId);
				this->__isset.shardId = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 5:
			if (field.GetType() == Thrift::Protocol::TypeString)
			{
				iprot.ReadString(this->shareKey);
				this->__isset.shareKey = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 6:
			if (field.GetType() == Thrift::Protocol::TypeString)
			{
				iprot.ReadString(this->uri);
				this->__isset.uri = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 7:
			if (field.GetType() == Thrift::Protocol::TypeString)
			{
				iprot.ReadString(this->guid);
				this->__isset.guid = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 8:
			if (field.GetType() == Thrift::Protocol::TypeI32)
			{
				this->updateSequenceNum = iprot.ReadI32();
				this->__isset.updateSequenceNum = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		default: 
			Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			break;
		}
		iprot.ReadFieldEnd();
	}
	iprot.ReadStructEnd();
}

void LinkedNotebook::Write(Thrift::Protocol::TProtocol & oprot)
{
	Thrift::Protocol::TStruct struc;
	struc.SetName(L"LinkedNotebook");
	oprot.WriteStructBegin(struc);
	if (__isset.shareName)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"shareName");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(2);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->shareName);
		oprot.WriteFieldEnd();
	}
	if (__isset.username)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"username");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(3);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->username);
		oprot.WriteFieldEnd();
	}
	if (__isset.shardId)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"shardId");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(4);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->shardId);
		oprot.WriteFieldEnd();
	}
	if (__isset.shareKey)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"shareKey");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(5);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->shareKey);
		oprot.WriteFieldEnd();
	}
	if (__isset.uri)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"uri");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(6);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->uri);
		oprot.WriteFieldEnd();
	}
	if (__isset.guid)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"guid");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(7);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->guid);
		oprot.WriteFieldEnd();
	}
	if (__isset.updateSequenceNum)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"updateSequenceNum");
		field.SetType(Thrift::Protocol::TypeI32);
		field.SetID(8);
		oprot.WriteFieldBegin(field);
		oprot.WriteI32(this->updateSequenceNum);
		oprot.WriteFieldEnd();
	}
	oprot.WriteFieldStop();
	oprot.WriteStructEnd();
}

