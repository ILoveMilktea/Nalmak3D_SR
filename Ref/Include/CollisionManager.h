#pragma once
#ifndef __COLLISIONMANAGER_H__
#define __COLLISIONMANAGER_H__

#include "Nalmak_Include.h"

class Collider;

class CollisionManager
{
	DECLARE_SINGLETON(CollisionManager)
private:
	CollisionManager();
	~CollisionManager();
private:
	void Release();
public:
	void Initialize(int _collisionLayerCount);
	void Update();
public:
	void ActiveCollsionLayer(int _layer1, int _layer2);
	void AddCollidier(Collider* _col);
	void DeleteCollider(Collider* _col);
	void Process(Collider* _colA, Collider* _colB);
private:
	vector<Collider*>* m_colliderList;
private:
	void SphereToSphere(Collider* _colA, Collider* _colB);
	void LineToSphere(Collider* _colLine, Collider* _colSphere);
private:
	vector<UINT> m_collisionLayer;
	int m_collisionLayerCount;
	bool* m_activeLayers;
};

#endif // !__COLLISIONMANAGER_H__
