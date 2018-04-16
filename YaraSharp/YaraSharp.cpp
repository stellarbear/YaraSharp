#include "Stdafx.h"

//	CMatches
namespace YaraSharp
{
	//	Check list of yara files
	Dictionary<String^, List<String^>^>^ CYaraSharp::CheckYaraRules([Out] List<String^>^ FilePathList, Dictionary<String^, Object^>^ ExternalVariables)
	{
		Dictionary<String^, List<String^>^>^ CompilationErrors =
			gcnew Dictionary<String^, List<String^>^>();

		//	Iterative check
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

		//	Simultaneous check
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

					//	New compiler must be created if we fail
					delete TestCompiler;
					break;
				}
			}
		}

		return CompilationErrors;
	}


	//	Rule compilation
	CRules^ CYaraSharp::CompileFromFiles(List<String^>^ FilePathList, Dictionary<String^, Object^>^ ExternalVariables,
		[Out] Dictionary<String^, List<String^>^>^% CompilationErrors)
	{
		//	TODO: add namespace support

		//	First: check
		CompilationErrors = CheckYaraRules(FilePathList, ExternalVariables);

		//	Second: compile
		CCompiler^ Compiler = gcnew CCompiler(ExternalVariables);
		Compiler->AddFiles(FilePathList);
		CRules^ Result = Compiler->GetRules();
		delete Compiler;

		//	Return compiled rules
		return Result;
	}
	
	//	Scanning file
	List<CMatches^>^ CYaraSharp::ScanFile(String^ Path, CRules^ Rules, Dictionary<String^, Object^>^ ExternalVariables, int Timeout)
	{
		CScanner^ FScanner = gcnew CScanner(Rules, ExternalVariables);

		//	File existance check disabled. This cause crashes on long filenames (260+ symbols)
		//if (!File::Exists(Path))
		//	throw gcnew FileNotFoundException(Path);

		//	Callback section
		List<CMatches^>^ Results = gcnew List<CMatches^>();
		GCHandle ResultsHandle = GCHandle::Alloc(Results);
		void* ResultsPointer = GCHandle::ToIntPtr(ResultsHandle).ToPointer();

		YaraScanCallback^ ScannerCallback = gcnew YaraScanCallback(FScanner, &CScanner::HandleScannerCallback);
		GCHandle CallbackHandle = GCHandle::Alloc(ScannerCallback);
		YR_CALLBACK_FUNC CallbackPointer = (YR_CALLBACK_FUNC)Marshal::GetFunctionPointerForDelegate(ScannerCallback).ToPointer();
		
		//	Scanning
		ErrorUtility::ThrowOnError(yr_rules_scan_file(Rules, (marshal_as<std::string>(Path)).c_str(), 0, CallbackPointer, ResultsPointer, Timeout));

		return Results;
	}
	//	Scanning process (not yet tested)
	List<CMatches^>^ CYaraSharp::ScanProcess(int PID, CRules^ Rules, int Timeout, Dictionary<String^, Object^>^ ExternalVariables)
	{
		CScanner^ PScanner = gcnew CScanner(Rules, ExternalVariables);
		
		//	Callback section
		List<CMatches^>^ Results = gcnew List<CMatches^>();
		GCHandle ResultsHandle = GCHandle::Alloc(Results);
		void* ResultsPointer = GCHandle::ToIntPtr(ResultsHandle).ToPointer();

		YaraScanCallback^ ScannerCallback = gcnew YaraScanCallback(PScanner, &CScanner::HandleScannerCallback);
		GCHandle CallbackHandle = GCHandle::Alloc(ScannerCallback);
		YR_CALLBACK_FUNC CallbackPointer = (YR_CALLBACK_FUNC)Marshal::GetFunctionPointerForDelegate(ScannerCallback).ToPointer();

		//	Scanning
		ErrorUtility::ThrowOnError(yr_rules_scan_proc(Rules, PID, 0, CallbackPointer, ResultsPointer, Timeout));

		return Results;
	}
	//	Scanning memory (not yet tested)
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
	//	Scanning memory (not yet tested)
	List<CMatches^>^ CYaraSharp::ScanMemory(uint8_t* Buffer, int Length, CRules^ Rules, Dictionary<String^, Object^>^ ExternalVariables, int Timeout)
	{
		CScanner^ MScanner = gcnew CScanner(Rules, ExternalVariables);

		//	Callback section
		List<CMatches^>^ Results = gcnew List<CMatches^>();
		GCHandle ResultsHandle = GCHandle::Alloc(Results);
		void* ResultsPointer = GCHandle::ToIntPtr(ResultsHandle).ToPointer();

		YaraScanCallback^ ScannerCallback = gcnew YaraScanCallback(MScanner, &CScanner::HandleScannerCallback);
		GCHandle CallbackHandle = GCHandle::Alloc(ScannerCallback);
		YR_CALLBACK_FUNC CallbackPointer = (YR_CALLBACK_FUNC)Marshal::GetFunctionPointerForDelegate(ScannerCallback).ToPointer();

		//	Scanning
		ErrorUtility::ThrowOnError(yr_rules_scan_mem(Rules, Buffer, Length, 0, CallbackPointer, ResultsPointer, Timeout));

		return Results;
	}
}