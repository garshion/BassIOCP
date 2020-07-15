#pragma once

namespace Bass
{
	template <class T>
	class Singleton
	{
	public:
		static T& GetInstance()
		{
			return m_Instance;
		}

	protected:
		static T m_Instance;
	};
}

template <class T>
T Bass::Singleton<T>::m_Instance;

