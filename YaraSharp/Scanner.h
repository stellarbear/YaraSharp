#pragma once

namespace YaraSharp
{
	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	delegate int YaraScanCallback(int Message, void* Data, void* Context);

	public ref class CScanner sealed
	{
		initonly YR_SCANNER * Scanner;
		List<CMatches^>^ Matches;

	public:
		CScanner(CRules^ rules, Dictionary<String^, Object^>^ ExternalVariables);
		~CScanner();

		List<CMatches^>^ ScanProcess(int PID);
		List<CMatches^>^ ScanFile(String^ Path);
		List<CMatches^>^ ScanMemory(uint8_t* Buffer, int Length);
		int HandleScannerCallback(int Message, void* Data, void* Context);
	private:
		void SetScannerCallback();
		void SetScannerExternals(Dictionary<String^, Object^>^ ExternalVariables);
	};
}