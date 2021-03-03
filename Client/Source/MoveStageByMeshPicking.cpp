#include "stdafx.h"
#include "..\Include\MoveStageByMeshPicking.h"



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
			Core::GetInstance()->LoadScene(m_targetScene);
			return;
		}
	}
	
}
