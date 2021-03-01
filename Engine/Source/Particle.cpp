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
		/*	{
				Vector3 particleRight;
				D3DXVec3Cross(&particleRight, &dir, &Vector3(_billboard._31, _billboard._32, _billboard._33));

			}*/

	/*	Vector3 rightB, upB, lookB;
		D3DXVec3TransformNormal(&rightB, &Vector3(1, 0, 0), &stretch);
		D3DXVec3TransformNormal(&upB, &Vector3(0, 1, 0), &stretch);
		D3DXVec3TransformNormal(&lookB, &Vector3(0, 0, 1), &stretch);

		Vector3 cross;
		D3DXVec3Cross(&cross, &dir, &Vector3(0, 0, 1));

		Nalmak_Math::GetMatrixRotateACoordtoBCoord(&stretch,
			Vector3(1, 0, 0),
			Vector3(0, 1, 0),
			Vector3(0, 0, 1),
			rightB,
			upB,
			lookB);*/


		rot = stretch;
	}
	else
	{
		D3DXMatrixRotationZ(&rot, angle);
		D3DXMatrixScaling(&scale, curScale, curScale, curScale);

	}

	if (parents)
		_info->worldMatrix = _billboard * scale * rot * trans * parents->GetWorldMatrix();
	else
		_info->worldMatrix = _billboard * scale * rot * trans;

	m_currentLifeTime += delta;

	if (m_currentLifeTime >= lifeTime)
	{
		m_isAlive = false;
		return;
	}
}
