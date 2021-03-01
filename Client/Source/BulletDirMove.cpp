#include "stdafx.h"
#include "..\Include\BulletDirMove.h"




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
