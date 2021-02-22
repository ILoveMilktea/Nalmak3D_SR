#include "common_h.fx"

matrix g_world;

texture g_diffuse;
texture g_depth;
texture g_normal;
texture g_light;

sampler DiffuseSampler = sampler_state
{
	texture = g_diffuse;
};
sampler DepthSampler = sampler_state
{
	texture = g_depth;
};
sampler NormalSampler = sampler_state
{
	texture = g_normal;
};
sampler LightSampler = sampler_state
{
	texture = g_light;
};

struct VS_INPUT
{
	float3 position : POSITION;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
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

VS_OUTPUT VS_Main_Default(VS_INPUT _input)
{
	VS_OUTPUT o = (VS_OUTPUT)0; 

	o.position = mul(float4(_input.position,1), g_world);
	o.uv = _input.uv;
	
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;
	float4 diffuse = tex2D(DiffuseSampler, _input.uv);
	float3 normal = tex2D(NormalSampler, _input.uv).xyz;
	float3 light = tex2D(LightSampler, _input.uv).xyz;
	////float3 light = 0.3f;
	//float intensity;
	//if (g_cBuffer.isDirectionalLight == 1)
	//{
	//
	//	if (normal.x == 0 && normal.y == 0 && normal.z == 0)
	//	{
	//		intensity = max(dot(float3(0,1,0), g_cBuffer.directionalLight.direction), 0.) + 0.2f;
	//		light = intensity;
	//	}
	//	else
	//	{
	//		intensity = max(dot(normal, g_cBuffer.directionalLight.direction), 0.0) + 0.2f;
	//		intensity *=  g_cBuffer.directionalLight.intensity;
	//		light = g_cBuffer.directionalLight.color * intensity;
	//	}

	//}
	o.color = diffuse * 0.2f+ float4(light, 1);
	//o.color = 1;
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
