#pragma once

namespace YaraSharp
{
	public ref class CMatch sealed
	{
	public:

		property uint64_t Base;
		property uint64_t Offset;
		property array<uint8_t>^ Data;

		CMatch();
		CMatch(YR_MATCH* Match);
	};

	public ref class CMatches sealed
	{
	public:

		property CRule^ Rule;
		property Dictionary<String^, List<CMatch^>^>^ Matches;

		CMatches();
		CMatches(YR_RULE* MatchingRule);
	};
}