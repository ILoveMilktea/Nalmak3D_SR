#include "stdafx.h"
#include "..\Include\UIManager.h"

UIManager* UIManager::m_Instance = nullptr;

UIManager::UIManager(Desc * _desc)
{
}

UIManager::~UIManager()
{
}

void UIManager::Initialize()
{
	m_isSkillRotate = false;
	m_curSkillIndex = 0;
}

void UIManager::Update()
{
	if (m_isSkillRotate)
	{
		SkillRotate();
	}
}


void UIManager::SkillRotateOn(int _weaponIndex)
{
	if (_weaponIndex == m_curSkillIndex)
		return;

	m_isSkillRotate = true;
	m_rotateTimer = 0.f;

	int weaponCount = 5; // change if weapon added

	if (_weaponIndex < m_curSkillIndex)
	{
		if (abs(_weaponIndex + weaponCount - m_curSkillIndex) < abs(_weaponIndex - m_curSkillIndex))
		{
			// normal
			m_targetSkillIndex = _weaponIndex + weaponCount;
			m_isInverseRotate = false;
		}
		else
		{
			// inverse
			m_targetSkillIndex = _weaponIndex;
			m_isInverseRotate = true;
		}
	}
	else
	{
		if (abs((_weaponIndex - weaponCount) - m_curSkillIndex) < abs(_weaponIndex - m_curSkillIndex))
		{
			// inverse
			m_targetSkillIndex = _weaponIndex - weaponCount;
			m_isInverseRotate = true;
		}
		else
		{
			// normal
			m_targetSkillIndex = _weaponIndex;
			m_isInverseRotate = false;
		}
	}
}

void UIManager::SkillRotate()
{
	// 0, 120, 240, 360, 480
	if (!SkillSingleRotate(m_isInverseRotate, abs(m_targetSkillIndex - m_curSkillIndex)))
	{
		// next skill load

		if (m_isInverseRotate)
		{
			--m_nextSkillIndex;
			if (m_nextSkillIndex < m_targetSkillIndex)
				m_isSkillRotate = false;
		}
		else
		{
			++m_nextSkillIndex;
			if (m_nextSkillIndex > m_targetSkillIndex)
				m_isSkillRotate = false;
		}

		m_rotateTimer = 0.f;
	}
}

bool UIManager::SkillSingleRotate(bool _inverse, int _speed)
{
	float angle;
	if (_inverse)
		angle = -120.f;
	else
		angle = 120.f;

	m_rotateTimer += dTime * _speed;
	if (1.f <= m_rotateTimer)
	{
		m_skillRotatePivot->GetTransform()->SetRotationZ(120.f * (m_nextSkillIndex - m_curSkillIndex));

		int count = m_skillRotatePivot->GetTransform()->GetChildCount();
		for (int i = 0; i < count; ++i)
		{
			Transform* child = m_skillRotatePivot->GetTransform()->GetChild(i);
			child->GetTransform()->SetRotationZ(-120.f * (m_nextSkillIndex - m_curSkillIndex));
		}

		return false;
	}

	m_skillRotatePivot->GetTransform()->RotateZ(angle * dTime * _speed);

	int count = m_skillRotatePivot->GetTransform()->GetChildCount();
	for (int i = 0; i < count; ++i)
	{
		Transform* child = m_skillRotatePivot->GetTransform()->GetChild(i);
		child->RotateZ(-angle * dTime * _speed);
	}

	return true;
}

UIManager * UIManager::GetInstance()
{
	if (m_Instance == nullptr)
	{
		auto Instance = INSTANTIATE();
		Instance->AddComponent<UIManager>();
		m_Instance = Instance->GetComponent<UIManager>();

		Instance->SetDontDestroy(true);
	}
	return m_Instance;
}

void UIManager::DeleteInstance()
{
	if (m_Instance)
	{
		DESTROY(m_Instance->GetGameObject());
	}
}