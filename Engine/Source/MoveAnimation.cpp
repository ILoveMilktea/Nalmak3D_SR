#include "..\Include\MoveAnimation.h"

#include "GameObject.h"
#include "Transform.h"

MoveAnimation::MoveAnimation()
{
	m_isPlay = false;
	m_playTimer = 0.f;
	m_playDuration = 1.f;

	m_currentAnimation = LERP;
}


MoveAnimation::~MoveAnimation()
{
}

void MoveAnimation::Start_Animation()
{
	IAnimation::Start_Animation();
}

bool MoveAnimation::Play_CurrentAnimation()
{
	if (!IAnimation::Play_CurrentAnimation())
		return false;

	switch (m_currentAnimation)
	{
	case MoveAnimation::LERP:
		Play_MoveLerp();
		break;
	case MoveAnimation::CUSTOM:
		Play_MoveCustom();
		break;
	}

	return true;
}

void MoveAnimation::End_Animation()
{
	IAnimation::End_Animation();

	m_actor->SetPosition(m_destination);
}

void MoveAnimation::Play_MoveLerp()
{
	Vector3 curPos;
	float curTime = (m_playTimer - m_startDelay) / m_playDuration;
	D3DXVec3Lerp(&curPos, &m_start, &m_destination, curTime);

	m_actor->SetPosition(curPos);
}

void MoveAnimation::Play_MoveCustom()
{
}

void MoveAnimation::SetAnimation(ANIMATION _animation)
{
	m_start = m_actor->GetTransform()->position;

	m_currentAnimation = _animation;
}

void MoveAnimation::SetActor(GameObject * _actor)
{
	m_actor = _actor;
}
