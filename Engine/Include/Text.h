#pragma once

#ifndef __TEXT_H__
#define __TEXT_H__


#include "Component.h"

class CanvasRenderer;
class NALMAK_DLL Text :
	public Component
{
	friend class RenderManager;
public:
	struct Desc
	{
		UINT width = 12;
		UINT height = 21;
		UINT weight = 500; // 0 ~ 1000
		DWORD option = DT_CENTER | DT_WORDBREAK;
		const TCHAR* fontName = L"Consolas";
		wstring text = L"default";
		D3DCOLOR color = D3DCOLOR_RGBA(255, 255, 255, 255);
	};
	Text(Desc* _desc);
private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void PreRender() override;
	virtual void Release() override;
public:
	void RenderText();

	void SetText(wstring _text) { m_text = _text; }
	void SetColor(const D3DXCOLOR& _color) { m_color = _color; }
	void SetAlpha(float _alpha) { m_color.a = _alpha; }

	RECT* GetBoundary();


private:
	LPD3DXFONT m_font = nullptr;
	PDIRECT3DDEVICE9 m_device = nullptr;
	RenderManager* m_render = nullptr;
	CanvasRenderer* m_renderer = nullptr;

private:
	UINT m_width;
	UINT m_height;
	UINT m_weight;
	DWORD m_option;
	D3DXCOLOR m_color;
	const TCHAR* m_fontName;
	wstring m_text;
};

#endif // !__TEXT_H__
