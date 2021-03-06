#include "ParticleRenderer.h"
#include "Transform.h"
#include "Particle.h"
#include "ParticleInfo.h"
#include "RenderManager.h"
ParticleRenderer::ParticleRenderer(Desc * _desc)
{
	m_viBuffer = ResourceManager::GetInstance()->GetResource<VIBuffer>(L"quadNoneNormal");

	ParticleInfo* info = ResourceManager::GetInstance()->GetResource<ParticleInfo>(_desc->particleDataName);
	m_emitBursts = info->GetParticleBurst();
	m_material = info->GetMaterial();
	m_info = info->GetParticleInfo();


	if (m_material->GetShader()->GetInputLayout() != VERTEX_INPUT_LAYOUT_PARTICLE)
		assert(L"Particle Renderer must have particle Shader Material!" && 0);



	m_currentCount = 0;
	m_playTime = 0.f;

	m_type = RENDERER_TYPE_PARTICLE;


}

void ParticleRenderer::Initialize()
{
	UpdateParticleInfo(m_info.maxParticleCount);

	m_spriteIndexRatio = 1.f / (m_info.animationTileX * m_info.animationTileY);

	m_awakeTime = Nalmak_Math::Rand(m_info.minAwakeTime, m_info.maxAwakeTime);

	m_secPerEmit = 1 / (float)m_info.emittorCount;

	m_camera = RenderManager::GetInstance()->GetMainCamera();
}

void ParticleRenderer::Update()
{
	if (m_info.isPlay)
	{
		if (m_awakeTime > 0)
		{
			m_awakeTime -= dTime;
			return;
		}
		
		m_playTime += dTime;
		if (m_playTime > m_info.duration)
		{
			if (m_emitBursts.size() > 0)
			{
				m_currentBurstIndex = 0;
				m_currentBurst = &m_emitBursts[0];
			}

			if (!m_info.isLoop)
			{
				m_info.isPlay = false;
				return;
			}
			m_playTime -= m_info.duration;
			
		}

		if (m_currentBurst)
		{
			if (m_currentBurst->time < m_playTime)
			{
				Emit(m_currentBurst->count);

				if (m_currentBurstIndex >= m_emitBursts.size() - 1)
				{
					m_currentBurst = nullptr;
				}
				else
				{
					++m_currentBurstIndex;
					m_currentBurst = &m_emitBursts[m_currentBurstIndex];
				}
			}
		}


		if (m_currentEmitTime > m_secPerEmit)
		{
			int count = (int)(m_currentEmitTime / m_secPerEmit);
			m_currentEmitTime -= m_secPerEmit * count;
			Emit(count);
		}

		m_currentEmitTime += dTime;

	}

}

void ParticleRenderer::LateUpdate()
{
	ParticleUpdate();
}

void ParticleRenderer::Release()
{
	while (!m_particlePool.empty())
	{
		SAFE_DELETE(m_particlePool.front());
		m_particlePool.pop();
	}
	for (auto& particle : m_activedParticles)
		SAFE_DELETE(particle);
	m_activedParticles.clear();

	SAFE_DELETE_ARR(m_particlesInfo);
	SAFE_DELETE(m_instanceBuffer);
}

void ParticleRenderer::Render(Shader * _shader, int _index)
{
	if (m_currentCount == 0)
		return;

	assert("Current Shader is nullptr! " && _shader);

	_shader->CommitChanges();
	ThrowIfFailed(m_device->DrawIndexedPrimitive(_shader->GetPrimitiveType(), 0, 0, 4 * m_currentCount, 0, m_viBuffer->GetFigureCount()));

	ThrowIfFailed(m_device->SetStreamSourceFreq(0, 1));
	ThrowIfFailed(m_device->SetStreamSourceFreq(1, 1));
}

void ParticleRenderer::BindingStreamSource()
{
	if (m_currentCount == 0)
		return;

	ThrowIfFailed(m_device->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | m_currentCount));
	ThrowIfFailed(m_device->SetStreamSource(0, m_viBuffer->GetVertexBuffer(), 0, sizeof(INPUT_LAYOUT_POSITION_UV)));

	ThrowIfFailed(m_device->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1ul));
	ThrowIfFailed(m_device->SetStreamSource(1, m_instanceBuffer->GetVertexBuffer(), 0, sizeof(INPUT_LAYOUT_PARTICLE)));

	ThrowIfFailed(m_device->SetIndices(m_viBuffer->GetIndexBuffer()));

}

void ParticleRenderer::UpdateParticleInfo(int _maxCount)
{
	if (_maxCount <= 0)
		return;

	m_info.maxParticleCount = _maxCount;
	m_currentBurstIndex = 0;

	m_currentCount = 0;
	m_playTime = 0.f;

	while (!m_particlePool.empty())
	{
		SAFE_DELETE(m_particlePool.front());
		m_particlePool.pop();
	}
	for (auto& particle : m_activedParticles)
		SAFE_DELETE(particle);
	m_activedParticles.clear();

	SAFE_DELETE_ARR(m_particlesInfo);
	SAFE_DELETE(m_instanceBuffer);

	m_instanceBuffer = new DynamicInstanceBuffer(m_info.maxParticleCount);
	m_particlesInfo = new INPUT_LAYOUT_PARTICLE[m_info.maxParticleCount];
	
	SetAnimationCount(m_info.animationTileX *  m_info.animationTileY);
	for (int i = 0; i < m_info.maxParticleCount; ++i)
	{
		m_particlesInfo[i].spriteX_spriteY_index.x = (float)m_info.animationTileX;
		m_particlesInfo[i].spriteX_spriteY_index.y = (float)m_info.animationTileY;
	}
	for (int i = 0; i < m_info.maxParticleCount; ++i)
	{
		auto particle = new Particle;
		particle->gravityScale = m_info.gravity;
		particle->StretchedScale = m_info.stretchedScale;
		m_particlePool.push(particle);
	}
	
	
}

void ParticleRenderer::SetAnimationCount(int _count)
{
	m_spriteIndexRatio = 1.f / _count;
}



void ParticleRenderer::SetGravityScale(float _scale)
{
	m_info.gravity = _scale;
	UpdateParticleInfo(m_info.maxParticleCount);
}

void ParticleRenderer::Emit(int _count)
{
	
	switch (m_info.shape)
	{
	case PARTICLE_EMIT_SHAPE_SPHERE:
	{
		EmitSphere(_count);
		break;
	}
	case PARTICLE_EMIT_SHAPE_CIRCLE:
	{
		EmitCircle(_count);
		break;
	}
	case PARTICLE_EMIT_SHAPE_BOX:
	{
		EmitBox(_count);
		break;
	}
	case PARTICLE_EMIT_SHAPE_CONE:
	{
		EmitCone(_count);
		break;
	}
	default:
		break;
	}



}

void ParticleRenderer::SetEmitCount(int _count)
{
	m_info.emittorCount = _count;
	m_secPerEmit = 1 / (float)_count;
}

void ParticleRenderer::EmitSphere(int _count)
{

	Matrix world = m_transform->GetWorldMatrix();
	Vector3 pos;
	memcpy(&pos, &world._41, sizeof(Vector3));
	Matrix rotMat;
	memcpy(&rotMat._11, &world._11, sizeof(Vector3));
	memcpy(&rotMat._21, &world._21, sizeof(Vector3));
	memcpy(&rotMat._31, &world._31, sizeof(Vector3));

	Transform* parents = nullptr;
	if (m_info.isLocal)
	{
		parents = m_transform;
	}

	for (int i = 0; i < _count; ++i)
	{
		if (m_particlePool.size() == 0)
			return;

		Particle* particle = m_particlePool.front();
		m_particlePool.pop();
		particle->Reset();

		Vector3 direction = Vector::Normalize(Vector3(Nalmak_Math::Rand(-1.f, 1.f), Nalmak_Math::Rand(-1.f, 1.f), Nalmak_Math::Rand(-1.f, 1.f)));

		if (parents)
		{
			particle->parents = parents;
			particle->position = Nalmak_Math::Rand(m_info.minRadius, m_info.maxRadius) * direction;

		}
		else
		{
			particle->position = pos + Nalmak_Math::Rand(m_info.minRadius, m_info.maxRadius) * direction;

		}
		
		particle->direction = direction;
		if (m_info.isVelocityLocal)
			D3DXVec3TransformNormal(&particle->acceleration, &m_info.force, &rotMat);
		else
			particle->acceleration = m_info.force;
		particle->startSpeed = Nalmak_Math::Rand(m_info.startMinSpeed, m_info.startMaxSpeed);
		particle->endSpeed = Nalmak_Math::Rand(m_info.endMinSpeed, m_info.endMaxSpeed);
		particle->startScale = Nalmak_Math::Rand(m_info.startMinScale, m_info.startMaxScale);
		particle->endScale = Nalmak_Math::Rand(m_info.endMinScale, m_info.endMaxScale);	
		particle->angle = Nalmak_Math::Rand(m_info.minAngle, m_info.maxAngle);
		particle->angluarVelocity = Nalmak_Math::Rand(m_info.minAngularVelocity, m_info.maxAngularVelocity);
		float startColor = Nalmak_Math::Rand(0.f, 1.f);
		particle->startColor = Nalmak_Math::Lerp(m_info.startMinColor, m_info.startMaxColor,startColor);
		float endColor = Nalmak_Math::Rand(0.f, 1.f);
		particle->endColor = Nalmak_Math::Lerp(m_info.endMinColor, m_info.endMaxColor,endColor);
		particle->lifeTime = Nalmak_Math::Rand(m_info.minLifeTime, m_info.maxLifeTime);

		m_activedParticles.emplace_back(particle);
	}
}

void ParticleRenderer::EmitCircle(int _count)
{
	Matrix world = m_transform->GetWorldMatrix();
	Vector3 pos;
	memcpy(&pos, &world._41, sizeof(Vector3));
	Matrix rotMat;
	memcpy(&rotMat._11, &world._11, sizeof(Vector3));
	memcpy(&rotMat._21, &world._21, sizeof(Vector3));
	memcpy(&rotMat._31, &world._31, sizeof(Vector3));

	Transform* parents = nullptr;
	if (m_info.isLocal)
	{
		parents = m_transform;
	}

	for (int i = 0; i < _count; ++i)
	{
		if (m_particlePool.size() == 0)
			return;

		Particle* particle = m_particlePool.front();
		m_particlePool.pop();
		particle->Reset();
		Vector3 direction = Vector::Normalize(Vector3(Nalmak_Math::Rand(-1.f, 1.f), 0, Nalmak_Math::Rand(-1.f, 1.f)));
		if (parents)
		{
			particle->parents = parents;
			particle->position = Nalmak_Math::Rand(m_info.minRadius, m_info.maxRadius) * direction;
		}
		else
		{
			D3DXVec3TransformNormal(&direction, &direction, &rotMat);
			particle->position = pos + Nalmak_Math::Rand(m_info.minRadius, m_info.maxRadius) * direction;
		}
		if (m_info.isVelocityLocal)
			D3DXVec3TransformNormal(&particle->acceleration, &m_info.force, &rotMat);
		else
			particle->acceleration = m_info.force;
		particle->startScale = Nalmak_Math::Rand(m_info.startMinScale, m_info.startMaxScale);
		particle->endScale = Nalmak_Math::Rand(m_info.endMinScale, m_info.endMaxScale);
		particle->direction = direction;
		particle->startSpeed = Nalmak_Math::Rand(m_info.startMinSpeed, m_info.startMaxSpeed);
		particle->endSpeed = Nalmak_Math::Rand(m_info.endMinSpeed, m_info.endMaxSpeed);
		particle->angle = Nalmak_Math::Rand(m_info.minAngle, m_info.maxAngle);
		particle->angluarVelocity = Nalmak_Math::Rand(m_info.minAngularVelocity, m_info.maxAngularVelocity);
		float startColor = Nalmak_Math::Rand(0.f, 1.f);
		particle->startColor = Nalmak_Math::Lerp(m_info.startMinColor, m_info.startMaxColor, startColor);
		float endColor = Nalmak_Math::Rand(0.f, 1.f);
		particle->endColor = Nalmak_Math::Lerp(m_info.endMinColor, m_info.endMaxColor, endColor);
		particle->lifeTime = Nalmak_Math::Rand(m_info.minLifeTime, m_info.maxLifeTime);

		m_activedParticles.emplace_back(particle);
	}
}

void ParticleRenderer::EmitBox(int _count)
{
	Matrix world = m_transform->GetWorldMatrix();
	Vector3 pos;
	memcpy(&pos, &world._41, sizeof(Vector3));
	Matrix rotMat;
	memcpy(&rotMat._11, &world._11, sizeof(Vector3));
	memcpy(&rotMat._21, &world._21, sizeof(Vector3));
	memcpy(&rotMat._31, &world._31, sizeof(Vector3));


	Vector3 direction = Vector3(0, 1, 0);

	Transform* parents = nullptr;
	if (m_info.isLocal)
	{
		parents = m_transform;
	}

	float halfWidth = m_info.width * 0.5f;
	float halfHeight = m_info.height * 0.5f;
	float halfDepth = m_info.depth * 0.5f;


	for (int i = 0; i < _count; ++i)
	{
		if (m_particlePool.size() == 0)
			return;

		Particle* particle = m_particlePool.front();
		m_particlePool.pop();
		particle->Reset();
		Vector3 posOffset = Vector3(Nalmak_Math::Rand(-halfWidth, halfWidth), Nalmak_Math::Rand(-halfHeight, halfHeight), Nalmak_Math::Rand(-halfDepth, halfDepth));
		
		if (parents)
		{
			particle->parents = parents;
			particle->position = posOffset;

		}
		else
		{
			D3DXVec3TransformNormal(&posOffset, &posOffset, &rotMat);
			particle->position = pos + posOffset;
			D3DXVec3TransformNormal(&direction, &direction, &rotMat);

			//D3DXVec3TransformNormal(&direction, &direction, &rotMat);
		}
		if (m_info.isVelocityLocal)
			D3DXVec3TransformNormal(&particle->acceleration, &m_info.force, &rotMat);
		else
			particle->acceleration = m_info.force;
		particle->startScale = Nalmak_Math::Rand(m_info.startMinScale, m_info.startMaxScale);
		particle->endScale = Nalmak_Math::Rand(m_info.endMinScale, m_info.endMaxScale);
		particle->direction = direction;
		particle->startSpeed = Nalmak_Math::Rand(m_info.startMinSpeed, m_info.startMaxSpeed);
		particle->endSpeed = Nalmak_Math::Rand(m_info.endMinSpeed, m_info.endMaxSpeed);
		particle->angle = Nalmak_Math::Rand(m_info.minAngle, m_info.maxAngle);
		particle->angluarVelocity = Nalmak_Math::Rand(m_info.minAngularVelocity, m_info.maxAngularVelocity);
		float startColor = Nalmak_Math::Rand(0.f, 1.f);
		particle->startColor = Nalmak_Math::Lerp(m_info.startMinColor, m_info.startMaxColor, startColor);
		float endColor = Nalmak_Math::Rand(0.f, 1.f);
		particle->endColor = Nalmak_Math::Lerp(m_info.endMinColor, m_info.endMaxColor, endColor);
		particle->lifeTime = Nalmak_Math::Rand(m_info.minLifeTime, m_info.maxLifeTime);

		m_activedParticles.emplace_back(particle);
	}
}

void ParticleRenderer::EmitCone(int _count)
{
	Matrix world = m_transform->GetWorldMatrix();
	Vector3 pos;
	memcpy(&pos, &world._41, sizeof(Vector3));
	Matrix rotMat;
	memcpy(&rotMat._11, &world._11, sizeof(Vector3));
	memcpy(&rotMat._21, &world._21, sizeof(Vector3));
	memcpy(&rotMat._31, &world._31, sizeof(Vector3));

	Transform* parents = nullptr;
	if (m_info.isLocal)
	{
		parents = m_transform;
	}

	for (int i = 0; i < _count; ++i)
	{
		if (m_particlePool.size() == 0)
			return;

		Particle* particle = m_particlePool.front();
		m_particlePool.pop();
		particle->Reset();

		Vector3 direction = Nalmak_Math::Normalize(Vector3(Nalmak_Math::Rand(-1.f, 1.f), Nalmak_Math::Rand(-1.f, 1.f), Nalmak_Math::Rand(-1.f, 1.f)));
		float rotAngle = Nalmak_Math::Rand(0.f, m_info.coneAngle);
		Matrix coneMat;
		D3DXMatrixRotationAxis(&coneMat, &direction, rotAngle);
		D3DXVec3TransformNormal(&direction, &Vector3(0, 1, 0), &coneMat);

		if (parents)
		{
			particle->parents = parents;
		}
		else
		{
			D3DXVec3TransformNormal(&direction, &direction, &rotMat);
			particle->position = pos;
		}
		if (m_info.isVelocityLocal)
			D3DXVec3TransformNormal(&particle->acceleration, &m_info.force, &rotMat);
		else
			particle->acceleration = m_info.force;
		particle->direction = direction;
		particle->startSpeed = Nalmak_Math::Rand(m_info.startMinSpeed, m_info.startMaxSpeed);
		particle->endSpeed = Nalmak_Math::Rand(m_info.endMinSpeed, m_info.endMaxSpeed);
		particle->startScale = Nalmak_Math::Rand(m_info.startMinScale, m_info.startMaxScale);
		particle->endScale = Nalmak_Math::Rand(m_info.endMinScale, m_info.endMaxScale);
		particle->angle = Nalmak_Math::Rand(m_info.minAngle, m_info.maxAngle);
		particle->angluarVelocity = Nalmak_Math::Rand(m_info.minAngularVelocity, m_info.maxAngularVelocity);
		float startColor = Nalmak_Math::Rand(0.f, 1.f);
		particle->startColor = Nalmak_Math::Lerp(m_info.startMinColor, m_info.startMaxColor, startColor);
		float endColor = Nalmak_Math::Rand(0.f, 1.f);
		particle->endColor = Nalmak_Math::Lerp(m_info.endMinColor, m_info.endMaxColor, endColor);
		particle->lifeTime = Nalmak_Math::Rand(m_info.minLifeTime, m_info.maxLifeTime);
		m_activedParticles.emplace_back(particle);
	
	}
}

void ParticleRenderer::ParticleUpdate()
{


	if (m_activedParticles.size() == 0)
		return;


	Matrix view = m_camera->GetViewMatrix();
	Matrix billboard;
	D3DXMatrixIdentity(&billboard);

	switch (m_info.billboard)
	{
	case PARTICLE_BILLBOARD_TYPE_NONE:
	
		break;
	case PARTICLE_BILLBOARD_TYPE_DEFAULT:
	{

		memcpy(&billboard.m[0][0], &view.m[0][0], sizeof(Vector3));
		memcpy(&billboard.m[1][0], &view.m[1][0], sizeof(Vector3));
		memcpy(&billboard.m[2][0], &view.m[2][0], sizeof(Vector3));

		D3DXMatrixInverse(&billboard, 0, &billboard);
		break;
	}
	case PARTICLE_BILLBOARD_TYPE_HORIZONTAL:
	{

		billboard._11 = view._11;
		billboard._21 = view._21;
		billboard._22 = view._22;
		billboard._12 = view._12;

		D3DXMatrixInverse(&billboard, 0, &billboard);

		break;
	}
	case PARTICLE_BILLBOARD_TYPE_VERTICAL:
	{

		billboard._11 = view._11;
		billboard._13 = view._13;
		billboard._31 = view._31;
		billboard._33 = view._33;

		D3DXMatrixInverse(&billboard, 0, &billboard);
		break;
	}
	case PARTICLE_BILLBOARD_TYPE_STERTCHED:
	{
		memcpy(&billboard.m[0][0], &view.m[0][0], sizeof(Vector3));
		memcpy(&billboard.m[1][0], &view.m[1][0], sizeof(Vector3));
		memcpy(&billboard.m[2][0], &view.m[2][0], sizeof(Vector3));

		D3DXMatrixInverse(&billboard, 0, &billboard);
		break;
	}
	case PARTICLE_BILLBOARD_TYPE_MAX:
		break;
	default:
		break;
	}

	int i = 0;
	for (auto iter = m_activedParticles.begin(); iter != m_activedParticles.end();)
	{
		if (!(*iter)->IsAlive())
		{
			m_particlePool.push(*iter);
			iter = m_activedParticles.erase(iter);
		}
		else
		{
			(*iter)->Update(&m_particlesInfo[i], billboard, m_spriteIndexRatio, m_info.billboard);
			++iter;
			++i;
			
		}
	}
	m_instanceBuffer->UpdateInstanceBuffer(m_particlesInfo, i);
	m_currentCount = i;
}

int ParticleRenderer::GetMaterialCount()
{
	return 1;
}

Material * ParticleRenderer::GetMaterial(int _index)
{
	return m_material;
}

void ParticleRenderer::SetMaterial(Material * _material, int _index)
{
	m_material = _material;
}

void ParticleRenderer::SetMaterial(const wstring& _mtrlName, int _index)
{
	m_material = ResourceManager::GetInstance()->GetResource<Material>(_mtrlName);
}

void ParticleRenderer::Stop()
{
	m_info.isPlay = false;
	for (auto& particle : m_activedParticles)
	{
		m_particlePool.push(particle);
	}
	m_activedParticles.clear();
	m_currentCount = 0;
	m_playTime = 0.f;
}

void ParticleRenderer::Play()
{
	m_info.isPlay = true;
	for (auto& particle : m_activedParticles)
	{
		m_particlePool.push(particle);
	}
	m_activedParticles.clear();
	m_currentCount = 0;
	m_playTime = 0.f;
	m_awakeTime = Nalmak_Math::Rand(m_info.minAwakeTime, m_info.maxAwakeTime);
}

void ParticleRenderer::AddBurst(Burst _burst)
{
	m_emitBursts.emplace_back(_burst);

	sort(m_emitBursts.begin(), m_emitBursts.end(), []  (Burst _b1, Burst _b2)
	-> bool{
		if (_b1.time < _b2.time)
			return true;
		return false;
	});
	int a = 5;
}

void ParticleRenderer::DeleteBurst(size_t _index)
{
	if (_index >= m_emitBursts.size())
		return;

	auto iterBurst= m_emitBursts.begin() + _index;

	m_emitBursts.erase(iterBurst);
}
