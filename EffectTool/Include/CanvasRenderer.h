#pragma once
#ifndef __CANVASRENDERER_H__
#define __CANVASRENDERER_H__


#include "IRenderer.h"

class Texture;
class Animator;
class NALMAK_DLL CanvasRenderer :
	public IRenderer
{
public:
	struct Desc
	{
	};
	CanvasRenderer(Desc* _desc);

private:
	// MeshRenderer을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
public:
	virtual void Render() override;
	virtual void BindingStreamSource() override;

public:
	void UpdateBoundary();

	void SetImage(Texture* _Image) { m_targetImage = _Image; }
	void SetColor(Vector4 _color) { m_color = _color; }
	RECT* GetBoundary();

private:
	Animator* m_animator = nullptr;
	Texture* m_targetImage = nullptr;
	Vector4 m_color;

	Vector3 m_observedPosition;
	Vector3 m_observedScale;
	RECT m_boundary;
};



#endif // !__CANVASRENDERER_H__

