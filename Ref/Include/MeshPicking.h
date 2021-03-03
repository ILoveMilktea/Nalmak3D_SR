#pragma once
#ifndef __MESHPICKING_H__
#define __MESHPICKING_H__

#include "Component.h"

class Camera;
class DrawGizmo;
class PositionHandle;
class VIBufferRenderer;
class NALMAK_DLL MeshPicking :
	public Component
{
public:
	struct Desc
	{
	};
public:
	MeshPicking(Desc* _desc);

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;

	bool IsMousePicking();

private:
	Camera* m_mainCam;
	VIBufferRenderer* m_renderer;

	
	DrawGizmo* m_gizmo;
	PositionHandle* m_handle;
};



#endif // !__MESHPICKING_H__

