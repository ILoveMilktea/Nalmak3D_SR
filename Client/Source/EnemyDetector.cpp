#include "stdafx.h"
#include "..\Include\EnemyDetector.h"

#include "PlayerInfoManager.h"
#include "EnemyManager.h"
#include "InputManager.h"

#define WINCENTER Vector2(WINCX*0.5f, WINCY*0.5f)

EnemyDetector::EnemyDetector(Desc * _desc)
{
	m_detectRect.left = LONG(-_desc->detectRectWidth * 0.5f);
	m_detectRect.right = LONG(_desc->detectRectWidth * 0.5f);
	m_detectRect.top = LONG(-_desc->detectRectHeight * 0.5f);
	m_detectRect.bottom = LONG(_desc->detectRectHeight * 0.5f);

	m_detectRange = _desc->detectRange;
	m_crosshair = _desc->crosshair;

	// tag ready
	m_nametagContainer.reserve(_desc->readyTag);
	for (size_t i = 0; i < m_nametagContainer.capacity(); ++i)
	{
		NameTag newNametag;

		// text
		{
			CanvasRenderer::Desc desc_cr;
			desc_cr.group = CANVAS_GROUP_STAGE1;

			Text::Desc desc;
			desc.width = 12;
			desc.height = 30;
			desc.text = L"";
			desc.color = D3DCOLOR_RGBA(255, 255, 255, 255);
			desc.option = DT_CENTER | DT_WORDBREAK | DT_VCENTER;

			auto text = INSTANTIATE(OBJECT_TAG_UI, L"Stage_NameTagText");
			text->AddComponent<CanvasRenderer>(&desc_cr);
			text->AddComponent<Text>(&desc);
			text->SetScale(110.f, 40.f);

			newNametag.text = text;
		}
		// tag
		{
			CanvasRenderer::Desc desc_cr;
			desc_cr.group = CANVAS_GROUP_STAGE1;

			SingleImage::Desc desc;
			desc.textureName = L"nametag";

			auto nametag =
				INSTANTIATE()->
				AddComponent<CanvasRenderer>(&desc_cr)->
				AddComponent<SingleImage>(&desc)->
				SetScale(128.f, 128.f, 0.f);

			//nametag->GetComponent<CanvasRenderer>()->SetColor(Vector4(1.f, 1.f, 1.f, 1.f));

			nametag->SetActive(false);

			newNametag.image = nametag;
		}

		newNametag.area = NONE;
		m_nametagContainer.emplace_back(newNametag);
	}
}

EnemyDetector::~EnemyDetector()
{
	m_nametagContainer.shrink_to_fit();
}

void EnemyDetector::Initialize()
{
	m_enemyManager = EnemyManager::GetInstance();
	m_mainCamera = Core::GetInstance()->GetMainCamera();
}

void EnemyDetector::Update()
{
	m_timer += TimeManager::GetInstance()->GetdeltaTime();

	UpdateTarget();
	SetNameTag();
}

void EnemyDetector::UpdateTarget()
{
	m_detectedTarget.clear();
	m_enemyPoint.clear();

	list<GameObject*> enemyList = m_enemyManager->Get_EnemyList();
	if (enemyList.size() > m_nametagContainer.size())
	{
		CreateMoreTag(m_nametagContainer.size() / 2);
	}

	int index = 0;
	float minDistance = WINCX;
	m_lockonTarget = nullptr;
	m_targetIndex = 0;

	if (!PlayerInfoManager::GetInstance()->GetPlayer())
		return;

	Transform* playerTr = PlayerInfoManager::GetInstance()->GetPlayer()->GetTransform();
	for (auto& enemy : enemyList)
	{

		Camera* mainCam = Core::GetInstance()->GetMainCamera();
		auto renderer = enemy->GetComponent<MeshRenderer>();

		if(!renderer)
			continue;

		if (!mainCam->IsInFrustumCulling(renderer))
			continue;		// 현재 비워놓은....

		Vector3 playerToEnemy = playerTr->position - enemy->GetTransform()->position;
		float dist = D3DXVec3Length(&playerToEnemy);
		if (dist > m_detectRange)
		{
			continue;
		}
		
		Vector2 screenPos = m_mainCamera->WorldToScreenPos(enemy->GetTransform()->position);
		
		if (CheckArea_LT(screenPos))
		{
			m_nametagContainer[index].area = LEFT_TOP;
		}
		else if (CheckArea_LB(screenPos))
		{
			m_nametagContainer[index].area = LEFT_BOTTOM;
		}
		else if (CheckArea_RT(screenPos))
		{
			m_nametagContainer[index].area = RIGHT_TOP;
		}
		else if (CheckArea_RB(screenPos))
		{
			m_nametagContainer[index].area = RIGHT_BOTTOM;
		}
		else
		{
			continue;
		}

		m_nametagContainer[index].text->GetComponent<Text>()->SetText(enemy->GetName());
		screenPos = Vector2(screenPos.x + WINCENTER.x, WINCENTER.y - screenPos.y);
		m_enemyPoint.emplace_back(screenPos);
		// target regist
		m_detectedTarget.emplace_back(enemy);

		Vector2 crosshairPos = Vector2(m_crosshair->GetTransform()->position.x, m_crosshair->GetTransform()->position.y);
		Vector2 enemyToCrosshair = screenPos - crosshairPos;
		float len = D3DXVec2Length(&enemyToCrosshair);
		if (len < minDistance)
		{
			// closest target
			m_lockonTarget = enemy;
			m_targetIndex = index;
		}

		++index;
	}
}

void EnemyDetector::SetNameTag()
{
	int index = 0;

	for (size_t i = 0; i < m_nametagContainer.size(); ++i)
	{
		if (!m_nametagContainer[i].image->IsActive())
			break;

		m_nametagContainer[i].image->SetActive(false);
		m_nametagContainer[i].text->SetActive(false);
	}

	for (auto& point : m_enemyPoint)
	{
		// area.....?
		// z값으로 판단해서 뒤집는거 생각해보자.

		m_nametagContainer[index].image->GetTransform()->position = Vector3(point.x, point.y, 0.f);
		m_nametagContainer[index].image->SetActive(true);

		if (index == m_targetIndex)
		{
			m_nametagContainer[index].image->GetComponent<CanvasRenderer>()->SetColor(Vector4(1.f, 0.f, 0.f, 1.f));
		}
		else
		{
			m_nametagContainer[index].image->GetComponent<CanvasRenderer>()->SetColor(Vector4(1.f, 1.f, 1.f, 1.f));
		}

		m_nametagContainer[index].text->GetTransform()->position =
			Vector3(point.x + m_nametagContainer[index].image->GetTransform()->scale.x * 0.5f + m_nametagContainer[index].text->GetTransform()->scale.x * 0.5f
				, point.y - 48.f
				, 0.f);
		m_nametagContainer[index].text->SetActive(true);


		++index;
	}


}

bool EnemyDetector::CheckArea_LT(const Vector2 & _pos)
{
	if (_pos.x > m_detectRect.left &&
		_pos.x <= 0 &&
		_pos.y > m_detectRect.top &&
		_pos.y <= 0)
		return true;

	return false;
}

bool EnemyDetector::CheckArea_LB(const Vector2 & _pos)
{
	if (_pos.x > m_detectRect.left &&
		_pos.x <= 0 &&
		_pos.y >= 0 &&
		_pos.y < m_detectRect.bottom)
		return true;

	return false;
}

bool EnemyDetector::CheckArea_RT(const Vector2 & _pos)
{
	if (_pos.x >= 0 &&
		_pos.x < m_detectRect.right &&
		_pos.y > m_detectRect.top &&
		_pos.y <= 0)
		return true;

	return false;
}

bool EnemyDetector::CheckArea_RB(const Vector2 & _pos)
{
	if (_pos.x >= 0 &&
		_pos.x < m_detectRect.right &&
		_pos.y >= 0 &&
		_pos.y < m_detectRect.bottom)
		return true;

	return false;
}

void EnemyDetector::CreateMoreTag(size_t _count)
{
	// icon ready
	m_nametagContainer.resize(m_nametagContainer.size() + _count);
	for (size_t i = 0; i < _count; ++i)
	{
		NameTag newNametag;

		// text
		{
			CanvasRenderer::Desc desc_cr;
			desc_cr.group = CANVAS_GROUP_STAGE1;

			Text::Desc desc;
			desc.width = 12;
			desc.height = 30;
			desc.text = L"";
			desc.color = D3DCOLOR_RGBA(255, 255, 255, 255);
			desc.option = DT_CENTER | DT_WORDBREAK | DT_VCENTER;

			auto text = INSTANTIATE(OBJECT_TAG_UI, L"Stage_NameTagText");
			text->AddComponent<CanvasRenderer>(&desc_cr);
			text->AddComponent<Text>(&desc);
			text->SetScale(110.f, 40.f);

			newNametag.text = text;
		}
		// tag
		{
			CanvasRenderer::Desc desc_cr;
			desc_cr.group = CANVAS_GROUP_STAGE1;

			SingleImage::Desc desc;
			desc.textureName = L"nametag";

			auto nametag =
				INSTANTIATE()->
				AddComponent<CanvasRenderer>(&desc_cr)->
				AddComponent<SingleImage>(&desc)->
				SetScale(128.f, 128.f, 0.f);

			//nametag->GetComponent<CanvasRenderer>()->SetColor(Vector4(1.f, 1.f, 1.f, 1.f));

			nametag->SetActive(false);

			newNametag.image = nametag;
		}

		newNametag.area = NONE;
		m_nametagContainer.emplace_back(newNametag);
	}
}
