#pragma once

namespace YaraSharp
{
	public ref class CRules sealed
	{
		YR_RULES* Rules;

	public:
		CRules(YR_RULES* rules);
		operator YR_RULES*();
		~CRules();
	};


	public ref class CRule sealed
	{
	public:
		property String^ Namespace;
		property String^ Identifier;
		property List<String^>^ Tags;
		property Dictionary<String^, Object^>^ Meta;
		//  property List<String^>^ Strings;
		//	Ќесколько бесполезно, поскольку в Match уже имеетс€ ключ, 
		//	соответвующий найденному совпадению

		CRule();
		CRule(YR_RULE* Rule);

	private:
		List<String^>^ CRule::GetRuleTags(YR_RULE* Rule);
		List<String^>^ CRule::GetRuleStrings(YR_RULE* Rule);
		Dictionary<String^, Object^>^ CRule::GetRuleMeta(YR_RULE* Rule);
	};
}
