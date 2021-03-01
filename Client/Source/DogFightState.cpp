#include "stdafx.h"
#include "..\Include\DogFightState.h"

#include "PlayerInfoManager.h"
#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerTopViewMove.h"

#include "FixToTarget.h"
#include "MouseOption.h"
#include "SmoothFollow.h"

#include "EnemyManager.h"
#include "Bullet_Manager.h"

#include "StageManager.h"
#include "UIWindowFactory.h"
#include "SceneChanger.h"
#include "PlayerBossStageMove.h"
#include "PlayerShooter.h"

// playerskill 시전자
#include "PlayerSkillActor.h"

//스킬 상태별 상태
#include "PlayerEscapeState.h"

DogFightState::DogFightState()
{

}


DogFightState::~DogFightState()
{
}

void DogFightState::Initialize()
{

}

void DogFightState::EnterState()
{
	INSTANTIATE(OBJECT_TAG_DEBUG, L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(50, 50, 0);
	INSTANTIATE()->AddComponent<Grid>();

	m_Player = INSTANTIATE(OBJECT_TAG_PLAYER, L"player");
	m_Player->SetScale(0.1f, 0.1f, 0.1f);

	m_Player->AddComponent<StateControl>();
	m_Player->GetComponent<StateControl>()->AddState<PlayerIdle>(L"playerIdle");
	m_Player->GetComponent<StateControl>()->AddState<PlayerMove>(L"playerMove");
	m_Player->GetComponent<StateControl>()->AddState<PlayerTopViewMove>(L"playerTopViewMove");
	m_Player->GetComponent<StateControl>()->AddState<PlayerBossStageMove>(L"playerBossMove");

	// 스킬관려된 스테이트 
	m_Player->GetComponent<StateControl>()->AddState<PlayerEscapeState>(L"playerEscape");

	m_Player->GetComponent<StateControl>()->InitState(L"playerIdle");

	MeshRenderer::Desc render;
	render.mtrlName = L"default"; //210223ȭ 12:50 ������ ������ �ȳ��ͼ� ���� �ٲ���
	render.meshName = L"flight";
	m_Player->AddComponent<MeshRenderer>(&render);
	m_Player->AddComponent<DrawGizmo>();
	m_Player->AddComponent<MouseOption>();
	m_Player->AddComponent<PlayerShooter>();
	m_Player->AddComponent<PlayerSkillActor>();
	SphereCollider::Desc player_col;
	player_col.radius = 1.f;
	m_Player->AddComponent<SphereCollider>();

	//m_Player->AddComponent<PlayerToTopView>();

	/*SceneChanger::Desc SceneChangerDescInfo;
	SceneChangerDescInfo.keyState = KEY_STATE_ENTER;
	SceneChangerDescInfo.sceneName = L"garage";
	auto SceneSelect = INSTANTIATE()->AddComponent<SceneChanger>(&SceneChangerDescInfo);
	*/

	auto infoManager = PlayerInfoManager::GetInstance();
	infoManager->SetTimeLimit(2000.f);
	infoManager->SetScore(123456.f);
	infoManager->SetPlayer(m_Player);

	auto smoothFollow = INSTANTIATE(0, L"SmoothFollow");
	SmoothFollow::Desc smoothFollowDesc;
	smoothFollowDesc.toTarget = m_Player;
	smoothFollow->AddComponent<SmoothFollow>(&smoothFollowDesc);

	m_MainCamera = Core::GetInstance()->FindFirstObject(OBJECT_TAG_CAMERA);

	m_Player->AddComponent<UIInteractor>();
	UIWindowFactory::StageWindow(m_Player);

	EnemyManager::GetInstance();

	ENEMY_STATUS tStatus(10, 20, 1);
	BULLET_STATUS tGun(0, 10, 50, 3, 180, 100, 0);
	BULLET_STATUS tMissile(10, 50, 5, 10, 30, 50, 0);
	EnemyManager::GetInstance()->Enemy_Spawn(Vector3(0.f, 0.f, 100.f), ENEMY_STATE::HOLD, tStatus, tGun, tMissile);

}


void DogFightState::UpdateState()
{
	++m_iFrame;

	if (m_iFrame > 0)
	{
		DEBUG_LOG(L"Current Combat State : ", L"Dog Fight State");


		int i = EnemyManager::GetInstance()->Get_EnemyCount();
		if (EnemyManager::GetInstance()->Get_EnemyCount() <= 0)
		{
			SceneToEvasion();
		}
		//지금 Enter에서 에너미 생성하면 newGameobjectList에 담기니까
		//gameobjectlist에는 Enemy가 없으니 바로 ScenetoEvasion으로 넘어옴.
		//그리고 나서 Player도 newGameObjectList에 있으니 못 찾아와서 팅김.


		if (m_bProduce)
		{
			Accelerate();
			Player_Faraway();

			Vector3 Dir = m_Player->GetTransform()->position - vPlayerOrigin;

			if (D3DXVec3Length(&Dir) >= 1100.f)
			{
				StageManager::GetInstance()->ToScene(L"Evasion");
			}
		}

		m_fDogFightTime += dTime;
	}
}

void DogFightState::ExitState()
{
	//DESTROY(Core::GetInstance()->FindObjectByName(0, L"SmoothFollow"));
	//monster들 다 없애기


	m_Player->GetComponent<StateControl>()->SetState(L"playerTopViewMove");
}

float DogFightState::Get_Time() const
{
	return m_fDogFightTime;
}

float DogFightState::Get_Score() const
{
	return m_fDogFightScore;
}

void DogFightState::Set_Score(float _score)
{
	m_fDogFightScore = _score;
}

void DogFightState::Add_Score(float _score)
{
	m_fDogFightScore += _score;
}



void DogFightState::SceneToEvasion()
{
	if (!m_bProduce)
	{
		Vector3 PosTemp = Core::GetInstance()->FindObjectByName(0, L"SmoothFollow")->GetTransform()->position;
		Quaternion RotTemp = Core::GetInstance()->FindObjectByName(0, L"SmoothFollow")->GetTransform()->rotation;


		DESTROY(Core::GetInstance()->FindObjectByName(0, L"SmoothFollow"));


		m_MainCamera->GetTransform()->position = PosTemp;
		m_MainCamera->GetTransform()->rotation = RotTemp;

		vPlayerOrigin = m_Player->GetTransform()->position;

		m_bProduce = true;
	}
}

void DogFightState::Player_Faraway()
{
	Vector3 forward = m_Player->GetTransform()->GetForward();

	m_Player->GetTransform()->position += forward * m_fSpd;
}

void DogFightState::Accelerate()
{
	//m_fSpd = Nalmak_Math::Lerp(m_fSpd, 5.f, dTime);
	//if u using lerp, object will be slower in lowFrame Computer.

	m_fSpd = dTime * 500.f;
	
}
