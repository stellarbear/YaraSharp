#include "Stdafx.h"
#include "YaraExceptions.h"

namespace YaraSharp
{
	// Code 1 is handled by OutOfMemoryException

	// Code 2
	YaraAttachToProcessFailure::YaraAttachToProcessFailure() : Exception(String::Format("{0} - Code {1}", "ERROR_COULD_NOT_ATTACH_TO_PROCESS", ERROR_COULD_NOT_ATTACH_TO_PROCESS)) {}

	// Code 3
	YaraOpenFileFailure::YaraOpenFileFailure() : Exception(String::Format("{0} - Code {1}", "ERROR_COULD_NOT_OPEN_FILE", ERROR_COULD_NOT_OPEN_FILE)) {}

	// Code 4
	YaraMapFileFailure::YaraMapFileFailure() : Exception(String::Format("{0} - Code {1}", "ERROR_COULD_NOT_MAP_FILE", ERROR_COULD_NOT_MAP_FILE)) {}

	// Code 6
	YaraInvalidFile::YaraInvalidFile() : Exception(String::Format("{0} - Code {1}", "ERROR_INVALID_FILE", ERROR_INVALID_FILE)) {}

	// Code 7
	YaraCorruptFile::YaraCorruptFile() : Exception(String::Format("{0} - Code {1}", "ERROR_CORRUPT_FILE", ERROR_CORRUPT_FILE)) {}

	// Code 8
	YaraUnsupportedFileVersion::YaraUnsupportedFileVersion() : Exception(String::Format("{0} - Code {1}", "ERROR_UNSUPPORTED_FILE_VERSION", ERROR_UNSUPPORTED_FILE_VERSION)) {}

	// Code 9
	YaraInvalidRegularExpression::YaraInvalidRegularExpression() : Exception(String::Format("{0} - Code {1}", "ERROR_INVALID_REGULAR_EXPRESSION", ERROR_INVALID_REGULAR_EXPRESSION)) {}

	// Code 10
	YaraInvalidHexString::YaraInvalidHexString() : Exception(String::Format("{0} - Code {1}", "ERROR_INVALID_HEX_STRING", ERROR_INVALID_HEX_STRING)) {}

	// Code 11
	YaraSyntaxError::YaraSyntaxError() : Exception(String::Format("{0} - Code {1}", "ERROR_SYNTAX_ERROR", ERROR_SYNTAX_ERROR)) {}

	// Code 12
	YaraLoopNestingLimitExceeded::YaraLoopNestingLimitExceeded() : Exception(String::Format("{0} - Code {1}", "ERROR_LOOP_NESTING_LIMIT_EXCEEDED", ERROR_LOOP_NESTING_LIMIT_EXCEEDED)) {}

	// Code 13
	YaraDuplicatedLoopIdentifier::YaraDuplicatedLoopIdentifier() : Exception(String::Format("{0} - Code {1}", "ERROR_DUPLICATED_LOOP_IDENTIFIER", ERROR_DUPLICATED_LOOP_IDENTIFIER)) {}

	// Code 14
	YaraDuplicatedIdentifier::YaraDuplicatedIdentifier() : Exception(String::Format("{0} - Code {1}", "ERROR_DUPLICATED_IDENTIFIER", ERROR_DUPLICATED_IDENTIFIER)) {}

	// Code 15
	YaraDuplicatedTagIdentifier::YaraDuplicatedTagIdentifier() : Exception(String::Format("{0} - Code {1}", "ERROR_DUPLICATED_TAG_IDENTIFIER", ERROR_DUPLICATED_TAG_IDENTIFIER)) {}

	// Code 16
	YaraDuplicatedMetaIdentifier::YaraDuplicatedMetaIdentifier() : Exception(String::Format("{0} - Code {1}", "ERROR_DUPLICATED_META_IDENTIFIER", ERROR_DUPLICATED_META_IDENTIFIER)) {}

	// Code 17
	YaraDuplicatedStringIdentifier::YaraDuplicatedStringIdentifier() : Exception(String::Format("{0} - Code {1}", "ERROR_DUPLICATED_STRING_IDENTIFIER", ERROR_DUPLICATED_STRING_IDENTIFIER)) {}

	// Code 18
	YaraUnreferencedString::YaraUnreferencedString() : Exception(String::Format("{0} - Code {1}", "ERROR_UNREFERENCED_STRING", ERROR_UNREFERENCED_STRING)) {}

	// Code 19
	YaraUndefinedString::YaraUndefinedString() : Exception(String::Format("{0} - Code {1}", "ERROR_UNDEFINED_STRING", ERROR_UNDEFINED_STRING)) {}

	// Code 20
	YaraUndefinedIdentifier::YaraUndefinedIdentifier() : Exception(String::Format("{0} - Code {1}", "ERROR_UNDEFINED_IDENTIFIER", ERROR_UNDEFINED_IDENTIFIER)) {}

	// Code 21
	YaraMisplacedAnonymousString::YaraMisplacedAnonymousString() : Exception(String::Format("{0} - Code {1}", "ERROR_MISPLACED_ANONYMOUS_STRING", ERROR_MISPLACED_ANONYMOUS_STRING)) {}

	// Code 22
	YaraCircularReference::YaraCircularReference() : Exception(String::Format("{0} - Code {1}", "ERROR_INCLUDES_CIRCULAR_REFERENCE", ERROR_INCLUDES_CIRCULAR_REFERENCE)) {}

	// Code 23
	YaraDepthExceeded::YaraDepthExceeded() : Exception(String::Format("{0} - Code {1}", "ERROR_INCLUDE_DEPTH_EXCEEDED", ERROR_INCLUDE_DEPTH_EXCEEDED)) {}

	// Code 24
	YaraWrongType::YaraWrongType() : Exception(String::Format("{0} - Code {1}", "ERROR_WRONG_TYPE", ERROR_WRONG_TYPE)) {}

	// Code 25
	YaraExecStackOverflow::YaraExecStackOverflow() : Exception(String::Format("{0} - Code {1}", "ERROR_EXEC_STACK_OVERFLOW", ERROR_EXEC_STACK_OVERFLOW)) {}

	// Code 26
	YaraScanTimeout::YaraScanTimeout() : Exception(String::Format("{0} - Code {1}", "ERROR_SCAN_TIMEOUT", ERROR_SCAN_TIMEOUT)) {}

	// Code 27
	YaraTooManyScanThreads::YaraTooManyScanThreads() : Exception(String::Format("{0} - Code {1}", "ERROR_TOO_MANY_SCAN_THREADS", ERROR_TOO_MANY_SCAN_THREADS)) {}

	// Code 28
	YaraCallbackError::YaraCallbackError() : Exception(String::Format("{0} - Code {1}", "ERROR_CALLBACK_ERROR", ERROR_CALLBACK_ERROR)) {}

	// Code 29
	YaraInvalidArgument::YaraInvalidArgument() : Exception(String::Format("{0} - Code {1}", "ERROR_INVALID_ARGUMENT", ERROR_INVALID_ARGUMENT)) {}

	// Code 30
	YaraTooManyMatches::YaraTooManyMatches() : Exception(String::Format("{0} - Code {1}", "ERROR_TOO_MANY_MATCHES", ERROR_TOO_MANY_MATCHES)) {}

	// Code 31
	YaraInternalFatalError::YaraInternalFatalError() : Exception(String::Format("{0} - Code {1}", "ERROR_INTERNAL_FATAL_ERROR", ERROR_INTERNAL_FATAL_ERROR)) {}

	// Code 32
	YaraNestedForOfLoop::YaraNestedForOfLoop() : Exception(String::Format("{0} - Code {1}", "ERROR_NESTED_FOR_OF_LOOP", ERROR_NESTED_FOR_OF_LOOP)) {}

	// Code 33
	YaraInvalidFieldName::YaraInvalidFieldName() : Exception(String::Format("{0} - Code {1}", "ERROR_INVALID_FIELD_NAME", ERROR_INVALID_FIELD_NAME)) {}

	// Code 34
	YaraUnknownModule::YaraUnknownModule() : Exception(String::Format("{0} - Code {1}", "ERROR_UNKNOWN_MODULE", ERROR_UNKNOWN_MODULE)) {}

	// Code 35
	YaraNotAStructure::YaraNotAStructure() : Exception(String::Format("{0} - Code {1}", "ERROR_NOT_A_STRUCTURE", ERROR_NOT_A_STRUCTURE)) {}

	// Code 36
	YaraNotIndexable::YaraNotIndexable() : Exception(String::Format("{0} - Code {1}", "ERROR_NOT_INDEXABLE", ERROR_NOT_INDEXABLE)) {}

	// Code 37
	YaraNotAFunction::YaraNotAFunction() : Exception(String::Format("{0} - Code {1}", "ERROR_NOT_A_FUNCTION", ERROR_NOT_A_FUNCTION)) {}

	// Code 38
	YaraInvalidFormat::YaraInvalidFormat() : Exception(String::Format("{0} - Code {1}", "ERROR_INVALID_FORMAT", ERROR_INVALID_FORMAT)) {}

	// Code 39
	YaraTooManyArguments::YaraTooManyArguments() : Exception(String::Format("{0} - Code {1}", "ERROR_TOO_MANY_ARGUMENTS", ERROR_TOO_MANY_ARGUMENTS)) {}

	// Code 40
	YaraWrongArguments::YaraWrongArguments() : Exception(String::Format("{0} - Code {1}", "ERROR_WRONG_ARGUMENTS", ERROR_WRONG_ARGUMENTS)) {}

	// Code 41
	YaraWrongReturnType::YaraWrongReturnType() : Exception(String::Format("{0} - Code {1}", "ERROR_WRONG_RETURN_TYPE", ERROR_WRONG_RETURN_TYPE)) {}

	// Code 42
	YaraDuplicatedStructureMember::YaraDuplicatedStructureMember() : Exception(String::Format("{0} - Code {1}", "ERROR_DUPLICATED_STRUCTURE_MEMBER", ERROR_DUPLICATED_STRUCTURE_MEMBER)) {}

	// Code 43
	YaraEmptyString::YaraEmptyString() : Exception(String::Format("{0} - Code {1}", "ERROR_EMPTY_STRING", ERROR_EMPTY_STRING)) {}

	// Code 44
	YaraDivisionByZero::YaraDivisionByZero() : Exception(String::Format("{0} - Code {1}", "ERROR_DIVISION_BY_ZERO", ERROR_DIVISION_BY_ZERO)) {}

	// Code 45
	YaraRegularExpressionTooLarge::YaraRegularExpressionTooLarge() : Exception(String::Format("{0} - Code {1}", "ERROR_REGULAR_EXPRESSION_TOO_LARGE", ERROR_REGULAR_EXPRESSION_TOO_LARGE)) {}

	// Code 46
	YaraTooManyReFibers::YaraTooManyReFibers() : Exception(String::Format("{0} - Code {1}", "ERROR_TOO_MANY_RE_FIBERS", ERROR_TOO_MANY_RE_FIBERS)) {}

	// Code 47
	YaraCouldNotReadProcessMemory::YaraCouldNotReadProcessMemory() : Exception(String::Format("{0} - Code {1}", "ERROR_COULD_NOT_READ_PROCESS_MEMORY", ERROR_COULD_NOT_READ_PROCESS_MEMORY)) {}

	// Code 48
	YaraInvalidExternalVariableType::YaraInvalidExternalVariableType() : Exception(String::Format("{0} - Code {1}", "ERROR_INVALID_EXTERNAL_VARIABLE_TYPE", ERROR_INVALID_EXTERNAL_VARIABLE_TYPE)) {}
}