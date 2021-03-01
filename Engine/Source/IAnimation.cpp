#include "..\Include\IAnimation.h"
#include "TimeManager.h"

IAnimation::IAnimation()
{
	m_timeManager = TimeManager::GetInstance();
}

void IAnimation::Start_Animation()
{
	m_playTimer = 0.f;
	m_isPlay = true;
}

bool IAnimation::Play_CurrentAnimation()
{
	if (!m_isPlay)
		return false;

	m_playTimer += m_timeManager->GetdeltaTime();

	if (m_playTimer > m_playDuration)
	{
		End_Animation();
		return false;
	}

	return true;
}

void IAnimation::End_Animation()
{
	m_isPlay = false;
}
