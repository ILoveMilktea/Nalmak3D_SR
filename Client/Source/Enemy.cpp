#include "stdafx.h"
#include "..\Include\Enemy.h"

#include "Enemy_Bullet_Manager.h"


Enemy::Enemy(Desc * _Desc)
{
	m_tStatus =		_Desc->tStatus;
	
	m_tMachineGun = _Desc->tGun;
	m_tMissile =	_Desc->tMissile;
	m_tHoming =		_Desc->tHoming;
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	Target_Setting(true);
	Target_Update();
	Look_Target();

	m_vOriginForward = m_transform->GetForward();
}

void Enemy::Update()
{	
	Reloading_Gun();
	Reloading_Missile();

	Death_Check();

	if (m_bAccel)
	{
		Accelerate();
	}
	else { Decelerate(); }



#pragma region DebugLog
	DEBUG_LOG(L"Enemy CurPos", m_transform->position);
	//DEBUG_LOG(L"CurHP", m_tStatus.m_iCurHp);
	DEBUG_LOG(L"타겟 까지의 거리",		m_fDist_Target);
	//DEBUG_LOG(L"forward벡터와 사이벡터의 내적",		m_fInner);
	//DEBUG_LOG(L"Player is in the Enemy Fov", m_bFov);
	DEBUG_LOG(L"Enemy Current Speed", m_tStatus.m_fCurSpd);
	DEBUG_LOG(L"Enemy Max Spd", m_tStatus.m_fMaxSpd);
	//DEBUG_LOG(L"Remain Gun Round", m_tMachineGun.m_iRound_Cur);
	//DEBUG_LOG(L"Remain Missile Round", m_tMissile.m_iRound_Cur);
	DEBUG_LOG(L"Current Pattern", m_gameObject->GetComponent<StateControl>()->GetCurStateString());
#pragma endregion
}

void Enemy::OnTriggerEnter(Collisions & _collision)
{
	for (auto& obj : _collision)
	{ 
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_BULLET_PLAYER)
		{
			//데미지 입는건 거 Player bullet에서 해줌.


			//if (m_pSmokeParticle == nullptr)
			//{
			//	m_pSmokeParticle = INSTANTIATE();
			//	
			//	ParticleRenderer::Desc smoke_desc;
			//	smoke_desc.particleDataName = L"enemy_smoke_0";
			//	smoke_desc.PlayOnAwake = true; //기냥 객체 생성과 동시에 파티클 on
			//	//파티클 삭제는 EnemyDeath에 자세히 적어놨음.

			//	if (m_pSmokeParticle != nullptr)
			//	{
			//		m_pSmokeParticle->AddComponent<ParticleRenderer>(&smoke_desc);
			//	}
			//}
		}
	}
}



void Enemy::Target_Setting(bool _onoff)
 {	
	if (_onoff == true)
	{
		m_pTarget = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);

		if (m_pTarget)
		{
			/* First Inner Setting */
			Vector3 vDir = m_pTarget->GetTransform()->position - m_transform->position;
			D3DXVec3Normalize(&vDir, &vDir);
			
			m_fInner_First = D3DXVec3Dot(&vDir, &m_transform->GetForward());

			bTarget = true;
			return;
		}
	}
	else 
	{
		m_pTarget = nullptr;
		bTarget = false;
	}

}

void Enemy::Target_Update()
{
	if (bTarget) 
	{
		/* Dot calc to Target Direction Vector */
		/* for distance, fInner */
		Vector3 vDir = m_pTarget->GetTransform()->position - m_transform->position;
		m_fDist_Target = D3DXVec3Length(&vDir);
		D3DXVec3Normalize(&vDir, &vDir);

		m_fInner = D3DXVec3Dot(&vDir, &m_transform->GetForward());

		/* Dot calc to Target Up Vector */
		/* for horizontally */
		Vector3 Flight = { 0.f, 0.f, 0.f };
		D3DXVec3Normalize(&Flight, &m_transform->GetRight());

		Vector3 World = { 0.f, 1.f, 0.f };
		m_fUpInner = D3DXVec3Dot(&Flight, &World);
		m_fUpAngle = D3DXToDegree(acosf(m_fUpInner));
	}
}


void Enemy::Go_ToPos(Vector3 _pos)
{
	m_transform->LookAt(_pos, m_tStatus.m_fLookSpd, &m_QuartRot);
	//Go_Straight();
}

void Enemy::Go_Straight()
{
	m_transform->position += m_transform->GetForward() * m_tStatus.m_fCurSpd * dTime;
}

void Enemy::Look_Target()
{
	if (bTarget)
	{
		m_transform->LookAt(m_pTarget, m_tStatus.m_fLookSpd, &m_QuartRot);
	}
}

bool Enemy::Fov_Check()
{
	if (D3DXToRadian(m_fFov/2.f) >= acosf(m_fInner))
	{
		m_bFov = true;
		return true; 
	}
	else 
	{ 
		m_bFov = false; 
		return false;
	}
}

void Enemy::Death_Check()
{
	if (m_tStatus.m_iCurHp <= 0)
	{
		//지금 Falling, Death, Explosion상태 아닐때만 가능하게.
		if (m_gameObject->GetComponent<StateControl>()->GetCurStateString() != L"Falling"
			&&m_gameObject->GetComponent<StateControl>()->GetCurStateString() != L"Explosion"
			&&m_gameObject->GetComponent<StateControl>()->GetCurStateString() != L"Death")
		{
			m_gameObject->GetComponent<StateControl>()
				->SetState(Nalmak_Math::Random<wstring>(L"Explosion", L"Falling"));

			m_gameObject->DeleteComponent<SphereCollider>();

		}
	}
}

void Enemy::Damaged(const int & _playerDmg)
{
	m_tStatus.m_iCurHp -= _playerDmg;

	if (m_tStatus.m_iCurHp <= 0.f)
	{
		m_tStatus.m_iCurHp = 0;
	}
}

const ENEMY_STATUS & Enemy::Get_Status() const
{
	return m_tStatus;
}

const int & Enemy::Get_FullHp() const
{
	return m_tStatus.m_iFullHp;
}

const int & Enemy::Get_CurHp() const
{
	return m_tStatus.m_iCurHp;
}

const int & Enemy::Get_CurSpd() const
{
	return m_tStatus.m_fCurSpd;
}

const BULLET_STATUS & Enemy::Get_GunStatus() const
{
	return m_tMachineGun;
}

const BULLET_STATUS & Enemy::Get_MissileStatus() const
{
	return m_tMissile;
}

const BULLET_STATUS & Enemy::Get_HomingStatus() const
{
	return m_tHoming;
}

const int & Enemy::Get_GunDamage() const
{
	return m_tMachineGun.m_iDmg_Max;
}

const int & Enemy::Get_MissileDamage() const
{
	//Select Randomly Among min and max Dmg
	return m_tMissile.m_iDmg_Max;
}

const int & Enemy::Get_HomingDamage() const
{
	return  m_tHoming.m_iDmg_Max;
}

const int & Enemy::Get_GunCurRound() const
{
	return m_tMachineGun.m_iRound_Cur;
}

const int & Enemy::Get_GunFullRound() const
{
	return m_tMachineGun.m_iRound_Full;
}

const int & Enemy::Get_MissileCurRound() const
{
	return m_tMissile.m_iRound_Cur;
}

const int & Enemy::Get_MissileFullRound() const
{
	return m_tMissile.m_iRound_Full;
}


const int & Enemy::Get_HomingCurRound() const
{
	return m_tHoming.m_iRound_Cur;
}

const int & Enemy::Get_HomingFullRound() const
{
	return m_tHoming.m_iRound_Full;
}

const float & Enemy::Get_Distance() const
{
	return m_fDist_Target;
}

const float & Enemy::Get_Inner() const
{
	return m_fInner;
}

const Vector3 & Enemy::Get_RandPos() const
{
	return m_vRandPos;
}

void Enemy::Set_Damage(const int & _dmg)
{
}

void Enemy::Set_OriginForward()
{
	m_vOriginForward = m_transform->GetForward();
}

void Enemy::Set_CurSpd(float _spd)
{
	m_tStatus.m_fCurSpd = 0.f;
}

void Enemy::Set_Accel(bool _onoff)
{
	m_bAccel = _onoff;
}

void Enemy::Set_LookSpd(float _lookSpd)
{
	m_tStatus.m_fLookSpd = _lookSpd;
}

void Enemy::Horizontally()
{
	//Player Axis is not always alinged to World Y axis
	//therefore, need modify. alinged to Player Y axis.
	
	if (m_fInner >= 0.99f)
	{
		if (m_fUpAngle < 89.f)
		{
			Quaternion qTemp = m_transform->RotateAxis(m_transform->GetForward(), -dTime);
			m_transform->rotation *= qTemp;
		}
		if (m_fUpAngle > 89.f)
		{
			Quaternion qTemp = m_transform->RotateAxis(m_transform->GetForward(), dTime);
			m_transform->rotation *= qTemp;
		}
	}
	if (m_fInner < 0.f)
	{

	}
}

void Enemy::Turn()
{

}

bool Enemy::Dive()
{
	Target_Setting(false);
	
	Quaternion Xaxis = m_transform->RotateAxis(m_transform->GetRight(), dTime);
	m_transform->rotation *= Xaxis;

	// 다이브,소어 둘 다 시작 할때 원래 forward값 받아 놨다가 
	// 그 값이랑 비교해서 수직이 될때까지 몸체 돌기
	Vector3 vForward = m_transform->GetForward();
	//Vector3 WorldY = { 0.f,1.f,0.f };

	Go_Straight();

	m_fDiveInner = D3DXVec3Dot(&vForward, &m_vOriginForward);

	if (m_fDiveInner <= 0.1f && m_fDiveInner >= -0.1f) //범위 0에 가까우면
	{
		//Go_Straight();
		DEBUG_LOG(L"다이브 Inner", m_fDiveInner);
		return true;
	}
	return false;
}

bool Enemy::Soar()
{
	Target_Setting(false);

	Quaternion Xaxis = m_transform->RotateAxis(m_transform->GetRight(), -dTime);
	m_transform->rotation *= Xaxis;

	Vector3 vForward = m_transform->GetForward();
	//Vector3 WorldY = { 0.f,1.f,0.f };

	Go_Straight();

	m_fSoarInner = D3DXVec3Dot(&vForward, &m_vOriginForward);

	if (m_fSoarInner <= 0.1f && m_fSoarInner >= -0.1f) //범위 0에 가까우면
	{
		//Go_Straight();
		DEBUG_LOG(L"Soar Inner", m_fSoarInner);
		return true;
	}
	return false;
}

void Enemy::Create_RandPos()
{
	m_vRandPos.y = m_transform->position.y + rand() % 1001 - 500;
	m_vRandPos.x = m_transform->position.x + rand() % 1001 - 500;
	m_vRandPos.z = m_transform->position.z + rand() % 1001 - 500;

}

bool Enemy::Fire_Gun()
{
	if (m_tMachineGun.m_iRound_Cur > 0)
	{
		m_fGunFpmDelta += dTime;

		if (m_fGunFpmDelta >= 60.f / m_tMachineGun.m_fFpm
			&& Fov_Check())
		{
			Bullet_Manager::GetInstance()->Fire_Gun(m_transform->position, m_transform->rotation,
				m_tMachineGun.m_iDmg_Max, m_tMachineGun.m_fMaxSpd);
			--m_tMachineGun.m_iRound_Cur;
			m_fGunFpmDelta = 0.f;

			return true;
		}
		return false;
	}
	return false;
}

bool Enemy::Reloading_Gun()
{
	if (m_tMachineGun.m_iRound_Cur <= 0)
	{
		m_fGunReload += dTime;

		if (m_fGunReload >= m_tMachineGun.m_fReload)
		{
			m_tMachineGun.m_iRound_Cur = m_tMachineGun.m_iRound_Full;

			m_fGunReload = 0.f;
			
			return true;
		}
		return false;
	}
	return false;
}

bool Enemy::Fire_Missile()
{
	if (m_tMissile.m_iRound_Cur > 0)
	{
		m_fMissileFpmDelta += dTime;

		if (m_fMissileFpmDelta >= 60.f / m_tMissile.m_fFpm
			&& Fov_Check())
		{
			--m_tMissile.m_iRound_Cur;
			Bullet_Manager::GetInstance()->Fire_Missile(m_transform->position, m_transform->rotation);
			m_fMissileFpmDelta = 0.f;

			return true;
		}
		return false;
	}
	return false;
}

bool Enemy::Reloading_Missile()
{
	if (m_tMissile.m_iRound_Cur <= 0)
	{
		m_fMissileReload += dTime;

		if (m_fMissileReload >= m_tMissile.m_fReload)
		{
			m_tMissile.m_iRound_Cur = m_tMissile.m_iRound_Full;

			m_fMissileReload = 0.f;

			return true;
		}
		return false;
	}
	return false;
}

void Enemy::Accelerate()
{
	if (/*m_fDist_Target >= 100
		&& */m_tStatus.m_fCurSpd <= m_tStatus.m_fMaxSpd)
	{
		m_tStatus.m_fCurSpd += dTime * 10.f;
	}
}


void Enemy::Decelerate()
{	
	if (/*m_fDist_Target <= 50.f
		&& */m_tStatus.m_fCurSpd >= 0.f)
	{
		m_tStatus.m_fCurSpd -= dTime * 10.0f;
	}

	if(m_tStatus.m_fCurSpd < 0.f)
	{
		m_tStatus.m_fCurSpd = 0.f;
	}
}
