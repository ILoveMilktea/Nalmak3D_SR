#include "stdafx.h"
#include "../Include/EnemyManager.h"

#include "Enemy.h"
#include "Boss.h"

#include "Enemy_Idle.h"
#include "Enemy_Chase.h"
#include "Enemy_Hold.h"
#include "Enemy_Drop.h"
#include "Enemy_Death.h"
#include "Enemy_Explosion.h"
#include "Enemy_Falling.h"

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
	{//업데이트를 쓰기 위해서 야를 Component를 상속받은 컴포넌트 객체루다가 만듦.
		
		auto Instance = INSTANTIATE();
		Instance->AddComponent<EnemyManager>();
		m_Instance = Instance->GetComponent<EnemyManager>();
		
		Instance->SetDontDestroy(true);//씬 넘어가도 지우지마라 이거야.
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
{//유니티의 스따뜨

	
}

void EnemyManager::Update()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F1))
	{
		ENEMY_STATUS tStatus(10, 20, 1);
		BULLET_STATUS tGun(0, 10, 50, 3, 180, 100, 0);
		BULLET_STATUS tMissile(10, 50, 5, 10, 30, 50, 0);


		Enemy_Spawn(Vector3(0.f, 0.f, 100.f), ENEMY_STATE::HOLD,
			tStatus,tGun,tMissile);
	}

	DEBUG_LOG(L"Remianed Enemy Count", m_iEnemyCount);
}

int EnemyManager::Get_EnemyCount() const
{
	//size_t size = Core::GetInstance()->GetObjectList(OBJECT_TAG_ENEMY).size();
	//최적화를 위해서 그냥 멤버 변수루다가 넘기자
	return  m_iEnemyCount;
}

list<GameObject*> EnemyManager::Get_EnemyList() const
{
	return Core::GetInstance()->GetObjectList(OBJECT_TAG_ENEMY);
}

void EnemyManager::Add_EnemyCount(int _count)
{
	m_iEnemyCount += _count;
}



void EnemyManager::Destroy_AllEnemy()
{
	for (auto& enemy : Get_EnemyList())
	{
		DESTROY(enemy);
	}
	m_iEnemyCount = 0;
}

void EnemyManager::Enemy_Spawn(Vector3 _pos,
	ENEMY_STATE _initState, ENEMY_STATUS _status, 
	BULLET_STATUS _gun, BULLET_STATUS _missile, BULLET_STATUS _homing)
{
	GameObject* Enemy_obj = INSTANTIATE(OBJECT_TAG_ENEMY, L"Enemy");
	Enemy_obj->SetPosition(_pos);
	Enemy_obj->SetScale(0.1f,0.1f,0.1f);

	Enemy_obj->AddComponent<StateControl>();
	m_pStateControl = Enemy_obj->GetComponent<StateControl>();
	m_pStateControl->AddState<Enemy_Idle>(L"Idle");
	m_pStateControl->AddState<Enemy_Chase>(L"Chase");
	m_pStateControl->AddState<Enemy_Hold>(L"Hold");
	m_pStateControl->AddState<Enemy_Drop>(L"Drop");
	m_pStateControl->AddState<Enemy_Explosion>(L"Explosion");
	m_pStateControl->AddState<Enemy_Falling>(L"Falling");
	m_pStateControl->AddState<Enemy_Death>(L"Death");
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
	{m_pStateControl->InitState(L"Explosion"); }
	break;

	case FALLING:
	{m_pStateControl->InitState(L"Falling"); }
	break;

	case DEATH:
	{
		m_pStateControl->InitState(L"Death");
	}
		break;
	case ENEMY_STATE_MAX:
		break;
	default:
		break;
	}


	Enemy::Desc Enemy_desc(_status, _gun, _missile);
	/*desc 세팅*/
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

void EnemyManager::Boss_Spawn()
{
	GameObject* Boss_obj = INSTANTIATE(OBJECT_TAG_BOSS, L"Boss");
	Boss_obj->SetPosition(Vector3(0.f, 0.f, 200.f));
	Boss_obj->SetScale(100.f, 200.f, 100.f);

	Boss::Desc Boss_Desc;
	/*desc 세팅*/
	Boss_obj->AddComponent<Boss>(&Boss_Desc);

	VIBufferRenderer::Desc Boss_Mesh;
	Boss_Mesh.mtrlName = L"niniz";
	Boss_Mesh.meshName = L"box";
	Boss_obj->AddComponent<VIBufferRenderer>(&Boss_Mesh);

	SphereCollider::Desc Boss_col;
	Boss_col.radius = 100.f;
	Boss_col.collisionLayer = COLLISION_LAYER_ENEMY;
	Boss_obj->AddComponent<SphereCollider>(&Boss_col);

	++m_iEnemyCount;

}

