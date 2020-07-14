#pragma once
#include <queue>
#include <mutex>

namespace Bass
{
	template <class T>
	class MTQueue
	{
	public:
		MTQueue();
		~MTQueue();

		size_t Size();
		bool Pop(T& o_data);
		void Push(T data);
		bool Empty();
		bool MoveAll(std::queue<T>& o_queue);

	private:
		std::queue<T> m_queue;
		std::mutex m_lock;
	};




	template<class T>
	Bass::MTQueue<T>::MTQueue()
	{
	}

	template<class T>
	Bass::MTQueue<T>::~MTQueue()
	{
		std::lock_guard<std::mutex> smartlock(m_lock);
		while (false == m_queue.empty())
			m_queue.pop();
	}

	template<class T>
	size_t Bass::MTQueue<T>::Size()
	{
		std::lock_guard<std::mutex> smartlock(m_lock);
		return m_queue.size();
	}

	template<class T>
	bool Bass::MTQueue<T>::Pop(T & o_data)
	{
		if (true == Empty())
			return false;

		std::lock_guard<std::mutex> smartlock(m_lock);
		o_data = m_queue.front();
		m_queue.pop();

		return true;
	}

	template<class T>
	void Bass::MTQueue<T>::Push(T data)
	{
		std::lock_guard<std::mutex> smartlock(m_lock);
		m_queue.push(data);
	}

	template<class T>
	bool Bass::MTQueue<T>::Empty()
	{
		std::lock_guard<std::mutex> smartlock(m_lock);
		return m_queue.empty();
	}

	template<class T>
	bool Bass::MTQueue<T>::MoveAll(std::queue<T>& o_queue)
	{
		while (false == m_queue.empty())
			o_queue.pop();

		std::lock_guard<std::mutex> smartlock(m_lock);
		o_queue.swap(m_queue);

		return !o_queue.empty();
	}




}