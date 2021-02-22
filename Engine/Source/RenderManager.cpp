#include "RenderManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "DeviceManager.h"
#include "IRenderer.h"
#include "Camera.h"
#include "Transform.h"
#include "Material.h"
#include "RenderTarget.h"
#include "Shader.h"
#include "VIBuffer.h"
#include "GameObject.h"
#include "Text.h"
#include "DebugManager.h"
#include "MeshRenderer.h"
#include "LightManager.h"
#include "PointLight.h"
#include "Transform.h"

USING(Nalmak)
IMPLEMENT_SINGLETON(RenderManager)
RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
	Release();
}

void RenderManager::Release()
{
	m_device = nullptr;
	m_cameraList.clear();
}

void RenderManager::Initialize()
{
	m_device = DeviceManager::GetInstance()->GetDevice();
	m_debugManager = DebugManager::GetInstance();
	m_lightManager = LightManager::GetInstance();
	m_resourceManager = ResourceManager::GetInstance();

	m_renderingMode = RENDERING_MODE_MAX;
	m_blendingMode = BLENDING_MODE_MAX;

	m_currentMaterial = nullptr;
	m_currentShader = nullptr;
	m_currentVIBuffer = nullptr;

	m_cameraList.clear();

	for (int i = 0; i < 4; ++i)
		m_currentRenderTarget[i] = nullptr;

	D3DVIEWPORT9 vp = { 0,0,m_wincx,m_wincy,0,1 };
	m_device->SetViewport(&vp);

	m_imageVIBuffer = ResourceManager::GetInstance()->GetResource<VIBuffer>(L"quadNoneNormal");
	m_currentUIMaterial = ResourceManager::GetInstance()->GetResource<Material>(L"defaultUI");
}

void RenderManager::Render()
{

	ThrowIfFailed(m_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, m_cameraList.front()->m_clearColor, 1, 0));

	for (auto& cam : m_cameraList)
	{
		if (cam->GetActive())
		{
			Render(cam);
		}
	}
	RenderText();
	ThrowIfFailed(m_device->Present(nullptr, nullptr, 0, nullptr));

	for (auto& renderList : m_renderOpaqueLists)
		renderList.second.clear();

}

void RenderManager::Render(Camera * _cam)
{



	///////////////////////////////////////////////////////
	// 공용 상수버퍼
	ConstantBuffer cBuffer;
	Matrix view = _cam->GetViewMatrix();
	Matrix proj = _cam->GetProjMatrix();
	Matrix invView;
	D3DXMatrixInverse(&invView, nullptr, &view);
	//D3DXMatrixTranspose(&invView, &invView);
	Matrix invProj;
	D3DXMatrixInverse(&invProj, nullptr, &proj);
	//D3DXMatrixTranspose(&invProj, &invProj);

	cBuffer.viewProj = view * proj;
	cBuffer.worldCamPos = _cam->GetTransform()->GetWorldPosition();
	cBuffer.invView = invView;
	cBuffer.invProj = invProj;

	////////////////////////////////////////////////////////
	ThrowIfFailed(m_device->BeginScene());
	DeferredRender(_cam, cBuffer);
	ThrowIfFailed(m_device->EndScene());


}

void RenderManager::RenderText()
{
	for (auto& text : m_textRenderList)
	{
		text->m_font->DrawTextW(
			nullptr,
			text->m_text.c_str(),
			-1,
			text->GetBoundary(),
			text->m_option,
			text->m_color
		);
	}
	m_textRenderList.clear();
	m_debugManager->EraseTheRecord();
}

void RenderManager::Reset()
{
	m_currentMaterial = nullptr;

	m_cameraList.clear();
	for (auto& renderList : m_renderOpaqueLists)
		renderList.second.clear();
	for (auto& renderList : m_renderTransparentLists)
		renderList.second.clear();
}

void RenderManager::SkyboxPass(ConstantBuffer & _cBuffer)
{
	m_currentShader = nullptr;
	m_currentMaterial = nullptr;


	auto viBuffer = m_lightManager->GetSkyboxVIBuffer();

	UpdateMaterial(m_lightManager->GetSkyboxMaterial(), _cBuffer);
	UpdateRenderTarget();
	ThrowIfFailed(m_device->SetStreamSource(0, viBuffer->GetVertexBuffer(), 0, m_currentShader->GetInputLayoutSize()));
	ThrowIfFailed(m_device->SetIndices(viBuffer->GetIndexBuffer()));

	ThrowIfFailed(m_device->SetStreamSource(0, viBuffer->GetVertexBuffer(), 0,sizeof(INPUT_LAYOUT_SKYBOX)));
	ThrowIfFailed(m_device->SetIndices(viBuffer->GetIndexBuffer()));

	m_currentShader->CommitChanges();
	ThrowIfFailed(m_device->DrawIndexedPrimitive(m_currentShader->GetPrimitiveType(), 0, 0, viBuffer->GetVertexCount(), 0, viBuffer->GetFigureCount()));

	if (m_currentShader)
	{
		m_currentShader->EndPass();
		EndRenderTarget();
	}

}

void RenderManager::DeferredRender(Camera* _cam, ConstantBuffer& _cBuffer)
{
	ClearRenderTarget(L"GBuffer_Diffuse");
	ClearRenderTarget(L"GBuffer_Normal");
	ClearRenderTarget(L"GBuffer_Depth");
	ClearRenderTarget(L"GBuffer_Position");
	ClearRenderTarget(L"GBuffer_Light");
	ClearRenderTarget(L"GBuffer_Shade");

	SkyboxPass(_cBuffer);

	GBufferPass(_cam, _cBuffer); // GBuffer -> Gemotry 를 그림 -> 기하도형

	LightPass(_cam,_cBuffer); // 위에서 그린정보를 바탕으로 빛 연산 (하나의 텍스쳐)

	ShadePass(_cBuffer); // GBuffer + Lightpass 합성

	RenderImageToScreen(m_resourceManager->GetResource<RenderTarget>(L"GBuffer_Diffuse")->GetTexture(), _cBuffer); // 원래화면에 띄워줌

	TransparentPass(_cBuffer); // 투명객체를 그림
}

void RenderManager::GBufferPass(Camera * _cam, ConstantBuffer& _cBuffer)
{
	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	for (auto& MeshRendererList : m_renderOpaqueLists)
	{
		for (auto& renderer : MeshRendererList.second)
		{
			if (_cam->CompareLayer(renderer->GetLayer()))
			{
				if (_cam->IsInFrustumCulling(renderer))
				{
					Material* material = renderer->GetMaterial();
					UpdateMaterial(material, _cBuffer);
					UpdateRenderTarget();

					UpdateVIBuffer(renderer);

					renderer->Render();
				}
			}
		}
	}

	if (m_currentShader)
	{
		m_currentShader->EndPass();
		EndRenderTarget();
	}



}

void RenderManager::LightPass(Camera* _cam, ConstantBuffer& _cBuffer)
{


	PointLightPass(_cam,_cBuffer);

	DirectionalLightPass(_cBuffer);

}

void RenderManager::PointLightPass(Camera* _cam, ConstantBuffer & _cBuffer)
{
	size_t count = m_lightManager->GetPointLightCount();

	VIBuffer* viBuffer = m_resourceManager->GetResource<VIBuffer>(L"sphere");
	Material* mtrlStencilLight = m_resourceManager->GetResource<Material>(L"PointLight_Stencil");
	Material* mtrlLight = m_resourceManager->GetResource<Material>(L"PointLight");

	mtrlStencilLight->SetDataToShader();
	mtrlLight->SetDataToShader();

	m_device->SetRenderState(D3DRS_STENCILENABLE, true);
	m_device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP::D3DSTENCILOP_KEEP);
	m_device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP::D3DSTENCILOP_DECR);
	m_device->SetRenderState(D3DRS_CCW_STENCILPASS, D3DSTENCILOP::D3DSTENCILOP_KEEP);
	m_device->SetRenderState(D3DRS_CCW_STENCILZFAIL, D3DSTENCILOP::D3DSTENCILOP_INCR);


	ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_ADD));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_ONE));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_ONE));

	ThrowIfFailed(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILLMODE::D3DFILL_SOLID));

	ThrowIfFailed(m_device->SetStreamSource(0, viBuffer->GetVertexBuffer(), 0, sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV)));
	ThrowIfFailed(m_device->SetIndices(viBuffer->GetIndexBuffer()));

	for (int i = 0; i < count; ++i)
	{
		auto pointLight = m_lightManager->GetPointLight(i);

		Matrix world;
		Vector3 pos = pointLight->GetTransform()->GetWorldPosition();
		float scale = pointLight->GetRadius();
		pointLight->SetLightPosition(pos);

		Matrix matTrs, matScale;
		D3DXMatrixTranslation(&matTrs, pos.x, pos.y, pos.z);
		D3DXMatrixScaling(&matScale, scale, scale, scale);
		world = matScale * matTrs;

		if (_cam->IsInFrustumCulling(pos, scale))
		{
			PointLightPass(world, pointLight->GetLightInfo(), viBuffer, _cBuffer, mtrlStencilLight, mtrlLight);
			m_device->Clear(0, nullptr, D3DCLEAR_STENCIL, 0, 1, 0);
		}
	}
	m_device->SetRenderState(D3DRS_STENCILENABLE, false);
	m_device->SetRenderState(D3DRS_ZENABLE, true);
	m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}



void RenderManager::PointLightPass(const Matrix& _matWorld, PointLightInfo _lightInfo, VIBuffer* _viBuffer, ConstantBuffer & _cBuffer, Material* _mtrlStencilLight, Material* _mtrlLight)
{
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));

	UpdateShader(_mtrlStencilLight->GetShader(), _cBuffer);

	UpdateRenderTarget();

	m_device->SetRenderState(D3DRS_ZENABLE, true);
	m_device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	m_device->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, true);

	m_currentShader->SetMatrix("g_world", _matWorld);
	m_currentShader->CommitChanges();
	ThrowIfFailed(m_device->DrawIndexedPrimitive(m_currentShader->GetPrimitiveType(), 0, 0, _viBuffer->GetVertexCount(), 0, _viBuffer->GetFigureCount()));

	if (m_currentShader)
	{
		m_currentShader->EndPass();
		EndRenderTarget();
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true));

	UpdateShader(_mtrlLight->GetShader(), _cBuffer);

	UpdateRenderTarget();

	m_device->SetRenderState(D3DRS_ZENABLE, false);
	m_device->SetRenderState(D3DRS_ZWRITEENABLE, true);
	m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	m_device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_NOTEQUAL);
	m_device->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, false);

	m_currentShader->SetValue("g_pointLight", &_lightInfo, sizeof(PointLightInfo));
	m_currentShader->SetMatrix("g_world", _matWorld);

	m_currentShader->CommitChanges();
	ThrowIfFailed(m_device->DrawIndexedPrimitive(m_currentShader->GetPrimitiveType(), 0, 0, _viBuffer->GetVertexCount(), 0, _viBuffer->GetFigureCount()));

	if (m_currentShader)
	{
		m_currentShader->EndPass();
		EndRenderTarget();
	}
}

void RenderManager::ShadePass(ConstantBuffer & _cBuffer)
{
	RecordRenderTarget(0, L"GBuffer_Shade");

	Material* material = m_resourceManager->GetResource<Material>(L"GBuffer_Shade");
	RenderByMaterialToScreen(material, _cBuffer);

	EndRenderTarget(L"GBuffer_Shade");

}


void RenderManager::DirectionalLightPass(ConstantBuffer& _cBuffer)
{
	DirectionalLightInfo info;
	if (!m_lightManager->GetDirectionalLightInfo(info))
		return;
	Material* material = m_resourceManager->GetResource<Material>(L"DirectionalLight");
	material->SetValue("g_directionalLight", &info, sizeof(DirectionalLightInfo));

	RecordRenderTarget(0, L"GBuffer_Light");

	RenderByMaterialToScreen(material, _cBuffer);

	EndRenderTarget(L"GBuffer_Light");
}


void RenderManager::TransparentPass(ConstantBuffer& _cBuffer)
{
}


void RenderManager::RenderByMaterialToScreen(Material* _mtrl, ConstantBuffer & _cBuffer)
{
	m_currentMaterial = nullptr;
	m_currentShader = nullptr;

	UpdateMaterial(_mtrl, _cBuffer);

	Matrix mat;
	D3DXMatrixScaling(&mat, 2, 2, 2);
	m_currentShader->SetMatrix("g_world", mat);

	ThrowIfFailed(m_device->SetStreamSource(0, m_imageVIBuffer->GetVertexBuffer(), 0, m_currentShader->GetInputLayoutSize()));
	ThrowIfFailed(m_device->SetIndices(m_imageVIBuffer->GetIndexBuffer()));

	m_currentShader->CommitChanges();
	ThrowIfFailed(m_device->DrawIndexedPrimitive(m_currentShader->GetPrimitiveType(), 0, 0, m_imageVIBuffer->GetVertexCount(), 0, m_imageVIBuffer->GetFigureCount()));

	if (m_currentShader)
	{
		m_currentShader->EndPass();
	}

}

void RenderManager::RenderImageToScreen(IDirect3DBaseTexture9 * _tex, ConstantBuffer & _cBuffer)
{
	m_currentShader = nullptr;
	m_currentMaterial = nullptr;



	UpdateMaterial(m_currentUIMaterial, _cBuffer);
	m_currentShader->SetTexture("g_mainTex", _tex);
	Matrix mat;
	D3DXMatrixScaling(&mat, 2, 2, 2);
	m_currentShader->SetMatrix("g_world", mat);

	ThrowIfFailed(m_device->SetStreamSource(0, m_imageVIBuffer->GetVertexBuffer(), 0, m_currentShader->GetInputLayoutSize()));
	ThrowIfFailed(m_device->SetIndices(m_imageVIBuffer->GetIndexBuffer()));

	m_currentShader->CommitChanges();
	ThrowIfFailed(m_device->DrawIndexedPrimitive(m_currentShader->GetPrimitiveType(), 0, 0, m_imageVIBuffer->GetVertexCount(), 0, m_imageVIBuffer->GetFigureCount()));

	if (m_currentShader)
	{
		m_currentShader->EndPass();
	}

}



void RenderManager::RenderRequest(IRenderer * _render)
{
	auto mtrl = _render->GetMaterial();
	if (mtrl->GetRenderingMode() != RENDERING_MODE_TRANSPARENT)
		m_renderOpaqueLists[mtrl->GetRenderQueue()].emplace_back(_render);
	else
		m_renderTransparentLists[mtrl->GetRenderQueue()].emplace_back(_render);

}

void RenderManager::RenderRequest(Text * _text)
{
	assert("text is nullptr!" && _text);
	m_textRenderList.emplace_back(_text);
}

void RenderManager::AddCamera(Camera * _cam)
{
	assert("Camera is nullptr " && _cam);
	m_cameraList.emplace_back(_cam);
}

void RenderManager::AddCamera(GameObject * _cam)
{
	AddCamera(_cam->GetComponent<Camera>());
}

void RenderManager::UpdateMaterial(Material * _material, ConstantBuffer & _cBuffer)
{
	if (m_currentMaterial != _material)
	{
		m_currentMaterial = _material;

		UpdateRenderingMode(_material);
		UpdateBlendingMode(_material);
		UpdateFillMode(_material);
		_material->SetDataToShader();

		UpdateShader(m_currentMaterial->GetShader(), _cBuffer);
	}
}

void RenderManager::UpdateRenderingMode(Material * _material)
{
	auto mode = _material->GetRenderingMode();
	if (m_renderingMode != mode)
	{
		m_renderingMode = mode;

		switch (mode)
		{
		case RENDERING_MODE_OPAQUE:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHATESTENABLE, false));
			break;
		case RENDERING_MODE_CUTOUT:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHATESTENABLE, true));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHAREF, 50));
			break;
		case RENDERING_MODE_TRANSPARENT:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHATESTENABLE, false));
			break;
		default:
			break;
		}
	}
}

void RenderManager::UpdateBlendingMode(Material * _material)
{

	auto mode = _material->GetBlendingMode();
	if (m_blendingMode != mode)
	{
		m_blendingMode = mode;
		switch (mode)
		{
		case BLENDING_MODE_DEFAULT:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_ADD));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_SRCALPHA));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_INVSRCALPHA));

			break;
		case BLENDING_MODE_ADDITIVE:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_ADD));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_ONE));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_ONE));
			break;
		case BLENDING_MODE_SUBTRACTIVE:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_REVSUBTRACT));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_ONE));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_ONE));
			break;
		case BLENDING_MODE_MULTIPLY:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_ADD));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_SRCCOLOR));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_DESTCOLOR));
			break;
		default:
			break;
		}
	}
}

void RenderManager::UpdateFillMode(Material * _material)
{
	auto fillMode = _material->GetFillMode();
	if (m_fillMode != fillMode)
	{
		m_fillMode = fillMode;

		switch (m_fillMode)
		{
		case FILL_MODE_SOLID:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILLMODE::D3DFILL_SOLID));
			break;
		case FILL_MODE_WIREFRAME:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILLMODE::D3DFILL_WIREFRAME));
			break;
		case FILL_MODE_POINT:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILLMODE::D3DFILL_POINT));

			break;
		default:
			break;
		}
	}

}



void RenderManager::UpdateVIBuffer(IRenderer * _renderer)
{
	auto viBuffer = _renderer->GetVIBuffer();
	_renderer->BindingStreamSource();
}

void RenderManager::UpdateRenderTarget()
{

	for (int i = 0; i < 4; ++i)
	{
		RenderTarget* newRendertarget = m_currentShader->GetRenderTarget(i);

		if (!newRendertarget)
			return;

		if (m_currentRenderTarget[i] != newRendertarget)
		{
			if (m_currentRenderTarget[i])
				m_currentRenderTarget[i]->EndRecord();

			m_currentRenderTarget[i] = newRendertarget;
			m_currentRenderTarget[i]->StartRecord(i);
		}

	}
}


void RenderManager::EndRenderTarget()
{
	for (int i = 0; i < 4; ++i)
	{
		if (m_currentRenderTarget[i])
		{
			m_currentRenderTarget[i]->EndRecord();
			m_currentRenderTarget[i] = nullptr;
		}
	}
}

void RenderManager::UpdateShader(Shader * _shader, ConstantBuffer& _cBuffer)
{
	if (m_currentShader != _shader)
	{
		if (m_currentShader)
			m_currentShader->EndPass();

		m_currentShader = _shader;


		m_currentShader->SetValue("g_cBuffer", &_cBuffer, sizeof(ConstantBuffer));
		m_currentShader->BeginPass();

		ThrowIfFailed(m_device->SetVertexDeclaration(m_currentShader->GetDeclartion()));



	}
}

void RenderManager::RecordRenderTarget(UINT _index, const wstring & _name)
{
	m_resourceManager->GetResource<RenderTarget>(_name)->StartRecord(_index);
}

void RenderManager::EndRenderTarget(const wstring & _name)
{
	m_resourceManager->GetResource<RenderTarget>(_name)->EndRecord();
}

void RenderManager::SetWindowSize(UINT _x, UINT _y)
{
	m_wincx = _x;
	m_wincy = _y;

	m_halfWincx = (UINT)(m_wincx * 0.5f);
	m_halfWincy = (UINT)(m_wincy * 0.5f);
}

Camera * RenderManager::GetMainCamera()
{
	if (m_cameraList.size() > 0)
		return m_cameraList.front();
	return nullptr;
}

void RenderManager::DeleteCamera(Camera * _cam)
{
	if (!m_device)
		return;

	if (m_cameraList.size() == 0)
		return;

	for (auto iter = m_cameraList.begin(); iter != m_cameraList.end(); ++iter)
	{
		if ((*iter) == _cam)
		{
			//(*iter) = nullptr;
			m_cameraList.erase(iter);
			return;
		}
	}
}

void RenderManager::ClearRenderTarget(const wstring & _targetName)
{
	m_resourceManager->GetResource<RenderTarget>(_targetName)->Clear();
}
