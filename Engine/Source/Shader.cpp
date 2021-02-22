#include "..\Include\Shader.h"
#include "RenderTarget.h"
#include "ResourceManager.h"

#include <fstream>

USING(Nalmak)



Shader::Shader()
{
	m_inputLayoutSize = 0;
	m_effect = nullptr;
	m_decl = nullptr;
}


Shader::~Shader()
{
	Release();
}

void Shader::Initialize(wstring _fp)
{
	for(int i = 0 ; i < 4;  ++i)
		m_renderTarget[i] = nullptr;

	VERTEX_INPUT_LAYOUT vertexInputLayout;
	DRAW_PRIMITIVE_TYPE primitiveType;

	string path;
	path.assign(_fp.begin(), _fp.end());

	ifstream file(path.c_str());

	string buffer;
	size_t length = 0;

	int renderTargetIndex = 0;
	while (true)
	{
		getline(file, buffer);
		if ('#' == buffer[0] || "" == buffer)
			continue;

		// 항목 확인
		size_t firstWordEnd;
		for (firstWordEnd = 0; firstWordEnd < buffer.size(); ++firstWordEnd)
		{
			if (' ' == buffer[firstWordEnd])
				break;
		}

		string memberName = buffer.substr(0, firstWordEnd);

		// 다음 " 찾기
		while ('\"' != buffer[firstWordEnd])
		{
			++firstWordEnd;
		}
		++firstWordEnd;


		// 1. input layout
		if (strcmp(memberName.c_str(), "inputLayout") == 0)
		{
			// handle name
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}
			string handleName = buffer.substr(firstWordEnd, handleNameEnd - firstWordEnd);

			vertexInputLayout = (VERTEX_INPUT_LAYOUT)atoi(handleName.c_str());
		}

		// 2. render target
		if (strcmp(memberName.c_str(), "renderTarget") == 0)
		{
			// handle name
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}
			string handleName = buffer.substr(firstWordEnd, handleNameEnd - firstWordEnd);
			wstring name;
			name.assign(handleName.begin(), handleName.end());
			AddRenderTarget(renderTargetIndex, name);
			++renderTargetIndex;
		}

		// 3. draw primitive
		if (strcmp(memberName.c_str(), "primitive") == 0)
		{
			// handle name
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}
			string handleName = buffer.substr(firstWordEnd, handleNameEnd - firstWordEnd);

			primitiveType = (DRAW_PRIMITIVE_TYPE)atoi(handleName.c_str());

			break;
		}
	}

	
	D3DPRIMITIVETYPE d3dprimitiveType;

	switch (primitiveType)
	{
	case DRAW_PRIMITIVE_TYPE_POINTLIST:
		d3dprimitiveType = D3DPRIMITIVETYPE::D3DPT_POINTLIST;
		break;
	case DRAW_PRIMITIVE_TYPE_LINELIST:
		d3dprimitiveType = D3DPRIMITIVETYPE::D3DPT_LINELIST;
		break;
	case DRAW_PRIMITIVE_TYPE_TRIANGLELIST:
		d3dprimitiveType = D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST;
		break;
	default:
		break;
	}

	switch (vertexInputLayout)
	{
	case VERTEX_INPUT_LAYOUT_POSITION:
	{
		D3DVERTEXELEMENT9 decl[] =
		{
			{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },

			D3DDECL_END()
		};
		SetInputLayout(d3dprimitiveType, decl, sizeof(INPUT_LAYOUT_POSITION));
	}
	break;
	case VERTEX_INPUT_LAYOUT_POSITION_UV:
	{
		D3DVERTEXELEMENT9 decl[] =
		{
			{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0,12,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,0 },
			D3DDECL_END()
		};
		SetInputLayout(d3dprimitiveType, decl, sizeof(INPUT_LAYOUT_POSITION_UV));
	}
		break;
	case VERTEX_INPUT_LAYOUT_POSITION_NORMAL_UV:
	{
		D3DVERTEXELEMENT9 decl[] =
		{
			{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0,12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,  0 },
			{ 0,24,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,0 },
			D3DDECL_END()
		};
		SetInputLayout(d3dprimitiveType, decl, sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV));
	}
		break;
	case VERTEX_INPUT_LAYOUT_SKYBOX:
	{
		D3DVERTEXELEMENT9 decl[] =
		{
			{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0,12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },

			D3DDECL_END()
		};
		SetInputLayout(d3dprimitiveType, decl, sizeof(INPUT_LAYOUT_SKYBOX));
	}
		break;
	case VERTEX_INPUT_LAYOUT_PARTICLE:
	{
		D3DVERTEXELEMENT9 decl[] =
		{
			{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0,12,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,0 },
			{ 1,0,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },
			{ 1,16,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },
			{ 1,32,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },
			{ 1,48,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 },
			{ 1,64,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 5 },
			D3DDECL_END()
		};
		SetInputLayout(d3dprimitiveType, decl, sizeof(INPUT_LAYOUT_PARTICLE));

	}
		break;
	
	default:
		break;
	}

	LPD3DXBUFFER error = NULL;
	DWORD dwShaderFlags = 0;

#if _DEBUG
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

	wstring fxCompilePath = _fp.substr(0, _fp.size() - 2);
	fxCompilePath += L"fx";
	D3DXCreateEffectFromFile(
		m_device,
		fxCompilePath.c_str(),
		nullptr, // 전처리기
		nullptr,
		dwShaderFlags,		 // 컴파일 플래그
		NULL,
		&m_effect,
		&error
	);


	if (error)
	{
		void* ack = error->GetBufferPointer();
		MessageBoxA(nullptr, (char*)ack, "Shader Compile Fail", MB_OK);

		assert(!error);
	}


}

HRESULT Shader::CheckShaderInitialize()
{
	if (!m_decl)
		return E_FAIL;

	if (!m_effect)
		return E_FAIL;

	if (m_inputLayoutSize == 0)
		return E_FAIL;

	return S_OK;
}

void Shader::Release()
{
	SAFE_RELEASE(m_effect);
}

void Shader::SetBool(const string& _parameter, bool _value)
{
	ThrowIfFailed(m_effect->SetBool(_parameter.c_str(), _value));
}

void Shader::SetInt(const string& _parameter, int _value)
{
	ThrowIfFailed(m_effect->SetInt(_parameter.c_str(), _value));
}

void Shader::SetFloat(const string& _parameter, float _value)
{
	ThrowIfFailed(m_effect->SetFloat(_parameter.c_str(), _value));
}

void Shader::SetMatrix(const string& _parameter, const Matrix & _value)
{
	ThrowIfFailed(m_effect->SetMatrix(_parameter.c_str(), &_value));
}

void Shader::SetTexture(const string& _parameter, IDirect3DBaseTexture9* _value)
{
	ThrowIfFailed(m_effect->SetTexture(_parameter.c_str(), _value));
}

void Shader::SetVector(const string& _parameter, const Vector4 & _vec)
{
	ThrowIfFailed(m_effect->SetVector(_parameter.c_str(), &_vec));
}

void Shader::SetVector(const string& _parameter, const Vector2 & _vec)
{
	float arr[2];
	arr[0] = _vec.x;
	arr[1] = _vec.y;
	ThrowIfFailed(m_effect->SetFloatArray(_parameter.c_str(), arr, 2));
}

void Shader::SetValue(const string& _parameter, void * value, UINT UINT)
{
	m_effect->SetValue(_parameter.c_str(), value, UINT);
}

void Shader::CommitChanges()
{
	m_effect->CommitChanges();
}

void Shader::BeginPass()
{
	ThrowIfFailed(m_effect->Begin(nullptr, 0));
	ThrowIfFailed(m_effect->BeginPass(0));
}

void Shader::EndPass()
{
	ThrowIfFailed(m_effect->End());
	ThrowIfFailed(m_effect->EndPass());
}



void Shader::AddRenderTarget(int _index, const wstring & _rtName)
{

#ifdef _DEBUG
	if(_index < 0 || _index > 3)
	{
		ERR_MSG((L"Put a render target index between 0 and 3 int this " + GetName() + L" shader").c_str());
		assert(0);
	}
#endif // DEBUG

	
	m_renderTarget[_index] = ResourceManager::GetInstance()->GetResource<RenderTarget>(_rtName);

}

void Shader::SetInputLayout(D3DPRIMITIVETYPE _primitive, D3DVERTEXELEMENT9 * _decl, UINT _inputLayoutSize)
{
	m_primitiveType = _primitive;
	m_inputLayoutSize = _inputLayoutSize;
	m_device->CreateVertexDeclaration(_decl, &m_decl);
}
