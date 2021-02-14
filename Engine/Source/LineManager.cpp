#include "..\Include\LineManager.h"

#include "GameObject.h"
#include "MeshRenderer.h"
#include "Transform.h"

IMPLEMENT_SINGLETON(LineManager)

LineManager::LineManager()
{
}


LineManager::~LineManager()
{
	Release();
}

void LineManager::Initialize()
{
	m_lineCount = 0;

	MeshRenderer::Desc desc;
	desc.meshName = L"line";
	desc.mtrlName = L"greenLine";
	desc.layer = 0;
	m_isLineRender = true;

	for (UINT i = 0; i < m_maxLineCount; ++i)
	{
		auto line = GameObject::Instantiate(0, L"line")->AddComponent<MeshRenderer>(&desc);
		line->SetDontDestroy(true);
		line->SetActive(false);
		line->InitializeComponents();
		m_dynamicLine.emplace_back(line);
	}

	m_debugMaterial[0] = ResourceManager::GetInstance()->GetResource<Material>(L"redLine");
	m_debugMaterial[1] = ResourceManager::GetInstance()->GetResource<Material>(L"greenLine");
	m_debugMaterial[2] = ResourceManager::GetInstance()->GetResource<Material>(L"blueLine");

}

void LineManager::DrawLine(const Vector3 & _vec1, const Vector3 & _vec2, DEBUG_COLOR _color)
{
	if (!m_isLineRender)
		return;

	if (m_lineCount >= m_maxLineCount)
		return;

	auto line = m_dynamicLine[m_lineCount];
	line->GetComponent<MeshRenderer>()->SetMaterial(m_debugMaterial[_color]);
	line->SetActive(true);
	line->GetTransform()->scale = Vector3(Vector::Distance(_vec1, _vec2), Vector::Distance(_vec1, _vec2), Vector::Distance(_vec1, _vec2));
	Vector3 norLine = Vector::Normalize(_vec2 - _vec1);
	Vector3 axis = Vector::Cross(Vector3(1, 0, 0), norLine);
	if (axis != Vector3(0, 0, 0))
		line->GetTransform()->rotation =  line->GetTransform()->RotateAxis(axis, acos(Vector::Dot(Vector3(1, 0, 0), norLine)));
	line->GetTransform()->position = (_vec1 + _vec2) * 0.5f;


	++m_lineCount;
}

void LineManager::Release()
{
	m_dynamicLine.clear();
}

void LineManager::DeleteLines()
{
	for (UINT i = 0; i < m_lineCount; ++i)
		m_dynamicLine[i]->SetActive(false);
	m_lineCount = 0;
}

void LineManager::Toggle()
{
	m_isLineRender ^= true;
}
