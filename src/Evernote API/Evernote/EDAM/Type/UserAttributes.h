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

class UserAttributes
{
public:

	struct Isset
	{
		bool defaultLocationName;
		bool defaultLatitude;
		bool defaultLongitude;
		bool preactivation;
		bool viewedPromotions;
		bool incomingEmailAddress;
		bool recentMailedAddresses;
		bool comments;
		bool dateAgreedToTermsOfService;
		bool maxReferrals;
		bool referralCount;
		bool refererCode;
		bool sentEmailDate;
		bool sentEmailCount;
		bool dailyEmailLimit;
		bool emailOptOutDate;
		bool partnerEmailOptInDate;
		bool preferredLanguage;
		bool preferredCountry;
		bool clipFullPage;
		bool twitterUserName;
		bool twitterId;
		bool groupName;
		bool recognitionLanguage;
		bool customerProfileId;
		bool referralProof;
		bool educationalDiscount;
		bool businessAddress;
	};

	Thrift::Protocol::TString defaultLocationName;
	double defaultLatitude;
	double defaultLongitude;
	bool preactivation;
	std::vector<Thrift::Protocol::TString > viewedPromotions;
	Thrift::Protocol::TString incomingEmailAddress;
	std::vector<Thrift::Protocol::TString > recentMailedAddresses;
	Thrift::Protocol::TString comments;
	Timestamp dateAgreedToTermsOfService;
	__int32 maxReferrals;
	__int32 referralCount;
	Thrift::Protocol::TString refererCode;
	Timestamp sentEmailDate;
	__int32 sentEmailCount;
	__int32 dailyEmailLimit;
	Timestamp emailOptOutDate;
	Timestamp partnerEmailOptInDate;
	Thrift::Protocol::TString preferredLanguage;
	Thrift::Protocol::TString preferredCountry;
	bool clipFullPage;
	Thrift::Protocol::TString twitterUserName;
	Thrift::Protocol::TString twitterId;
	Thrift::Protocol::TString groupName;
	Thrift::Protocol::TString recognitionLanguage;
	__int64 customerProfileId;
	Thrift::Protocol::TString referralProof;
	bool educationalDiscount;
	Thrift::Protocol::TString businessAddress;

	Isset __isset;

	UserAttributes();
	virtual ~UserAttributes() throw() {}

	void Read(Thrift::Protocol::TProtocol & iprot);
	void Write(Thrift::Protocol::TProtocol & oprot);
};
} // Type
} // EDAM
} // Evernote