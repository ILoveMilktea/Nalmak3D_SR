#include "Core.h"

#include "Exception.h"
#include "DeviceManager.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "TimeManager.h"
#include "SystemManager.h"
#include "DebugManager.h"
#include "CollisionManager.h"
#include "Quad.h"
#include "LineVI.h"
#include "Triangle.h"
USING(Nalmak)




IMPLEMENT_SINGLETON(Core)


// Core changes 02.22 for.jjy
// Device Getter Func 1Add;
// Renderman GetterFunc 2Add;


Core::Core()
{
	m_sceneManager = SceneManager::GetInstance();
	m_prototypeManager = PrototypeManager::GetInstance();
	m_objectManager = ObjectManager::GetInstance();
	m_inputManager = InputManager::GetInstance();
	m_resourceManager = ResourceManager::GetInstance();
	m_timeManager = TimeManager::GetInstance();
	m_lineManager = LineManager::GetInstance();
	m_systemManager = SystemManager::GetInstance();
	m_debugManager = DebugManager::GetInstance();
	m_collisionManager = CollisionManager::GetInstance();
	m_lightManager = LightManager::GetInstance();
	//
	m_deviceManager = DeviceManager::GetInstance();
	m_renderManager = RenderManager::GetInstance();
	//
}


Core::~Core()
{
	ResourceManager::DestroyInstance();
	InputManager::DestroyInstance();
	SceneManager::DestroyInstance();
	RenderManager::DestroyInstance();
	LineManager::DestroyInstance();
	PrototypeManager::DestroyInstance();
	ObjectManager::DestroyInstance();
	DeviceManager::DestroyInstance();
	TimeManager::DestroyInstance();
	SystemManager::DestroyInstance();
	DebugManager::DestroyInstance();
	CollisionManager::DestroyInstance();
	LightManager::DestroyInstance();
}



void Core::Initialize(HWND handle, Desc * _desc)
{
	RenderManager::GetInstance()->SetWindowSize(_desc->wincx, _desc->wincy);
	ObjectManager::GetInstance()->Initialize(_desc->OBJECT_TAG_COUNT);
	DeviceManager::GetInstance()->Initialize(_desc->wincx, _desc->wincy, handle, _desc->windowMode);

	m_collisionManager->Initialize(_desc->COLLISION_LAYER_COUNT);
	m_resourceManager->Initialize(_desc->resourceDirectoryPath);
	m_resourceManager->CreateDefaultResource();

	RenderManager::GetInstance()->Initialize();

	m_inputManager->Initialize();
	m_lineManager->Initialize();

	
}

void Core::Run()
{
	
	m_timeManager->Tick();
	m_systemManager->Update();
	m_inputManager->Update();

	m_sceneManager->Update();
	m_sceneManager->LateUpdate();
	m_collisionManager->Update();
	m_sceneManager->PreRender();
	m_sceneManager->Render();
	m_sceneManager->PostRender();

}

void Core::SetStartScene(wstring _name)
{
	m_sceneManager->SetFirstScene(_name);
}

void Core::AddScene(wstring _name, Scene * _scene)
{
	m_sceneManager->AddScene(_name, _scene);
}



void Core::LoadScene(wstring _name)
{
	m_sceneManager->Load(_name);
}

void Core::SetInputLayoutToShader(wstring _shaderName, D3DPRIMITIVETYPE _primitive, D3DVERTEXELEMENT9 * _decl, UINT _inputLayoutSize)
{
	m_resourceManager->SetShaderInfo(_shaderName, _primitive, _decl, _inputLayoutSize);
}

void Core::DrawLine(const Vector3 & _start, const Vector3 & _end, DEBUG_COLOR _debugColor)
{
	m_lineManager->DrawLine(_start, _end, _debugColor);

}






GameObject * Core::GetPrototype(wstring _name)
{
	return m_prototypeManager->GetPrototype(_name);
}

void Core::ActivateCollisionByLayer(_COLLISION_LAYER _layer1, _COLLISION_LAYER _layer2)
{
	m_collisionManager->ActiveCollsionLayer(_layer1, _layer2);
}

GameObject * Core::FindFirstObject(_OBJECT_TAG _tag)
{
	return m_objectManager->FindFirstObjectbyTag(_tag);
}

GameObject * Core::FindObjectByName(_OBJECT_TAG _tag, wstring name)
{
	return m_objectManager->Find(_tag, name);
}

UINT Core::GetWindowWidth()
{
	return m_renderManager->GetWindowWidth();
}

UINT  Core::GetWindowHeight()
{
	return m_renderManager->GetWindowHeight();
}

HWND  Core::GetHWND()
{
	return m_deviceManager->GetHWND();
}

const wstring & Core::GetResourceDirectoryPath()
{
	return m_resourceManager->GetResourceDirectoryPath();
}

void Core::SetSkyBox(const wstring & _skyBoxName)
{
	m_lightManager->SetSkyBox(_skyBoxName);
}




LRESULT Core::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOUSEWHEEL:
		if ((short)HIWORD(wParam) < 0)
		{
			InputManager::GetInstance()->AddWheelScroll(1);
		}
		else
		{
			InputManager::GetInstance()->AddWheelScroll(-1);
		}
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;

}

