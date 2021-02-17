#include "common_h.fx"
#include "light_h.fx"


matrix g_world;
PointLight g_pointLight;

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

	o.screenPos = ComputeScreenPos(o.position);

	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float3 diffuse = tex2D(DiffuseSampler, _input.screenPos).xyz;
	float3 normal = tex2D(NormalSampler, _input.screenPos).xyz;
	float depth = tex2D(DepthSampler, _input.screenPos).x;
	float3 worldPos = GetWorldPosFromDepth(depth, _input.screenPos);
	normal = normalize(normal);

	float4 light = float4(diffuse,1) * CalcPointLight(g_pointLight.base, g_pointLight.position, g_cBuffer.worldCamPos, worldPos, normal);

	o.diffuse = light;

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
