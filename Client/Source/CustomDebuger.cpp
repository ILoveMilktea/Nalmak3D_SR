#include "stdafx.h"
#include "..\Include\CustomDebuger.h"

CustomDebuger::CustomDebuger(Desc * _desc)
{
}

void CustomDebuger::Initialize()
{
}

void CustomDebuger::Update()
{
	DEBUG_LOG(m_gameObject->GetName(), GetTransform()->position);
}
