#include "..\Include\Particle.h"
#include "Transform.h"
#include "TimeManager.h"

Particle::Particle()
{
}

Particle::~Particle()
{
}
void Particle::Reset()
{
	totalAcceleration = Vector3(0, 0, 0);
	m_isAlive = true;
	m_currentLifeTime = 0;
	parents = nullptr;
}
void Particle::Update(INPUT_LAYOUT_PARTICLE* _info)
{
	float delta = dTime;
	float lifeTimeRatio = m_currentLifeTime / lifeTime;
	float speed = Nalmak_Math::Lerp(startSpeed, endSpeed, lifeTimeRatio);
	Vector3 finalVelocity = direction * speed;
	totalAcceleration += (acceleration - Vector3(0, 9.8f, 0)* gravityScale) * delta;
	finalVelocity += totalAcceleration;
	position += finalVelocity * delta;

	angle += angluarVelocity * delta;


	_info->color = Nalmak_Math::Lerp(startColor, endColor, lifeTimeRatio);
	float curScale = Nalmak_Math::Lerp(startScale, endScale, lifeTimeRatio);

	Matrix trans, rot, scale;
	D3DXMatrixTranslation(&trans, position.x, position.y, position.z);
	D3DXMatrixRotationZ(&rot, angle);
	D3DXMatrixScaling(&scale, curScale, curScale, curScale);

	if (parents)
		_info->worldMatrix = scale * rot * trans * parents->GetWorldMatrix();
	else
		_info->worldMatrix = scale * rot * trans;

	m_currentLifeTime += delta;

	if (m_currentLifeTime > lifeTime)
	{
		m_isAlive = false;
		return;
	}

}
