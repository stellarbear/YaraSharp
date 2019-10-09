#include "Stdafx.h"
#include "YaraExceptions.h"

namespace YaraSharp
{
	void YSException::ThrowOnError(int error)
	{
		switch (error)
		{
		case ERROR_SUCCESS:
			return;
		case ERROR_INSUFICIENT_MEMORY:
			throw gcnew OutOfMemoryException();
		case ERROR_COULD_NOT_ATTACH_TO_PROCESS:
			throw gcnew YaraAttachToProcessFailure();
		case ERROR_COULD_NOT_OPEN_FILE:
			throw gcnew YaraOpenFileFailure();
		case ERROR_COULD_NOT_MAP_FILE:
			throw gcnew YaraMapFileFailure();
		case ERROR_INVALID_FILE:
			throw gcnew YaraInvalidFile();
		case ERROR_CORRUPT_FILE:
			throw gcnew YaraCorruptFile();
		case ERROR_UNSUPPORTED_FILE_VERSION:
			throw gcnew YaraUnsupportedFileVersion();
		case ERROR_INVALID_REGULAR_EXPRESSION:
			throw gcnew YaraInvalidRegularExpression();
		case ERROR_INVALID_HEX_STRING:
			throw gcnew YaraInvalidHexString();
		case ERROR_SYNTAX_ERROR:
			throw gcnew YaraSyntaxError();
		case ERROR_LOOP_NESTING_LIMIT_EXCEEDED:
			throw gcnew YaraLoopNestingLimitExceeded();
		case ERROR_DUPLICATED_LOOP_IDENTIFIER:
			throw gcnew YaraDuplicatedLoopIdentifier();
		case ERROR_DUPLICATED_IDENTIFIER:
			throw gcnew YaraDuplicatedIdentifier();
		case ERROR_DUPLICATED_TAG_IDENTIFIER:
			throw gcnew YaraDuplicatedTagIdentifier();
		case ERROR_DUPLICATED_META_IDENTIFIER:
			throw gcnew YaraDuplicatedMetaIdentifier();
		case ERROR_DUPLICATED_STRING_IDENTIFIER:
			throw gcnew YaraDuplicatedStringIdentifier();
		case ERROR_UNREFERENCED_STRING:
			throw gcnew YaraUnreferencedString();
		case ERROR_UNDEFINED_STRING:
			throw gcnew YaraUndefinedString();
		case ERROR_UNDEFINED_IDENTIFIER:
			throw gcnew YaraUndefinedIdentifier();
		case ERROR_MISPLACED_ANONYMOUS_STRING:
			throw gcnew YaraMisplacedAnonymousString();
		case ERROR_INCLUDES_CIRCULAR_REFERENCE:
			throw gcnew YaraCircularReference();
		case ERROR_INCLUDE_DEPTH_EXCEEDED:
			throw gcnew YaraDepthExceeded();
		case ERROR_WRONG_TYPE:
			throw gcnew YaraWrongType();
		case ERROR_EXEC_STACK_OVERFLOW:
			throw gcnew YaraExecStackOverflow();
		case ERROR_SCAN_TIMEOUT:
			throw gcnew YaraScanTimeout();
		case ERROR_TOO_MANY_SCAN_THREADS:
			throw gcnew YaraTooManyScanThreads();
		case ERROR_CALLBACK_ERROR:
			throw gcnew YaraCallbackError();
		case ERROR_INVALID_ARGUMENT:
			throw gcnew YaraInvalidArgument();
		case ERROR_TOO_MANY_MATCHES:
			throw gcnew YaraTooManyMatches();
		case ERROR_INTERNAL_FATAL_ERROR:
			throw gcnew YaraInternalFatalError();
		case ERROR_NESTED_FOR_OF_LOOP:
			throw gcnew YaraNestedForOfLoop();
		case ERROR_INVALID_FIELD_NAME:
			throw gcnew YaraInvalidFieldName();
		case ERROR_UNKNOWN_MODULE:
			throw gcnew YaraUnknownModule();
		case ERROR_NOT_A_STRUCTURE:
			throw gcnew YaraNotAStructure();
		case ERROR_NOT_INDEXABLE:
			throw gcnew YaraNotIndexable();
		case ERROR_NOT_A_FUNCTION:
			throw gcnew YaraNotAFunction();
		case ERROR_INVALID_FORMAT:
			throw gcnew YaraInvalidFormat();
		case ERROR_TOO_MANY_ARGUMENTS:
			throw gcnew YaraTooManyArguments();
		case ERROR_WRONG_ARGUMENTS:
			throw gcnew YaraWrongArguments();
		case ERROR_WRONG_RETURN_TYPE:
			throw gcnew YaraWrongReturnType();
		case ERROR_DUPLICATED_STRUCTURE_MEMBER:
			throw gcnew YaraDuplicatedStructureMember();
		case ERROR_EMPTY_STRING:
			throw gcnew YaraEmptyString();
		case ERROR_DIVISION_BY_ZERO:
			throw gcnew YaraDivisionByZero();
		case ERROR_REGULAR_EXPRESSION_TOO_LARGE:
			throw gcnew YaraRegularExpressionTooLarge();
		case ERROR_TOO_MANY_RE_FIBERS:
			throw gcnew YaraTooManyReFibers();
		case ERROR_COULD_NOT_READ_PROCESS_MEMORY:
			throw gcnew YaraCouldNotReadProcessMemory();
		case ERROR_INVALID_EXTERNAL_VARIABLE_TYPE:
			throw gcnew YaraInvalidExternalVariableType();
		default:
			throw gcnew Exception("An unknown exception occured");
		}
	}
	void YSException::ThrowOnError(String^ error)
	{
		throw gcnew Exception(String::Format("Error: {0}", error));
	}
}
