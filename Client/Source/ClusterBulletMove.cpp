#include "stdafx.h"
#include "..\Include\ClusterBulletMove.h"
#include "Player_NearGuideBullet.h"

#include "ItemManager.h"
#include "PlayerItem.h"
#include "Enemy_Boss.h"
#include "Enemy.h"




ClusterBulletMove::ClusterBulletMove(Desc * _desc)
{
	m_speed = _desc->speed;
	m_bulletCount = _desc->bulletCount;
	m_screenPos = _desc->screenPos;
	m_target = _desc->target;
}

ClusterBulletMove::~ClusterBulletMove()
{
	Release();

}

void ClusterBulletMove::Initialize()
{
	m_player = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);

	Vector3 playerLook = m_player->GetTransform()->GetForward();
	Vector3 playerRight = m_player->GetTransform()->GetRight();
	Vector3 playerUp = m_player->GetTransform()->GetUp();

	Vector3 winDir = playerRight * m_screenPos.x + playerUp * m_screenPos.y;
	D3DXVec3Normalize(&winDir, &winDir);
	m_firstDir = playerLook + winDir;

}

void ClusterBulletMove::Update()
{
	if (m_target)
	{
		Vector3 dir = m_target->GetTransform()->position - m_transform->position;
		D3DXVec3Normalize(&dir, &dir);
		m_transform->LookAt(dir + m_transform->position, 1.5f);
		m_firstDir = Nalmak_Math::Lerp(m_firstDir, m_player->GetTransform()->GetForward(), dTime);
		m_transform->position += ((dir + m_firstDir)  * 45.f * dTime);

		float EnemyPlayerLenght = Nalmak_Math::Distance(m_player->GetTransform()->position, m_target->GetTransform()->position);
		float fromEnemyLenght = Nalmak_Math::Distance(m_target->GetTransform()->position, m_gameObject->GetTransform()->position);

		float ratioValue = fromEnemyLenght / EnemyPlayerLenght;

		DEBUG_LOG(L"NOOOOO", ratioValue);
		if (ratioValue <= 0.5f)
		{
			DESTROY(m_gameObject);
			m_start = true;
		}
	}

}

void ClusterBulletMove::Release()
{
	if (m_start)
	{
		MeshRenderer::Desc render;
		render.meshName = L"kfir_weapon1";
		render.mtrlName = L"kfir";

		float angleInterval = PI2 / m_bulletCount;
		float length = 10.f;

		Player_NearGuideBullet::Desc guidebulletInfo;
		SphereCollider::Desc sphereColInfo;
		sphereColInfo.collisionLayer = COLLISION_LAYER_BULLET_PLAYER;
		guidebulletInfo.speed = m_speed;

		Vector3 dir = m_target->GetTransform()->position - m_transform->position;
		D3DXVec3Normalize(&dir, &dir);

		Vector3* axis = new Vector3[m_bulletCount];

		D3DXMATRIX world = m_transform->GetWorldMatrix();
		Vector3 forward = { world._31,  world._32,  world._33 };
		Vector3 up = { world._21,  world._22,  world._23 };
		Vector3 pos = { world._41, world._42, world._43 };

		for (int i = 0; i < m_bulletCount; ++i)
		{
			D3DXMATRIX matRot;
			D3DXMatrixRotationAxis(&matRot, &forward, D3DXToRadian((360.f / m_bulletCount) * i));
			D3DXVec3TransformNormal(&axis[i], &up, &matRot);


			D3DXMATRIX matRot2;
			D3DXMatrixRotationAxis(&matRot2, &axis[i], 90.f * Deg2Rad);
			D3DXVec3TransformNormal(&axis[i], &forward, &matRot2);

			D3DXVec3Normalize(&axis[i], &axis[i]);

			pos += axis[i] * length;

			auto child = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER)->AddComponent<MeshRenderer>(&render);
			child->AddComponent<SphereCollider>(&sphereColInfo);
			guidebulletInfo.firstTarget = { pos };

			child->AddComponent<Player_NearGuideBullet>(&guidebulletInfo);
			child->SetPosition(m_transform->position);
			child->GetTransform()->rotation = m_transform->rotation;

		}

		SAFE_DELETE_ARR(axis);

		m_start = false;
	}
	m_gameObject = nullptr;
}
