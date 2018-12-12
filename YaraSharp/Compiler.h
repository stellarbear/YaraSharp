#pragma once

namespace YaraSharp
{
	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	delegate void YaraCompilerCallback(int errorLevel, const char* filename, int lineNumber, const char* message, void* userData);

	public ref class YSCompiler sealed
	{
		YSReport^ errors;
		YSReport^ warnings;
		initonly YR_COMPILER* compiler;

	public:
		YSCompiler(Dictionary<String^, Object^>^ externalVariables);
		~YSCompiler();

		YSRules^ GetRules();
		YSReport^ GetErrors();
		YSReport^ GetWarnings();

		int AddFile(String^ FilePath);
		int TryAddFile(String^ FilePath, Dictionary<String^, Object^>^ externalVariables);
		void AddFiles(List<String^>^ filePathList, Dictionary<String^, Object^>^ externalVariables);
		
	private:
		void SetCompilerCallback();
		void SetCompilerExternals(Dictionary<String^, Object^>^ externalVariables);
		void HandleCompilerCallback(int errorLevel, const char* filename, int lineNumber, const char* message, void* userData);
	};
}