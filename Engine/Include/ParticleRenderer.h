#pragma once

#ifndef __PARTICLE_RENDERER_H__
#define __PARTICLE_RENDERER_H__
#include "IRenderer.h"
#include "DynamicInstanceBuffer.h"
class Particle;

class NALMAK_DLL ParticleRenderer :
	public IRenderer
{
public:
	struct Desc
	{
		PARTICLE_EMIT_SHAPE shape = PARTICLE_EMIT_SHAPE::PARTICLE_EMIT_SHAPE_SPHERE;

		// for Circle
		// for Sphere 
		float minRadius = 0.2f;
		float maxRadius = 0.3f;

		// for box
		float width = 1.f;
		float height = 1.f;
		float depth = 1.f;

		// for cone
		float coneAngle = 45.f;

		float startMinSpeed = 0.1f;
		float startMaxSpeed = 0.1f;
		float endMinSpeed = 0.1f;
		float endMaxSpeed = 0.15f;

		UINT emittorCount = 30;
		float duration = 5.f;
		float minAwakeTime = 0.f;
		float maxAwakeTime = 0.f;


		Vector3 force = Vector3(0, 0, 0);

		float gravity = 0.f;

		float minAngle = 0.f;
		float maxAngle = 0.f;

		float startMinScale = 0.1f;
		float startMaxScale = 0.2f;
		float endMinScale = 0.15f;
		float endMaxScale = 0.2f;


		Vector4 startMinColor = Vector4(1, 1, 1, 1);
		Vector4 startMaxColor = Vector4(1, 1, 1, 1);
		Vector4 endMinColor = Vector4(0, 0, 0, 0);
		Vector4 endMaxColor = Vector4(0, 0, 0, 0);

		float minLifeTime = 3;
		float maxLifeTime = 5;

		int maxParticleCount = 300;

		bool  isLoop = true;
		bool  isPlay = true;
		bool isPlayOnAwake = true;
		bool isLocal = false;
		bool isVelocityLocal = false;
	};
	struct Burst
	{
		float time;
		UINT count;
	};
	ParticleRenderer(Desc* _desc);
private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
public:
	virtual void Render() override;
	virtual void BindingStreamSource() override;
public:
	// 런타임중엔 왠만해선 바꾸지말자! 상당히 무거운 작업
	void SetMaxParticleCount(int _maxCount);

	void SetGravityScale(float _scale);
public:
	ParticleRenderer::Desc m_info;
private:
	float m_awakeTime = 0;
	float m_playTime = 0;
	float m_currentEmitTime;
	int m_currentCount;
	float m_secPerEmit;
public:
	void Emit(int _count);
	void SetEmitCount(int _count);
private:
	void EmitSphere(int _count);
	void EmitCircle(int _count);
	void EmitBox(int _count);
	void EmitCone(int _count);
public:
	void Stop();
	void Play();
public:
	const vector<Burst>& GetBurstList() { return m_emitBursts; }
	void AddBurst(Burst _burst);
	void DeleteBurst(size_t _index);
private:
	list<Particle*> m_activedParticles;
	queue<Particle*> m_particlePool;
	INPUT_LAYOUT_PARTICLE* m_particlesInfo;
	vector<Burst> m_emitBursts;
	size_t m_currentBurstIndex;
	size_t m_currentBurstTime;

	Burst* m_currentBurst;
	

private:
	DynamicInstanceBuffer* m_instanceBuffer;
	void ParticleUpdate();
};

#endif
