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
// 리소스 정리 방법 // Type (Material, shader , mesh) -> Tag(Player, Enemy)
//////////////////////////////////////////////////////////////////////////////////
// Renderer 종류
// 1. MeshRenderer      : 기존 사용방법
// 2. CanvasRenderer    : 좌표계가 스크린상으로 바뀜 (0,0,wincx,wincy)
//      -> Button , Text , singleImage 
//
// 3. ParticleRenderer  : 이펙트
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// Component
// 1. SceneChanger 
// 2. DrawGizmo  -> 피킹 가능 (한 개만 가능)
// 3. PrintInfo  -> 객체 정보  Debug Log Transform
// 4. DirectionalLight -> 직사광 (전체 조명)
// 5. PointLight -> 점조명 
// 
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// Core -> Skybox Setting   SetSkyBox(dds name)
// Core -> 모든 리소스를 이제 엔진에서 안 만듬 
// Shader , Renertarget -> 클라만듬 (데이터 파싱으로 사용)


void TitleScene::Initialize()

{
	Core::GetInstance()->SetSkyBox(L"skyBox_default");

	INSTANTIATE()->AddComponent<Grid>();


	
	
	{
		FreeMove::Desc free;

		auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>()->AddComponent<FreeMove>(&free)->AddComponent<PrintInfo>()->SetPosition(0,0,-5);
	}


	


	{
		VIBufferRenderer::Desc render;
		render.mtrlName = L"standard";
		render.meshName = L"plane";
		INSTANTIATE()->AddComponent<VIBufferRenderer>(&render)->SetPosition(0, 0, -1)->SetScale(100, 100, 100);
	}


	INSTANTIATE(OBJECT_TAG_DEBUG,L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(50, 50, 0);
	

	SceneChanger::Desc SceneChangerDescInfo;
	SceneChangerDescInfo.keyState = KEY_STATE_ENTER;
	SceneChangerDescInfo.sceneName = L"garage";
	auto SceneSelect = INSTANTIATE()->AddComponent<SceneChanger>(&SceneChangerDescInfo);


	//SceneChanger::Desc SceneToHee;
	//SceneToHee.keyState = KEY_STATE_SPACE;
	//SceneToHee.sceneName = L"Hee";
	//SceneSelect->AddComponent<SceneChanger>(&SceneToHee);


	auto pauseButton = UIFactory::CreatePauseButton();
	pauseButton->SetPosition(1800.f, 240.f, 0.f);

	

}
