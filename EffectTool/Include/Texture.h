#pragma once

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "IResource.h"

BEGIN(Nalmak)
class NALMAK_DLL Texture :
	public IResource
{
	friend class ResourceManager;
private:
	explicit Texture();
	~Texture();
private:
	// IResource을(를) 통해 상속됨
	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;

public:
	PDIRECT3DTEXTURE9 GetTexure(size_t _index);
	size_t GetSpriteCount()const { return m_textures.size(); }
private:
	vector<PDIRECT3DTEXTURE9> m_textures;
};
END
#endif // !__TEXTURE_H__
