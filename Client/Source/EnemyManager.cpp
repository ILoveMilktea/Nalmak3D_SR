#include "stdafx.h"
#include "../Include/EnemyManager.h"

#include "Enemy.h"

#include "Enemy_Idle.h"
#include "Enemy_Chase.h"
#include "Enemy_Hold.h"
#include "Enemy_Drop.h"
#include "Enemy_Death.h"

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
		//int x, y, z;
		//x = rand() % 300 - 150;
		//y = rand() % 300 - 150;
		//z = rand() % 300 - 150;
		//Enemy_Spawn(Vector3((float)x, (float)y, (float)z));
		Enemy_Spawn(Vector3(0.f, 20.f, 150.f), ENEMY_STATE::CHASE);
	}
}

const int & EnemyManager::Get_EnemyCount() const
{
	return int(0);
}


void EnemyManager::Enemy_Spawn(Vector3 _pos, ENEMY_STATE _initState)
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

	Enemy::Desc Enemy_desc;
	/*desc 세팅*/
	Enemy_obj->AddComponent<Enemy>(&Enemy_desc);
	
	
	MeshRenderer::Desc Enemy_Mesh;
	Enemy_Mesh.mtrlName = L"default";
	Enemy_Mesh.meshName = L"flight";
	Enemy_obj->AddComponent<MeshRenderer>(&Enemy_Mesh);

	SphereCollider::Desc Enemy_col;
	Enemy_col.radius = 1.f;
	Enemy_col.collisionLayer = COLLISION_LAYER_ENEMY;
	Enemy_obj->AddComponent<SphereCollider>(&Enemy_col);
}

