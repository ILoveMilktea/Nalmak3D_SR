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
	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;

public:
	void SetTexture(wstring _name);

public:
	IDirect3DBaseTexture9* GetTexture();
	RECT* GetBoundary();

	
private:
	Texture* m_image;
	CanvasRenderer* m_renderer;

};



#endif // !__CANVASRENDERER_H__



//canvas -> �׳� ��ǥ�� ����
// �̹����� material �����ؼ� �̹����� �ٲ��شٰ�?