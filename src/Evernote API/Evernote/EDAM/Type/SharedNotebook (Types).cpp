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

SharedNotebook::SharedNotebook()
{
	::ZeroMemory(&__isset, sizeof(Isset));
}

void SharedNotebook::Read(Thrift::Protocol::TProtocol & iprot)
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
			if (field.GetType() == Thrift::Protocol::TypeI64)
			{
				this->id = iprot.ReadI64();
				this->__isset.id = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 2:
			if (field.GetType() == Thrift::Protocol::TypeI32)
			{
				this->userId = iprot.ReadI32();
				this->__isset.userId = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 3:
			if (field.GetType() == Thrift::Protocol::TypeString)
			{
				iprot.ReadString(this->notebookGuid);
				this->__isset.notebookGuid = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 4:
			if (field.GetType() == Thrift::Protocol::TypeString)
			{
				iprot.ReadString(this->email);
				this->__isset.email = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 5:
			if (field.GetType() == Thrift::Protocol::TypeBool)
			{
				this->notebookModifiable = iprot.ReadBool();
				this->__isset.notebookModifiable = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 6:
			if (field.GetType() == Thrift::Protocol::TypeBool)
			{
				this->requireLogin = iprot.ReadBool();
				this->__isset.requireLogin = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 7:
			if (field.GetType() == Thrift::Protocol::TypeI64)
			{
				this->serviceCreated = iprot.ReadI64();
				this->__isset.serviceCreated = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 8:
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
		case 9:
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
		default: 
			Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			break;
		}
		iprot.ReadFieldEnd();
	}
	iprot.ReadStructEnd();
}

void SharedNotebook::Write(Thrift::Protocol::TProtocol & oprot)
{
	Thrift::Protocol::TStruct struc;
	struc.SetName(L"SharedNotebook");
	oprot.WriteStructBegin(struc);
	if (__isset.id)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"id");
		field.SetType(Thrift::Protocol::TypeI64);
		field.SetID(1);
		oprot.WriteFieldBegin(field);
		oprot.WriteI64(this->id);
		oprot.WriteFieldEnd();
	}
	if (__isset.userId)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"userId");
		field.SetType(Thrift::Protocol::TypeI32);
		field.SetID(2);
		oprot.WriteFieldBegin(field);
		oprot.WriteI32(this->userId);
		oprot.WriteFieldEnd();
	}
	if (__isset.notebookGuid)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"notebookGuid");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(3);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->notebookGuid);
		oprot.WriteFieldEnd();
	}
	if (__isset.email)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"email");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(4);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->email);
		oprot.WriteFieldEnd();
	}
	if (__isset.notebookModifiable)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"notebookModifiable");
		field.SetType(Thrift::Protocol::TypeBool);
		field.SetID(5);
		oprot.WriteFieldBegin(field);
		oprot.WriteBool(this->notebookModifiable);
		oprot.WriteFieldEnd();
	}
	if (__isset.requireLogin)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"requireLogin");
		field.SetType(Thrift::Protocol::TypeBool);
		field.SetID(6);
		oprot.WriteFieldBegin(field);
		oprot.WriteBool(this->requireLogin);
		oprot.WriteFieldEnd();
	}
	if (__isset.serviceCreated)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"serviceCreated");
		field.SetType(Thrift::Protocol::TypeI64);
		field.SetID(7);
		oprot.WriteFieldBegin(field);
		oprot.WriteI64(this->serviceCreated);
		oprot.WriteFieldEnd();
	}
	if (__isset.shareKey)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"shareKey");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(8);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->shareKey);
		oprot.WriteFieldEnd();
	}
	if (__isset.username)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"username");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(9);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->username);
		oprot.WriteFieldEnd();
	}
	oprot.WriteFieldStop();
	oprot.WriteStructEnd();
}

