#include "..\Include\Texture.h"



USING(Nalmak)

Texture::Texture()
{
}


Texture::~Texture()
{
	Release();
}

void Texture::Initialize(wstring _fp)
{
	PDIRECT3DTEXTURE9 tex = nullptr;

	D3DXIMAGE_INFO info;
	ThrowIfFailed(D3DXGetImageInfoFromFile(_fp.c_str(), &info));
	ThrowIfFailed(D3DXCreateTextureFromFileEx(
		m_device,
		_fp.c_str(),
		info.Width,
		info.Height,
		info.MipLevels,
		0,
		info.Format,
		D3DPOOL_MANAGED,
		D3DX_FILTER_LINEAR,
		D3DX_DEFAULT,
		0,
		nullptr,
		nullptr,
		&tex));
	m_textures.emplace_back(tex);
}

void Texture::Release()
{
	for (auto& tex : m_textures)
	{
		SAFE_RELEASE(tex);
	}
	m_textures.clear();
	m_textures.shrink_to_fit();
}

PDIRECT3DTEXTURE9 Texture::GetTexure(size_t _index)
{
	PDIRECT3DTEXTURE9 tex = nullptr;
	if (_index < m_textures.size())
		tex = m_textures[_index];
	else
		tex = m_textures.back();
	return tex;
}
