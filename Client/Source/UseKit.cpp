#include "stdafx.h"
#include "..\Include\UseKit.h"

UseKit::UseKit(Desc * _desc)
{
	m_delay = _desc->delay;
	m_kitAttack = _desc->kitAttack;
	m_kitSpeed = _desc->kitSpeed;
	m_eWeponType = _desc->wepontype;

}

UseKit::~UseKit()
{
}

void UseKit::Initialize()
{
}

void UseKit::Update()
{
}
