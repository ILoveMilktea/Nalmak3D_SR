#pragma once
#ifndef __CANVASRENDERER_H__
#define __CANVASRENDERER_H__


#include "IRenderer.h"
#include "ICanvasGroup.h"

class Texture;
class Animator;
class NALMAK_DLL CanvasRenderer :
	public IRenderer, public ICanvasGroup
{
public:
	struct Desc
	{
		wstring mtrlName = L"defaultUI";
		_CANVAS_GROUP group = 0;
	};
	CanvasRenderer();
	CanvasRenderer(Desc* _desc);
	
private:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
public:
	virtual void Render() override;
	virtual void BindingStreamSource() override;

	void Render_Image();
	void Render_Text();
	void Render_Number();
public:
	void UpdateBoundary();
	bool IsCursorOnRect();

	void SetImage(IDirect3DBaseTexture9* _Image) { m_targetImage = _Image; }
	void SetColor(Vector4 _color) { m_color = _color; }

	RECT* GetBoundary() { return &m_boundary; }

public:
	// ICanvasGroup
	virtual void SetFade(float _alpha) override;
	virtual void SetInteractive(bool _value) override;
	virtual void SetBlockPicking(bool _value) override;

	void SetGroup(_CANVAS_GROUP _group);
	_CANVAS_GROUP GetGroup() { return m_group; }

	bool MouseClickDown();
	bool MouseClickPress();
	bool MouseClickUp_InRect();
	bool MouseClickUp_OutRect();

private:
	InputManager* m_input;

private:
	Animator* m_animator = nullptr;
	IDirect3DBaseTexture9* m_targetImage = nullptr;
	Vector4 m_color;

	Vector3 m_observedPosition;
	Vector3 m_observedScale;

	RECT m_boundary;
};



#endif // !__CANVASRENDERER_H__

