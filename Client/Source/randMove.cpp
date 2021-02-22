#include "stdafx.h"
#include "..\Include\randMove.h"


randMove::randMove(Desc * _desc)
{
	m_fSpd = _desc->fSpd;
}

randMove::~randMove()
{
}

void randMove::Initialize()
{
}

void randMove::Update()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F4))
	{	
		int x = rand() % 201 - 100;
		int y = rand() % 201 - 100;
		int z = rand() % 201 - 100;

		Vector3 temp;
		temp = { (float)x,(float)y,(float)z };

		m_transform->SetPosition(temp);
	}

	DEBUG_LOG(L"Target Pos", m_transform->position);
}
