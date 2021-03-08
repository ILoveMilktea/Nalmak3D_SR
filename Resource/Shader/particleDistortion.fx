#include "H_common.fx"

matrix g_world;

texture g_distortionTex;
texture g_distortionMask;
texture g_mainTex;

sampler distortionSampler = sampler_state
{
	texture = g_distortionTex;
};

sampler maskSampler = sampler_state
{
	texture = g_distortionMask;
};

sampler mainSampler = sampler_state
{
	texture = g_mainTex;
};

struct VS_INPUT
{
	float3 pos : POSITION;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
	float4 clipPos : TEXCOORD0;
	float2 uv : TEXCOORD1;
};

struct PS_INPUT
{
	float4 clipPos : TEXCOORD0;
	float2 uv :TEXCOORD1;
};

struct PS_OUTPUT
{
	float4 diffuse : COLOR;

};



VS_OUTPUT VS_Main_Default(VS_INPUT _in)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 

	o.pos = float4(_in.pos, 1);

	o.uv = _in.uv;
	
	o.clipPos = o.pos;
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _in) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;
	float2 screenUV = ComputeScreenUV(_in.clipPos);
	float4 mask = tex2D(maskSampler, screenUV + float2(perPixelX, perPixelY));
	clip(mask.r);


	float4 distortion = tex2D(distortionSampler, screenUV + float2(perPixelX, perPixelY));
	float distort = distortion.r;

	float4 screen;
	float2 distortUV = screenUV + distort * 0.02f * mask.x;
	distortUV.y = clamp(distortUV.y, 0, 1);
	screen = tex2D(mainSampler, distortUV - float2(perPixelX, perPixelY));
	o.diffuse = screen;

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
