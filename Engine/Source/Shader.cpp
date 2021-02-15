#include "..\Include\Shader.h"


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
	LPD3DXBUFFER error = NULL;

	DWORD dwShaderFlags = 0;

#if _DEBUG
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

	D3DXCreateEffectFromFile(
		m_device,
		_fp.c_str(),
		nullptr, // 전처리기
		nullptr,
		dwShaderFlags,		 // 컴파일 플래그
		NULL,
		&m_effect,
		&error
	);


	//if (error)
	//{
	//	void* ack = error->GetBufferPointer();
	//	MessageBoxA(nullptr, (char*)ack, "Shader Compile Fail", MB_OK);

	//	assert(!error);
	//}
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

void Shader::SetInputLayout(D3DPRIMITIVETYPE _primitive, D3DVERTEXELEMENT9 * _decl, UINT _inputLayoutSize)
{
	m_primitiveType = _primitive;
	m_inputLayoutSize = _inputLayoutSize;
	m_device->CreateVertexDeclaration(_decl, &m_decl);
}
