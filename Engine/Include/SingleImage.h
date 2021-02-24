#pragma once

#ifndef __SINGLEIMAGE_H__
#define __SINGLEIMAGE_H__

#include "IRenderer.h"

class Texture;
class CanvasRenderer;

class NALMAK_DLL SingleImage :
	public Component
{
public:
	struct Desc
	{
		wstring textureName = L"UIWhite";
	};
	SingleImage(Desc* _desc);

protected:
	virtual void Initialize() override;
	virtual void Update() override;

public:
	void SetTexture(wstring _name);
	void SetTexture(IDirect3DBaseTexture9* _tex);

public:
	IDirect3DBaseTexture9* GetTexture();
	
private:
	IDirect3DBaseTexture9* m_image;
	CanvasRenderer* m_renderer;

};



#endif // !__CANVASRENDERER_H__



//canvas -> localface
