#include "stdafx.h"
#include "EnImporter.h"

#include "EnRecognitionParser.h"
#include "Note.h"
#include "Tools.h"

#include "RapidXML/rapidxml.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>

using namespace boost;
using namespace rapidxml;
using namespace std;
using namespace Tools;

void EnImporter::ImportNotes
	( const wstring        & text
	, NoteList             & notes
	, NoteBodyList         & bodies
	, ResourceList         & resources
	, RecognitionEntryList & recognitionEntries
	)
{
	if (text.empty())
		return;
	try
	{
		typedef xml_document<wchar_t> XmlDocument;
		auto_ptr<XmlDocument> doc(new XmlDocument());

		vector<wchar_t> textCopy;
		textCopy.reserve(text.size() + 1);
		copy(text.begin(), text.end(), ::back_inserter(textCopy));
		textCopy.push_back(L'\0');
		doc->parse<0>(&textCopy[0]);

		xml_node<wchar_t> * node(doc->first_node());
		while (node && 0 != wcscmp(node->name(), L"en-export"))
			node = node->next_sibling();
		if (!node)
			return;
		node = node->first_node();

		while (node)
		{
			Guid    guid;
			wstring body;
			wstring title;
			wstring created;

			xml_node<wchar_t> * noteNode(node->first_node());
			while (noteNode)
			{
				wstring name(noteNode->name(), noteNode->name_size());
				if (name == L"content")
				{
					if (noteNode->value_size() > 0)
						body = noteNode->value();
					else
					{
						xml_node<wchar_t> * contentNode(noteNode->first_node());
						if (contentNode)
						{
							body.assign
								( contentNode->value()
								, contentNode->value_size()
								);
						}
					}
				}
				else if (name == L"resource")
				{
					xml_node<wchar_t> * resourceNode(noteNode->first_node());
					resources.push_back(Resource());
					while (resourceNode)
					{
						wstring name(resourceNode->name(), resourceNode->name_size());
						if (name == L"data")
						{
							resources.back().Note = guid;
							Tools::DecodeBase64
								( resourceNode->value()
								, resources.back().Data
								);
							resources.back().Hash = HashWithMD5(resources.back().Data);
						}
						else if (name == L"mime")
						{
							resources.back().Mime = resourceNode->value();
						}
						else if (name == L"recognition")
						{
							xml_node<wchar_t> * dataNode(resourceNode->first_node());
							if (dataNode)
							{
								wstring value(dataNode->value(), dataNode->value_size());

								EnRecognitionParser parser;
								parser.Parse(value, recognitionEntries, resources.back().Guid);
							}
						}
						resourceNode = resourceNode->next_sibling();
					}
				}
				else if (name == L"title")
					title = noteNode->value();
				else if (name == L"created")
					created = noteNode->value();
				noteNode = noteNode->next_sibling();
			}

			Timestamp timestamp = Timestamp(ParseTime(created));
			notes.push_back(Note());
			notes.back().guid         = guid;
			notes.back().name         = title;
			notes.back().creationDate = timestamp;
			notes.back().usn          = -1;
			notes.back().isDirty      = true;
			bodies.push_back(body);

			node = node->next_sibling();
		}
	}
	catch (rapidxml::parse_error & e)
	{
		const wchar_t * fragment(e.where<wchar_t>());
		cout << fragment << endl;
	}
}
time_t EnImporter::ParseTime(wstring time)
{
	if (time.size() != 16 || time[8] != L'T' || time[15] != L'Z')
		return 0;
	SYSTEMTIME systemTime = { };
	systemTime.wYear
		= static_cast<WORD>
		( GetDigit(time[0]) * 1000
		+ GetDigit(time[1]) * 100
		+ GetDigit(time[2]) * 10
		+ GetDigit(time[3]) * 1
		);
	systemTime.wMonth
		= static_cast<WORD>
		( GetDigit(time[4]) * 10
		+ GetDigit(time[5]) * 1
		);
	systemTime.wDay
		= static_cast<WORD>
		( GetDigit(time[6]) * 10
		+ GetDigit(time[7]) * 1
		);
	systemTime.wHour
		= static_cast<WORD>
		( GetDigit(time[9])  * 10
		+ GetDigit(time[10]) * 1
		);
	systemTime.wMinute
		= static_cast<WORD>
		( GetDigit(time[11]) * 10
		+ GetDigit(time[12]) * 1
		);
	systemTime.wSecond
		= static_cast<WORD>
		( GetDigit(time[13]) * 10
		+ GetDigit(time[14]) * 1
		);
	return SystemTimeToUnixTime(systemTime);
}

int EnImporter::GetDigit(wchar_t c)
{
	if (c < L'0') return 0;
	if (c > L'9') return 9;
	return c - L'0';
}
