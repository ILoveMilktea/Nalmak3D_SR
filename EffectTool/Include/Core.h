#pragma once


#ifndef __CORE_H__
#define __CORE_H__

#include <windows.h>


#include "Nalmak_Struct.h"
#include "Nalmak_Define.h"
#include "Nalmak_Extern.h"
#include "Nalmak_Struct.h"

#include "SceneManager.h"
#include "PrototypeManager.h"
#include "GameObject.h"	
#include "ObjectManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "GameObject.h"
#include "LineManager.h"
#include "DebugManager.h"
#include "LightManager.h"
#include "CanvasGroup.h"

#include "BitFlag.h"
#include "Exception.h"
#include "FileIO.h"
#include "SplineCurve.h"

#include "MoveAnimation.h"
#include "RotateAnimation.h"
#include "ScaleAnimation.h"
#include "ColorAnimation.h"

#pragma region Component
#include "MeshRenderer.h"
#include "VIBufferRenderer.h"
#include "Camera.h"
#include "Transform.h"
#include "FreeMove.h"
#include "Grid.h"
#include "Text.h"
#include "SystemInfo.h"
#include "ParticleRenderer.h"
#include "DrawGizmo.h"
#include "DrawGizmo_2D.h"
#include "SphereCollider.h"
#include "StateControl.h"
#include "Button.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Terrain.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "AutoRotate.h"
#include "CanvasRenderer.h"
#include "SingleImage.h"
#include "MeshPicking.h"
#include "CanvasPicking.h"
#include "DeviceManager.h"
#include "RenderManager.h"
#include "Toggle.h"
#include "Slider.h"
#include "Number.h"
#pragma endregion

class CollisionManager;
class SystemManager;
BEGIN(Nalmak)

class NALMAK_DLL Core
{
	DECLARE_SINGLETON(Core)
private:
	Core();
	~Core();
public:

	struct Desc
	{
		UINT wincx = 1920;
		UINT wincy = 1080;
		bool windowMode = true;
		wstring startSceneName;
		wstring resourceDirectoryPath = L"../../Resource";
		_OBJECT_TAG OBJECT_TAG_COUNT = 1;
		_RENDER_LAYER RENDER_LAYER_COUNT = 1;
		_COLLISION_LAYER COLLISION_LAYER_COUNT = 1;
		_CANVAS_GROUP CANVAS_GROUP_COUNT = 1;
	};
public:
	void Initialize(HWND handle, Desc* _desc);
	void Run();

public:
	void SetStartScene(wstring _name);
	void AddScene(wstring _name, Scene* _scene);
	void LoadScene(wstring _name);
public:
	void SetInputLayoutToShader(wstring _shaderName, D3DPRIMITIVETYPE _primitive, D3DVERTEXELEMENT9* _decl, UINT _inputLayoutSize);
public:
	void DrawLine(const Vector3& _start, const Vector3& _end, DEBUG_COLOR = DEBUG_COLOR_GREEN);


public:
	template <typename T>
	void AddResource(wstring _name, const T& _resource)
	{
		m_resourceManager->AddResource(_name, _resource);
	}
public:
	GameObject* GetPrototype(wstring _name);
public:
	void ActivateCollisionByLayer(_COLLISION_LAYER _layer1, _COLLISION_LAYER _layer2);
public:
	// Search
	GameObject* FindFirstObject(_OBJECT_TAG _tag);
	GameObject* FindObjectByName(_OBJECT_TAG _tag, wstring name);
	list<GameObject*> GetObjectList(_OBJECT_TAG _tag);
	Camera* GetMainCamera();
public:
	UINT GetWindowWidth();
	UINT GetWindowHeight();
	void SetWindowSize(UINT _wincx, UINT _wincy);

public:
	HWND GetHWND();
public:
	const wstring& GetResourceDirectoryPath();


	// Environment Setting
public:
	void SetSkyBox(const wstring& _skyBoxName);
private:
	SceneManager* m_sceneManager;
	PrototypeManager* m_prototypeManager;
	ObjectManager* m_objectManager;
	InputManager* m_inputManager;
	ResourceManager* m_resourceManager;
	LineManager* m_lineManager;
	SystemManager* m_systemManager;
	DebugManager* m_debugManager;
	CollisionManager* m_collisionManager;
	LightManager* m_lightManager;
	TimeManager* m_timeManager;
	CanvasGroup* m_canvasGroup;
private:
	DeviceManager* m_deviceManager;
	RenderManager* m_renderManager;


public:
	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	

};

END


#endif
