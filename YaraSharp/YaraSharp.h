#pragma once

namespace YaraSharp
{
	public ref class CYaraSharp
	{
	private:
		//	Проверка файлов
		Dictionary<String^, List<String^>^>^ CheckYaraRules([Out] List<String^>^ FilePathList, Dictionary<String^, Object^>^ ExternalVariables);

	public:
		//	Компиляция правил
		CRules^ CompileFromFiles(List<String^>^ FilePathList,
								 Dictionary<String^, Object^>^ ExternalVariables,
								 [Out] Dictionary<String^, List<String^>^>^% CompilationErrors);

		//	Сканироварние 
		List<CMatches^>^ ScanFile(String^ Path, CRules^ Rules, Dictionary<String^, Object^>^ ExternalVariables, int Timeout);
		List<CMatches^>^ ScanProcess(int PID, CRules^ Rules, int Timeout, Dictionary<String^, Object^>^ ExternalVariables);
		List<CMatches^>^ ScanMemory(array<uint8_t>^ Buffer, CRules^ Rules, Dictionary<String^, Object^>^ ExternalVariables, int Timeout);
		List<CMatches^>^ ScanMemory(uint8_t* Buffer, int Length, CRules^ Rules, Dictionary<String^, Object^>^ ExternalVariables, int Timeout);
	};
}