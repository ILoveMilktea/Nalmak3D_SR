#include "stdafx.h"
#include "..\Include\MoveStageByMeshPicking.h"
#include "GameManager.h"



MoveStageByMeshPicking::MoveStageByMeshPicking(Desc * _desc)
{
	m_targetScene = _desc->targetStage;
}

MoveStageByMeshPicking::~MoveStageByMeshPicking()
{
}

void MoveStageByMeshPicking::Initialize()
{
	m_meshPicking = GetComponent<MeshPicking>();
}

void MoveStageByMeshPicking::Update()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_LEFT_MOUSE))
	{
		if (m_meshPicking->IsMousePicking())
		{
			Core::GetInstance()->LoadScene(L"garage");
			GameManager::GetInstance()->Set_NestStage(m_targetScene);
			return;
		}
	}
	
}
