#pragma once

#ifndef __SHADER_H__
#define __SHADER_H__

#include "IResource.h"

BEGIN(Nalmak)
class NALMAK_DLL Shader :
	public IResource
{
	friend class ResourceManager;
public:
	explicit Shader();
	~Shader();
private:
	virtual void Initialize(wstring _fp) override;

	virtual void Release() override;
public:
	void SetBool(const string& _parameter, bool _value);
	void SetInt(const string& _parameter, int _value);
	void SetFloat(const string& _parameter, float _value);
	void SetMatrix(const string& _parameter, const Matrix& _value);
	void SetTexture(const string& _parameter, PDIRECT3DTEXTURE9 _value);
	void SetVector(const string& _parameter, const Vector4& _vec);
	void SetVector(const string& _parameter, const Vector2& _vec);
	void SetValue(const string& _parameter, void* value, UINT _size);
public:
	HRESULT CheckShaderInitialize();
	wstring GetName() { return m_name; }
	void CommitChanges();
	void BeginPass();
	void EndPass();
private:
	LPD3DXEFFECT m_effect = nullptr;
	IDirect3DVertexDeclaration9* m_decl = nullptr;
	UINT m_inputLayoutSize;
	D3DPRIMITIVETYPE m_primitiveType;


public:
	IDirect3DVertexDeclaration9* GetDeclartion()const { assert("Is not define Vertex Declaration. Please Set Vertex Declaration at Resource Manager Load Shader! " && m_decl); return m_decl; }
	unsigned int GetInputLayoutSize()const { return m_inputLayoutSize; }
	D3DPRIMITIVETYPE GetPrimitiveType() { return m_primitiveType; }
	
public:
	void SetInputLayout(D3DPRIMITIVETYPE _primitive, D3DVERTEXELEMENT9* _decl, UINT _inputLayoutSize);

	template<typename T>
	void SetInputLayout()
	{
		if (typeid(T) == typeid(INPUT_LAYOUT_POSITION_UV))
		{
			m_primitiveType = D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST;
			m_inputLayoutSize = sizeof(INPUT_LAYOUT_POSITION_UV);
			D3DVERTEXELEMENT9 decl[] =
			{
				{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
				{ 0,12,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,0 },
				D3DDECL_END()
			};
			m_device->CreateVertexDeclaration(decl, &m_decl);
		}
		else if (typeid(T) == typeid(INPUT_LAYOUT_POSITION_NORMAL_UV))
		{
			m_primitiveType = D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST;
			m_inputLayoutSize = sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV);
			D3DVERTEXELEMENT9 decl[] =
			{
				{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
				{ 0,12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,  0 },
				{ 0,24,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,0 },
				D3DDECL_END()
			};
			m_device->CreateVertexDeclaration(decl, &m_decl);
		}
		else if (typeid(T) == typeid(INPUT_LAYOUT_POSITION))
		{
			m_primitiveType = D3DPRIMITIVETYPE::D3DPT_LINELIST;
			m_inputLayoutSize = sizeof(INPUT_LAYOUT_POSITION);
			D3DVERTEXELEMENT9 decl[] =
			{
				{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },

				D3DDECL_END()
			};
			m_device->CreateVertexDeclaration(decl, &m_decl);
		}
		else if (typeid(T) == typeid(INPUT_LAYOUT_PARTICLE))
		{
			m_primitiveType = D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST;
			m_inputLayoutSize = sizeof(INPUT_LAYOUT_PARTICLE);
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
			m_device->CreateVertexDeclaration(decl, &m_decl);
		}
		else if (typeid(T) == typeid(INPUT_LAYOUT_STATIC_MESH))
		{
			m_primitiveType = D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST;
			m_inputLayoutSize = sizeof(INPUT_LAYOUT_STATIC_MESH);
			D3DVERTEXELEMENT9 decl[] =
			{
				{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
				{ 0,12,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,0 },
				{ 1,0,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },
				{ 1,16,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },
				{ 1,32,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },
				{ 1,48,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 },
				D3DDECL_END()
			};
			m_device->CreateVertexDeclaration(decl, &m_decl);
		}
		else
		{
			assert("Input Layout is not defined!" && 0);
		}
	}
};
END
#endif // !__SHADER_H__
