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

	//if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F1))
	//{
	//	Player_FovSpawnTest(true, 100.f);
	//	//Spawn_S1P1();
	//}

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F9))
	{
		Destroy_AllEnemy();
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

int EnemyManager::Get_BossHp() const
{
	return Core::GetInstance()->FindObjectByName(OBJECT_TAG_ENEMY, L"Boss")->GetComponent<Boss>()->Get_CurHp();
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

void EnemyManager::Enemy_Spawn(Vector3 _pos, Vector3 _scale,
	ENEMY_STATE _initState, ENEMY_STATUS _status,
	BULLET_STATUS _gun, BULLET_STATUS _missile, BULLET_STATUS _homing)
{
	GameObject* Enemy_obj = INSTANTIATE(OBJECT_TAG_ENEMY, L"Enemy");
	Enemy_obj->SetPosition(_pos);
	Enemy_obj->GetTransform()->scale = _scale;

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
	Enemy_col.radius = 5.f;
	Enemy_col.collisionLayer = COLLISION_LAYER_ENEMY;
	Enemy_obj->AddComponent<SphereCollider>(&Enemy_col);

	++m_iEnemyCount;
}

void EnemyManager::Enemy_Spwan_Evasion(ENEMY_EVASION_STATE _initState)
{
	GameObject* Enemy_obj = INSTANTIATE(OBJECT_TAG_ENEMY, L"Enemy");
	Enemy_obj->SetRotation(0.f, 180.f, 0.f);
	Enemy_obj->SetScale(0.1f, 0.1f, 0.1f);

	Enemy_obj->AddComponent<StateControl>();
	m_pStateControl = Enemy_obj->GetComponent<StateControl>();
	m_pStateControl->AddState<Slide_Evasion>(L"Slide");
	m_pStateControl->AddState<Diagonal_Evasion>(L"Diagonal");
	m_pStateControl->AddState<CrossFire_Evasion>(L"CrossFire");
	m_pStateControl->AddState<Look_Evasion>(L"Look");
	m_pStateControl->AddState<Circle_Evasion>(L"Circle");
	m_pStateControl->AddState<Prymide_Evasion>(L"Prymide");
	m_pStateControl->AddState<AirFire_Evasion>(L"AirFire");
	m_pStateControl->AddState<Exit_Evasion>(L"Exit");
	//m_pStateControl->AddState<Enemy_Explosion>(L"Explosion");
	//m_pStateControl->AddState<Enemy_Falling>(L"Falling");
	//m_pStateControl->AddState<Enemy_Death>(L"Death");

	switch (_initState)
	{
	case SLIDE:
	{m_pStateControl->InitState(L"Slide"); }
		break;
	case DIAGONAL:
	{m_pStateControl->InitState(L"Diagonal"); }
		break;
	case CROSSFIRE:
	{m_pStateControl->InitState(L"CrossFire"); }
		break;
	case LOOK:
	{m_pStateControl->InitState(L"Look"); }
		break;
	case CIRCLE:
	{m_pStateControl->InitState(L"Circle"); }
		break;
	case PRYMIDE:
	{m_pStateControl->InitState(L"Prymide"); }
		break;
	case AIRFIRE:
	{m_pStateControl->InitState(L"AirFire"); }
		break;
	case EVASION_STATE_MAX:
		break;
	default:
		break;
	}


	Enemy::Desc Enemy_desc;
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
	Boss_obj->SetScale(100.f, 100.f, 100.f);

	ENEMY_STATUS Boss_Status(1000, 0, 0);

	Boss::Desc Boss_Desc(Boss_Status);
	/*desc 세팅*/
	Boss_obj->AddComponent<Boss>(&Boss_Desc);

	VIBufferRenderer::Desc Boss_Mesh;
	Boss_Mesh.mtrlName = L"boss";
	Boss_Mesh.meshName = L"box";
	Boss_obj->AddComponent<VIBufferRenderer>(&Boss_Mesh);

	SphereCollider::Desc Boss_col;
	Boss_col.radius = 100.f;
	Boss_col.collisionLayer = COLLISION_LAYER_ENEMY;
	Boss_obj->AddComponent<SphereCollider>(&Boss_col);

	++m_iEnemyCount;
}

void EnemyManager::Player_FovSpawnTest(bool _front, float _distance)
{
	if (_front) //앞에서 생성.
	{
		//킹론 : 플레이어 앞에서 생성되어야한다 -> 카메라랑 같은 방향
				//플레이어 시야각 안에 생성되어야 한다 -> 카메라 안에 있어야 함.
				// 즉 걍 카메라에 보이는 곳에 생성 되면 된다. 이말이야.
				// 그래서 카메라 화면 즉 뷰포트의 랜덤 좌표를 넘겨줘서 
				// 월드 좌표로 옮긴 뒤 해당 위치에 에ㅡ너미를 생성 되게 하는 것.

		//Vector3 vPlayerPos = PlayerInfoManager::GetInstance()->GetPlayer()->GetTransform()->position;
		
		Vector3 vResult;

		Vector2 vScreenSpace = { WINCX/2.f, WINCY/2.f };
		Vector3 vProjSpace;

		/* 뷰 포트(스크린 좌표) -> 투영 스페이스 좌표 */
		vProjSpace.x = vScreenSpace.x / (WINCX * 0.5f) - 1.f;
		vProjSpace.y = 1.f - (vScreenSpace.y / (WINCY * 0.5f));
		vProjSpace.z = 1.f;
		//->스크린 좌표를 반반 줬기때문에 원래 계획대로라면 투영 스페이스 좌표는 0,0,1 이 나와야함.

		/* 투영 스페이스 -> 뷰 스페이스 (투영 매트릭스 역행렬 곱해주기.) */
		Matrix matProj_Inverse;
		D3DXMatrixInverse(&matProj_Inverse, 0, &Core::GetInstance()->GetMainCamera()->GetProjMatrix());
		Vector3 vViewSpace;
		D3DXVec3TransformCoord(&vViewSpace, &vProjSpace, &matProj_Inverse);

		/* 뷰 스페이스 -> 월드 스페이스 (뷰 매트릭스 역행렬 곱해주기.) */
		Matrix matView_Inverse;
		D3DXMatrixInverse(&matView_Inverse, 0, &Core::GetInstance()->GetMainCamera()->GetViewMatrix());
		D3DXVec3TransformCoord(&vResult, &vViewSpace, &matView_Inverse);
		
		//근데 너무 멂.
		//vResult를 바로 Normalize 해벌이고 넘기면 그냥 0,0,0에 생성됨.
		//거리를 더 해주자.
		D3DXVec3Normalize(&vResult, &vResult);
		Vector3 temp = Core::GetInstance()->GetMainCamera()->GetTransform()->position + vResult * 100.f;
		//기준 위치 + (거리{생성된 방향벡터 * 거리});

		Enemy_Spawn(temp);

		//근데 Camera 기준으로 할꺼면 Camera-> GetCamToMouseWorldDirection 함수 있음 ㅎㅎ;
	}

	if (!_front) //뒤에서 생성.
	{
		Vector3 vPlayerPos = PlayerInfoManager::GetInstance()->GetPlayer()->GetTransform()->position;

		Vector3 vResult;

		Vector2 vScreenSpace = { WINCX / 2.f, WINCY / 2.f };
		Vector3 vProjSpace;

		/* 뷰 포트(스크린 좌표) -> 투영 스페이스 좌표 */
		vProjSpace.x = vScreenSpace.x / (WINCX * 0.5f) - 1.f;
		vProjSpace.y = 1.f - (vScreenSpace.y / (WINCY * 0.5f));
		vProjSpace.z = 1.f;
		//->스크린 좌표를 반반 줬기때문에 원래 계획대로라면 투영 스페이스 좌표는 0,0,1 이 나와야함.

		/* 투영 스페이스 -> 뷰 스페이스 (투영 매트릭스 역행렬 곱해주기.) */
		Matrix matProj_Inverse;
		D3DXMatrixInverse(&matProj_Inverse, 0, &Core::GetInstance()->GetMainCamera()->GetProjMatrix());
		Vector3 vViewSpace;
		D3DXVec3TransformCoord(&vViewSpace, &vProjSpace, &matProj_Inverse);

		/* 뷰 스페이스 -> 월드 스페이스 (뷰 매트릭스 역행렬 곱해주기.) */
		Matrix matView_Inverse;
		D3DXMatrixInverse(&matView_Inverse, 0, &Core::GetInstance()->GetMainCamera()->GetViewMatrix());
		D3DXVec3TransformCoord(&vResult, &vViewSpace, &matView_Inverse);

		//근데 너무 멂.
		//vResult를 바로 Normalize 해벌이고 넘기면 그냥 0,0,0에 생성됨.
		//거리를 더 해주자.
		D3DXVec3Normalize(&vResult, &(vResult));
		Vector3 temp = Core::GetInstance()->GetMainCamera()->GetTransform()->position + vResult * _distance * -1.f;
		//기준 위치 + (거리{생성된 방향벡터 * 거리});

		Enemy_Spawn(temp);
	}
}

Vector3 EnemyManager::Pos_ScreenToWorld(float _x, float _y, float _distance)
{
	Vector3 vResult;

	Vector2 vScreenSpace = { _x, _y };
	Vector3 vProjSpace;

	/* 뷰 포트(스크린 좌표) -> 투영 스페이스 좌표 */
	vProjSpace.x = vScreenSpace.x / (WINCX * 0.5f) - 1.f;
	vProjSpace.y = 1.f - (vScreenSpace.y / (WINCY * 0.5f));
	vProjSpace.z = 1.f;
	//->스크린 좌표를 반반 줬기때문에 원래 계획대로라면 투영 스페이스 좌표는 0,0,1 이 나와야함.

	/* 투영 스페이스 -> 뷰 스페이스 (투영 매트릭스 역행렬 곱해주기.) */
	Matrix matProj_Inverse;
	D3DXMatrixInverse(&matProj_Inverse, 0, &Core::GetInstance()->GetMainCamera()->GetProjMatrix());
	Vector3 vViewSpace;
	D3DXVec3TransformCoord(&vViewSpace, &vProjSpace, &matProj_Inverse);

	/* 뷰 스페이스 -> 월드 스페이스 (뷰 매트릭스 역행렬 곱해주기.) */
	Matrix matView_Inverse;
	D3DXMatrixInverse(&matView_Inverse, 0, &Core::GetInstance()->GetMainCamera()->GetViewMatrix());
	D3DXVec3TransformCoord(&vResult, &vViewSpace, &matView_Inverse);

	//근데 너무 멂.
	//vResult를 바로 Normalize 해벌이고 넘기면 그냥 0,0,0에 생성됨.
	//거리를 더 해주자.
	D3DXVec3Normalize(&vResult, &vResult);
	Vector3 temp = Core::GetInstance()->GetMainCamera()->GetTransform()->position + vResult * _distance;
	//기준 위치 + (거리{생성된 방향벡터 * 거리});

	return temp;
}

//Vector3 EnemyManager::Pos_ViewToWorld(float _x, float _y, float _Distance)
//{
//	/* x,y : 0 ~ 1.0 */
//	/* z : 100 ~ 1000 */
//	GameObject* mainCam = Core::GetInstance()->FindObjectByName(OBJECT_TAG_CAMERA, L"mainCamera");
//
//	Vector3 vResult;
//
//	/* 뷰 포트(스크린좌표) -> 투영 스페이스*/
//	Vector3 vScreenPos = { _x, _y, 0.f };
//	Vector3 vProjSpace; 
//	vProjSpace.x = vScreenPos.x / (WINCX * 0.5f) - 1.f;
//	vProjSpace.y = 1.f - vScreenPos.y / (WINCY * 0.5f);
//	vProjSpace.z = 1.f; //asdf
//
//
//	/* 투영스페이스 -> 뷰 스페이스*/
//	Matrix InverseProj;
//	D3DXMatrixInverse(&InverseProj, 0, &mainCam->GetComponent<Camera>()->GetProjMatrix());
//	D3DXVec3TransformCoord(&vResult, &vScreenPos, &InverseProj);
//	//두번째 인자를 계산 끝난 투영 스페이스를 줘야지 시! 팔새기야 ! 씨팔 이거때문에 두시간동안 지1랄 햇네
//
//	//카메라 기준으로 멀어지는걸 원한다면 여기서 쁘라스 해줘야함.
//	//vResult.z += _Distance;
//
//	/* 뷰스페이스 -> 월드 스페이스*/
//	Matrix InverseView;
//	D3DXMatrixInverse(&InverseView, 0, &mainCam->GetComponent<Camera>()->GetViewMatrix());
//	D3DXVec3TransformCoord(&vResult, &vResult, &InverseView);
//
//	//나온 결과 
//	//vResult.z += _Distance; //
//
//	//D3DXVec3Normalize(&vResult, &vResult);
//
//	return vResult;
//}


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

	Enemy_Spawn(vPos, Vector3(0.4f, 0.4f, 0.4f), ENEMY_STATE::IDLE, tStatus, tGun);

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
