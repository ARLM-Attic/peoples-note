/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 */

#include "../UserStore.h"
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <windows.h>
#include <Thrift/Thrift.h>
#include <Thrift/Protocol.h>
#include <Thrift/Transport.h>
#include <Evernote/EDAM/Type.h>
#include <Evernote/EDAM/Error.h>

using namespace Evernote::EDAM::UserStore;

bool UserStore::Client::checkVersion(Thrift::Protocol::TString clientName, __int16 edamVersionMajor, __int16 edamVersionMinor)
{
	send_checkVersion(clientName, edamVersionMajor, edamVersionMinor);
	return recv_checkVersion();
}

void UserStore::Client::send_checkVersion(Thrift::Protocol::TString clientName, __int16 edamVersionMajor, __int16 edamVersionMinor)
{
	oprot_.WriteMessageBegin(Thrift::Protocol::TMessage(L"checkVersion", Thrift::Protocol::MessageCall, seqid_));
	checkVersion_args args;
	args.clientName = clientName;
	args.__isset.clientName = true;
	args.edamVersionMajor = edamVersionMajor;
	args.__isset.edamVersionMajor = true;
	args.edamVersionMinor = edamVersionMinor;
	args.__isset.edamVersionMinor = true;
	args.Write(oprot_);
	oprot_.WriteMessageEnd();
	oprot_.GetTransport().Flush();
}

bool UserStore::Client::recv_checkVersion()
{
	Thrift::Protocol::TMessage msg;
	iprot_.ReadMessageBegin(msg);
	if (msg.GetType() == Thrift::Protocol::MessageException)
	{
		Thrift::TApplicationException x = Thrift::TApplicationException::Read(iprot_);
		iprot_.ReadMessageEnd();
		throw x;
	}
	checkVersion_result result;
	result.Read(iprot_);
	iprot_.ReadMessageEnd();
	if (result.__isset.success)
	{
		return result.success;
	}
	throw Thrift::TApplicationException(Thrift::TApplicationException::MissingResult, L"checkVersion failed: unknown result");
}

AuthenticationResult UserStore::Client::authenticate(Thrift::Protocol::TString username, Thrift::Protocol::TString password, Thrift::Protocol::TString consumerKey, Thrift::Protocol::TString consumerSecret)
{
	send_authenticate(username, password, consumerKey, consumerSecret);
	return recv_authenticate();
}

void UserStore::Client::send_authenticate(Thrift::Protocol::TString username, Thrift::Protocol::TString password, Thrift::Protocol::TString consumerKey, Thrift::Protocol::TString consumerSecret)
{
	oprot_.WriteMessageBegin(Thrift::Protocol::TMessage(L"authenticate", Thrift::Protocol::MessageCall, seqid_));
	authenticate_args args;
	args.username = username;
	args.__isset.username = true;
	args.password = password;
	args.__isset.password = true;
	args.consumerKey = consumerKey;
	args.__isset.consumerKey = true;
	args.consumerSecret = consumerSecret;
	args.__isset.consumerSecret = true;
	args.Write(oprot_);
	oprot_.WriteMessageEnd();
	oprot_.GetTransport().Flush();
}

AuthenticationResult UserStore::Client::recv_authenticate()
{
	Thrift::Protocol::TMessage msg;
	iprot_.ReadMessageBegin(msg);
	if (msg.GetType() == Thrift::Protocol::MessageException)
	{
		Thrift::TApplicationException x = Thrift::TApplicationException::Read(iprot_);
		iprot_.ReadMessageEnd();
		throw x;
	}
	authenticate_result result;
	result.Read(iprot_);
	iprot_.ReadMessageEnd();
	if (result.__isset.success)
	{
		return result.success;
	}
	if (result.__isset.userException)
	{
		throw result.userException;
	}
	if (result.__isset.systemException)
	{
		throw result.systemException;
	}
	throw Thrift::TApplicationException(Thrift::TApplicationException::MissingResult, L"authenticate failed: unknown result");
}

AuthenticationResult UserStore::Client::refreshAuthentication(Thrift::Protocol::TString authenticationToken)
{
	send_refreshAuthentication(authenticationToken);
	return recv_refreshAuthentication();
}

void UserStore::Client::send_refreshAuthentication(Thrift::Protocol::TString authenticationToken)
{
	oprot_.WriteMessageBegin(Thrift::Protocol::TMessage(L"refreshAuthentication", Thrift::Protocol::MessageCall, seqid_));
	refreshAuthentication_args args;
	args.authenticationToken = authenticationToken;
	args.__isset.authenticationToken = true;
	args.Write(oprot_);
	oprot_.WriteMessageEnd();
	oprot_.GetTransport().Flush();
}

AuthenticationResult UserStore::Client::recv_refreshAuthentication()
{
	Thrift::Protocol::TMessage msg;
	iprot_.ReadMessageBegin(msg);
	if (msg.GetType() == Thrift::Protocol::MessageException)
	{
		Thrift::TApplicationException x = Thrift::TApplicationException::Read(iprot_);
		iprot_.ReadMessageEnd();
		throw x;
	}
	refreshAuthentication_result result;
	result.Read(iprot_);
	iprot_.ReadMessageEnd();
	if (result.__isset.success)
	{
		return result.success;
	}
	if (result.__isset.userException)
	{
		throw result.userException;
	}
	if (result.__isset.systemException)
	{
		throw result.systemException;
	}
	throw Thrift::TApplicationException(Thrift::TApplicationException::MissingResult, L"refreshAuthentication failed: unknown result");
}

Evernote::EDAM::Type::User UserStore::Client::getUser(Thrift::Protocol::TString authenticationToken)
{
	send_getUser(authenticationToken);
	return recv_getUser();
}

void UserStore::Client::send_getUser(Thrift::Protocol::TString authenticationToken)
{
	oprot_.WriteMessageBegin(Thrift::Protocol::TMessage(L"getUser", Thrift::Protocol::MessageCall, seqid_));
	getUser_args args;
	args.authenticationToken = authenticationToken;
	args.__isset.authenticationToken = true;
	args.Write(oprot_);
	oprot_.WriteMessageEnd();
	oprot_.GetTransport().Flush();
}

Evernote::EDAM::Type::User UserStore::Client::recv_getUser()
{
	Thrift::Protocol::TMessage msg;
	iprot_.ReadMessageBegin(msg);
	if (msg.GetType() == Thrift::Protocol::MessageException)
	{
		Thrift::TApplicationException x = Thrift::TApplicationException::Read(iprot_);
		iprot_.ReadMessageEnd();
		throw x;
	}
	getUser_result result;
	result.Read(iprot_);
	iprot_.ReadMessageEnd();
	if (result.__isset.success)
	{
		return result.success;
	}
	if (result.__isset.userException)
	{
		throw result.userException;
	}
	if (result.__isset.systemException)
	{
		throw result.systemException;
	}
	throw Thrift::TApplicationException(Thrift::TApplicationException::MissingResult, L"getUser failed: unknown result");
}

PublicUserInfo UserStore::Client::getPublicUserInfo(Thrift::Protocol::TString username)
{
	send_getPublicUserInfo(username);
	return recv_getPublicUserInfo();
}

void UserStore::Client::send_getPublicUserInfo(Thrift::Protocol::TString username)
{
	oprot_.WriteMessageBegin(Thrift::Protocol::TMessage(L"getPublicUserInfo", Thrift::Protocol::MessageCall, seqid_));
	getPublicUserInfo_args args;
	args.username = username;
	args.__isset.username = true;
	args.Write(oprot_);
	oprot_.WriteMessageEnd();
	oprot_.GetTransport().Flush();
}

PublicUserInfo UserStore::Client::recv_getPublicUserInfo()
{
	Thrift::Protocol::TMessage msg;
	iprot_.ReadMessageBegin(msg);
	if (msg.GetType() == Thrift::Protocol::MessageException)
	{
		Thrift::TApplicationException x = Thrift::TApplicationException::Read(iprot_);
		iprot_.ReadMessageEnd();
		throw x;
	}
	getPublicUserInfo_result result;
	result.Read(iprot_);
	iprot_.ReadMessageEnd();
	if (result.__isset.success)
	{
		return result.success;
	}
	if (result.__isset.notFoundException)
	{
		throw result.notFoundException;
	}
	if (result.__isset.systemException)
	{
		throw result.systemException;
	}
	if (result.__isset.userException)
	{
		throw result.userException;
	}
	throw Thrift::TApplicationException(Thrift::TApplicationException::MissingResult, L"getPublicUserInfo failed: unknown result");
}

UserStore::Processor::Processor(Iface & iface) : iface_(iface)
{
	processMap_[L"checkVersion"] = &Processor::checkVersion_Process;
	processMap_[L"authenticate"] = &Processor::authenticate_Process;
	processMap_[L"refreshAuthentication"] = &Processor::refreshAuthentication_Process;
	processMap_[L"getUser"] = &Processor::getUser_Process;
	processMap_[L"getPublicUserInfo"] = &Processor::getPublicUserInfo_Process;
}

bool UserStore::Processor::Process(Thrift::Protocol::TProtocol & iprot, Thrift::Protocol::TProtocol & oprot)
{
	Thrift::Protocol::TMessage msg;
	iprot.ReadMessageBegin(msg);
	ProcessMap::iterator fn = processMap_.find(msg.GetName());
	if (fn == processMap_.end())
	{
		Thrift::Protocol::TProtocolUtil::Skip(iprot, Thrift::Protocol::TypeStruct);
		iprot.ReadMessageEnd();
		Thrift::TApplicationException x(Thrift::TApplicationException::UnknownMethod, (std::wstring(L"Invalid method name: '") + msg.GetName() + L"'").c_str());
		oprot.WriteMessageBegin(Thrift::Protocol::TMessage(msg.GetName(), Thrift::Protocol::MessageException, msg.GetSeqID()));
		x.Write(oprot);
		oprot.WriteMessageEnd();
		oprot.GetTransport().Flush();
		return true;
	}
	(this->*fn->second)(msg.GetSeqID(), iprot, oprot);
	return true;
}

void UserStore::Processor::checkVersion_Process(int seqid, Thrift::Protocol::TProtocol & iprot, Thrift::Protocol::TProtocol & oprot)
{
	checkVersion_args args;
	args.Read(iprot);
	iprot.ReadMessageEnd();
	checkVersion_result result;
	result.success = iface_.checkVersion(args.clientName, args.edamVersionMajor, args.edamVersionMinor);
	oprot.WriteMessageBegin(Thrift::Protocol::TMessage(L"checkVersion", Thrift::Protocol::MessageReply, seqid)); 
	result.Write(oprot);
	oprot.WriteMessageEnd();
	oprot.GetTransport().Flush();
}

void UserStore::Processor::authenticate_Process(int seqid, Thrift::Protocol::TProtocol & iprot, Thrift::Protocol::TProtocol & oprot)
{
	authenticate_args args;
	args.Read(iprot);
	iprot.ReadMessageEnd();
	authenticate_result result;
	try
	{
		result.success = iface_.authenticate(args.username, args.password, args.consumerKey, args.consumerSecret);
	}
	catch (Evernote::EDAM::Error::EDAMUserException userException)
	{
		result.userException = userException;
	}
	catch (Evernote::EDAM::Error::EDAMSystemException systemException)
	{
		result.systemException = systemException;
	}
	oprot.WriteMessageBegin(Thrift::Protocol::TMessage(L"authenticate", Thrift::Protocol::MessageReply, seqid)); 
	result.Write(oprot);
	oprot.WriteMessageEnd();
	oprot.GetTransport().Flush();
}

void UserStore::Processor::refreshAuthentication_Process(int seqid, Thrift::Protocol::TProtocol & iprot, Thrift::Protocol::TProtocol & oprot)
{
	refreshAuthentication_args args;
	args.Read(iprot);
	iprot.ReadMessageEnd();
	refreshAuthentication_result result;
	try
	{
		result.success = iface_.refreshAuthentication(args.authenticationToken);
	}
	catch (Evernote::EDAM::Error::EDAMUserException userException)
	{
		result.userException = userException;
	}
	catch (Evernote::EDAM::Error::EDAMSystemException systemException)
	{
		result.systemException = systemException;
	}
	oprot.WriteMessageBegin(Thrift::Protocol::TMessage(L"refreshAuthentication", Thrift::Protocol::MessageReply, seqid)); 
	result.Write(oprot);
	oprot.WriteMessageEnd();
	oprot.GetTransport().Flush();
}

void UserStore::Processor::getUser_Process(int seqid, Thrift::Protocol::TProtocol & iprot, Thrift::Protocol::TProtocol & oprot)
{
	getUser_args args;
	args.Read(iprot);
	iprot.ReadMessageEnd();
	getUser_result result;
	try
	{
		result.success = iface_.getUser(args.authenticationToken);
	}
	catch (Evernote::EDAM::Error::EDAMUserException userException)
	{
		result.userException = userException;
	}
	catch (Evernote::EDAM::Error::EDAMSystemException systemException)
	{
		result.systemException = systemException;
	}
	oprot.WriteMessageBegin(Thrift::Protocol::TMessage(L"getUser", Thrift::Protocol::MessageReply, seqid)); 
	result.Write(oprot);
	oprot.WriteMessageEnd();
	oprot.GetTransport().Flush();
}

void UserStore::Processor::getPublicUserInfo_Process(int seqid, Thrift::Protocol::TProtocol & iprot, Thrift::Protocol::TProtocol & oprot)
{
	getPublicUserInfo_args args;
	args.Read(iprot);
	iprot.ReadMessageEnd();
	getPublicUserInfo_result result;
	try
	{
		result.success = iface_.getPublicUserInfo(args.username);
	}
	catch (Evernote::EDAM::Error::EDAMNotFoundException notFoundException)
	{
		result.notFoundException = notFoundException;
	}
	catch (Evernote::EDAM::Error::EDAMSystemException systemException)
	{
		result.systemException = systemException;
	}
	catch (Evernote::EDAM::Error::EDAMUserException userException)
	{
		result.userException = userException;
	}
	oprot.WriteMessageBegin(Thrift::Protocol::TMessage(L"getPublicUserInfo", Thrift::Protocol::MessageReply, seqid)); 
	result.Write(oprot);
	oprot.WriteMessageEnd();
	oprot.GetTransport().Flush();
}

UserStore::checkVersion_args::checkVersion_args()
{
	edamVersionMajor = 1;

	edamVersionMinor = 19;

	::ZeroMemory(&__isset, sizeof(Isset));
}

void UserStore::checkVersion_args::Read(Thrift::Protocol::TProtocol & iprot)
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
				iprot.ReadString(this->clientName);
				this->__isset.clientName = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 2:
			if (field.GetType() == Thrift::Protocol::TypeI16)
			{
				this->edamVersionMajor = iprot.ReadI16();
				this->__isset.edamVersionMajor = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 3:
			if (field.GetType() == Thrift::Protocol::TypeI16)
			{
				this->edamVersionMinor = iprot.ReadI16();
				this->__isset.edamVersionMinor = true;
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

void UserStore::checkVersion_args::Write(Thrift::Protocol::TProtocol & oprot)
{
	Thrift::Protocol::TStruct struc;
	struc.SetName(L"checkVersion_args");
	oprot.WriteStructBegin(struc);
	if (__isset.clientName)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"clientName");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(1);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->clientName);
		oprot.WriteFieldEnd();
	}
	if (__isset.edamVersionMajor)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"edamVersionMajor");
		field.SetType(Thrift::Protocol::TypeI16);
		field.SetID(2);
		oprot.WriteFieldBegin(field);
		oprot.WriteI16(this->edamVersionMajor);
		oprot.WriteFieldEnd();
	}
	if (__isset.edamVersionMinor)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"edamVersionMinor");
		field.SetType(Thrift::Protocol::TypeI16);
		field.SetID(3);
		oprot.WriteFieldBegin(field);
		oprot.WriteI16(this->edamVersionMinor);
		oprot.WriteFieldEnd();
	}
	oprot.WriteFieldStop();
	oprot.WriteStructEnd();
}

UserStore::checkVersion_result::checkVersion_result()
{
	::ZeroMemory(&__isset, sizeof(Isset));
}

void UserStore::checkVersion_result::Read(Thrift::Protocol::TProtocol & iprot)
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
		case 0:
			if (field.GetType() == Thrift::Protocol::TypeBool)
			{
				this->success = iprot.ReadBool();
				this->__isset.success = true;
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

void UserStore::checkVersion_result::Write(Thrift::Protocol::TProtocol & oprot)
{
	Thrift::Protocol::TStruct struc;
	struc.SetName(L"checkVersion_result");
	oprot.WriteStructBegin(struc);

	if (this->__isset.success)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"success");
		field.SetType(Thrift::Protocol::TypeBool);
		field.SetID(0);
		oprot.WriteFieldBegin(field);
		oprot.WriteBool(this->success);
		oprot.WriteFieldEnd();
	}

	oprot.WriteFieldStop();
	oprot.WriteStructEnd();
}
UserStore::authenticate_args::authenticate_args()
{
	::ZeroMemory(&__isset, sizeof(Isset));
}

void UserStore::authenticate_args::Read(Thrift::Protocol::TProtocol & iprot)
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
				iprot.ReadString(this->username);
				this->__isset.username = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 2:
			if (field.GetType() == Thrift::Protocol::TypeString)
			{
				iprot.ReadString(this->password);
				this->__isset.password = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 3:
			if (field.GetType() == Thrift::Protocol::TypeString)
			{
				iprot.ReadString(this->consumerKey);
				this->__isset.consumerKey = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 4:
			if (field.GetType() == Thrift::Protocol::TypeString)
			{
				iprot.ReadString(this->consumerSecret);
				this->__isset.consumerSecret = true;
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

void UserStore::authenticate_args::Write(Thrift::Protocol::TProtocol & oprot)
{
	Thrift::Protocol::TStruct struc;
	struc.SetName(L"authenticate_args");
	oprot.WriteStructBegin(struc);
	if (__isset.username)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"username");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(1);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->username);
		oprot.WriteFieldEnd();
	}
	if (__isset.password)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"password");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(2);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->password);
		oprot.WriteFieldEnd();
	}
	if (__isset.consumerKey)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"consumerKey");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(3);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->consumerKey);
		oprot.WriteFieldEnd();
	}
	if (__isset.consumerSecret)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"consumerSecret");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(4);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->consumerSecret);
		oprot.WriteFieldEnd();
	}
	oprot.WriteFieldStop();
	oprot.WriteStructEnd();
}

UserStore::authenticate_result::authenticate_result()
{
	::ZeroMemory(&__isset, sizeof(Isset));
}

void UserStore::authenticate_result::Read(Thrift::Protocol::TProtocol & iprot)
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
		case 0:
			if (field.GetType() == Thrift::Protocol::TypeStruct)
			{
				this->success.Read(iprot);
				this->__isset.success = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 1:
			if (field.GetType() == Thrift::Protocol::TypeStruct)
			{
				this->userException.Read(iprot);
				this->__isset.userException = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 2:
			if (field.GetType() == Thrift::Protocol::TypeStruct)
			{
				this->systemException.Read(iprot);
				this->__isset.systemException = true;
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

void UserStore::authenticate_result::Write(Thrift::Protocol::TProtocol & oprot)
{
	Thrift::Protocol::TStruct struc;
	struc.SetName(L"authenticate_result");
	oprot.WriteStructBegin(struc);

	if (this->__isset.success)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"success");
		field.SetType(Thrift::Protocol::TypeStruct);
		field.SetID(0);
		oprot.WriteFieldBegin(field);
		this->success.Write(oprot);
		oprot.WriteFieldEnd();
	}
 else if (this->__isset.userException)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"userException");
		field.SetType(Thrift::Protocol::TypeStruct);
		field.SetID(1);
		oprot.WriteFieldBegin(field);
		this->userException.Write(oprot);
		oprot.WriteFieldEnd();
	}
 else if (this->__isset.systemException)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"systemException");
		field.SetType(Thrift::Protocol::TypeStruct);
		field.SetID(2);
		oprot.WriteFieldBegin(field);
		this->systemException.Write(oprot);
		oprot.WriteFieldEnd();
	}

	oprot.WriteFieldStop();
	oprot.WriteStructEnd();
}
UserStore::refreshAuthentication_args::refreshAuthentication_args()
{
	::ZeroMemory(&__isset, sizeof(Isset));
}

void UserStore::refreshAuthentication_args::Read(Thrift::Protocol::TProtocol & iprot)
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
				iprot.ReadString(this->authenticationToken);
				this->__isset.authenticationToken = true;
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

void UserStore::refreshAuthentication_args::Write(Thrift::Protocol::TProtocol & oprot)
{
	Thrift::Protocol::TStruct struc;
	struc.SetName(L"refreshAuthentication_args");
	oprot.WriteStructBegin(struc);
	if (__isset.authenticationToken)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"authenticationToken");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(1);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->authenticationToken);
		oprot.WriteFieldEnd();
	}
	oprot.WriteFieldStop();
	oprot.WriteStructEnd();
}

UserStore::refreshAuthentication_result::refreshAuthentication_result()
{
	::ZeroMemory(&__isset, sizeof(Isset));
}

void UserStore::refreshAuthentication_result::Read(Thrift::Protocol::TProtocol & iprot)
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
		case 0:
			if (field.GetType() == Thrift::Protocol::TypeStruct)
			{
				this->success.Read(iprot);
				this->__isset.success = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 1:
			if (field.GetType() == Thrift::Protocol::TypeStruct)
			{
				this->userException.Read(iprot);
				this->__isset.userException = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 2:
			if (field.GetType() == Thrift::Protocol::TypeStruct)
			{
				this->systemException.Read(iprot);
				this->__isset.systemException = true;
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

void UserStore::refreshAuthentication_result::Write(Thrift::Protocol::TProtocol & oprot)
{
	Thrift::Protocol::TStruct struc;
	struc.SetName(L"refreshAuthentication_result");
	oprot.WriteStructBegin(struc);

	if (this->__isset.success)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"success");
		field.SetType(Thrift::Protocol::TypeStruct);
		field.SetID(0);
		oprot.WriteFieldBegin(field);
		this->success.Write(oprot);
		oprot.WriteFieldEnd();
	}
 else if (this->__isset.userException)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"userException");
		field.SetType(Thrift::Protocol::TypeStruct);
		field.SetID(1);
		oprot.WriteFieldBegin(field);
		this->userException.Write(oprot);
		oprot.WriteFieldEnd();
	}
 else if (this->__isset.systemException)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"systemException");
		field.SetType(Thrift::Protocol::TypeStruct);
		field.SetID(2);
		oprot.WriteFieldBegin(field);
		this->systemException.Write(oprot);
		oprot.WriteFieldEnd();
	}

	oprot.WriteFieldStop();
	oprot.WriteStructEnd();
}
UserStore::getUser_args::getUser_args()
{
	::ZeroMemory(&__isset, sizeof(Isset));
}

void UserStore::getUser_args::Read(Thrift::Protocol::TProtocol & iprot)
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
				iprot.ReadString(this->authenticationToken);
				this->__isset.authenticationToken = true;
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

void UserStore::getUser_args::Write(Thrift::Protocol::TProtocol & oprot)
{
	Thrift::Protocol::TStruct struc;
	struc.SetName(L"getUser_args");
	oprot.WriteStructBegin(struc);
	if (__isset.authenticationToken)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"authenticationToken");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(1);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->authenticationToken);
		oprot.WriteFieldEnd();
	}
	oprot.WriteFieldStop();
	oprot.WriteStructEnd();
}

UserStore::getUser_result::getUser_result()
{
	::ZeroMemory(&__isset, sizeof(Isset));
}

void UserStore::getUser_result::Read(Thrift::Protocol::TProtocol & iprot)
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
		case 0:
			if (field.GetType() == Thrift::Protocol::TypeStruct)
			{
				this->success.Read(iprot);
				this->__isset.success = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 1:
			if (field.GetType() == Thrift::Protocol::TypeStruct)
			{
				this->userException.Read(iprot);
				this->__isset.userException = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 2:
			if (field.GetType() == Thrift::Protocol::TypeStruct)
			{
				this->systemException.Read(iprot);
				this->__isset.systemException = true;
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

void UserStore::getUser_result::Write(Thrift::Protocol::TProtocol & oprot)
{
	Thrift::Protocol::TStruct struc;
	struc.SetName(L"getUser_result");
	oprot.WriteStructBegin(struc);

	if (this->__isset.success)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"success");
		field.SetType(Thrift::Protocol::TypeStruct);
		field.SetID(0);
		oprot.WriteFieldBegin(field);
		this->success.Write(oprot);
		oprot.WriteFieldEnd();
	}
 else if (this->__isset.userException)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"userException");
		field.SetType(Thrift::Protocol::TypeStruct);
		field.SetID(1);
		oprot.WriteFieldBegin(field);
		this->userException.Write(oprot);
		oprot.WriteFieldEnd();
	}
 else if (this->__isset.systemException)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"systemException");
		field.SetType(Thrift::Protocol::TypeStruct);
		field.SetID(2);
		oprot.WriteFieldBegin(field);
		this->systemException.Write(oprot);
		oprot.WriteFieldEnd();
	}

	oprot.WriteFieldStop();
	oprot.WriteStructEnd();
}
UserStore::getPublicUserInfo_args::getPublicUserInfo_args()
{
	::ZeroMemory(&__isset, sizeof(Isset));
}

void UserStore::getPublicUserInfo_args::Read(Thrift::Protocol::TProtocol & iprot)
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

void UserStore::getPublicUserInfo_args::Write(Thrift::Protocol::TProtocol & oprot)
{
	Thrift::Protocol::TStruct struc;
	struc.SetName(L"getPublicUserInfo_args");
	oprot.WriteStructBegin(struc);
	if (__isset.username)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"username");
		field.SetType(Thrift::Protocol::TypeString);
		field.SetID(1);
		oprot.WriteFieldBegin(field);
		oprot.WriteString(this->username);
		oprot.WriteFieldEnd();
	}
	oprot.WriteFieldStop();
	oprot.WriteStructEnd();
}

UserStore::getPublicUserInfo_result::getPublicUserInfo_result()
{
	::ZeroMemory(&__isset, sizeof(Isset));
}

void UserStore::getPublicUserInfo_result::Read(Thrift::Protocol::TProtocol & iprot)
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
		case 0:
			if (field.GetType() == Thrift::Protocol::TypeStruct)
			{
				this->success.Read(iprot);
				this->__isset.success = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 1:
			if (field.GetType() == Thrift::Protocol::TypeStruct)
			{
				this->notFoundException.Read(iprot);
				this->__isset.notFoundException = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 2:
			if (field.GetType() == Thrift::Protocol::TypeStruct)
			{
				this->systemException.Read(iprot);
				this->__isset.systemException = true;
			}
			else
			{
				Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());
			}
			break;
		case 3:
			if (field.GetType() == Thrift::Protocol::TypeStruct)
			{
				this->userException.Read(iprot);
				this->__isset.userException = true;
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

void UserStore::getPublicUserInfo_result::Write(Thrift::Protocol::TProtocol & oprot)
{
	Thrift::Protocol::TStruct struc;
	struc.SetName(L"getPublicUserInfo_result");
	oprot.WriteStructBegin(struc);

	if (this->__isset.success)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"success");
		field.SetType(Thrift::Protocol::TypeStruct);
		field.SetID(0);
		oprot.WriteFieldBegin(field);
		this->success.Write(oprot);
		oprot.WriteFieldEnd();
	}
 else if (this->__isset.notFoundException)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"notFoundException");
		field.SetType(Thrift::Protocol::TypeStruct);
		field.SetID(1);
		oprot.WriteFieldBegin(field);
		this->notFoundException.Write(oprot);
		oprot.WriteFieldEnd();
	}
 else if (this->__isset.systemException)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"systemException");
		field.SetType(Thrift::Protocol::TypeStruct);
		field.SetID(2);
		oprot.WriteFieldBegin(field);
		this->systemException.Write(oprot);
		oprot.WriteFieldEnd();
	}
 else if (this->__isset.userException)
	{
		Thrift::Protocol::TField field;
		field.SetName(L"userException");
		field.SetType(Thrift::Protocol::TypeStruct);
		field.SetID(3);
		oprot.WriteFieldBegin(field);
		this->userException.Write(oprot);
		oprot.WriteFieldEnd();
	}

	oprot.WriteFieldStop();
	oprot.WriteStructEnd();
}
