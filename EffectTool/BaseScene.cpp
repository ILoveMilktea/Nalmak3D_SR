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
	Core::GetInstance()->SetSkyBox(L"SkyBox1");

	{
		MeshRenderer::Desc render;
		render.meshName = L"f15";
		render.mtrlName = L"f15_base";

		auto plane = INSTANTIATE()->AddComponent<MeshRenderer>(&render)->SetPosition(0, 0, 0)->SetScale(0.4f, 0.4f, 0.4f);
		plane->GetComponent<MeshRenderer>()->SetFrustumCulling(false);
		plane->GetComponent<MeshRenderer>()->AddMaterial(L"f15_glass");
		plane->GetComponent<MeshRenderer>()->AddMaterial(L"f15_base");
	}
	DirectionalLight::Desc light;
	light.diffuseIntensity = 0.9f;
	light.ambientIntensity = 0.02f;
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(60, 180, 0);

	auto cam = INSTANTIATE()->AddComponent<Camera>()->SetPosition(2, 1, -10.f)->AddComponent<FreeMove>();
	INSTANTIATE()->AddComponent<Grid>();

	INSTANTIATE()->AddComponent<SystemInfo>()->SetPosition(350, 350, 0);
	//ParticleRenderer::Desc particle;
	//particle.startMinScale = 1;
	//particle.startMaxScale = 1;
	//particle.endColor = Vector4(1, 0, 0, 1);
	//particle.endMaxScale = 3;
	//particle.shape = PARTICLE_EMIT_SHAPE_CIRCLE;
	//particle.radius = 2.f;
	//INSTANTIATE()->AddComponent<ParticleRenderer>(&particle);
}
