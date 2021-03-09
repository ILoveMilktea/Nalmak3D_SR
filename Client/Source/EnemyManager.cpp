#include "stdafx.h"
#include "../Include/EnemyManager.h"

#include "Enemy.h"
#include "Enemy_Boss.h"

#include "Enemy_Idle.h"
#include "Enemy_Chase.h"
#include "Enemy_Hold.h"
#include "Enemy_Drop.h"
#include "Enemy_Death.h"
#include "Enemy_Explosion.h"
#include "Enemy_Falling.h"

#include "Enemy_Slide_Evasion.h"
#include "Enemy_Diagonal_Evasion.h"
#include "Enemy_CrossFire_Evasion.h"
#include "Enemy_Circle_Evasion.h"
#include "Enemy_Prymide_Evasion.h"
#include "Enemy_AirFire_Evasion.h"
#include "Enemy_Look_Evasion.h"
#include "Enemy_Exit_Evasion.h"
#include "Boss_Enter.h"
#include "Boss_Interrupt.h"

#include "Enemy_Evasion_Appear.h"
#include "Enemy_Evasion_Disappear.h"
#include "MidBoss_Headers.h"
#include "MidBoss_Define.h"
#include "Enemy_Debugging.h"
#include "Player_WindEffect.h"
#include "PlayerInfoManager.h"

EnemyManager* EnemyManager::m_Instance = nullptr;


EnemyManager::EnemyManager(Desc * _Desc)
{
}

EnemyManager::~EnemyManager()
{

}

EnemyManager * EnemyManager::GetInstance()
{
	if (!m_Instance)
	{

		auto Instance = INSTANTIATE();
		Instance->AddComponent<EnemyManager>();
		m_Instance = Instance->GetComponent<EnemyManager>();

		Instance->SetDontDestroy(true);
	}

	return m_Instance;
}

void EnemyManager::DeleteInstance()
{
	if (m_Instance)
	{
		DESTROY(m_Instance->GetGameObject());
	}

}

void EnemyManager::Initialize()
{


}

void EnemyManager::Update()
{

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_K))
	{
		ENEMY_STATUS temp;
		temp.m_iFullHp = 10;
		temp.m_iCurHp = 10;

		Enemy_Spawn(Vector3(50.f, 50.f, 50.f), Vector3(0.2f, 0.2f, 0.2f), IDLE, temp);
	}

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_SHIFT)
		&& InputManager::GetInstance()->GetKeyDown(KEY_STATE_LEFT_MOUSE))
	{
		Enemy_Spawn_Debug();
	}

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F9))
	{
		Destroy_AllEnemy();
	}

	DEBUG_LOG(L"Remianed Enemy Count", m_iEnemyCount);
}

int EnemyManager::Get_EnemyCount() const
{
	//size_t size = Core::GetInstance()->GetObjectList(OBJECT_TAG_ENEMY).size();
	return  m_iEnemyCount;
}

list<GameObject*> EnemyManager::Get_EnemyList() const
{
	return Core::GetInstance()->GetObjectList(OBJECT_TAG_ENEMY);
}

int EnemyManager::Get_BossHp() const
{
	return Core::GetInstance()->FindObjectByName(OBJECT_TAG_BOSS, L"Boss")->GetComponent<Boss>()->Get_CurHp();
}

const Vector3 & EnemyManager::Get_BossPos() const
{
		return m_pBoss->GetTransform()->position;
}

int EnemyManager::Get_BossCount() const
{
	return m_iBossCount;
}

GameObject * EnemyManager::Get_Boss()
{
	if (m_pBoss == nullptr)
	{
		Boss_Spawn();
		return m_pBoss;
	}

	return m_pBoss;
}

void EnemyManager::Add_EnemyCount(int _count)
{
	m_iEnemyCount += _count;
}

GameObject * EnemyManager::NearFindEenemy( GameObject * _finderObj, float _minDis)
{
	GameObject* target = nullptr;
	float mindis = _minDis;
	for (auto& value : Get_EnemyList())
	{
		float lenght = Nalmak_Math::Distance(value->GetTransform()->position, _finderObj->GetTransform()->position);
		lenght = abs(lenght);
		//value->

		if (mindis > lenght || !target)
		{
			target = value;
			mindis =lenght;
			break;
		}
	}

	return target;
}

void EnemyManager::Boss_Release()
{
	--m_iBossCount;
	m_pBoss = nullptr;
}

void EnemyManager::Destroy_AllEnemy()
{
	for (auto& enemy : Get_EnemyList())
	{
		DESTROY(enemy);
	}
	m_iEnemyCount = 0;
}

void EnemyManager::Enemy_Spawn_Debug(Vector3 _scale,
	ENEMY_STATE _initState, ENEMY_STATUS _status)
{
	Camera* MainCamera = Core::GetInstance()->GetMainCamera();

	Vector3 vMouseDir = MainCamera->GetCamToMouseWorldDirection();

	float fDistance = 100.f;
	Vector3 vResult = MainCamera->GetTransform()->position + vMouseDir * 100.f;

	Enemy_Spawn(vResult, Vector3(0.1f, 0.1f, 0.1f), _initState, _status);
}


void EnemyManager::Enemy_Spawn(Vector3 _pos, Vector3 _scale,
	ENEMY_STATE _initState, ENEMY_STATUS _status,
	BULLET_STATUS _gun, BULLET_STATUS _missile, BULLET_STATUS _homing)
{
	GameObject* Enemy_obj = INSTANTIATE(OBJECT_TAG_ENEMY, L"Enemy");
	Enemy_obj->SetPosition(_pos);
	Enemy_obj->GetTransform()->scale = _scale;

	Enemy_obj->AddComponent<StateControl>();
	StateControl* m_pStateControl = Enemy_obj->GetComponent<StateControl>();
	m_pStateControl->AddState<Enemy_Idle>(L"Idle");
	m_pStateControl->AddState<Enemy_Chase>(L"Chase");
	m_pStateControl->AddState<Enemy_Hold>(L"Hold");
	m_pStateControl->AddState<Enemy_Drop>(L"Drop");
	m_pStateControl->AddState<Enemy_Explosion>(L"Explosion");
	m_pStateControl->AddState<Enemy_Falling>(L"Falling");
	m_pStateControl->AddState<Enemy_Death>(L"Death");

	m_pStateControl->AddState<Enemy_Debugging>(L"Debugging");


	switch (_initState)
	{
	case IDLE:
	{
		m_pStateControl->InitState(L"Idle");
	}
	break;
	case CHASE:
	{
		m_pStateControl->InitState(L"Chase");
	}
		break;
	case HOLD:
	{
		m_pStateControl->InitState(L"Hold");
	}
		break;
	case DROP:
	{
		m_pStateControl->InitState(L"Drop");
	}
		break;
	case EXPLOSION:
	{
		m_pStateControl->InitState(L"Explosion");
	}
	break;

	case FALLING:
	{m_pStateControl->InitState(L"Falling"); }
	break;

	case DEATH:
	{
		m_pStateControl->InitState(L"Death");
	}
	break;

	case DEBUGGING:
	{
		m_pStateControl->InitState(L"Debugging");
	}
	break;

	case ENEMY_STATE_MAX:
		break;
	default:
		break;
	}


	Enemy::Desc Enemy_desc(_status, _gun, _missile);
	Enemy_obj->AddComponent<Enemy>(&Enemy_desc);


	MeshRenderer::Desc Enemy_Mesh;
	Enemy_Mesh.mtrlName = L"su34";
	Enemy_Mesh.meshName = L"su34";
	Enemy_obj->AddComponent<MeshRenderer>(&Enemy_Mesh);

	Player_WindEffect::Desc wind;
	wind.leftTrailPos = Vector3(-1.6f, 0.5f, 0.f);
	wind.rightTrailPos = Vector3(1.6f, 0.5f, 0.f);
	wind.trailThick = 0.2f;
	Enemy_obj->AddComponent<Player_WindEffect>(&wind);



	SphereCollider::Desc Enemy_col;
	Enemy_col.radius = 5.f;
	Enemy_col.collisionLayer = COLLISION_LAYER_ENEMY;
	Enemy_obj->AddComponent<SphereCollider>(&Enemy_col);

	++m_iEnemyCount;
}

void EnemyManager::Enemy_Spawn_Test(ENEMY_STATE _initState, Vector3 pos)
{
}


void EnemyManager::Enemy_Spawn_Evasion(
	ENEMY_EVASION_STATE _initState,
	Vector3 _spawnPos,
	Vector3 _destpos,
	float _lifeTime)
{
	GameObject* Enemy_obj = INSTANTIATE(OBJECT_TAG_ENEMY, L"Enemy");
	Enemy_obj->SetRotation(0.f, 180.f, 0.f);
	Enemy_obj->SetScale(0.1f, 0.1f, 0.1f);

	Enemy_obj->AddComponent<StateControl>();
	m_pStateControl = Enemy_obj->GetComponent<StateControl>();

	m_pStateControl->AddState<Exit_Evasion>(L"Exit");
	m_pStateControl->AddState<Enemy_Explosion>(L"Explosion");
	m_pStateControl->AddState<Enemy_Falling>(L"Falling");
	m_pStateControl->AddState<Enemy_Death>(L"Death");

	// appear
	m_pStateControl->AddState<Enemy_Evasion_Appear>(L"Evasion_Appear");
	Enemy_Evasion_Appear* appearState = m_pStateControl->GetState<Enemy_Evasion_Appear>(L"Evasion_Appear");
	appearState->SetStartPos(_spawnPos);
	appearState->SetDestPos(_destpos);

	m_pStateControl->AddState<Enemy_Evasion_Disappear>(L"Evasion_Disappear");
	Enemy_Evasion_Disappear* d_state = m_pStateControl->GetState<Enemy_Evasion_Disappear>(L"Evasion_Disappear");
	d_state->SetDestPos(_spawnPos);

	// pattern
	switch (_initState)
	{
	case SLIDE:
	{
		m_pStateControl->AddState<Slide_Evasion>(L"Slide");
		m_pStateControl->InitState(L"Slide");
	}
	break;
	case DIAGONAL:
	{
		m_pStateControl->AddState<Diagonal_Evasion>(L"Diagonal");
		m_pStateControl->InitState(L"Diagonal");
	}
	break;
	case CROSSFIRE:
	{
		Enemy_obj->SetPosition(_spawnPos);
		m_pStateControl->AddState<CrossFire_Evasion>(L"CrossFire");
		m_pStateControl->GetState<CrossFire_Evasion>(L"CrossFire")->SetLifeTime(_lifeTime);
		appearState->SetNextState(L"CrossFire");
		m_pStateControl->InitState(L"Evasion_Appear");
	}
	break;
	case LOOK:
	{
		Enemy_obj->SetPosition(_spawnPos);
		m_pStateControl->AddState<Look_Evasion>(L"Look");
		m_pStateControl->GetState<Look_Evasion>(L"Look")->SetLifeTime(_lifeTime);
		appearState->SetNextState(L"Look");
		m_pStateControl->InitState(L"Evasion_Appear");
	}
	break;
	case CIRCLE:
	{
		Enemy_obj->SetPosition(_spawnPos);
		m_pStateControl->AddState<Circle_Evasion>(L"Circle");
		m_pStateControl->GetState<Circle_Evasion>(L"Circle")->SetLifeTime(_lifeTime);
		appearState->SetNextState(L"Circle");
		m_pStateControl->InitState(L"Evasion_Appear");
	}
	break;
	case PRYMIDE:
	{
		Enemy_obj->SetPosition(_spawnPos);
		m_pStateControl->AddState<Prymide_Evasion>(L"Prymide");
		m_pStateControl->GetState<Prymide_Evasion>(L"Prymide")->SetLifeTime(_lifeTime);
		appearState->SetNextState(L"Prymide");
		m_pStateControl->InitState(L"Evasion_Appear");
	}
	break;
	case AIRFIRE:
	{
		Enemy_obj->SetPosition(_spawnPos);
		m_pStateControl->AddState<AirFire_Evasion>(L"AirFire");
		m_pStateControl->GetState<AirFire_Evasion>(L"AirFire")->SetLifeTime(_lifeTime);
		appearState->SetNextState(L"AirFire");
		m_pStateControl->InitState(L"Evasion_Appear");
	}
	break;
	}


	Enemy::Desc Enemy_desc;

	Enemy_obj->AddComponent<Enemy>(&Enemy_desc);


	VIBufferRenderer::Desc Enemy_Mesh;
	Enemy_Mesh.mtrlName = L"default";
	Enemy_Mesh.meshName = L"flight";
	Enemy_obj->AddComponent<VIBufferRenderer>(&Enemy_Mesh);

	SphereCollider::Desc Enemy_col;
	Enemy_col.radius = 1.f;
	Enemy_col.collisionLayer = COLLISION_LAYER_ENEMY;
	Enemy_obj->AddComponent<SphereCollider>(&Enemy_col);

	++m_iEnemyCount;

}

void EnemyManager::MidBoss_Spawn(Vector3 _pos)
{
	GameObject* boss = INSTANTIATE(OBJECT_TAG_MIDBOSS, L"MidBoss");
	boss->SetPosition(_pos);
	boss->SetRotation(0.f, 180.f, 0.f);
	boss->SetScale(20.f, 20.f, 20.f);

	boss->AddComponent<StateControl>();
	StateControl* stateControl = boss->GetComponent<StateControl>();

	// add staaaaaaaaate
	{
		stateControl->AddState<MidBoss_Appear>(_sn_appear);
		stateControl->AddState<MidBoss_Idle>(_sn_idle);
		stateControl->AddState<MidBoss_MoveLeft>(_sn_moveLeft);
		stateControl->AddState<MidBoss_MoveRight>(_sn_moveRight);
		stateControl->AddState<MidBoss_MoveToCenter>(_sn_moveToCenter);
		stateControl->AddState<MidBoss_Rotate180>(_sn_rotate180);

		stateControl->AddState<MidBoss_Wave_Start>(_sn_waveStart);
		stateControl->AddState<MidBoss_Wave_Idle>(_sn_waveIdle);
		stateControl->AddState<MidBoss_Wave_Attack>(_sn_waveAttack);

		stateControl->AddState<MidBoss_Sweep_Start>(_sn_sweepStart);
		stateControl->AddState<MidBoss_Sweep_Left>(_sn_sweepLeft);
		stateControl->AddState<MidBoss_Sweep_Right>(_sn_sweepRight);
		stateControl->AddState<MidBoss_Sweep_MoveToForward>(_sn_sweepMoveToForward);

		stateControl->AddState<MidBoss_Laser_Start>(_sn_laserStart);
		stateControl->AddState<MidBoss_Laser_Siege>(_sn_laserSiege);
		stateControl->AddState<MidBoss_Laser_Charge>(_sn_laserCharge);
		stateControl->AddState<MidBoss_Laser_Discharge>(_sn_laserDischarge);
		stateControl->AddState<MidBoss_Laser_Fire>(_sn_laserFire);
		stateControl->AddState<MidBoss_Laser_Attach>(_sn_laserAttach);
		stateControl->AddState<MidBoss_Laser_Detach>(_sn_laserDetach);

		stateControl->AddState<MidBoss_Defense_Start>(_sn_defenseStart);
		stateControl->AddState<MidBoss_Defense_Move>(_sn_defenseMove);

		stateControl->InitState(_sn_appear);
	}

	auto bulletproofPivot = INSTANTIATE();
	bulletproofPivot->SetParents(boss);
	bulletproofPivot->SetPosition(0.f, 0.f, 0.f);

	ENEMY_STATUS Boss_Status(1000, 0, 0);

	Enemy_MidBoss::Desc Boss_Desc(Boss_Status);
	Boss_Desc.pivot = bulletproofPivot;
	/*desc */
	boss->AddComponent<Enemy_MidBoss>(&Boss_Desc);

	VIBufferRenderer::Desc Boss_Mesh;
	Boss_Mesh.mtrlName = L"boss";
	Boss_Mesh.meshName = L"sphere";
	boss->AddComponent<VIBufferRenderer>(&Boss_Mesh);

	SphereCollider::Desc Boss_col;
	float colRadius = boss->GetTransform()->scale.x * 0.5f;
	Boss_col.radius = colRadius;
	Boss_col.collisionLayer = COLLISION_LAYER_ENEMY;
	boss->AddComponent<SphereCollider>(&Boss_col);



	// bulletproof plates

	Vector3 shieldModePos[4];
	for (int i = 0; i < 4; ++i)
	{
		float cosValue = cosf(Deg2Rad * (45.f - 90.f * i));
		float sinValue = sinf(Deg2Rad * (45.f - 90.f * i));
		shieldModePos[i] = Vector3(colRadius * cosValue, 0.f, colRadius * sinValue);

	}

	Vector3 attackModePos[4] =
	{
		Vector3(colRadius * 3.f, 0.f, 0.f),
		Vector3(colRadius * 2.f, 0.f, -colRadius * 2.f),
		Vector3(-colRadius * 2.f, 0.f, -colRadius * 2.f),
		Vector3(-colRadius * 3.f, 0.f, 0.f)
	};

	colRadius *= 0.8f;
	for (int i = 0; i < 4; ++i)
	{
		ENEMY_STATUS plate_status(9999, 0, 0);

		Enemy_BulletProof::Desc desc_bp(plate_status);
		desc_bp.shieldModePos = shieldModePos[i];
		desc_bp.attackModePos = attackModePos[i];

		VIBufferRenderer::Desc desc_plate;
		desc_plate.mtrlName = L"default_blue";
		desc_plate.meshName = L"sphere";

		SphereCollider::Desc desc_col;
		desc_col.radius = colRadius * 0.5f;
		desc_col.collisionLayer = COLLISION_LAYER_ENEMY_SHIELD;

		auto plate = INSTANTIATE(OBJECT_TAG_ENEMYSHIELD);
		plate->AddComponent<Enemy_BulletProof>(&desc_bp);
		plate->AddComponent<VIBufferRenderer>(&desc_plate);
		plate->AddComponent<SphereCollider>(&desc_col);

		plate->SetParents(bulletproofPivot);
		plate->SetScale(colRadius, colRadius, colRadius);
	}


	++m_iEnemyCount;
}

GameObject* EnemyManager::Boss_Spawn()
{
	GameObject* Boss_obj = INSTANTIATE(OBJECT_TAG_BOSS, L"Boss");
	Boss_obj->SetPosition(Vector3(0.f, 0.f, 120.f));
	Boss_obj->SetScale(100.f, 100.f, 100.f);

	ENEMY_STATUS Boss_Status(1000, 0, 0);

	Boss::Desc Boss_Desc(Boss_Status);

	Boss_obj->AddComponent<Boss>(&Boss_Desc);

	VIBufferRenderer::Desc Boss_Mesh;
	Boss_Mesh.mtrlName = L"boss";
	Boss_Mesh.meshName = L"box";
	Boss_obj->AddComponent<VIBufferRenderer>(&Boss_Mesh);

	SphereCollider::Desc Boss_col;
	Boss_col.radius = 50.f;
	Boss_col.collisionLayer = COLLISION_LAYER_ENEMY;
	Boss_obj->AddComponent<SphereCollider>(&Boss_col);

	Boss_obj->AddComponent<StateControl>();
	StateControl* Boss_stateControler = Boss_obj->GetComponent<StateControl>();
	Boss_stateControler->AddState<Boss_Enter>(L"Boss_Enter");
	Boss_stateControler->AddState<Boss_Interrupt>(L"Boss_Interrupt");

	Boss_stateControler->InitState(L"Boss_Enter");

	++m_iEnemyCount;
	++m_iBossCount;
	m_pBoss = Boss_obj;

	return m_pBoss;
}

void EnemyManager::Player_FovSpawnTest(bool _front, float _distance)
{
	if (_front)
	{

		Vector3 vResult;

		Vector2 vScreenSpace = { WINCX/2.f, WINCY/2.f };
		Vector3 vProjSpace;

		vProjSpace.x = vScreenSpace.x / (WINCX * 0.5f) - 1.f;
		vProjSpace.y = 1.f - (vScreenSpace.y / (WINCY * 0.5f));
		vProjSpace.z = 1.f;

		Matrix matProj_Inverse;
		D3DXMatrixInverse(&matProj_Inverse, 0, &Core::GetInstance()->GetMainCamera()->GetProjMatrix());
		Vector3 vViewSpace;
		D3DXVec3TransformCoord(&vViewSpace, &vProjSpace, &matProj_Inverse);


		Matrix matView_Inverse;
		D3DXMatrixInverse(&matView_Inverse, 0, &Core::GetInstance()->GetMainCamera()->GetViewMatrix());
		D3DXVec3TransformCoord(&vResult, &vViewSpace, &matView_Inverse);


		D3DXVec3Normalize(&vResult, &vResult);
		Vector3 temp = Core::GetInstance()->GetMainCamera()->GetTransform()->position + vResult * 100.f;


		Enemy_Spawn(temp);


	}

	if (!_front)
	{
		Vector3 vPlayerPos = PlayerInfoManager::GetInstance()->GetPlayer()->GetTransform()->position;

		Vector3 vResult;

		Vector2 vScreenSpace = { WINCX / 2.f, WINCY / 2.f };
		Vector3 vProjSpace;

		vProjSpace.x = vScreenSpace.x / (WINCX * 0.5f) - 1.f;
		vProjSpace.y = 1.f - (vScreenSpace.y / (WINCY * 0.5f));
		vProjSpace.z = 1.f;

		Matrix matProj_Inverse;
		D3DXMatrixInverse(&matProj_Inverse, 0, &Core::GetInstance()->GetMainCamera()->GetProjMatrix());
		Vector3 vViewSpace;
		D3DXVec3TransformCoord(&vViewSpace, &vProjSpace, &matProj_Inverse);


		Matrix matView_Inverse;
		D3DXMatrixInverse(&matView_Inverse, 0, &Core::GetInstance()->GetMainCamera()->GetViewMatrix());
		D3DXVec3TransformCoord(&vResult, &vViewSpace, &matView_Inverse);


		D3DXVec3Normalize(&vResult, &(vResult));
		Vector3 temp = Core::GetInstance()->GetMainCamera()->GetTransform()->position + vResult * _distance * -1.f;


		Enemy_Spawn(temp);
	}
}

Vector3 EnemyManager::Pos_ScreenToWorld(float _x, float _y, float _distance)
{
	Vector3 vResult;

	Vector2 vScreenSpace = { _x, _y };
	Vector3 vProjSpace;


	vProjSpace.x = vScreenSpace.x / (WINCX * 0.5f) - 1.f;
	vProjSpace.y = 1.f - (vScreenSpace.y / (WINCY * 0.5f));
	vProjSpace.z = 1.f;

	Matrix matProj_Inverse;
	D3DXMatrixInverse(&matProj_Inverse, 0, &Core::GetInstance()->GetMainCamera()->GetProjMatrix());
	Vector3 vViewSpace;
	D3DXVec3TransformCoord(&vViewSpace, &vProjSpace, &matProj_Inverse);


	Matrix matView_Inverse;
	D3DXMatrixInverse(&matView_Inverse, 0, &Core::GetInstance()->GetMainCamera()->GetViewMatrix());
	D3DXVec3TransformCoord(&vResult, &vViewSpace, &matView_Inverse);


	D3DXVec3Normalize(&vResult, &vResult);
	Vector3 temp = Core::GetInstance()->GetMainCamera()->GetTransform()->position + vResult * _distance;

	return temp;
}



void EnemyManager::Spawn_S1P1_Normal()
{
	//Stage1 Phase1 -> Stage1 DogFight's 1Pattern => like tutorial.
	//The big one & four Wls

	/* Four Wls */
	for (int i = 0; i < 4; ++i)
	{
		ENEMY_STATUS tStatus(10, 20, 1);
		BULLET_STATUS tGun(0, 10, 50, 3, 180, 100, 0);

		Vector2 vRand = Nalmak_Math::Rand(Vector2(0.f, 0.f), Vector2((float)WINCX, (float)WINCY));
		Vector3 vPos = Pos_ScreenToWorld(vRand.x, vRand.y, 400.f);


		Enemy_Spawn(vPos, Vector3(0.2f, 0.2f, 0.2f), ENEMY_STATE::IDLE, tStatus, tGun);
	}
}

void EnemyManager::Spawn_S1P1_Huge()
{
	ENEMY_STATUS tStatus(10, 15, 1);
	BULLET_STATUS tGun(0, 10, 50, 3, 180, 100, 0);

	Vector3 vPos = Pos_ScreenToWorld(WINCX / 2.f, WINCY / 2.f, 400.f);

	Enemy_Spawn(vPos, Vector3(0.7f, 0.7f, 0.7f), ENEMY_STATE::IDLE, tStatus, tGun);

}



void EnemyManager::Spawn_S1P1_Quick()
{
	for (int i = 0; i < 4; ++i)
	{
		ENEMY_STATUS tStatus(5, 25, 1);
		BULLET_STATUS tGun(0, 10, 50, 3, 180, 100, 0);

		Vector2 vRand = Nalmak_Math::Rand(Vector2(-20.f, -20.f), Vector2((float)WINCX +20.f, (float)WINCY + 20.f));
		Vector3 vPos = Pos_ScreenToWorld(vRand.x, vRand.y, -200.f);


		Enemy_Spawn(vPos, Vector3(0.2f, 0.2f, 0.2f), ENEMY_STATE::HOLD, tStatus, tGun);
	}
}
