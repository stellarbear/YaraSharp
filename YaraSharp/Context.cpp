#include "Stdafx.h"

//	CContext
namespace YaraSharp
{
	//	Constructor
	CContext::CContext() { ErrorUtility::ThrowOnError(yr_initialize()); }
	//	Destructor
	CContext::~CContext() { ErrorUtility::ThrowOnError(yr_finalize()); }
	void CContext::Destroy() { delete this; }
}