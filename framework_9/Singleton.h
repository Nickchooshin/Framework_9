#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#define macro_singleton(T) \
	private:\
	static T* m_instance;\
	\
	static void DestroySingleton()\
		{\
		if (m_instance)\
						{\
			delete m_instance;\
			m_instance = nullptr;\
						}\
		}\
	public:\
	static T* GetInstance()\
		{\
		if (!m_instance)\
						{\
			m_instance = new T;\
			atexit(DestroySingleton);\
						}\
		\
		return m_instance;\
		}

#define macro_singleton2(T) T* T::m_instance = nullptr;

#endif