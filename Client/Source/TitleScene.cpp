#include "stdafx.h"
#include "TitleScene.h"
#include "NextSceneLoad.h"
#include "TestComponent.h"
#include "core.h"
#include "PlaneController.h"
#include "PlaneInfo.h"
#include "ClimbTerrain.h"

#include "PlayerInfoManager.h"
#include "SceneChanger.h"

//////////////////////////////////////////////////////////////////////////////////
// 2021 02 22
//////////////////////////////////////////////////////////////////////////////////
// ���ҽ� ���� ��� // Type (Material, shader , mesh) -> Tag(Player, Enemy)
//////////////////////////////////////////////////////////////////////////////////
// Renderer ����
// 1. MeshRenderer      : ���� �����
// 2. CanvasRenderer    : ��ǥ�谡 ��ũ�������� �ٲ� (0,0,wincx,wincy)
//      -> Button , Text , singleImage 
//
// 3. ParticleRenderer  : ����Ʈ
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// Component
// 1. SceneChanger 
// 2. DrawGizmo  -> ��ŷ ���� (�� ���� ����)
// 3. PrintInfo  -> ��ü ����  Debug Log Transform
// 4. DirectionalLight -> ���籤 (��ü ����)
// 5. PointLight -> ������ 
// 
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// Core -> Skybox Setting   SetSkyBox(dds name)
// Core -> ��� ���ҽ��� ���� �������� �� ���� 
// Shader , Renertarget -> Ŭ�󸸵� (������ �Ľ����� ���)


void TitleScene::Initialize()
{
	INSTANTIATE()->AddComponent<Grid>();

	DirectionalLight::Desc light;
	light.intensity = 1.f;
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(60, 20, 0);// ->AddComponent<AutoRotate>(&rot);
	
	{
		auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>();
	}

	{
		for (int i = 0; i < 200; ++i)
		{
			MeshRenderer::Desc mesh;
			mesh.meshName = L"sphere";
			mesh.mtrlName = L"standard";
			INSTANTIATE()->AddComponent<MeshRenderer>(&mesh)->SetScale(Vector3(1,1,1) * Nalmak_Math::Rand(1.f, 3.f))->SetPosition(Nalmak_Math::Rand(-60.f, 60.f), Nalmak_Math::Rand(1.f, 20.f), Nalmak_Math::Rand(-60.f, 60.f));
		}
		
	}
	MeshRenderer::Desc mesh;
	mesh.meshName = L"teapot";
	mesh.mtrlName = L"standard";
	INSTANTIATE()->AddComponent<MeshRenderer>(&mesh)->SetPosition(0, 0, 2);


	{
		MeshRenderer::Desc render;
		render.mtrlName = L"standard";
		render.meshName = L"plane";
		INSTANTIATE()->AddComponent<MeshRenderer>(&render)->SetPosition(0, 0, -1)->SetScale(100, 100, 100);
	}


	INSTANTIATE(OBJECT_TAG_DEBUG,L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(-HALF_WINCX, HALF_WINCY, 0);
	
	SceneChanger::Desc SceneChangerDescInfo;
	SceneChangerDescInfo.keyState = KEY_STATE_ENTER;
	SceneChangerDescInfo.sceneName = L"phantom";
	auto SceneSelect =  INSTANTIATE()->AddComponent<SceneChanger>(&SceneChangerDescInfo);


	SceneChanger::Desc SceneToHee;
	SceneToHee.keyState = KEY_STATE_SPACE;
	SceneToHee.sceneName = L"Hee";
	
	SceneSelect->AddComponent<SceneChanger>(&SceneToHee);


	

}
