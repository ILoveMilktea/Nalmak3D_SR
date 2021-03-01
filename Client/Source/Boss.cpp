#include "stdafx.h"
#include "..\Include\Boss.h"

Boss::Boss(Desc * _desc)
{
}

Boss::~Boss()
{
}

void Boss::Initialize()
{
}

void Boss::Update()
{

	DEBUG_LOG(L"Boss Pos", m_transform->position);
}
