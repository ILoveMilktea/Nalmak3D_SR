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
	float3 pos : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
	float3 normal :NORMAL;
	float4 uvAndDepth : TEXCOORD0; // x,y = uv  z = depth
	float4 worldPos : TEXCOORD1;
};

struct PS_INPUT
{
	float3 normal :NORMAL;
	float4 uvAndDepth : TEXCOORD0;
	float4 worldPos : TEXCOORD1;
};

struct PS_OUTPUT
{
	float4 diffuse : COLOR0;
	float4 normal : COLOR1;
	float4 depth : COLOR2;
	float4 worldPos : COLOR3;

};

VS_OUTPUT VS_Main_Default(VS_INPUT _in)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 

	o.worldPos = mul(float4(_in.pos, 1), g_world);
	o.pos = mul(o.worldPos, g_cBuffer.viewProj);

	o.normal = GetWorldNormal(_in.normal, g_world);

	o.uvAndDepth.xy = _in.uv;
	o.uvAndDepth.zw = o.pos.zw;
	
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _in) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float4 diffuse = tex2D(mainSampler, _in.uvAndDepth.xy);
	o.diffuse = diffuse * g_mainTexColor;

	o.normal = GetScaleBiasNormal(_in.normal);
	
	o.depth = GetDepth(_in.uvAndDepth.zw);

	o.worldPos = _in.worldPos;
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
