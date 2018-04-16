#include "Stdafx.h"

//	CScanner
namespace YaraSharp
{
	//	Constructor
	CScanner::CScanner(CRules^ rules, Dictionary<String^, Object^>^ ExternalVariables)
	{
		YR_SCANNER* TestScanner;
		ErrorUtility::ThrowOnError(yr_scanner_create((YR_RULES*)rules, &TestScanner));
		Scanner = TestScanner;

		SetScannerExternals(ExternalVariables);
	}
	//	Destructor
	CScanner::~CScanner() { if (Scanner) yr_scanner_destroy(Scanner); }

	//	Set externals
	void CScanner::SetScannerExternals(Dictionary<String^, Object^>^ ExternalVariables)
	{
		if (ExternalVariables)
		{
			marshal_context CTX;

			for each (auto ExternalVariable in ExternalVariables)
			{
				const char* VariablePointer = CTX.marshal_as<const char*>(ExternalVariable.Key);
				Type^ VariableType = ExternalVariable.Value->GetType();
				int ExternalError = ERROR_SUCCESS;

				if (VariableType == Boolean::typeid)
					ExternalError = yr_scanner_define_boolean_variable(Scanner, VariablePointer, (bool)ExternalVariable.Value);
				else if (VariableType == Double::typeid)
					ExternalError = yr_scanner_define_float_variable(Scanner, VariablePointer, (double)ExternalVariable.Value);
				else if (VariableType == Int64::typeid || VariableType == Int32::typeid)
					ExternalError = yr_scanner_define_integer_variable(Scanner, VariablePointer, (Int64)ExternalVariable.Value);
				else if (VariableType == String::typeid)
					ExternalError = yr_scanner_define_string_variable(Scanner, VariablePointer, CTX.marshal_as<const char*>((String^)ExternalVariable.Value));
				else
					throw gcnew NotSupportedException(String::Format("Unsupported external variable: '{0}'", VariableType->Name));

				if (ExternalError != ERROR_SUCCESS)
					ErrorUtility::ThrowOnError("(Scanner) Error during external variable intialization");
			}
		}
	}
	
	//	Callback
	int CScanner::HandleScannerCallback(int message, void* data, void* context)
	{
		if (message == CALLBACK_MSG_RULE_MATCHING)
		{
			auto resultsHandle = GCHandle::FromIntPtr(IntPtr(context));
			auto results = (List<CMatches^>^)resultsHandle.Target;

			results->Add(gcnew CMatches((YR_RULE*)data));
		}

		return CALLBACK_CONTINUE;
	}
}