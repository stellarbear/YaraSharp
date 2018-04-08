#pragma once

namespace YaraSharp
{
	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	delegate void YaraCompilerCallback(int ErrorLevel, const char* Filename, int LineNumber, const char* Message, void* UserData);

	public ref class CCompiler sealed
	{
	public:
		initonly YR_COMPILER* Compiler;
		initonly List<String^>^ Errors;
		YaraCompilerCallback ^ CompilerCallback;

		CCompiler(Dictionary<String^, Object^>^ ExternalVariables);
		~CCompiler();

		CRules^ GetRules();
		int AddFile(String^ FilePath);
		void AddFiles(List<String^>^ FilePathList);

	private:
		void SetCompilerExternals(Dictionary<String^, Object^>^ ExternalVariables);
		void HandleCompilerCallback(int ErrorLevel, const char* Filename, int LineNumber, const char* Message, void* UserData);
	};
}