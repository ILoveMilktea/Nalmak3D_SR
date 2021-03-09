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
void Particle::Update(INPUT_LAYOUT_PARTICLE * _info, const Matrix & _billboard, float _spriteCountRatio, PARTICLE_BILLBOARD_TYPE _type)
{
	float delta = dTime;
	float lifeTimeRatio = m_currentLifeTime / lifeTime;
	float speed = Nalmak_Math::Lerp(startSpeed, endSpeed, lifeTimeRatio);
	Vector3 finalVelocity = direction * speed;
	totalAcceleration += (acceleration - Vector3(0, 9.8f, 0)* gravityScale) * delta;
	finalVelocity += totalAcceleration;
	position += finalVelocity * delta;
	angle += angluarVelocity * delta;

	
	_info->spriteX_spriteY_index.z = float(int(lifeTimeRatio / _spriteCountRatio));

	_info->color = Nalmak_Math::Lerp(startColor, endColor, lifeTimeRatio);
	float curScale = Nalmak_Math::Lerp(startScale, endScale, lifeTimeRatio);

	Matrix trans, rot, scale;
	D3DXMatrixTranslation(&trans, position.x, position.y, position.z);

	if (_type == PARTICLE_BILLBOARD_TYPE_STERTCHED)
	{
		D3DXMatrixScaling(&scale, curScale, curScale* StretchedScale, curScale);

		Matrix stretch;
		Matrix billboard;
		Vector3 dir = Nalmak_Math::Normalize(finalVelocity);
		{
			float angle = Nalmak_Math::Dot(Vector3(0, 1, 0), dir);

			Vector3 axis;
			D3DXVec3Cross(&axis, &Vector3(0, 1, 0), &dir);
			D3DXMatrixRotationAxis(&stretch, &axis, acos(angle));
		}
		rot = stretch;

		if (parents)
			_info->worldMatrix = _billboard * scale * rot * trans * parents->GetWorldMatrix();
		else
			_info->worldMatrix = _billboard * scale * rot * trans;
	}
	else if (_type == PARTICLE_BILLBOARD_TYPE_HORIZONTAL)
	{
		Matrix rotX, rotY;
		D3DXMatrixScaling(&scale, curScale, curScale, curScale);
		D3DXMatrixRotationAxis(&rotX, &Vector3(1, 0, 0), Deg2Rad * 90);// 0.157079632f); // 90�� 
		D3DXMatrixRotationAxis(&rotY, &Vector3(0, 1, 0), Deg2Rad * angle); // 90�� 
		rot = rotX * rotY;
		if (parents)
			_info->worldMatrix =  scale * rot * trans * parents->GetWorldMatrix();
		else
			_info->worldMatrix =  scale * rot * trans;
	}
	else
	{
		D3DXMatrixRotationAxis(&rot, &Vector3(0,0,1), Deg2Rad * angle);
		D3DXMatrixScaling(&scale, curScale, curScale, curScale);

		if (parents)
			_info->worldMatrix = _billboard * scale * rot * trans * parents->GetWorldMatrix();
		else
			_info->worldMatrix = _billboard * scale * rot * trans;

	}

	

	m_currentLifeTime += delta;

	if (m_currentLifeTime >= lifeTime)
	{
		m_isAlive = false;
		return;
	}
}
