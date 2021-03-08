#include "..\Include\LineCollider.h"

#include "MeshRenderer.h"
#include "VIBufferRenderer.h"


LineCollider::LineCollider(Desc * _desc)
{
	m_startPoint = _desc->startPoint;
	m_endPoint = _desc->endPoint;

	m_radius = _desc->radius;
	m_collisionLayer = _desc->collisionLayer;
	m_type = COLLIDER_TYPE_LINE;
}

LineCollider::~LineCollider()
{
}

void LineCollider::Initialize()
{
	Collider::Initialize();
}

void LineCollider::Update()
{
}

void LineCollider::Release()
{
}


void LineCollider::OnTriggerEnter(Collisions & _collision)
{
	DEBUG_LOG(L"Line Collider Enter", L"Line Collider Enter");
}

void LineCollider::OnTriggerStay(Collisions & _collision)
{
	DEBUG_LOG(L"Line Collider Stay", L"Line Collider Stay");
}

void LineCollider::OnTriggerExit(Collisions & _collision)
{
	DEBUG_LOG(L"Line Collider Exit", L"Line Collider Exit");
}
