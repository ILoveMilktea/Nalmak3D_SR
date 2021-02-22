#include "stdafx.h"
#include "..\Include\UILabScene.h"
#include "Rader.h"
#include "SingleLine.h"
#include "SplineCurve.h"

void UILabScene::Initialize()
{
	INSTANTIATE()->AddComponent<Grid>();
	INSTANTIATE(OBJECT_TAG_DEBUG, L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(100, 100, 0);
	
	{
		auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>()->AddComponent<FreeMove>();
		mainCam->GetComponent<Camera>()->OffLayer(RENDER_LAYER_UI);
		mainCam->SetPosition(0, 5, -5);
		mainCam->SetRotation(30, 0, 0);
		mainCam->SetDontDestroy(true);
	}


	// ������Ʈ�� Add�ϸ�?
	// �����ڰ� ȣ��?
	// transform ���� ( �̰ŵ� ������ �����ڸ�)

	// component add -> ������ -> ���� ������ ������Ʈ �� initialize
	// �״ϱ� �����ڳ� initialize���� ���� �����ϸ� ���� �����ϼ���

	{
		//Camera::Desc cam;
		//cam.mode = CAMERA_PROJECTION_MODE_ORTHOGRAPHIC;
		//cam.width = WINCX;
		//cam.height = WINCY;
		//auto uiCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"uiCamera")->AddComponent<Camera>(&cam);
		//uiCam->GetComponent<Camera>()->AllOffLayer();
		//uiCam->GetComponent<Camera>()->OnLayer(RENDER_LAYER_UI);
		//uiCam->SetPosition(0, 0, -10);
		//uiCam->SetDontDestroy(true);
	}

	{
		//INSTANTIATE()->AddComponent<CanvasRenderer>()->SetScale(400.f,300.f,0.f);
	}
	{
		//INSTANTIATE()->
		//	/*AddComponent<CanvasRenderer>()->*/
		//	AddComponent<Text>()->
		//	SetPosition(50.f, 50.f, 0.f)->
		//	SetScale(100.f, 100.f, 0.f);
	}

	{
		//auto button1 = INSTANTIATE(OBJECT_TAG_DEFAULT, L"button1")->
		//	AddComponent<Button>()
		//	->SetPosition(0.f, 50.f,0.f);

		//Button::Desc desc;
		//desc.eventFunc = EventHandler([=]() {
		//	BUTTON_TRANSITION tr = button1->GetComponent<Button>()->GetTransition();
		//	switch (tr)
		//	{
		//	case BUTTON_TRANSITION_NONE:
		//		break;
		//	case BUTTON_TRANSITION_COLOR:
		//		button1->GetComponent<Button>()->SetTransition(BUTTON_TRANSITION_SWAP);
		//		break;
		//	case BUTTON_TRANSITION_SWAP:
		//		button1->GetComponent<Button>()->SetTransition(BUTTON_TRANSITION_COLOR);
		//		break;
		//	}
		//});

		//// culling�� memory leak �߻�
		//auto button2 = INSTANTIATE(OBJECT_TAG_DEFAULT, L"button2")->
		//	AddComponent<Button>(&desc)
		//	->SetPosition(-50.f, 100.f, 0.f)
		//	->SetScale(250.f, 250.f, 0.f);
	}

	// curve lab
	{
		MeshRenderer::Desc circledesc;
		circledesc.meshName = L"box";
		circledesc.mtrlName = L"default_green";

		auto p1 =
			INSTANTIATE()->
			AddComponent<MeshRenderer>(&circledesc)->
			AddComponent<DrawGizmo>()->
			AddComponent<MeshPicking>()->
			SetPosition(0.f, 0.f, 0.f)->
			SetScale(0.3f, 0.3f, 0.3f);
		auto p2 =
			INSTANTIATE()->
			AddComponent<MeshRenderer>(&circledesc)->
			AddComponent<DrawGizmo>()->
			AddComponent<MeshPicking>()->
			SetPosition(3.f, 5.f, 1.f);
		auto p3 =
			INSTANTIATE()->
			AddComponent<MeshRenderer>(&circledesc)->
			AddComponent<DrawGizmo>()->
			AddComponent<MeshPicking>()->
			SetPosition(6.f, -2.f, 5.f);
		auto p4 =
			INSTANTIATE()->
			AddComponent<MeshRenderer>(&circledesc)->
			AddComponent<DrawGizmo>()->
			AddComponent<MeshPicking>()->
			SetPosition(8.f, -4.f, 0.f);
		auto p5 =
			INSTANTIATE()->
			AddComponent<MeshRenderer>(&circledesc)->
			AddComponent<DrawGizmo>()->
			AddComponent<MeshPicking>()->
			SetPosition(12.f, 3.f, -3.f);
		// test 5 point
		{
			//SingleLine::Desc linedesc;
			//linedesc.point1 = p1->GetTransform()->position;
			//linedesc.point2 = p2->GetTransform()->position;
			//p1->AddComponent<SingleLine>(&linedesc);
			//linedesc.point1 = p2->GetTransform()->position;
			//linedesc.point2 = p3->GetTransform()->position;
			//p2->AddComponent<SingleLine>(&linedesc);
			//linedesc.point1 = p3->GetTransform()->position;
			//linedesc.point2 = p4->GetTransform()->position;
			//p3->AddComponent<SingleLine>(&linedesc);
			//linedesc.point1 = p4->GetTransform()->position;
			//linedesc.point2 = p5->GetTransform()->position;
			//p4->AddComponent<SingleLine>(&linedesc);
		}


		// generate curve
		SplineCurve curveGenerator;
		curveGenerator.AddPoint(p1->GetTransform()->position);
		curveGenerator.AddPoint(p2->GetTransform()->position);
		curveGenerator.AddPoint(p3->GetTransform()->position);
		curveGenerator.AddPoint(p4->GetTransform()->position);
		curveGenerator.AddPoint(p5->GetTransform()->position);
		curveGenerator.DrawCurve();
		list<Vector3>* curve = curveGenerator.GetCurve();

		int index = 0;
		GameObject* prevPoint = nullptr;
		for (auto lerpPoint = curve->begin(); lerpPoint != curve->end(); ++lerpPoint)
		{
			auto curPoint =
				INSTANTIATE()->
				AddComponent<MeshRenderer>(&circledesc)->
				SetPosition(*lerpPoint)->
				SetScale(0.3f, 0.3f, 0.3f);

			if (prevPoint)
			{
				SingleLine::Desc linedesc;
				linedesc.point1 = prevPoint->GetTransform()->position;
				linedesc.point2 = curPoint->GetTransform()->position;
				prevPoint->AddComponent<SingleLine>(&linedesc);
			}
			prevPoint = curPoint;
		}
	}

	//rader lab
	{
		//// player
		//MeshRenderer::Desc boxdesc;
		//SphereCollider::Desc coldesc;
		//coldesc.radius = 2.f;
		//boxdesc.meshName = L"box";
		//auto player =
		//	INSTANTIATE()->
		//	AddComponent<MeshRenderer>(&boxdesc)->
		//	AddComponent<DrawGizmo>()->
		//	AddComponent<MeshPicking>()->
		//	AddComponent<SphereCollider>(&coldesc);

		//// rader
		//Rader::Desc desc;
		//desc.player = player->GetTransform();
		//desc.findRange = 100.f;
		//desc.readyflight = 5;

		//auto rader = INSTANTIATE()->
		//	AddComponent<Rader>(&desc);

		//// enemy
		//MeshRenderer::Desc circledesc;
		//circledesc.meshName = L"sphere";
		//circledesc.mtrlName = L"default_red";
		//auto enemy1 =
		//	INSTANTIATE()->
		//	AddComponent<MeshRenderer>(&circledesc)->
		//	SetPosition(8.f, 0.f, 8.f);
		//circledesc.mtrlName = L"default_yellow";
		//auto enemy2 =
		//	INSTANTIATE()->
		//	AddComponent<MeshRenderer>(&circledesc)->
		//	SetPosition(6.f, 5.f, -12.f);
		//circledesc.mtrlName = L"default_green";
		//auto enemy3 =
		//	INSTANTIATE()->
		//	AddComponent<MeshRenderer>(&circledesc)->
		//	SetPosition(25.f, -15.f, 3.f);

		//rader->GetComponent<Rader>()->Temp_AddEnemy(enemy1->GetTransform());
		//rader->GetComponent<Rader>()->Temp_AddEnemy(enemy2->GetTransform());
		//rader->GetComponent<Rader>()->Temp_AddEnemy(enemy3->GetTransform());

		{
			//MeshRenderer::Desc boxdesc;
			//boxdesc.meshName = L"sphere";
			//auto player =
			//	INSTANTIATE()->
			//	AddComponent<MeshRenderer>(&boxdesc)->
			//	AddComponent<SphereCollider>()->
			//	SetPosition(5.f,0.f,0.f);

		}
	}


	// meshName ���
	// box, line, quad, sphere, triangle, quadNoneNormal
}
