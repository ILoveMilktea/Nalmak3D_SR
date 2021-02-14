#include "stdafx.h"
#include "BaseScene.h"


BaseScene::BaseScene()
{
}


BaseScene::~BaseScene()
{
}

void BaseScene::Initialize()
{
	auto cam = INSTANTIATE()->AddComponent<Camera>()->SetPosition(2, 1, -10.f)->AddComponent<FreeMove>();
	INSTANTIATE()->AddComponent<Grid>();

	INSTANTIATE()->AddComponent<SystemInfo>()->SetPosition(-300, 300, 0);
	//ParticleRenderer::Desc particle;
	//particle.startMinScale = 1;
	//particle.startMaxScale = 1;
	//particle.endColor = Vector4(1, 0, 0, 1);
	//particle.endMaxScale = 3;
	//particle.shape = PARTICLE_EMIT_SHAPE_CIRCLE;
	//particle.radius = 2.f;
	//INSTANTIATE()->AddComponent<ParticleRenderer>(&particle);
}
