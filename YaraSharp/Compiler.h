#pragma once

namespace YaraSharp
{
	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	delegate void YaraCompilerCallback(int ErrorLevel, const char* Filename, int LineNumber, const char* Message, void* UserData);

	public ref class CCompiler sealed
	{
		initonly YR_COMPILER* Compiler;
		initonly List<String^>^ Errors;

	public:
		CCompiler(Dictionary<String^, Object^>^ ExternalVariables);
		~CCompiler();

		CRules^ GetRules();
		YR_COMPILER* GetCompiler();
		List<String^>^ GetErrors();
		int AddFile(String^ FilePath);
		void AddFiles(List<String^>^ FilePathList);

		void HandleCompilerCallback(int ErrorLevel, const char* Filename, int LineNumber, const char* Message, void* UserData);
	private:
		void SetCompilerExternals(Dictionary<String^, Object^>^ ExternalVariables);
	};
}