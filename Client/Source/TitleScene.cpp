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
#include "PrintInfo.h"


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
	Core::GetInstance()->SetSkyBox(L"skyBox_default");

	INSTANTIATE()->AddComponent<Grid>();


	
	
	{
		FreeMove::Desc free;

		auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>()->AddComponent<FreeMove>(&free)->AddComponent<PrintInfo>()->SetPosition(0,0,-5);
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


	INSTANTIATE(OBJECT_TAG_DEBUG,L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(50, 50, 0);
	

	SceneChanger::Desc SceneChangerDescInfo;
	SceneChangerDescInfo.keyState = KEY_STATE_ENTER;
	SceneChangerDescInfo.sceneName = L"phantom";
	auto SceneSelect = INSTANTIATE()->AddComponent<SceneChanger>(&SceneChangerDescInfo);


	//SceneChanger::Desc SceneToHee;
	//SceneToHee.keyState = KEY_STATE_SPACE;
	//SceneToHee.sceneName = L"Hee";
	//SceneSelect->AddComponent<SceneChanger>(&SceneToHee);


	auto pauseButton = UIFactory::CreatePauseButton();
	pauseButton->SetPosition(1800.f, 240.f, 0.f);

	

}
