#include "..\Include\Text.h"
#include "RenderManager.h"


Text::Text(Desc * _desc)
{
	m_width = _desc->width;
	m_height = _desc->height;
	m_weight = _desc->weight;
	m_weight = Nalmak_Math::Clamp<UINT>(m_weight, 0, 1000);
	m_fontName = _desc->fontName;
	m_option = _desc->option;
	m_textBoundary.left = _desc->textBoundary.left;
	m_textBoundary.right = _desc->textBoundary.right;
	m_textBoundary.top = -_desc->textBoundary.top;
	m_textBoundary.bottom = -_desc->textBoundary.bottom;

	m_text = _desc->text;
	m_color = _desc->color;
	

}

void Text::Initialize()
{
	m_render = RenderManager::GetInstance();
	m_device = DeviceManager::GetInstance()->GetDevice();

	D3DXFONT_DESCW fontDesc;
	ZeroMemory(&fontDesc, sizeof(D3DXFONT_DESCW));
	fontDesc.Height = m_height;
	fontDesc.Width = m_width;
	fontDesc.Weight = m_weight;
	fontDesc.CharSet = HANGUL_CHARSET;
	lstrcpy(fontDesc.FaceName, m_fontName);
	ThrowIfFailed(D3DXCreateFontIndirect(m_device, &fontDesc, &m_font));

}

void Text::Update()
{
}

void Text::LateUpdate()
{
}

void Text::PreRender()
{
	m_render->RenderRequest(this);
}



void Text::Release()
{
	if(m_font)
		m_font->Release();
}

