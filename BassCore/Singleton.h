#pragma once
namespace Bass
{
	template <class T>
	class Singleton
	{
	public:
		static T Instance;
	};
}

template <class T>
T Bass::Singleton<T>::Instance;