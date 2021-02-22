#pragma once
#ifndef __MESHPICKING_H__
#define __MESHPICKING_H__

#include "Component.h"

class Camera;
class DrawGizmo;
class MeshRenderer;
class NALMAK_DLL MeshPicking :
	public Component
{
public:
	struct Desc
	{
	};
public:
	MeshPicking(Desc* _desc);

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;

	bool IsMousePicking();

private:
	Camera* m_mainCam;
	MeshRenderer* m_renderer;
	DrawGizmo* m_gizmo;
};



#endif // !__MESHPICKING_H__

