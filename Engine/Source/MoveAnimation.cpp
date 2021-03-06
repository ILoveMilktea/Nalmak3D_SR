#include "..\Include\MoveAnimation.h"

#include "GameObject.h"
#include "Transform.h"

MoveAnimation::MoveAnimation()
{
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
	
	return true;
}

void MoveAnimation::End_Animation()
{
	IAnimation::End_Animation();

	m_actor->SetPosition(m_destPos);
}

void MoveAnimation::Play_Lerp()
{
	Vector3 curPos;
	float curTime = (m_playTimer - m_startDelay) / m_playDuration;
	D3DXVec3Lerp(&curPos, &m_startPos, &m_destPos, curTime);

	m_actor->SetPosition(curPos);
}

void MoveAnimation::Play_Custom()
{
}


void MoveAnimation::SetStartPosition()
{
	m_startPos = m_actor->GetTransform()->position;
}

void MoveAnimation::SetStartPosition(Vector3 _start)
{
	m_actor->GetTransform()->position = _start;
	m_startPos = _start;
}
