#include "Stdafx.h"

//	CRules
namespace YaraSharp
{
	CRules::operator YR_RULES*() { return Rules; }
	CRules::CRules(YR_RULES* rules) : Rules(rules) { }
	CRules::~CRules() { if (Rules) yr_rules_destroy(Rules); }
	void CRules::Destroy() { delete this; }
}
//	CRule
namespace YaraSharp
{
	CRule::CRule()
	{
		Namespace = nullptr;
		Identifier = nullptr;
		Tags = gcnew List<String^>();
		//	Strings = gcnew List<String^>();
		Meta = gcnew Dictionary<String^, Object^>();
	}
	CRule::CRule(YR_RULE* Rule)
	{
		Namespace = nullptr;
		Tags = CRule::GetRuleTags(Rule);
		Meta = CRule::GetRuleMeta(Rule);
		//	Strings = CRule::GetRuleStrings(Rule);
		Identifier = gcnew String(Rule->identifier);
	}

	List<String^>^ CRule::GetRuleTags(YR_RULE* Rule)
	{
		List<String^>^ Result = gcnew List<String^>();

		const char* TagEntry;
		yr_rule_tags_foreach(Rule, TagEntry)
			Result->Add(gcnew String(TagEntry));

		return Result;
	}
	List<String^>^ CRule::GetRuleStrings(YR_RULE* Rule)
	{
		List<String^>^ Result = gcnew List<String^>();

		YR_STRING* StringEntry;
		yr_rule_strings_foreach(Rule, StringEntry)
			Result->Add(gcnew String(StringEntry->identifier));

		return Result;
	}
	Dictionary<String^, Object^>^ CRule::GetRuleMeta(YR_RULE* Rule)
	{
		Dictionary<String^, Object^>^ Result = gcnew Dictionary<String^, Object^>();

		YR_META* MetaEntry;
		yr_rule_metas_foreach(Rule, MetaEntry)
		{
			if (MetaEntry->identifier == NULL)
				throw gcnew NullReferenceException("(Meta) Значение не может быть пустым");

			String^ MetaID = gcnew String(MetaEntry->identifier);
			Object^ MetaValue = nullptr;

			switch (MetaEntry->type)
			{
			case META_TYPE_BOOLEAN:
				MetaValue = (bool)(MetaEntry->integer == 1);
				break;
			case META_TYPE_INTEGER:
				MetaValue = (Int32)MetaEntry->integer;
				break;
			case META_TYPE_STRING:
				MetaValue = gcnew String(MetaEntry->string);
				break;
			}

			//	Отсеиваем дубликаты
			if (!Result->ContainsKey(MetaID))
				Result->Add(MetaID, MetaValue);
		}

		return Result;
	}
}