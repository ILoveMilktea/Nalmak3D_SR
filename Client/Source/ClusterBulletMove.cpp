#include "stdafx.h"
#include "..\Include\ClusterBulletMove.h"
#include "Player_NearGuideBullet.h"

#include "ItemManager.h"
#include "PlayerItem.h"
#include "Enemy_Boss.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "PlayerInfoManager.h"
#include "EnemyDetector.h"
#include "ParticleRenderer.h"
#include "ParticleDead_IfCount0.h"


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

	if (m_smokeParticle)
	{
		m_smokeParticle->AddComponent<ParticleDead_IfCount0>();
		m_smokeParticle->StopEmit();
		m_smokeParticle = nullptr;
	}

	m_gameObject = nullptr;

}

void ClusterBulletMove::Initialize()
{

	ParticleRenderer::Desc render;
	render.particleDataName = L"missile_smoke";
	auto obj = INSTANTIATE()->AddComponent<ParticleRenderer>(&render);
	m_smokeParticle = obj->GetComponent<ParticleRenderer>();
	obj->SetParents(m_gameObject);


	m_player = PlayerInfoManager::GetInstance()->GetPlayer();

	Matrix worldMat = m_player->GetTransform()->GetWorldMatrix();
	Vector3 dirX = { worldMat._11, worldMat._12, worldMat._13 };
	Vector3 dirY = { worldMat._21, worldMat._22, worldMat._23 };
	Vector3 dirZ = { worldMat._31, worldMat._32, worldMat._33 };


	m_enemyDetector = Core::GetInstance()->FindObjectByName(OBJECT_TAG_UI, L"detector");
	if (m_enemyDetector)
		m_target = m_enemyDetector->GetComponent<EnemyDetector>()->GetLockOnTarget();


	if (m_target)
	{
		Vector2 screenPos = Core::GetInstance()->GetMainCamera()->WorldToScreenPos(m_target->GetTransform()->position);
		Vector2 enemyScreenPos = Vector2(screenPos.x * cosf(D3DXToRadian(90.f)), screenPos.y * sinf(D3DXToRadian(90.f)));

		Vector3 screenDir = dirX * enemyScreenPos.x + dirY * enemyScreenPos.y;
		D3DXVec3Normalize(&screenDir, &screenDir);
		m_firstDir = dirZ + screenDir;
	}

}

void ClusterBulletMove::Update()
{
	
}

void ClusterBulletMove::LateUpdate()
{
	if (m_target)
	{
		// screen Pos Set, for.VERTICAL Range
		Vector3 dir = m_target->GetTransform()->position - m_transform->position;
		D3DXVec3Normalize(&dir, &dir);
		m_firstDir = Nalmak_Math::Lerp(m_firstDir, m_player->GetTransform()->GetForward(), dTime);
		m_transform->position += ((dir + m_firstDir)  * 45.f * dTime);

		float EnemyPlayerLenght = Nalmak_Math::Distance(m_player->GetTransform()->position, m_target->GetTransform()->position);
		float fromEnemyLenght = Nalmak_Math::Distance(m_target->GetTransform()->position, m_gameObject->GetTransform()->position);
		float ratioValue = fromEnemyLenght / EnemyPlayerLenght;
		if (ratioValue <= 0.5f)
		{

			Boom();
			DESTROY(m_gameObject);
			m_deadCheck = true;
		}
	}
	else
	{
		m_transform->position += ((m_player->GetTransform()->GetForward())  * 45.f * dTime);

	}

	if (Nalmak_Math::Distance(m_player->GetTransform()->position, m_transform->position) > 250.f)
	{
		Boom();
		DESTROY(m_gameObject);
		m_gameObject = nullptr;
	}
}

void ClusterBulletMove::Release()
{
	if (m_deadCheck)
	{
		MeshRenderer::Desc render;
		render.meshName = L"kfir_weapon1";
		render.mtrlName = L"kfir";

		float angleInterval = PI2 / m_bulletCount;
		float length = 10.f;

		Player_NearGuideBullet::Desc guidebulletInfo;
		guidebulletInfo.speed = m_speed;
		guidebulletInfo.lockonTarget = m_enemyDetector;

		SphereCollider::Desc sphereColInfo;
		sphereColInfo.collisionLayer = COLLISION_LAYER_BULLET_PLAYER;
		

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
		m_deadCheck = false;

		Boom();
		m_gameObject = nullptr;
	}
	
}

void ClusterBulletMove::Boom()
{
	Vector3 pos = m_transform->GetWorldPosition();
	ParticleRenderer::Desc particle;
	particle.particleDataName = L"explosion_Flame";
	INSTANTIATE()->AddComponent<ParticleRenderer>(&particle)->AddComponent<ParticleDead_IfCount0>()->SetPosition(pos);
	particle.particleDataName = L"explosion_smokeBomb";
	INSTANTIATE()->AddComponent<ParticleRenderer>(&particle)->AddComponent<ParticleDead_IfCount0>()->SetPosition(pos);
	particle.particleDataName = L"explosion_spark";
	INSTANTIATE()->AddComponent<ParticleRenderer>(&particle)->AddComponent<ParticleDead_IfCount0>()->SetPosition(pos);
}
