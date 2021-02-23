#pragma once

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Nalmak_Include.h"
#include "Component.h"
#include "RenderManager.h"

BEGIN(Nalmak)
class RenderTarget;
class IRenderer;
class DepthStencil;

class NALMAK_DLL Camera :
	public Component
{
	friend class RenderManager;
public:
	struct Desc
	{
		// for perspective
		float fovY = D3DX_PI * 0.3f;
		float aspect = 0;
		// 변경시 common shader 상수 값도 바꿔주기!
		float zNear = 1.f;
		float zFar = 1000.f; 
		// for orthographic
		UINT width = 0;
		UINT height = 0; 
		// for common
		CAMERA_PROJECTION_MODE  mode = CAMERA_PROJECTION_MODE_PERSPECTIVE;
		CAMERA_RENDERING_MODE renderMode = CAMERA_RENDERING_MODE_FORWARD;
		// for clear solidColor
		D3DXCOLOR clearColor = D3DCOLOR_RGBA(40, 40, 110, 1);
		wstring skyBoxName = L"";
	};
public:
	Camera(Desc* _desc);
private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void PreRender() override;
private:
	float m_fovY;
	float m_aspect;
	float m_zNear;
	float m_zFar;
	float m_width;
	float m_height;
	D3DXCOLOR m_clearColor;
	Matrix m_projMatrix;

	CAMERA_PROJECTION_MODE m_mode;
	CAMERA_RENDERING_MODE m_renderingMode;
	BitFlag<_RENDER_LAYER> m_layer;
public:
	const Matrix GetViewMatrix() const;
	const Matrix& GetProjMatrix() { return m_projMatrix; }
	const Matrix GetViewportMatrix() const;
	Vector2 WorldToScreenPos(const Vector3& _pos);


	vector<RenderTarget*>& GetRenderTargets() { return m_renderTargets; }
	bool CompareLayer(_RENDER_LAYER _layer) { return m_layer.Check(_layer); }
	bool IsInFrustumCulling(IRenderer* _transform);
	bool IsInFrustumCulling(const Vector3& _pos,float _radius);

	const float GetFovY() const { return m_fovY; }
	Vector3 GetCamToMouseWorldDirection();

public:
	void SetRenderTarget(UINT _index,wstring  _rtName);

	void RecordRenderTarget();
	void EndRenderTarget();	

	CAMERA_RENDERING_MODE GetRenderingMode() { return m_renderingMode; }
public:
	void AllOnLayer();
	void AllOffLayer();
	void OnLayer(_RENDER_LAYER _layer);
	void OffLayer(_RENDER_LAYER _layer);
private:
	vector<RenderTarget*> m_renderTargets;
	D3DXPLANE m_frustumPlane[6];
private:
	void UpdateFrustumPlane();
	void UpdateProjMatrix();

private:
	HWND m_handle;
	// Component을(를) 통해 상속됨
};
END
#endif // !__CAMERA_H__
