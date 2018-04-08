#pragma once

namespace YaraSharp
{
	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	delegate int YaraScanCallback(int Message, void* Data, void* Context);

	public ref class CScanner sealed
	{
	public:
		YR_SCANNER * Scanner;
		YaraScanCallback^ ScanCallback;

		CScanner(CRules^ rules, Dictionary<String^, Object^>^ ExternalVariables);
		~CScanner();

	private:
		void SetScannerExternals(Dictionary<String^, Object^>^ ExternalVariables);
		int HandleScannerCallback(int Message, void* Data, void* Context);
	};
}