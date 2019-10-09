#pragma once

namespace YaraSharp
{
	// Code 1 is handled by OutOfMemoryException

	// Code 2
	public ref class YaraAttachToProcessFailure : public Exception
	{
	public:
		YaraAttachToProcessFailure();
	};

	// Code 3
	public ref class YaraOpenFileFailure : public Exception
	{
	public:
		YaraOpenFileFailure();
	};

	// Code 4
	public ref class YaraMapFileFailure : public Exception
	{
	public:
		YaraMapFileFailure();
	};

	// Code 6
	public ref class YaraInvalidFile : public Exception
	{
	public:
		YaraInvalidFile();
	};

	// Code 7
	public ref class YaraCorruptFile : public Exception
	{
	public:
		YaraCorruptFile();
	};

	// Code 8
	public ref class YaraUnsupportedFileVersion : public Exception
	{
	public:
		YaraUnsupportedFileVersion();
	};

	// Code 9
	public ref class YaraInvalidRegularExpression : public Exception
	{
	public:
		YaraInvalidRegularExpression();
	};

	// Code 10
	public ref class YaraInvalidHexString : public Exception
	{
	public:
		YaraInvalidHexString();
	};

	// Code 11
	public ref class YaraSyntaxError : public Exception
	{
	public:
		YaraSyntaxError();
	};

	// Code 12
	public ref class YaraLoopNestingLimitExceeded : public Exception
	{
	public:
		YaraLoopNestingLimitExceeded();
	};

	// Code 13
	public ref class YaraDuplicatedLoopIdentifier : public Exception
	{
	public:
		YaraDuplicatedLoopIdentifier();
	};

	// Code 14
	public ref class YaraDuplicatedIdentifier : public Exception
	{
	public:
		YaraDuplicatedIdentifier();
	};

	// Code 15
	public ref class YaraDuplicatedTagIdentifier : public Exception
	{
	public:
		YaraDuplicatedTagIdentifier();
	};

	// Code 16
	public ref class YaraDuplicatedMetaIdentifier : public Exception
	{
	public:
		YaraDuplicatedMetaIdentifier();
	};

	// Code 17
	public ref class YaraDuplicatedStringIdentifier : public Exception
	{
	public:
		YaraDuplicatedStringIdentifier();
	};

	// Code 18
	public ref class YaraUnreferencedString : public Exception
	{
	public:
		YaraUnreferencedString();
	};

	// Code 19
	public ref class YaraUndefinedString : public Exception
	{
	public:
		YaraUndefinedString();
	};

	// Code 20
	public ref class YaraUndefinedIdentifier : public Exception
	{
	public:
		YaraUndefinedIdentifier();
	};

	// Code 21
	public ref class YaraMisplacedAnonymousString : public Exception
	{
	public:
		YaraMisplacedAnonymousString();
	};

	// Code 22
	public ref class YaraCircularReference : public Exception
	{
	public:
		YaraCircularReference();
	};

	// Code 23
	public ref class YaraDepthExceeded : public Exception
	{
	public:
		YaraDepthExceeded();
	};

	// Code 24
	public ref class YaraWrongType : public Exception
	{
	public:
		YaraWrongType();
	};

	// Code 25
	public ref class YaraExecStackOverflow : public Exception
	{
	public:
		YaraExecStackOverflow();
	};

	// Code 26
	public ref class YaraScanTimeout : public Exception
	{
	public:
		YaraScanTimeout();
	};

	// Code 27
	public ref class YaraTooManyScanThreads : public Exception
	{
	public:
		YaraTooManyScanThreads();
	};

	// Code 28
	public ref class YaraCallbackError : public Exception
	{
	public:
		YaraCallbackError();
	};

	// Code 29
	public ref class YaraInvalidArgument : public Exception
	{
	public:
		YaraInvalidArgument();
	};

	// Code 30
	public ref class YaraTooManyMatches : public Exception
	{
	public:
		YaraTooManyMatches();
	};

	// Code 31
	public ref class YaraInternalFatalError : public Exception
	{
	public:
		YaraInternalFatalError();
	};

	// Code 32
	public ref class YaraNestedForOfLoop : public Exception
	{
	public:
		YaraNestedForOfLoop();
	};

	// Code 33
	public ref class YaraInvalidFieldName : public Exception
	{
	public:
		YaraInvalidFieldName();
	};

	// Code 34
	public ref class YaraUnknownModule : public Exception
	{
	public:
		YaraUnknownModule();
	};

	// Code 35
	public ref class YaraNotAStructure : public Exception
	{
	public:
		YaraNotAStructure();
	};

	// Code 36
	public ref class YaraNotIndexable : public Exception
	{
	public:
		YaraNotIndexable();
	};

	// Code 37
	public ref class YaraNotAFunction : public Exception
	{
	public:
		YaraNotAFunction();
	};

	// Code 38
	public ref class YaraInvalidFormat : public Exception
	{
	public:
		YaraInvalidFormat();
	};

	// Code 39
	public ref class YaraTooManyArguments : public Exception
	{
	public:
		YaraTooManyArguments();
	};

	// Code 40
	public ref class YaraWrongArguments : public Exception
	{
	public:
		YaraWrongArguments();
	};

	// Code 41
	public ref class YaraWrongReturnType : public Exception
	{
	public:
		YaraWrongReturnType();
	};

	// Code 42
	public ref class YaraDuplicatedStructureMember : public Exception
	{
	public:
		YaraDuplicatedStructureMember();
	};

	// Code 43
	public ref class YaraEmptyString : public Exception
	{
	public:
		YaraEmptyString();
	};

	// Code 44
	public ref class YaraDivisionByZero : public Exception
	{
	public:
		YaraDivisionByZero();
	};

	// Code 45
	public ref class YaraRegularExpressionTooLarge : public Exception
	{
	public:
		YaraRegularExpressionTooLarge();
	};

	// Code 46
	public ref class YaraTooManyReFibers : public Exception
	{
	public:
		YaraTooManyReFibers();
	};

	// Code 47
	public ref class YaraCouldNotReadProcessMemory : public Exception
	{
	public:
		YaraCouldNotReadProcessMemory();
	};

	// Code 48
	public ref class YaraInvalidExternalVariableType : public Exception
	{
	public:
		YaraInvalidExternalVariableType();
	};
}