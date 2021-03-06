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
namespace Types
{

class Accounting
{
public:

	struct Isset
	{
		bool uploadLimit;
		bool uploadLimitEnd;
		bool uploadLimitNextMonth;
		bool premiumServiceStatus;
		bool premiumOrderNumber;
		bool premiumCommerceService;
		bool premiumServiceStart;
		bool premiumServiceSKU;
		bool lastSuccessfulCharge;
		bool lastFailedCharge;
		bool lastFailedChargeReason;
		bool nextPaymentDue;
		bool premiumLockUntil;
		bool updated;
		bool premiumSubscriptionNumber;
		bool lastRequestedCharge;
	};

	__int64 uploadLimit;
	Timestamp uploadLimitEnd;
	__int64 uploadLimitNextMonth;
	PremiumOrderStatus premiumServiceStatus;
	Thrift::Protocol::TString premiumOrderNumber;
	Thrift::Protocol::TString premiumCommerceService;
	Timestamp premiumServiceStart;
	Thrift::Protocol::TString premiumServiceSKU;
	Timestamp lastSuccessfulCharge;
	Timestamp lastFailedCharge;
	Thrift::Protocol::TString lastFailedChargeReason;
	Timestamp nextPaymentDue;
	Timestamp premiumLockUntil;
	Timestamp updated;
	Thrift::Protocol::TString premiumSubscriptionNumber;
	Timestamp lastRequestedCharge;

	Isset __isset;

	Accounting();
	virtual ~Accounting() throw() {}

	void Read(Thrift::Protocol::TProtocol & iprot);
	void Write(Thrift::Protocol::TProtocol & oprot);
};
} // Types
} // EDAM
} // Evernote
