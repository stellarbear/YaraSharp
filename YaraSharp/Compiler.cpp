#include "Stdafx.h"

//	CCompiler
namespace YaraSharp
{
	//	Constructor
	CCompiler::CCompiler(Dictionary<String^, Object^>^ ExternalVariables)
	{
		YR_COMPILER* TestCompiler;
		ErrorUtility::ThrowOnError(yr_compiler_create(&TestCompiler));
		Compiler = TestCompiler;

		// Set up and initialize the error dictionary for errors and warnings
		// Which are populated by the callback handler
		Errors = gcnew Dictionary<int, List<String^>^>();
		Errors->Add(YARA_ERROR_LEVEL_ERROR, gcnew List<String^>());
		Errors->Add(YARA_ERROR_LEVEL_WARNING, gcnew List<String^>());

		SetCompilerExternals(ExternalVariables);
		SetCompilerCallback();
	}
	//	Destructor
	CCompiler::~CCompiler() { if (Compiler) yr_compiler_destroy(Compiler); }

	//	Rule region
	int CCompiler::AddFile(String^ FilePath)
	{
		FILE* File;
		Errors->Clear();
		Errors->Add(YARA_ERROR_LEVEL_ERROR, gcnew List<String^>());
		Errors->Add(YARA_ERROR_LEVEL_WARNING, gcnew List<String^>());

		auto NativePath = marshal_as<std::string>(FilePath);

		auto FileOpenError = fopen_s(&File, NativePath.c_str(), "r");

		if (FileOpenError)
			ErrorUtility::ThrowOnError(String::Format("Error opening file: {0}", FileOpenError));

		auto errors = yr_compiler_add_file(Compiler, File, nullptr, NativePath.c_str());

		if (File) fclose(File);

		return errors;
	}

	void CCompiler::AddFiles(List<String^>^ FilePathList)
	{
		for each (auto FilePath in FilePathList)
			AddFile(FilePath);
	}

	CRules^ CCompiler::GetRules()
	{
		YR_RULES* Rules;

		ErrorUtility::ThrowOnError(
			yr_compiler_get_rules(Compiler, &Rules));

		return gcnew CRules(Rules);
	}

	List<String^>^ CCompiler::GetErrors(Boolean IncludeWarnings)
	{
		if (IncludeWarnings)
		{
			List<String^>^ errorsAndWarnings = gcnew List<String^>(this->Errors[YARA_ERROR_LEVEL_ERROR]);
			errorsAndWarnings->AddRange(this->Errors[YARA_ERROR_LEVEL_WARNING]);
			return errorsAndWarnings;
		}
		
		return this->Errors[YARA_ERROR_LEVEL_ERROR];
	}

	//	Set externals
	void CCompiler::SetCompilerExternals(Dictionary<String^, Object^>^ ExternalVariables)
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
					ExternalError = yr_compiler_define_boolean_variable(Compiler, VariablePointer, (bool)ExternalVariable.Value);
				else if (VariableType == Double::typeid)
					ExternalError = yr_compiler_define_float_variable(Compiler, VariablePointer, (double)ExternalVariable.Value);
				else if (VariableType == Int64::typeid || VariableType == Int32::typeid)
					ExternalError = yr_compiler_define_integer_variable(Compiler, VariablePointer, (Int64)ExternalVariable.Value);
				else if (VariableType == String::typeid)
					ExternalError = yr_compiler_define_string_variable(Compiler, VariablePointer, CTX.marshal_as<const char*>((String^)ExternalVariable.Value));
				else
					throw gcnew NotSupportedException(String::Format("Unsupported external variable: '{0}'", VariableType->Name));

				if (ExternalError != ERROR_SUCCESS)
					ErrorUtility::ThrowOnError("(Compiler) Error during external variable intialization");
			}
		}
	}

	//	Callback
	void CCompiler::SetCompilerCallback()
	{
		YaraCompilerCallback^ CompilerCallback = gcnew YaraCompilerCallback(this, &CCompiler::HandleCompilerCallback);
		GCHandle CallbackHandle = GCHandle::Alloc(CompilerCallback);
		YR_COMPILER_CALLBACK_FUNC CallbackPointer = (YR_COMPILER_CALLBACK_FUNC)(Marshal::GetFunctionPointerForDelegate(CompilerCallback)).ToPointer();
		yr_compiler_set_callback(Compiler, CallbackPointer, NULL);
	}

	void CCompiler::HandleCompilerCallback(int ErrorLevel, const char* Filename, int LineNumber, const char* Message, void* UserData)
	{
		UNREFERENCED_PARAMETER(ErrorLevel);
		UNREFERENCED_PARAMETER(UserData);

		String^ errorLevel = "ERROR";

		if (ErrorLevel == YARA_ERROR_LEVEL_WARNING)
		{
			errorLevel = "WARNING";
		}
		
		auto msg = String::Format("{0}: {1} on line {2} in file: {3}",
			errorLevel, marshal_as<String^>(Message), LineNumber,
			Filename ? marshal_as<String^>(Filename) : "[none]");

		Errors[ErrorLevel]->Add(msg);
	}
}