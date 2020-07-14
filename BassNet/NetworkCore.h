#pragma once
#include <atomic>

namespace Bass
{
	class NetworkCore
	{
	public:
		~NetworkCore();
		static NetworkCore& GetInstance();

		void InitSocket();
		void CleanSocket();

		bool IsError(int nErrorCode);
	private:
		NetworkCore();

	private:
		static NetworkCore m_Instance;
		std::atomic_bool m_IsWinsockInit = false;

	};
}

