#include "TimerHandle.h"

namespace framework9
{
	CTimerHandle::HandleID CTimerHandle::m_idCounter = 0U;

	CTimerHandle::CTimerHandle()
		: m_id(0)
	{
	}
	CTimerHandle::CTimerHandle(HandleID id)
		: m_id(id)
	{
	}
	CTimerHandle::~CTimerHandle()
	{
	}

	CTimerHandle CTimerHandle::NewHandle()
	{
		CTimerHandle handle(++m_idCounter);

		return handle;
	}

	bool CTimerHandle::operator==(const CTimerHandle &handle)
	{
		return m_id == handle.m_id;
	}

	bool CTimerHandle::operator!=(const CTimerHandle &handle)
	{
		return m_id != handle.m_id;
	}
}