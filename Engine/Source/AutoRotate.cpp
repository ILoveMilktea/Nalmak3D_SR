#include "..\Include\AutoRotate.h"
#include "Transform.h"


AutoRotate::AutoRotate(Desc* _desc)
{
	m_xAxisSpeed = _desc->xAxisSpeed;
	m_yAxisSpeed = _desc->yAxisSpeed;
	m_zAxisSpeed = _desc->zAxisSpeed;
}


AutoRotate::~AutoRotate()
{
}

void AutoRotate::Initialize()
{
}

void AutoRotate::Update()
{
	m_transform->RotateRollPitchYaw(m_xAxisSpeed * dTime, m_yAxisSpeed* dTime, m_zAxisSpeed* dTime);
}
