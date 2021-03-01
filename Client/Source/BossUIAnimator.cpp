#include "stdafx.h"
#include "..\Include\BossUIAnimator.h"

BossUIAnimator::BossUIAnimator(Desc * _desc)
{
}

void BossUIAnimator::Initialize()
{
	m_moveAnim.SetActor(m_gameObject);
	m_moveAnim.SetAnimation(MoveAnimation::LERP);
}

void BossUIAnimator::Update()
{
	m_moveAnim.Play_CurrentAnimation();
}

void BossUIAnimator::StartMoveDown(float _amount)
{
	m_moveAnim.SetDestination(Vector3(m_transform->position.x, m_transform->position.y + _amount, 0.f));
	m_moveAnim.Start_Animation();
}

void BossUIAnimator::StartMoveUp(float _amount)
{
	m_moveAnim.SetDestination(Vector3(m_transform->position.x, m_transform->position.y - _amount, 0.f));
	m_moveAnim.Start_Animation();
}
