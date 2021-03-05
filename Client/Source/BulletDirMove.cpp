#include "stdafx.h"
#include "..\Include\BulletDirMove.h"
#include "Enemy.h"




BulletDirMove::BulletDirMove(Desc * _desc)
{
	m_speed = _desc->speed;
}

BulletDirMove::~BulletDirMove()
{
}

void BulletDirMove::Initialize()
{
	m_dir = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER)->GetTransform()->GetForward();
}

void BulletDirMove::Update()
{
	m_transform->position += m_dir * m_speed * dTime;


	DEBUG_LOG(L"À§Ä¡", m_transform->position);
}

void BulletDirMove::OnTriggerEnter(Collisions & _collision)
{
	for (auto& obj : _collision)
	{
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_ENEMY)
		{
			obj.GetGameObject()->GetComponent<Enemy>()->Damaged(-1);
		}
	}
}

void BulletDirMove::OnTriggerStay(Collisions & _collision)
{
}

void BulletDirMove::OnTriggerExit(Collisions & _collision)
{
}
