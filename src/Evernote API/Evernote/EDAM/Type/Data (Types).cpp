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

Data::Data()
{
	::ZeroMemory(&__isset, sizeof(Isset));
}

void Data::Read(Thrift::Protocol::TProtocol & iprot)
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
		case 1:
			if (field.GetType() == Thrift::Protocol::TypeString)
			{
				iprot.ReadBinary(this->bodyHash);
				this->__isset.bodyHash = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 2:
			if (field.GetType() == Thrift::Protocol::TypeI32)
			{
				this->size = iprot.ReadI32();
				this->__isset.size = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 3:
			if (field.GetType() == Thrift::Protocol::TypeString)
			{
				iprot.ReadBinary(this->body);
				this->__isset.body = true;
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

void Data::Write(Thrift::Protocol::TProtocol & oprot)
{
	Thrift::Protocol::TStruct struc;
	struc.SetName(L"Data");
	oprot.WriteStructBegin(struc);
	if (__isset.bodyHash)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"bodyHash");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(1);
		oprot.WriteFieldBegin(field);
		oprot.WriteBinary(this->bodyHash);
		oprot.WriteFieldEnd();
	}
	if (__isset.size)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"size");
		field.SetType(Thrift::Protocol::TypeI32);
		field.SetID(2);
		oprot.WriteFieldBegin(field);
		oprot.WriteI32(this->size);
		oprot.WriteFieldEnd();
	}
	if (__isset.body)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"body");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(3);
		oprot.WriteFieldBegin(field);
		oprot.WriteBinary(this->body);
		oprot.WriteFieldEnd();
	}
	oprot.WriteFieldStop();
	oprot.WriteStructEnd();
}

