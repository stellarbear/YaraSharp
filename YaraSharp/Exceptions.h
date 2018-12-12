#pragma once

namespace YaraSharp
{
	public ref class YSException abstract sealed
	{
	private:
		static String^ NiceErrorCode(int error);

	public:
		static void ThrowOnError(int error);
		static void ThrowOnError(String^ error);
	};
}
