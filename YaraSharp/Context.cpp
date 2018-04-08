#include "Stdafx.h"

//	CContext
namespace YaraSharp
{
	//	Конструктор
	CContext::CContext() { ErrorUtility::ThrowOnError(yr_initialize()); }
	//	Деструктор
	CContext::~CContext() { ErrorUtility::ThrowOnError(yr_finalize()); }
}