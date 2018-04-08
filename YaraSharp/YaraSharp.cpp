#include "Stdafx.h"

//	CMatches
namespace YaraSharp
{
	//	Проверка правил
	Dictionary<String^, List<String^>^>^ CYaraSharp::CheckYaraRules([Out] List<String^>^ FilePathList, Dictionary<String^, Object^>^ ExternalVariables)
	{
		Dictionary<String^, List<String^>^>^ CompilationErrors =
			gcnew Dictionary<String^, List<String^>^>();

		//	Последовательная проверка
		for (int i = 0; i < FilePathList->Count; i++)
		{
			CCompiler^ TestCompiler = gcnew CCompiler(ExternalVariables);

			if (TestCompiler->AddFile(FilePathList[i]))
			{
				CompilationErrors->Add(FilePathList[i], TestCompiler->Errors);
				FilePathList->Remove(FilePathList[i--]);
			}
		}

		//	Одновременная проверка
		bool SuccessFlag = false;
		while (!SuccessFlag)
		{
			SuccessFlag = true;
			CCompiler^ TestCompiler = gcnew CCompiler(ExternalVariables);
			for each (auto FilePath in FilePathList)
			{
				if (TestCompiler->AddFile(FilePath))
				{
					CompilationErrors->Add(FilePath, TestCompiler->Errors);
					FilePathList->Remove(FilePath);
					SuccessFlag = false;

					//	В случае ошибки необходимо создавать новый компилятор
					break;
				}
			}
		}

		return CompilationErrors;
	}
	//	Компиляция правил
	CRules^ CYaraSharp::CompileFromFiles(CCompiler^ Compiler, List<String^>^ FilePathList, Dictionary<String^, Object^>^ ExternalVariables,
		[Out] Dictionary<String^, List<String^>^>^% CompilationErrors)
	{
		//	TODO: добавить поддержку namespace

		//	Проверка правил на корректность
		CompilationErrors = CheckYaraRules(FilePathList, ExternalVariables);

		//	Компиляция правил
		Compiler->AddFiles(FilePathList);

		//	Возвращаем скомпилированные правила
		return Compiler->GetRules();
	}
	
	//	Сканирование файла
	List<CMatches^>^ CYaraSharp::ScanFile(String^ Path, CRules^ Rules, Dictionary<String^, Object^>^ ExternalVariables, int Timeout)
	{
		CScanner^ FScanner = gcnew CScanner(Rules, ExternalVariables);

		if (!File::Exists(Path))
			throw gcnew FileNotFoundException(Path);

		auto results = gcnew List<CMatches^>();
		auto nativePath = marshal_as<std::string>(Path);
		GCHandle resultsHandle = GCHandle::Alloc(results);

		ErrorUtility::ThrowOnError(
			yr_rules_scan_file(Rules, nativePath.c_str(), 0, FScanner->Scanner->callback,
				GCHandle::ToIntPtr(resultsHandle).ToPointer(), Timeout));

		return results;
	}
	//	Сканирование процесса
	List<CMatches^>^ CYaraSharp::ScanProcess(int PID, CRules^ Rules, int Timeout, Dictionary<String^, Object^>^ ExternalVariables)
	{
		CScanner^ PScanner = gcnew CScanner(Rules, ExternalVariables);

		auto results = gcnew List<CMatches^>();
		GCHandle resultsHandle = GCHandle::Alloc(results);

		ErrorUtility::ThrowOnError(
			yr_rules_scan_proc(Rules, PID, 0, PScanner->Scanner->callback,
				GCHandle::ToIntPtr(resultsHandle).ToPointer(), Timeout));

		return results;
	}
	//	Сканирование памяти
	List<CMatches^>^ CYaraSharp::ScanMemory(array<uint8_t>^ Buffer, CRules^ Rules, Dictionary<String^, Object^>^ ExternalVariables, int Timeout)
	{
		if (Buffer == nullptr || Buffer->Length == 0)
			return gcnew List<CMatches^>();
		else
		{
			pin_ptr<uint8_t> BufferPointer = &Buffer[0];
			return ScanMemory(BufferPointer, Buffer->Length, Rules, ExternalVariables, Timeout);
		}
	}
	//	Сканирование памяти
	List<CMatches^>^ CYaraSharp::ScanMemory(uint8_t* Buffer, int Length, CRules^ Rules, Dictionary<String^, Object^>^ ExternalVariables, int Timeout)
	{
		CScanner^ MScanner = gcnew CScanner(Rules, ExternalVariables);

		auto results = gcnew List<CMatches^>();
		GCHandle resultsHandle = GCHandle::Alloc(results);

		ErrorUtility::ThrowOnError(
			yr_rules_scan_mem(Rules, Buffer, Length, 0, MScanner->Scanner->callback,
				GCHandle::ToIntPtr(resultsHandle).ToPointer(), Timeout));

		return results;
	}
}