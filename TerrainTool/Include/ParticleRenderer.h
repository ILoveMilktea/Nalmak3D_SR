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
		wstring particleDataName;
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
	ParticleData m_info;
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
