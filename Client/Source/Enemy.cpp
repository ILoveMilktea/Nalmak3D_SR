#include "stdafx.h"
#include "..\Include\Enemy.h"

#include "Enemy_Bullet_Manager.h"
#include "Indicator_EnemyPos.h"


Enemy::Enemy(Desc * _Desc)
{
	m_tStatus =		_Desc->tStatus;

	m_tMachineGun = _Desc->tGun;
	m_tMissile =	_Desc->tMissile;
	m_tHoming =		_Desc->tHoming;

	m_pArrow_Indicator = _Desc->pArrow;
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

	m_pMainCamera = Core::GetInstance()->GetMainCamera();
	assert(L"거 에너미에서 메인카메라 못찾았다 이말이야"&&m_pMainCamera);
}

void Enemy::Update()
{
	Reloading_Gun();
	Reloading_Missile();


	Death_Check();
	Indicator_OnOff();

	if (m_bAccel)
	{
		Accelerate();
	}
	else { Decelerate(); }



#pragma region DebugLog
	//DEBUG_LOG(L"Enemy CurPos", m_transform->position);
	//DEBUG_LOG(L"CurHP", m_tStatus.m_iCurHp);
	//DEBUG_LOG(L"Ÿ�� ������ �Ÿ�",		m_fDist_Target);
	//DEBUG_LOG(L"forward���Ϳ� ���̺����� ����",		m_fInner);
	//DEBUG_LOG(L"Player is in the Enemy Fov", m_bFov);
	//DEBUG_LOG(L"Enemy Current Speed", m_tStatus.m_fCurSpd);
	//DEBUG_LOG(L"Enemy Max Spd", m_tStatus.m_fMaxSpd);
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
			//������ �Դ°� �� Player bullet���� ����.

			//if (m_pSmokeParticle == nullptr)
			//{
			//	m_pSmokeParticle = INSTANTIATE();
			//
			//	ParticleRenderer::Desc smoke_desc;
			//	smoke_desc.particleDataName = L"enemy_smoke_0";
			//	smoke_desc.PlayOnAwake = true; //���� ��ü ������ ���ÿ� ��ƼŬ on
			//	//��ƼŬ ������ EnemyDeath�� �ڼ��� ��������.

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
		if (m_gameObject->GetComponent<StateControl>()->GetCurStateString() != L"Falling"
			&& m_gameObject->GetComponent<StateControl>()->GetCurStateString() != L"Explosion"
			&& m_gameObject->GetComponent<StateControl>()->GetCurStateString() != L"Death")
		{
			if (m_pArrow_Indicator)
			{
				m_pArrow_Indicator->GetComponent<Indicator_EnemyPos>()->Release_Target();
				DESTROY(m_pArrow_Indicator);
				m_pArrow_Indicator = nullptr;
			}

		 //death State ->
			m_gameObject->GetComponent<StateControl>()
				->SetState(Nalmak_Math::Random<wstring>(L"Explosion", L"Falling"));

			
		}
	}
}

bool Enemy::Screen_Check()
{

	Vector2 ScreenPos = m_pMainCamera->WorldToScreenPos(m_transform->position);

/*	if (ScreenPos.x >= -(WINCX /2.f)&& ScreenPos.x <= (WINCX/2.f)
		&&
		ScreenPos.y >= -(WINCY /2.f) && ScreenPos.y <= (WINCY/2.f))*/
	if(ScreenPos.x >= -(TARGET_RANGE/2.f) && ScreenPos.x <= (TARGET_RANGE/2.f)
		&&
		ScreenPos.y >= -(TARGET_RANGE/ 2.f) && ScreenPos.y <= (TARGET_RANGE / 2.f))
	{//Inside Range
		return false;
	}

	return true;

}

void Enemy::Indicator_OnOff()
{
	if (m_pArrow_Indicator != nullptr)
	{
		m_pArrow_Indicator->SetActive(Screen_Check());
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

const float & Enemy::Get_CurSpd() const
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

void Enemy::Set_CurHp(int _hp)
{
	m_tStatus.m_iCurHp = _hp;
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

	// ���̺�,�Ҿ� �� �� ���� �Ҷ� ���� forward�� �޾� ���ٰ�
	// �� ���̶� �����ؼ� ������ �ɶ����� ��ü ����
	Vector3 vForward = m_transform->GetForward();
	//Vector3 WorldY = { 0.f,1.f,0.f };

	Go_Straight();

	m_fDiveInner = D3DXVec3Dot(&vForward, &m_vOriginForward);

	if (m_fDiveInner <= 0.1f && m_fDiveInner >= -0.1f) //���� 0�� ��������
	{
		//Go_Straight();
		//DEBUG_LOG(L"���̺� Inner", m_fDiveInner);
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

	if (m_fSoarInner <= 0.1f && m_fSoarInner >= -0.1f) //���� 0�� ��������
	{
		//Go_Straight();
		//DEBUG_LOG(L"Soar Inner", m_fSoarInner);
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
		m_tStatus.m_fCurSpd -= dTime * 5.0f;
	}

	if(m_tStatus.m_fCurSpd < 0.f)
	{
		m_tStatus.m_fCurSpd = 0.f;
	}
}
