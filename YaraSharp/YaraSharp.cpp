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
				CompilationErrors->Add(FilePathList[i], TestCompiler->GetErrors());
				FilePathList->Remove(FilePathList[i--]);
			}

			delete TestCompiler;
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
					CompilationErrors->Add(FilePath, TestCompiler->GetErrors());
					FilePathList->Remove(FilePath);
					SuccessFlag = false;

					//	В случае ошибки необходимо создавать новый компилятор
					delete TestCompiler;
					break;
				}
			}
		}

		return CompilationErrors;
	}


	//	Компиляция правил
	CRules^ CYaraSharp::CompileFromFiles(List<String^>^ FilePathList, Dictionary<String^, Object^>^ ExternalVariables,
		[Out] Dictionary<String^, List<String^>^>^% CompilationErrors)
	{
		//	TODO: добавить поддержку namespace

		//	Проверка правил на корректность
		CompilationErrors = CheckYaraRules(FilePathList, ExternalVariables);

		//	Компиляция правил
		CCompiler^ Compiler = gcnew CCompiler(ExternalVariables);
		Compiler->AddFiles(FilePathList);
		CRules^ Result = Compiler->GetRules();
		delete Compiler;

		//	Возвращаем скомпилированные правила
		return Result;
	}
	
	//	Сканирование файла
	List<CMatches^>^ CYaraSharp::ScanFile(String^ Path, CRules^ Rules, Dictionary<String^, Object^>^ ExternalVariables, int Timeout)
	{
		CScanner^ FScanner = gcnew CScanner(Rules, ExternalVariables);

		if (!File::Exists(Path))
			throw gcnew FileNotFoundException(Path);

		//	Callback секция
		List<CMatches^>^ Results = gcnew List<CMatches^>();
		GCHandle ResultsHandle = GCHandle::Alloc(Results);
		void* ResultsPointer = GCHandle::ToIntPtr(ResultsHandle).ToPointer();

		YaraScanCallback^ ScannerCallback = gcnew YaraScanCallback(FScanner, &CScanner::HandleScannerCallback);
		GCHandle CallbackHandle = GCHandle::Alloc(ScannerCallback);
		YR_CALLBACK_FUNC CallbackPointer = (YR_CALLBACK_FUNC)Marshal::GetFunctionPointerForDelegate(ScannerCallback).ToPointer();
		
		//	Сканирование
		ErrorUtility::ThrowOnError(yr_rules_scan_file(Rules, (marshal_as<std::string>(Path)).c_str(), 0, CallbackPointer, ResultsPointer, Timeout));

		return Results;
	}
	//	Сканирование процесса
	List<CMatches^>^ CYaraSharp::ScanProcess(int PID, CRules^ Rules, int Timeout, Dictionary<String^, Object^>^ ExternalVariables)
	{
		CScanner^ PScanner = gcnew CScanner(Rules, ExternalVariables);
		
		//	Callback секция
		List<CMatches^>^ Results = gcnew List<CMatches^>();
		GCHandle ResultsHandle = GCHandle::Alloc(Results);
		void* ResultsPointer = GCHandle::ToIntPtr(ResultsHandle).ToPointer();

		YaraScanCallback^ ScannerCallback = gcnew YaraScanCallback(PScanner, &CScanner::HandleScannerCallback);
		GCHandle CallbackHandle = GCHandle::Alloc(ScannerCallback);
		YR_CALLBACK_FUNC CallbackPointer = (YR_CALLBACK_FUNC)Marshal::GetFunctionPointerForDelegate(ScannerCallback).ToPointer();

		//	Сканирование
		ErrorUtility::ThrowOnError(yr_rules_scan_proc(Rules, PID, 0, CallbackPointer, ResultsPointer, Timeout));

		return Results;
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

		//	Callback секция
		List<CMatches^>^ Results = gcnew List<CMatches^>();
		GCHandle ResultsHandle = GCHandle::Alloc(Results);
		void* ResultsPointer = GCHandle::ToIntPtr(ResultsHandle).ToPointer();

		YaraScanCallback^ ScannerCallback = gcnew YaraScanCallback(MScanner, &CScanner::HandleScannerCallback);
		GCHandle CallbackHandle = GCHandle::Alloc(ScannerCallback);
		YR_CALLBACK_FUNC CallbackPointer = (YR_CALLBACK_FUNC)Marshal::GetFunctionPointerForDelegate(ScannerCallback).ToPointer();

		//	Сканирование
		ErrorUtility::ThrowOnError(yr_rules_scan_mem(Rules, Buffer, Length, 0, CallbackPointer, ResultsPointer, Timeout));

		return Results;
	}
}