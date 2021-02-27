#include "stdafx.h"
#include "Rader.h"

#include "PlayerInfoManager.h"

Rader::Rader(Desc * _desc)
{
	m_findRange =_desc->findRange;

	// icon ready
	m_IconContainer.reserve(_desc->readyflight);
	for (size_t i = 0; i < m_IconContainer.capacity(); ++i)
	{
		SingleImage::Desc desc;
		desc.textureName = L"flighticon";

		auto icon =
			INSTANTIATE()->
			AddComponent<CanvasRenderer>()->
			AddComponent<SingleImage>(&desc)->
			SetScale(8.f, 16.f, 0.f);

		icon->SetActive(false);
		m_IconContainer.emplace_back(icon);
	}
}

void Rader::Initialize()
{
	m_playerInfoManager = PlayerInfoManager::GetInstance();

	// circle ready
	SingleImage::Desc desc;
	desc.textureName = L"circle";
	m_circleBackground =
		INSTANTIATE()->
		AddComponent<CanvasRenderer>()->
		AddComponent<SingleImage>(&desc)->
		SetPosition(0.f, 0.f, 0.f)->
		SetScale(400.f, 400.f, 0.f);
	m_circleBackground->SetParents(m_transform);


	SingleImage::Desc playerdesc;
	playerdesc.textureName = L"flighticon";
	m_playerIcon =
		INSTANTIATE()->
		AddComponent<CanvasRenderer>()->
		AddComponent<SingleImage>(&playerdesc)->
		SetPosition(0.f, 0.f, 0.f)->
		SetScale(8.f, 16.f, 0.f);

	m_playerIcon->SetParents(m_transform);
}

void Rader::Update()
{
	if (!m_playerInfoManager->GetPlayer()->GetTransform())
		return;

	// 한바퀴 돌면 업뎃 하면 될듯
	m_timer += TimeManager::GetInstance()->GetdeltaTime();
	if (1.f <= m_timer)
	{
		UpdateTarget();
		SetFlightPoint();

		m_IconContainer[0]->GetComponent<CanvasRenderer>()->SetColor(Vector4(0.8f, 0.f, 0.f, 1.f));
		m_IconContainer[1]->GetComponent<CanvasRenderer>()->SetColor(Vector4(0.8f, 0.8f, 0.f, 1.f));
		m_IconContainer[2]->GetComponent<CanvasRenderer>()->SetColor(Vector4(0.f, 0.8f, 0.f, 1.f));

		m_timer = 0.f;
	}
}

void Rader::UpdateTarget()
{
	m_iconPoint.clear();

	for (auto& enemy : m_enemy)
	{
		Transform* tr = m_playerInfoManager->GetPlayer()->GetTransform();
		Vector2 point = { enemy->position.x, enemy->position.z };
		Vector2 dir = point - Vector2(tr->position.x, tr->position.z);
		float length = D3DXVec2Length(&dir);

		if (length < m_findRange)
		{
			dir = Vector2(m_playerIcon->GetTransform()->position.x + dir.x, m_playerIcon->GetTransform()->position.y - dir.y);
			m_iconPoint.emplace_back(dir);
		}
			
	}
}

void Rader::SetFlightPoint()
{
	int index = 0;
	for (auto& point : m_iconPoint)
	{
		m_IconContainer[index]->GetTransform()->position = Vector3(point.x, point.y, 0.f);
		m_IconContainer[index]->SetActive(true);
		++index;
	}

	for (size_t i = m_iconPoint.size(); i < m_IconContainer.size(); ++i)
	{
		if (!m_IconContainer[i]->IsActive())
			m_IconContainer[i]->SetActive(false);
		else
			break;
	}

}
