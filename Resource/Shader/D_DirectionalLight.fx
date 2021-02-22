#include "H_common.fx"
#include "H_light.fx"

matrix g_world;
DirectionalLight g_directionalLight;

texture g_diffuse;
texture g_normal;
texture g_depth;


sampler DiffuseSampler = sampler_state
{
	texture = g_diffuse;
};

sampler NormalSampler = sampler_state
{
	texture = g_normal;
};

sampler DepthSampler = sampler_state
{
	texture = g_depth;
};



struct VS_INPUT
{
	float3 pos : POSITION;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
};

struct PS_INPUT
{
	float2 uv :TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 color : COLOR0;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _in)
{
	VS_OUTPUT o = (VS_OUTPUT)0;

	o.pos = mul(float4(_in.pos, 1), g_world);
	o.uv = _in.uv;


	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _in) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float2 uvRT = _in.uv + float2(0.5f / WINCX, 0.5f / WINCY);
	
	float4 diffuse = tex2D(DiffuseSampler, uvRT);
	float3 normal = tex2D(NormalSampler, uvRT).xyz;

	float2 depth = tex2D(DepthSampler, uvRT).xy;
	float4 worldPos = GetWorldPosFromDepth(depth, _in.uv);

	float4 light = CalcLightInternal(g_directionalLight.base, g_cBuffer.worldCamPos, g_directionalLight.direction, worldPos.xyz, normal);

	o.color = light * 2 - 1;

	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z 값에대한 활용

		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
