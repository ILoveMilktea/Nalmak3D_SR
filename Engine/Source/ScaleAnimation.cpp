#include "..\Include\ScaleAnimation.h"
#include "GameObject.h"
#include "Transform.h"


ScaleAnimation::ScaleAnimation()
{
}


ScaleAnimation::~ScaleAnimation()
{
}

void ScaleAnimation::Start_Animation()
{
	IAnimation::Start_Animation();
}

bool ScaleAnimation::Play_CurrentAnimation()
{
	if (!IAnimation::Play_CurrentAnimation())
		return false;

	return true;
}

void ScaleAnimation::End_Animation()
{
	IAnimation::End_Animation();

	m_actor->SetScale(m_destScale);
}

void ScaleAnimation::Play_Lerp()
{
	Vector3 curScale;
	float curTime = (m_playTimer - m_startDelay) / m_playDuration;
	D3DXVec3Lerp(&curScale, &m_startScale, &m_destScale, curTime);

	m_actor->GetTransform()->SetScale(curScale);
}

void ScaleAnimation::Play_Custom()
{
}

void ScaleAnimation::SetStart()
{
	m_startScale = m_actor->GetTransform()->scale;
}

void ScaleAnimation::SetStartScale(Vector3 _start)
{
	m_actor->GetTransform()->scale = _start;
	m_startScale = _start;
}
