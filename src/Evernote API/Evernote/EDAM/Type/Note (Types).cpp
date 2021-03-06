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

Note::Note()
{
	::ZeroMemory(&__isset, sizeof(Isset));
}

void Note::Read(Thrift::Protocol::TProtocol & iprot)
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
				iprot.ReadString(this->guid);
				this->__isset.guid = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 2:
			if (field.GetType() == Thrift::Protocol::TypeString)
			{
				iprot.ReadString(this->title);
				this->__isset.title = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 3:
			if (field.GetType() == Thrift::Protocol::TypeString)
			{
				iprot.ReadString(this->content);
				this->__isset.content = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 4:
			if (field.GetType() == Thrift::Protocol::TypeString)
			{
				iprot.ReadBinary(this->contentHash);
				this->__isset.contentHash = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 5:
			if (field.GetType() == Thrift::Protocol::TypeI32)
			{
				this->contentLength = iprot.ReadI32();
				this->__isset.contentLength = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 6:
			if (field.GetType() == Thrift::Protocol::TypeI64)
			{
				this->created = iprot.ReadI64();
				this->__isset.created = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 7:
			if (field.GetType() == Thrift::Protocol::TypeI64)
			{
				this->updated = iprot.ReadI64();
				this->__isset.updated = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 8:
			if (field.GetType() == Thrift::Protocol::TypeI64)
			{
				this->deleted = iprot.ReadI64();
				this->__isset.deleted = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 9:
			if (field.GetType() == Thrift::Protocol::TypeBool)
			{
				this->active = iprot.ReadBool();
				this->__isset.active = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 10:
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
		case 11:
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
		case 12:
			if (field.GetType() == Thrift::Protocol::TypeList)
			{
				{
					Thrift::Protocol::TList _list8;
					iprot.ReadListBegin(_list8);
					for (int _i9 = 0; _i9 < _list8.GetCount(); ++_i9)
					{
						Guid _elem10;
						iprot.ReadString(_elem10);
						this->tagGuids.push_back(_elem10);
					}
					iprot.ReadListEnd();
				}
				this->__isset.tagGuids = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 13:
			if (field.GetType() == Thrift::Protocol::TypeList)
			{
				{
					Thrift::Protocol::TList _list11;
					iprot.ReadListBegin(_list11);
					for (int _i12 = 0; _i12 < _list11.GetCount(); ++_i12)
					{
						Resource _elem13;
						_elem13.Read(iprot);
						this->resources.push_back(_elem13);
					}
					iprot.ReadListEnd();
				}
				this->__isset.resources = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 14:
			if (field.GetType() == Thrift::Protocol::TypeStruct)
			{
				this->attributes.Read(iprot);
				this->__isset.attributes = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 15:
			if (field.GetType() == Thrift::Protocol::TypeList)
			{
				{
					Thrift::Protocol::TList _list14;
					iprot.ReadListBegin(_list14);
					for (int _i15 = 0; _i15 < _list14.GetCount(); ++_i15)
					{
						Thrift::Protocol::TString _elem16;
						iprot.ReadString(_elem16);
						this->tagNames.push_back(_elem16);
					}
					iprot.ReadListEnd();
				}
				this->__isset.tagNames = true;
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

void Note::Write(Thrift::Protocol::TProtocol & oprot)
{
	Thrift::Protocol::TStruct struc;
	struc.SetName(L"Note");
	oprot.WriteStructBegin(struc);
	if (__isset.guid)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"guid");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(1);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->guid);
		oprot.WriteFieldEnd();
	}
	if (__isset.title)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"title");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(2);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->title);
		oprot.WriteFieldEnd();
	}
	if (__isset.content)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"content");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(3);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->content);
		oprot.WriteFieldEnd();
	}
	if (__isset.contentHash)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"contentHash");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(4);
		oprot.WriteFieldBegin(field);
		oprot.WriteBinary(this->contentHash);
		oprot.WriteFieldEnd();
	}
	if (__isset.contentLength)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"contentLength");
		field.SetType(Thrift::Protocol::TypeI32);
		field.SetID(5);
		oprot.WriteFieldBegin(field);
		oprot.WriteI32(this->contentLength);
		oprot.WriteFieldEnd();
	}
	if (__isset.created)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"created");
		field.SetType(Thrift::Protocol::TypeI64);
		field.SetID(6);
		oprot.WriteFieldBegin(field);
		oprot.WriteI64(this->created);
		oprot.WriteFieldEnd();
	}
	if (__isset.updated)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"updated");
		field.SetType(Thrift::Protocol::TypeI64);
		field.SetID(7);
		oprot.WriteFieldBegin(field);
		oprot.WriteI64(this->updated);
		oprot.WriteFieldEnd();
	}
	if (__isset.deleted)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"deleted");
		field.SetType(Thrift::Protocol::TypeI64);
		field.SetID(8);
		oprot.WriteFieldBegin(field);
		oprot.WriteI64(this->deleted);
		oprot.WriteFieldEnd();
	}
	if (__isset.active)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"active");
		field.SetType(Thrift::Protocol::TypeBool);
		field.SetID(9);
		oprot.WriteFieldBegin(field);
		oprot.WriteBool(this->active);
		oprot.WriteFieldEnd();
	}
	if (__isset.updateSequenceNum)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"updateSequenceNum");
		field.SetType(Thrift::Protocol::TypeI32);
		field.SetID(10);
		oprot.WriteFieldBegin(field);
		oprot.WriteI32(this->updateSequenceNum);
		oprot.WriteFieldEnd();
	}
	if (__isset.notebookGuid)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"notebookGuid");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(11);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->notebookGuid);
		oprot.WriteFieldEnd();
	}
	if (__isset.tagGuids)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"tagGuids");
		field.SetType(Thrift::Protocol::TypeList);
		field.SetID(12);
		oprot.WriteFieldBegin(field);
		{
			Thrift::Protocol::TList list;
			list.SetElementType(Thrift::Protocol::TypeString);
			list.SetCount(this->tagGuids.size());
			oprot.WriteListBegin(list);
			for (std::vector<Guid >::iterator _iter17(this->tagGuids.begin()), end(this->tagGuids.end()); _iter17 != end; ++_iter17)
			{
				oprot.WriteString((*_iter17));
				oprot.WriteListEnd();
			}
		}
		oprot.WriteFieldEnd();
	}
	if (__isset.resources)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"resources");
		field.SetType(Thrift::Protocol::TypeList);
		field.SetID(13);
		oprot.WriteFieldBegin(field);
		{
			Thrift::Protocol::TList list;
			list.SetElementType(Thrift::Protocol::TypeStruct);
			list.SetCount(this->resources.size());
			oprot.WriteListBegin(list);
			for (std::vector<Resource >::iterator _iter18(this->resources.begin()), end(this->resources.end()); _iter18 != end; ++_iter18)
			{
				(*_iter18).Write(oprot);
				oprot.WriteListEnd();
			}
		}
		oprot.WriteFieldEnd();
	}
	if (__isset.attributes)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"attributes");
		field.SetType(Thrift::Protocol::TypeStruct);
		field.SetID(14);
		oprot.WriteFieldBegin(field);
		this->attributes.Write(oprot);
		oprot.WriteFieldEnd();
	}
	if (__isset.tagNames)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"tagNames");
		field.SetType(Thrift::Protocol::TypeList);
		field.SetID(15);
		oprot.WriteFieldBegin(field);
		{
			Thrift::Protocol::TList list;
			list.SetElementType(Thrift::Protocol::TypeString);
			list.SetCount(this->tagNames.size());
			oprot.WriteListBegin(list);
			for (std::vector<Thrift::Protocol::TString >::iterator _iter19(this->tagNames.begin()), end(this->tagNames.end()); _iter19 != end; ++_iter19)
			{
				oprot.WriteString((*_iter19));
				oprot.WriteListEnd();
			}
		}
		oprot.WriteFieldEnd();
	}
	oprot.WriteFieldStop();
	oprot.WriteStructEnd();
}

