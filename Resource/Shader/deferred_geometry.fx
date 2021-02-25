#include "H_common.fx"

matrix g_world;

texture g_diffuse;
texture g_depth;
texture g_normal;
texture g_light;
texture g_transparent;

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
sampler TransSampler = sampler_state
{
	texture = g_transparent;
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

	float3 diffuse = tex2D(DiffuseSampler, _input.uv).xyz;
	float3 normal = tex2D(NormalSampler, _input.uv).xyz;
	float3 light = tex2D(LightSampler, _input.uv).xyz;
	float3 trans = tex2D(TransSampler, _input.uv).xyz;


	float3 final;
	if (normal.x == 0 && normal.y == 0 && normal.z == 0)
	{
		final =  diffuse;
	}
	else
	{
		final = light * diffuse;
	}

	
	o.color = float4(final, 1) + float4(trans,1);

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
