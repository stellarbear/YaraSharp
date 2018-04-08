#include "Stdafx.h"

//	CMatches
namespace YaraSharp
{
	CMatches::CMatches()
	{
		Rule = nullptr;
		Matches = gcnew Dictionary<String^, List<CMatch^>^>();
	}

	CMatches::CMatches(YR_RULE * MatchingRule)
	{
		Rule = gcnew CRule(MatchingRule);
		Matches = gcnew Dictionary<String^, List<CMatch^>^>();

		YR_STRING* StringEntry;
		YR_MATCH* MatchEntry;

		yr_rule_strings_foreach(MatchingRule, StringEntry)
		{
			auto identifier = marshal_as<String^>(StringEntry->identifier);

			yr_string_matches_foreach(StringEntry, MatchEntry)
			{
				if (!Matches->ContainsKey(identifier))
					Matches->Add(identifier, gcnew List<CMatch^>());

				Matches[identifier]->Add(gcnew CMatch(MatchEntry));
			}
		}
	}
}

//	CMatch
namespace YaraSharp
{
	CMatch::CMatch()
	{
		Base = 0;
		Offset = 0;
		Data = gcnew array<uint8_t>(0);
	}

	CMatch::CMatch(YR_MATCH* Match)
	{
		/*
		int64_t base;              // Base address for the match
		int64_t offset;            // Offset relative to base for the match
		int32_t match_length;      // Match length
		int32_t data_length;
		const uint8_t* data;
		*/

		Base = Match->base;
		Offset = Match->offset;

		Data = gcnew array<uint8_t>(Match->match_length);
		Marshal::Copy(IntPtr((void *)Match->data), Data, 0, Match->data_length);
	}
}