#include "common_h.fx"

matrix g_world;

texture g_mainTex;
float4 g_mainTexColor;

sampler mainSampler = sampler_state
{
	texture = g_mainTex;

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
	float3 normal :NORMAL;
	float3 uvAndDepth : TEXCOORD0; // x,y = uv  z = depth
	float4 worldPosition : TEXCOORD1;
};

struct PS_INPUT
{
	float3 normal :NORMAL;
	float3 uvAndDepth : TEXCOORD0;
	float4 worldPosition :TEXCOORD1;
};

struct PS_OUTPUT
{
	float4 diffuse : COLOR0;
	float4 normal : COLOR1;
	float4 depth : COLOR2;
	float4 position : COLOR3;
	//float4 motionNSpec : COLOR2;

};

VS_OUTPUT VS_Main_Default(VS_INPUT _input)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 

	o.worldPosition = mul(float4(_input.position, 1), g_world);
	o.position = mul(o.worldPosition, g_cBuffer.viewProj);
	o.normal = _input.normal;
	o.uvAndDepth.xy = _input.uv;
	o.uvAndDepth.z = 1 - (o.position.z / o.position.w);
	
	//o.normal = float3(0, 0, 1);
	
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;
	float4 diffuse = tex2D(mainSampler, _input.uvAndDepth.xy);
	o.diffuse = diffuse * g_mainTexColor;

	o.normal.xyz = ((_input.normal + 1) * 0.5f);
	o.normal.w = 1;

	o.depth = _input.uvAndDepth.z;

	o.position = _input.worldPosition;
	
	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z 값에대한 활용

	/*	ZEnable = true;
		ZWriteEnable = true;
		CullMode = CCW;*/
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
