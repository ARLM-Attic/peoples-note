#include "stdafx.h"
#include "Timestamp.h"
#include "Tools.h"

#include <sstream>

using namespace std;
using namespace Tools;

Timestamp::Timestamp()
	: unixTime (0)
{
}

Timestamp::Timestamp(time_t unixTime)
	: unixTime (unixTime)
{
}

bool Timestamp::IsValid() const
{
	return unixTime > 0;
}

wstring Timestamp::GetFormattedDateTime() const
{
	SYSTEMTIME time;
	UnixTimeToLocalSystemTime(unixTime, time);

	const LCID locale = LOCALE_USER_DEFAULT;

	vector<wchar_t> dateChars(11);
	::GetDateFormat
		( locale           // Locale
		, 0                // dwFlags
		, &time            // lpDate
		, L"yyyy-MM-dd"    // lpFormat
		, &dateChars[0]    // lpDateSTr
		, dateChars.size() // cchDate
		);

	vector<wchar_t> timeChars(6);
	::GetTimeFormat
		( locale           // Locale
		, 0                // dwFlags
		, &time            // lpTime
		, L"HH:mm"         // lpFormat
		, &timeChars[0]    // lpTimeStr
		, timeChars.size() // cchTime
		);

	wostringstream stream;
	stream << &dateChars[0] << L" " << &timeChars[0];
	return stream.str();
}

__int64 Timestamp::GetTime() const
{
	return unixTime;
}

bool Timestamp::operator < (const Timestamp & rhs) const
{
	return unixTime < rhs.unixTime;
}

Timestamp Timestamp::GetCurrentTime()
{
	SYSTEMTIME time;
	::GetSystemTime(&time);
	return SystemTimeToUnixTime(time);
}
