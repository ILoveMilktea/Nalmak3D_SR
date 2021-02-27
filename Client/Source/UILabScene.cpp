#include "stdafx.h"
#include "..\Include\UILabScene.h"
#include "Rader.h"
#include "SingleLine.h"
#include "SplineCurve.h"
#include "CustomDebuger.h"

void UILabScene::Initialize()
{
	INSTANTIATE()->AddComponent<Grid>();
	INSTANTIATE(OBJECT_TAG_DEBUG, L"systemInfo")->
		AddComponent<SystemInfo>()->
		SetPosition(50, 100, 0);
	
	{
		auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>()->AddComponent<FreeMove>();
		mainCam->GetComponent<Camera>()->OffLayer(RENDER_LAYER_UI);
		mainCam->SetPosition(0, 5, -5);
		mainCam->SetRotation(30, 0, 0);
	}

	PlayerUIPatitial();

	//CreatePauseButton();

	//CreateRader();
	//CreateSplineCurve();
	//GarageMainWindow();

	// meshName 
	// box, line, quad, sphere, triangle, quadNoneNormal
	UIFactory::CreateEditController();
}

void UILabScene::CreatePauseButton()
{
	auto button1 = INSTANTIATE(OBJECT_TAG_DEFAULT, L"button1")->
		AddComponent<Button>()
		->SetPosition(200.f, 500.f, 0.f);

	EventHandler eventFunc = EventHandler([=]() {
		BUTTON_TRANSITION tr = button1->GetComponent<Button>()->GetTransition();
		switch (tr)
		{
		case BUTTON_TRANSITION_NONE:
			break;
		case BUTTON_TRANSITION_COLOR:
			button1->GetComponent<Button>()->SetTransition(BUTTON_TRANSITION_SWAP);
			break;
		case BUTTON_TRANSITION_SWAP:
			button1->GetComponent<Button>()->SetTransition(BUTTON_TRANSITION_COLOR);
			break;
		}
	});

	auto button2 = UIFactory::CreateButton(eventFunc);
	button2->SetPosition(400.f, 500.f, 0.f);

	auto pauseButton = UIFactory::CreatePauseButton();
	pauseButton->SetPosition(800.f, 500.f, 0.f);

	auto toggle = UIFactory::CreateToggle();
	toggle->SetPosition(1200.f, 500.f, 0.f);

}

void UILabScene::CreateRader()
{
	// player
	MeshRenderer::Desc boxdesc;
	SphereCollider::Desc coldesc;
	coldesc.radius = 2.f;
	boxdesc.meshName = L"box";
	auto player =
		INSTANTIATE()->
		AddComponent<MeshRenderer>(&boxdesc)->
		AddComponent<DrawGizmo>()->
		AddComponent<MeshPicking>()->
		AddComponent<SphereCollider>(&coldesc);

	// rader
	Rader::Desc desc;
	desc.findRange = 100.f;
	desc.readyflight = 5;

	auto rader = INSTANTIATE()->
		AddComponent<Rader>(&desc);

	// enemy
	MeshRenderer::Desc circledesc;
	circledesc.meshName = L"sphere";
	circledesc.mtrlName = L"default_red";
	auto enemy1 =
		INSTANTIATE()->
		AddComponent<MeshRenderer>(&circledesc)->
		SetPosition(8.f, 0.f, 8.f);
	circledesc.mtrlName = L"default_yellow";
	auto enemy2 =
		INSTANTIATE()->
		AddComponent<MeshRenderer>(&circledesc)->
		SetPosition(6.f, 5.f, -12.f);
	circledesc.mtrlName = L"default_green";
	auto enemy3 =
		INSTANTIATE()->
		AddComponent<MeshRenderer>(&circledesc)->
		SetPosition(25.f, -15.f, 3.f);

	rader->GetComponent<Rader>()->Temp_AddEnemy(enemy1->GetTransform());
	rader->GetComponent<Rader>()->Temp_AddEnemy(enemy2->GetTransform());
	rader->GetComponent<Rader>()->Temp_AddEnemy(enemy3->GetTransform());

	{
		MeshRenderer::Desc boxdesc;
		boxdesc.meshName = L"sphere";
		auto player =
			INSTANTIATE()->
			AddComponent<MeshRenderer>(&boxdesc)->
			AddComponent<SphereCollider>()->
			SetPosition(5.f, 0.f, 0.f);

	}
}

void UILabScene::CreateSplineCurve()
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
			linedesc.point1 = &prevPoint->GetTransform()->position;
			linedesc.point2 = &curPoint->GetTransform()->position;

			prevPoint->AddComponent<SingleLine>(&linedesc);
		}
		prevPoint = curPoint;
	}
}

void UILabScene::PlayerUIPatitial()
{
	//grid line 
	{
		//left

		//right
	}
	

	SingleImage::Desc desc_si;
	desc_si.textureName = L"dfSample";
	auto background = INSTANTIATE();
	background->AddComponent<CanvasRenderer>();
	background->AddComponent<SingleImage>(&desc_si);
	background->GetComponent<CanvasRenderer>()->SetFade(0.5f);
	background->SetPosition(WINCX * 0.5f, WINCY * 0.5f);
	background->SetScale(WINCX, WINCY);

	auto bigtext = UIFactory::CreateText_Title_LEFT_White_Grid(L"BIG TEXT");
	bigtext->AddComponent<DrawGizmo_2D>();
	bigtext->AddComponent<CanvasPicking>();
	bigtext->AddComponent<CustomDebuger>(); // debuglog
	bigtext->SetPosition(200.f, 100.f);
	bigtext->SetScale(300.f, 80.f);

	auto smalltext = UIFactory::CreateText_Contents_LEFT_White_Grid(L"Small Text");
	smalltext->AddComponent<DrawGizmo_2D>();
	smalltext->AddComponent<CanvasPicking>();
	smalltext->AddComponent<CustomDebuger>();
	smalltext->SetPosition(200.f, 300.f);
	smalltext->SetScale(400.f, 80.f);
	//auto image1 = UIFactory::CreateImage();
	//image1->SetPosition(100.f, 100.f, 0.f);
	//auto image2 = UIFactory::CreateImage(CANVAS_GROUP_G1);
	//image2->SetPosition(300.f, 100.f, 0.f);
	//auto image3 = UIFactory::CreateImage();
	//image3->SetPosition(500.f, 100.f, 0.f);
	//auto image4 = UIFactory::CreateImage(CANVAS_GROUP_G2);
	//image4->SetPosition(700.f, 100.f, 0.f);
	//image4->GetComponent<CanvasRenderer>()->SetFade(0.f);

}
