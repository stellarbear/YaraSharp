#pragma once

namespace YaraSharp
{
	public ref class CContext sealed
	{
	public:
		CContext();
		~CContext();
		void Destroy();
	};
}