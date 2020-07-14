#pragma once

#include <queue>
#include <mutex>
#include <atomic>
#include "BassCommon.h"

namespace Bass
{
	template <class T>
	class MemoryPool
	{
	public:
		MemoryPool();
		MemoryPool(size_t nReserve);
		~MemoryPool();

		bool SetSize(size_t nReserve);

		T* Pop();
		bool Push(T* pVal);

	private:
		T* m_pBuffer = nullptr;
		std::queue<T*> m_Pool;
		std::mutex m_Lock;

		std::atomic_bool m_Initialized = false;
	};

	template<class T>
	inline MemoryPool<T>::MemoryPool()
	{
	}

	template<class T>
	inline MemoryPool<T>::MemoryPool(size_t nReserve)
	{
		SetSize(nReserve);
	}

	template<class T>
	inline MemoryPool<T>::~MemoryPool()
	{
		m_Initialized = false;
		AutoLock(m_Lock);
		while (false == m_Pool.empty())
		{
			m_Pool.pop();
		}
		SafeDeleteArray(m_pBuffer);
	}

	template<class T>
	inline bool MemoryPool<T>::SetSize(size_t nReserve)
	{
		if (true == m_Initialized)
			return false;

		if (nReserve == 0)
			return false;

		AutoLock(m_Lock);

		m_pBuffer = new T[nReserve]();
		for (size_t i = 0; i < nReserve; ++i)
		{
			m_Pool.push(&m_pBuffer[i]);
		}

		m_Initialized = true;
		return true;
	}

	template<class T>
	inline T * MemoryPool<T>::Pop()
	{
		if (false == m_Initialized)
			return nullptr;

		AutoLock(m_Lock);
		if (true == m_Pool.empty())
			return nullptr;
		T* pRet = m_Pool.front();
		m_Pool.pop();

		return pRet;
	}

	template<class T>
	inline bool MemoryPool<T>::Push(T * pVal)
	{
		if (false == m_Initialized)
			return false;

		AutoLock(m_Lock);
		m_Pool.push(pVal);
		return true;
	}

}