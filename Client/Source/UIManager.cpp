#include "stdafx.h"
#include "..\Include\UIManager.h"

#include "UI_Alarm.h"

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

	// ----- alarm ----
	m_messenger.push_back(nullptr);
	m_messenger.push_back(nullptr);
	m_messenger.push_back(nullptr);
	m_messenger.push_back(nullptr);
	m_alarmTimer = 0.f;
}

void UIManager::Update()
{
	if (m_isSkillRotate)
	{
		SkillRotate();
	}

	m_alarmTimer += dTime;
	if (1.5f < m_alarmTimer)
	{
		UpdateAlarm();
		m_alarmTimer = 0.f;
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
		if (abs(_weaponIndex + weaponCount - m_curSkillIndex) < abs(m_curSkillIndex - _weaponIndex))
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
		if (abs(m_curSkillIndex - (_weaponIndex - weaponCount)) < abs(_weaponIndex - m_curSkillIndex))
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

		size_t count = m_skillRotatePivot->GetTransform()->GetChildCount();
		for (int i = 0; i < count; ++i)
		{
			Transform* child = m_skillRotatePivot->GetTransform()->GetChild(i);
			child->GetTransform()->SetRotationZ(-120.f * (m_nextSkillIndex - m_curSkillIndex));
		}

		return false;
	}

	m_skillRotatePivot->GetTransform()->RotateZ(angle * dTime * _speed );

	size_t count = m_skillRotatePivot->GetTransform()->GetChildCount();
	for (int i = 0; i < count; ++i)
	{
		Transform* child = m_skillRotatePivot->GetTransform()->GetChild(i);
		child->RotateZ(-angle * dTime * _speed);
	}

	return true;
}

void UIManager::AddAlarm(UI_Alarm* _alarm)
{
	m_alarmQueue.push(_alarm);
}

void UIManager::UpdateAlarm()
{
	//up anim
	RemoveAlarm();

	if (!m_alarmQueue.empty())
	{
		if (!m_alarmQueue.front()->IsPlay())
		{
			m_alarmQueue.front()->AlarmOffAnim();
			m_trashbag.push(m_alarmQueue.front());
			m_alarmQueue.pop();
		}
	}
}

void UIManager::RemoveAlarm()
{
	while (!m_trashbag.empty())
	{
		GameObject* trash = m_trashbag.front()->GetGameObject();

		m_trashbag.front()->Remove();
		DESTROY(trash);
		trash = nullptr;
		m_trashbag.pop();
	}
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

void UIManager::BuyItem()
{
}

void UIManager::BuyPopupOn()
{
	// weapon img
	// weapon single dpm
	// weapon multi dpm
	// money
	//buy button func
	m_buyPopup->SetActive(true);
}

void UIManager::BuyPopupOff()
{
	m_buyPopup->SetActive(false);
}
