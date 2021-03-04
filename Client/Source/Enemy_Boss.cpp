#include "stdafx.h"
#include "..\Include\Enemy_Boss.h"

Boss::Boss(Desc * _desc)
{
	m_tBossStatus = _desc->tStatus;
}

Boss::~Boss()
{
}

void Boss::Initialize()
{
}

void Boss::Update()
{

	DEBUG_LOG(L"Boss CurHP", m_tBossStatus.m_iCurHp);
	DEBUG_LOG(L"Boss Pos", m_transform->position);
}

void Boss::OnTriggerEnter(Collisions & _collision)
{
	for (auto& obj : _collision)
	{
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_BULLET_PLAYER)
		{
			m_tBossStatus.m_iCurHp -= 10;
		}
	}
}

void Boss::OnTriggerStay(Collisions & _collision)
{
}

void Boss::OnTriggerExit(Collisions & _collision)
{
}

int Boss::Get_FullHp() const
{
	return m_tBossStatus.m_iFullHp;
}

int Boss::Get_CurHp() const
{
	return m_tBossStatus.m_iCurHp;
}
