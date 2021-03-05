#include "stdafx.h"
#include "Rader.h"

#include "PlayerInfoManager.h"
#include "EnemyManager.h"

Rader::Rader(Desc * _desc)
{
	m_findRange =_desc->findRange;

	// icon ready
	m_IconContainer.reserve(_desc->readyIcon);
	for (size_t i = 0; i < m_IconContainer.capacity(); ++i)
	{
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = CANVAS_GROUP_STAGE1;
			
		SingleImage::Desc desc;
		desc.textureName = L"enemyicon";

		auto icon =
			INSTANTIATE()->
			AddComponent<CanvasRenderer>(&desc_cr)->
			AddComponent<SingleImage>(&desc)->
			SetScale(8.f, 8.f, 0.f);

		//icon->GetComponent<CanvasRenderer>()->SetColor(Vector4(1.f, 1.f, 1.f, 1.f));
		icon->SetActive(false);
		m_IconContainer.emplace_back(icon);
	}
}

Rader::~Rader()
{
	m_IconContainer.shrink_to_fit();
}

void Rader::Initialize()
{
	m_playerInfoManager = PlayerInfoManager::GetInstance();
	m_enemyManager = EnemyManager::GetInstance();

	// circle
	{
		SingleImage::Desc desc;
		desc.textureName = L"raderBox";
		m_circleBackground =
			INSTANTIATE()->
			AddComponent<CanvasRenderer>()->
			AddComponent<SingleImage>(&desc)->
			SetPosition(0.f, 0.f, 0.f)->
			SetScale(300.f, 300.f, 0.f);
		m_circleBackground->SetParents(m_transform);
	}

	// player icon
	{
		SingleImage::Desc playerdesc;
		playerdesc.textureName = L"flighticon";
		m_playerIcon =
			INSTANTIATE()->
			AddComponent<CanvasRenderer>()->
			AddComponent<SingleImage>(&playerdesc)->
			SetPosition(0.f, 0.f, 0.f)->
			SetScale(8.f, 16.f, 0.f);

		m_playerIcon->SetParents(m_transform);

		m_pivot = INSTANTIATE()->
			AddComponent<CanvasRenderer>()->
			SetPosition(0.f, 0.f, 0.f);

		m_pivot->GetTransform()->SetParents(m_transform);
		for (size_t i = 0; i < m_IconContainer.capacity(); ++i)
		{
			m_IconContainer[i]->SetParents(m_pivot);
		}
	}

}

void Rader::Update()
{
	if (!m_playerInfoManager->GetPlayer())
		return;

	m_timer += TimeManager::GetInstance()->GetdeltaTime();
	if (0.01f <= m_timer)
	{
		UpdateTarget();
		SetFlightPoint();
		
		m_timer = 0.f;
	}
}

void Rader::UpdateTarget()
{
	m_iconPoint.clear();

	list<GameObject*> enemyList = m_enemyManager->Get_EnemyList();
	if (enemyList.size() > m_IconContainer.size())
	{
		CreateMoreIcon(m_IconContainer.size() / 2);
	}

	int index = 0;
	for (auto& enemy : enemyList)
	{
		Transform* playerTr = m_playerInfoManager->GetPlayer()->GetTransform();
		Transform* enemyTr = enemy->GetTransform();

		Vector2 point = { enemyTr->position.x, enemyTr->position.z };
		Vector2 dir = point - Vector2(playerTr->position.x, playerTr->position.z);
		float length = D3DXVec2Length(&dir);

		if (length < m_findRange)
		{
			dir = Vector2(m_playerIcon->GetTransform()->position.x + dir.x, m_playerIcon->GetTransform()->position.y - dir.y);
			m_iconPoint.emplace_back(dir);
		}

		++index;
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


	Transform* playerTr = m_playerInfoManager->GetPlayer()->GetTransform();
	Vector3 forward = playerTr->GetForward();
	Vector2 rotateDir = Vector2(forward.x, forward.z);
	D3DXVec2Normalize(&rotateDir,&rotateDir);
	Vector2 up = Vector2(0.f, 1.f);
	float cosValue = D3DXVec2Dot(&rotateDir, &up);
	//m_pivot->GetTransform()->SetRotation(0.f, 0.f, 0.f);
	if(forward.x < 0.f)
		m_pivot->GetTransform()->SetRotationZ(Rad2Deg * acosf(cosValue));
	else if (forward.x >= 0.f)
		m_pivot->GetTransform()->SetRotationZ(Rad2Deg * -acosf(cosValue));

	//m_pivot->GetTransform()->RotateAxis(Vector3(0.f, 0.f, 1.f), Rad2Deg * cosf(cosValue));
}

void Rader::CreateMoreIcon(size_t _count)
{
	// icon ready
	m_IconContainer.resize(m_IconContainer.size() + _count);
	for (size_t i = 0; i < _count; ++i)
	{
		SingleImage::Desc desc;
		desc.textureName = L"flighticon";

		auto icon =
			INSTANTIATE()->
			AddComponent<CanvasRenderer>()->
			AddComponent<SingleImage>(&desc)->
			SetScale(8.f, 16.f, 0.f);

		icon->GetComponent<CanvasRenderer>()->SetColor(Vector4(0.f, 0.8f, 0.f, 1.f));
		icon->SetActive(false);
		m_IconContainer.emplace_back(icon);
	}
}
