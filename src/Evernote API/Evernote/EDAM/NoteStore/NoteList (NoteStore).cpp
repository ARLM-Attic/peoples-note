/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 */

#include "../NoteStore.h"
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
#include <Evernote/EDAM/Types.h>
#include <Evernote/EDAM/Error.h>
#include <Evernote/EDAM/Limits.h>

using namespace Evernote::EDAM::NoteStore;

NoteList::NoteList()
{
	memset(&__isset, 0, sizeof(Isset));
}

void NoteList::Read(Thrift::Protocol::TProtocol & iprot)
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
			if (field.GetType() == Thrift::Protocol::TypeI32)
			{
				this->startIndex = iprot.ReadI32();
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 2:
			if (field.GetType() == Thrift::Protocol::TypeI32)
			{
				this->totalNotes = iprot.ReadI32();
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 3:
			if (field.GetType() == Thrift::Protocol::TypeList)
			{
				{
					Thrift::Protocol::TList _list40;
					iprot.ReadListBegin(_list40);
					for (int _i41 = 0; _i41 < _list40.GetCount(); ++_i41)
					{
						Evernote::EDAM::Types::Note _elem42;
						_elem42.Read(iprot);
						this->notes.push_back(_elem42);
					}
					iprot.ReadListEnd();
				}
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 4:
			if (field.GetType() == Thrift::Protocol::TypeList)
			{
				{
					Thrift::Protocol::TList _list43;
					iprot.ReadListBegin(_list43);
					for (int _i44 = 0; _i44 < _list43.GetCount(); ++_i44)
					{
						Thrift::Protocol::TString _elem45;
						_elem45;
						iprot.ReadString(_elem45);
						this->stoppedWords.push_back(_elem45);
					}
					iprot.ReadListEnd();
				}
				this->__isset.stoppedWords = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 5:
			if (field.GetType() == Thrift::Protocol::TypeList)
			{
				{
					Thrift::Protocol::TList _list46;
					iprot.ReadListBegin(_list46);
					for (int _i47 = 0; _i47 < _list46.GetCount(); ++_i47)
					{
						Thrift::Protocol::TString _elem48;
						_elem48;
						iprot.ReadString(_elem48);
						this->searchedWords.push_back(_elem48);
					}
					iprot.ReadListEnd();
				}
				this->__isset.searchedWords = true;
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

void NoteList::Write(Thrift::Protocol::TProtocol & oprot)
{
	Thrift::Protocol::TStruct struc;
	struc.SetName(L"NoteList");
	oprot.WriteStructBegin(struc);
	{
		Thrift::Protocol::TField field;
		field.SetName(L"startIndex");
		field.SetType(Thrift::Protocol::TypeI32);
		field.SetID(1);
		oprot.WriteFieldBegin(field);
		oprot.WriteI32(this->startIndex);
		oprot.WriteFieldEnd();
	}
	{
		Thrift::Protocol::TField field;
		field.SetName(L"totalNotes");
		field.SetType(Thrift::Protocol::TypeI32);
		field.SetID(2);
		oprot.WriteFieldBegin(field);
		oprot.WriteI32(this->totalNotes);
		oprot.WriteFieldEnd();
	}
	{
		Thrift::Protocol::TField field;
		field.SetName(L"notes");
		field.SetType(Thrift::Protocol::TypeList);
		field.SetID(3);
		oprot.WriteFieldBegin(field);
		{
			Thrift::Protocol::TList list;
			list.SetElementType(Thrift::Protocol::TypeStruct);
			list.SetCount(this->notes.size());
			oprot.WriteListBegin(list);
			for (std::vector<Evernote::EDAM::Types::Note >::iterator _iter49(this->notes.begin()), end(this->notes.end()); _iter49 != end; ++_iter49)
			{
				(*_iter49).Write(oprot);
				oprot.WriteListEnd();
			}
		}
		oprot.WriteFieldEnd();
	}
	if (__isset.stoppedWords)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"stoppedWords");
		field.SetType(Thrift::Protocol::TypeList);
		field.SetID(4);
		oprot.WriteFieldBegin(field);
		{
			Thrift::Protocol::TList list;
			list.SetElementType(Thrift::Protocol::TypeString);
			list.SetCount(this->stoppedWords.size());
			oprot.WriteListBegin(list);
			for (std::vector<Thrift::Protocol::TString >::iterator _iter50(this->stoppedWords.begin()), end(this->stoppedWords.end()); _iter50 != end; ++_iter50)
			{
				oprot.WriteString((*_iter50));
				oprot.WriteListEnd();
			}
		}
		oprot.WriteFieldEnd();
	}
	if (__isset.searchedWords)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"searchedWords");
		field.SetType(Thrift::Protocol::TypeList);
		field.SetID(5);
		oprot.WriteFieldBegin(field);
		{
			Thrift::Protocol::TList list;
			list.SetElementType(Thrift::Protocol::TypeString);
			list.SetCount(this->searchedWords.size());
			oprot.WriteListBegin(list);
			for (std::vector<Thrift::Protocol::TString >::iterator _iter51(this->searchedWords.begin()), end(this->searchedWords.end()); _iter51 != end; ++_iter51)
			{
				oprot.WriteString((*_iter51));
				oprot.WriteListEnd();
			}
		}
		oprot.WriteFieldEnd();
	}
	oprot.WriteFieldStop();
	oprot.WriteStructEnd();
}

