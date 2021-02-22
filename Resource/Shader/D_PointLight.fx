#include "common_h.fx"
#include "light_h.fx"


matrix g_world;
PointLight g_pointLight;

texture g_diffuse;
texture g_normal;
texture g_depth;
texture g_position;

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

sampler PositionSampler = sampler_state
{
	texture = g_position;
};

struct VS_INPUT
{
	float3 pos : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
	float4 clipPos : TEXCOORD0;
};

struct PS_INPUT
{
	float4 clipPos : TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 diffuse : COLOR0;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _in)
{
	VS_OUTPUT o = (VS_OUTPUT)0; 

	float4x4 wvp = mul(g_world, g_cBuffer.viewProj);
	o.pos = mul(float4(_in.pos,1), wvp);

	o.clipPos = o.pos;


	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _in) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float2 uv = ComputeScreenUV(_in.clipPos);
	float2 uvRT = uv +float2(0.5f / WINCX, 0.5f / WINCY);

	float3 diffuse = tex2D(DiffuseSampler, uvRT).xyz;
	float3 normal = tex2D(NormalSampler, uvRT).xyz;
	normal = normal * 2.f - 1.f;
	

	float2 depth = tex2D(DepthSampler, uvRT).xy;
	float4 worldPos = GetWorldPosFromDepth(depth, uv);

	//float3 test = worldPos.xyz - g_pointLight.position;

	float4 light =  CalcPointLight(g_pointLight, g_cBuffer.worldCamPos, worldPos.xyz, normal);

	o.diffuse = float4(diffuse,1) *light;
	//o.diffuse = worldPos;
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
