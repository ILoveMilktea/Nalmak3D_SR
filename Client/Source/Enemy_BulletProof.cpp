#include "stdafx.h"
#include "..\Include\Enemy_BulletProof.h"


Enemy_BulletProof::Enemy_BulletProof(Desc* _desc)
{
	m_shieldModePos = _desc->shieldModePos;
	m_attackModePos = _desc->attackModePos;
}


Enemy_BulletProof::~Enemy_BulletProof()
{
}

void Enemy_BulletProof::Initialize()
{
	m_transform->position = m_shieldModePos;
}

void Enemy_BulletProof::Update()
{
}
