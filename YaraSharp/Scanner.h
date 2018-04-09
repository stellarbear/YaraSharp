#pragma once

namespace YaraSharp
{
	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	delegate int YaraScanCallback(int Message, void* Data, void* Context);

	public ref class CScanner sealed
	{
		initonly YR_SCANNER * Scanner;

	public:
		CScanner(CRules^ rules, Dictionary<String^, Object^>^ ExternalVariables);
		~CScanner();

		int HandleScannerCallback(int Message, void* Data, void* Context);
	private:
		void SetScannerExternals(Dictionary<String^, Object^>^ ExternalVariables);
	};
}