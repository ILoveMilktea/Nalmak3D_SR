#include "..\Include\CollisionManager.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "Transform.h"

IMPLEMENT_SINGLETON(CollisionManager)

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
	Release();
}

void CollisionManager::Release()
{
	SAFE_DELETE_ARR(m_activeLayers);
	delete[] m_colliderList;
}

void CollisionManager::Initialize(int _collisionLayerCount)
{
	m_collisionLayerCount = _collisionLayerCount;
	m_colliderList = new vector<Collider*>[_collisionLayerCount];
	m_activeLayers = new bool[_collisionLayerCount];
}

void CollisionManager::Update()
{
	Collider* colA = nullptr;
	Collider* colB = nullptr;

	for (int i = 0; i < m_collisionLayerCount; ++i)
	{
		m_activeLayers[i] = false;
	}

	for (int i = 0; i < m_collisionLayerCount; ++i)
	{
		for (int j = i; j < m_collisionLayerCount; ++j)
		{
			for (auto& collisionLayer : m_collisionLayer)
			{
				if ((UINT)pow(2, i + 1) + (UINT)pow(2, j + 1) == collisionLayer)
				{
					for (auto iterA = m_colliderList[i].begin(); iterA != m_colliderList[i].end(); ++iterA)
					{
						colA = *iterA;
						for (auto iterB = m_colliderList[j].begin(); iterB != m_colliderList[j].end(); ++iterB)
						{
							colB = *iterB;

							if (colA == colB)
								continue;

							Process(colA, colB);
						}
					}
					m_activeLayers[i] = true;
					m_activeLayers[j] = true;
					break;
				}
			}
		}
	}
	for (int i = 0; i < m_collisionLayerCount; ++i)
	{
		if (m_activeLayers[i])
		{
			for (auto& col : m_colliderList[i])
				col->GetGameObject()->CollisionUpdate();
		}

		m_colliderList[i].clear();
	}
}

void CollisionManager::AddCollidier(Collider * _col)
{
	assert("Collider is nullptr!" && _col);
	m_colliderList[_col->m_collisionLayer].emplace_back(_col);
}

void CollisionManager::DeleteCollider(Collider * _col)
{
	int layer = _col->m_collisionLayer;
	if (m_colliderList[layer].size() == 0)
		return;

	for (auto iter = m_colliderList[layer].begin(); iter != m_colliderList[layer].end(); ++iter)
	{
		if ((*iter) == _col)
		{
			m_colliderList[_col->m_collisionLayer].erase(iter);
			return;
		}
	}
}

void CollisionManager::Process(Collider * _colA, Collider * _colB)
{
	if (_colA->m_type == COLLIDER_TYPE_SPHERE || _colB->m_type == COLLIDER_TYPE_SPHERE)
		SphereToSphere(_colA, _colB);
}

void CollisionManager::SphereToSphere(Collider * _colA, Collider * _colB)
{
	SphereCollider* colA = (SphereCollider*)_colA;
	SphereCollider* colB = (SphereCollider*)_colB;

	Vector3 positionA = colA->GetTransform()->GetWorldPosition() + colA->GetCenter();
	Vector3 positionB = colB->GetTransform()->GetWorldPosition() + colA->GetCenter();

	if (Vector::DistanceSq(positionA, positionB) < pow(colA->m_radius + colB->m_radius ,2))
	{
		Vector3 hitPoint;

		colA->GetGameObject()->CollisionNotify(Collision(colA->m_gameObject, hitPoint));
		colB->GetGameObject()->CollisionNotify(Collision(colB->m_gameObject, hitPoint));
	}
	
}

void CollisionManager::ActiveCollsionLayer(int _layer1, int _layer2)
{
	m_collisionLayer.emplace_back((UINT)pow(2, (_layer1 + 1)) + (UINT)pow(2, (_layer2 + 1)));
}
