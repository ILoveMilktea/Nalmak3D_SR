#include "stdafx.h"
#include "StageSelectCamera_Stage2.h"
#include "verticalBillboard.h"
#include "MoveStageByMeshPicking.h"
#include "StageSelectCamera.h"

StageSelectCamera_Stage2::StageSelectCamera_Stage2()
{
}


StageSelectCamera_Stage2::~StageSelectCamera_Stage2()
{
}

void StageSelectCamera_Stage2::Initialize()
{
	m_stageCam = GetComponent<StageSelectCamera>();

	m_stage2_position = Vector3(50, 0, 30);

	{
		VIBufferRenderer::Desc render;
		render.mtrlName = L"StageSelect_Stage2UI";
		render.meshName = L"quadNoneNormal";
		auto obj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"stage2_icon")
			->AddComponent<VIBufferRenderer>(&render)
			->AddComponent<verticalBillboard>()
			->SetScale(6.f, 1.8f, 6.f)->SetPosition(m_stage2_position + Vector3(0,5,0));
	}
	{
		VIBufferRenderer::Desc render;
		render.mtrlName = L"StageSelect_PillarUI";
		render.meshName = L"quadNoneNormal";
		auto obj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"pillar")
			->AddComponent<VIBufferRenderer>(&render)
			->AddComponent<verticalBillboard>()
			->SetScale(0.3f, 4.1f, 0.3f)->SetPosition(m_stage2_position + Vector3(0, 2.05f, 0));
	}
	{
		VIBufferRenderer::Desc render;
		render.mtrlName = L"default_red";
		render.meshName = L"box";
		MoveStageByMeshPicking::Desc target;
		target.targetStage = L"stage2";
		INSTANTIATE()->AddComponent<VIBufferRenderer>(&render)->AddComponent<MeshPicking>()
			->AddComponent<MoveStageByMeshPicking>(&target)->SetPosition(m_stage2_position);
	}

	
}

void StageSelectCamera_Stage2::EnterState()
{
	m_stageCam->SetXMyAngle(20);
	m_stageCam->SetDistance(-25);
	m_stageCam->SetFollowSpeed(3);
	m_stageCam->SetRotateSpeed(3);
	m_stageCam->SetLookSpeed(3);
	m_stageCam->RotateYAxisAngle(3);
	m_stageCam->SetAxisTargetPos(m_stage2_position + Vector3(0, 10, 0));
}

void StageSelectCamera_Stage2::UpdateState()
{

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_A))
	{
		SetState(L"idle");
		return;
	}
}

void StageSelectCamera_Stage2::ExitState()
{

}
