#include "stdafx.h"
#include "PrintInfo.h"



PrintInfo::PrintInfo(Desc * _desc)
{
}

PrintInfo::~PrintInfo()
{
}

void PrintInfo::Initialize()
{
}

void PrintInfo::Update()
{
	DEBUG_LOG(L"obj", m_transform);
	DEBUG_LOG(L"distance", Nalmak_Math::Distance(m_transform->position, Vector3(0,0,0)));
}
