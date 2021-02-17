#include "common_h.fx"
matrix g_world;

texture g_diffuse;
texture g_depthStencil;
texture g_normal;

sampler DiffuseSampler = sampler_state
{
	texture = g_diffuse;
};
sampler DepthSampler = sampler_state
{
	texture = g_depthStencil;
};
sampler NormalSampler = sampler_state
{
	texture = g_normal;
};


struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
	float2 screenPos : TEXCOORD0;
};

struct PS_INPUT
{
	float2 screenPos : TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 diffuse : COLOR0;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _input)
{
	VS_OUTPUT o = (VS_OUTPUT)0; 

	float4x4 wvp = mul(g_world, g_cBuffer.viewProj);
	o.position = mul(float4(_input.position,1), wvp);
	o.screenPos = (o.position.xy + 1.0f) * 0.5f;
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	o.diffuse.xy = _input.screenPos;
	o.diffuse.z = 1;


	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z 값에대한 활용

		ZEnable = false;
		ZWriteEnable = false;
		//CullMode = NONE;
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
