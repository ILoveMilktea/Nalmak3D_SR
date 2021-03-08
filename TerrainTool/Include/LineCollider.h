#pragma once
#include "Collider.h"
class NALMAK_DLL LineCollider :
	public Collider
{
	friend class CollisionManager;
public:
	struct Desc
	{
		Vector3 startPoint = Vector3(0.f, 0.f, 0.f);
		Vector3 endPoint = Vector3(0.f, 0.f, 10.f);

		float radius = 0.5f;
		
		_COLLISION_LAYER collisionLayer = 0;
	};
public:
	LineCollider(Desc* _desc);
	~LineCollider();
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

public:
	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;


	void SetStartPoint(Vector3 _point) { m_startPoint = _point; }
	void SetEndPoint(Vector3 _point) { m_endPoint = _point; }
	void SetRadius(float _radius) { m_radius = _radius; }

	const Vector3& GetStartPoint() { return m_startPoint; }
	const Vector3& GetEndPoint() { return m_endPoint; }
	float GetRadius() { return m_radius; }
	
private:
	Vector3 m_startPoint;
	Vector3 m_endPoint;

	float m_radius; // width
};

