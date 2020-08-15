#pragma once

template< class T>
class Singleton
{
public:
	Singleton() {}
	virtual ~Singleton() {}

private:
	static T* inst;

public:
	static T* GetInstance()
	{
		if (inst == nullptr) inst = new T();
		return inst;
	}
	static void ReleaseInstance()
	{
		delete inst;
	}
};
template <class T>
T* Singleton<T>::inst = nullptr;