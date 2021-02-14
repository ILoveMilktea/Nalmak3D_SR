#include "..\Include\TimeManager.h"

IMPLEMENT_SINGLETON(TimeManager)


void TimeManager::Initialize()
{
	Reset();
	m_bStop = false;
}

void TimeManager::Reset()
{
	QueryPerformanceCounter(&m_startTime);
	QueryPerformanceCounter(&m_currentTime);
	QueryPerformanceCounter(&m_previousTime);
	QueryPerformanceFrequency(&m_countPerSec);

}

void TimeManager::Start()
{
	Reset();
	m_bStop = false;
	Tick();
}



void TimeManager::Pause()
{
	m_bStop = true;
}

void TimeManager::Toggle()
{
	m_bStop ^= true;
}

void TimeManager::Tick()
{
	if (m_bStop)
	{
		m_deltaTime = 0.0;
		return;
	}
	QueryPerformanceCounter(&m_currentTime);
	QueryPerformanceFrequency(&m_countPerSec); // ÃÊ´ç Æ½¼ö¸¦ ¾Ë¾Æ³¿
	m_deltaTime = float(m_currentTime.QuadPart - m_previousTime.QuadPart) / m_countPerSec.QuadPart;
	//if (m_deltaTime < 1 / 60.f)
	//{
	//	m_deltaTime = 1 / 60.f;
	//}

	m_previousTime.QuadPart = m_currentTime.QuadPart;
}



float TimeManager::GetTotalTime()
{
	return ((m_currentTime.QuadPart - m_startTime.QuadPart) / static_cast<float>(m_countPerSec.QuadPart));
}
