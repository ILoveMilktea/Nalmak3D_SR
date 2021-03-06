#include "stdafx.h"
#include "DeadTimer.h"


DeadTimer::DeadTimer(Desc * _desc)
{
	m_timer = _desc->timer;
}

DeadTimer::~DeadTimer()
{
}

void DeadTimer::Initialize()
{
}

void DeadTimer::Update()
{
	
	m_timer -= dTime;

	if (m_timer < 0)
		DESTROY(m_gameObject);

}
